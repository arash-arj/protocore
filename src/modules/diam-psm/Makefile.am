MODNAME = mod_diam_psm
FD_BUILDDIR = $(top_srcdir)/libs/freeDiameter

lib_LTLIBRARIES = mod_diam_psm.la
mod_diam_psm_la_SOURCES =  mod_diam_psm.c
mod_diam_psm_la_CFLAGS = -I$(top_srcdir)/include/
mod_diam_psm_la_CFLAGS += -I$(top_srcdir)/libs/apr-1.5.2/include
mod_diam_psm_la_CFLAGS += -I$(top_srcdir)/libs/apr-util-1.5.4/include
mod_diam_psm_la_CFLAGS += -I$(top_srcdir)/libs/freeDiameter/libfdproto/
mod_diam_psm_la_CFLAGS += -I$(top_srcdir)/libs/freeDiameter/libfdcore/
mod_diam_psm_la_CFLAGS += -I$(top_srcdir)/libs/freeDiameter/include/

# libcore_la_LDFLAGS = -all-static
mod_diam_psm_la_LDFLAGS = -module
mod_diam_psm_la_LDFLAGS += -L$(top_srcdir)/libs/apr-1.5.2/.libs/
mod_diam_psm_la_LDFLAGS += -lapr-1
mod_diam_psm_la_LDFLAGS += -L$(top_srcdir)/libs/apr-util-1.5.4/.libs/
mod_diam_psm_la_LDFLAGS += -laprutil-1
mod_diam_psm_la_LDFLAGS += -L$(top_srcdir)/libs/freeDiameter/.libs/
mod_diam_psm_la_LDFLAGS += -lfd
mod_diam_psm_la_LDFLAGS += -lgnutls

mod_diam_psm_la_LDFLAGS += -version-info 1:0:0
# mod_diam_psm_la_LIBADD = $(top_srcdir)/libs/freeDiameter/libfd.la  $(top_srcdir)/.libs/libcore.la
mod_diam_psm_la_LIBADD = $(top_srcdir)/.libs/libcore.la
# mod_diam_psm_la_LIBADD += $(top_srcdir)/libs/freeDiameter/.libs/libfd.la

$(top_srcdir)/libs/freeDiameter/libfd.la: 
	cd $(FD_BUILDDIR) && make && make install

libs/freeDiameter/Makefile:
	cd libs/freeDiameter && ./configure $(MY_DEFAULT_ARGS)

