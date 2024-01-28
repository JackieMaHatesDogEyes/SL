#pragma once

#ifdef FORCE_EXTERNAL_GL_LOADER
    #include <glcorearb.h>
#else
    #include <glad/gl.h>
#endif

class GLRenderer {
    public:
        GLRenderer(void* windowHandle);


        struct ShaderProgram CreateShaderProgram(const char* vsfile, const char* fsfile);

        void Clear();
        void Clear(char r, char g, char b, char a);
        void Clear(float r, float g, float b, float a);

        void Close();
};