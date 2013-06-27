#!/usr/bin/perl
#
# Author: Emanuele Di Marco
#

use Getopt::Std;
getopts('hd:');

print "Starting...\n";

if($opt_d){
        @LS=qx/ls -1 $opt_d/;
        @LIST=@LS;
} else {
        @LIST=@ARGV;
}
if($opt_h){help();}

$n_tcl=0;
foreach $tclfile (@LIST) {
  $n_tcl++;
  if($opt_d){
    $tclfile=$opt_d."/".$tclfile;
  }
  print "processing $tclfile...\n";

  open(INFILE,$tclfile);
  @infile=<INFILE>;
  close(INFILE);
  open(OUTFILE, ">out.txt") or die "I cannot create out.txt";
  # Customize here Framework Configuration Variables
  print OUTFILE "# === This file was generated automatically by generateTcl_DstarToKLomega_style.pl of K0LUser package \n";
  print OUTFILE "# === Framework Configuration Variables customization: \n";
  print OUTFILE "set BetaMicro \"yes\" \n";
  print OUTFILE "set BetaSaveMC \"yes\" \n";
  print OUTFILE "set ConfigMC \"yes\" \n";
  print OUTFILE "set ThisIsABEvent \"yes\" \n";
  # uncomment next 2 lines if you want run the SVT mis-alignment systematics
  #  print OUTFILE "set levelOfDetail \"refit\" \n";
  #  print OUTFILE "source maBoost.tcl \n";

  print OUTFILE "# === End of customization \n\n\n";
  # End customization
  $RootDir ="scratch/output/";
  ($barefile = $tclfile) =~ s/\.tcl//g;
  $rest = substr($barefile, 0, rindex($barefile, '/')+1);
  $barefile =~ s/$rest//;
  $rootfile="$RootDir"."omega"."$barefile".".root";
  print OUTFILE "set RootFilename $rootfile \n\n\n";
  $i+=0;
  for ($i=0;$i<($#infile+1);$i++){
    #    if ($infile[$i] =~ /lappend\sinputList\s(\S+)/){
    print OUTFILE "$infile[$i]";
    #    }
  }
  print OUTFILE "sourceFoundFile K0LUser/K0LRecoD0_KLomega.tcl \n";
  close (OUTFILE);
  system ("\mv out.txt omegaMCTcl/$barefile.tcl");
  system ("\rm out.txt");
}

sub help(){
  print "Options: \n";
  print "-d: directory with all tclfiles \n";
  print "Usage: \n";
  print "Customize your Framework Configuration Variables in this script \n";
  print "generateTcl_DstarToKLomega_style.pl tcl1, tcl2, ... tcln \n";
  print "or:\n";
  print "generateTcl_DstarToKLomega_style.pl -d tcldir/ \n";
  die "enjoy running your CM2 analysis!\n\n";
}


