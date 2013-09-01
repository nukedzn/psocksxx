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
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( sockstreambuf_test );

// use namespace psocksxx
using namespace psocksxx;


sockstreambuf_test::sockstreambuf_test() :
	_local_sock( -1 ) {

}


void sockstreambuf_test::setup_local_listener() throw() {

	// initialise socket
	if ( ( _local_sock = socket( PF_LOCAL, SOCK_STREAM, 0 ) ) < 0 ) {
		std::cerr << "failed to setup local socket" << std::endl;
		return;
	}

	// socket address
	const char * path = LOCAL_LISTENER_SOCK_PATH;
	sockaddr_un saddr;

	bzero( (void *) &saddr, sizeof( saddr ) );
	saddr.sun_family = AF_LOCAL;
	strcpy( saddr.sun_path, path );


	// bind
	if ( bind( _local_sock, (::sockaddr *) &saddr,
			sizeof( sockaddr_un ) ) != 0 ) {
		std::cerr << "failed to bind to local socket" << std::endl;
		return;
	}


	// listen
	if ( listen( _local_sock, 2 ) != 0 ) {
		std::cerr << "failed to listen on local socket" << std::endl;
		return;
	}

}


void sockstreambuf_test::connect_local() throw() {

	int csock;
	sockaddr_un saddr;

	const char * path = LOCAL_SOCK_PATH;
	bzero( (void *) &saddr, sizeof( saddr ) );
	saddr.sun_family = AF_LOCAL;
	strcpy( saddr.sun_path, path );

	// not worth having error handling here so we hope for the best
	csock = socket( AF_LOCAL, SOCK_STREAM, 0 );
	connect( csock, (::sockaddr *) &saddr, sizeof( sockaddr_un ) );

}


void sockstreambuf_test::setUp() {

	// initialise locals
	_sockaddr.sa_family = AF_LOCAL;

	// setup communication sockets
	setup_local_listener();

}


void sockstreambuf_test::tearDown() {

	// close opened sockets
	close( _local_sock );
	unlink( LOCAL_LISTENER_SOCK_PATH );

}


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


void sockstreambuf_test::test_bad_flush() {

	// socket stream buffer
	sockstreambuf ssb( -1 );

	// add a char into the buffer
	ssb.sputc( 'c' );

	// flush buffer
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

	// socket stream buffer
	sockstreambuf ssb;

	// local (unix) socket address
	const char * path = LOCAL_SOCK_PATH;
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

	// socket stream buffer
	sockstreambuf ssb;

	// local (unix) socket address
	const char * path = LOCAL_SOCK_PATH;
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


void sockstreambuf_test::test_local_connect() {

	// socket steam buffer
	sockstreambuf ssb;

	// local (unix) socket address
	const char * path = LOCAL_LISTENER_SOCK_PATH;
	lsockaddr saddr( path );

	// prepare the socket
	try {
		ssb.open( sockstreambuf::pf_local, sockstreambuf::sock_stream, sockstreambuf::proto_unspec );
	} catch( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
		return;
	}

	// connect
	CPPUNIT_ASSERT_NO_THROW( ssb.connect( &saddr ) );

	// close socket
	ssb.close();

}


void sockstreambuf_test::test_local_accept() {

	// fork variables
	pid_t  cpid, wpid;
	int    wpid_status;

	// socket stream buffer
	sockstreambuf ssb;

	// local (unix) socket address
	const char * path = LOCAL_SOCK_PATH;
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
	try {
		ssb.listen();
	} catch ( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
	}


	// fork
	cpid = fork();

	if ( cpid == -1 ) {
		CPPUNIT_FAIL( "failed to fork" );
	} else if ( cpid == 0 ) {

		// child - connect to the local socket created by the parent
		connect_local();

		// exit
		exit( 0 );

	} else {

		// parent - accept a connection from the child
		CPPUNIT_ASSERT( ssb.accept() != -1 );

		// wait for child to exit
		if ( ( wpid = waitpid( cpid, &wpid_status, 0 ) ) == -1 ) {
			CPPUNIT_FAIL( "failed waiting for the child process to terminate" );
		}

	}

	// close socket
	ssb.close();

	// unlink
	if ( unlink( path ) !=0 ) {
		CPPUNIT_FAIL( std::string( "failed to unlink socket: " ).append( path ) );
	}

}


void sockstreambuf_test::test_local_flush() {

	// fork variables
	pid_t  cpid, wpid;
	int    wpid_status;

	// socket stream buffers
	sockstreambuf ssb;
	sockstreambuf * peer_ssb;

	// local (unix) socket address
	const char * path = LOCAL_SOCK_PATH;
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
	try {
		ssb.listen();
	} catch ( sockexception &e ) {
		CPPUNIT_FAIL( e.what() );
	}


	// fork
	cpid = fork();

	if ( cpid == -1 ) {
		CPPUNIT_FAIL( "failed to fork" );
	} else if ( cpid == 0 ) {

		// child - connect to the local socket created by the parent
		connect_local();

		// exit
		exit( 0 );

	} else {

		// parent - accept a connection from the child
		peer_ssb = new sockstreambuf( ssb.accept() );

		// put a char into the buffer and flush
		peer_ssb->sputc( 'c' );
		CPPUNIT_ASSERT( 1 == peer_ssb->flush() );

		// cleanup
		delete peer_ssb;

		// wait for child to exit
		if ( ( wpid = waitpid( cpid, &wpid_status, 0 ) ) == -1 ) {
			CPPUNIT_FAIL( "failed waiting for the child process to terminate" );
		}

	}

	// close socket
	ssb.close();

	// unlink
	if ( unlink( path ) !=0 ) {
		CPPUNIT_FAIL( std::string( "failed to unlink socket: " ).append( path ) );
	}

}

