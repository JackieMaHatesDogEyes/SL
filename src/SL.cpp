#include "Renderer.hpp"
#include "Audio.hpp"

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

    SDL_Window *window = SDL_CreateWindow("Scarlet Lotus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 450, SDL_WINDOW_SHOWN);

    Renderer renderer(getNativeWindowHandle(window));

    isRunning = true;
    

    while (isRunning) {
        PollWindowEvents();
    }

    AudioDevice::Close();
    renderer.Close();

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}