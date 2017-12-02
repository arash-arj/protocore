
#include "fdproto-internal.h"
#include "fdcore-internal.h"

static struct fd_config conf;
extern struct fd_config *fd_g_config;

/* /\* for dumps *\/ */
/* static char * tbuf = NULL; size_t tbuflen = 0; */
/* #define FD_DUMP_TEST_PARAMS &tbuf, &tbuflen, NULL */


int main(int argc, char *argv[])
{
  struct msg * acr = NULL;
  struct avp * pi = NULL, *avp1, *avp2;
  unsigned char * buf = NULL;
  struct avp_hdr * avpdata = NULL;
  struct msg_hdr * msgdata = NULL;

  fd_g_config = &conf;
  memset(fd_g_config, 0, sizeof(struct fd_config));
  /* fd_g_debug_lvl--; */
  /* fd_g_debug_lvl--; */
	
  fd_libproto_init();
  fd_dict_init(&fd_g_config->cnf_dict) ;
  fd_dict_base_protocol(fd_g_config->cnf_dict);
	

  
  /* Create the message object from model */
  struct dict_object * acr_model = NULL;
  fd_dict_search ( fd_g_config->cnf_dict, DICT_COMMAND, CMD_BY_NAME, "Accounting-Request", &acr_model, ENOENT );
  fd_msg_new ( acr_model, 0, &acr );
  fd_msg_browse ( acr, MSG_BRW_FIRST_CHILD, NULL, NULL);

  
  /* Create the Proxy-Info AVP from model */
  struct dict_object * pi_model = NULL;
  fd_dict_search ( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Proxy-Info", &pi_model, ENOENT );
  fd_msg_avp_new ( pi_model, 0, &pi );
  fd_msg_avp_add ( acr, MSG_BRW_LAST_CHILD, pi) ;
  

  /* 		#define ADD_AVP( _parent, _position, _avpi, _avpvendor, _avpname) {			\ */
  /* 			struct dict_object * _avp = NULL;						\ */
  /* 			struct dict_avp_request _req = { (_avpvendor), 0, (_avpname) };			\ */
  /* 			CHECK( 0, fd_dict_search( fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME_AND_VENDOR, &_req, &_avp, ENOENT));\ */
  /* 			CHECK( 0, fd_msg_avp_new ( _avp, 0, &_avpi ) );					\ */
  /* 			CHECK( 0, fd_msg_avp_add ( (_parent), (_position), _avpi ) );			\ */
  /* 		} */

  
  fd_msg_hdr ( acr, &msgdata );
  /* msgdata->msg_appl = 73566; */			
  msgdata->msg_hbhid = 0x4b44b41d;
  msgdata->msg_eteid = 0xe2ee2e1d;


  fd_msg_update_length ( acr );
  fd_msg_bufferize( acr, &buf, NULL );

  printf("first>>>%d\n", buf[0]);
  printf("size>>>>%d\n", msgdata->msg_length);

  /* fd_log_notice("%s", fd_msg_dump_treeview(FD_DUMP_TEST_PARAMS, acr, fd_g_config->cnf_dict, 0, 1)); */
	
  fd_dict_fini(&fd_g_config->cnf_dict) ;

} 
	
