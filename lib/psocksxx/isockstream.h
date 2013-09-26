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

#ifndef PSOCKSXX_ISOCKSTREAM_H
#define PSOCKSXX_ISOCKSTREAM_H

#include <psocksxx/sockstreambuf.h>

#include <istream>


namespace psocksxx {

	/**
	*   @brief Input controller class for socket streams
	*
	*   This class acts as an interface for getting inputs
	*   from a psocksxx::sockstreambuf class.
	*/
	class isockstream : public std::istream {
	public:

		/**
		*   @brief constructor
		*   @param ssb socket stream buffer
		*
		*   Create an input socket stream controller instance.
		*
		*/
		isockstream( sockstreambuf * ssb ) throw();

		virtual ~isockstream() throw();  //!< destructor

		/**
		*   @brief get the timed-out status for this stream
		*   @return boolean @c true if timed-out flag is set or @c false
		*           otherwise.
		*
		*   Returns the timed-out status.
		*
		*/
		bool timedout() const throw();

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_ISOCKSTREAM_H */

