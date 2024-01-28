#pragma once

#include "Renderer.hpp"

#include <d3d11.h> // DX11 (Uses DXVK)
#include <dxgi.h> // DXGI (Uses DXVK)
#include <d3dcompiler.h> // D3DCompiler (Doesn't use DXVK)

class DX11Renderer {
    public:
        DX11Renderer(void* nativeWindowHandle);

        struct ShaderProgram CreateShaderProgram(const char* file);

        void Close();
    private:
        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* context = nullptr;
        IDXGISwapChain* swapchain = nullptr;
        ID3D11RenderTargetView* renderTargetView = nullptr;
        ID3D11Texture2D* framebuffer = nullptr;
};

