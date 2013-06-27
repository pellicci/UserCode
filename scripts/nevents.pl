#!/usr/local/bin/perl

MAIN:
{
    print "sourcing the logs's\n";
    open(INFILE, $ARGV[0]) || die "Couldn't open INFILE.\n";
    $risultato = 0;
    while (<INFILE>){
     @input = split();
     open(INTWO, "./scratch/log/".$input[0]);
     
     while(<INTWO>){
      if (/total number of events=(\d+)/) {
      $risultato = $1 + $risultato;
      }
     }
   
    close(INTWO);
   
   }
   
  print "number of events: $risultato\n";
  
  close(INFILE);
  
  
}
