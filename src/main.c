#include <core.h>
#include <core_mqueue.h>
#include <core_event.h>

int main()
{
  apr_status_t rv;
  apr_pool_t *core_pool = NULL;

  
  ////////////////////////////////
  /////// Initialize the whole beast
  ////////////////////////////////
  // Initialize apr and create main memory pool
  apr_initialize();
  rv = core_pool_create(&core_pool, NULL);
  if(rv != APR_SUCCESS) {
    printf("Not successful\n");
    return 0;
  }
  else {
    printf("Successfully created core memory pool\n");
  }
  ////////////////////////////////


  ////////////////////////////////
  /////// Load Modules
  ////////////////////////////////
  char path_prefix[] = "/root/dev/AVA-ProtoCore/bin/";
  core_module_t *mod_radius = core_load_module(core_pool, "mod_radius", path_prefix);
  core_module_t *mod_cli = core_load_module(core_pool, "mod_cli", path_prefix);
  ////////////////////////////////


  ////////////////////////////////
  /////// Create event server
  ////////////////////////////////
  core_event_server_t *ev_server;
  ev_server = core_event_server_create();
  core_event_subscribe(ev_server, "radius_request", mod_radius->mqueue);
  ////////////////////////////////

  core_event_t * my_event;
  int *test_int;
  test_int = core_palloc(mod_cli->pool, sizeof(int*));
  *test_int = 5464;

  //apr_sleep(1000000); /* sleep 100 seconds */

  int i = 0;
  printf("Successfully published the event\n");
  for(i = 0; i < 50000000; i++) {
    my_event = core_event_create("radius_request", (void *) test_int, sizeof(int), 0);
    core_event_publish(ev_server, my_event);
  }
  printf("Successfully published the event\n");
  ////////////////////////////////
  /////// Testing
  ////////////////////////////////
  /* int *test_int = core_palloc(mod_cli->pool, sizeof(int*)); */
  /* *test_int = 5464; */
  /* void *data = test_int; */
  /* rv = apr_queue_push(mod_cli->mqueue->queue, data); */
  ////////////////////////////////
  
  //apr_sleep(10000000); /* sleep 100 seconds */

  ////////////////////////////////
  /////// Destroy Modules
  ////////////////////////////////
  printf("destroying mod_radius\n");
  core_destroy_module(mod_radius);
  printf("destroying mod_cli\n");
  core_destroy_module(mod_cli);
  ////////////////////////////////


  //apr_sleep(300000); /* sleep 100 seconds */

  ////////////////////////////////
  /////// Kill the whole beast
  ////////////////////////////////
  apr_pool_destroy(core_pool);
  apr_terminate();
  ////////////////////////////////
  
  return 0;
}

