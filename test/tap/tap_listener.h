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

#ifndef TAP_TAP_LISTENER_H
#define TAP_TAP_LISTENER_H

#include <cppunit/TestListener.h>
#include <cppunit/Message.h>


namespace tap {

	class TAPListener : public CppUnit::TestListener {
	public:

		TAPListener( CppUnit::Test * factory_suite );
		~TAPListener();

		void startSuite( CppUnit::Test * suite );
		void startTest( CppUnit::Test * test );
		void addFailure( const CppUnit::TestFailure &failure );
		void endTest( CppUnit::Test * test);
		void endSuite( CppUnit::Test * suite );

	private:
		CppUnit::Test *     _factory_suite;
		CppUnit::Message *  _failure_msg;
		bool                _test_success;

	};

} /* end of namespace tap */

#endif /* !TAP_TAP_LISTENER_H */

