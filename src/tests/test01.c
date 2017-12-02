#include <time.h>
#include <core.h>

int main()
{
  core_status_t rv;


  // initialize core
  core_init();
  
  
  // Load Modules
  char path_prefix[] = "/core/lib";
  core_module_t *mod_diam_psm = core_load_module("mod_diam_psm", path_prefix);
  core_module_t *mod_sip_tu = core_load_module("mod_sip_tu", path_prefix);
  core_module_t *mod_route_logic = core_load_module("mod_route_logic", path_prefix);
  

  /* // Testing */
  /* core_event_t * my_event; */
  
  /* int i = 0; */
  /* printf("Test: Starting event test\n"); */

  /* struct timespec tstart={0,0}, tend={0,0}; */
  /* clock_gettime(CLOCK_MONOTONIC, &tstart); */

  /* for(i = 0; i < 10; i++) { */

  /*   my_event = core_event_create("diam_psm_request", 0, NULL); */

  /*   core_event_header_add(my_event, "Event", "test-event"); */
  /*   core_event_header_add(my_event, "Event-Priority", "0"); */
  /*   core_event_header_add(my_event, "Param01", "arash"); */

  /*   core_event_publish(my_event, 0); */
  /* } */

  /* clock_gettime(CLOCK_MONOTONIC, &tend); */
  /* double time_diff = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - */
  /*   ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec); */

  
  /* printf("Test: Event test ended with %d events published in %.5f seconds (rate of %f kilo events/sec.)\n", i, time_diff, i*0.001/time_diff); */


  int i = 0;
  for(i = 0; i < 100000; i++) {
    core_sleep(1000000); /* sleep 100 seconds */
  }

  
  
  // Destroy Modules
  if(mod_diam_psm) {
    printf("destroying mod_diam_psm\n");
    core_destroy_module(mod_diam_psm);
  }

  if(mod_sip_tu) {
    printf("destroying mod_sip_tu\n");
    core_destroy_module(mod_sip_tu);
  }

  if(mod_route_logic) {
    printf("destroying mod_route_logic\n");
    core_destroy_module(mod_route_logic);
  }


  // shutdown core
  core_terminate();
  
  return 0;
}

