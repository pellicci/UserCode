#include <iostream>
#include <math.h>
#include <unistd.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TDatime.h>

using namespace std;

const double Pi = acos(-1.);

int main(int argc, char *argv[]){

  TString outfile = "DDmix.root";
  if (argc!=1) outfile  = (const char *)argv[1],strlen(argv[1]);

  const double minx = -0.015; 
  const double maxx = 0.025;
  const double miny = -0.015;
  const double maxy = 0.025;
  const double minRd = 0.;
  const double maxRd = 0.007;

  TH2D *Hyvsx   = new TH2D("yvsx", "yvsx", 200, minx, maxx, 200, miny, maxy);
  TH1D *Hx = new TH1D("x", "x", 200, minx, maxx);
  TH1D *Hy = new TH1D("y", "y", 200, miny, maxy);
  TH1D *Hdelta_kpi = new TH1D("Hdelta_kpi", "Hdelta_kpi", 200, -180.,180.);
  TH1D *Hdelta_kpipiz = new TH1D("Hdelta_kpipiz", "Hdelta_kpipiz", 200, -180.,180.);
  TH1D *HRd = new TH1D("Rd", "Rd", 200, minRd, maxRd);

  const int NExtractions = 30000000;

  cout << "=========> number of extractions " << NExtractions << endl;
  
  const int jobpid = getpid();
  TDatime *now = new TDatime();
  const int today = now->GetDate();
  const int clock = now->GetTime();
  const int seed = today+clock+jobpid;
  //TRandom3 *gRandom = new TRandom3(seed);
  TRandom3 *gRandom = new TRandom3(52);
  cout << " Seed = " << seed << endl;  
  
  for(int k=1; k<=NExtractions; k++) {
    if(fmod((double)k,NExtractions/100.) == 0) cout << k << " events generated" << endl;

    //const double tauD = gRandom->Gaus(.4101,0.0015); //ps

    //assume a flat prior, rejoice of your humiliation!
    double xprob(1.);

    const double x = minx + (maxx-minx)*gRandom->Rndm();
    const double y = miny + (maxy-miny)*gRandom->Rndm();
    const double delta_kpi = 2.*Pi*gRandom->Rndm() -Pi;
    const double delta_kpipiz = 2.*Pi*gRandom->Rndm() -Pi;
    const double Rd = minRd + (maxRd-minRd)*gRandom->Rndm();;

    //this will allow us to add the Kpi and Kpipi0 results
    const double x_kpi =  x*cos(delta_kpi)+y*sin(delta_kpi);
    const double y_kpi = -x*sin(delta_kpi)+y*cos(delta_kpi);

    const double x_kpipiz =  x*cos(delta_kpipiz)+y*sin(delta_kpipiz);
    const double y_kpipiz = -x*sin(delta_kpipiz)+y*cos(delta_kpipiz);

    //this is for the semileptonic and the K3pi
    const double Rm = (x*x+y*y)/2.;

    //add Kspipi HFAG avg (no correlation)
    xprob *= exp(-0.5*pow((x-0.00811)/0.00334,2.)); // x from threebody
    xprob *= exp(-0.5*pow((y-0.00309)/0.00281,2.)); // y from theebody

    // HFAG avg y_CP
    xprob *= exp(-0.5*pow((y-0.01072)/0.00257,2.));

    //add Rm from semileptonics
    xprob *= exp(-0.5*pow((Rm-0.000130)/0.000269,2.));

    //add Rm from K3pi
    xprob *= exp(-0.5*pow((Rm-0.00019)/0.00016,2.));

    //delta_kpi*sqrt(Rd) from CLEO
    xprob *= exp(-0.5*pow(( cos(delta_kpi)*sqrt(Rd) - 0.08878)/0.03706,2.));

    //add Kpi BaBar with correlation
    double rho_kpi = -0.94;
    double D_xkpi = x_kpi*x_kpi + 0.00022;
    double D_ykpi = y_kpi - 0.0097;

    xprob *= exp(-0.5*(pow(D_xkpi/0.00036,2.) +  pow(D_ykpi/0.0054,2.) - 2*rho_kpi*D_xkpi*D_ykpi/(0.00036*0.0054) ));
    xprob *= exp(-0.5*pow((Rd-0.00303)/0.00018,2.));

    //add Kpi CDF with correlation
    rho_kpi = -0.984;
    D_xkpi = x_kpi*x_kpi + 0.00012;
    D_ykpi = y_kpi - 0.0085;

    xprob *= exp(-0.5*(pow(D_xkpi/0.00035,2.) +  pow(D_ykpi/0.0076,2.) - 2*rho_kpi*D_xkpi*D_ykpi/(0.00035*0.0076) ));
    xprob *= exp(-0.5*pow((Rd-0.00304)/0.00055,2.));

    //add Kpi from Belle with correlation
    rho_kpi = -0.91;
    D_xkpi = x_kpi*x_kpi - 0.00018;
    D_ykpi = y_kpi - 0.0006;

    xprob *= exp(-0.5*(pow(D_xkpi/0.00023,2.) +  pow(D_ykpi/0.0040,2.) - 2*rho_kpi*D_xkpi*D_ykpi/(0.00023*0.0040) ));
    xprob *= exp(-0.5*pow((Rd-0.00364)/0.00017,2.));

    //adding our result!
    double rho_kpipiz = -0.75;
    double D_xkpipiz = x_kpipiz - 0.0261;
    double D_ykpipiz = y_kpipiz + 0.0006;

    //xprob *= exp(-0.5*(pow(D_xkpipiz/0.0078,2.) +  pow(D_ykpipiz/0.0072,2.) - 2*rho_kpipiz*D_xkpipiz*D_ykpipiz/(0.0078*0.0072) ));

    Hyvsx->Fill(x,y,xprob);
    Hx->Fill(x,xprob);
    Hy->Fill(y,xprob);
    Hdelta_kpi->Fill(delta_kpi*180./Pi,xprob);
    Hdelta_kpipiz->Fill(delta_kpipiz*180./Pi,xprob);
    HRd->Fill(Rd,xprob);

  }

  TFile *output = new TFile(outfile,"RECREATE");
  output->cd();
  
  output->mkdir("Input","some input distributions");
  output->cd("Input");  

  Hyvsx->Write();
  Hx->Write();
  Hy->Write();
  Hdelta_kpi->Write();
  Hdelta_kpipiz->Write();
  HRd->Write();

  output->Close();

  return 1;
}
