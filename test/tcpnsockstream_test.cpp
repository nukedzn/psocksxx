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
#include <sys/wait.h>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( tcpnsockstream_test );

// use namespace psocksxx
using namespace psocksxx;


void tcpnsockstream_test::connect_naddr( nsockaddr * naddr ) throw() {

	int csock;

	// not worth having error handling here so we hope for the best
	csock = socket( AF_INET, SOCK_STREAM, 0 );
	connect( csock, naddr->psockaddr(), naddr->size() );

}


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
	necho n( NSOCK_NODE, NSOCK_SERVICE_2 );

	// connect
	CPPUNIT_ASSERT_NO_THROW( ss.connect( NSOCK_NODE, atoi( NSOCK_SERVICE_2 ) ) );

}


void tcpnsockstream_test::test_bind_addr() {

	// tcp socket stream
	tcpnsockstream ss;

	// network address to bind to
	nsockaddr naddr( NSOCK_NODE, NSOCK_BIND_SERVICE );

	// bind
	CPPUNIT_ASSERT_NO_THROW( ss.bind( &naddr, true ) );

}


void tcpnsockstream_test::test_listen_addr() {

	// tcp socket stream
	tcpnsockstream ss;

	// network address to bind to
	nsockaddr naddr( NSOCK_NODE, NSOCK_BIND_SERVICE );

	// bind
	try {
		ss.bind( &naddr, true );
	} catch( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
		return;
	}

	// listen
	CPPUNIT_ASSERT_NO_THROW( ss.listen( 1 ) );

}


void tcpnsockstream_test::test_accept_addr() {

	// fork variables
	pid_t cpid, wpid;
	int   wpid_status;

	// tcp socket stream
	tcpnsockstream ss;

	// network socket pointer
	nsockstream * nsock = 0;

	// network address to bind to
	nsockaddr naddr( NSOCK_NODE, NSOCK_BIND_SERVICE );

	// bind
	try {
		ss.bind( &naddr, true );
	} catch( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
		return;
	}

	// listen
	try {
		ss.listen( 1 );
	} catch( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
		return;
	}


	// fork
	cpid = fork();

	if ( cpid == -1 ) {
		CPPUNIT_FAIL( "failed to fork" );
	} else if ( cpid == 0 ) {

		// child - connect to the network socket created by the parent
		connect_naddr( &naddr );

		// exit
		exit( 0 );

	} else {

		// parent - accept a connection from the child
		CPPUNIT_ASSERT_NO_THROW( nsock = ss.accept() );
		CPPUNIT_ASSERT( nsock != 0 );

		// cleanup
		if ( nsock != 0 ) {
			delete nsock;
		}

		// wait for child to exit
		if ( ( wpid = waitpid( cpid, &wpid_status, 0 ) ) == -1 ) {
			CPPUNIT_FAIL( "failed waiting for the child process to terminate" );
		}

	}

}


void tcpnsockstream_test::test_bind_addr_fail() {

	// tcp socket stream
	tcpnsockstream ss;

	// network address to bind to
	nsockaddr naddr( NSOCK_NODE, NSOCK_BIND_SERVICE );

	// bind - this should fail with address already in use error
	// because of test_accept_addr()
	CPPUNIT_ASSERT_THROW( ss.bind( &naddr ), sockexception );

}


void tcpnsockstream_test::test_io_addr() {

	// tcp socket stream
	tcpnsockstream ss;

	// network echo server
	necho n( NSOCK_NODE, NSOCK_SERVICE );

	// network address to connect to
	nsockaddr saddr( NSOCK_NODE, NSOCK_SERVICE );

	// connect
	try {
		ss.connect( &saddr );
	} catch ( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
		return;
	}

	// write
	ss << 'c' << std::endl;

	// read
	char c;
	ss >> c;

	// assert
	CPPUNIT_ASSERT( c == 'c' );

}

