#ifndef MOD_RADIUS_H
#define MOD_RADIUS_H

#include <core.h>


void mod_radius_load(core_module_t *module);
static void * APR_THREAD_FUNC radius_core_msg_consumer(apr_thread_t *, core_module_t *);
  

typedef struct {

  apr_thread_t *consumer_thread;
 
} radius_context_t;

#endif
