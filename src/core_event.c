#include <core.h>
#include <protected/core_protect.h>


// Create our message dispatcher
core_event_server_t *core_event_server_create(core_pool_t *pool) {
  int i;
  core_status_t rv;
  core_event_server_t *ev_server;
  
  /* allocate the event server object */
  ev_server = core_palloc(pool, sizeof (core_event_server_t));
  ev_server->flag_shutdown = 0;
  
  for(i = 0; i < NUM_PRIORITY_LEVELS; i++) {
    core_queue_t * ev_queue = NULL;
    ev_queue = core_palloc(pool, sizeof(core_queue_t *));
    rv = core_queue_create(&ev_queue, QUEUE_SIZE, pool);
    if (rv == CORE_SUCCESS) { // on a successful pop
      printf("core: successfully created modules input message queue\n");
      ev_server->queues[i] = ev_queue;
    }
  }

  core_queue_t * sem_queues = NULL;
  sem_queues = core_palloc(pool, sizeof(core_queue_t *));
  rv = core_queue_create(&(sem_queues), QUEUE_SIZE * NUM_PRIORITY_LEVELS, pool);
  if (rv == CORE_SUCCESS) { // on a successful pop
    printf("core: successfully created modules input message semaphore\n");
    ev_server->sem_queues = sem_queues;
  }
  
  rv = core_thread_create(&(ev_server->dispatcher_thread), NULL,
			 (core_thread_start_t) core_msg_dispatcher_worker,
			 (void *) ev_server, pool);

  if (rv == CORE_SUCCESS) // on success 
    printf("core: successfully created modules msg. consumer thread\n");

  printf("core: creating message consumer\n");

        
  core_hash_t *subs_hash = core_hash_make(pool);
  ev_server->pool = pool;
  ev_server->subscriptions = subs_hash;

  return ev_server;
 error:
  return 0;
}



void core_event_server_destroy( core_event_server_t *ev_server) {
  int i;
  core_status_t rv;
  ev_server->flag_shutdown = 1;
  core_queue_interrupt_all(ev_server->sem_queues);
  /* rv = core_queue_term(ev_server->sem_queues); */
  /* if (rv == CORE_SUCCESS) // on success */
  /*   printf("core: terminated the semaphore\n"); */

  rv = core_thread_join(&rv, ev_server->dispatcher_thread);
  if (rv == CORE_SUCCESS) // on success
    printf("core: successfully destroyed the message dispatcher thread\n");

  
  for(i = 0; i < NUM_PRIORITY_LEVELS; i++) {
    core_queue_t * ev_queue = ev_server->queues[i];
    rv = core_queue_term(ev_queue);
    if (rv == CORE_SUCCESS) { // on success
      printf("core: terminated the queue.%d\n", i);
      ev_queue = NULL;
    }
  }


}



static void * core_msg_dispatcher_worker(core_thread_t *thd, core_event_server_t * ev_server) {
  
  core_status_t rv;
  void *v = NULL;
  int i = 0;
  
  while (1) {
    if(ev_server && ev_server->sem_queues) {

      if((core_queue_size(ev_server->sem_queues) == 0) && (ev_server->flag_shutdown == 1)) {
	
	rv = core_queue_term(ev_server->sem_queues);
	if (rv == CORE_SUCCESS) { // on success
	  printf("mod_diam_psm: queue terminated\n");
	  ev_server->sem_queues = NULL;
	}
	
	printf("mod_diam_psm: exiting msg consumer thread\n");
	core_thread_exit(thd, CORE_SUCCESS);      
      }
      
      rv = core_queue_pop(ev_server->sem_queues, &v);
    }
    else {
      printf("mod_diam_psm: exiting msg consumer thread\n");
      core_thread_exit(thd, CORE_SUCCESS);      
    }

    if(rv == CORE_INTR) {
      printf("the semaphore has been interrupted\n");
      continue;
    }
    

    /* // pop from the sem_queue to simulate a semaphore */
    /* if((rv = core_queue_pop(ev_server->sem_queues, &v)) != CORE_SUCCESS) { */
    /*   char buf[256]; */
    /*   core_strerror(rv, buf, sizeof(buf)); */
    /*   puts(buf);  /\* show the error description *\/ */
    /* } */
    
    
    /* if (rv == CORE_INTR) { // the blocking was interrupted (try again) */
    /*   printf("core: the blocking was interrupted\n"); */
    /* } */
    /* else if (rv == CORE_TERM) { // if the queue has been terminated */
    /*   printf("core: the queue has been terminated\n"); */
    /*   break; */
    /* }     */
    /* else if (rv == CORE_NOTFOUND) { // end of file */
    /*   printf("core: end of file\n"); */
    /*   break; */
    /* }     */
    /* else if (rv != CORE_SUCCESS) { // every thing but successful */
    /*   printf("core: poping from semaphore was unsuccessful\n"); */
    /*   continue; */
    /* } */

    /* printf("poping from semaphore was successful\n"); */

    /* poping from semaphore was successful, */
    /* so that we can look for the actual message in */
    /* one of the queues */
    for(i = 0; i < NUM_PRIORITY_LEVELS; i++) {
      core_queue_t * ev_queue = ev_server->queues[i];
      rv = core_queue_trypop(ev_queue, &v);
      if (rv == CORE_INTR) { // the blocking was interrupted (try again)
	printf("core: the blocking was interrupted\n");
	continue;
      }      
      else if (rv == CORE_TERM) { // if the queue has been terminated
	printf("core: fatal error... the queue has been terminated\n");
	return NULL;
      }    
      else if (rv != CORE_SUCCESS) { // every thing but successful
	printf("core: the pop was unsuccessful\n");
	continue;
      }

      core_event_t* event = (core_event_t *) v;
      /* int * data = (int *) (event->data); */
      /* printf("got an event with priority %d: event name: %s \n", i, event->name); */
      core_queue_t *mod_queue = NULL;
      core_hash_t *subs_hash;
      core_event_t* new_event = NULL;

      subs_hash = ev_server->subscriptions;

      // iterate over queue subscribed for this event (currently one person can subscribe)
      mod_queue = (core_queue_t *) core_hash_get(subs_hash,
					     (void *) event->name,
					     CORE_HASH_KEY_STRING
					     );

      if(mod_queue) {
	// copy event for each subscriber
	new_event = (void *) core_event_dup(event);
	rv = core_queue_push(mod_queue, new_event);
	if (rv == CORE_SUCCESS) { // on success
	  printf("core: message successfully published\n");
	}
      }
      else {
	printf("no one has subscribed for this event!\n");
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




void core_event_server_subscribe(core_event_server_t *event_server, const char *event_name, core_queue_t *queue) {

  //apr_status_t rv;
  void *value = (void *) queue;
  core_pool_t *pool        = event_server->pool;
  const char *key = core_pstrdup(pool, event_name);
  core_hash_set(event_server->subscriptions, key, CORE_HASH_KEY_STRING, value);
  /* printf("reached here\n"); */
}


void core_event_server_publish(core_event_server_t *event_server, core_event_t* event, int priority) {

  core_status_t rv;
  core_event_t *new_event;
  char *sem_data;

  /* copy the event and destroy the given event */
  new_event = (core_event_t *) core_event_dup(event);
  sem_data = (char *) new_event->name;
  core_event_destroy(event);

  /* check the priority and publish to the relevent queue */
  if(priority >= NUM_PRIORITY_LEVELS) {
    priority = NUM_PRIORITY_LEVELS - 1;
  }
  rv = core_queue_push(event_server->queues[priority], new_event);
  rv = core_queue_push(event_server->sem_queues, sem_data);
  if (rv == CORE_SUCCESS) { // on success
    /* printf("core: event successfully published with priority: %d\n", priority); */
  }
}
  



void core_event_subscribe(const char *event_name, core_queue_t *queue) {
  /* core_event_server_t *event_server; */
  core_event_server_subscribe(core_instance.event_server, event_name, queue);
}


void core_event_publish(core_event_t* event, int priority) {
  /* core_event_server_t *event_server; */
  core_event_server_publish(core_instance.event_server, event, priority);
}
  

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

core_event_t * core_event_create(const char *event_name, int event_type, char* event_body) {
  core_event_t *event = NULL;

  if(!event_name) {
    return NULL;
  }

  event = (core_event_t *) malloc(sizeof(core_event_t));
  
  if(!event) {
    return NULL;
  }

  event->name = strdup(event_name);

  event->body = NULL;
  if(event_body) {
    event->body = strdup(event_body);
  }

  event->type = event_type;
  event->first_header = NULL;
  event->last_header = NULL;
  
  return event;
}


core_event_t * core_event_dup(core_event_t *event) {
  core_event_t *new_event = NULL;
  core_event_header_t *fh = NULL;
  core_event_header_t *lh = NULL;
  
  new_event = core_event_create(event->name, event->type, NULL);
  
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


char * core_event_header_get(core_event_t *event, char *name) {
  core_event_header_t *next = NULL;

  if(!event && !name) {
    return NULL;
  }

  for(next = event->first_header; next != NULL; next = next->next) {
    if(next && next->name && (!strcmp(next->name, name)) ) {
      return next->value;
    }
  }
  return NULL;
}
