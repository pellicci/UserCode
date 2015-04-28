#!/bin/bash

cd /home/pellicci/.wine/drive_c/Program\ Files\ \(x86\)/Steam/
__GL_THREADED_OPTIMIZATIONS=1 WINEDEBUG=-all optirun wine Steam.exe -no-dwrite
