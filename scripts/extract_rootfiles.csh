#!/bin/csh

echo "Please enter a crab dir name:"
set dir = $<                      # C shell input from stdin

foreach file (`ls $dir/res/out_files_*.tgz`)

tar -xzvf $file

set number = `echo $file | cut -d'_' -f6 | cut -d'.' -f1`

rm CMSSW_$number.stderr
rm CMSSW_$number.stdout
rm crab_fjr_$number.xml

mv *_$number.root rootfiles_tmp/

end
