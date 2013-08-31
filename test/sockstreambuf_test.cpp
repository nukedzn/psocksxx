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
#include <psocksxx/lsockaddr.h>

#include <cerrno>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( sockstreambuf_test );

// use namespace psocksxx
using namespace psocksxx;


void sockstreambuf_test::setUp() {

	// initialise locals
	_sockaddr.sa_family = AF_LOCAL;

}


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

	// socket stream buffer
	sockstreambuf ssb( -1 );

	// this should throw a bad file descriptor error
	CPPUNIT_ASSERT_THROW( ssb.connect( &_sockaddr ), sockexception );

}


void sockstreambuf_test::test_bad_bind_failure() {

	// socket stream buffer
	sockstreambuf ssb( -1 );

	// this should throw a bad file descriptor error
	CPPUNIT_ASSERT_THROW( ssb.bind( &_sockaddr ), sockexception );

}


void sockstreambuf_test::test_bad_listen_failure() {

	// socket stream buffer
	sockstreambuf ssb( -1 );

	// this should throw a bad file descriptor error
	CPPUNIT_ASSERT_THROW( ssb.listen(), sockexception );

}


void sockstreambuf_test::test_bad_accept_failure() {

	// socket stream buffer
	sockstreambuf ssb( -1 );

	// this should throw a bad file descriptor error
	CPPUNIT_ASSERT_THROW( ssb.accept(), sockexception );

}


void sockstreambuf_test::test_local_bind() {

	// socket stream buffer;
	sockstreambuf ssb;

	// local (unix) socket address
	const char * path = "/tmp/psocksxx.sock";
	lsockaddr saddr( path );


	// prepare the socket
	try {
		ssb.open( sockstreambuf::pf_local, sockstreambuf::sock_stream, sockstreambuf::proto_unspec );
	} catch( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
		return;
	}

	// bind to address
	CPPUNIT_ASSERT_NO_THROW( ssb.bind( &saddr ) );


	// close socket
	ssb.close();

	// unlink
	if ( unlink( path ) !=0 ) {
		CPPUNIT_FAIL( std::string( "failed to unlink socket: " ).append( path ) );
	}

}


void sockstreambuf_test::test_local_listen() {

	// socket stream buffer;
	sockstreambuf ssb;

	// local (unix) socket address
	const char * path = "/tmp/psocksxx.sock";
	lsockaddr saddr( path );


	// prepare the socket
	try {
		ssb.open( sockstreambuf::pf_local, sockstreambuf::sock_stream, sockstreambuf::proto_unspec );
	} catch( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
		return;
	}

	// bind to address
	try {
		ssb.bind( &saddr );
	} catch ( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
	}

	// listen
	CPPUNIT_ASSERT_NO_THROW( ssb.listen() );


	// close socket
	ssb.close();

	// unlink
	if ( unlink( path ) !=0 ) {
		CPPUNIT_FAIL( std::string( "failed to unlink socket: " ).append( path ) );
	}

}

