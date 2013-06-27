#!/usr/bin/perl

MAIN:
{
    print "sourcing the root's\n";
    open(INFILE, $ARGV[0]) || die "Couldn't open INFILE.\n";
    
    open(OUTFILE, ">out.txt") or die "I cannot create out.txt";
    # Customize here the merger
    print OUTFILE "//=== This file was generated automatically by Mario Pelliccioni of K0LUser package \n";
    print OUTFILE "// === Configuration customization: \n";
    print OUTFILE "{\n";
    print OUTFILE "gSystem->Load(\"libPhysics.so\");\n";
    print OUTFILE "TChain *tree = new TChain(\"ntp1\");\n";

    while (<INFILE>){
        @input = split();
	print "$input[0]\n";
	print OUTFILE "tree->Add(\"scratch/output/$input[0]\");\n";
    }
    close(INFILE);
    print OUTFILE "tree->MakeClass(\"Omegabase\");\n";
    print OUTFILE "}";
    
    close (INFILE);
    close (OUTFILE);
    system ("\mv out.txt mergeomega.C");
    system ("\rm out.txt");

}
