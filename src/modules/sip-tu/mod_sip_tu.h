#ifndef MOD_SIP_TU_H
#define MOD_SIP_TU_H

#include <core.h>


#include <sofia-sip/su_wait.h>
#include <sofia-sip/nta.h>
#include "sofia-sip/sip_status.h"

#include <sofia-sip/sdp.h>
#include <sofia-sip/sip_header.h>

#include <sofia-sip/su_log.h>
#include <sofia-sip/su_tagarg.h>
#include <sofia-sip/su_tag_io.h>
#include <sofia-sip/su_string.h>

#include <sofia-sip/tport_tag.h>
#include <sofia-sip/auth_module.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <unistd.h>


typedef struct {

  core_thread_t *consumer_thread;

  core_thread_t *sofia_thread;

  int module_shutdown;
  
} sip_tu_module_context_t;


typedef struct {

  /* possible incoming request */
  nta_incoming_t *irq;

  /* possible outgoing request */
  nta_outgoing_t *orq;
  
} sip_tu_trans_context_t;


typedef struct {

  /* uac transactions own core side uuid
  */
  const char * trans_id;

  /* uuid of the originator, 
     can be anything, needed to
     route back the response to the
     corresponding route logic
  */
  const char * origin_id;
  
} sofia_magic_t;


static su_home_t *home;
static su_root_t *root;
static nta_agent_t *external_agent;
static nta_agent_t *internal_agent;

static nta_leg_t *external_leg;
static nta_leg_t *internal_leg;


void mod_sip_tu_load(core_module_t *module);
void sip_tu_handle_core_event(core_event_t * event);
static void * sip_tu_core_msg_consumer(core_thread_t *, core_module_t *);
static void * sip_tu_sofia_worker(core_thread_t *, core_module_t *);

int sip_tu_sofia_incoming_callback(nta_leg_magic_t *context, nta_leg_t *leg, nta_incoming_t *irq, const sip_t *sip);
int sip_tu_sofia_outgoing_callback(nta_outgoing_magic_t *sip_tu_magic, nta_outgoing_t *orq, sip_t const *sip);
void sip_tu_sofia_init();



#endif
