#ifndef CORE_MQUEUE_H
#define CORE_MQUEUE_H


#include <apr_queue.h>

#define core_queue_create apr_queue_create

typedef struct {
  /* modules input message queue */
  apr_queue_t *queue;
} core_mqueue_t;

#endif
