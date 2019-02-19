#include "Utility.h"

[[cheerp::genericjs]] void DOMOutput( const char* toLog ) {
    	client::console.log( toLog );
}

void PushPoint( std::vector< float >&& toPush, float x, float y, float z )
{
	toPush.push_back( x );
	toPush.push_back( y );
	toPush.push_back( z );
}
