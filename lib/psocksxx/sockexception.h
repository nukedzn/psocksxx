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

#ifndef PSOCKSXX_SOCKEXCEPTION_H
#define PSOCKSXX_SOCKEXCEPTION_H

#include <exception>
#include <cstddef>
#include <string>


namespace psocksxx {

	/**
	*   @brief Socket exception
	*
	*   This is the base class for all socket exceptions.
	*/
	class sockexception : public std::exception {
	public:
		/**
		*   @brief constructor
		*
		*   Create an instance with the passed in error message.
		*   If a message is not passed in or is equal to NULL then
		*   the system error message is used.
		*
		*   @param message (optional) user error message
		*/
		sockexception( const char * message = NULL ) throw();

		virtual ~sockexception() throw();   //!< destructor

		/**
		*   @brief Returns exception message
		*
		*   Returns a C-Style character string describing the
		*   exception.
		*
		*   @return exception message
		*   @sa sockexception() constructor
		*/
		const char * what() const throw();

	protected:
		/** user exception message */
		std::string _message;

		/** system error number */
		int _errno;

		/** system error message */
		std::string _sys_msg;

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_SOCKEXCEPTION_H */

