#ifndef DX_CONTEXT
#define DX_CONTEXT

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <filesystem>
#include <tchar.h>
#include <thread>

namespace dx {
    struct FrameContext;
    class DX_WINDOW;
    class Image;
}

struct dx::FrameContext
{
    ID3D12CommandAllocator* CommandAllocator;
    UINT64                  FenceValue;
};


class dx::DX_WINDOW {
public:
                                               DX_WINDOW(const wchar_t*, int, int, int, int, int);
                                               ~DX_WINDOW();

    static bool                                LoadTexturFromFile(const char* filename, ID3D12Device* d3d_device, D3D12_CPU_DESCRIPTOR_HANDLE srv_cpu_handle, ID3D12Resource** out_tex_resource, int* out_width, int* out_height);
    void                                       RenderLoopDX12();

    FrameContext*                              WaitForNextFrameResources();
    static void                                WaitForLastSubmittedFrame();
    static void                                CreateRenderTarget();
    static void                                CleanupRenderTarget();
    static LRESULT WINAPI                      WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


    HWND                                       get_hwnd() { return hWnd; }
    std::pair<int, int>                        get_size() { return std::pair<int, int>(width, height); }

    // Data
    inline static int const                    NUM_FRAMES_IN_FLIGHT = 3;
    inline static IDXGISwapChain3*             g_pSwapChain = nullptr;
    inline static ID3D12Device*                g_pd3dDevice = nullptr;
    inline static ID3D12DescriptorHeap*        g_pd3dSrvDescHeap = nullptr;

private:
    WNDCLASSEXW                                wc;
    HWND                                       hWnd;
    int                                        height;
    int                                        width;
    int                                        round_radius;

    bool                                       CreateDeviceD3D();
    void                                       CleanupDeviceD3D();

    HRGN                                       CreateRoundRectRgn(int x, int y, int width, int height, int radius);
    void                                       SetWindowRoundCorners();

    inline static FrameContext                 g_frameContext[NUM_FRAMES_IN_FLIGHT] = {};
    inline static UINT                         g_frameIndex = 0;

    inline static int const                    NUM_BACK_BUFFERS = 3;
    inline static ID3D12DescriptorHeap*        g_pd3dRtvDescHeap = nullptr;
    inline static ID3D12CommandQueue*          g_pd3dCommandQueue = nullptr;
    inline static ID3D12GraphicsCommandList*   g_pd3dCommandList = nullptr;
    inline static ID3D12Fence*                 g_fence = nullptr;
    inline static HANDLE                       g_fenceEvent = nullptr;
    inline static UINT64                       g_fenceLastSignaledValue = 0;
    inline static HANDLE                       g_hSwapChainWaitableObject = nullptr;
    inline static ID3D12Resource*              g_mainRenderTargetResource[NUM_BACK_BUFFERS] = {};
    inline static D3D12_CPU_DESCRIPTOR_HANDLE  g_mainRenderTargetDescriptor[NUM_BACK_BUFFERS] = {};

};

class dx::Image {
public:
    // We need to pass a D3D12_CPU_DESCRIPTOR_HANDLE in ImTextureID, so make sure it will fit
    static_assert(sizeof(ImTextureID) >= sizeof(D3D12_CPU_DESCRIPTOR_HANDLE), "D3D12_CPU_DESCRIPTOR_HANDLE is too large to fit in an ImTextureID");

    Image(std::filesystem::path path);

    Image(const Image &) = default;
    Image(Image &&) = default;
    Image &operator=(const Image &) = default;
    Image &operator=(Image &&) = default;
    // We presume here that we have our D3D device pointer in g_pd3dDevice

    int my_image_width = 0;
    int my_image_height = 0;
    ID3D12Resource* my_texture = NULL;

    // Get CPU/GPU handles for the shader resource view
    // Normally your engine will have some sort of allocator for these - here we assume that there's an SRV descriptor heap in
    // g_pd3dSrvDescHeap with at least two descriptors allocated, and descriptor 1 is unused
    UINT handle_increment = dx::DX_WINDOW::g_pd3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    int descriptor_index = 1; // The descriptor table index to use (not normally a hard-coded constant, but in this case we'll assume we have slot 1 reserved for us)
    D3D12_CPU_DESCRIPTOR_HANDLE my_texture_srv_cpu_handle = dx::DX_WINDOW::g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart();
    D3D12_GPU_DESCRIPTOR_HANDLE my_texture_srv_gpu_handle = dx::DX_WINDOW::g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart();
    bool ret = false;
};

#endif //DX_CONTEXT
