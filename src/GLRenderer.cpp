#ifdef __linux__
#elif defined(__APPLE__)
#elif defined(_WIN32)
#else
    #define FORCE_EXTERNAL_GL_LOADER // Use custom GL loader on unknown platforms
#endif


#include "GLRenderer.hpp"
#include "Utils.hpp"

GLRenderer::GLRenderer(void* wptr) {
    // Window handle should be proc address OR NULL

    #ifndef FORCE_EXTERNAL_GL_LOADER
        GLADloadfunc loader = (GLADloadfunc)wptr;

        gladLoadGL(loader);
    #endif
}

void GLRenderer::Close() {
    // Nothing to do here (User should remember to destroy VAOs, ShaderPrograms, etc.)
}

void GLRenderer::Clear() {
    // Clear to white
    this->Clear(1.0f, 1.0f, 1.0f, 1.0f);
}

void GLRenderer::Clear(char r, char g, char b, char a) {
    this->Clear((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
}

void GLRenderer::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

struct GLProgram {
    GLuint program;
};


struct ShaderProgram GLRenderer::CreateShaderProgram(const char* vsfile, const char* fsfile) {
    struct ShaderProgram program;

    GLuint vert, frag;

    char* vs = LoadFile(vsfile);
    char* fs = LoadFile(fsfile);

    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vs, NULL);
    glCompileShader(vert);

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fs, NULL);
    glCompileShader(frag);

    GLuint prgm =  glCreateProgram();
    glAttachShader(prgm, vert);
    glAttachShader(prgm, frag);
    glLinkProgram(prgm);

    GLProgram* p = (GLProgram*) malloc(sizeof(GLProgram));
    p->program = prgm;

    program.program = (void*) p;

    glDeleteShader(vert);
    glDeleteShader(frag);

    free(vs);
    free(fs);

    return program;
}