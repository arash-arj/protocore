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
					     (void *) event->name,
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
	
      core_event_destroy(event);

      
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
  sem_data = (char *) new_event->name;
  core_event_destroy(event);

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
  

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

core_event_t * core_event_create(const char *event_name, int event_type, char* event_body) {
  core_event_t *event = NULL;

  event = (core_event_t *) malloc(sizeof(core_event_t));
  
  if(!event) {
    return NULL;
  }

  
  if(event_name) {
    event->name = strdup(event_name);
  }

  if(event_body) {
    event->body = strdup(event_body);
  }

  event->type = event_type;
  event->first_header = NULL;
  event->last_header = NULL;
  
  return event;
}


core_event_t * core_event_dup(core_event_t *event) {
  core_event_t *new_event = core_event_create(event->name, event->type, event->body);
  core_event_header_t *fh = NULL;
  core_event_header_t *lh = NULL;
  
  core_event_header_list_dup(event->first_header, &fh, &lh);
  new_event->first_header = fh;
  new_event->last_header = lh;
  return new_event;
}


void core_event_destroy(core_event_t *event) {

  core_event_header_list_destroy(event->first_header);
  event->first_header = NULL;
  event->last_header = NULL;

  if(event->name) {
    free(event->name);
    event->name = 0;
  }

  if(event->body) {
    free(event->body);
    event->body = 0;
  }

  free(event);

}


core_event_header_t * core_event_header_create(const char *header_name, const char *header_value) {
  core_event_header_t *header = NULL;

  header = (core_event_header_t *) malloc(sizeof(core_event_header_t));
  if(!header) {
    return NULL;
  }

  if(header_name) {
    header->name = strdup(header_name);
  }
  if(header_value) {
    header->value = strdup(header_value);
  }
  header->next = NULL;
  return header;
}


core_event_header_t * core_event_header_add(core_event_t *event, const char *header_name, const char *header_value) {
  core_event_header_t *header = NULL;

  if(!event || !header_name || !header_value) {
    return NULL;
  }

  header = core_event_header_create(header_name, header_value);

  if(!header) {
    return NULL;
  }

  /* no first header */
  if(!(event->first_header)) { 
    event->first_header = header;
    event->last_header = header;
    return header;
  }

  if(!(event->last_header)) {
    /* this is a fault! possible memory leak */
  }

  if(event->last_header && event->last_header->next) {
    /* this is a fault! possible memory leak */
  }
  
  /* we should assert that here, event->last_header && !(event->last_header->next) */

  event->last_header->next = header;
  event->last_header = header;

  return header;
}


core_event_header_t * core_event_header_dup(core_event_header_t *header) {
  core_event_header_t *new_header = NULL;
  new_header = core_event_header_create(header->name, header->value);
  return new_header;
}


core_event_header_t* core_event_header_destroy(core_event_header_t *header) {
  core_event_header_t *next = header->next;
  free(header->name);
  free(header->value);
  free(header);
  return next;
}


void core_event_header_list_dup(core_event_header_t *header, core_event_header_t **first_header, core_event_header_t **last_header) {
  core_event_header_t *head = NULL;
  core_event_header_t *new = NULL;
  core_event_header_t *prev = NULL;

  /* iterate over given header list */
  for(head = header; head; head = head->next) {
    new = core_event_header_dup(head);
    if(prev) {
      prev->next = new;
    }
    prev = new;
    if(!(*first_header)) {
        *first_header = new;
    }
  }
  *last_header = prev;
}


void core_event_header_list_destroy(core_event_header_t *header) {
  core_event_header_t *next = NULL;
  for(next = header;
      next != NULL;
      next = core_event_header_destroy(next)
      );
}
