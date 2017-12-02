#include <mod_route_logic.h>


void route_logic_handle_core_event(core_event_t * event, route_logic_context_t * mod_context) {

  core_event_t *response_event = NULL;
  core_event_header_t *next = NULL;
  route_proxy_t *proxy = NULL;
  char * trans_id = NULL;
  char * originator_id = NULL;

  char * sip_method = NULL;
  char * sip_status = NULL;
  char * sip_call_id = NULL;
  char * sip_cseq = NULL;
  char * sip_to = NULL;
  char * sip_from = NULL;
  char * sip_contact = NULL;
  char * sip_www_authenticate = NULL;
  char * sip_authorization = NULL;
  char * sip_proxy_auth_required = NULL;
  

  if(!event) {
    return;
  }

  if(!strcmp(event->name, "sip_i_trans") ) {

    /* get required info from uas event */
    trans_id = core_event_header_get(event, "trans-id");
    sip_method = core_event_header_get(event, "sip-method");
    sip_call_id = core_event_header_get(event, "sip-call-id");
    sip_cseq = core_event_header_get(event, "sip-cseq");
    sip_to = core_event_header_get(event, "sip-to");
    sip_from = core_event_header_get(event, "sip-from");
    sip_contact = core_event_header_get(event, "sip-contact");
    sip_authorization = core_event_header_get(event, "sip-authorization");

    printf("icscf: incoming sip request: '%s' with trans_id of '%s'\n", sip_method, trans_id);

    /* create proxy object */
    proxy = route_proxy_create(trans_id, mod_context);
    
    /* publish event for sip uac to relay the sip message */
    response_event = core_event_create("sip_tu_do_request", 0, NULL);

    core_event_header_add(response_event, "originator-id", trans_id);
    if(sip_cseq) {
    core_event_header_add(response_event, "sip-call-id", sip_call_id);
    }
    if(sip_cseq) {
      core_event_header_add(response_event, "sip-cseq", sip_cseq);
    }
    if(sip_authorization) {
      core_event_header_add(response_event, "sip-authorization", sip_authorization);
    }
    if(sip_to) {
      core_event_header_add(response_event, "sip-to", sip_to);
    }
    if(sip_from) {
      core_event_header_add(response_event, "sip-from", sip_from);
    }
    if(sip_contact) {
      core_event_header_add(response_event, "sip-contact", sip_contact);
    }

    core_event_publish(response_event, 0);

  }
  else if(!strcmp(event->name, "sip_r_trans") ) {

    originator_id = core_event_header_get(event, "originator-id");
    trans_id = core_event_header_get(event, "trans-id");
    sip_method = core_event_header_get(event, "sip-method");
    sip_call_id = core_event_header_get(event, "sip-call-id");
    sip_cseq = core_event_header_get(event, "sip-cseq");
    sip_status = core_event_header_get(event, "sip-status");
    sip_to = core_event_header_get(event, "sip-to");
    sip_from = core_event_header_get(event, "sip-from");
    sip_contact = core_event_header_get(event, "sip-contact");
    sip_www_authenticate = core_event_header_get(event, "sip-www-authenticate");;
    sip_proxy_auth_required = core_event_header_get(event, "sip-proxy-authorization-required");;

    
    printf("icscf: response to sip request: '%s' with trans_id of '%s', originator id of '%s'\n", sip_method, trans_id, originator_id);

    
    response_event = core_event_create("sip_tu_do_respond", 0, NULL);
    core_event_header_add(response_event, "trans-id", originator_id);
    core_event_header_add(response_event, "sip-method", sip_method);
    core_event_header_add(response_event, "sip-status", sip_status);
    core_event_header_add(response_event, "sip-call-id", sip_call_id);
    core_event_header_add(response_event, "sip-cseq", sip_cseq);
    core_event_header_add(response_event, "sip-to", sip_to);
    core_event_header_add(response_event, "sip-from", sip_from);
    core_event_header_add(response_event, "sip-contact", sip_contact);
    core_event_header_add(response_event, "sip-www-authenticate", sip_www_authenticate);
    core_event_header_add(response_event, "sip-proxy-authorization-required", sip_proxy_auth_required);
    core_event_publish(response_event, 0);

  }

}
