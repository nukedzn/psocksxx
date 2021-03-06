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

#ifndef PSOCKSXX_LSOCKADDR_H
#define PSOCKSXX_LSOCKADDR_H

#include <psocksxx/sockaddr.h>
#include <sys/un.h>


namespace psocksxx {

	/**
	*   @brief Socket address class for local sockets
	*
	*   This class holds the socket addressing structure for local
	*   (unix) socket communications.
	*
	*/
	class lsockaddr : public sockaddr, public sockaddr_un {
	public:

		/**
		*   @brief constructor
		*   @param path local socket address file path
		*
		*   Create a local socket address instance with the given file
		*   path as the socket address.
		*
		*/
		lsockaddr( const char * path ) throw();

		// abstract method implementations
		socklen_t size() const throw();
		::sockaddr* psockaddr() const throw();

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_LSOCKADDR_H */

