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

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>

#include "tap/tap_listener.h"


int main( int argc, char * argv[] ) {

	// Get the top level suite from the registry
	CppUnit::Test * suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// the event manager and test controller
	CppUnit::TestResult controller;

	// TAP listener
	tap::TAPListener listener( suite );
	controller.addListener( &listener );

	// register listener for collecting the test-results
	CppUnit::TestResultCollector collectedresults;
	controller.addListener( &collectedresults );

	// test runner
	CppUnit::TestRunner runner;
	runner.addTest( suite );

	// run tests.
	runner.run( controller );

	// output XML for Jenkins xunit plugin
	std::ofstream xmloutput( "xunit.xml" );
	CppUnit::XmlOutputter xmloutputter( &collectedresults, xmloutput );
	xmloutputter.write();

	return 0;

}

