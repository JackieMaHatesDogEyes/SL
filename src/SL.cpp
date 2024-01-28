#include "Renderer.hpp"
#include "Audio.hpp"
#include "Utils.hpp"

#include <SDL2/SDL.h>

static bool isRunning;

void PollWindowEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) isRunning = false;
    }
}

int main(int argv, char** args) { 
    SDL_Init(SDL_INIT_VIDEO);
    AudioDevice::Setup();

    uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    #ifndef _WIN32
        flags |= SDL_WINDOW_OPENGL;
    #endif

    SDL_Window *window = SDL_CreateWindow("Scarlet Lotus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 450, flags);

    #ifdef _WIN32
        Renderer renderer(getNativeWindowHandle(window));
    #else
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        auto ctx = SDL_GL_CreateContext(window);
        Renderer renderer((void*) SDL_GL_GetProcAddress);
    #endif


    isRunning = true;
    

    while (isRunning) {
        PollWindowEvents();


        renderer.Clear();

        #ifndef _WIN32
            SDL_GL_SwapWindow(window);
        #endif
    }

    AudioDevice::Close();
    renderer.Close();

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}