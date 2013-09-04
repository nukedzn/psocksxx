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

#ifndef PSOCKSXX_LSOCKSTREAM_H
#define PSOCKSXX_LSOCKSTREAM_H

#include <psocksxx/iosockstream.h>

namespace psocksxx {

	/**
	*   @brief Local (unix) socket controller class
	*
	*   This class acts as a controller for communicating through a
	*   local (unix) socket and uses an instance of psocksxx::sockstreambuf
	*   as the underlying / associated sequence.
	*/
	class lsockstream : public iosockstream {
	public:

		/**
		*   @brief destructor
		*/
		~lsockstream() throw();

	};

} /* end of namespace psocksxx */

#endif /* !PSOCKSXX_LSOCKSTREAM_H */

