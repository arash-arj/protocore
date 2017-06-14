#include <core.h>
#include <core_mqueue.h>

apr_pool_t *core_pool = NULL;
apr_dso_handle_t *dso_h = NULL;

int main()
{
  apr_status_t rv;
  
  // initialize apr and create main memory pool
  apr_initialize();
  rv = core_pool_create(&core_pool, NULL);
  if(rv != APR_SUCCESS) {
    printf("Not successful\n");
    return 0;
  }
  else {
    printf("Successfully created core memory pool\n");
  }

  char path_prefix[] = "/root/dev/AVA-ProtoCore/bin/";
  core_module_t *mod_radius = core_load_module(dso_h, core_pool, "mod_radius", path_prefix);
  core_module_t *mod_cli = core_load_module(dso_h, core_pool, "mod_cli", path_prefix);
  //core_module_t *mod_cli = core_load_module(core_pool);

  apr_sleep(300000); /* sleep 100 seconds */
 
  int *test_int = core_palloc(mod_radius->pool, sizeof(int*));
  *test_int = 5464;
  void *data = test_int;
  rv = apr_queue_push(mod_cli->mqueue->queue, data);

  apr_sleep(300000); /* sleep 100 seconds */

  printf("destroying mod_radius\n");
  core_destroy_module(mod_radius);
  printf("destroying mod_cli\n");
  core_destroy_module(mod_cli);


  apr_sleep(300000); /* sleep 100 seconds */

  apr_dso_unload(dso_h);
  apr_pool_destroy(core_pool);
  apr_terminate();
  return 0;
}



/* static void * APR_THREAD_FUNC producer(apr_thread_t *thd) */
/* { */
/*   long sleeprate; */
/*   //abts_case *tc = data; */
/*   apr_status_t rv; */
/*   int i = 0; */
/*   while (1) */
/*     { */
/*       i++; */
/*       if(i > 10) { */
/* 	return; */
/*       } */
/*       rv = apr_queue_push(queue, NULL); */
/*       if (rv == APR_EINTR) // the blocking was interrupted (try again) */
/* 	continue; */
/*       if (rv == APR_EOF) // if the queue has been terminated */
/* 	break; */
/*       if (rv == APR_SUCCESS) // on a successful pop */
/* 	printf("Pushing #%d\n", i); */
/*     } */
/*   return NULL; */
/* } */

