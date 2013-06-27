#!/usr/bin/perl

MAIN:
{
    print "sourcing the tcl's\n";
    open(INFILE, $ARGV[0]) || die "Couldn't open INFILE.\n";
    while (<INFILE>){
        @input = split(/\//,$_);
        @inputTcl = split(/\.tcl/,$input[1]);
	print "$input[0]/$input[1]/$inputTcl[0].tcl\n";
	open(TMPFILE, $_);
	while (<TMPFILE>){
	  if (/\#\# Total events selected: (\d+)/) {
		system ("SubmitJobs $inputTcl[0] $ARGV[1]");
	    }
	}
	close (TMPFILE);
    }
    close (INFILE);
}
