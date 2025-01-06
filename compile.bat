@echo off
setlocal enabledelayedexpansion

set SRC_FILES=
for %%f in (src\*.c) do (
    set SRC_FILES=!SRC_FILES! %%f
)

gcc !SRC_FILES! -o main.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -I src/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm