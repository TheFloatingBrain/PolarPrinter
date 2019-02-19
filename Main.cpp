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
	}
	static void Update()
	{
		gl->clear( gl->get_COLOR_BUFFER_BIT() );
		client::requestAnimationFrame( cheerp::Callback( Update ) );
	}
	static client::HTMLCanvasElement* canvas;
	static client::WebGLRenderingContext* gl;
	static const char* vertexShaderSource;
	static const char* fragmentShaderSource;
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

void webMain()
{
    	DOMOutput( "<begin>" );
		Renderer::Initialize( "glcanvas", 400, 400 );
		Renderer::Update();
    	DOMOutput( "<end>" );
}
