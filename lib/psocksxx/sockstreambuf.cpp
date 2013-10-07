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

#include <fcntl.h>
#include <cstring>


namespace psocksxx {

	sockstreambuf::sockstreambuf() throw() :
			_socket( -1 ), _bufsize( SOCKSTREAMBUF_SIZE ),
			_putbacksize( SOCKSTREAMBUF_PUTBACK_SIZE ) {

		// initialise defaults
		init_defaults();

		// initialise internal buffers
		init_buffers();

	}


	sockstreambuf::sockstreambuf( socket_t socket ) throw() :
			_bufsize( SOCKSTREAMBUF_SIZE ),
			_putbacksize( SOCKSTREAMBUF_PUTBACK_SIZE ) {

		// update local copy of the socket data
		_socket = socket;

		// initialise defaults
		init_defaults();

		// initialise internal buffers
		init_buffers();

	}


	sockstreambuf::~sockstreambuf() {

		// close any open sockets
		close();

		// cleanup buffers
		cleanup_buffers();

		// cleanup timeout
		if ( _timeout != 0 ) {
			delete _timeout;
		}

	}


	void sockstreambuf::init_defaults() throw() {

		// timeout structure reference
		_timeout = 0;

		// timed-out status
		_timed_out = false;

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


	void sockstreambuf::connect( const sockaddr * dest_addr, unsigned int timeout ) throw( sockexception, socktimeoutexception ) {

		timeval t_val;
		timeval * t_ptr;

		// check timeout value
		if ( timeout > 0 ) {

			// setup timeval structure
			t_val.tv_sec  = timeout;
			t_val.tv_usec = 0;

			// update pointer
			t_ptr = &t_val;

		} else {

			// fall-back to class value
			t_ptr = _timeout;

		}

		// call overloaded connect()
		connect( dest_addr, t_ptr );

	}


	void sockstreambuf::connect( const sockaddr * dest_addr, timeval * timeout ) throw( sockexception, socktimeoutexception ) {

		// copy current flags
		int s_flags = fcntl( _socket, F_GETFL );

		// sanity check - affectively we ignore the fcntl() error
		if ( s_flags == -1 ) {
			s_flags = 0;
		}

		// setup timeout if needed
		if ( timeout > 0 ) {

			// make the socket non-blocking
			if ( fcntl( _socket, F_SETFL, ( s_flags | O_NONBLOCK ) ) == -1 ) {
				throw sockexception();
			}

		}

		// connect
		if ( ::connect( _socket, dest_addr->psockaddr(), dest_addr->size() ) != 0 ) {
			throw sockexception();
		}

		// check for timeout if set
		if ( timeout > 0 ) {

			if (! ready( timeout ) ) {

				// shutdown
				::shutdown( _socket, 2 );

				// throw a timeout exception
				if ( _timed_out ) {
					throw socktimeoutexception( timeout, "sockstreambuf::connect()" );
				}

			}

			// reset flags back to what they were
			fcntl( _socket, F_SETFL, s_flags );

		}

	}


	void sockstreambuf::bind( const sockaddr * bind_addr, bool reuse_addr ) throw( sockexception ) {

		// set socket options - SO_REUSEADDR
		if ( reuse_addr ) {

			int optval = 1;
			if ( setsockopt( _socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof( optval ) ) != 0 ) {
				throw sockexception();
			}

		}

		// bind
		if ( ::bind( _socket, bind_addr->psockaddr(), bind_addr->size() ) != 0 ) {
			throw sockexception();
		}

	}


	void sockstreambuf::listen( int backlog ) throw( sockexception ) {

		if ( ::listen( _socket, backlog ) != 0 ) {
			throw sockexception();
		}

	}


	sockstreambuf::socket_t sockstreambuf::accept() throw( sockexception ) {

		socket_t peer_sock;

		if ( ( peer_sock = ::accept( _socket, 0, 0 ) ) < 0 ) {
			throw sockexception();
		}

		return peer_sock;

	}


	const sockstreambuf::socket_t & sockstreambuf::socket() const throw() {
		return _socket;
	}


	const timeval * sockstreambuf::timeout( time_t sec, suseconds_t usec ) throw() {

		_timeout = new timeval;

		_timeout->tv_sec  = sec;
		_timeout->tv_usec = usec;

		return _timeout;

	}


	void * sockstreambuf::clear_timeout() throw() {

		// sanity check
		if ( _timeout != 0 ) {

			// delete structure
			delete _timeout;

			// set a null pointer
			_timeout = 0;

		}

		return _timeout;

	}


	bool sockstreambuf::timedout() const throw() {
		return _timed_out;
	}


	void sockstreambuf::init_buffers() throw() {

		// allocate output buffer space
		char * pbuf = new char[_bufsize];

		// allocate input buffer space
		char * gbuf = new char[_bufsize];

		// setup output buffer
		setp( pbuf, pbuf + ( _bufsize - 1 ) );

		// setup input buffer
		setg( gbuf, gbuf, gbuf );

	}


	void sockstreambuf::cleanup_buffers() throw() {

		// cleanup output buffer
		delete [] pbase();

		// cleanup input buffer
		delete [] eback();

	}


	int sockstreambuf::flush() throw( socktimeoutexception ) {

		int flush_size = pptr() - pbase();
		bool b_ready   = false;

		// sanity check
		if ( flush_size > 0 ) {

			try {
				b_ready = ready( _timeout, false, true );
			} catch ( sockexception &e ) {
				// couldn't select the socket
				return eof;
			}

			if ( b_ready ) {
				if ( ::send( _socket, pbase(), flush_size, 0 ) == flush_size ) {
					pbump( -flush_size );
					return flush_size;
				}
			} else {

				// timed out - throw a timeout exception
				if ( _timed_out ) {
					throw socktimeoutexception( _timeout, "sockstreambuf::flush()" );
				}

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


	int sockstreambuf::overflow( int c ) throw( socktimeoutexception ) {

		// sanity check
		if ( c != eof ) {

			// insert the overflowed char into the buffer
			*pptr() = c;
			pbump( 1 );

		}

		// flush the buffer - could throw a timeout exception
		if ( flush() == eof ) {
			return eof;
		}

		return c;

	}


	int sockstreambuf::underflow() throw( socktimeoutexception ) {

		// sanity check - read position before end-of-buffer?
		if ( gptr() < egptr() ) {
			return traits_type::to_int_type( *gptr() );
		}


		char * read_buffer;
		size_t putback_size  = gptr() - eback();
		size_t readable_size = 0;

		bool b_ready = false;
		ssize_t read_size = 0;

		// sanitise putback size
		if ( putback_size > _putbacksize ) {
			putback_size = _putbacksize;
		}

		// update read buffer position
		read_buffer = eback() + putback_size;

		// calculate read buffer size
		readable_size = _bufsize - putback_size;

		// check for availability
		try {
			b_ready = ready( _timeout, true, false );
		} catch ( sockexception &e ) {
			// couldn't select the socket
			return eof;
		}

		// read from socket
		if ( b_ready ) {
			read_size = ::read( _socket, read_buffer, readable_size );
		} else {

			// timed out - throw a timeout exception
			if ( _timed_out ) {
				throw socktimeoutexception( _timeout, "sockstreambuf::overflow()" );
			}

		}

		// sanity check
		if ( read_size <= 0 ) {
			return eof;
		}

		// update pointers
		setg( eback(), read_buffer, read_buffer + read_size );

		// return next character
		return traits_type::to_int_type( *gptr() );

	}


	bool sockstreambuf::ready( timeval * timeout, bool chk_read, bool chk_write ) throw( sockexception ) {

		// sanity check
		if ( _socket < 0 ) {
			throw sockexception( "sockstreambuf::ready(): invalid socket" );
		}


		fd_set  fds;
		fd_set * read_fds  = 0;
		fd_set * write_fds = 0;

		// set the fd_set so we only check our socket
		memset( &fds, 0, sizeof( fds ) );
		FD_SET( _socket, &fds );

		// set the actions we want to check
		if ( chk_read ) {
			read_fds = &fds;
		}

		if ( chk_write ) {
			write_fds = &fds;
		}

		// reset timed-out status
		_timed_out = false;

		// select the socket
		int s_status = ::select( ( _socket + 1 ), read_fds, write_fds, 0, timeout );

		// check status
		switch ( s_status ) {
			case 0:
				// timed-out
				_timed_out = true;
				break;

			case -1:
				throw sockexception();
				break;

			default:
				break;
		}

		// sanity check
		if ( FD_ISSET( _socket, &fds ) ) {
			return true;
		}

		return false;

	}

} /* end of namespace psocksxx */

