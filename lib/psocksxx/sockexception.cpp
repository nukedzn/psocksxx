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

#include "sockexception.h"

#include <cerrno>
#include <cstring>


namespace psocksxx {

	sockexception::sockexception( const char * message ) throw() {

		// copy system error
		_errno   = errno;
		_sys_msg = strerror( _errno );

		// sanity check
		if ( message == NULL ) {

			// use system error message if no user message is passed in
			_message = _sys_msg;

		} else {

			// use the user message
			_message = message;

		}

	}


	sockexception::~sockexception() throw() {

	}


	const char * sockexception::what() const throw() {
		return _message.c_str();
	}

} /* end of namespace psocksxx */

