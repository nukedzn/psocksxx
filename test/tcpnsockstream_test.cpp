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

#include "tcpnsockstream_test.h"
#include "necho.h"

#include <psocksxx/tcpnsockstream.h>
#include <cstdlib>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( tcpnsockstream_test );

// use namespace psocksxx
using namespace psocksxx;


void tcpnsockstream_test::test_constructors() {

	// default constructor
	CPPUNIT_ASSERT_NO_THROW( tcpnsockstream ss );

}


void tcpnsockstream_test::test_connect_addr() {

	// tcp socket stream
	tcpnsockstream ss;

	// network echo server
	necho n( NSOCK_NODE, NSOCK_SERVICE );

	// network address to connect to
	nsockaddr saddr( NSOCK_NODE, NSOCK_SERVICE );

	// connect
	CPPUNIT_ASSERT_NO_THROW( ss.connect( &saddr ) );

}


void tcpnsockstream_test::test_connect_host_port() {

	// tcp socket stream
	tcpnsockstream ss;

	// network echo server
	necho n( NSOCK_NODE, NSOCK_SERVICE );

	// connect
	CPPUNIT_ASSERT_NO_THROW( ss.connect( NSOCK_NODE, atoi( NSOCK_SERVICE ) ) );

}

