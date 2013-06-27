#!/bin/tcsh

set startdir = "`pwd`"

set enddir = `echo $startdir | awk '{split($1,a,"src")} ; END {print a[1]"src"}'`

echo $enddir

cd "$enddir"

exit
