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

#ifndef PSOCKSXX_SOCKSTREAMBUF_H
#define PSOCKSXX_SOCKSTREAMBUF_H

#include <streambuf>


namespace psocksxx {

	/**
	*   @brief Socket stream buffer class
	*
	*   This buffer class associates its both input and output
	*   sequences with an external POSIX socket.
	*/
	class sockstreambuf : public std::streambuf {
	public:

		/** socket data type definition */
		typedef int socket_t;


	private:

		/** POSIX socket descriptor */
		socket_t _socket;

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_SOCKSTREAMBUF_H */

