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

#include "necho.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <netdb.h>


necho::necho( const char * node, const char * service, int socket_type ) :
		_sockfd( -1 ), _nsock_node( node ), _nsock_service( service ),
		_socket_type( socket_type ) {

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


necho::~necho() {

	// cleanup
	shutdown();

}


void necho::init_listener() {

	addrinfo hints, * saddr_info;
	int status = 0;

	// setup hints
	memset( &hints, 0, sizeof ( hints ) );
	hints.ai_family   = AF_INET;
	hints.ai_socktype = _socket_type;

	if ( ( status = getaddrinfo( _nsock_node, _nsock_service, &hints, &saddr_info ) ) != 0 ) {
		std::cerr << "getaddrinfo: " << gai_strerror( status ) << std::endl;
		exit( -1 );
	}

	// initialise socket
	if ( ( _sockfd = socket( saddr_info->ai_family, saddr_info->ai_socktype, saddr_info->ai_protocol ) ) < 0 ) {
		std::cerr << "failed to setup network socket" << std::endl;
		exit( -1 );
	}

	// set SO_REUSEADDR to true so we can reuse the socket
	int optval = 1;
	setsockopt( _sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof( optval ) );

	// bind
	if ( bind( _sockfd, saddr_info->ai_addr, saddr_info->ai_addrlen ) != 0 ) {
		std::cerr << "failed to bind to network socket" << std::endl;
		exit( -1 );
	}


	// listen
	if ( listen( _sockfd, 5 ) != 0 ) {
		std::cerr << "failed to listen on network socket" << std::endl;
		exit( -1 );
	}

	// cleanup
	freeaddrinfo ( saddr_info );

}


void necho::serve_requests() {

	int peer_sockfd;

	int n = 0;
	char cbuffer[64];
	bool close_peer;

	for (;;) {

		if ( ( peer_sockfd = accept( _sockfd, NULL, 0 ) ) == -1 ) {
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


void necho::wait_connect() {

	int sockfd = -1;
	int status = 0;
	unsigned int max_tries = 10;
	addrinfo hints, * saddr_info;

	// setup hints
	memset( &hints, 0, sizeof ( hints ) );
	hints.ai_family   = AF_INET;
	hints.ai_socktype = _socket_type;

	if ( ( status = getaddrinfo( _nsock_node, _nsock_service, &hints, &saddr_info ) ) != 0 ) {
		std::cerr << "getaddrinfo: " << gai_strerror( status ) << std::endl;
		exit( -1 );
	}

	// loop until we can establish a connection or
	// we exhaust our attempts
	for ( int i = 0; i < max_tries; i++ ) {

		// try to connect
		if ( ( connect( sockfd, saddr_info->ai_addr, saddr_info->ai_addrlen ) == -1 ) ) {

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


void necho::shutdown() {

	if ( _cpid == 0 ) {
		// child - should never get here
	} else {

		// parent - send kill to child
		kill( _cpid, SIGTERM );

	}

}

