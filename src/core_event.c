#include <core.h>
#include <core_event.h>
#include <core_mqueue.h>
#include <core_apr.h>

/* worker thread function which dispatches the messages to modules */
static void * APR_THREAD_FUNC core_msg_dispatcher_worker(apr_thread_t *, core_event_server_t *);



// Create our message dispatcher
core_event_server_t *core_event_server_create() {
  int i;
  apr_status_t rv;
  core_event_server_t *ev_server;
  
  // Allocate and initialize event servers memory pool
  // create event servers memory pool
  apr_pool_t *pool;
  rv = apr_pool_create(&pool, NULL);
  if(rv != APR_SUCCESS) {
    goto error;
  }

  /* allocate the event server object */
  ev_server = core_palloc(pool, sizeof (core_event_server_t));

  for(i = 0; i < NUM_PRIORITY_LEVELS; i++) {
    core_mqueue_t * mqueue = NULL;
    mqueue = core_palloc(pool, sizeof(core_mqueue_t));
    rv = core_queue_create(&(mqueue->queue), QUEUE_SIZE, pool);
    if (rv == APR_SUCCESS) { // on a successful pop
      printf("core: successfully created modules input message queue\n");
      ev_server->queues[i] = mqueue;
    }
  }

  core_mqueue_t * sem_queues = NULL;
  sem_queues = core_palloc(pool, sizeof(core_mqueue_t));
  rv = core_queue_create(&(sem_queues->queue), QUEUE_SIZE * NUM_PRIORITY_LEVELS, pool);
  if (rv == APR_SUCCESS) { // on a successful pop
    printf("core: successfully created modules input message semaphore\n");
    ev_server->sem_queues = sem_queues;
  }
  
  rv = apr_thread_create(
			 &(ev_server->dispatcher_thread),
			 NULL,
			 (apr_thread_start_t) core_msg_dispatcher_worker,
			 (void *) ev_server,
			 pool);

  if (rv == APR_SUCCESS) // on success 
    printf("core: successfully created modules msg. consumer thread\n");

  printf("core: creating message consumer\n");

        
  apr_hash_t *subs_hash = apr_hash_make(pool);
  ev_server->pool = pool;
  ev_server->subscriptions = subs_hash;

  return ev_server;
 error:
  return 0;
}


static void * APR_THREAD_FUNC core_msg_dispatcher_worker(apr_thread_t *thd, core_event_server_t * ev_server) {
  
  apr_status_t rv;
  void *v = NULL;
  int i = 0;
  
  while (1) {
    //printf("core: entering thread\n");

    // pop from the sem_queue to simulate a semaphore
    rv = apr_queue_pop(ev_server->sem_queues->queue, &v);
    
    if (rv == APR_EINTR) { // the blocking was interrupted (try again)
      printf("core: the blocking was interrupted\n");
    }
    else if (rv == APR_EOF) { // if the queue has been terminated
      printf("core: the queue has been terminated\n");
      return NULL;
    }    
    else if (rv == APR_EAGAIN) { // the queue is empty
      printf("core: the queue is empty\n");
      continue;
    }    
    else if (rv != APR_SUCCESS) { // every thing but successful
      printf("core: the pop was unsuccessful\n");
      continue;
    }
    
    /* poping from semaphore was successful, */
    /* so that we can look for the actual message in */
    /* one of the queues */

    for(i = 0; i < NUM_PRIORITY_LEVELS; i++) {
      core_mqueue_t * mqueue = ev_server->queues[i];
      rv = apr_queue_trypop(mqueue->queue, &v);
      if (rv == APR_EINTR) { // the blocking was interrupted (try again)
	printf("core: the blocking was interrupted\n");
	continue;
      }      
      else if (rv == APR_EOF) { // if the queue has been terminated
	printf("core: fatal error... the queue has been terminated\n");
	return NULL;
      }    
      else if (rv == APR_EAGAIN) { // the queue is empty
	//printf("core: the queue is empty\n");
	continue;
      }
      else if (rv != APR_SUCCESS) { // every thing but successful
	printf("core: the pop was unsuccessful\n");
	continue;
      }

      core_event_t* event = (core_event_t *) v;
      /* int * data = (int *) (event->data); */
      //printf("got an event with priority %d: event name: %s \n", i, event->event_name);
      core_mqueue_t *queue = NULL;
      apr_hash_t *subs_hash;
      core_event_t* new_event = NULL;

      subs_hash = ev_server->subscriptions;

      // iterate over queue subscribed for this event (currently one person can subscribe)
      queue = (core_mqueue_t *) apr_hash_get(subs_hash,
					     (void *) event->event_name,
					     APR_HASH_KEY_STRING
					     );

      if(queue) {
	// copy event for each subscriber
	new_event = (void *) core_event_dup(event);
	rv = apr_queue_push(queue->queue, new_event);
	if (rv == APR_SUCCESS) { // on success
	  //printf("core: message successfully published\n");
	}
      }
	
      apr_pool_destroy(event->pool);

      
      break;
    }
    continue;
    
  }
  return NULL;
}



//###################################################################
//###################################################################
//###################################################################




void core_event_subscribe(core_event_server_t *event_server, const char *event_name, core_mqueue_t *queue) {

  //apr_status_t rv;
  void *value = (void *) queue;
  apr_pool_t *pool        = event_server->pool;
  const char *key = apr_pstrdup(pool, event_name);
  apr_hash_set(event_server->subscriptions, key, APR_HASH_KEY_STRING, value);
  /* printf("reached here\n"); */
}


void core_event_publish(core_event_server_t *event_server, core_event_t* event, int priority) {

  apr_status_t rv;
  core_event_t *new_event;
  char *sem_data;
  /* core_mqueue_t *queue; */
  /* apr_hash_t *subs_hash; */

  /* subs_hash = event_server->subscriptions; */

  /* queue = (core_mqueue_t *) apr_hash_get(subs_hash, */
  /* 					 (void *) event->event_name, */
  /* 					 APR_HASH_KEY_STRING */
  /* 					 ); */

  /* data = (void *) core_event_dup(event); */
  /* apr_pool_destroy(event->pool); */
  /* rv = apr_queue_push(queue->queue, data); */
  /* if (rv == APR_SUCCESS) { // on success  */
  /*   //printf("core: message successfully published\n"); */
  /* } */

  /* copy the event and destroy the given event */
  new_event = (core_event_t *) core_event_dup(event);
  sem_data = core_palloc(new_event->pool, sizeof (char));
  apr_pool_destroy(event->pool);

  /* check the priority and publish to the relevent queue */
  if(priority >= NUM_PRIORITY_LEVELS) {
    printf("core: wrong priority!");
    priority = NUM_PRIORITY_LEVELS - 1;
  }
  rv = apr_queue_push(event_server->queues[priority]->queue, new_event);
  rv = apr_queue_push(event_server->sem_queues->queue, sem_data);
  if (rv == APR_SUCCESS) { // on success
    //printf("core: event successfully published\n");
  }
}
  



core_event_t * core_event_create(const char *event_name, void* data, int data_len, int type) {
  apr_status_t rv;
  core_event_t *event;

  // Allocate and initialize events memory pool
  // create event memory pool
  apr_pool_t *pool;
  rv = core_pool_create(&pool, NULL);
  if(rv != APR_SUCCESS) {
  /* printf("Not successful\n"); */
  return NULL;
}
  else {
  /* printf("Successfully created events memory pool\n"); */
}

  event = core_palloc(pool, sizeof (core_event_t));
  event->pool = pool;
  event->event_name = apr_pstrdup(pool, event_name);
  event->data = apr_pmemdup(pool, data, data_len);
  event->data_len = data_len;
  event->type = type;

  return event;
}


  core_event_t * core_event_dup(core_event_t *event) {
  return core_event_create(event->event_name, event->data, event->data_len, event->type);
}


  void core_event_destroy(core_event_t *event) {
  apr_pool_destroy(event->pool);
}


