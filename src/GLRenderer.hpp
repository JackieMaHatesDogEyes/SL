#pragma once

#ifdef FORCE_EXTERNAL_GL_LOADER
    #include <glcorearb.h>
#else
    #ifdef GL_IMPL
        #define GLAD_GL_IMPLEMENTATION
    #endif
    #include <glad/gl.h>
#endif

class GLRenderer {
    public:
        GLRenderer(void* windowHandle);

        static void Setup();

        struct ShaderProgram CreateShaderProgram(const char* file);

        static void Close();
};