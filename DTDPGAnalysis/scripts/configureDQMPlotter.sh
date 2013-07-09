#!/bin/sh
###
# This script is meant to:
# A) get the list of DQM root files produced in parellel with CRAB 
#    running the runDQMOfflineDPGSources_cfg.py
# B) configure the runDQMOfflineDPGClients_cfg_template.py with the correct Run number
#    and the correct DQM root files to read
###
if [ $# -lt 2 ];then
  echo "Run Number or eos dir not provided!"
  echo "Usage :"
  echo "  $0 <Run Number> <eos dir with DQM root files for that Run>"
  echo ""
  echo "  <Run Number> is the Run number you what to produce plots for "
  echo "  <eos dir> is the eos caf dir where the DQM root files have been copied "
  echo "               as configured with storage_path + lfn in crab_runDQM*.cfg "
  echo "               For example:   "
  echo "                 /eos/cms/store/caf/marycruz/PromptOffline/DQMDTRun<Run Number>"
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
####InputFiles=`rfdir ${OutputDir} | awk '{print $9}' | grep root`
###InputFiles=`/afs/cern.ch/project/eos/installation/0.1.0-22d/bin/eos.select ls ${OutputDir} | awk '{print $1}' | grep root`
InputFiles=`/afs/cern.ch/project/eos/installation/pro/bin/eos.select ls ${OutputDir} | awk '{print $1}' | grep root`
#echo $InputFiles
first=0
for file in $InputFiles; do
  ##remotefile="rfio:$OutputDir/$file"
  remotefile="root://eoscms/$OutputDir/$file"
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

