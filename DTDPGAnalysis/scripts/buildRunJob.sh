if [ $# -lt 2 ]; then
    dataset="/SingleMu/Run2012B-PromptReco-v1/RECO"
else
    dataset=$2
fi
if [ $# -lt 3 ]; then
    template=Skim_and_Ntuple_template_cfg.py
    name=Skim_and_Ntuple_$1_cfg.py
    castor=DTDPG/2012/DTNtuple/SingleMu/
    jobid=dt
else
    template=Skim_and_Ntuple_UncT0_template_cfg.py
    name=Skim_and_Ntuple_UncT0_$1_cfg.py
    castor=DTDPG/2012/DTNtuple_UncT0/SingleMu/
    jobid=du
fi

# find number of events for req job
events=`dbs --search --query "find sum(file.numevents) where run=$1 and dataset=$dataset"  | tail -n 1`
# prepare list of files
dbs --search --query "find file, file.parent where run=$1 and dataset=$dataset" | grep store > "$1""_files.txt"
cat $1_files.txt | awk '{print $1}' | sed "s|^|'|;s|$|',|" > $1_reco_files.txt
cat $1_files.txt | awk '{print $2}' | sed "s|^|'|;s|$|',|" > $1_raw_files.txt
streco=RECOFILES
straw=RAWFILES
stfile=FILENAME
# create python
sed -e "/$streco/r $1_reco_files.txt" -e "/$streco/d" $CMSSW_BASE/src/UserCode/DTDPGAnalysis/test/$template | sed  -e "/$straw/r $1_raw_files.txt" -e "/$straw/d" | sed  -e "s/$stfile/DTNtuple_run$1.root/g" > $CMSSW_BASE/src/$name
rm $1_*files*txt
echo "Python file for processing run $1 created. Job should be running on $events events..."
# create shell job
echo "#!/bin/csh" > $CMSSW_BASE/src/job$1.csh
echo "setenv SCRAM_ARCH slc5_amd64_gcc462" >> $CMSSW_BASE/src/job$1.csh
echo "cd $CMSSW_BASE/src" >> $CMSSW_BASE/src/job$1.csh
echo "eval \`scram runtime -csh\`" >> $CMSSW_BASE/src/job$1.csh
echo "cd -" >> $CMSSW_BASE/src/job$1.csh
echo "cmsRun $CMSSW_BASE/src/$name" >> $CMSSW_BASE/src/job$1.csh
echo "rfcp DTNtuple_run$1.root /castor/cern.ch/user/g/guiducci/$castor/DTNtuple_run$1.root" >> $CMSSW_BASE/src/job$1.csh
# submit
bsub -R "pool>15000" -q 1nw -J $jobid$1 < $CMSSW_BASE/src/job$1.csh
sleep 1
bjobs
#nohup cmsRun Skim_and_Ntuple_$1_cfg.py > /tmp/guiducci/$1.out 2> /tmp/guiducci/$1.err < /dev/null &
