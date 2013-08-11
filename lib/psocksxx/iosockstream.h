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

#ifndef PSOCKSXX_IOSOCKSTREAM_H
#define PSOCKSXX_IOSOCKSTREAM_H

#include <psocksxx/isockstream.h>
#include <psocksxx/osockstream.h>


namespace psocksxx {

	/**
	*   @brief Input and Output controller class for socket streams
	*
	*   This merges the two input and output controller
	*   classes to create a single interface for controlling
	*   both input and output socket streams.
	*
	*/
	class iosockstream :
		public isockstream,
		public osockstream {

	public:

		/**
		*   @brief constructor
		*   @param ssb socket stream buffer
		*
		*   This constructor simply initialises the parent
		*   classes with the passed in socket stream buffer
		*/
		iosockstream( sockstreambuf * ssb ) throw() :
			isockstream( ssb ), osockstream( ssb ) {
			// constructor
		}

		/**
		*   @brief destructor
		*/
		virtual ~iosockstream() throw() {
			// destructor
		}

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_IOSOCKSTREAM_H */

