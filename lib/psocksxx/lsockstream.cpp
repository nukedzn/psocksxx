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

#include "lsockstream.h"


namespace psocksxx {

	lsockstream::lsockstream() throw( sockexception ) : iosockstream( 0 ) {

		// socket stream buffer instance
		sockstreambuf * ssb = new sockstreambuf();

		// open local socket
		ssb->open( sockstreambuf::pf_local, sockstreambuf::sock_stream, sockstreambuf::proto_unspec );

		// update I/O buffer
		iosockstream::init( ssb );

	}


	lsockstream::~lsockstream() throw() {

		// cleanup
		delete iosockstream::rdbuf();

	}


	void lsockstream::connect( const char * path ) throw( sockexception, socktimeoutexception ) {

		lsockaddr saddr( path );
		sockstreambuf * ssb = (sockstreambuf *) rdbuf();

		ssb->connect( &saddr );

	}


	void lsockstream::connect( const lsockaddr * saddr ) throw( sockexception, socktimeoutexception ) {

		sockstreambuf * ssb = (sockstreambuf *) rdbuf();
		ssb->connect( saddr );

	}

} /* end of namespace psocksxx */

