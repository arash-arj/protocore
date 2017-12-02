#ifndef MOD_ROUTE_LOGIC_H
#define MOD_ROUTE_LOGIC_H

#include <core.h>

struct route_proxy {

  /* proxy's memory pool */
  core_pool_t *pool;

  /* life-cycle of the proxy is 
     the same as uas transaction */
  const char * uas_uuid;

  /* for invite client transactions, 
     we need to remeber uac uuid for 
     possible cancel or ack methods */
  const char * uac_uuid;

  /* rwlock for the proxy */
  core_rwlock_t * rwlock;

};
typedef struct route_proxy route_proxy_t;


struct route_logic_context {

  /* a thread to dequeue from 
     modules input fifo */
  core_thread_t *consumer_thread;

  /* hash-table to keep the relation
     between transaction id and 
     the proxy object, which keeps
     the proxy state */
  core_hash_t *trans_proxy_table;

  /* mutex to keep table thread-safe */
  core_mutex_t *trans_proxy_table_lock;  

  /* a flag to indicate module
     shutdown request */
  int module_shutdown;
  
};
typedef struct route_logic_context route_logic_context_t;


/* module functions */
void mod_route_logic_load(core_module_t *module);

void route_logic_handle_core_event(core_event_t *, route_logic_context_t *);

static void * route_logic_core_msg_consumer(core_thread_t *, core_module_t *);


/* proxy object manipullation functions */
route_proxy_t * route_proxy_create(const char * uas_uuid_str, route_logic_context_t * mod_context);

void route_proxy_destroy(route_proxy_t * proxy, route_logic_context_t * mod_context);

route_proxy_t * route_proxy_get(const char * uas_uuid, route_logic_context_t * mod_context);

void route_proxy_rwunlock(route_proxy_t * proxy);

void * route_proxy_alloc(route_proxy_t * proxy, core_size_t mem_size);

const char * route_proxy_uas_uuid(route_proxy_t * proxy);


#endif
