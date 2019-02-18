#include <cheerp/clientlib.h>
#include <cheerp/client.h>

[[cheerp::genericjs]] void domOutput( const char* toLog ) {
    	client::console.log( toLog );
}


struct [[cheerp::genericjs]] Application
{
	static client::CanvasRenderingContext2D* GetRenderingContext( const char* canvasName, int height_, int width_ )
	{
		x = 0;
		canvas = ( client::HTMLCanvasElement* ) client::document.getElementById( canvasName );
		canvas->set_width( width = width_ );
		canvas->set_height( height = height_ );
		client::document.get_body()->appendChild( canvas );
		return ( context2D = ( client::CanvasRenderingContext2D* ) canvas->getContext( "2d" ) );
	}

	static void TestOut( const char* text ) {
		context2D->set_font( "24px sans-serif" );
		context2D->fillText( text, ++x, height - 24 );
	}


	static void Init() {
		client::requestAnimationFrame( cheerp::Callback( RunLoop ) );
	}

	static int x;
	static int height, width;
	static client::HTMLCanvasElement* canvas;
	static client::CanvasRenderingContext2D* context2D;

	private:
		static void RunLoop() {
			Application::TestOut( "test" );
			client::requestAnimationFrame( cheerp::Callback( RunLoop ) );
		}
};


void webMain()
{
    	domOutput( "<begin>" );
		Application::GetRenderingContext( "renderCanvas", 400, 400 );
		Application::Init();
    	domOutput( "<end>" );
}
