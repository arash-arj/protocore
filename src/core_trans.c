#include <core.h>
#include <protected/core_protect.h>


/* create new transaction object based on uuid from modules */
core_trans_t * core_trans_create(const char * uuid_str, core_trans_direction_t direction) {
  core_status_t rv;
  core_pool_t * trans_pool = NULL;
  core_rwlock_t * trans_rwlock = NULL;
  core_trans_t * trans = NULL;
  char trans_id[128];
  core_uuid_t uuid;
  
  /* create transactions memory pool */
  rv = core_pool_create(&(trans_pool));
  if(rv != CORE_SUCCESS) {
    printf("core_trans.c: creating transaction memory pool was not successful\n");
    return NULL;
  }

  trans = core_palloc(trans_pool, sizeof(core_trans_t));
  trans->pool = trans_pool;

  rv = core_rwlock_create(trans_pool, &(trans_rwlock));
  if(rv != CORE_SUCCESS) {
    printf("core_trans.c: creating transaction was not successful\n");
    return NULL;
  }
  
  trans->rwlock = trans_rwlock;

  memset(trans_id, '\0', sizeof(trans_id));
  if (!uuid_str || *uuid_str == '\0') { /* empty string */
    core_uuid_get(&uuid);
    core_uuid_format(trans_id, &uuid);
  }
  else {
    strcpy(trans_id, uuid_str);
  }

  trans->uuid = core_pstrdup(trans_pool, trans_id);

  trans->direction = direction;
  
  core_mutex_lock(core_trans_manager.trans_table_lock);
  core_hash_set(core_trans_manager.trans_table, trans->uuid, CORE_HASH_KEY_STRING, (void *)trans);
  core_mutex_unlock(core_trans_manager.trans_table_lock);

  
  if(trans && trans->rwlock) {
    core_rwlock_rdlock(trans->rwlock);
  }
  

  return trans;
}


void core_trans_destroy(core_trans_t * trans) {
  core_status_t rv;

  if(trans && trans->uuid) {
  
    /* remove from transaction managers table */
    core_mutex_lock(core_trans_manager.trans_table_lock);
    core_hash_set(core_trans_manager.trans_table, trans->uuid, CORE_HASH_KEY_STRING, NULL);
    core_mutex_unlock(core_trans_manager.trans_table_lock);

    /* wait for transaction readers */
    core_rwlock_wrlock(trans->rwlock);
    core_rwlock_unlock(trans->rwlock);
  
    /* destroy transactions memory pool */
    core_pool_destroy(&(trans->pool));
    trans = NULL;
  } 
}


core_trans_t * core_trans_get(const char * uuid) {
  core_status_t rv;
  core_trans_t * trans = NULL;

  /* remove from transaction managers table */
  core_mutex_lock(core_trans_manager.trans_table_lock);
  trans = (core_trans_t *) core_hash_get(core_trans_manager.trans_table, uuid, CORE_HASH_KEY_STRING);
  core_mutex_unlock(core_trans_manager.trans_table_lock);

  if(trans && trans->rwlock) {
    core_rwlock_rdlock(trans->rwlock);
  }
  return trans;
}


void core_trans_rwunlock(core_trans_t * trans) {
  if(trans && trans->rwlock) {
    core_rwlock_unlock(trans->rwlock);
  }
}


void * core_trans_alloc(core_trans_t * trans, core_size_t mem_size) {
  void *ptr = NULL;
  core_assert(trans != NULL);
  core_assert(trans->pool != NULL);


  ptr = core_palloc(trans->pool, mem_size);
  core_assert(ptr != NULL);

  memset(ptr, 0, mem_size);

  return ptr;
}


void core_trans_set_context(core_trans_t * trans, core_trans_context_t * context) {
  core_assert(trans != NULL);
  trans->context = context;
}

core_trans_context_t * core_trans_get_context(core_trans_t * trans) {
  core_assert(trans != NULL);
  return trans->context;
}


const char * core_trans_uuid(core_trans_t * trans) {
  core_assert(trans != NULL);
  return trans->uuid;
}

char* core_trans_pstrdup(core_trans_t * trans, const char *s) {
  core_assert(trans != NULL);
  return core_pstrdup(trans->pool, s);
}
