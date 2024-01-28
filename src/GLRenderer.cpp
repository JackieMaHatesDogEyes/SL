#ifdef __linux__
#elif defined(__APPLE__)
#elif defined(_WIN32)
#else
    #define FORCE_EXTERNAL_GL_LOADER // Use custom GL loader on unknown platforms
#endif


#include "GLRenderer.hpp"

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