## [psocksxx] test/

AUTOMAKE_OPTIONS        = subdir-objects
LOG_DRIVER              = env AM_TAP_AWK='$(AWK)' $(SHELL) \
	$(top_srcdir)/aux-build/tap-driver.sh


if HAVE_CPPUNIT
TESTS          = tap-runner
check_PROGRAMS = tap-runner

CPPUNIT_TEST_SOURCES = \
	sockstreambuf_test.h sockstreambuf_test.cpp

tap_runner_SOURCES = tap-runner.cpp \
	$(CPPUNIT_TEST_SOURCES) \
	tap/tap_listener.h tap/tap_listener.cpp

tap_runner_CXXFLAGS = -I$(top_srcdir)/lib $(CPPUNIT_CFLAGS)
tap_runner_LDFLAGS  = $(top_builddir)/lib/psocksxx/libpsocksxx.la $(CPPUNIT_LIBS)
endif

