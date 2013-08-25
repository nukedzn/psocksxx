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

#ifndef PSOCKSXX_SOCKADDR_H
#define PSOCKSXX_SOCKADDR_H

#include <sys/socket.h>


namespace psocksxx {

	/**
	*   @brief Socket address base class
	*
	*   This class holds the socket addressing structure for socket
	*   communications.
	*
	*/
	class sockaddr : public ::sockaddr {
	public:
		virtual ~sockaddr();

		/**
		*   @brief get socket address size
		*   @return address size
		*
		*   Helper function to get the size of the socket address.
		*
		*/
		virtual socklen_t size() const =0;

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_SOCKADDR_H */

