#!/usr/bin/perl
  
MAIN:
{
    print "starting processing...\n";
    $contatore =0;    
    
    $ARGV[0] || die "You stupid tell me what to do!!!\n";
    
    if($ARGV[0] eq "kstar"){
     $decayfile = "ccbar_Dstar+_D0pi_D0Kstarrho.dec";
     $moosefile = "mykstarmoose.hbook";
     $mooseoutput = "dstarkstarrho-";
     $moosetcl = "Dstarkstar-";
    }

    if($ARGV[0] eq "omega"){
     $decayfile = "ccbar_Dstar+_D0pi_D0Komega.dec";
     $moosefile = "myomegamoose.hbook";
     $mooseoutput = "dstaromega-";
     $moosetcl = "Dstaromega-";
    }
    
    while($contatore < '100'){
     open(OUTFILE, ">moosetcl/$moosetcl$contatore.tcl");
     print OUTFILE "set ProdTclOnly              true\n";
     print OUTFILE "set RUNNUM 957099655\n";
     print OUTFILE "set CONDALIAS Aug2001\n";
     print OUTFILE "set NEVENT  1000\n";
     print OUTFILE "set UFILTER \"D*+ D*-\"\n";
     print OUTFILE "set UDECAY $decayfile\n";
     print OUTFILE "set GENERATE continuum\n";
     print OUTFILE "set MooseHBookFile  moosehbook/$moosefile\n";
     print OUTFILE "set MooseOutputCollection  scratch/$mooseoutput".$contatore."\n";
     print OUTFILE "mod talk KanEventOutput\n";
     print OUTFILE "  allowDirectoryCreation set true\n";
     print OUTFILE "exit\n";
     print OUTFILE "module talk HbkTupleEnv\n";
     print OUTFILE "  outputFile set false\n";
     print OUTFILE "exit\n\n";
     print OUTFILE "sourceFoundFile  Moose/MooseProduction.tcl\n";
     
     close OUTFILE;
     
     $contatore++;
    
    }
    
    print "I wrote your moose tcls!";
    
}
