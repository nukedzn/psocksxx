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

#include "lecho.h"

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <cstring>
#include <cstdlib>
#include <signal.h>


lecho::lecho( const char * path ) :
		_sockfd( -1 ), _lsock_path( path ) {

	// fork
	_cpid = fork();

	if ( _cpid == -1 ) {
		std::cerr << "failed to fork out child process" << std::endl;
	} else if ( _cpid == 0 ) {

		// child - initialise echo server on a local socket
		init_listener();

		// serve requests
		serve_requests();

		// exit - should never get here
		exit( 0 );

	} else {
		// parent - wait for the child to create the socket and return
		wait_connect();
	}

}


lecho::~lecho() {

	// cleanup
	shutdown();

}


void lecho::init_listener() {

	// initialise socket
	if ( ( _sockfd = socket( PF_LOCAL, SOCK_STREAM, 0 ) ) < 0 ) {
		std::cerr << "failed to setup local socket" << std::endl;
		exit( -1 );
	}

	// socket address
	sockaddr_un saddr;

	bzero( (void *) &saddr, sizeof( saddr ) );
	saddr.sun_family = AF_LOCAL;
	strcpy( saddr.sun_path, _lsock_path );


	// bind
	if ( bind( _sockfd, (::sockaddr *) &saddr,
			sizeof( sockaddr_un ) ) != 0 ) {
		std::cerr << "failed to bind to local socket" << std::endl;
		exit( -1 );
	}


	// listen
	if ( listen( _sockfd, 2 ) != 0 ) {
		std::cerr << "failed to listen on local socket" << std::endl;
		exit( -1 );
	}

}


void lecho::serve_requests() {

	int peer_sockfd;
	sockaddr_un peer_addr;
	socklen_t   addrlen = sizeof( peer_addr );

	int n = 0;
	char cbuffer[64];
	bool close_peer;

	for (;;) {

		if ( ( peer_sockfd = accept( _sockfd, (sockaddr *) &peer_addr, &addrlen ) ) == -1 ) {
			continue;
		}

		close_peer = false;
		do {

			// read from the socket
			n = recv( peer_sockfd, cbuffer, sizeof( cbuffer ), 0 );

			// sanity check - did we receive anything?
			if ( n <= 0 ) {
				close_peer = true;
			} else {

				// send back what we received
				if ( send( peer_sockfd, cbuffer, n, 0 ) < 0 ) {
					close_peer = true;
				}

			}

		} while (! close_peer );

		// close peer
		close( peer_sockfd );

	}

}


void lecho::shutdown() {

	if ( _cpid == 0 ) {
		// child - should never get here
	} else {

		// parent - send kill to child
		kill( _cpid, SIGTERM );

	}

	// unlink
	unlink( _lsock_path );

}


void lecho::wait_connect() {

	int sockfd = -1;
	unsigned int max_tries = 10;
	sockaddr_un saddr;

	// initialise socket
	if ( ( sockfd = socket( PF_LOCAL, SOCK_STREAM, 0 ) ) < 0 ) {
		std::cerr << "failed to setup local socket" << std::endl;
		exit( -1 );
	}

	// socket address structure
	bzero( (void *) &saddr, sizeof( saddr ) );
	saddr.sun_family = AF_LOCAL;
	strcpy( saddr.sun_path, _lsock_path );

	// loop until we can establish a connection or
	// we exhaust our attempts
	for ( int i = 0; i < max_tries; i++ ) {

		// try to connect
		if ( ( connect( sockfd, (sockaddr *) &saddr, sizeof( sockaddr_un ) ) == -1 ) ) {

			// connect failed - sleep for a bit
			usleep( 500 );

		} else {
			// connect successful - break out of the loop
			break;
		}

	}

	// close socket
	close( sockfd );

}

