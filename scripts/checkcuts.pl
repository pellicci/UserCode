#!/usr/local/bin/perl

MAIN:
{
  print "sourcing the logs's\n";
  open(INFILE, $ARGV[0]) || die "Couldn't open INFILE.\n";
  $pi_vtx = 0;
  $truepi_vtx = 0;
  $nDOFpi_vtx = 0;
  $truenDOFpi_vtx = 0;
  $probpi_vtx = 0;
  $trueprobpi_vtx = 0;
  $dxydz = 0;
  $truedxydz = 0;
  $ecal = 0;
  $trueecal = 0;
  $klmom = 0;
  $trueklmom = 0;
  $D0fit = 0;
  $trueD0fit = 0;
  $pstar = 0;
  $truepstar = 0;
  $Dstarfit = 0;
  $trueDstarfit = 0;
  $deltam = 0;
  $truedeltam = 0;

  while (<INFILE>) {
    @input = split();
    open(INTWO, "$input[0]");

    while (<INTWO>) {
      if (/pi_vtx : (\d+)/) { $pi_vtx = $1 + $pi_vtx; }
      if (/pi_vtx : (\d+)e\+(\i+)/) { $pi_vtx = $1*exp($2*log(10)) + $pi_vtx; }
      
      if (/truepi_vtx : (\d+)/) { $truepi_vtx = $1 + $truepi_vtx; }
      if (/truepi_vtx : (\d+)e\+(\i+)/) { $truepi_vtx = $1*exp($2*log(10)) + $truepi_vtx; }
      
      if (/nDOFpi_vtx : (\d+)e\+(\i+)/) { $nDOFpi_vtx = $1*exp($2*log(10)) + $nDOFpi_vtx; }
      if (/nDOFpi_vtx : (\d+)/) { $nDOFpi_vtx = $1 + $nDOFpi_vtx; }

      if (/truenDOFpi_vtx : (\d+)/) { $truenDOFpi_vtx = $1 + $truenDOFpi_vtx; }
      if (/truenDOFpi_vtx : (\d+)e\+(\i+)/) { $truenDOFpi_vtx = $1*exp($2*log(10)) + $truenDOFpi_vtx; }
 
      if (/probpi_vtx : (\d+)/) { $probpi_vtx = $1 + $probpi_vtx; }
      if (/probpi_vtx : (\d+)e\+(\i+)/) { $probpi_vtx = $1*exp($2*log(10)) + $probpi_vtx; }

      if (/trueprobpi_vtx : (\d+)/) { $trueprobpi_vtx = $1 + $trueprobpi_vtx; }
      if (/trueprobpi_vtx : (\d+)e\+(\i+)/) { $trueprobpi_vtx = $1*exp($2*log(10)) + $trueprobpi_vtx; }

      if (/dxydz : (\d+)/) { $dxydz = $1 + $dxydz; }
      if (/dxydz : (\d+)e\+(\i+)/) { $dxydz = $1*exp($2*log(10)) + $dxydz; }

      if (/truedxydz : (\d+)/) { $truedxydz = $1 + $truedxydz; }
      if (/truedxydz : (\d+)e\+(\i+)/) { $truedxydz = $1*exp($2*log(10)) + $truedxydz; }

      if (/ecal : (\d+)/) { $ecal = $1 + $ecal; }
      if (/ecal : (\d+)e\+(\i+)/) { $ecal = $1*exp($2*log(10)) + $ecal; }
      
      if (/trueecal : (\d+)/) { $trueecal = $1 + $trueecal; }
      if (/trueecal : (\d+)e\+(\i+)/) { $trueecal = $1*exp($2*log(10)) + $trueecal; }
      
      if (/klmom : (\d+)/) { $klmom = $1 + $klmom; }
      if (/klmom : (\d+)e\+(\i+)/) { $klmom = $1*exp($2*log(10)) + $klmom; }
      
      if (/trueklmom : (\d+)/) { $trueklmom = $1 + $trueklmom; }
      if (/trueklmom : (\d+)e\+(\i+)/) { $trueklmom = $1*exp($2*log(10)) + $trueklmom; }
      
      if (/D0fit : (\d+)/) { $D0fit = $1 + $D0fit; }
      if (/D0fit : (\d+)e\+(\i+)/) { $D0fit = $1*exp($2*log(10)) + $D0fit; }
      
      if (/trueD0fit : (\d+)/) { $trueD0fit = $1 + $trueD0fit; }
      if (/trueD0fit : (\d+)e\+(\i+)/) { $trueD0fit = $1*exp($2*log(10)) + $trueD0fit; }
      
      if (/pstar : (\d+)/) { $pstar = $1 + $pstar; }
      if (/pstar : (\d+)e\+(\i+)/) { $pstar = $1 + $pstar; }
      
      if (/truepstar : (\d+)/) { $truepstar = $1 + $truepstar; }
      if (/truepstar : (\d+)e\+(\i+)/) { $truepstar = $1*exp($2*log(10)) + $truepstar; }
      
      if (/Dstarfit : (\d+)/) { $Dstarfit = $1 + $Dstarfit; }
      if (/Dstarfit : (\d+)e\+(\i+)/) { $Dstarfit = $1*exp($2*log(10)) + $Dstarfit; }
      
      if (/trueDstarfit : (\d+)/) { $trueDstarfit = $1 + $trueDstarfit; }
      if (/trueDstarfit : (\d+)e\+(\i+)/) { $trueDstarfit = $1*exp($2*log(10)) + $trueDstarfit; }
      
      if (/deltam : (\d+)/) { $deltam = $1 + $deltam; }
      if (/deltam : (\d+)e\+(\i+)/) { $deltam = $1*exp($2*log(10)) + $deltam; }
      
      if (/truedeltam : (\d+)/) { $truedeltam = $1 + $truedeltam; }
      if (/truedeltam : (\d+)e\+(\i+)/) { $truedeltam = $1*exp($2*log(10)) + $truedeltam; }
      
    }

    close(INTWO);

  }

  print "pi_vtx: $pi_vtx\n";
  print "truepi_vtx: $truepi_vtx\n";
  print "nDOFpi_vtx: $nDOFpi_vtx\n";
  print "truenDOFpi_vtx: $truenDOFpi_vtx\n";
  print "probpi_vtx: $probpi_vtx\n";
  print "trueprobpi_vtx: $trueprobpi_vtx\n";
  print "dxydz: $dxydz\n";
  print "truedxydz: $truedxydz\n";
  print "ecal: $ecal\n";
  print "trueecal: $trueecal\n";
  print "klmom: $klmom\n";
  print "trueklmom: $trueklmom\n";
  print "D0fit: $D0fit\n";
  print "trueD0fit: $trueD0fit\n";
  print "pstar: $pstar\n";
  print "truepstar: $truepstar\n";
  print "Dstar_fit: $Dstarfit\n";
  print "true Dstar_fit: $trueDstarfit\n";
  print "deltam: $deltam\n";
  print "truedeltam: $truedeltam\n";

  close(INFILE);
  
  
}
