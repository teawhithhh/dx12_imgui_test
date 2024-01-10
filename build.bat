@echo off
cd .\build
echo -- CMAKE START
cmake ..
echo -- CMAKE END
echo -- NINJA START
ninja
echo -- NINJA END
main.exe
