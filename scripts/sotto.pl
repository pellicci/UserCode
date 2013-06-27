#!/usr/bin/perl

MAIN:
{

  print "starting processing...\n";

  $ARGV[0] || die "You stupid tell me what to do!!!\n";

  if ($ARGV[0] eq "segnale") {
    $tclfile = "datamooseTcl/dstard0kpipi";
    $logfile = "dstard0kpipi";
    $stop = 200;
  }

  if ($ARGV[0] eq "ccbar") {
    $tclfile = "ccbarMCTcl/ccbar-";
    $logfile = "ccbar-";
    $stop = 2000;
  }

  $attesa = 999; if ($opt_a) {$attesa = $opt_a;}

  print "sourcing the tcl's\n";
  $start = 1;
  $contaconta = 0;

  while ($start < $stop) {

    if ($contaconta == 0) {
      my @jobs = `/usr/local/bin/bjobs -u $user -q $queue -p | /bin/grep PEND`;
      $pendJobs = $#jobs;
    }
    $contaconta = 1;

    if ($pendJobs < $attesa) {

      $itera = 0;

      while ($itera < $attesa) {
	system("bbrbsub -o scratch/log/$logfile$start.log -q kanga K0LMiniUser $tclfile$start.tcl");
	$start = $start + 1;
	$itera = $itera + 1;
      }
    }

    if ($pendJobs > $attesa) {

      print "Total Jobs:$stop --- Job Submitted: $start --- Job Pending: $pendjobs";
      sleep 300;
      $contaconta = 0;
    }
  }

}
