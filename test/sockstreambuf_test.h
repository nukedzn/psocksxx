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

#ifndef SOCKSTREAMBUF_TEST_H
#define SOCKSTREAMBUF_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <psocksxx/sockaddr.h>

#define LOCAL_LISTENER_SOCK_PATH    "/tmp/psocksxx.listener.sock"
#define LOCAL_SOCK_PATH             "/tmp/psocksxx.sock"


class sockstreambuf_test : public CppUnit::TestFixture {

	// setup the test suite
	CPPUNIT_TEST_SUITE( sockstreambuf_test );
	CPPUNIT_TEST( test_constructors );
	CPPUNIT_TEST( test_open_close_local_ip );
	CPPUNIT_TEST( test_flush_empty );
	CPPUNIT_TEST( test_bad_flush );
	CPPUNIT_TEST( test_bad_connect_failure );
	CPPUNIT_TEST( test_bad_bind_failure );
	CPPUNIT_TEST( test_bad_listen_failure );
	CPPUNIT_TEST( test_bad_accept_failure );
	CPPUNIT_TEST( test_local_bind );
	CPPUNIT_TEST( test_local_listen );
	CPPUNIT_TEST( test_local_connect );
	CPPUNIT_TEST( test_local_connect_timeout );
	CPPUNIT_TEST( test_local_accept );
	CPPUNIT_TEST( test_local_flush );
	CPPUNIT_TEST( test_local_flush_read );
	CPPUNIT_TEST( test_local_ostream );
	CPPUNIT_TEST( test_local_istream );
	CPPUNIT_TEST( test_set_timeout );
	CPPUNIT_TEST( test_clear_timeout );
	CPPUNIT_TEST_SUITE_END();

public:
	sockstreambuf_test();
	~sockstreambuf_test();

	void setUp();
	void tearDown();

	void test_constructors();
	void test_open_close_local_ip();
	void test_flush_empty();
	void test_bad_flush();
	void test_bad_connect_failure();
	void test_bad_bind_failure();
	void test_bad_listen_failure();
	void test_bad_accept_failure();
	void test_local_bind();
	void test_local_listen();
	void test_local_connect();
	void test_local_connect_timeout();
	void test_local_accept();
	void test_local_flush();
	void test_local_flush_read();
	void test_local_ostream();
	void test_local_istream();
	void test_set_timeout();
	void test_clear_timeout();


private:

	// base sockaddr class for negative testing purposes
	struct : public psocksxx::sockaddr, public sockaddr {
		socklen_t size() const throw() { return sizeof( ::sockaddr ); }
		::sockaddr * psockaddr() const throw() { return (::sockaddr *) this; }
	} _sockaddr;


	void connect_local() throw();

};


#endif /* !SOCKSTREAMBUF_TEST_H */

