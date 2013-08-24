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

#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/CompilerOutputter.h>
#include <fstream>


int main( int argc, char * argv[] ) {

	// informs test-listener about testresults
	CppUnit::TestResult testresult;

	// register listener for collecting the test-results
	CppUnit::TestResultCollector collectedresults;
	testresult.addListener( &collectedresults );

	// register listener for per-test progress output
	CppUnit::BriefTestProgressListener progress;
	testresult.addListener( &progress );

	// insert test-suite at test-runner by registry
	CppUnit::TestRunner testrunner;
	testrunner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest () );
	testrunner.run( testresult );

	// output results in compiler-format
	CppUnit::CompilerOutputter compileroutputter( &collectedresults, std::cout );
	compileroutputter.write();

	// output XML for Jenkins xunit plugin
	std::ofstream xmloutput( "xunit-runner.xml" );
	CppUnit::XmlOutputter xmloutputter( &collectedresults, xmloutput );
	xmloutputter.write();

	// return 0 if tests were successful
	return collectedresults.wasSuccessful() ? 0 : 1;

}

