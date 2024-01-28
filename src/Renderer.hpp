#pragma once

#include <SDL2/SDL.h>

struct ShaderProgram {
    void* program = nullptr; // Used when shader is compiled to a single program (e.g. OpenGL)
    
    // Used when shader is compiled to multiple programs (e.g. DX11)
    void* vertexShader = nullptr;
    void* fragmentShader = nullptr;
};

void* getNativeWindowHandle(SDL_Window* window);

#ifdef _WIN32
    #include "DX11Renderer.hpp"
    #define Renderer DX11Renderer
#else
    // TODO: Include OpenGL Renderer
#endif