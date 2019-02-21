#include "Renderer.h"

void Renderer::Initialize( const char* canvasName, float* verticies, size_t verticyCount_, int height, int width )
{
	verticyCount = verticyCount_;
	cameraPositionVector = new float[ 3 ];
	cameraAnglesVector = new float[ 3 ];
	cameraPositionVector[ 0 ] = 0.f;
	cameraPositionVector[ 1 ] = 0.f;
	cameraPositionVector[ 2 ] = 0.f;
	cameraAnglesVector[ 0 ] = 0.f;
	cameraAnglesVector[ 1 ] = 0.f;
	cameraAnglesVector[ 2 ] = 0.f;
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

void Renderer::Update()
{
	gl->clear( gl->get_COLOR_BUFFER_BIT() );
	cameraPosition = gl->getUniformLocation( shaderProgram, "cameraPosition" );
	cameraAngles = gl->getUniformLocation( shaderProgram, "cameraAngles" );

	near = gl->getUniformLocation( shaderProgram, "near" );
	far = gl->getUniformLocation( shaderProgram, "far" );
	width = gl->getUniformLocation( shaderProgram, "width" );
	height = gl->getUniformLocation( shaderProgram, "height" );

	cameraAnglesVector[ 2 ] += .01f;
	cameraPositionVector[ 2 ] -= .01f;
	gl->uniform3fv( cameraPosition, cheerp::MakeTypedArray( cameraPositionVector ) );
	gl->uniform3fv( cameraAngles, cheerp::MakeTypedArray( cameraAnglesVector ) );

	gl->uniform1f( near, 0.0 );
	gl->uniform1f( far, 10.0 );
	gl->uniform1f( width, 1.0 );
	gl->uniform1f( height, 1.0 );

	gl->drawArrays( gl->get_TRIANGLES(), 0, verticyCount );
	client::requestAnimationFrame( cheerp::Callback( Update ) );
}

void Renderer::CreateShader()
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

const char* Renderer::vertexShaderSource = 
	"uniform vec3 cameraPosition;\n"
	"uniform vec3 cameraAngles;\n"
	"uniform float near;\n"
	"uniform float far;\n"
	"uniform float width;\n"
	"uniform float height;\n"
	"attribute vec3 a_position;\n"
	"void main() {\n"
/*	"\tfloat x = ( a_position.x - cameraPosition.x );\n"
	"\tfloat y = ( a_position.y - cameraPosition.y );\n"
	"\tfloat z = ( a_position.z - cameraPosition.z );\n"
	"\tvec4 projection;\n"
	"\tprojection.x = cameraPosition.y * ( sin( cameraAngles.z ) * y + cameraPosition.z * x );\n"
	"\tprojection.y = sin( cameraAngles.x ) * ( cameraPosition.y * z + sin( cameraAngles.y ) * ( sin( cameraAngles.z ) * y + cameraPosition.z * x ) ) + cameraPosition.x * ( cameraPosition.z * y - sin( cameraAngles.z ) * x );\n"
	"\tprojection.z = cameraPosition.x * ( cameraPosition.y * z + sin( cameraAngles.y ) * ( sin( cameraAngles.z ) * y + cameraPosition.z * x ) ) - sin( cameraAngles.x ) * ( cameraPosition.z * y - sin( cameraAngles.z ) * x );\n"
	"\tprojection.w = 1.0;\n"*/
	////////////////////////////////////////////////
		"\tmat3 a = mat3( vec3( 1, 0, 0 ), \n"
				"\t\tvec3( 0, cos( cameraAngles.x ), sin( cameraAngles.x ) ), \n"
				"\t\tvec3( 0, -sin( cameraAngles.x ), cos( cameraAngles.x ) ) );\n"
		"\tmat3 b = mat3( vec3( cos( cameraAngles.y ), 0, -sin( cameraAngles.y ) ), \n"
				"\t\tvec3( 0, 1, 0 )\n, "
				"\t\tvec3( sin( cameraAngles.y ), 0, cos( cameraAngles.y ) ) );\n"
		"\tmat3 c = mat3( vec3( cos( cameraAngles.z ), sin( cameraAngles.z ), 0 ), \n"
				"\t\tvec3( -sin( cameraAngles.z ), cos( cameraAngles.z ), 0 ),\n"
				"\t\tvec3( 0, 0, 1 ) );\n"
/*		"\tmat4 m = mat4("
				"\t\tvec4( 1.0, 0.0, 0.0, 0.0 ), \n"
				"\t\tvec4( 0.0, 1.0, 0.0, 0.0 ), \n"
				"\t\tvec4( 0.0, 0.0, -2.0 / 10.0, 0.0 ), \n"
				"\t\tvec4( 0.0, 0.0, 1.0, 1.0 ) );\n"
*///		"\tgl_Position = vec4( a * b * c * ( a_position - cameraPosition ).xyz, 1.0 );\n"
		"\tmat4 m = mat4("
				"\t\tvec4( 1.0 / width, 0.0, 0.0, 0.0 ), \n"
				"\t\tvec4( 0.0, 1.0 / height, 0.0, 0.0 ), \n"
				"\t\tvec4( 0.0, 0.0, -2.0 / ( far - near ), 0.0 ), \n"
				"\t\tvec4( 0.0, 0.0, -( far + near ) / ( far - near ), 1.0 ) );\n"
		"\tgl_Position = vec4( a * b * c * ( a_position - cameraPosition ), 1.0 ) * m;\n"
	"}\n";
const char* Renderer::fragmentShaderSource = 
	"void main() {\n"
	"\tgl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );\n"
	"}\n";
