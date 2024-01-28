#include "Renderer.hpp"
#include <SDL2/SDL_syswm.h>

#ifdef _WIN32
    #include "DX11Renderer.cpp"
#else
    #include "GLRenderer.cpp"
#endif


void* getNativeWindowHandle(SDL_Window* window) {
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(window, &info);
    #ifdef _WIN32
        return (void*)info.info.win.window;
    #elif __linux__
        return (void*)info.info.x11.window;
    #elif __APPLE__
        return (void*)info.info.cocoa.window;
    #else
        #warning "Unknown platform!"
        return nullptr;
    #endif
}