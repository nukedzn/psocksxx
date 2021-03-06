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

#ifndef PSOCKSXX_OSOCKSTREAM_H
#define PSOCKSXX_OSOCKSTREAM_H

#include <psocksxx/iosocks.h>

#include <ostream>


namespace psocksxx {

	/**
	*   @brief Output controller class for socket streams
	*
	*   This class acts as an interface for sendding outputs
	*   to a psocksxx::sockstreambuf class
	*/
	class osockstream :
		public virtual iosocks,
		public std::ostream {

	public:

		/**
		*   @brief constructor
		*   @param ssb socket stream buffer
		*
		*   Create and output socket stream controller instance
		*
		*/
		osockstream( sockstreambuf * ssb ) throw();

		virtual ~osockstream() throw();  //!< destructor

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKS_OSOCKSTREAM_H */

