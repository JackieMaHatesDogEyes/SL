#ifndef _WIN32

#if defined(__APPLE__) || defined(__linux__)
    #define GLAD_GL_IMPLEMENTATION
    #include <glad/gl.h>

#else
    // If OS not supported by GLAD, use glcorearb.h
    // (this means user must load all OpenGL functions manually)
    #include "glcorearb.h" // Does nothing
#endif


#endif