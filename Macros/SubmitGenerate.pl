#!/usr/local/bin/perl -w
#
#SubmitGenerate.pl
#N. Danielson June 19, 2003
#

#use strict;

# Defaults...
$nexp=1;
$nev = 3009;
$njobs = 2000;
$queue='kanga';
$command='ToyIter';
$directory="Toy_results/central_value/";
$SEED=4;

#$c1pval = 0.15;
#$c2pval = 0.15;

$c1pval = -0.00563796;
$c2pval = 0.357336;
#$c1pval = -0.106595;
#$c2pval = 0.359225;
$c1mval = 0.0127581;
$c2mval = 0.399144;

    my $ntotal = $nexp*$njobs;

print "Will run $njobs jobs with $nexp experiments per job for a total of: $ntotal experiments.\n";
print "Command:                  $command\n";
print "Directory to use:         $directory\n";
print "Queue:                    $queue\n";
print "c1 value                  $c1pval\n";
print "c2 value                  $c2pval\n";

# Submit the jobs...
for (my $i = 1; $i <= $njobs; $i++){

    $SEED = $i + 4;
    print "Running job $i out of $njobs . Using seed = $SEED\n";
    my $resultfile="$directory/toy_$i";
    my $logfile="$directory/logfile_$i.log";
    my $bbrrootcommand="$command -f $resultfile -s $SEED -e $nexp -n $nev -1 $c1pval -3 $c2pval -2 $c1mval -4 $c2mval";
    system("bbrbsub -q $queue -J `/u/rd/pellicci/rline` -o $logfile $bbrrootcommand");
}

print "Done.\n";
