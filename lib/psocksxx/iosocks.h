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

#ifndef PSOCKSXX_IOSOCKS_H
#define PSOCKSXX_IOSOCKS_H

#include <psocksxx/sockstreambuf.h>

#include <ios>


namespace psocksxx {

	/**
	*   @brief base class for socket stream controller classes
	*
	*   This class holds the common methods for socket stream controller
	*   classes.
	*/
	class iosocks : public virtual std::ios {
	public:

		/**
		*   @brief destructor
		*
		*   Does nothing.
		*
		*/
		virtual ~iosocks() throw() { };

		/**
		*   @brief get the timed-out status flag value
		*   @return boolean @c true if timed-out flag is set or @c false
		*           otherwise.
		*
		*   Returns the timed-out status for the associated socket stream
		*   buffer.
		*
		*/
		bool timedout() const throw();

		/**
		*   @brief set the timeout value for stream communications
		*   @param sec seconds
		*   @param usec microseconds
		*   @return a reference to the internal timeout structure
		*
		*   Wrapper method for sockstreambuf::timeout() to set the
		*   timeout value for stream communications.
		*
		*   @see sockstreambuf::timeout()
		*
		*/
		const timeval * timeout( time_t sec, suseconds_t usec ) throw();

		/**
		*   @brief clear the timeout value
		*   @return a reference to the internal timeout structure which will
		*           always be a @c NULL pointer after clearing the timeout
		*
		*   This will clear any timeout values set for this stream using
		*   timeout().
		*
		*/
		void * clear_timeout() throw();

	protected:

		/**
		*   @brief empty default constructor
		*
		*   Empty default constructor so that derived classes through virtual
		*   inheritance does not have to call the constructor.
		*
		*/
		iosocks() throw() { }

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_IOSOCKS_H */

