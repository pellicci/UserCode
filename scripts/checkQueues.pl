#!/usr/local/bin/perl -w
#
#use strict;

$wait = 200;

use Getopt::Std;
getopts('t:q:');

$queue = "kanga";

if ($opt_t) {$totalJobs = $opt_t;}
if ($opt_q) {$queue = $opt_q;}

my @jobs = `/usr/local/bin/bjobs -u pellicci -q $queue -p | /bin/grep PEND`;
my $pendJobs = $#jobs;
if ($pendJobs > $wait){
    my $datum = `/bin/date`; chop $datum;
    print "limit: $wait, pending: $pendJobs ($datum)\n";
    sleep 180;
    goto retry;
}

