#!/usr/bin/perl
 
MAIN:
{
    print "starting processing...\n";
        
    system("rm rootout.log");
    system("rm offchargedk.log");
    system("ls scratch/output/ > merge.txt");
    
    print "generating the analysis macro...\n";
    
    open(RUNFILE, ">offchargedk.C");
    print RUNFILE "#include <iostream>\n";
    print RUNFILE "#include <fstream>\n";
    print RUNFILE "#include <string>\n";
    print RUNFILE "#include <stdio.h>\n";
    print RUNFILE "#include <TROOT.h>\n";
    print RUNFILE "#include\"myChargedk.h\"\n";
    print RUNFILE "int main(){\n";
    print RUNFILE "myChargedk *t = new myChargedk();\n";
    print RUNFILE "t->EMCLoop();\n";
    print RUNFILE "return 0;\n}";
    
    close RUNFILE;
    
     print "sourcing the root's\n";
     open(INFILE, "merge.txt") || die "Couldn't open INFILE.\n";
     
     open(OUTFILE, ">out.txt") or die "I cannot create out.txt";
     # Customize here the merger
     print OUTFILE "//=== This file was generated automatically by Mario Pelliccioni of K0LUser package \n";
     print OUTFILE "// === Configuration customization: \n";
     print OUTFILE "{\n";
     print OUTFILE "gSystem->Load(\"libPhysics.so\");\n";
     print OUTFILE "TChain *tree = new TChain(\"h102\");\n\n";
 
     while (<INFILE>){
      @input = split();
      #print "$input[0]\n";
      print OUTFILE "tree->Add(\"scratch/output/$input[0]\");\n";
     }
     close(INFILE);
     print OUTFILE "tree->MakeClass(\"Chargedkbase\");\n";
     print OUTFILE "}";
     
     close (INFILE);
     close (OUTFILE);
     system ("\mv out.txt merger.C");
     system ("\rm out.txt");
    
    system("bbrroot -b -q .x merger.C+ >& rootout.log");
    system("gmake -f Makefile clean");
    system("gmake -f Makefile offchargedk");
    system("bbrbsub -q long -o offchargedk.log offchargedk");
    system("rm merge.txt");
    system("rm merger.C");
    system("rm offchargedk.C");
    system("rm Chargedkbase.C");
    system("rm Chargedkbase.h");
    
    print "wait for the result!!!\n";
       
}
