#!/usr/bin/perl
#
###################################################################################################
##
## usage: perl5 LumiFromTcl.pl <fromtcl>.log <badfiles>.log
##
###################################################################################################

MAIN:
{
    open(INFILE_TCL, $ARGV[0]);
    $filescrivi = "runlist.txt";
    open(OUT, ">$filescrivi") or die "Cacchio! Non posso scrivere nel file $filescrivi\n";

    $badevents=0;
    $badtot=0;
    $tclevents=0;
    $badlumival=0;
    $badbcval=0;
#    system ("rm lumi.txt");
    
    while (<INFILE_TCL>){
	@input = split();
	$file=$input[0];
	open(FILE_TCL, $file);
	while (<FILE_TCL>){
	    if(/run\s{1}(\d{5}):\s{1}(\d{1,7})\s{1}events/) {
		my $run=$1;
		my $evt=$2;
		print OUT "$run\n";
		$tclevents=$tclevents+$evt;
#		system ("touch lumi.txt");
#		system ("lumi -R $run | \grep Lumi | \grep Processed >> lumi.txt");
	    }
	}
	close (FILE_TCL);

    }
    print "total number of events: $tclevents\n";
    close (INFILE_TCL);

    open(BADFILE_LOG, $ARGV[1]);
    $per=0;
    while (<BADFILE_LOG>){
	if(/processed\s{1}(\d{1,7})\s{1}of\s{1}the\s{1}total\s{1}(\d{1,7})/) {
	    my $done=$1;
	    my $tot=$2;
	    $bad=$tot-$done;
	    $per=$bad/$tot;
##	    print "$per\n";
	    $badtot=$badtot+$bad;
	}
	if(/bad\s{1}kshort/) {
	    @inputlog = split();
	    @logfile=split(/-/,$inputlog[1]);
	    $badtcl="kshort/tcl/$logfile[0]-$logfile[1]-$logfile[2].tcl";
	    $set="$logfile[3]";
	    open(BAD_TCL, $badtcl);
##	    print "$badtcl\n";
	    $events=0;
	    while (<BAD_TCL>){
		if(/run\s{1}(\d{5}):\s{1}(\d{1,7})\s{1}events/) {
		    my $badrun=$1;
		    my $badevt=$2;
		    $events=$events+$badevt;
		    $badevents=$badevents+$badevt;
		    system ("touch badlumi.txt");
		    system ("lumi -R $badrun | \grep Lumi | \grep Processed | cut -d' ' -f 13-20 >> badlumi.txt");
		    system ("lumi -RB $badrun | \grep Total | cut -d' ' -f 3-20 >> badbcount.txt");
		}
	    }
            open(BAD_LUMI, "badlumi.txt");
	    $lumi=0;
            while (<BAD_LUMI>){
		@inputlumi = split();
##		print "da lumi -> $inputlumi[0]\n";
		$lumi=$lumi+$inputlumi[0];
	    }
	    system ("rm badlumi.txt");
##	    print "sommo... $lumi con $per\n";
	    $badlumival=$badlumival+($lumi*$per);

            open(BAD_BC, "badbcount.txt");
	    $bcount=0;
            while (<BAD_BC>){
		@inputbc = split();
##		print "dal bcount -> $inputbc[0]\n";
		$bcount=$bcount+$inputbc[0];
	    }
	    system ("rm badbcount.txt");
	    $badbcval=$badbcval+($bcount*$per);
	    close (BAD_LUMI);
	    close (BAD_BC);
	}
	close (BAD_TCL);
    }
    close (BADFILE_LOG);
    close (OUT);
    system ("rm lumitot.txt");
    system ("touch lumitot.txt");
    system ("lumi -f runlist.txt | \grep Lumi | \grep Processed | cut -d' ' -f 13-20 > lumitot.txt");
    system ("lumi -fB runlist.txt | \grep Total > bcounttot.txt");
    print "total number of bad events: $badtot\n";
    $good=$tclevents-$badtot;
    print "good events: $good\n";

    open(ALL_LUMI, "lumitot.txt");
    $totlumi=0;
    while (<ALL_LUMI>){
	@inputalllumi = split();
	$totlumi=$inputalllumi[0];
    }
    close (ALL_LUMI);

    print "total luminosity: $totlumi\n";
    print "bad lumi: -$badlumival\n";
    $goodlumi=$totlumi-$badlumival;
    print "good run luminosity: $goodlumi\n";

    open(ALL_BC, "bcounttot.txt");
    $totbc=0;
    while (<ALL_BC>){
	@inputallbc = split();
	$totbc=$inputallbc[1];
    }
    close (ALL_BC);

    print "total number of Bs: $totbc\n";
    print "bad bcount: -$badbcval\n";
    $goodbc=$totbc-$badbcval;
    print "good run B counting: $goodbc\n";

}



