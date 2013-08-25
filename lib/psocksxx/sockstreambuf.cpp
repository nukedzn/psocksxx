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


namespace psocksxx {

	sockstreambuf::sockstreambuf() throw() : _socket( -1 ) {

		// initialise internal buffers
		init_buffers();

	}


	sockstreambuf::sockstreambuf( socket_t socket ) throw() {

		// update local copy of the socket data
		_socket = socket;

		// initialise internal buffers
		init_buffers();

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

			// sync
			sync();

			// close the socket
			::close( _socket );

			// update socket data
			_socket = -1;

		}

	}


	void sockstreambuf::connect( const sockaddr * dest_addr ) throw( sockexception ) {

		if ( ::connect( _socket, (::sockaddr *) dest_addr, dest_addr->size() ) != 0 ) {
			throw sockexception();
		}

	}


	const sockstreambuf::socket_t & sockstreambuf::socket() const throw() {
		return _socket;
	}


	void sockstreambuf::init_buffers() throw() {

		// setup output buffer
		setp( _pbuf, _pbuf + ( SOCKSTREAMBUF_SIZE - 1 ) );

	}


	int sockstreambuf::flush() throw() {

		int flush_size = pptr() - pbase();

		// sanity check
		if ( flush_size > 0 ) {

			// FIXME: timeouts? check whether socket is connected?
			// FIXME: error handling?
			if ( ::send( _socket, _pbuf, flush_size, 0 ) == flush_size ) {
				pbump( -flush_size );
				return flush_size;
			}

		}

		return eof;

	}


	int sockstreambuf::sync() throw() {

		// flush buffer
		if ( flush() == eof ) {
			return -1;
		}

		return 0;

	}


	int sockstreambuf::overflow( int c ) throw() {

		// sanity check
		if ( c != eof ) {

			// insert the overflowed char into the buffer
			*pptr() = c;
			pbump( 1 );

		}

		// flush the buffer
		if ( flush() == eof ) {
			return eof;
		}

		return c;

	}

} /* end of namespace psocksxx */

