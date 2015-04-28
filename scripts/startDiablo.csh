#!/bin/bash

cd /home/pellicci/.wine/drive_c/Program\ Files\ \(x86\)/Diablo\ III/
#__GL_THREADED_OPTIMIZATIONS=1 WINEDEBUG=-all optirun wine64 Wow-64.exe -openglW
__GL_THREADED_OPTIMIZATIONS=1 WINEDEBUG=-all setarch i386 -3 optirun wine Diablo\ III.exe -launch
