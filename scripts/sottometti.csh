#!/bin/csh

set start = 1
set stop  = 2000
@ stop = $stop + 1

while ( $start < $stop )

set logfile = "/afs/cern.ch/user/p/pellicci/scratch0/HH_rulez/CMSSW_2_2_4/src/GeneratorInterface/AlpgenInterface/test/log/logfile_$start.log"

set config = "/afs/cern.ch/user/p/pellicci/scratch0/HH_rulez/CMSSW_2_2_4/src/GeneratorInterface/AlpgenInterface/test/simdigiTcl/config_$start""_cfg.py"

bsub -q 1nh -o $logfile execute.csh $config

echo "$config"

@ start = $start + 1
end
