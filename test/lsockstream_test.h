/*
*  psocksxx - A C++ wrapper for POSIX sockets
*  Copyright (C) 2013 Uditha Atukorala
*
*  This software library is free software; you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.
*
*  This software library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with this software library. If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef LSOCKSTREAM_TEST_H
#define LSOCKSTREAM_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#ifndef LOCAL_LISTENER_SOCK_PATH
#define LOCAL_LISTENER_SOCK_PATH    "/tmp/psocksxx.listener.sock"
#endif

#ifndef LOCAL_SOCK_PATH
#define LOCAL_SOCK_PATH             "/tmp/psocksxx.sock"
#endif


class lsockstream_test : public CppUnit::TestFixture {

	// setup the test suite
	CPPUNIT_TEST_SUITE( lsockstream_test );
	CPPUNIT_TEST( test_constructors );
	CPPUNIT_TEST( test_connect_fail );
	CPPUNIT_TEST( test_connect_addr_fail );
	CPPUNIT_TEST( test_connect );
	CPPUNIT_TEST( test_connect_addr );
	CPPUNIT_TEST( test_read_timeout );
	CPPUNIT_TEST_SUITE_END();

public:

	void test_constructors();
	void test_connect_fail();
	void test_connect_addr_fail();
	void test_connect();
	void test_connect_addr();
	void test_read_timeout();

};

#endif /* !LSOCKSTREAM_TEST_H */

