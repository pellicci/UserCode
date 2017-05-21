#!/usr/bin/perl
  
MAIN:
{
    print "starting processing...\n";

    open(INFILE, $ARGV[0]) || die "Couldn't open INFILE.\n";
    while (<INFILE>){

    @input = split(/\//,$_);
    @inputname = split(/\./,$input[10]);
    
    $rootfile = $inputname[0];
     $analtcl = "MCK0LRecoD0_KstarPi.tcl";

    print $input[10];
       
    open(OUTFILE, ">datamooseTcl/$rootfile.tcl");
     
    print OUTFILE "# === This file was generated automatically by generateTcl_DstarToKLomega_style.pl of K0LUser package \n";
    print OUTFILE "# === Framework Configuration Variables customization: \n";
    print OUTFILE "set BetaMicro \"yes\" \n";
    print OUTFILE "set BetaSaveMC \"yes\" \n";
    print OUTFILE "set ConfigMC \"yes\" \n";
    print OUTFILE "set ThisIsABEvent \"yes\" \n";
    print OUTFILE "# === End of customization \n\n\n";
    # End customization
    $RootDir ="scratch/output/";
    $rootyfile="$RootDir"."$rootfile".".root";
    print OUTFILE "set RootFilename $rootyfile \n\n\n";
#    print OUTFILE "lappend inputList /nfs/farm/babar/AWG26/mario/mc_dstard0kpipi/$rootfile\n";
    print OUTFILE "lappend inputList /a/surrey04/vol/vol0/bbrwork/d/dimarcoe/output/$rootfile\n";
    print OUTFILE "sourceFoundFile K0LUser/$analtcl \n";
    close (OUTFILE);

    
    }
    
    
    
    
}
