#ifndef DX_CONTEXT
#define DX_CONTEXT

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>
#include <thread>

namespace dx {
    struct FrameContext;
    class DX_WINDOW;
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

    void                                       render_loop_dx12();

    FrameContext*                              WaitForNextFrameResources();
    static void                                WaitForLastSubmittedFrame();
    static void                                CreateRenderTarget();
    static void                                CleanupRenderTarget();

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

#endif
