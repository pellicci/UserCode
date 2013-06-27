#!/bin/tcsh
#set echo

if($#argv == 0) then 
echo "usage: copyFromCastor.csh <castor-dir-name>"
exit 1
endif


set CASTORDIR=$1

#stageFiles.csh $CASTORDIR


foreach FILE (`rfdir $CASTORDIR | awk '{ print $9 }'`)  

if($FILE != "DTLocalRecoAnalysisStd_10.root") then 
    echo "copy: $CASTORDIR/$FILE" 
    rfcp $CASTORDIR/$FILE .
endif


end

exit 0
#foreach FILE (`ls ${DIRNAME}`) 
#/afs/cern.ch/delphi/scratch_week/m/mariotti
