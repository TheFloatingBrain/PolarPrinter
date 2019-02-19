#include <cheerp/clientlib.h>
#include <cheerp/client.h>
#include <cheerp/webgl.h>
#include <vector>
#include <math.h>
#include <utility>
#define PI_M 3.1415f
#define TAU_M ( 2.0f * PI_M )

[[cheerp::genericjs]] void DOMOutput( const char* toLog ) {
    	client::console.log( toLog );
}

struct [[cheerp::genericjs]] Renderer
{
	static void Initialize( const char* canvasName, float* verticies, size_t verticyCount_, int height, int width )
	{
		verticyCount = verticyCount_;
		canvas = static_cast< client::HTMLCanvasElement* >( client::document.getElementById( canvasName ) );
		canvas->set_height( height );
		canvas->set_width( width );
		gl = ( client::WebGLRenderingContext* ) canvas->getContext( "experimental-webgl" );
		gl->clearColor( 0, 0, 1, 1 );
		vertexBuffer = gl->createBuffer();
		gl->bindBuffer( gl->get_ARRAY_BUFFER(), vertexBuffer );
		gl->bufferData( gl->get_ARRAY_BUFFER(), cheerp::MakeTypedArray( verticies ), gl->get_STATIC_DRAW() );
		CreateShader();
		double position = gl->getAttribLocation( shaderProgram, "a_position" );
		gl->vertexAttribPointer( position, 3, gl->get_FLOAT(), false, 0, 0 );
		gl->enableVertexAttribArray( position );
		gl->enable( gl->get_DEPTH_TEST() );
		gl->viewport( 0, 0, width, height );
	}
	static void Update()
	{
		gl->clear( gl->get_COLOR_BUFFER_BIT() );
		gl->drawArrays( gl->get_TRIANGLES(), 0, verticyCount );
		client::requestAnimationFrame( cheerp::Callback( Update ) );
	}

	static void CreateShader()
	{
		vertexShader = gl->createShader( gl->get_VERTEX_SHADER() );
		fragmentShader = gl->createShader( gl->get_FRAGMENT_SHADER() );
		gl->shaderSource( vertexShader, vertexShaderSource );
		gl->shaderSource( fragmentShader, fragmentShaderSource );
		gl->compileShader( vertexShader );
		gl->compileShader( fragmentShader );
		shaderProgram = gl->createProgram();
		gl->attachShader( shaderProgram, vertexShader );
		gl->attachShader( shaderProgram, fragmentShader );
		gl->linkProgram( shaderProgram );
		gl->useProgram( shaderProgram );
	}

	static client::HTMLCanvasElement* canvas;
	static client::WebGLRenderingContext* gl;
	static const char* vertexShaderSource;
	static const char* fragmentShaderSource;
	static size_t verticyCount;
	//static float verticies[];
	static client::WebGLBuffer* vertexBuffer;
	static client::WebGLShader* vertexShader, *fragmentShader;
	static client::WebGLProgram* shaderProgram;
};

const char* Renderer::vertexShaderSource = 
	"attribute vec3 a_position;"
	"void main() {"
	"\tgl_Position = vec4( a_position.x, a_position.y, a_position.z, 1.0 );"
	"}";
const char* Renderer::fragmentShaderSource = 
	"void main() {"
	"\tgl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );"
	"}";
/*
float Renderer::verticies[] = { 
						0.0f, 0.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						.5f, 1.0f, 0.0f
					 };*/

void PushPoint( std::vector< float >&& toPush, float x, float y, float z )
{
	toPush.push_back( x );
	toPush.push_back( y );
	toPush.push_back( z );
}

std::vector< float > GenerateGear( float scale, float toothLength )
{
	std::vector< float > gear;
	const float POINTS_C = 20.f;
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

void webMain()
{
    	DOMOutput( "<begin>" );
		auto verts = GenerateGear( .5f, .4f );
		Renderer::Initialize( "glcanvas", verts.data(), verts.size() / 3, 400, 400 );
		Renderer::Update();
    	DOMOutput( "<end>" );
}
