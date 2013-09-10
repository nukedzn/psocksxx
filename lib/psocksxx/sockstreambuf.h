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

#include <psocksxx/sockexception.h>
#include <psocksxx/sockaddr.h>

#include <streambuf>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>

#ifndef SOCKSTREAMBUF_SIZE
#define SOCKSTREAMBUF_SIZE 1024
#endif

#ifndef SOCKSTREAMBUF_PUTBACK_SIZE
#define SOCKSTREAMBUF_PUTBACK_SIZE 8
#endif


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

		/** socket end-of-file type */
		enum eof_t {
			eof = EOF       /*!< end of file */
		};

		/** socket domains type definition */
		enum socket_domain_t {
			pf_local   = PF_LOCAL,        /*!< Host-internal protocols */
			pf_inet    = PF_INET,         /*!< Internet version 4 protocols */
			pf_route   = PF_ROUTE,        /*!< Internal Routing protocol */
			pf_key     = PF_KEY,          /*!< Internal key-management function */
			pf_inet6   = PF_INET6         /*!< Internet version 6 protocols */
		};

		/** socket types type definition */
		enum socket_type_t {
			sock_stream     = SOCK_STREAM,
			sock_dgram      = SOCK_DGRAM,
			sock_raw        = SOCK_RAW,
			sock_rdm        = SOCK_RDM,
			sock_seqpacket  = SOCK_SEQPACKET
		};

		/** socket protocols type definition */
		enum socket_protocol_t {
			proto_unspec    = 0,               /*!< Unspecified system default */
			ipproto_ip      = IPPROTO_IP,      /*!< Internet protocol */
			ipproto_ipv6    = IPPROTO_IPV6,    /*!< Internet Protocol Version 6 */
			ipproto_icmp    = IPPROTO_ICMP,    /*!< Control message protocol */
			ipproto_raw     = IPPROTO_RAW,     /*!< Raw IP Packets Protocol */
			ipproto_tcp     = IPPROTO_TCP,     /*!< Transmission control protocol */
			ipproto_udp     = IPPROTO_UDP      /*!< User datagram protocol */
		};


		sockstreambuf() throw();          //!< constructor
		virtual ~sockstreambuf();         //!< destructor

		/**
		*   @brief overloaded constructor
		*   @param socket socket data
		*
		*   Create an instance with the passed in sockstreambuf::socket_t
		*   type socket. It is assumed that the socket is initialised and
		*   ready to use.
		*
		*/
		sockstreambuf( socket_t socket ) throw();

		/**
		*   @brief get internal socket data
		*   @return socket data
		*
		*   Returns a read-only reference to the internal POSIX socket
		*   data.
		*
		*/
		const socket_t & socket() const throw();

		/**
		*   @brief open a socket
		*   @param domain communications domain for the socket
		*   @param type socket communications type
		*   @param proto socket communications protocol
		*   @throw psocksxx::sockexception socket exception
		*
		*   Open a socket and initialise socket communications.
		*
		*/
		void open( socket_domain_t domain, socket_type_t type, socket_protocol_t proto = proto_unspec ) throw( sockexception );

		/**
		*   @brief close open sockets
		*
		*   Close any open socket connections used by this buffer. This
		*   will also flush any data in the buffer before closing.
		*
		*/
		void close() throw();

		/**
		*   @brief flush the socket output buffer
		*   @return number of characters flushed
		*
		*   Flush the socket buffer by writing date into the
		*   socket and returns the number of characters flushed.
		*   If the output buffer is empty sockstreambuf::eof is returned.
		*
		*/
		virtual int flush() throw();


		/**
		*   @brief initiate a connection on a socket
		*   @param dest_addr destination address to connect to
		*   @param timeout connection timeout value in seconds
		*   @throw psocksxx::sockexception socket exception
		*
		*   Initiate a connection on a socket previously opened using
		*   open() method. If the timeout value is 0 (default) then
		*   the timeouts are ignored.
		*
		*/
		void connect( const sockaddr * dest_addr, unsigned int timeout = 0 ) throw( sockexception );

		/**
		*   @brief initiate a connection on a socket
		*   @param dest_addr destination address to connect to
		*   @param timeout connection timeout value as a reference to a
		*          @c timeval structure
		*
		*   @throw psocksxx::sockexception socket exception
		*
		*   Initiate a connection on a socket previously opened using
		*   open() method.
		*
		*/
		void connect( const sockaddr * dest_addr, timeval * timeout ) throw( sockexception );

		/**
		*   @brief bind the socket to a specified address
		*   @param bind_addr address to bind to
		*   @throw psocksxx::sockexception socket exception
		*
		*   After a socket is configured using open() this method can
		*   be used to assign an address to it.
		*
		*/
		void bind( const sockaddr * bind_addr ) throw( sockexception );

		/**
		*   @brief make the socket passive and capable of accepting connections
		*   @param backlog maximum length of the queue for pending connections
		*                  and defaults to SOMAXCONN (128) defined in @c <sys/socket.h>
		*
		*   @throw psocksxx::sockexception socket exception
		*
		*   This method will make the currently opened socket connection
		*   to passive and capable of accepting client connections using accept()
		*   method.
		*
		*/
		void listen( int backlog = SOMAXCONN ) throw( sockexception );

		/**
		*   @brief accept a connection on a listening (passive) socket
		*   @throw psocksxx::sockexception socket exception
		*   @return peer socket data structure
		*
		*   This method will accept incoming connections on a socket
		*   set to be passive using the listen() method. Upon success
		*   this will return the peer socket data structure that can be used
		*   to create a socket stream buffer instance to communicate
		*   with the accepted socket connection.
		*
		*/
		socket_t accept() throw( sockexception );


	protected:

		/**
		*   @brief initialise internal buffers
		*/
		void init_buffers() throw();

		/**
		*   @brief cleanup internal buffers
		*/
		void cleanup_buffers() throw();

		/**
		*   @brief sync data with the socket
		*   @return 0 or -1 to denote success or failure
		*
		*   Synchronise the buffer with the associated socket
		*   by flushing data from the buffer to the socket.
		*
		*/
		virtual int sync() throw();

		/**
		*   @brief consumes the buffer by writing the contents to
		*          the socket
		*
		*   @param c additional character to consume
		*   @return sockstreambuf::eof to indicate failure or @a c
		*           if successful.
		*
		*   Consumes the buffer contents and writes to the opened socket.
		*   If @a c is not sockstreambuf::eof then @a c is also written
		*   out.
		*
		*/
		virtual int overflow( int c = eof ) throw();

		/**
		*   @brief read more data into the buffer from the socket
		*   @return the first character from the buffer or sockstreambuf::eof
		*           if no data is available to read
		*
		*   This reads more data into the buffer from the socket when
		*   the input buffer is empty and returns the next readable
		*   character from the buffer. If the buffer is empty and no
		*   data is available through the socket, this returns sockstreambuf::eof.
		*
		*/
		virtual int underflow() throw();

		/**
		*   @brief check for the read/write availability on the socket
		*   @param timeout timeout value reference to a @c timeval structure
		*   @param chk_read check for read availability
		*   @param chk_write check for write availability
		*   @return boolean @c true to denote availability or @c false
		*           if none of the checked actions are available.
		*
		*   This will check the socket for read and/or write availability.
		*
		*/
		bool ready( timeval * timeout, bool chk_read = true, bool chk_write = true ) throw( sockexception );


	private:

		/** POSIX socket data */
		socket_t _socket;

		size_t _bufsize;
		size_t _putbacksize;

		timeval * _timeout;


		void init_defaults() throw();

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_SOCKSTREAMBUF_H */

