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

#ifndef PSOCKSXX_NSOCKSTREAM_H
#define PSOCKSXX_NSOCKSTREAM_H

#include <psocksxx/iosockstream.h>


namespace psocksxx {

	/**
	*   @brief Network (IPv4) controller class
	*
	*   This is the base class for network (IP version 4)
	*   communications streams.
	*
	*/
	class nsockstream : public iosockstream {
	public:

		/**
		*   @brief constructor
		*   @param type socket communications type
		*   @param proto socket communications protocol
		*   @throw psocksxx::sockexception socket exception
		*
		*   Open a network (IPv4) communications stream with the
		*   passed in type and protocol.
		*/
		nsockstream( sockstreambuf::socket_type_t type, sockstreambuf::socket_protocol_t proto ) throw( sockexception );

		/**
		*   @brief destructor
		*/
		virtual ~nsockstream() throw();

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_NSOCKSTEAM_H */

