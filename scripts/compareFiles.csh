
ls std/* | awk '{split($0,array,"_") ; print "cp 125percent/*_"array[3]"_*.root merge/125percent/"}'
