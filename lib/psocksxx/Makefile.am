## [psocksxx] lib/psocksxx/

AM_CPPFLAGS             = -I$(top_srcdir)/lib
libpsocksxxincludedir   = $(includedir)/psocksxx

lib_LTLIBRARIES         = libpsocksxx.la
libpsocksxx_la_LIBADD   =
libpsocksxx_la_LDFLAGS  = -version-info @LIBPSOCKSXX_LT_VERSION@ -no-undefined
libpsocksxx_la_SOURCES  = \
	sockbuf.cpp \
	isockstream.cpp \
	osockstream.cpp

libpsocksxxinclude_HEADERS = \
	sockbuf.h \
	isockstream.h \
	osockstream.h

