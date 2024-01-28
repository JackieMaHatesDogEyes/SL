#include "Audio.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <cassert>

ma_result err;
ma_engine engine;

void AudioDevice::Setup() {
    printf("Setting up audio device...\n");
    err = ma_engine_init(nullptr, &engine);
    assert(err == MA_SUCCESS);

    printf("Audio device set up!\n");
}

void AudioDevice::Close() {
    printf("Closing audio device...\n");
    ma_engine_uninit(&engine);
    printf("Audio device closed!\n");
}