@echo off

cmake -S src/ -B build/
cmake --build build

REM Pause to keep the console window open
pause

