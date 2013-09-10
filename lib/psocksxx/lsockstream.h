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

#ifndef PSOCKSXX_LSOCKSTREAM_H
#define PSOCKSXX_LSOCKSTREAM_H

#include <psocksxx/iosockstream.h>
#include <psocksxx/lsockaddr.h>


namespace psocksxx {

	/**
	*   @brief Local (unix) socket controller class
	*
	*   This class acts as a controller for communicating through a
	*   local (unix) socket and uses an instance of psocksxx::sockstreambuf
	*   as the underlying / associated sequence.
	*/
	class lsockstream : public iosockstream {
	public:

		/**
		*   @brief constructor
		*   @throw psocksxx::sockexception socket exception
		*
		*   Initialise a local (unix) communication stream.
		*
		*/
		lsockstream() throw( sockexception );

		/**
		*   @brief destructor
		*/
		~lsockstream() throw();

		/**
		*   @brief connect to a local socket
		*   @param path local socket path
		*   @throw psocksxx::sockexception socket exception
		*   @throw psocksxx::socktimeoutexception connection timeout
		*          exception
		*
		*   Connect a to local socket at the given path. It is assumed
		*   that the socket is ready to accept connections.
		*
		*/
		void connect( const char * path ) throw( sockexception, socktimeoutexception );

		/**
		*   @brief connect to a local socket
		*   @param saddr local socket address instance
		*   @throw psocksxx::sockexception socket exception
		*   @throw psocksxx::socktimeoutexception connection timeout
		*          exception
		*
		*   Connect to a local socket using the passed in socket address
		*   object.
		*
		*/
		void connect( const lsockaddr * saddr ) throw( sockexception, socktimeoutexception );

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_LSOCKSTREAM_H */

