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

#include "nsockstream_test.h"

#include <psocksxx/nsockstream.h>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( nsockstream_test );

// use namespace psocksxx
using namespace psocksxx;


void nsockstream_test::test_constructor_tcp() {

	// TCP/IP
	CPPUNIT_ASSERT_NO_THROW( nsockstream n( sockstreambuf::sock_stream, sockstreambuf::ipproto_tcp ) );

}


void nsockstream_test::test_constructor_udp() {

	// UDP
	CPPUNIT_ASSERT_NO_THROW( nsockstream n( sockstreambuf::sock_dgram, sockstreambuf::ipproto_udp ) );

}


void nsockstream_test::test_constructor_streambuf() {

	// socket stream buffer
	sockstreambuf * ssb = new sockstreambuf();

	// network socket stream
	nsockstream ss( ssb );

	// assert
	CPPUNIT_ASSERT( ssb == ss.rdbuf() );

}


void nsockstream_test::test_set_timeout() {

	// socket stream buffer
	sockstreambuf * ssb = new sockstreambuf();

	// network socket stream
	nsockstream ss( ssb );

	time_t sec = 1;
	suseconds_t usec = 500;

	// set timeout
	const timeval * t = ss.timeout( sec, usec );

	// validate
	CPPUNIT_ASSERT( sec == t->tv_sec );
	CPPUNIT_ASSERT( usec == t->tv_usec );

}


void nsockstream_test::test_clear_timeout() {

	// socket stream buffer
	sockstreambuf * ssb = new sockstreambuf();

	// network socket stream
	nsockstream ss( ssb );

	// clear the timeout before a timeout is set
	CPPUNIT_ASSERT( 0 == ss.clear_timeout() );


	time_t sec = 1;
	suseconds_t usec = 500;

	// set timeout
	const timeval * t = ss.timeout( sec, usec );

	// clear the timeout after a timeout is set
	CPPUNIT_ASSERT( 0 == ss.clear_timeout() );

}

