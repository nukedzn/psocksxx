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

#include "sockstreambuf.h"

#include <unistd.h>


namespace psocksxx {

	sockstreambuf::sockstreambuf() throw() : _socket(-1) {

	}


	sockstreambuf::sockstreambuf( socket_t socket ) throw() {
		_socket = socket;
	}


	sockstreambuf::~sockstreambuf() {

		// close any open sockets
		close();

	}


	void sockstreambuf::open( socket_domain_t domain, socket_type_t type, socket_protocol_t proto ) throw( sockexception ) {

		// create a communication endpoint
		_socket = ::socket( domain, type, proto );

		// sanity check
		if ( _socket == -1 ) {
			throw sockexception();
		}

	}


	void sockstreambuf::close() throw() {

		// sanity check
		if ( _socket > -1 ) {

			// close the socket
			::close( _socket );

		}

	}

} /* end of namespace psocksxx */

