#ifndef MOD_DIAM_PSM_H
#define MOD_DIAM_PSM_H

#include "fdproto-internal.h"
#include "fdcore-internal.h"

#include <core.h>






void mod_diam_psm_load(core_module_t *module);
void diam_psm_handle_core_event(core_event_t * event);
static void * diam_psm_core_msg_consumer(core_thread_t *, core_module_t *);
void diam_psm_fd_init();
void diam_psm_fd_fini();

typedef struct {

  core_thread_t *consumer_thread;

  int module_shutdown;
  
} diam_psm_context_t;


void my_main();

#endif
