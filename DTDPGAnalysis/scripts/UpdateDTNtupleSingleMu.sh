
if [ $# -lt 1 ]; then
    dataset="/SingleMu/Run2012B-PromptReco-v1/RECO"
else
    dataset=$1
fi
if [ $# -lt 2 ]; then
    castor=DTDPG/2012/DTNtuple/SingleMu
    jobid=dt
else
    castor=DTDPG/2012/DTNtuple_UncT0/SingleMu
    jobid=du
fi

# get all runs with > 1k events from DBS
dbs --search --query "find run,sum(file.numevents)  where dataset=$dataset" | grep -v Using | grep -v run | awk '{ if ($2 >= 1000) print $1 }' > runlist.txt
# get runs with running job
bjobs | grep -v JOBID | awk '{print $7}' | grep $jobid | sed 's/^..//' > runningjobslist.txt
# get runs with ntuple already created
rfdir /castor/cern.ch/user/g/guiducci/$castor/ | awk '{print $9}' | sed 's/^............//;s/.\{5\}$//' > donejobslist.txt
# generate list of runs still to process
L=`cat runningjobslist.txt | wc -l`
echo $L
if [[ $L -eq 0 ]]; then
    cat runlist.txt > filt1.txt
else
    awk 'NR==FNR{_[$1];next}!($1 in _)' runningjobslist.txt runlist.txt > filt1.txt
fi
awk 'NR==FNR{_[$1];next}!($1 in _)' donejobslist.txt filt1.txt > runstodo.txt
# submit jobs
if [ $# -lt 2 ]; then
    cat runstodo.txt | while read A; do ./buildRunJob.sh $A $dataset; done
else
    cat runstodo.txt | while read A; do ./buildRunJob.sh $A $dataset c; done
fi

# clean up
rm runlist.txt
rm runningjobslist.txt
rm donejobslist.txt
rm filt1.txt
rm runstodo.txt
