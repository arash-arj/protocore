MODNAME = mod_route_logic

lib_LTLIBRARIES = mod_route_logic.la
mod_route_logic_la_SOURCES =  mod_route_logic.c route_proxy.c icscf.c
mod_route_logic_la_CFLAGS = -I$(top_srcdir)/include/
mod_route_logic_la_CFLAGS += -I$(top_srcdir)/libs/apr-1.5.2/include
mod_route_logic_la_CFLAGS += -I$(top_srcdir)/libs/apr-util-1.5.4/include

# libcore_la_LDFLAGS = -all-static
mod_route_logic_la_LDFLAGS = -module
mod_route_logic_la_LDFLAGS += -L$(top_srcdir)/libs/apr-1.5.2/.libs/
mod_route_logic_la_LDFLAGS += -lapr-1
mod_route_logic_la_LDFLAGS += -L$(top_srcdir)/libs/apr-util-1.5.4/.libs/
mod_route_logic_la_LDFLAGS += -laprutil-1

mod_route_logic_la_LDFLAGS += -version-info 1:0:0
# mod_route_logic_la_LIBADD = $(top_srcdir)/libs/freeDiameter/libfd.la  $(top_srcdir)/.libs/libcore.la
mod_route_logic_la_LIBADD = $(top_srcdir)/.libs/libcore.la
# mod_route_logic_la_LIBADD += $(top_srcdir)/libs/freeDiameter/.libs/libfd.la

