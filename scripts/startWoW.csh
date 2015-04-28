#!/bin/bash

cd /home/pellicci/.wine/drive_c/Program\ Files\ \(x86\)/World\ of\ Warcraft/
__GL_THREADED_OPTIMIZATIONS=1 WINEDEBUG=-all optirun wine Wow-64.exe -opengl
#__GL_THREADED_OPTIMIZATIONS=1 WINEDEBUG=-all optirun wine Wow-64.exe 

