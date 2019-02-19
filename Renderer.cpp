#include "Renderer.h"

void Renderer::Initialize( const char* canvasName, float* verticies, size_t verticyCount_, int height, int width )
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

void Renderer::Update()
{
	gl->clear( gl->get_COLOR_BUFFER_BIT() );
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
	"attribute vec3 a_position;"
	"void main() {"
	"\tgl_Position = vec4( a_position.x, a_position.y, a_position.z, 1.0 );"
	"}";
const char* Renderer::fragmentShaderSource = 
	"void main() {"
	"\tgl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );"
	"}";
