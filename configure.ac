# configure.ac
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([psocksxx], [1.1.1], [https://github.com/nukedzn/psocksxx/issues])
AC_CONFIG_AUX_DIR([aux-build])
AC_CONFIG_MACRO_DIR([aux-build/m4])
AC_CONFIG_HEADERS([include/config.h])

# Versioning rules ( C:R:A )
#
# 1. Start with version 0:0:0.
# 2. If any of the sources have changed, increment R. This is a new revision
#    of the current interface.
# 3. If the interface has changed, increment C and set R to 0. This is the
#    first revision of a new interface.
# 4. If the new interface is a superset of the previous interface
#    (that is, if the previous interface has not been broken by the
#    changes in this new release), increment A. This release is backwards
#    compatible with the previous release.
# 5. If the new interface has removed elements with respect to the
#    previous interface, then backward compatibility is broken; set A to 0.
#    This release has a new, but backwards incompatible interface.
#
# For more info see section 6.3 of the GNU Libtool Manual.
#
# In short;
# +1 : ? : +1  == new interface that does not break old one
# +1 : ? : 0   == new interface that breaks old one
#  ? : ? : 0   == no new interfaces, but breaks apps
#  ? :+1 : ?   == just some internal changes, nothing breaks but might work
#                 better
# CURRENT : REVISION : AGE

# lib versions
LIBPSOCKSXX_LT_VERSION=1:4:1
AC_SUBST(LIBPSOCKSXX_LT_VERSION)

# init
AM_INIT_AUTOMAKE([1.13 foreign])
LT_INIT()

# check for programs
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_MKDIR_P
AC_PROG_LIBTOOL

# language
AC_LANG(C++)

# doxygen
AC_CHECK_PROGS([DOXYGEN], [doxygen], [false])
AM_CONDITIONAL([HAVE_DOXYGEN], [test "x$DOXYGEN" != xfalse])
AM_COND_IF([HAVE_DOXYGEN],,
	AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
)

# cppunit
AM_PATH_CPPUNIT(1.12.1,
	[cppunit=true],
	[
		cppunit=false
		AC_MSG_WARN([Cppunit not found - continuing without unit test support])
	]
)
AM_CONDITIONAL([HAVE_CPPUNIT], [test x$cppunit = xtrue])

# TAP driver
AC_REQUIRE_AUX_FILE([tap-driver.sh])


AC_CONFIG_FILES([ \
	Makefile \
	psocksxx.pc \
	doc/doxygen.cfg \
	doc/Makefile \
	include/Makefile \
	lib/Makefile \
	lib/psocksxx/Makefile \
	src/Makefile \
	src/examples/Makefile \
	src/examples/echo/Makefile \
	test/Makefile \
])

AC_OUTPUT

