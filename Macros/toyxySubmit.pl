#!/usr/local/bin/perl -w
#
#SubmitGenerate.pl
#N. Danielson June 19, 2003
#

#use strict;

# Defaults...
$njobs = 2000;
$queue='kanga';
$command='toyxy';
$directory="generate_xy/syst/";

$SEED=1;

# Submit the jobs...
for (my $i = 1; $i <= $njobs; $i++){

    $SEED = $i + 4;
    print "Running job $i out of $njobs . Using seed = $SEED\n";
    my $resultfile="$directory/toyxy_$i";
    my $logfile="$directory/logfile_$i.log";
    my $bbrrootcommand="$command -s $SEED -f $resultfile";
    system("bbrbsub -q $queue -J `/u/rd/pellicci/rline` -o $logfile $bbrrootcommand");
}

print "Done.\n";
