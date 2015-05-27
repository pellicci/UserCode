#!/usr/local/bin/perl -w
#
#use strict;

# Defaults...
$njobs = 30;
$queue='kanga';
$directory_plus="contours_plus/";
$directory_minus="contours_minus/";

$c1pluscentral = -0.125082;
$c2pluscentral = 0.360853;
$c1plussigma = 0.0935283;
$c2plussigma = 0.09727971;

$c1minuscentral = 0.00188502;
$c2minuscentral = 0.428975;
$c1minussigma = 0.0692658;
$c2minussigma = 0.0694682;

$c1plusval_init = $c1pluscentral - 7*$c1plussigma;
$c2plusval_init = $c2pluscentral - 7*$c2plussigma;
$c1minusval_init = $c1minuscentral - 7*$c1minussigma;
$c2minusval_init = $c2minuscentral - 7*$c2minussigma;

# Submit the jobs
#first the D0
for (my $i = 0; $i <= $njobs+1; $i++){

    my $c1_tmp = $c1plusval_init + $i*$c1plussigma/2.;

    for (my $j = 0; $j <= $njobs + 1; $j++){

	my $c2_tmp = $c2plusval_init + $j*$c2plussigma/2.;

	next if($i < $njobs + 1 && $j == $njobs + 1);
        next if($i == $njobs + 1 && $j != $njobs + 1);

	if($i == $njobs + 1){
	    $c1_tmp = 0;
	    $c2_tmp = 0;
	}

	my $resultfile=$directory_plus."/cont_".$i."_".$j.".dat";
	my $logfile="$directory_plus/logfile_".$i."_".$j.".log";

	my $mycommand = "drawContoursCP -n CP -f ".$resultfile." -s 1 -y ".$c1_tmp." -x ".$c2_tmp;

	print "mycommand = ".$mycommand."\n";
	system("bbrbsub -C 0 -q $queue -J `~/rline` -o $logfile $mycommand");
    }
}

for (my $i = 0; $i <= $njobs+1; $i++){

    my $c1_tmp = $c1minusval_init + $i*$c1minussigma/2.;

    for (my $j = 0; $j <= $njobs + 1; $j++){

	my $c2_tmp = $c2minusval_init + $j*$c2minussigma/2.;

	next if($i < $njobs + 1 && $j == $njobs + 1);
        next if($i == $njobs + 1 && $j != $njobs + 1);

	if($i == $njobs + 1){
	    $c1_tmp = 0;
	    $c2_tmp = 0;
	}

	my $resultfile=$directory_minus."/cont_".$i."_".$j.".dat";
	my $logfile="$directory_minus/logfile_".$i."_".$j.".log";

	my $mycommand = "drawContoursCP -n std -f ".$resultfile." -s 0 -y ".$c1_tmp." -x ".$c2_tmp;

	print "mycommand = ".$mycommand."\n";
	system("bbrbsub -C 0 -q $queue -J `~/rline` -o $logfile $mycommand");
    }
}

print "Done.\n";
