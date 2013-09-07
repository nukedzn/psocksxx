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


	nsockstream::~nsockstream() throw() {

		// cleanup
		delete iosockstream::rdbuf();

	}

} /* end of namespace psocksxx */

