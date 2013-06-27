#!/usr/local/bin/perl -w
#
#use strict;

# Defaults...
$njobs = 30;
$queue='kanga';
$directory="contours/";

$c1central = -0.00199031;
$c2central = 0.353517;
$c1sigma = 0.0908079;
$c2sigma = 0.091869;

$c1val_init = $c1central - 7*$c1sigma;
$c2val_init = $c2central - 7*$c2sigma;

# Submit the jobs...
for (my $i = 0; $i <= $njobs+1; $i++){

    my $c1_tmp = $c1val_init + $i*$c1sigma/2.;

    for (my $j = 0; $j <= $njobs + 1; $j++){

	my $c2_tmp = $c2val_init + $j*$c2sigma/2.;

	next if($i < $njobs + 1 && $j == $njobs + 1);
        next if($i == $njobs + 1 && $j != $njobs + 1);

	if($i == $njobs + 1){
	    $c1_tmp = 0;
	    $c2_tmp = 0;
	}

	my $resultfile=$directory."/cont_".$i."_".$j.".dat";
	my $logfile="$directory/logfile_".$i."_".$j.".log";

	my $mycommand = "drawContours -n std -f ".$resultfile." -y ".$c1_tmp." -x ".$c2_tmp;

	print "mycommand = ".$mycommand;
	system("bbrbsub -C 0 -q $queue -J `~/rline` -o $logfile $mycommand");
    }
}

print "Done.\n";
