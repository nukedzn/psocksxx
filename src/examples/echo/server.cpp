
#include <iostream>
#include <psocksxx/tcpnsockstream.h>


int main( int argc, char **argv ) {

	// tcp socket stream
	psocksxx::tcpnsockstream ss;

	// network address to bind to
	psocksxx::nsockaddr naddr( "localhost", "21555" );

	// bind
	try {
		ss.bind( &naddr, true );
	} catch( psocksxx::sockexception &e ) {
		std::cerr <<  e.what() << std::endl;
		return 1;
	}

	// listen
	try {
		ss.listen( 1 );
	} catch( psocksxx::sockexception &e ) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;

}

