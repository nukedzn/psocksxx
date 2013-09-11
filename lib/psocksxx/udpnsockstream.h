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

#ifndef PSOCKSXX_UDPNSOCKSTREAM_H
#define PSOCKSXX_UDPNSOCKSTREAM_H

#include <psocksxx/nsockstream.h>


namespace psocksxx {

	/**
	*   @brief UDP over IPv4 controller class
	*
	*   This acts as the controller class for UDP over IPv4 communication
	*   streams.
	*
	*/
	class udpnsockstream : public nsockstream {
	public:

		/**
		*   @brief constructor
		*   @throw psocksxx::sockexception socket exception
		*
		*   Initialise a UDP communication stream over IPv4.
		*
		*/
		udpnsockstream() throw( sockexception );

		/**
		*   @brief destructor
		*/
		virtual ~udpnsockstream() throw();

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_UDPNSOCKSTREAM_H */

