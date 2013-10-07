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

#include "socktimeoutexception.h"

#include <sstream>


namespace psocksxx {

	socktimeoutexception::socktimeoutexception( const char * message ) throw() {
		_message = message;
	}

	socktimeoutexception::socktimeoutexception( const timeval * t_val, const char * method ) throw() {

		// string stream
		std::stringstream ss;

		if ( method != 0 ) {
			ss << method << " ";
		}

		ss << "timed out (" << t_val->tv_sec << "." << t_val->tv_usec << "s)";

		// update exception message
		_message = ss.str();

	}

	socktimeoutexception::~socktimeoutexception() throw() { }

} /* end of namespace psocksxx */

