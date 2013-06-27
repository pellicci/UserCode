#!/usr/bin/perl
 
MAIN:
{
    print "starting processing...\n";
    
    $ARGV[0] || die "You stupid tell me what to do!!!\n";
    
    if($ARGV[0] eq "kstar"){
     $logfile = "offkstar";
     $analclass = "myDstkstar";
     $classtomake = "Kstarbase";
    }
    
    if($ARGV[0] eq "omega"){
     $logfile = "offomega";
     $analclass = "myDstomega";
     $classtomake = "Omegabase";
    }
    
    system("rm rootout.log");
    system("rm $logfile.log");
    system("ls scratch/output/ > merge.txt");
    
    print "generating the analysis macro...\n";
    
    open(RUNFILE, ">$logfile.C");
    print RUNFILE "#include <iostream>\n";
    print RUNFILE "#include <fstream>\n";
    print RUNFILE "#include <string>\n";
    print RUNFILE "#include <stdio.h>\n";
    print RUNFILE "#include <TROOT.h>\n";
    print RUNFILE "#include\"$analclass.h\"\n";
    print RUNFILE "int main(){\n";
    print RUNFILE "$analclass *t = new $analclass();\n";
    print RUNFILE "t->EMCLoop();\n";
    print RUNFILE "return 0;}";
    
    close RUNFILE;
    
     print "sourcing the root's\n";
     open(INFILE, "merge.txt") || die "Couldn't open INFILE.\n";
     
     open(OUTFILE, ">out.txt") or die "I cannot create out.txt";
     # Customize here the merger
     print OUTFILE "//=== This file was generated automatically by Mario Pelliccioni of K0LUser package \n";
     print OUTFILE "// === Configuration customization: \n";
     print OUTFILE "{\n";
     print OUTFILE "gSystem->Load(\"libPhysics.so\");\n";
     print OUTFILE "TChain *tree = new TChain(\"ntp1\");\n";
 
     while (<INFILE>){
      @input = split();
      #print "$input[0]\n";
      print OUTFILE "tree->Add(\"scratch/output/$input[0]\");\n";
     }
     close(INFILE);
     print OUTFILE "tree->MakeClass(\"$classtomake\");\n";
     print OUTFILE "}";
     
     close (INFILE);
     close (OUTFILE);
     system ("\mv out.txt merger.C");
     system ("\rm out.txt");
    
    system("bbrroot -b -q .x merger.C+ >& rootout.log");
    system("gmake -f Makefile clean");
    system("gmake -f Makefile $logfile");
    system("bbrbsub -q long -o $logfile.log $logfile");
    system("rm merge.txt");
    system("rm merger.C");
    system("rm $logfile.C");
    system("rm $classtomake.C");
    system("rm $classtomake.h");
    
    print "wait for the result!!!\n";
       
}
