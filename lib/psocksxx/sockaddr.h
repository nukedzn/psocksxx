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
	*   This abstract class acts as an interface for accessing derived
	*   socket address structures.
	*
	*/
	class sockaddr {
	public:

		/** socket address types definition */
		enum address_t {
			af_unspec   = AF_UNSPEC,    /*! unspecified */
			af_local    = AF_LOCAL,     /*! local addresses */
			af_inet     = AF_INET       /*! network addresses */
		};


		/**
		*   @brief destructor
		*/
		virtual ~sockaddr() { };

		/**
		*   @brief get POSIX socket address size
		*   @return POSIX address size
		*
		*   Helper function to get the size of the related POSIX socket
		*   address.
		*
		*/
		virtual socklen_t size() const throw() =0;

		/**
		*   @brief get a POSIX socket address structure
		*   @return POSIX socket address structure
		*
		*   Helper function to get a pointer to the POSIX socket
		*   address structure relating to this socket address instance.
		*
		*/
		virtual ::sockaddr * psockaddr() const throw() =0;

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_SOCKADDR_H */

