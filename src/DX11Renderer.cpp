#include "DX11Renderer.hpp"

#include <stdio.h>

#include <cassert>

void assertHResult(HRESULT hr) {
    assert(SUCCEEDED(hr));
}

DX11Renderer::DX11Renderer(void* nativeWindowHandle) {

    HRESULT hr;

    // Create the device and context

    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = (HWND)nativeWindowHandle;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = TRUE;

    D3D_FEATURE_LEVEL feature_level;
    UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
    #if defined( DEBUG ) || defined( _DEBUG )
    flags |= D3D11_CREATE_DEVICE_DEBUG;
    #endif

    hr = D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        flags,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &device,
        &feature_level,
        &context
    );

    assertHResult(hr);

    // Create the framebuffer

    hr = swapchain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**)&framebuffer
    );

    assertHResult(hr);

    hr = device->CreateRenderTargetView(
        framebuffer,
        NULL,
        &renderTargetView
    );

    assertHResult(hr);

    framebuffer->Release();

    this->CreateShaderProgram("shaders/triangle.hlsl");

}



void DX11Renderer::Close() {
    
    renderTargetView->Release();

    //framebuffer->Release();

    swapchain->Release();

    context->Release();

    device->Release();
}

struct ShaderProgram DX11Renderer::CreateShaderProgram(const char* file, const char* _unused) {
    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;

    #if defined( DEBUG ) || defined( _DEBUG )
        flags |= D3DCOMPILE_DEBUG;
    #endif

    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* fsBlob = nullptr;

    WCHAR* wfile;
    mbstowcs(wfile, file, strlen(file) + 1);

    HRESULT hr = D3DCompileFromFile(
        wfile,
        NULL,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "vs_main",
        "vs_5_0",
        flags,
        0,
        &vsBlob,
        NULL
    );

    assertHResult(hr);

    hr = D3DCompileFromFile(
        wfile,
        NULL,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "fs_main",
        "ps_5_0",
        flags,
        0,
        &fsBlob,
        NULL
    );

    assertHResult(hr);

    ID3D11VertexShader* vs;
    ID3D11PixelShader* fs;

    hr = device->CreateVertexShader(
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        NULL,
        &vs
    );

    assertHResult(hr);


    hr = device->CreatePixelShader(
        fsBlob->GetBufferPointer(),
        fsBlob->GetBufferSize(),
        NULL,
        &fs
    );

    assertHResult(hr);

    ID3D11InputLayout* inputLayout;
    D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
    { "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    /*
    { "COL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    */
    };

    hr = device->CreateInputLayout(
        inputElementDesc,
        ARRAYSIZE(inputElementDesc),
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        &inputLayout
    );

    assertHResult(hr);



    return (ShaderProgram) {
        (void*) inputLayout, // Used as input layout for DX11
        (void*)vs,
        (void*)fs
    };
}