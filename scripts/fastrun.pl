#!/usr/local/bin/perl

use strict ;
use warnings ;

my @lista_job;

my $queue = $ARGV[0]." ";

if ($queue eq 'xlong' || $queue eq 'long' || $queue eq 'bfobjy' || $queue eq 'kanga'){
   @lista_job = `bjobs -q $ARGV[0]` ;
} else {
   @lista_job = `bjobs` ;
}

my $num_running = 0 ;
my $num_pending = 0 ;
my @job_num = ( ) ;
my $num_stat = 0 ;

foreach my $job ( @lista_job ) {

	chomp ( $job ) ;

	my @item = split ( /\s/ , $job );

	if ( $item[3] eq "PEND" || $item[5] eq "PEND" || $item[4] eq "PEND" || $item[6] eq "PEND") {
	
		push ( @job_num , $item[0] ) ;
		$num_pending++ ;	
	
	}elsif ( $item[3] eq "RUN" || $item[6] eq "RUN" || $item[4] eq "RUN" || $item[5] eq "RUN"){
	
		 $num_running++ ; 	

	}elsif ( $item[3] eq "SSUSP" ){
	
		$num_stat++;
	
	}
}

if ($queue eq 'xlong ' || $queue eq 'long ' || $queue eq 'bfobjy '){
print "\njobs in queue \<$ARGV[0]\>:\n";
} else {
print "\njobs in queues:\n";
}
my $total = $#lista_job ;
print "$total" , "\ttotal jobs\n"; 
print $num_running, "\tRUN\n"; 
print $num_pending, "\tPEND\n";   
print $num_stat, "\tSSUSP\n";
#print "\nDo you want change priority ? ( Y / N )\n";
#my $decision = <>;
#chomp ( $decision );

#if ( $decision eq "Y" ){

#	foreach my $num ( @job_num ) {
	
#		my $command =  "bmod -G babarTrk " ;
#		$command .= $num ;
#		$command .= "\n" ;
#		system("$command" ) ;
#	}
	
#}else{
#	print "Bye\n";
#} 

print "\n";
exit ;
