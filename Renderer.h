#include "Utility.h"
#include <cheerp/webgl.h>

#ifndef RENDERER_HEADER_H
    #define RENDERER_HEADER_H
    struct [[cheerp::genericjs]] Renderer
    {
        static void Initialize( const char* canvasName, float* verticies, size_t verticyCount_, int height, int width );
        static void Update();
        static void CreateShader();
        static void UpdatePerspective();

        static client::HTMLCanvasElement* canvas;
        static client::WebGLRenderingContext* gl;
        static const char* vertexShaderSource;
        static const char* fragmentShaderSource;
        static size_t verticyCount;
        static client::WebGLBuffer* vertexBuffer;
        static client::WebGLShader* vertexShader, *fragmentShader;
        static client::WebGLProgram* shaderProgram;
        static client::WebGLUniformLocation* cameraPosition, *cameraAngles, *far, *near, *width, *height;
        static float* cameraPositionVector;
        static float* cameraAnglesVector;
    };
#endif
