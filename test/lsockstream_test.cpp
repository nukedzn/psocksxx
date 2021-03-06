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

#include "lsockstream_test.h"
#include "lecho.h"

#include <psocksxx/lsockstream.h>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( lsockstream_test );

// use namespace psocksxx
using namespace psocksxx;


void lsockstream_test::test_constructors() {

	// default constructor
	CPPUNIT_ASSERT_NO_THROW( lsockstream l );

}


void lsockstream_test::test_connect_fail() {

	// local socket stream
	lsockstream l;

	// this should throw a file not found error
	CPPUNIT_ASSERT_THROW( l.connect( LOCAL_SOCK_PATH ), sockexception );

}


void lsockstream_test::test_connect_addr_fail() {

	// local socket stream
	lsockstream l;

	// local (unix) socket address
	lsockaddr saddr( LOCAL_SOCK_PATH );

	// this should throw a file not found error
	CPPUNIT_ASSERT_THROW( l.connect( &saddr ), sockexception );

}


void lsockstream_test::test_connect() {

	// local socket stream
	lsockstream l;

	// local echo server
	lecho echo( LOCAL_LISTENER_SOCK_PATH );

	// connect
	CPPUNIT_ASSERT_NO_THROW( l.connect( LOCAL_LISTENER_SOCK_PATH ) );

}


void lsockstream_test::test_connect_addr() {

	// local socket stream
	lsockstream l;

	// local (unix) socket address
	lsockaddr saddr( LOCAL_LISTENER_SOCK_PATH );

	// local echo server
	lecho echo( LOCAL_LISTENER_SOCK_PATH );

	// connect
	CPPUNIT_ASSERT_NO_THROW( l.connect( &saddr ) );

}


void lsockstream_test::test_read_timeout() {

	// local socket stream
	lsockstream l;

	// local (unix) socket address
	lsockaddr saddr( LOCAL_LISTENER_SOCK_PATH );

	// local echo server
	lecho echo( LOCAL_LISTENER_SOCK_PATH );

	// connect
	try {
		l.connect( &saddr );
	} catch( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
		return;
	}

	// set timeout
	l.timeout( 0, 200 );

	// read
	char c = l.get();

	// read - should timed out
	CPPUNIT_ASSERT( true == l.timedout() );

}

