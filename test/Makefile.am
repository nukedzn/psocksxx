## [psocksxx] test/

if HAVE_CPPUNIT
TESTS          = runner
check_PROGRAMS = $(TESTS)

runner_SOURCES = runner.cpp \
	sockstreambuf_test.h sockstreambuf_test.cpp

runner_CXXFLAGS = -I$(top_srcdir)/lib $(CPPUNIT_CFLAGS)
runner_LDFLAGS  = $(top_builddir)/lib/psocksxx/libpsocksxx.la $(CPPUNIT_LIBS)
endif

