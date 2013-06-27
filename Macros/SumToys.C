#define SumToys_cxx
#include "SumToys.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void SumToys::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L SumToys.C
  //      Root > SumToys t
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

  TFile *file = new TFile("toy_tmp.root","RECREATE");
  TTree *reduced = new TTree("fitParData","");
  /*
  reduced->Branch("c1p",&c1p,"c1p/D");
  reduced->Branch("c1perr",&c1perr,"c1perr/D");
  reduced->Branch("c1ppull",&c1ppull,"c1ppull/D");
  reduced->Branch("c2p",&c2p,"c2p/D");
  reduced->Branch("c2perr",&c2perr,"c2perr/D");
  reduced->Branch("c2ppull",&c2ppull,"c2ppull/D");

  reduced->Branch("c1m",&c1m,"c1m/D");
  reduced->Branch("c1merr",&c1merr,"c1merr/D");
  reduced->Branch("c1mpull",&c1mpull,"c1mpull/D");
  reduced->Branch("c2m",&c2m,"c2m/D");
  reduced->Branch("c2merr",&c2merr,"c2merr/D");
  reduced->Branch("c2mpull",&c2mpull,"c2mpull/D");
  */
  reduced->Branch("c1",&c1,"c1/D");
  reduced->Branch("c1err",&c1err,"c1err/D");
  reduced->Branch("c1pull",&c1pull,"c1pull/D");
  reduced->Branch("c2",&c2,"c2/D");
  reduced->Branch("c2err",&c2err,"c2err/D");
  reduced->Branch("c2pull",&c2pull,"c2pull/D");
  
  reduced->Branch("Kstminus_amp",&Kstminus_amp,"Kstminus_amp/D");
  reduced->Branch("Kstminus_amperr",&Kstminus_amperr,"Kstminus_amperr/D");
  reduced->Branch("Kstminus_amppull",&Kstminus_amppull,"Kstminus_amppull/D");
  reduced->Branch("Kstminus_phase",&Kstminus_phase,"Kstminus_phase/D");
  reduced->Branch("Kstminus_phaseerr",&Kstminus_phaseerr,"Kstminus_phaseerr/D");
  reduced->Branch("Kstminus_phasepull",&Kstminus_phasepull,"Kstminus_phasepull/D");

  reduced->Branch("Kstzero_amp",&Kstzero_amp,"Kstzero_amp/D");
  reduced->Branch("Kstzero_amperr",&Kstzero_amperr,"Kstzero_amperr/D");
  reduced->Branch("Kstzero_amppull",&Kstzero_amppull,"Kstzero_amppull/D");
  reduced->Branch("Kstzero_phase",&Kstzero_phase,"Kstzero_phase/D");
  reduced->Branch("Kstzero_phaseerr",&Kstzero_phaseerr,"Kstzero_phaseerr/D");
  reduced->Branch("Kstzero_phasepull",&Kstzero_phasepull,"Kstzero_phasepull/D");

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    reduced->Fill();
  }
  reduced->Write();
  file->Close();
}
