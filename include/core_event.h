#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include <core_apr.h>

struct  core_event_server;
typedef struct core_event_server core_event_server_t;

struct  core_event;
typedef struct core_event core_event_t;

// Event Server Handle
struct core_event_server {
  /* event servers memory pool */
  apr_pool_t *pool;

  /* hashtable with the event as key and its subscriber list as value */
  apr_hash_t *subscriptions;
};

// Event Message
struct core_event {
  apr_pool_t *pool;
  char* event_name;
  void * data;
  int data_len;
  int type;
};

core_event_t * core_event_create(const char *event_name, void* data, int data_len, int type);
core_event_t * core_event_dup(core_event_t *event);
void core_event_destroy(core_event_t *event);
core_event_server_t * core_event_server_create();

void core_event_subscribe(core_event_server_t *event_server, const char *event_name, core_mqueue_t *queue);
void core_event_publish(core_event_server_t *event_server, core_event_t* event);
#endif
