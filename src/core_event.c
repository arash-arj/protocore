#include <core.h>
#include <core_event.h>
#include <core_mqueue.h>
#include <core_apr.h>


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


core_event_server_t *core_event_server_create() {

  apr_status_t rv;
  core_event_server_t *ev_server;
  
  // Allocate and initialize event servers memory pool
  // create event servers memory pool
  apr_pool_t *pool;
  rv = apr_pool_create(&pool, NULL);
  if(rv != APR_SUCCESS) {
    /* printf("Not successful\n"); */
    return 0;
  }
  else {
    /* printf("Successfully created event servers memory pool\n"); */
  }


  ev_server = core_palloc(pool, sizeof (core_event_server_t));
  apr_hash_t *subs_hash = apr_hash_make(pool);
  ev_server->pool = pool;
  ev_server->subscriptions = subs_hash;

  return ev_server;
}


void core_event_subscribe(core_event_server_t *event_server, const char *event_name, core_mqueue_t *queue) {

  //apr_status_t rv;
  void *value = (void *) queue;
  apr_pool_t *pool        = event_server->pool;
  const char *key = apr_pstrdup(pool, event_name);
  apr_hash_set(event_server->subscriptions, key, APR_HASH_KEY_STRING, value);
  /* printf("reached here\n"); */
}


void core_event_publish(core_event_server_t *event_server, core_event_t* event) {

  apr_status_t rv;
  void *data;
  core_mqueue_t *queue;
  apr_hash_t *subs_hash;

  subs_hash = event_server->subscriptions;

  queue = (core_mqueue_t *) apr_hash_get(subs_hash,
					 (void *) event->event_name,
					 APR_HASH_KEY_STRING
					 );

  data = (void *) core_event_dup(event);
  apr_pool_destroy(event->pool);
  rv = apr_queue_push(queue->queue, data);
}
