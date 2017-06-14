#include <apu.h>
#include <apr_thread_pool.h>
#include <apr_time.h>
#include <apr_general.h>
#include <apr_dso.h>
#include <apr_hash.h>
#include <apr_strings.h>
#include <apr_thread_proc.h>
#include <apr_thread_cond.h>

#define core_palloc            apr_palloc
#define core_pool_create       apr_pool_create

