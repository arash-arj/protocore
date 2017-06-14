#include <core.h>


core_module_t * core_load_module(apr_dso_handle_t *dso_h, apr_pool_t *core_pool, const char * mod_name, const char * path) {

  apr_status_t rv;
  char full_path[100];
  char load_func_name[100];
  char destroy_func_name[100];
  core_module_t *mod;
  
  sprintf(full_path, "%s/%s.so", path, mod_name);
  sprintf(load_func_name, "%s_load", mod_name);
  sprintf(destroy_func_name, "%s_destroy", mod_name);

  // create and initialize modules handle from core's memory pool
  mod = core_palloc(core_pool, sizeof(core_module_t *));

  /////// Load modules shared-library
  if ((rv = apr_dso_load(&dso_h, full_path, core_pool)) != APR_SUCCESS) {
    printf("An error occured loading the module...'%s'\n", full_path);
    goto error;
  }
  
  if ((rv = apr_dso_sym((apr_dso_handle_sym_t*)&(mod->load_func), dso_h, load_func_name)) != APR_SUCCESS) {
    printf("An error occured loading the module's load function...\n");
    goto error;
  }

  if ((rv = apr_dso_sym((apr_dso_handle_sym_t*)&(mod->destroy_func), dso_h, destroy_func_name)) != APR_SUCCESS) {
    printf("An error occured loading the module's destroy function...\n");
    goto error;
  }
  ///////

  
  /////// Allocate and initialize modules memory pool

  // create modules memory pool
  rv = core_pool_create(&(mod->pool), NULL);
  if(rv != APR_SUCCESS) {
    printf("Not successful\n");
    return 0;
  }
  else {
    printf("Successfully created modules memory pool\n");
  }
  ///////
 
  /////// Actually load the module
  mod->load_func(mod);
  ///////
  
  return mod;
error:
  return 0;
}

void core_destroy_module(core_module_t * mod) {
  mod->destroy_func(mod);
}
