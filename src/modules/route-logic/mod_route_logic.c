#include <mod_route_logic.h>


void mod_route_logic_load(core_module_t *module) {
  core_status_t rv;
  core_pool_t *pool = NULL;
  route_logic_context_t *context = NULL;
  /* core_hash_t *trans_proxy_table; */
  core_mutex_t *trans_proxy_table_lock = NULL;
  
  pool = module->pool;
  
  printf("mod_route_logic: loading module\n");

  /* create and allocate memory for modules context */
  module->context = (core_module_context_t *) core_palloc(pool, sizeof(route_logic_context_t));
  context = (route_logic_context_t *) module->context;
  context->module_shutdown = 0;


  /* create trans table */
  context->trans_proxy_table = core_hash_make(pool);

  /* create trans table lock */
  rv = core_mutex_create(pool, &(trans_proxy_table_lock), CORE_MUTEX_NESTED);
  if(rv != CORE_SUCCESS) {
    printf("mod_route_logic: could not create lock for route_logic modules trans_proxy table\n");
    return;
  }
  context->trans_proxy_table_lock = trans_proxy_table_lock;

  /* create modules input queue */
  module->queue = core_palloc(module->pool, sizeof(core_queue_t *));
  rv = core_queue_create(&(module->queue), QUEUE_SIZE, module->pool);

  if (rv == CORE_SUCCESS) // on a successful pop
    printf("mod_route_logic: successfully created modules input message queue\n");


  /* subscribe for related events */
  if(module->queue) {
    core_event_subscribe("sip_i_trans", module->queue);
    core_event_subscribe("sip_r_trans", module->queue);
    core_event_subscribe("diam_r_trans", module->queue);
  }

  /* create modules msg consumer thread */
  rv = core_thread_create(
			 &(context->consumer_thread),
			 NULL,
			 (core_thread_start_t) route_logic_core_msg_consumer,
			 (void *) module,
			 pool);
  
  if (rv == CORE_SUCCESS) // on success 
    printf("mod_route_logic: successfully created modules msg. consumer thread\n");

}

void mod_route_logic_destroy(core_module_t *module) {
  core_status_t rv;
  route_logic_context_t *context = NULL;
  /* rv = core_queue_term(module->queue); */
  /* if (rv == CORE_SUCCESS) // on success  */
  /*   printf("mod_route_logic: queue terminated\n"); */

  context = (route_logic_context_t *) module->context;
  context->module_shutdown = 1;
  core_queue_interrupt_all(module->queue);
  rv = core_thread_join(&rv, context->consumer_thread);
  if (rv == CORE_SUCCESS) // on success 
    printf("mod_route_logic: thread terminated\n");

  module->queue = NULL;

}

static void * route_logic_core_msg_consumer(core_thread_t *thd, core_module_t *module) {
  
  core_status_t rv;
  void *v = NULL;
  core_event_t * event;
  route_logic_context_t *context = NULL;

  context = (route_logic_context_t *) module->context;
  

  while (1) {

    if(module && module->queue) {

      if((core_queue_size(module->queue) == 0) && (context->module_shutdown == 1)) {
	
	rv = core_queue_term(module->queue);
	if (rv == CORE_SUCCESS) // on success
	  printf("mod_route_logic: queue terminated\n");
	
	printf("mod_route_logic: exiting msg consumer thread\n");
	core_thread_exit(thd, CORE_SUCCESS);      
      }
      
      rv = core_queue_pop(module->queue, &v);
    }
    else {
      printf("mod_route_logic: exiting msg consumer thread\n");
      core_thread_exit(thd, CORE_SUCCESS);      
    }

    switch(rv) {
    case CORE_INTR:
      printf("mod_route_logic: queue was interrupted\n");
      break;
    case CORE_NOTFOUND:
      printf("mod_route_logic: the queue has been terminated\n");
      core_thread_exit(thd, CORE_SUCCESS);      
      return NULL;
    case CORE_SUCCESS:
      event = (core_event_t *) v;
      route_logic_handle_core_event(event, context);
      core_event_destroy(event);
    }
    continue;
    
  }

  return NULL;
}


