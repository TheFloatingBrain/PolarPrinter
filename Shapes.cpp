#include "Shapes.h"

#define PI_M 3.1415f
#define TAU_M ( 2.0f * PI_M )

std::vector< float > GenerateGear( unsigned int sides, float scale, float toothLength )
{
	std::vector< float > gear;
	const float POINTS_C = ( float ) sides;
	const float DELTA_C = TAU_M / POINTS_C;
	float lastX = cos( 0 ) * scale;
	float lastY = sin( 0 ) * scale;
	for( float i = 0.f; i < POINTS_C; i += 1.f )//POINTS_C; i += 1.f )
	{
		//Point on circle.//
		PushPoint( std::move( gear ), 0.f * scale, 0.f * scale, 0.f * scale );
		PushPoint( std::move( gear ), lastX, lastY, 0.f * scale );
		PushPoint( std::move( gear ), lastX = ( cos( DELTA_C * ( i + 1.f ) ) * scale ), 
				lastY = ( sin( DELTA_C * ( i + 1.f ) ) * scale ), 0.f * scale );
		//Tip on gear.//
		PushPoint( std::move( gear ), lastX, lastY, 0.f * scale );
		PushPoint( std::move( gear ), cos( DELTA_C * i ) * scale, 
				sin( DELTA_C * i ) * scale, 0.f * scale );
		PushPoint( std::move( gear ), 
				cos( DELTA_C * ( i + .5f ) ) * ( 1.f + toothLength ) * scale, 
				sin( DELTA_C * ( i + .5f ) ) * ( 1.f + toothLength ) * scale, 0.f * scale );
	}
	return gear;
}
