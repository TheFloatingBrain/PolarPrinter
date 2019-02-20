#include "Shapes.h"

void webMain()
{
    	DOMOutput( "<begin>" );
		auto verts = GenerateHollowGear( 30, .8f, .7f, .3f, .5f );
		Renderer::Initialize( "glcanvas", verts.data(), verts.size() / 3, 400, 400 );
		Renderer::Update();
    	DOMOutput( "<end>" );
}
