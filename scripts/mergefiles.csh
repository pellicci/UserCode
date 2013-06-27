#!/bin/csh

set direc1 = $1
set direc2 = $2
set direc3 = $3

@ globalnumber = 2

rfmkdir $direc3

set filename = "PYTHIA6_JPsi_10TeV_GEN_SIM_DIGI_L1_RAW_RECO_"

echo "File name is "; echo $filename

foreach numberONE(`rfdir $direc1 | awk '{print $9}' | awk -F _ '{print $10}' | awk -F . '{print $1}' | sort -n`)

#echo $direc1/$filename$numberONE.root $direc3/$filename$globalnumber.root
rfrename $direc1/$filename$numberONE.root $direc3/$filename$globalnumber.root
@ globalnumber++

end

foreach numberTWO(`rfdir $direc2 | awk '{print $9}' | awk -F _ '{print $10}' | awk -F . '{print $1}' | sort -n`)

#echo $direc2/$filename$numberTWO.root $direc3/$filename$globalnumber.root
rfrename $direc2/$filename$numberTWO.root $direc3/$filename$globalnumber.root
@ globalnumber++

end

