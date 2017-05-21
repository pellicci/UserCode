#!/bin/bash

cd /home/pellicci/.wine/drive_c/Program\ Files\ \(x86\)/Steam
WINEPREFIX=/home/pellicci/.wine-skyrim __GL_THREADED_OPTIMIZATIONS=1 WINEDEBUG=-all wine64 Steam.exe -no-dwrite &

cd /home/pellicci/.wine/drive_c/Program\ Files\ \(x86\)/Steam/SteamApps/common/Skyrim
WINEPREFIX=/home/pellicci/.wine-skyrim __GL_THREADED_OPTIMIZATIONS=1 WINEDEBUG=-all wine64 SkyrimLauncher.exe
