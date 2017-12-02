#include <core.h>
#include <protected/core_protect.h>

#include <apu.h>
#include <apr_thread_pool.h>
#include <apr_thread_rwlock.h>
#include <apr_time.h>
#include <apr_general.h>
#include <apr_dso.h>
#include <apr_hash.h>
#include <apr_strings.h>
#include <apr_thread_proc.h>
#include <apr_thread_cond.h>
#include <apr_queue.h>
#include <apr_md5.h>
#include <apr_base64.h>
#include <apr_uuid.h>


core_status_t core_apr_initialize() {
  return (core_status_t) apr_initialize();
}

void core_apr_terminate() {
  apr_terminate();
}

core_status_t core_queue_create(core_queue_t ** queue, unsigned int queue_capacity, core_pool_t *pool) {
  return apr_queue_create(queue, queue_capacity, pool);
}

unsigned int core_queue_size(core_queue_t *queue) {
  return apr_queue_size(queue);
}

core_status_t core_queue_pop(core_queue_t *queue, void **data) {
  return apr_queue_pop(queue, data);
}

/* core_status_t core_queue_pop_timeout(core_queue_t *queue, void **data, core_interval_time_t timeout) */
/* { */
/*   return apr_queue_pop_timeout(queue, data, timeout); */
/* } */

core_status_t core_queue_push(core_queue_t *queue, void *data) {
  apr_status_t s;

  do {
    s = apr_queue_push(queue, data);
  } while (s == APR_EINTR);

  return s;
}

core_status_t core_queue_trypop(core_queue_t *queue, void **data) {
  return apr_queue_trypop(queue, data);
}

core_status_t core_queue_interrupt_all(core_queue_t *queue) {
  return apr_queue_interrupt_all(queue);
}

core_status_t core_queue_term(core_queue_t *queue) {
  return apr_queue_term(queue);
}

core_status_t core_queue_trypush(core_queue_t *queue, void *data) {
  apr_status_t s;

  do {
    s = apr_queue_trypush(queue, data);
  } while (s == APR_EINTR);

  return s;
}


void * core_hash_get(core_hash_t *ht, const void *key, core_size_t klen) {
  return apr_hash_get(ht, key, klen);
}

void core_hash_set(core_hash_t *ht, const void *key, core_size_t klen, const void *val) {
  apr_hash_set(ht, key, klen, val);
}

core_hash_t * core_hash_make(core_pool_t *pool) {
  return apr_hash_make(pool);
}



void * core_palloc(core_pool_t *pool, core_size_t memory) {
  void *ptr = NULL;

  core_assert(pool != NULL);

  ptr = apr_palloc(pool, memory);
  core_assert(ptr != NULL);
  memset(ptr, 0, memory);

  return ptr;
}


void * core_pool_destroy(core_pool_t **pool) {

  core_assert(pool != NULL);
  apr_pool_destroy(*pool);
  *pool = NULL;
  
  return CORE_SUCCESS;
}


core_status_t core_pool_create(core_pool_t **pool) {

  apr_pool_create(pool, NULL);
  core_assert(*pool != NULL);
  core_assert(pool != NULL);

  return CORE_SUCCESS;
  
}

core_status_t core_thread_join(core_status_t * retval, core_thread_t * thd) {
  return apr_thread_join((apr_status_t *)retval, thd);
}

core_status_t core_thread_exit(core_thread_t * thd, core_status_t retval) {
  return apr_thread_exit(thd, retval);
}

core_status_t core_thread_create(core_thread_t **  new_thread, core_threadattr_t *  attr, core_thread_start_t  func, void *  data, core_pool_t *  cont) {
  return apr_thread_create(new_thread, attr, func, data, cont);
}


core_status_t core_dso_load(core_dso_handle_t **res_handle, const char *path, core_pool_t *ctx) {
  return apr_dso_load(res_handle, path, ctx);
}

core_status_t core_dso_unload(core_dso_handle_t *handle) {
  return apr_dso_unload(handle);
}

core_status_t core_dso_sym(core_dso_handle_sym_t *ressym, core_dso_handle_t *handle, const char *symname) {
  return apr_dso_sym((apr_dso_handle_sym_t *)ressym, handle, symname);
}

const char * core_dso_error(core_dso_handle_t *dso, char *buf, core_size_t bufsize) {
  return apr_dso_error(dso, buf, bufsize);
}


char* core_strerror(core_status_t  statcode, char * buf, core_size_t bufsize) {
  return apr_strerror((apr_status_t) statcode, buf, bufsize);
}

char* core_pstrdup(core_pool_t * p, const char *s) {
  return apr_pstrdup(p, s);
}

void core_sleep(core_interval_time_t t) {
  apr_sleep(t);
}


char * core_strdup(core_pool_t *pool, const char *todup)
{
  char *duped = NULL;
  core_size_t len;
  core_assert(pool != NULL);

  if (!todup || *todup == '\0') { /* empty string */
    return "";
  }

  len = strlen(todup) + 1;

  duped = apr_pstrmemdup(pool, todup, len);
  core_assert(duped != NULL);

  return duped;
}

char * core_sprintf(core_pool_t *pool, const char *fmt, ...)
{
  va_list ap;
  char *result;
  va_start(ap, fmt);
  result = core_vsprintf(pool, fmt, ap);
  va_end(ap);

  return result;
}

char * core_vsprintf(core_pool_t *pool, const char *fmt, va_list ap)
{
  char *result = NULL;

  core_assert(pool != NULL);


  result = apr_pvsprintf(pool, fmt, ap);
  core_assert(result != NULL);


  return result;
}

core_status_t core_rwlock_create (core_pool_t *pool, core_rwlock_t **rwlock) {
  return apr_thread_rwlock_create(rwlock, pool);
}

core_status_t core_rwlock_rdlock (core_rwlock_t *rwlock) {
  return apr_thread_rwlock_rdlock(rwlock);
}

core_status_t core_rwlock_tryrdlock (core_rwlock_t *rwlock) {
  return apr_thread_rwlock_tryrdlock(rwlock);
}

core_status_t core_rwlock_wrlock (core_rwlock_t *rwlock) {
  return apr_thread_rwlock_wrlock(rwlock);
}

core_status_t core_rwlock_trywrlock (core_rwlock_t *rwlock) {
  return apr_thread_rwlock_trywrlock(rwlock);
}

core_status_t core_rwlock_unlock (core_rwlock_t *rwlock) {
  return apr_thread_rwlock_unlock(rwlock);
}

core_status_t core_rwlock_destroy (core_rwlock_t *rwlock) {
  return apr_thread_rwlock_destroy(rwlock);
}

core_pool_t * core_rwlock_pool_get (const core_rwlock_t *rwlock) {
  return apr_thread_rwlock_pool_get(rwlock);
}

core_status_t core_mutex_create(core_pool_t * pool, core_mutex_t **mutex, unsigned int flags) {
  return apr_thread_mutex_create(mutex, flags, pool);
}

core_status_t core_mutex_lock(core_mutex_t *mutex) {
  return apr_thread_mutex_lock(mutex);
}

core_status_t core_mutex_trylock(core_mutex_t *mutex) {
  return apr_thread_mutex_trylock(mutex);
}

core_status_t core_mutex_unlock(core_mutex_t *mutex) {
  return apr_thread_mutex_unlock(mutex);  
}

core_status_t core_mutex_destroy(core_mutex_t *mutex) {
  return apr_thread_mutex_destroy(mutex);
}

core_pool_t * core_mutex_pool_get(const core_mutex_t *mutex) {
  return apr_thread_mutex_pool_get(mutex);  
}

void core_uuid_format(char *buffer, const core_uuid_t *uuid) {
  apr_uuid_format(buffer, (const apr_uuid_t *) uuid);
}

void core_uuid_get(core_uuid_t *uuid) {
  core_mutex_lock(core_instance.uuid_lock);
  apr_uuid_get((apr_uuid_t *) uuid);
  core_mutex_unlock(core_instance.uuid_lock);
}

core_status_t core_uuid_parse(core_uuid_t *uuid, const char *uuid_str) {
  return apr_uuid_parse((apr_uuid_t *) uuid, uuid_str);
}

core_status_t core_md5(unsigned char digest[CORE_MD5_DIGESTSIZE], const void *input, core_size_t inputLen) {
  return apr_md5(digest, input, inputLen);
}

core_status_t core_md5_string(char digest_str[CORE_MD5_DIGEST_STRING_SIZE], const void *input, core_size_t inputLen) {
  unsigned char digest[CORE_MD5_DIGESTSIZE];
  core_status_t status = core_md5(digest, input, inputLen);
  short i, x;
  uint8_t b;

  digest_str[CORE_MD5_DIGEST_STRING_SIZE - 1] = '\0';

  for (x = i = 0; x < CORE_MD5_DIGESTSIZE; x++) {
    b = (digest[x] >> 4) & 15;
    digest_str[i++] = b + (b > 9 ? 'a' - 10 : '0');
    b = digest[x] & 15;
    digest_str[i++] = b + (b > 9 ? 'a' - 10 : '0');
  }
  digest_str[i] = '\0';

  return status;
}
