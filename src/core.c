#include "core.h"
#include <protected/core_protect.h>

struct core_instance_handle core_instance;
struct core_transaction_manager_handle core_trans_manager;

/* initialize the whole beast */
void core_init() {
  core_status_t rv;
  core_mutex_t * trans_table_mutex = NULL;
  core_mutex_t * uuid_mutex = NULL;
  
  /* initialize APR */
  core_apr_initialize();

  /* create main memory pool */
  rv = core_pool_create(&(core_instance.pool));
  if(rv != CORE_SUCCESS) {
    printf("core: could not create core memory pool\n");
    return;
  }

  /* create event server */
  core_instance.event_server = core_event_server_create(core_instance.pool);

  /* create trans table */
  core_trans_manager.trans_table = core_hash_make(core_instance.pool);
  printf("core: created trans table (%p)\n", core_trans_manager.trans_table);

  /* create trans table lock */
  rv = core_mutex_create(core_instance.pool, &(trans_table_mutex), CORE_MUTEX_NESTED);
  if(rv != CORE_SUCCESS) {
    printf("core: could not create lock for transaction table\n");
    return;
  }
  
  core_trans_manager.trans_table_lock = trans_table_mutex;


  /* create uuid generator lock */
  rv = core_mutex_create(core_instance.pool, &(uuid_mutex), CORE_MUTEX_NESTED);
  if(rv != CORE_SUCCESS) {
    printf("core: could not create lock for uuid generator\n");
    return;
  }
  
  core_instance.uuid_lock = uuid_mutex;

}

/* terminator */
void core_terminate() {

  /* shutdown the event-loop */
  core_event_server_destroy(core_instance.event_server);

  /* destroy the memory pool */
  core_pool_destroy(&(core_instance.pool));

  /* terminate the holy APR */
  core_apr_terminate();
  
}

