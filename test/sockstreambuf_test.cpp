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

#include "sockstreambuf_test.h"

#include <psocksxx/sockstreambuf.h>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( sockstreambuf_test );

// use namespace psocksxx
using namespace psocksxx;


void sockstreambuf_test::setUp() { }
void sockstreambuf_test::tearDown() { }


void sockstreambuf_test::test_constructors() {

	const sockstreambuf ssb;
	const sockstreambuf ssb_s( -1 );

	// check the default constructor
	CPPUNIT_ASSERT( ssb.socket() == ssb_s.socket() );

}


void sockstreambuf_test::test_open_close_local_ip() {

	sockstreambuf ssb;

	CPPUNIT_ASSERT_NO_THROW_MESSAGE( "Failed to open socket communication end-point",
		ssb.open( sockstreambuf::pf_local, sockstreambuf::sock_stream, sockstreambuf::ipproto_ip ) );

	// close the opened socket end-point
	ssb.close();

}


void sockstreambuf_test::test_flush_empty() {

	sockstreambuf ssb( -1 );
	CPPUNIT_ASSERT( sockstreambuf::eof == ssb.flush() );

}


void sockstreambuf_test::test_bad_connect_failure() {

	// socket address
	psocksxx::sockaddr saddr;

	// socket stream buffer
	sockstreambuf ssb( -1 );

	// this should throw a bad file descriptor error
	CPPUNIT_ASSERT_THROW( ssb.connect( &saddr ), sockexception );

}


void sockstreambuf_test::test_bad_bind_failure() {

	// socket address
	psocksxx::sockaddr saddr;

	// socket stream buffer
	sockstreambuf ssb( -1 );

	// this should throw a bad file descriptor error
	CPPUNIT_ASSERT_THROW( ssb.bind( &saddr ), sockexception );

}

