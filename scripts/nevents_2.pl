#!/usr/local/bin/perl

MAIN:
{
    print "sourcing the logs's\n";
    open(INFILE, $ARGV[0]) || die "Couldn't open INFILE.\n";
    $risultato = 0;

    while (<INFILE>){
	open(INTWO, $_);
	$tmpfile = $_;     
	while(<INTWO>){
	    if (/total number of events=(\d+)/) {
		@input = split(/\//,$tmpfile);
		@input_1 = split(/\./,$input[2]);
                $mytcl = "SPTcl/$input_1[0].tcl";
		print "Found a good file: $mytcl\n";

		open(INTHREE,$mytcl);
		while(<INTHREE>){
		    if(/#\s{1}(\d+)\/(\d+)\s{1}events\s{1}selected/){
		       $numer = $1;
		       $denom = $2;
		       $risultato = $risultato + $denom;
		       print "selected $numer events of $denom\n";
		   }

		}
		close(INTHREE);
	    }
	}
	close(INTWO);
    }

    print "number of events: $risultato\n";

    close(INFILE);


}
