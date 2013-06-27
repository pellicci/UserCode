#!/bin/csh

set numcore = "`grep physical /proc/cpuinfo | wc -l`"

if ($numcore == 8) then
exit 0
endif

exit 1
