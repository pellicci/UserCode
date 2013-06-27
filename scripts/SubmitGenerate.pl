#!/usr/local/bin/perl -w
#
#SubmitGenerate.pl
#N. Danielson June 19, 2003
#

#use strict;

# Defaults...
$nexp=1;
$nev = 100;
$njobs=1;
$queue='medium';
$command='ToyIter.C';
$directory="Toy_results/toyresol/";
$SEED=4;

# Does it exist?
if (! -d "$directory") {
    print STDERR "$directory doesn't exist.  Do you want to create it? (y/n)\n";
    my $ans = <STDIN>;
    chomp($ans);
    if( ($ans =~ /yes/i) || ($ans eq "y") ) {
	print STDERR "Creating directory $directory\n";
	`mkdir -p $directory`;
    } else {
	print STDERR "Exiting because directory $directory doesn't exist\n";
	exit 0;
    }
}

    my $ntotal = $nexp*$njobs;

print <<ENDOUT;
Will run $njobs jobs with $nexp experiments per job for a total of: $ntotal experiments.
Command:                  $command    
Directory to use:         $directory  
Queue:                    $queue 
ENDOUT
    ;    

# Submit the jobs...
for (my $i = 1; $i <= $njobs; $i++){

    $SEED = $SEED + 4;
    print "Running job $i out of $njobs . Using seed = $SEED\n";
    my $resultfile="$directory/toy_$i";
    my $logfile="$directory/logfile_$i.log";
    my $bbrrootcommand="root -b -q \'$command(\"$resultfile\",$nexp,$nev,$SEED)\'";
    system("bbrbsub -q $queue -J `/u/rd/pellicci/rline` -o $logfile $bbrrootcommand");
}

print "Done.\n";
