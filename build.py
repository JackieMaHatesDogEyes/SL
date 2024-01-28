import platform

from os import system, makedirs
from shutil import copy, copytree



def cmd(command):
    print(command)
    system(command)


RELEASE = True

files = ["src/SL.cpp", "src/Renderer.cpp", "src/Audio.cpp", "src/gl.c"]



windows_libs = "-Wno-tautological-constant-out-of-range-compare -ld3dcompiler -ld3d11 -ldxgi -lSDL2 -lgdi32 -limm32 -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lwinmm -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -lSDL2main"
linux_libs = "-lSDL2 -lm -lGL -lX11"
apple_libs = "-liconv -framework ForceFeedback -framework CoreHaptics -framework AudioToolbox -framework GameController -framework OpenGL -framework Metal -framework Carbon -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo -lSDL2 -I/opt/local/include"

windows_lib_directory = "lib/win64"
linux_lib_directory = "lib/linux"
apple_lib_directory = "lib/macos"



files = " ".join(files)

CPP = "clang++"


if platform.system() == "Linux":
    libs = linux_libs
    lib_directory = linux_lib_directory
    CPP = "g++"
elif platform.system() == "Windows":
    libs = windows_libs
    lib_directory = windows_lib_directory
elif platform.system() == "Darwin":
    libs = apple_libs
    lib_directory = apple_lib_directory

if RELEASE:
    if "clang" in CPP:
        optimization_level = "-Os"
    else:
        optimization_level = "-O3"


# set version to c++ 11
libs += " -std=c++11"

cmd(f"{CPP} {files} -o SL -Iinclude -L{lib_directory} {libs} {optimization_level}")

makedirs("dist", exist_ok=True)

if platform.system() != "Windows":
    cmd("mv SL dist/SL")
else:
    cmd("move SL.exe dist/SL.exe")

    copy(f"{lib_directory}/d3d11.dll", "dist/d3d11.dll")
    copy(f"{lib_directory}/dxgi.dll", "dist/dxgi.dll")
    copytree("shaders", "dist/shaders", dirs_exist_ok=True)
