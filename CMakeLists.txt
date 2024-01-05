cmake_minimum_required(VERSION 3.12)

project(test)

set(CMAKE_CXX_STANDARD 23)

set(IMGUI_DIR "C:/Users/240821/app/imgui")

add_executable(main
    main.cpp
    ./dx_context/directx_context.cxx
    ./imgui_context/imgui_context.cxx
    ./styles/styles.cxx
    ./widgets/center_control_helper/center_control_helper.cxx
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx12.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

include_directories(
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ./widgets
    ./styles
    ./imgui_context
    ./dx_context
)

# Линковка с библиотеками
target_link_libraries(main PRIVATE d3dcompiler gdi32 dwmapi d3d12 user32 kernel32 dxgi)
