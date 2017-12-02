MODNAME = sip_tu
SOFIA_DIR=$(top_srcdir)/libs/sofia-sip
SOFIA_BUILDDIR=$(top_srcdir)/libs/sofia-sip
SOFIAUA_DIR=$(SOFIA_DIR)/libsofia-sip-ua
SOFIAUA_BUILDDIR=$(SOFIA_BUILDDIR)/libsofia-sip-ua
SOFIALA=$(SOFIAUA_BUILDDIR)/libsofia-sip-ua.la

lib_LTLIBRARIES = mod_sip_tu.la
mod_sip_tu_la_SOURCES =  mod_sip_tu.c
mod_sip_tu_la_CFLAGS = -I$(top_srcdir)/include/
mod_sip_tu_la_CFLAGS += -I$(top_srcdir)/libs/apr-1.5.2/include
mod_sip_tu_la_CFLAGS += -I$(top_srcdir)/libs/apr-util-1.5.4/include

mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/bnf -I$(SOFIAUA_BUILDDIR)/bnf
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/http -I$(SOFIAUA_BUILDDIR)/http
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/iptsec -I$(SOFIAUA_BUILDDIR)/iptsec
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/nea -I$(SOFIAUA_BUILDDIR)/nea
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/nth -I$(SOFIAUA_BUILDDIR)/nth
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/sdp -I$(SOFIAUA_BUILDDIR)/sdp
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/soa -I$(SOFIAUA_BUILDDIR)/soa
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/stun -I$(SOFIAUA_BUILDDIR)/stun
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/tport -I$(SOFIAUA_BUILDDIR)/tport
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/features -I$(SOFIAUA_BUILDDIR)/features
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/ipt -I$(SOFIAUA_BUILDDIR)/ipt
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/msg -I$(SOFIAUA_BUILDDIR)/msg
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/nta -I$(SOFIAUA_BUILDDIR)/nta
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/nua -I$(SOFIAUA_BUILDDIR)/nua
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/sip -I$(SOFIAUA_BUILDDIR)/sip
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/sresolv -I$(SOFIAUA_BUILDDIR)/sresolv
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/su -I$(SOFIAUA_BUILDDIR)/su
mod_sip_tu_la_CFLAGS += -I$(SOFIAUA_DIR)/url -I$(SOFIAUA_BUILDDIR)/url
# mod_sip_tu_la_CFLAGS += -I$(top_srcdir)/libs/freeDiameter/libfdproto/
# mod_sip_tu_la_CFLAGS += -I$(top_srcdir)/libs/freeDiameter/libfdcore/
# mod_sip_tu_la_CFLAGS += -I$(top_srcdir)/libs/freeDiameter/include/

# libcore_la_LDFLAGS = -all-static
mod_sip_tu_la_LDFLAGS = -module
mod_sip_tu_la_LDFLAGS += -L$(top_srcdir)/libs/apr-1.5.2/.libs/
mod_sip_tu_la_LDFLAGS += -lapr-1
mod_sip_tu_la_LDFLAGS += -L$(top_srcdir)/libs/apr-util-1.5.4/.libs/
mod_sip_tu_la_LDFLAGS += -laprutil-1



mod_sip_tu_la_LDFLAGS += -version-info 1:0:0
# mod_sip_tu_la_LIBADD = $(top_srcdir)/libs/freeDiameter/libfd.la  $(top_srcdir)/.libs/libcore.la
mod_sip_tu_la_LIBADD = $(top_srcdir)/.libs/libcore.la $(SOFIALA)
# mod_sip_tu_la_LIBADD += $(top_srcdir)/libs/freeDiameter/.libs/libfd.la

libs/sofia-sip/Makefile:
	cd $(top_srcdir)/libs/sofia-sip && sh ./configure.gnu $(MY_DEFAULT_ARGS)



$(SOFIALA): 
	cd $(SOFIA_BUILDDIR) && make && make install
