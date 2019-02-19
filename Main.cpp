#include "Shapes.h"

void webMain()
{
    	DOMOutput( "<begin>" );
		auto verts = GenerateGear( 30.f, .4f, .4f );
		Renderer::Initialize( "glcanvas", verts.data(), verts.size() / 3, 400, 400 );
		Renderer::Update();
    	DOMOutput( "<end>" );
}
