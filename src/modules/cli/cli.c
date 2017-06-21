#include <core.h>
#include <cli.h>

void mod_cli_load(core_module_t *module) {
  apr_status_t rv;
  apr_pool_t *pool;

  pool = module->pool;
  
  printf("mod_cli: loading module\n");
  
  module->context = (core_context_t *) core_palloc(pool, sizeof(cli_context_t));
  cli_context_t *context = (cli_context_t *) module->context;

  rv = apr_thread_create(
			 &(context->consumer_thread),
			 NULL,
			 (apr_thread_start_t) cli_core_msg_consumer,
			 (void *) module,
			 pool);

  if (rv == APR_SUCCESS) // on success 
    printf("mod_cli: successfully created modules msg. consumer thread\n");

  printf("mod_cli: creating message consumer\n");
  
}

void mod_cli_destroy(core_module_t *module) {
  apr_status_t rv;
  rv = apr_queue_term(module->mqueue->queue);
  if (rv == APR_SUCCESS) // on success 
    printf("mod_cli: successfully destroyed the module\n");
  
}

static void * APR_THREAD_FUNC cli_core_msg_consumer(apr_thread_t *thd, core_module_t *module) {
  
  apr_status_t rv;
  void *v = NULL;

  
  module->mqueue = core_palloc(module->pool, sizeof(core_mqueue_t));

  rv = core_queue_create(&(module->mqueue->queue), QUEUE_SIZE, module->pool);


  if (rv == APR_SUCCESS) // on a successful pop
    printf("mod_cli: successfully created modules input message queue\n");


  while (1) {
    printf("mod_cli: entering thread\n");

    rv = apr_queue_pop(module->mqueue->queue, &v);
    
    if (rv == APR_EINTR) // the blocking was interrupted (try again)
      printf("mod_cli: the blocking was interrupted\n");
    
    if (rv == APR_EOF) { // if the queue has been terminated
      printf("mod_cli: the queue has been terminated\n");
      break;
    }
    
    if (rv == APR_SUCCESS) { // on a successful pop
      printf("mod_cli: the pop was successful\n");
      int *k = (int *)v;
      printf("mod_cli: poping %d\n", *k);
      continue;
    }
    
    if (rv == APR_EAGAIN) // the queue is empty
      printf("mod_cli: the queue is empty\n");
    
  }

  return NULL;
}

