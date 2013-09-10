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

#ifndef PSOCKSXX_NSOCKADDR_H
#define PSOCKSXX_NSOCKADDR_H

#include <psocksxx/sockaddr.h>
#include <psocksxx/sockexception.h>
#include <netinet/in.h>


namespace psocksxx {

	/**
	*   @brief Socket address class for IPv4 addresses
	*
	*   This class holds the socket addressing structure for IPv4
	*   socket communications.
	*
	*/
	class nsockaddr : public sockaddr, public sockaddr_in {
	public:

		/**
		*   @brief constructor
		*   @param node node (host name or IP)
		*   @param port port number
		*   @throw psocksxx::sockexception socket exception
		*
		*   Create a IPv4 socket address instance with the give node
		*   and port information.
		*
		*/
		nsockaddr( const char * node, unsigned short port ) throw( sockexception );

		/**
		*   @brief constructor
		*   @param port port number
		*
		*   Create a IPv4 socket address instance with the given port
		*   and the node (host/IP) will be any available interface on
		*   the host computer.
		*
		*/
		nsockaddr( unsigned short port ) throw();

		/**
		*   @brief constructor
		*   @param node node (host name or IP)
		*   @param service port number of the service name (e.g. "http")
		*   @throw psocksxx::sockexception socket exception
		*
		*   Create a IPv4 socket address instance with the give node
		*   and service information.
		*
		*/
		nsockaddr( const char * node, const char * service ) throw( sockexception );

		// abstract method implementations
		socklen_t size() const throw();
		::sockaddr* psockaddr() const throw();


	protected:

		/**
		*   @brief convert a node name to a IPv4 address
		*   @param node node (host name or IP)
		*   @throw psocksxx::sockexception socket exception
		*   @return IPv4 address in network byte order
		*
		*   Helper function to convert a node name into a IPv4 network
		*   address.
		*
		*/
		in_addr_t resolve_node( const char * node ) throw( sockexception );

	};

} /* end of namespace psockxx */

#endif /* !PSOCKSXX_NSOCKADDR_H */

