#!/bin/tcsh
#
# copy recursively a directory and it's content to castor (subdirs are copied as well)
#
unalias ls

if($#argv != 2) then
echo "Usage: copyDirToCastor.csh <from_dir> <to_dir>"
echo "NOTE: use relative path (only one dir up) for local dir and full path for castor dir"
exit(1)
endif




set FROM_DIR=$1
set TO_DIR=$2

rfdir ${TO_DIR}/${FROM_DIR}
if($status == 2) then 
echo "Castor dir:  ${TO_DIR}/${FROM_DIR} does not exist, creating it!"
rfmkdir ${TO_DIR}/${FROM_DIR}
endif



cd ${FROM_DIR}
foreach FILE_TO_MOVE (`ls .`) 
    echo ${FILE_TO_MOVE}
    # check if directory
    if(-d $FILE_TO_MOVE) then 
	copyDirToCastor.csh $FILE_TO_MOVE ${TO_DIR}/${FROM_DIR}
    else
	rfcp ${FILE_TO_MOVE} ${TO_DIR}/${FROM_DIR}
    endif

end


cd -




