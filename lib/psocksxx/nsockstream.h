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
#include <psocksxx/nsockaddr.h>


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
		*   @brief constructor
		*   @param ssb initialised socket stream buffer instance
		*
		*   Initialise a network socket stream by using the passed in
		*   socket stream buffer, @c ssb, as the associated sequence
		*   which is assumed to be initialised with the correct type
		*   and protocol. The class destructor will delete the psocksxx::sockstreambuf
		*   instance pointed by @c ssb.
		*
		*/
		nsockstream( sockstreambuf * ssb ) throw();

		/**
		*   @brief destructor
		*/
		virtual ~nsockstream() throw();

		/**
		*   @brief connect to a network address
		*   @param saddr destination address information
		*
		*   Connect to a TCP/IPv4 communication end point making this
		*   stream ready for I/O.
		*
		*/
		void connect( const nsockaddr * saddr ) throw( sockexception );

		/**
		*   @brief bind the stream to a network address
		*   @param saddr address information to bind to
		*
		*   This binds the network socket stream to the specified network
		*   address.
		*
		*/
		void bind( const nsockaddr * saddr ) throw( sockexception );

		/**
		*   @brief make this stream passive and ready to accept connections
		*   @param backlog maximum length of the queue for pending connections
		*                  and if this value is 0 (default) then it assumes
		*                  system default
		*
		*   Make this network stream passive and ready to accept connections.
		*   Before calling this method the stream must be bound to a
		*   network address using the bind() method.
		*
		*/
		void listen( int backlog = 0 ) throw( sockexception );

		/**
		*   @brief accept a connection on a listening (passive) stream
		*   @return a new stream instance for the accepted connection
		*
		*   This method will accept an incoming connection on a listening
		*   stream and return a newly created stream instance that can
		*   be used to communicate with the accepted client connection.
		*   Note that the returned stream instance must be deleted by the
		*   caller.
		*
		*/
		nsockstream * accept() throw( sockexception );

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_NSOCKSTEAM_H */

