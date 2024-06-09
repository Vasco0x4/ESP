#include "Graphics.h"
#include <cstdio>

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;

bool InitializeDirectX(HWND hwnd) {
    OutputDebugStringA("Initializing DirectX...\n");

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create Direct3D 11 device and context.\n");
        return false;
    }

    OutputDebugStringA("Direct3D 11 device and context created successfully.\n");

    IDXGIFactory* pFactory = nullptr;
    hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), (void**)&pFactory);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create DXGI factory.\n");
        return false;
    }

    OutputDebugStringA("DXGI factory created successfully.\n");

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    hr = pFactory->CreateSwapChain(g_pd3dDevice, &sd, &g_pSwapChain);
    pFactory->Release();

    if (FAILED(hr)) {
        char error[256];
        sprintf_s(error, "Failed to create swap chain. HRESULT: 0x%X\n", hr);
        OutputDebugStringA(error);
        return false;
    }

    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to get swap chain buffer.\n");
        return false;
    }

    hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr)) {
        OutputDebugStringA("Failed to create render target view.\n");
        return false;
    }

    OutputDebugStringA("DirectX initialization successful.\n");
    return true;
}

void CleanupDirectX() {
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}
