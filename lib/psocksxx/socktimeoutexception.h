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

#ifndef PSOCKSXX_SOCKTIMEOUTEXCEPTION_H
#define PSOCKSXX_SOCKTIMEOUTEXCEPTION_H

#include <psocksxx/sockexception.h>

#include <sys/time.h>


namespace psocksxx {

	/**
	*   @brief Socket timeout exception
	*
	*   This acts as the socket timeout exception class.
	*
	*/
	class socktimeoutexception : public sockexception {
	public:

		/**
		*   @brief constructor
		*   @param message exception message
		*
		*   Create an timeout exception instance with the passed in exception
		*   message.
		*
		*/
		socktimeoutexception( const char * message ) throw();

		/**
		*   @brief constructor
		*   @param t_val timed-out value
		*   @param method action/method that timed-out
		*
		*   This will take the passed in timed-out value and the action
		*   to construct the exception message.
		*
		*/
		socktimeoutexception( const timeval * t_val, const char * method = 0 ) throw();

		virtual ~socktimeoutexception() throw();   //!< destructor

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_SOCKTIMEOUTEXCEPTION_H */

