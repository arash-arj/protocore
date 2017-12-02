#include <core_module.h>
#include <protected/core_protect.h>


core_module_t * core_load_module(const char * mod_name, const char * path) {

  core_status_t rv;
  char full_path[100];
  char load_func_name[100];
  char destroy_func_name[100];
  core_module_t *mod;
  core_pool_t *core_pool;

  core_pool = core_instance.pool;

  sprintf(full_path, "%s/%s.so", path, mod_name);
  sprintf(load_func_name, "%s_load", mod_name);
  sprintf(destroy_func_name, "%s_destroy", mod_name);

  printf("created path strings\n");
    
  // create and initialize modules handle from core's memory pool
  mod = core_palloc(core_pool, sizeof(core_module_t));
  
  printf("created modules handle\n");

  /////// Load modules shared-library
  if ((rv = core_dso_load(&(mod->dso_h), full_path, core_pool)) != CORE_SUCCESS) {
    char buf[256];
    core_strerror(rv, buf, sizeof(buf));
    puts(buf);  /* show the error description */
    printf("An error occured loading the module...'%s'\n", full_path);
    goto error;
  }
  
  if ((rv = core_dso_sym((core_dso_handle_sym_t*)&(mod->load_func), mod->dso_h, load_func_name)) != CORE_SUCCESS) {
    printf("An error occured loading the module's load function...\n");
    goto error;
  }

  if ((rv = core_dso_sym((core_dso_handle_sym_t*)&(mod->destroy_func), mod->dso_h, destroy_func_name)) != CORE_SUCCESS) {
    printf("An error occured loading the module's destroy function...\n");
    goto error;
  }
  ///////
  
  /////// Allocate and initialize modules memory pool
  // create modules memory pool
  rv = core_pool_create(&(mod->pool));
  if(rv != CORE_SUCCESS) {
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
  core_dso_unload(mod->dso_h);
  core_pool_destroy(&(mod->pool));
}
