#!/bin/sh
###
# This script is meant to:
# A) get the list of DQM root files produced in parellel with CRAB 
#    running the runDQMOfflineDPGSources_cfg.py
# B) configure the runDQMOfflineDPGClients_cfg_template.py with the correct Run number
#    and the correct DQM root files to read
###
if [ $# -lt 2 ];then
  echo "Run Number or CASTOR dir not provided!"
  echo "Usage :"
  echo "  $0 <Run Number> <CASTOR dir with DQM root files for that Run>"
  echo ""
  echo "  <Run Number> is the Run number you what to produce plots for "
  echo "  <CASTOR dir> is the CASTOR dir where the DQM root files have been copied "
  echo "               as configured with storage_path + lfn in crab_runDQM*.cfg "
  echo "               For example:   "
  echo "                 /castor/cern.ch/user/a/afanfani/DQMCRAFT/DQMDTRun<Run Number>"
  echo ""
  exit 1
fi

run=$1
OutputDir=$2


CONFIG_FILE="runDTDPGOfflineSummary_template_cfg.py"
if ! [ -e $CONFIG_FILE ]; then
 echo "ERROR: File $CONFIG_FILE do not exist in this directory"
 echo "Exiting..."
 exit 1
fi

## A)
echo "- Looking for DQM root files in ${OutputDir} "
InputFiles=`rfdir ${OutputDir} | awk '{print $9}' | grep root`
#echo $InputFiles
first=0
for file in $InputFiles; do
  remotefile="rfio:$OutputDir/$file"
  if [ $first -le 0 ];then
   INPUT="'$remotefile'"
  else
   INPUT="$INPUT , '$remotefile'"
  fi
  first=1
done
echo $INPUT
## B)
## replace in configuration template the Run number and input file list
if [ -e tmp.pycfg ];then
 rm tmp.pycfg
fi
less $CONFIG_FILE | sed -e "s?INPUT?$INPUT?g" > tmp.pycfg
less tmp.pycfg | sed -e "s?INSERTRUN?${run}?g" > runDTDPGOfflineSummary_cfg_${run}.py
rm tmp.pycfg
echo "- Created the configuration file: runDTDPGOfflineSummary_cfg_${run}.py "
echo "==> In order to produce DQM plots for run ${run} you should run it:"
echo "    cmsRun runDTDPGOfflineSummary_cfg_${run}.py"

