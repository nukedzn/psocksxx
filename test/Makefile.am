## [psocksxx] test/

AUTOMAKE_OPTIONS        = subdir-objects
TEST_EXTENSIONS         = .tap
TAP_LOG_DRIVER          = env AM_TAP_AWK='$(AWK)' $(SHELL) \
	$(top_srcdir)/aux-build/tap-driver.sh


if HAVE_CPPUNIT
TESTS          = tap-runner.tap
check_PROGRAMS = tap-runner.tap

CPPUNIT_TEST_SOURCES = \
	sockstreambuf_test.h sockstreambuf_test.cpp

tap_runner_tap_SOURCES = tap-runner.cpp \
	$(CPPUNIT_TEST_SOURCES) \
	tap/tap_listener.h tap/tap_listener.cpp

tap_runner_tap_CXXFLAGS = -I$(top_srcdir)/lib $(CPPUNIT_CFLAGS)
tap_runner_tap_LDFLAGS  = $(top_builddir)/lib/psocksxx/libpsocksxx.la $(CPPUNIT_LIBS)
endif

