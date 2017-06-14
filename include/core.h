#ifndef CORE_H
#define CORE_H

#include <apu.h>
#include <apr_thread_pool.h>
#include <apr_time.h>
#include <apr_general.h>
#include <apr_dso.h>
#include <apr_thread_proc.h>
#include <apr_thread_cond.h>
#include <core_mqueue.h>

#define NUMBER_CONSUMERS    3
#define CONSUMER_ACTIVITY   4
#define NUMBER_PRODUCERS    40
#define PRODUCER_ACTIVITY   5
#define QUEUE_SIZE          100

#define core_palloc            apr_palloc
#define core_pool_create       apr_pool_create

struct  core_module;
typedef struct core_module core_module_t;

// Module API Interface
typedef void (*MODULE_LOAD) (core_module_t *);
typedef void (*MODULE_DESTROY) (core_module_t *);

typedef void* core_context_t;

// Module Handle
struct core_module {

  /* modules main memory pool */
  apr_pool_t *pool;

  /* modules input message queue */
  core_mqueue_t *mqueue;
  
  /* shared context depends on module */
  core_context_t *context;

  /* modules api interface */
  MODULE_LOAD load_func;
  MODULE_DESTROY destroy_func;

};


core_module_t * core_load_module(apr_dso_handle_t *, apr_pool_t *, const char *, const char *);
void core_destroy_module(core_module_t *);


#endif
