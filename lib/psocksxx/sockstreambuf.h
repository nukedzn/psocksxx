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

#include <streambuf>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#ifndef SOCKSTREAMBUF_SIZE
#define SOCKSTREAMBUF_SIZE 1024
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
			pf_inet6   = PF_INET6,        /*!< Internet version 6 protocols */
			pf_system  = PF_SYSTEM,       /*!< System domain */
			pf_ndrv    = PF_NDRV          /*!< Raw access to network device */
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
		*   @brief open a socket
		*   @param domain communications domain for the socket
		*   @param type socket communications type
		*   @param proto socket communications protocol
		*   @throw psocksxx::sockexception socket exception
		*
		*   Open a socket and initialise socket communications.
		*
		*/
		void open( socket_domain_t domain, socket_type_t type, socket_protocol_t proto ) throw( sockexception );

		/**
		*   @brief close open sockets
		*
		*   Close any open socket connections used by this buffer
		*/
		void close() throw();

	protected:

		/**
		*   @brief initialise internal buffers
		*/
		void init_buffers() throw();

		/**
		*   @brief flush the socket output buffer
		*   @return number of characters flushed
		*
		*   Flush the socket buffer by writing date into the
		*   socket and returns the number of characters flushed.
		*   If the output buffer is empty EOF (-1) is returned.
		*
		*/
		virtual int flush() throw();

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

	private:

		/** POSIX socket descriptor */
		socket_t _socket;

		/** char array to be used as output buffer */
		char _pbuf[SOCKSTREAMBUF_SIZE];

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_SOCKSTREAMBUF_H */

