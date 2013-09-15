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

#include "nsockstream.h"


namespace psocksxx {

	nsockstream::nsockstream( sockstreambuf::socket_type_t type, sockstreambuf::socket_protocol_t proto )
		throw ( sockexception ) : iosockstream( NULL ) {

		// socket stream buffer instance
		sockstreambuf * ssb = new sockstreambuf();

		// open the socket communication
		ssb->open( sockstreambuf::pf_inet, type, proto );

		// update I/O buffer
		iosockstream::init( ssb );

	}


	nsockstream::nsockstream( sockstreambuf * ssb ) throw() : iosockstream( ssb ) {

	}


	nsockstream::~nsockstream() throw() {

		// cleanup
		delete iosockstream::rdbuf();

	}


	void nsockstream::connect( const nsockaddr * saddr ) throw( sockexception, socktimeoutexception ) {

		// socket stream buffer
		sockstreambuf * ssb = (sockstreambuf *) rdbuf();

		// connect
		ssb->connect( saddr );

	}


	void nsockstream::connect( const char * node, unsigned int port ) throw( sockexception, socktimeoutexception ) {

		// network address
		nsockaddr naddr( node, port );

		// connect
		connect( &naddr );

	}


	void nsockstream::bind( const nsockaddr * saddr, bool reuse_addr ) throw( sockexception ) {

		// socket stream buffer
		sockstreambuf * ssb = (sockstreambuf *) rdbuf();

		// bind
		ssb->bind( saddr, reuse_addr );

	}


	void nsockstream::listen( int backlog ) throw( sockexception ) {

		// socket stream buffer
		sockstreambuf * ssb = (sockstreambuf *) rdbuf();

		if ( backlog == 0 ) {
			ssb->listen();
		} else {
			ssb->listen( backlog );
		}

	}


	nsockstream * nsockstream::accept() throw( sockexception ) {

		// socket stream buffers
		sockstreambuf * ssb = (sockstreambuf *) rdbuf();
		sockstreambuf * cl_ssb;

		// accept
		sockstreambuf::socket_t cl_sock = ssb->accept();
		cl_ssb = new sockstreambuf( cl_sock );

		// return
		return new nsockstream( cl_ssb );

	}


	const timeval * nsockstream::timeout( time_t sec, suseconds_t usec ) throw() {

		// socket stream buffer
		sockstreambuf * ssb = (sockstreambuf *) rdbuf();

		return ssb->timeout( sec, usec );

	}


	void * nsockstream::clear_timeout() throw() {

		// socket stream buffer
		sockstreambuf * ssb = (sockstreambuf *) rdbuf();

		return ssb->clear_timeout();

	}

} /* end of namespace psocksxx */

