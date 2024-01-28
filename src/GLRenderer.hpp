#pragma once

#ifdef FORCE_EXTERNAL_GL_LOADER
    #include <glcorearb.h>
#else
    #include <glad/gl.h>
#endif

class GLRenderer {
    public:
        GLRenderer(void* windowHandle);


        struct ShaderProgram CreateShaderProgram(const char* file);

        void Close();
};