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

#include "tap_listener.h"

#include <cppunit/TestSuite.h>
#include <cppunit/TestFailure.h>
#include <cppunit/Exception.h>
#include <iostream>


namespace tap {


	TAPListener::TAPListener( CppUnit::Test * factory_suite )
			: _factory_suite( factory_suite ), _test_success( false ) {

		// defaults
		_failure_msg = 0;

		CppUnit::TestSuite * s = (CppUnit::TestSuite *) _factory_suite;
		CppUnit::TestSuite * c;
		int total_tests = 0;

		// calculate total number of tests
		for ( int i = 0; i < s->getChildTestCount(); i++ ) {
			c = (CppUnit::TestSuite *) s->getChildTestAt( i );
			total_tests += c->getChildTestCount();
		}

		// output tap header
		std::cout << "1.." << total_tests << std::endl;

	}


	TAPListener::~TAPListener() {
		// destructor
	}


	void TAPListener::startSuite( CppUnit::Test * suite ) {
		// start test suite
	}


	void TAPListener::startTest( CppUnit::Test * test ) {
		_test_success = true;
	}


	void TAPListener::addFailure( const CppUnit::TestFailure &failure ) {

		CppUnit::Exception * e = failure.thrownException();
		_failure_msg  = new CppUnit::Message ( e->message() );
		_test_success = false;

	}


	void TAPListener::endTest( CppUnit::Test * test ) {

		if ( _test_success ) {

			std::cout << "ok " << test->getName() << std::endl;

		} else {

			std::cout << "not ok " << test->getName() << std::endl;
			std::cout << "# " << _failure_msg->shortDescription() << std::endl;

			for ( int i = 0; i < _failure_msg->detailCount(); i++ ) {
				std::cout << "# \t" << _failure_msg->detailAt( i ) << std::endl;
			}

			// cleanup
			delete _failure_msg;

		}


	}


	void TAPListener::endSuite( CppUnit::Test * suite ) {
		// end test suite
	}

} /* end of namespace tap */

