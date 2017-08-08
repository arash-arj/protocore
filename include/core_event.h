#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include <core_apr.h>

#define NUM_PRIORITY_LEVELS 10

struct  core_event_server;
typedef struct core_event_server core_event_server_t;

struct  core_event;
typedef struct core_event core_event_t;

struct  core_event_header;
typedef struct core_event_header core_event_header_t;

// Event Server Handle
struct core_event_server {
  /* event servers memory pool */
  apr_pool_t *pool;

  /* hashtable with the event as key and its subscriber list as value */
  apr_hash_t *subscriptions;

  /* an array to store the multi-level message queues */
  core_mqueue_t* queues[NUM_PRIORITY_LEVELS];

  /* a semaphore to indicate incoming messages to one of the queues */
  core_mqueue_t* sem_queues;

  /* worker thread which dispatches the messages to modules */
  apr_thread_t *dispatcher_thread;

};

// Event Message Header
struct core_event_header {

  /* name of the header field */
  char* name;

  /* value of the header */
  char* value;

  /* pointer to the next header */
  core_event_header_t* next;
};

// Event Message
struct core_event {

  /* event message's name */
  char* name;

  /* event message's type */
  int type;

  /* pointer to the first header */
  core_event_header_t * first_header;

  /* pointer to the last header */
  core_event_header_t * last_header;
  
  /* body of the event message */
  char * body;
};

core_event_t * core_event_create(const char *event_name, int event_type, char* event_body);
core_event_t * core_event_dup(core_event_t *event);
void core_event_destroy(core_event_t *event);

core_event_header_t * core_event_add_header(core_event_t *event, const char *header_name, const char *header_value);
core_event_header_t * core_event_header_create(const char *header_name, const char *header_value);
core_event_header_t * core_event_header_dup(core_event_header_t *header);
core_event_header_t * core_event_header_destroy(core_event_header_t *header);
void core_event_header_list_destroy(core_event_header_t *header);


core_event_server_t * core_event_server_create();

void core_event_subscribe(core_event_server_t *event_server, const char *event_name, core_mqueue_t *queue);
void core_event_publish(core_event_server_t *event_server, core_event_t* event, int priority);
#endif
