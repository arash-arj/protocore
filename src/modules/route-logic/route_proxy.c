#include <mod_route_logic.h>


/* create new transaction object based on uuid from modules */
route_proxy_t * route_proxy_create(const char * uas_uuid_str, route_logic_context_t * mod_context) {
  core_status_t rv;
  core_pool_t * proxy_pool = NULL;
  core_rwlock_t * proxy_rwlock = NULL;
  route_proxy_t * proxy = NULL;
  char uas_trans_id[128];
  core_uuid_t uuid;
  
  /* create transactions memory pool */
  rv = core_pool_create(&(proxy_pool));
  if(rv != CORE_SUCCESS) {
    printf("route_proxy.c: creating proxy memory pool was not successful\n");
    return NULL;
  }

  proxy = core_palloc(proxy_pool, sizeof(route_proxy_t));
  proxy->pool = proxy_pool;

  rv = core_rwlock_create(proxy_pool, &(proxy_rwlock));
  if(rv != CORE_SUCCESS) {
    printf("core_trans.c: creating transaction was not successful\n");
    return NULL;
  }
  
  proxy->rwlock = proxy_rwlock;

  memset(uas_trans_id, '\0', sizeof(uas_trans_id));
  if (!uas_uuid_str || *uas_uuid_str == '\0') { /* empty string */
    core_uuid_get(&uuid);
    core_uuid_format(uas_trans_id, &uuid);
  }
  else {
    strcpy(uas_trans_id, uas_uuid_str);
  }

  proxy->uas_uuid = core_pstrdup(proxy_pool, uas_trans_id);

  
  core_mutex_lock(mod_context->trans_proxy_table_lock);
  core_hash_set(mod_context->trans_proxy_table, proxy->uas_uuid, CORE_HASH_KEY_STRING, (void *)proxy);
  core_mutex_unlock(mod_context->trans_proxy_table_lock);

  
  if(proxy && proxy->rwlock) {
    core_rwlock_rdlock(proxy->rwlock);
  }
  

  return proxy;
}


void route_proxy_destroy(route_proxy_t * proxy, route_logic_context_t * mod_context) {
  core_status_t rv;

  if(proxy && proxy->uas_uuid) {
  
    /* remove from transaction managers table */
    core_hash_set(mod_context->trans_proxy_table, proxy->uas_uuid, CORE_HASH_KEY_STRING, (void *)proxy);
    
    core_mutex_lock(mod_context->trans_proxy_table_lock);
    core_hash_set(mod_context->trans_proxy_table, proxy->uas_uuid, CORE_HASH_KEY_STRING, NULL);
    core_mutex_unlock(mod_context->trans_proxy_table_lock);

    /* wait for transaction readers */
    core_rwlock_wrlock(proxy->rwlock);
    core_rwlock_unlock(proxy->rwlock);
  
    /* destroy transactions memory pool */
    core_pool_destroy(&(proxy->pool));
    proxy = NULL;
  } 
}


route_proxy_t * route_proxy_get(const char * uas_uuid, route_logic_context_t * mod_context) {
  core_status_t rv;
  route_proxy_t * proxy = NULL;

  /* remove from transaction managers table */
  core_mutex_lock(mod_context->trans_proxy_table_lock);
  proxy = (route_proxy_t *) core_hash_get(mod_context->trans_proxy_table, uas_uuid, CORE_HASH_KEY_STRING);
  core_mutex_unlock(mod_context->trans_proxy_table_lock);

  if(proxy && proxy->rwlock) {
    core_rwlock_rdlock(proxy->rwlock);
  }
  return proxy;
}


void route_proxy_rwunlock(route_proxy_t * proxy) {
  if(proxy && proxy->rwlock) {
    core_rwlock_unlock(proxy->rwlock);
  }
}


void * route_proxy_alloc(route_proxy_t * proxy, core_size_t mem_size) {
  void *ptr = NULL;
  core_assert(proxy != NULL);
  core_assert(proxy->pool != NULL);


  ptr = core_palloc(proxy->pool, mem_size);
  core_assert(ptr != NULL);

  memset(ptr, 0, mem_size);

  return ptr;
}


const char * route_proxy_uas_uuid(route_proxy_t * proxy) {
  core_assert(proxy != NULL);
  return proxy->uas_uuid;
}
