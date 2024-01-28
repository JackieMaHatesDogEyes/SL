#pragma once
#include <miniaudio.h>

class AudioDevice {
    public:
        static void Setup();

        static void Close();
};