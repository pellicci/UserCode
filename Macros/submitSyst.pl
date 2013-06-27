#!/usr/local/bin/perl -w

MAIN:
{
    print "sourcing the configuration files\n";
    open(INFILE, $ARGV[0]) || die "Couldn't open INFILE.\n";
    while (<INFILE>){
        @input_1 = split(/g_/,$_);
        @input = split(/\//,$input_1[1]);

	print "now doing configuration key ".$input[0]."\n";
	$command = "bbrbsub -q xxl -o syst_root/fit_WS_".$input[0].".log WSTimeFit -n ".$input[0];
	#print $command;
	system($command);

    }
    close (INFILE);
}


