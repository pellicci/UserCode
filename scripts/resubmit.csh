#!/bin/csh

foreach file (`grep -L completed log/*.log`)
#foreach file (`grep -L completed log/* | xargs grep "Cputime" | awk -F C '{print $1}' `)

set num = `echo $file | awk -F . '{print $1}' | awk -F _ '{print $2}'`  

set logfile = "/afs/cern.ch/user/p/pellicci/scratch0/HH_rulez/CMSSW_2_2_4/src/GeneratorInterface/AlpgenInterface/test/log/logfile_$num.log"

set config = "/afs/cern.ch/user/p/pellicci/scratch0/HH_rulez/CMSSW_2_2_4/src/GeneratorInterface/AlpgenInterface/test/simdigiTcl/config_$num""_cfg.py"

bsub -q 8nh -o $logfile execute.csh $config

rm $logfile

echo "$config"

end

