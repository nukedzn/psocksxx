## [psocksxx] test/

AUTOMAKE_OPTIONS        = subdir-objects
TESTS                   =
TEST_EXTENSIONS         = .tap
TAP_LOG_DRIVER          = env AM_TAP_AWK='$(AWK)' $(SHELL) \
	$(top_srcdir)/aux-build/tap-driver.sh


if HAVE_CPPUNIT
check_PROGRAMS = tap-runner.tap
TESTS          += $(check_PROGRAMS)

CPPUNIT_TEST_SOURCES = \
	lecho.h lecho.cpp \
	sockstreambuf_test.h sockstreambuf_test.cpp \
	lsockstream_test.h lsockstream_test.cpp \
	nsockaddr_test.h nsockaddr_test.cpp \
	nsockstream_test.h nsockstream_test.cpp \
	tcpnsockstream_test.h tcpnsockstream_test.cpp

tap_runner_tap_SOURCES = \
	tap-runner.cpp \
	$(CPPUNIT_TEST_SOURCES) \
	tap/tap_listener.h tap/tap_listener.cpp

tap_runner_tap_CXXFLAGS = -I$(top_srcdir)/lib $(CPPUNIT_CFLAGS)
tap_runner_tap_LDFLAGS  = $(top_builddir)/lib/psocksxx/libpsocksxx.la $(CPPUNIT_LIBS)
endif


# remove xunit XML output files
CLEANFILES = xunit.xml

