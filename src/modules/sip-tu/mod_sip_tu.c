#include <core.h>
#include <core_event.h>
#include <mod_sip_tu.h>


void mod_sip_tu_load(core_module_t *module) {
  core_status_t rv;
  core_pool_t *pool = NULL;
  sip_tu_module_context_t *context = NULL;
  
  pool = module->pool;
  
  printf("mod_sip_tu: loading module\n");

  module->context = (core_module_context_t *) core_palloc(pool, sizeof(sip_tu_module_context_t));
  context = (sip_tu_module_context_t *) module->context;
  context->module_shutdown = 0;
  
  module->queue = core_palloc(module->pool, sizeof(core_queue_t *));
  rv = core_queue_create(&(module->queue), QUEUE_SIZE, module->pool);

  if (rv == CORE_SUCCESS) // on a successful pop
    printf("mod_sip_tu: successfully created modules input message queue\n");


  if(module->queue) {
    core_event_subscribe("sip_tu_do_request", module->queue);
    core_event_subscribe("sip_tu_do_respond", module->queue);
  }


  
  rv = core_thread_create(&(context->consumer_thread), NULL,
			 (core_thread_start_t) sip_tu_core_msg_consumer,
			 (void *) module, pool);
  
  if (rv == CORE_SUCCESS) // on success 
    printf("mod_sip_tu: successfully created modules msg. consumer thread\n");



  rv = core_thread_create(&(context->sofia_thread), NULL,
			 (core_thread_start_t) sip_tu_sofia_worker,
			 (void *) module, pool);
  
  if (rv == CORE_SUCCESS) // on success 
    printf("mod_sip_tu: successfully created sofia worker thread\n");


}

void mod_sip_tu_destroy(core_module_t *module) {
  core_status_t rv;
  sip_tu_module_context_t *context = NULL;

  context = (sip_tu_module_context_t *) module->context;
  context->module_shutdown = 1;
  core_queue_interrupt_all(module->queue);
  rv = core_thread_join(&rv, context->consumer_thread);
  if (rv == CORE_SUCCESS) // on success 
    printf("mod_sip_tu: thread terminated\n");

  module->queue = NULL;

}

static void * sip_tu_core_msg_consumer(core_thread_t *thd, core_module_t *module) {
  
  core_status_t rv;
  void *v = NULL;
  core_event_t * event;
  sip_tu_module_context_t *context = NULL;

  context = (sip_tu_module_context_t *) module->context;
  

  while (1) {

    if(module && module->queue) {

      if((core_queue_size(module->queue) == 0) && (context->module_shutdown == 1)) {
	
	rv = core_queue_term(module->queue);
	if (rv == CORE_SUCCESS) // on success
	  printf("mod_sip_tu: queue terminated\n");
	
	printf("mod_sip_tu: exiting msg consumer thread\n");
	core_thread_exit(thd, CORE_SUCCESS);      
      }
      
      rv = core_queue_pop(module->queue, &v);
    }
    else {
      printf("mod_sip_tu: exiting msg consumer thread\n");
      core_thread_exit(thd, CORE_SUCCESS);      
    }

    switch(rv) {
    case CORE_INTR:
      printf("mod_sip_tu: queue was interrupted\n");
      break;
    case CORE_SUCCESS:
      event = (core_event_t *) v;
      sip_tu_handle_core_event(event);
      core_event_destroy(event);
    }
    continue;
    
  }

  return NULL;
}



static void * sip_tu_sofia_worker(core_thread_t *thd, core_module_t *module) {
  
  core_status_t rv;
  void *v = NULL;
  core_event_t * event;
  sip_tu_module_context_t *context = NULL;

  context = (sip_tu_module_context_t *) module->context;

  sip_tu_sofia_init();

  return NULL;
}

void sip_tu_handle_core_event(core_event_t * event) {

  sip_tu_trans_context_t * sip_tu_ctx;
  core_trans_t *trans = NULL;
  char * trans_id = NULL;
  char * status_code = NULL;
  nta_outgoing_t * orq = NULL;
  core_event_t * my_event = NULL;
  sofia_magic_t * sip_tu_magic = NULL;
  char *originator_id = NULL;
  char *sip_method = NULL;
  char *sip_call_id = NULL;
  char *sip_cseq = NULL;
  char *sip_to = NULL;
  char *sip_from = NULL;
  char *sip_contact = NULL;
  char *sip_www_auth = NULL;
  char *sip_authorization = NULL;
  
  if(!event) {
    return;
  }

  if(!strcmp(event->name, "sip_tu_do_respond") ) {
    trans_id = core_event_header_get(event, "trans-id");
    sip_method = core_event_header_get(event, "sip-method");
    status_code = core_event_header_get(event, "sip-status");
    sip_to = core_event_header_get(event, "sip-to");
    sip_from = core_event_header_get(event, "sip-from");
    sip_contact = core_event_header_get(event, "sip-contact");
    sip_www_auth = core_event_header_get(event, "sip-www-authenticate");


    printf("mod_sip_tu: sip_tu_do_respond commands recieved for '%s' with status code '%s'\n", trans_id, status_code);
    if(trans = core_trans_get(trans_id)) {

      sip_tu_ctx = (sip_tu_trans_context_t *) core_trans_get_context(trans);

      if(sip_tu_ctx && sip_tu_ctx->irq) {
	printf("got context '%p', '%p'\n", (void *)sip_tu_ctx, (void *) (sip_tu_ctx->irq));



	if(!strcmp(status_code, "200")) {

	  nta_incoming_treply(sip_tu_ctx->irq, SIP_200_OK,
			      TAG_END());

	}
	else if(!strcmp(status_code, "401")) {
	  	  
	  nta_incoming_treply(sip_tu_ctx->irq, SIP_401_UNAUTHORIZED,
			      SIPTAG_WWW_AUTHENTICATE_STR(sip_www_auth),
			      TAG_END());
	  
	}
	else if(!strcmp(status_code, "407")) {

	  nta_incoming_treply(sip_tu_ctx->irq, SIP_407_PROXY_AUTH_REQUIRED,
			      TAG_END());

	}
	else if(!strcmp(status_code, "500")) {

	  nta_incoming_treply(sip_tu_ctx->irq, SIP_500_INTERNAL_SERVER_ERROR,
			      TAG_END());

	}
      }
      else {
	printf("empty context '%p', '%p'\n", (void *)sip_tu_ctx, (void *) (sip_tu_ctx->irq));
      }
      
      core_trans_rwunlock(trans);
    }
    else {
      printf("transaction not found\n");
    }
  }
  else if(!strcmp(event->name, "sip_tu_do_request") ) {

    /* create core transaction */
    if(trans = core_trans_create(NULL, CORE_TRANS_OUTBOUND)) {

      /* strcpy(trans_id, core_trans_uuid(trans)); */
      originator_id = core_event_header_get(event, "originator-id");
      sip_method = core_event_header_get(event, "sip-method");
      sip_call_id = core_event_header_get(event, "sip-call-id");
      sip_cseq = core_event_header_get(event, "sip-cseq");
      sip_to = core_event_header_get(event, "sip-to");
      sip_from = core_event_header_get(event, "sip-from");
      sip_contact = core_event_header_get(event, "sip-contact");
      sip_authorization = core_event_header_get(event, "sip-authorization");


      printf("sip_to: %s\n", sip_to);
      printf("sip_from: %s\n", sip_from);
      printf("sip_contact: %s\n", sip_contact);
      
      printf("mod_sip_tu: outbound transaction successfully created! (%s)\n", sip_authorization);

      /* create sip_tu context */
      sip_tu_ctx = core_trans_alloc(trans, sizeof(sip_tu_trans_context_t));
      sip_tu_magic = core_trans_alloc(trans, sizeof(sofia_magic_t));

      /* create sofia nta outgoing request */
      orq = nta_outgoing_tcreate(internal_leg, sip_tu_sofia_outgoing_callback, NULL,
				 (const url_string_t *)"sip:192.168.233.12", // proxy url
				 SIP_METHOD_REGISTER, /*  */
				 (const url_string_t *)"sip:192.168.233.12",
				 TAG_IF(sip_call_id && strlen(sip_call_id), SIPTAG_CALL_ID_STR(sip_call_id)),
				 TAG_IF(sip_cseq && strlen(sip_cseq), SIPTAG_CSEQ_STR(sip_cseq)),
				 TAG_IF(sip_to && strlen(sip_to), SIPTAG_TO_STR(sip_to)),
				 TAG_IF(sip_from && strlen(sip_from), SIPTAG_FROM_STR(sip_from)),
				 TAG_IF(sip_contact && strlen(sip_contact), SIPTAG_CONTACT_STR(sip_contact)),
				 TAG_IF(sip_authorization && strlen(sip_authorization), SIPTAG_AUTHORIZATION_STR(sip_authorization)),
				 TAG_END());
      
      sip_tu_magic->trans_id = core_trans_uuid(trans);
      sip_tu_magic->origin_id = core_trans_pstrdup(trans, originator_id);

      if(orq) {
	nta_outgoing_bind(orq, sip_tu_sofia_outgoing_callback, (nta_outgoing_magic_t *)sip_tu_magic );
	
	printf("mod_sip_tu: created outgoing request '%p' authorization header: '%s'\n", (void *) orq, sip_authorization ? sip_authorization : "null");
      
	sip_tu_ctx->orq = orq;

	/* assign sip-tu context */
	core_trans_set_context(trans, (core_trans_context_t *) sip_tu_ctx);
      }
      else {

	my_event = core_event_create("sip_r_trans", 0, NULL);

	core_event_header_add(my_event, "originator-id", originator_id);
	core_event_header_add(my_event, "trans-id", trans_id);
	core_event_header_add(my_event, "sip-method", sip_method);
	core_event_header_add(my_event, "sip-status", "500");

	core_event_publish(my_event, 0);

      }

      core_trans_rwunlock(trans);
    }
  }

  
  
}

void sip_tu_sofia_init() {
  /* initialize system utilities */
  su_init();

  /* initialize memory handling */
  su_home_init(home);

  /* initialize root object */
  root = su_root_create(NULL);

  if (root) {

    // create nta agents
    external_agent = nta_agent_create(root,
				      (const url_string_t *)"sip:192.168.233.190", // sip url
				      NULL, NULL, TAG_END());

    internal_agent = nta_agent_create(root,
				      (const url_string_t *)"sip:192.168.233.170", // sip url
				      NULL, NULL, TAG_END());


    // create nta legs
    external_leg = nta_leg_tcreate(external_agent,
				   sip_tu_sofia_incoming_callback,
				   NULL,
				   URLTAG_URL("sip:192.168.233.190"),
				   NTATAG_NO_DIALOG(1),
				   TAG_END());

    internal_leg = nta_leg_tcreate(internal_agent,
				   sip_tu_sofia_incoming_callback,
				   NULL,
				   URLTAG_URL("sip:192.168.233.170"),
				   NTATAG_NO_DIALOG(1),
				   TAG_END());
    
    // run
    su_root_run(root);

    /* deinit root object */
    su_root_destroy(root);
    root = NULL;
  }

  /* deinitialize memory handling */
  su_home_deinit(home);

  /* deinitialize system utilities */
  su_deinit();
}




int sip_tu_sofia_incoming_callback(nta_leg_magic_t *context, nta_leg_t *leg, nta_incoming_t *irq, const sip_t *sip) {
  core_event_t * my_event;
  core_trans_t *trans = NULL;
  sip_tu_trans_context_t * sip_tu_ctx;
  char trans_id[1024];
  char sip_method[998];
  char sip_cseq[998];
  char sip_authorization[998];
  char sip_to[998];
  char sip_from[998];
  char sip_contact[998];
  char sip_www_authenticate[998];
  core_size_t header_size;
  /* printf("incoming event\n"); */
  
  memset(trans_id, '\0', sizeof(trans_id));
  memset(sip_method, '\0', sizeof(sip_method));
  memset(sip_cseq, '\0', sizeof(sip_cseq));
  memset(sip_authorization, '\0', sizeof(sip_authorization));
  memset(sip_to, '\0', sizeof(sip_to));
  memset(sip_from, '\0', sizeof(sip_from));
  memset(sip_contact, '\0', sizeof(sip_contact));
  memset(sip_www_authenticate, '\0', sizeof(sip_www_authenticate));

  switch(sip->sip_request->rq_method) {
  case sip_method_register:

    /* create core transaction */
    if(trans = core_trans_create(NULL, CORE_TRANS_INBOUND)) {

      strcpy(trans_id, core_trans_uuid(trans));
      
      printf("mod_sip_tu: inbound transaction successfully created! \n");
      /* create sip_tu context */
      sip_tu_ctx = core_trans_alloc(trans, sizeof(sip_tu_trans_context_t));
      sip_tu_ctx->irq = irq;
      /* assign sip-tu context */
      core_trans_set_context(trans, (core_trans_context_t *) sip_tu_ctx);

      core_trans_rwunlock(trans);
    }

    if (!trans_id || *trans_id == '\0') { /* empty string */
      return 500;
    }

    if(sip && sip->sip_request && sip->sip_request->rq_method_name) {
      strcpy(sip_method, sip->sip_request->rq_method_name);
    }
    if(sip_cseq(sip)) {
      header_size = sip_cseq_e (sip_cseq, 512, (msg_header_t *) sip_cseq(sip), 0);
    }
    if(sip_authorization(sip)) {
      header_size = sip_authorization_e (sip_authorization, 512, (msg_header_t *) sip_authorization(sip), 0);
    }
    if(sip_to(sip)) {
      header_size = sip_to_e (sip_to, 512, (msg_header_t *) sip_to(sip), 0);
    }
    if(sip_from(sip)) {
      header_size = sip_from_e (sip_from, 512, (msg_header_t *) sip_from(sip), 0);
    }
    if(sip_contact(sip)) {
      header_size = sip_contact_e (sip_contact, 512, (msg_header_t *) sip_contact(sip), 0);
    }
    if(sip_www_authenticate(sip)) {
      header_size = sip_www_authenticate_e (sip_www_authenticate, 128, (msg_header_t *)sip_www_authenticate(sip), 0);
    }

    printf("mod_sip_tu: trans_id: '%s' (irq: '%p') method: %s\n", trans_id, (void *) irq, sip_method);//process = process_register;


    my_event = core_event_create("sip_i_trans", 0, NULL);

    core_event_header_add(my_event, "trans-id", trans_id);
    core_event_header_add(my_event, "sip-method", sip_method);
    core_event_header_add(my_event, "sip-call-id", sip->sip_call_id->i_id);
    core_event_header_add(my_event, "sip-cseq", sip_cseq);
    core_event_header_add(my_event, "sip-to", sip_to);
    core_event_header_add(my_event, "sip-from", sip_from);
    core_event_header_add(my_event, "sip-contact", sip_contact);
    core_event_header_add(my_event, "sip-authorization", sip_authorization);

    core_event_publish(my_event, 0);
    
    printf("mod_sip_tu: published 'sip_i_trans' event.\n");
    
    break;
  case sip_method_publish:
    printf("PUBLISH\n");//process = process_options;
    break;
  case sip_method_subscribe:
    printf("SUBSCRIBE\n");//process = process_options;
    break;
  case sip_method_options:
    printf("OPTIONS\n");//process = process_options;
    break;
  }


  return 0;

}


int sip_tu_sofia_outgoing_callback(nta_outgoing_magic_t * sip_tu_magic, nta_outgoing_t *orq, sip_t const *sip) {
  core_event_t * my_event;
  char sip_status[10];
  char sip_method[998];

  char trans_id[1024];
  char sip_call_id[998];
  char sip_cseq[998];
  char sip_authorization[998];
  char sip_to[998];
  char sip_from[998];
  char sip_contact[998];
  char sip_www_authenticate[998];
  core_size_t header_size;

  memset(trans_id, '\0', sizeof(trans_id));
  memset(sip_call_id, '\0', sizeof(sip_call_id));
  memset(sip_cseq, '\0', sizeof(sip_cseq));
  memset(sip_authorization, '\0', sizeof(sip_authorization));
  memset(sip_to, '\0', sizeof(sip_to));
  memset(sip_from, '\0', sizeof(sip_from));
  memset(sip_contact, '\0', sizeof(sip_contact));
  memset(sip_www_authenticate, '\0', sizeof(sip_www_authenticate));

  if(sip_call_id(sip)) {
    header_size = sip_call_id_e (sip_call_id, 512, (msg_header_t *) sip_call_id(sip), 0);
  }
  if(sip_cseq(sip)) {
    header_size = sip_cseq_e (sip_cseq, 512, (msg_header_t *) sip_cseq(sip), 0);
  }
  if(sip_authorization(sip)) {
    header_size = sip_authorization_e (sip_authorization, 512, (msg_header_t *) sip_authorization(sip), 0);
  }
  if(sip_to(sip)) {
    header_size = sip_to_e (sip_to, 512, (msg_header_t *) sip_to(sip), 0);
  }
  if(sip_from(sip)) {
    header_size = sip_from_e (sip_from, 512, (msg_header_t *) sip_from(sip), 0);
  }
  if(sip_contact(sip)) {
    header_size = sip_contact_e (sip_contact, 512, (msg_header_t *) sip_contact(sip), 0);
  }
  if(sip_www_authenticate(sip)) {
    header_size = sip_www_authenticate_e (sip_www_authenticate, 128, (msg_header_t *)sip_www_authenticate(sip), 0);
  }

  printf("mod_sip_tu: response received \n");
  sprintf(sip_status, "%d", sip->sip_status->st_status);

  my_event = core_event_create("sip_r_trans", 0, NULL);

  core_event_header_add(my_event, "originator-id", ((sofia_magic_t *) sip_tu_magic)->origin_id);
  core_event_header_add(my_event, "trans-id", ((sofia_magic_t *) sip_tu_magic)->trans_id);
  core_event_header_add(my_event, "sip-status", sip_status);
  core_event_header_add(my_event, "sip-to", sip_to);
  core_event_header_add(my_event, "sip-from", sip_from);
  core_event_header_add(my_event, "sip-contact", sip_contact);
  core_event_header_add(my_event, "sip-www-authenticate", sip_www_authenticate);

  core_event_publish(my_event, 0);
  return 0;
}
