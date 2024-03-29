cmake_minimum_required(VERSION 3.12)

project(test)

set(CMAKE_CXX_STANDARD 23)

set(IMGUI_DIR "C:/Users/240821/app/imgui")
set(DEBUG_FLAGS "-D DEBUG")

SET(CMAKE_CXX_FLAGS  "-static -static-libgcc -static-libstdc++ -fno-rtti -O5 ${CMAKE_CXX_FLAGS} ${STYLE_FLAGS} ${IMGUI_FLAGS} ${DEBUG_FLAGS}")

add_executable(main
    main.cpp
    resources.o

    ./dx_context/directx_context.cxx
    ./imgui_context/imgui_context.cxx

    ./styles/style.cxx

    ./widgets/center_control_helper/center_control_helper.cxx
    ./widgets/id_generator.cxx
    ./widgets/input_text.cxx

    ./windows/initialize_windows.cxx
    ./windows/logger.cxx
    ./windows/login_window.cxx
    ./windows/window_decorator.cxx
    ./windows/main_window.cxx

    ./config_parser/parser.cxx
    ./windows/controler_z_order/control_z_order.cxx

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
    ./windows
    ./config_parser
    ./exeptions
)

# Линковка с библиотеками
target_link_libraries(main PRIVATE d3dcompiler gdi32 dwmapi d3d12 user32 kernel32 dxgi dwmapi)
