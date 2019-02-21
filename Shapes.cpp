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

std::vector< float > GenerateHollowGear( unsigned int sides, float width, float scale, float outerToothLength, float innerToothLength )
{
	std::vector< float > gear;
	const float POINTS_C = ( float ) sides;
	const float DELTA_C = TAU_M / POINTS_C;
	float x, y;
	float lastX = cos( 0 ) * scale;
	float lastY = sin( 0 ) * scale;
	outerToothLength = ( 1.f + outerToothLength );
	innerToothLength = -( innerToothLength - 1.f );
	for( float i = 0.f; i < POINTS_C; i += 1.f )
	{
		x = ( cos( DELTA_C * ( i + 1.f ) ) * scale );
		y = ( sin( DELTA_C * ( i + 1.f ) ) * scale );
		float z = 0.f;
		//Point on circle.//
		PushPoint( std::move( gear ), lastX * width, lastY * width, z );
		PushPoint( std::move( gear ), lastX, lastY, z );
		PushPoint( std::move( gear ), x, y, z );
		//The width of the gears rim.//
		PushPoint( std::move( gear ), lastX * width, lastY * width, z );
		PushPoint( std::move( gear ), x * width, y * width, z );
		PushPoint( std::move( gear ), lastX = x, lastY = y, z );
		//Outer tips on gear.//
		if( outerToothLength != 0.0f )
		{	
			PushPoint( std::move( gear ), lastX, lastY, z );
			PushPoint( std::move( gear ), cos( DELTA_C * i ) * scale, 
					sin( DELTA_C * i ) * scale, z );
			PushPoint( std::move( gear ), 
					cos( DELTA_C * ( i + .5f ) ) * outerToothLength * scale, 
					sin( DELTA_C * ( i + .5f ) ) * outerToothLength * scale, z );
		}
		//Inner tips on gear.//
		if( innerToothLength != 0.0f )
		{
			PushPoint( std::move( gear ), lastX * width, lastY * width, z );
			PushPoint( std::move( gear ), cos( DELTA_C * i ) * scale * width, 
					sin( DELTA_C * i ) * scale * width, z );
			PushPoint( std::move( gear ), 
					cos( DELTA_C * ( i + .5f ) ) * innerToothLength * scale, 
					sin( DELTA_C * ( i + .5f ) ) * innerToothLength * scale, z );
		}
	}
	return gear;

}
