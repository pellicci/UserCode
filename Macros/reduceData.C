#define reduceData_cxx
#include "reduceData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "../EvtGenBase/EvtDalitzPlot.hh"
#include "../EvtGenBase/EvtDalitzPoint.hh"

void reduceData::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L reduceData.C
//      Root > reduceData t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
  Int_t D0flav = 0;
  Int_t myisWS = 0;
  Int_t mytag_opp_side = 0;
   Double_t pi0p3 = 0.;
   Double_t myd0Lifetime = 0.;
   Double_t myd0LifetimeErr = 0.;
   Double_t myrunnumber = 0.;
   Int_t mytruthIsSignal = 0;
   Int_t mytruthIsBkg_FakePiSlow = 0;

   Int_t tag_K = 0;
   Int_t tag_pi = 0;
   Int_t tag_e = 0;
   Int_t tag_mu = 0;

//define DalitzSpace for generation
   EvtPDL pdl;
   pdl.readPDT("evt.pdl");
   EvtDecayMode mode("D0 -> K- pi+ pi0");
   EvtDalitzPlot dalitzSpace(mode);

   TFile *file = new TFile("Data.root","RECREATE");
   TTree *reduced = new TTree("ntp3","The data tree");
   reduced->Branch("d0Mass",&d0Mass,"d0Mass/D");
   reduced->Branch("deltaMass",&deltaMass,"deltaMass/D");
   reduced->Branch("d0P_phi",&d0P_phi,"d0P_phi/D");
   reduced->Branch("d0P_theta",&d0P_theta,"d0P_theta/D");
   reduced->Branch("m2Kpi_d0mass",&m2Kpi_d0mass,"m2Kpi_d0mass/D");
   reduced->Branch("m2Kpi0_d0mass",&m2Kpi0_d0mass,"m2Kpi0_d0mass/D");
   reduced->Branch("m2pipi0_d0mass",&m2pipi0_d0mass,"m2pipi0_d0mass/D");
   reduced->Branch("d0Lifetime",&myd0Lifetime,"d0Lifetime/D");
   reduced->Branch("d0LifetimeErr",&myd0LifetimeErr,"d0LifetimeErr/D");
   reduced->Branch("D0flav",&D0flav,"D0flav/I");
   //reduced->Branch("pi0Pmag",&pi0Pmag,"pi0Pmag/D");
   reduced->Branch("isWS",&myisWS,"isWS/I");
   reduced->Branch("tag_opp_side",&mytag_opp_side,"tag_opp_side/I");
   reduced->Branch("runnumber",&myrunnumber,"runnumber/D");
   //reduced->Branch("tag_K",&tag_K,"tag_K/I");
   //reduced->Branch("tag_pi",&tag_pi,"tag_pi/I");
   //reduced->Branch("tag_e",&tag_e,"tag_e/I");
   //reduced->Branch("tag_mu",&tag_mu,"tag_mu/I");
   reduced->Branch("truthIsSignal",&mytruthIsSignal,"truthIsSignal/I");
   reduced->Branch("truthIsBkg_FakePiSlow",&mytruthIsBkg_FakePiSlow,"truthIsBkg_FakePiSlow/I");

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;

     if(isAntiD0==0) D0flav = -1;
     if(isAntiD0==1) D0flav = 1;
     if(isWS==0) myisWS = 0;
     if(isWS==1) myisWS = 1;
     //if(tag_opp_side != 1) continue;

     mytag_opp_side = tag_opp_side;
     mytruthIsSignal = truthIsSignal;
     mytruthIsBkg_FakePiSlow = truthIsBkg_FakePiSlow;

     myd0Lifetime = d0Lifetime*pow(10.,12.);
     myd0LifetimeErr = d0LifetimeErr*pow(10.,12.);
     myrunnumber = (Double_t)runnumber;

     EvtDalitzPoint *_dalitzPoint = new EvtDalitzPoint(dalitzSpace.mA(),dalitzSpace.mB(),dalitzSpace.mC(),m2Kpi_d0mass,m2pipi0_d0mass,m2Kpi0_d0mass);
     if(!_dalitzPoint->isValid()) continue;

     if(tag_k_cms_p > 0.) tag_K = 1;
     else tag_K = 0;
     if(tag_spi_pchi2 > 0.001 && tag_spi_dss_pt < 0.08 && tag_spi_dss_pl > -0.080 && tag_spi_dss_pl < 0.075 && tag_spi_dss_p < 0.09 && tag_spi_dss_p > 0.)
       tag_pi = 1;
     else tag_pi = 0;
     if(tag_e_m2 > 0.01 && tag_e_cms_p > 0.) tag_e = 1;
     else tag_e = 0;
     if(tag_mu_cms_p > 0.) tag_mu = 1;
     else tag_mu = 0;

     if(!(d0pstar > 2.4 && pi0Pmag > 0.35 && dstarChi2Prob > 0.01 && d0Chi2ProbPre > 0.005)) continue;

     //if(truthIsSignal == 0) continue;

     reduced->Fill();
   }
    file->cd();
   reduced->Write();
   file->Close();
}
