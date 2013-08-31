## [psocksxx] lib/psocksxx/

AM_CPPFLAGS             = -I$(top_srcdir)/lib
libpsocksxxincludedir   = $(includedir)/psocksxx

lib_LTLIBRARIES         = libpsocksxx.la
libpsocksxx_la_LIBADD   =
libpsocksxx_la_LDFLAGS  = -version-info @LIBPSOCKSXX_LT_VERSION@ -no-undefined
libpsocksxx_la_SOURCES  = \
	sockexception.cpp \
	sockstreambuf.cpp \
	isockstream.cpp \
	osockstream.cpp \
	nsockstream.cpp

libpsocksxxinclude_HEADERS = \
	sockexception.h \
	sockaddr.h \
	sockstreambuf.h \
	isockstream.h \
	osockstream.h \
	iosockstream.h \
	nsockstream.h

