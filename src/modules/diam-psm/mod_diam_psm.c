#include <core.h>
#include <core_event.h>
#include <mod_diam_psm.h>

static struct fd_config conf;
extern struct fd_config *fd_g_config;

void mod_diam_psm_load(core_module_t *module) {
  core_status_t rv;
  core_pool_t *pool = NULL;
  diam_psm_context_t *context = NULL;
  
  pool = module->pool;
  
  printf("mod_diam_psm: loading module\n");

  module->context = (core_module_context_t *) core_palloc(pool, sizeof(diam_psm_context_t));
  context = (diam_psm_context_t *) module->context;
  context->module_shutdown = 0;
  
  module->queue = core_palloc(module->pool, sizeof(core_queue_t *));
  rv = core_queue_create(&(module->queue), QUEUE_SIZE, module->pool);

  if (rv == CORE_SUCCESS) // on a successful pop
    printf("mod_diam_psm: successfully created modules input message queue\n");


  if(module->queue) {
    core_event_subscribe("diam_psm_do_request", module->queue);
    core_event_subscribe("diam_psm_do_repond", module->queue);
  }

  diam_psm_fd_init();

  rv = core_thread_create(
			 &(context->consumer_thread),
			 NULL,
			 (core_thread_start_t) diam_psm_core_msg_consumer,
			 (void *) module,
			 pool);
  
  if (rv == CORE_SUCCESS) // on success 
    printf("mod_diam_psm: successfully created modules msg. consumer thread\n");

}

void mod_diam_psm_destroy(core_module_t *module) {
  core_status_t rv;
  diam_psm_context_t *context = NULL;
  /* rv = core_queue_term(module->queue); */
  /* if (rv == CORE_SUCCESS) // on success  */
  /*   printf("mod_diam_psm: queue terminated\n"); */

  context = (diam_psm_context_t *) module->context;
  context->module_shutdown = 1;
  core_queue_interrupt_all(module->queue);
  rv = core_thread_join(&rv, context->consumer_thread);
  if (rv == CORE_SUCCESS) // on success 
    printf("mod_diam_psm: thread terminated\n");

  module->queue = NULL;
  diam_psm_fd_fini();

}

static void * diam_psm_core_msg_consumer(core_thread_t *thd, core_module_t *module) {
  
  core_status_t rv;
  void *v = NULL;
  core_event_t * event;
  diam_psm_context_t *context = NULL;

  context = (diam_psm_context_t *) module->context;
  

  while (1) {

    if(module && module->queue) {

      if((core_queue_size(module->queue) == 0) && (context->module_shutdown == 1)) {
	
	rv = core_queue_term(module->queue);
	if (rv == CORE_SUCCESS) // on success
	  printf("mod_diam_psm: queue terminated\n");
	
	printf("mod_diam_psm: exiting msg consumer thread\n");
	core_thread_exit(thd, CORE_SUCCESS);      
      }
      
      rv = core_queue_pop(module->queue, &v);
    }
    else {
      printf("mod_diam_psm: exiting msg consumer thread\n");
      core_thread_exit(thd, CORE_SUCCESS);      
    }

    switch(rv) {
    case CORE_INTR:
      printf("mod_diam_psm: queue was interrupted\n");
      break;
    case CORE_NOTFOUND:
      printf("mod_diam_psm: the queue has been terminated\n");
      core_thread_exit(thd, CORE_SUCCESS);      
      return NULL;
    case CORE_SUCCESS:
      event = (core_event_t *) v;
      diam_psm_handle_core_event(event);
      core_event_destroy(event);
    }
    continue;
    
  }

  return NULL;
}



void diam_psm_handle_core_event(core_event_t * event) {

  core_event_header_t *next = NULL;
  char * Param01 = NULL;
  
  /* printf("> An Event has been received\n"); */
  if(Param01 = core_event_header_get(event, "Param01")) {
    /* printf("> Param01 is: '%s'\n", Param01); */
  }

  my_main();
}


void diam_psm_fd_init() {

  fd_g_config = &conf;
  memset(fd_g_config, 0, sizeof(struct fd_config));
  /* fd_g_debug_lvl--; */
  /* fd_g_debug_lvl--; */
	
  fd_libproto_init();
  fd_dict_init(&fd_g_config->cnf_dict) ;
  fd_dict_base_protocol(fd_g_config->cnf_dict);
	

}


void diam_psm_fd_fini() {
    fd_dict_fini(&fd_g_config->cnf_dict) ;
}


void my_main() {

  struct msg * acr = NULL;
  struct avp * pi = NULL, *avp1, *avp2;
  unsigned char * buf = NULL;
  struct avp_hdr * avpdata = NULL;
  struct msg_hdr * msgdata = NULL;

  
  /* Create the message object from model */
  struct dict_object * acr_model = NULL;
  fd_dict_search ( fd_g_config->cnf_dict, DICT_COMMAND, CMD_BY_NAME, "Accounting-Request", &acr_model, ENOENT );
  fd_msg_new ( acr_model, 0, &acr );
  fd_msg_browse ( acr, MSG_BRW_FIRST_CHILD, NULL, NULL);

  
  /* Create the Proxy-Info AVP from model */
  struct dict_object * pi_model = NULL;
  fd_dict_search ( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Proxy-Info", &pi_model, ENOENT );
  fd_msg_avp_new ( pi_model, 0, &pi );
  fd_msg_avp_add ( acr, MSG_BRW_LAST_CHILD, pi) ;
  

  /* 		#define ADD_AVP( _parent, _position, _avpi, _avpvendor, _avpname) {			\ */
  /* 			struct dict_object * _avp = NULL;						\ */
  /* 			struct dict_avp_request _req = { (_avpvendor), 0, (_avpname) };			\ */
  /* 			CHECK( 0, fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &_req, &_avp, ENOENT));\ */
  /* 			CHECK( 0, fd_msg_avp_new ( _avp, 0, &_avpi ) );					\ */
  /* 			CHECK( 0, fd_msg_avp_add ( (_parent), (_position), _avpi ) );			\ */
  /* 		} */

  
  fd_msg_hdr ( acr, &msgdata );
  /* msgdata->msg_appl = 73566; */			
  msgdata->msg_hbhid = 0x4b44b41d;
  msgdata->msg_eteid = 0xe2ee2e1d;


  fd_msg_update_length ( acr );
  fd_msg_bufferize( acr, &buf, NULL );

  /* printf("first>>>%d\n", buf[0]); */
  printf("size>>>>%d\n", msgdata->msg_length);
  
  free(buf);
  fd_msg_free( pi );
  fd_msg_free( acr );
  /* fd_log_notice("%s", fd_msg_dump_treeview(FD_DUMP_TEST_PARAMS, acr, fd_g_config->cnf_dict, 0, 1)); */
	

}
