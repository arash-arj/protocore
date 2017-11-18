#include <time.h>
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
  char path_prefix[] = "/root/dev/protocore/bin";
  core_module_t *mod_radius = core_load_module(core_pool, "mod_radius", path_prefix);
  /* core_module_t *mod_cli = core_load_module(core_pool, "mod_cli", path_prefix); */
  ////////////////////////////////


  ////////////////////////////////
  /////// Create event server
  ////////////////////////////////
  core_event_server_t *ev_server;
  ev_server = core_event_server_create();
  core_event_subscribe(ev_server, "radius_request", mod_radius->mqueue);
  ////////////////////////////////

  core_event_t * my_event;

  //apr_sleep(1000000); /* sleep 100 seconds */

  int i = 0;
  printf("Test: Starting event test\n");

  struct timespec tstart={0,0}, tend={0,0};
  clock_gettime(CLOCK_MONOTONIC, &tstart);

  for(i = 0; i < 10000000; i++) {

    my_event = core_event_create("radius_request", 0, NULL);

    core_event_header_add(my_event, "Event", "test-event");
    core_event_header_add(my_event, "Param01", "arash");


    core_event_publish(ev_server, my_event, 0);
  }

  clock_gettime(CLOCK_MONOTONIC, &tend);
  double time_diff = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
    ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
  printf("Test: Event test ended with %d events published in %.5f seconds (rate of %f kilo events/sec.)\n", i, time_diff, i*0.001/time_diff);
  
  ////////////////////////////////
  /////// Testing
  ////////////////////////////////

  printf("Here i am\n");
  /* apr_sleep(5000000); /\* sleep 100 seconds *\/ */
  ////////////////////////////////
  /////// Destroy Modules
  ////////////////////////////////
  printf("destroying mod_radius\n");
  core_destroy_module(mod_radius);
  /* core_destroy_module(mod_cli); */
  ////////////////////////////////


  //apr_sleep(300000); /* sleep 100 seconds */
  ////////////////////////////////
  /////// Kill the whole beast
  ////////////////////////////////
  /* apr_pool_destroy(core_pool); */
  printf("Terminating APR\n");
  apr_terminate();
  printf("voila! c'est fini!\n");
  ////////////////////////////////
  
  return 0;
}

