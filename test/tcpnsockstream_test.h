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

#ifndef TCPNSOCKSTREAM_TEST_H
#define TCPNSOCKSTREAM_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <psocksxx/nsockaddr.h>

#ifndef NSOCK_NODE
#define NSOCK_NODE "localhost"
#endif

#ifndef NSOCK_SERVICE
#define NSOCK_SERVICE "21234"
#endif

#ifndef NSOCK_SERVICE_2
#define NSOCK_SERVICE_2 "21236"
#endif

#ifndef NSOCK_BIND_SERVICE
#define NSOCK_BIND_SERVICE "21235"
#endif


class tcpnsockstream_test : public CppUnit::TestFixture {

	// setup the test suite
	CPPUNIT_TEST_SUITE( tcpnsockstream_test );
	CPPUNIT_TEST( test_constructors );
	CPPUNIT_TEST( test_connect_addr );
	CPPUNIT_TEST( test_connect_host_port );
	CPPUNIT_TEST( test_bind_addr );
	CPPUNIT_TEST( test_listen_addr );
	CPPUNIT_TEST( test_accept_addr );
	CPPUNIT_TEST( test_bind_addr_fail );
	CPPUNIT_TEST( test_io_addr );
	CPPUNIT_TEST_SUITE_END();

public:

	void test_constructors();
	void test_connect_addr();
	void test_connect_host_port();
	void test_bind_addr();
	void test_listen_addr();
	void test_accept_addr();
	void test_bind_addr_fail();
	void test_io_addr();


private:

	void connect_naddr( psocksxx::nsockaddr * naddr ) throw();

};

#endif /* !TCPNSOCKSTREAM_TEST_H */

