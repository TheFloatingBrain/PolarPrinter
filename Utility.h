#include <vector>
#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#ifndef UTILITY_HEADER_H
#define UTILITY_HEADER_H
    [[cheerp::genericjs]] void DOMOutput( const char* toLog );

    void PushPoint( std::vector< float >&& toPush, float x, float y, float z );
#endif
