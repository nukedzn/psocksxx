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

#include "nsockaddr.h"
#include "sockstreambuf.h"

#include <netdb.h>


namespace psocksxx {

	nsockaddr::nsockaddr( const char * node, unsigned short port ) throw( sockexception ) {

		// set the socket address family
		sin_family = sockaddr::af_inet;

		// set the port
		sin_port = htons( port );

		// set the address
		sin_addr.s_addr = resolve_node( node );

	}


	in_addr_t nsockaddr::resolve_node( const char * node ) throw( sockexception ) {

		int status;
		addrinfo hints;
		addrinfo * result;
		in_addr_t in_addr;

		// empty the hints structure
		memset( &hints, 0, sizeof( hints ) );

		// setup hints
		hints.ai_family   = sockaddr::af_inet;
		hints.ai_socktype = sockstreambuf::sock_stream;

		if ( ( status = ( getaddrinfo( node, NULL, &hints, &result ) ) ) != 0 ) {
			throw sockexception( gai_strerror( status ) );
		}

		// grab the address info we need
		in_addr = ( (sockaddr_in *) result->ai_addr )->sin_addr.s_addr;

		// cleanup
		freeaddrinfo( result );

		return in_addr;

	}


	socklen_t nsockaddr::size() const throw() {
		return sizeof( sockaddr_in );
	}


	::sockaddr * nsockaddr::psockaddr() const throw() {
		return (::sockaddr *) (sockaddr_in *) this;
	}

} /* end of namespace psocksxx */

