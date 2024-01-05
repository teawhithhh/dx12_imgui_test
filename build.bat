@echo off
cd C:\Users\240821\app\imgui\examples\example_win32_directx12\build
echo -- CMAKE START
cmake ..
echo -- CMAKE END
echo -- NINJA START
ninja
echo -- NINJA END
main.exe
