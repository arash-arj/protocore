#ifndef MOD_CLI_H
#define MOD_CLI_H

#include <core.h>


void mod_cli_load(core_module_t *module);
static void * APR_THREAD_FUNC cli_core_msg_consumer(apr_thread_t *, core_module_t *);
  

typedef struct {

  apr_thread_t *consumer_thread;
 
} cli_context_t;


#endif
