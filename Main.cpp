#include <cheerp/clientlib.h>
#include <cheerp/client.h>
#include <cheerp/webgl.h>
#include <vector>

[[cheerp::genericjs]] void DOMOutput( const char* toLog ) {
    	client::console.log( toLog );
}

struct [[cheerp::genericjs]] Renderer
{
	static void Initialize( const char* canvasName, int height, int width )
	{
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
		gl->drawArrays( gl->get_TRIANGLES(), 0, 3 );
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
	static float verticies[];
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

float Renderer::verticies[] = { 
						0.0f, 0.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						.5f, 1.0f, 0.0f
					 };
void webMain()
{
    	DOMOutput( "<begin>" );
		Renderer::Initialize( "glcanvas", 400, 400 );
		Renderer::Update();
    	DOMOutput( "<end>" );
}
