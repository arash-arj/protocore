#include <core.h>
#include <core_event.h>
#include <radius.h>

void mod_radius_load(core_module_t *module) {
  apr_status_t rv;
  apr_pool_t *pool;

  pool = module->pool;
  
  printf("mod_radius: loading module\n");

  module->context = (core_context_t *) core_palloc(pool, sizeof(radius_context_t *));
  radius_context_t *context = (radius_context_t *) module->context;

  rv = apr_thread_create(
			 &(context->consumer_thread),
			 NULL,
			 (apr_thread_start_t) radius_core_msg_consumer,
			 (void *) module,
			 pool);
  
  if (rv == APR_SUCCESS) // on success 
    printf("mod_radius: successfully created modules msg. consumer thread\n");

  printf("mod_radius: creating message consumer\n");
  
}

void mod_radius_destroy(core_module_t *module) {
  apr_status_t rv;
  apr_pool_t *pool;
  pool = module->pool;
  apr_queue_term(module->mqueue->queue);
}

static void * APR_THREAD_FUNC radius_core_msg_consumer(apr_thread_t *thd, core_module_t *module) {
  
  apr_status_t rv;
  void *v = NULL;

  module->mqueue = core_palloc(module->pool, sizeof(core_mqueue_t *));
  rv = core_queue_create(&(module->mqueue->queue), QUEUE_SIZE, module->pool);

  if (rv == APR_SUCCESS) // on a successful pop
    printf("mod_radius: successfully created modules input message queue\n");


  while (1) {
    //printf("mod_radius: entering thread\n");

    rv = apr_queue_pop(module->mqueue->queue, &v);
    
    if (rv == APR_EINTR) // the blocking was interrupted (try again)
      printf("mod_radius: the blocking was interrupted\n");
    
    if (rv == APR_EOF) { // if the queue has been terminated
      printf("mod_radius: the queue has been terminated\n");
      break;
    }

    core_event_t* event = (core_event_t *) v;
    if (rv == APR_SUCCESS) { // on a successful pop
      int * data = (int *) (event->data);
      //printf("%d\n", *data);
      apr_pool_destroy(event->pool);

      continue;
    }
    
    if (rv == APR_EAGAIN) // the queue is empty
      printf("mod_radius: the queue is empty\n");
    
  }

  return NULL;
}

