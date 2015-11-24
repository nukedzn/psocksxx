## [psocksxx] src/examples/echo/

AM_CPPFLAGS         = -I$(top_srcdir)/lib
noinst_PROGRAMS     = echo-server echo-client

echo_server_LDADD   = \
	$(top_builddir)/lib/psocksxx/libpsocksxx.la

echo_client_LDADD   = \
	$(top_builddir)/lib/psocksxx/libpsocksxx.la

echo_server_SOURCES = \
	server.cpp

echo_client_SOURCES = \
	client.cpp

