#!/usr/bin/perl
  
MAIN:
{
 print "starting processing...\n";

 system("ls tempo/ > tempy.txt");
 open(INFILE,"tempy.txt");
 while(<INFILE>){
 @input = split(/\./,$_);
 system("bbrh2root tempo/$input[0].hbook tempo/$input[0].root"); 
 }
 close(INFILE);
 system("rm tempy.txt");
}
    
