#if !defined(_WIN32) || !defined(__linux__) || !defined(__APPLE__)
    #define FORCE_EXTERNAL_GL_LOADER // Use custom GL loader on unknown platforms
#endif

#define GL_IMPL
#include "GLRenderer.hpp"

GLRenderer::GLRenderer(void* wptr) {
    // Window handle should be proc address OR NULL

    #ifndef FORCE_EXTERNAL_GL_LOADER
        GLADloadfunc loader = (GLADloadfunc)wptr;

        gladLoadGL(loader);
    #endif
}