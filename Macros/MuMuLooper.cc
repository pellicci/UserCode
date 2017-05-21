#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TGraph.h>

#include <iostream>
#include <iomanip>
#include <string.h>

#include <math.h>

#include "MuMuLooper.hh"

using namespace std;


MuMuLooper::MuMuLooper(TChain *tree) 
  : smallHBaseClass(tree) {

  onlyTheBest = true;

  /// SELECTION CUTS ///
 
  MIN_nhits_trk = 12;
  MAX_normchi2_trk = 5.0;
  MAX_normchi2_glb = 20.0;
  MIN_nhits_pixel = 2;
  MAX_d0_trk = 2.0;
  MAX_dz_trk = 25.0;
  MIN_vtxprob = 0.05;
  MAX_S3Dip = 1.1;
  MAX_muisol = 0.11;
  MIN_muP = 4.4;
  bookHistos();
}

void MuMuLooper::bookHistos()
{
  hInvMass = new TH1F("hInvMass","#mu-#mu invariant mass",200,4.,12.);
//   hIsoVar03_glb_TKECAL1 = new TH1F("hIsoVar03_glb_TKECAL1", "isolation var03 on tk+ecal, glb", 200, 0., 5. );
//   hIsoVar03_glb_TKECAL2 = new TH1F("hIsoVar03_glb_TKECAL2", "isolation var03 on tk+ecal, glb", 200, 0., 5. );
//   hIsoVar03_trk_TKECAL1 = new TH1F("hIsoVar03_trk_TKECAL1", "isolation var03 on tk+ecal, trk", 200, 0., 5. );
//   hIsoVar03_trk_TKECAL2 = new TH1F("hIsoVar03_trk_TKECAL2", "isolation var03 on tk+ecal, trk", 200, 0., 5. );
//   hIsoVar03_glb_TK = new TH1F("hIsoVar03_glb_TK", "isolation var03 on tk, glb", 200, 0., 5. );
//   hIsoVar03_trk_TK = new TH1F("hIsoVar03_trk_TK", "isolation var03 on tk, trk", 200, 0., 5. );
//   hIsoVar03_glb_ECAL = new TH1F("hIsoVar03_glb_ECAL", "isolation var03 on ecal, glb", 200, 0., 5. );
//   hIsoVar03_trk_ECAL = new TH1F("hIsoVar03_trk_ECAL", "isolation var03 on ecal, trk", 200, 0., 5. );
  hQQProbChi2 = new TH1F("hQQProbChi2","#chi^2 prob", 50, 0., 1.);
  hQQS3Dip = new TH1F("hQQS3Dip", "", 100, 0., 5.);
  hQQSTip = new TH1F("hQQSTip", "", 100, 0., 5.);
  hQQEta = new TH1F("hQQEta", "Eta", 100, -5.,5.);
  hQQPt = new TH1F("hQQPt", "Pt", 100, 0., 50.);
  hMuEtaTk = new TH1F("hMuEtaTk","Muon Eta Tk", 100, -5., 5.);
  hMuPtTk = new TH1F("hMuPtTk","Muon Pt Tk", 100, 0., 50.);
  hMuEtaGlb = new TH1F("hMuEtaGlb","Muon Eta Glb", 100, -5., 5.);
  hMuPtGlb = new TH1F("hMuPtGlb","Muon Pt Glb", 100, 0., 50.);

  hMuPGlb = new TH1F("hMuPGlb","Muon P Glb", 100, 0., 50.);
  hMuPTk = new TH1F("hMuPTk","Muon P Tk", 100, 0., 50.);

  return;
}

void MuMuLooper::Loop() {

  if (fChain == 0) return;  
  int nentries = (int)fChain->GetEntries(); 

  // loop over events
  cout << "Number of entries = " << nentries << endl;

  // counters
  int totalEvents = 0;
  int passedCandidates = 0;
  int passedTriggers = 0;

  for (int jentry=0; jentry< nentries; jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    fChain->GetEntry(jentry);

    if (jentry%100000 == 0) cout << ">>> Processing event # " << jentry << endl;
    
    totalEvents++;


    passedTriggers++;

    TString filestring(fChain->GetCurrentFile()->GetName());

    //FIXME to be defined
    weight = 1.;
//     if (filestring.Contains("SimpleTree_ppMuX"))
//       weight = 4080.96;
//     else if (filestring.Contains("SimpleTree_Upsilon1S"))
//       weight = 70;
//     else if (filestring.Contains("SimpleTree_Upsilon2S"))
//       weight = 28;
//     else if (filestring.Contains("SimpleTree_Upsilon3S")) 
//       weight = 8;
//     else if (filestring.Contains("SimpleTree_A0_8GEV"))
//       weight = 0.12766; 
//     else if (filestring.Contains("SimpleTree_A0_10GEV"))
//       weight = 0.319149;
    
    // Find the best candidate (if needed)
    int myBest = 0;
    if (onlyTheBest) myBest = theBestQQ();

    for (int iqq=0; iqq<(*QQ_size)[0]; iqq++) {

      if ((*QQ_sign)[iqq] != 0) continue;//change here for opposite sign !=, for same sign ==

      if((*QQ_type)[iqq] == 0) continue;

      hQQProbChi2->Fill(QQ_probChi2 -> at(iqq));
      hQQS3Dip -> Fill(QQ_S3Dip -> at(iqq));
      hQQSTip  -> Fill(QQ_STip -> at(iqq) );
      hQQEta->Fill(((TLorentzVector*)QQ_4mom->At(iqq))->Eta());
      hQQPt->Fill(((TLorentzVector*)QQ_4mom->At(iqq))->Pt());
      hQQEta->Fill(((TLorentzVector*)QQ_4mom->At(iqq))->Eta());
      hQQPt->Fill(((TLorentzVector*)QQ_4mom->At(iqq))->Pt());

      if (onlyTheBest && iqq != myBest) continue;

      passedCandidates++;
      
      const float invMass = ((TLorentzVector*)QQ_4mom->At(iqq))->M();
      
	
      // Fill histos
      hInvMass->Fill(invMass, weight);

     //hIsoVar03_glb_TKECAL1->Fill(muons_glb_tkIsoR03->at(mu_index)/mu_4mom->Pt()+muons_glb_emIsoR03->at(mu_index));
     //hIsoVar03_glb_TKECAL2->Fill((muons_glb_tkIsoR03->at(mu_index)+muons_glb_emIsoR03->at(mu_index))/mu_4mom->Pt());
     //hIsoVar03_glb_TK->Fill(muons_glb_tkIsoR03->at(mu_index)/mu_4mom->Pt());
     //hIsoVar03_glb_ECAL->Fill(muons_glb_emIsoR03->at(mu_index));

     //hIsoVar03_trk_TKECAL1->Fill(muons_trk_tkIsoR03->at(mu_index)/mu_4mom->Pt()+muons_trk_emIsoR03->at(mu_index));
     //hIsoVar03_glb_TKECAL2->Fill((muons_trk_tkIsoR03->at(mu_index)+muons_trk_emIsoR03->at(mu_index))/mu_4mom->Pt());
     //hIsoVar03_trk_TK->Fill(muons_trk_tkIsoR03->at(mu_index)/mu_4mom->Pt());
     //hIsoVar03_trk_ECAL->Fill(muons_trk_emIsoR03->at(mu_index));

    
    }

  }//end loop on events
  
  cout << "###############" << endl;
  cout << "Some statistics " << endl;
  cout << "Total number of processed events = " << totalEvents << endl;
  cout << "Total number of triggered events = " << passedTriggers << endl;
  cout << "Total number of selected  events = " << passedCandidates << endl;
  cout << "###############" << endl;
  cout << "Total number of events scaled = " << hInvMass->Integral() << endl;

  return;
} // end of program

void MuMuLooper::saveHistos(TFile * f1)
{
  f1->cd();

  hInvMass->Write();
//   hIsoVar03_glb_TKECAL1->Write();
//   hIsoVar03_glb_TKECAL2->Write();
//   hIsoVar03_trk_TKECAL1->Write();
//   hIsoVar03_trk_TKECAL2->Write();
//   hIsoVar03_glb_TK->Write();
//   hIsoVar03_glb_ECAL->Write();
//   hIsoVar03_trk_TK->Write();
//   hIsoVar03_trk_ECAL->Write();
  hQQProbChi2->Write();
  hQQSTip->Write();
  hQQS3Dip->Write();
  hQQEta->Write()   ;
  hQQPt->Write()    ;
  hMuEtaTk->Write()   ;
  hMuPtTk->Write()    ;
  hMuEtaGlb ->Write()  ;
  hMuPtGlb->Write()    ;
  hMuPGlb->Write();
  hMuPTk->Write();

  f1->Close();

  return;
}


bool MuMuLooper::accept_glb_mu(const int mu_index) const
{
  TLorentzVector *mu_4mom = (TLorentzVector*)muons_glb_4mom->At(mu_index);
  if(muons_glb_nhitstrack->at(mu_index) > MIN_nhits_trk     &&
     muons_glb_normChi2->at(mu_index)   < MAX_normchi2_glb  &&
     fabs(muons_glb_d0->at(mu_index))   < MAX_d0_trk        &&
     fabs(muons_glb_dz->at(mu_index))   < MAX_dz_trk        &&
     (((muons_glb_nhitsPixB->at(mu_index) + muons_glb_nhitsPixE->at(mu_index)) > MIN_nhits_pixel) ||
      ((muons_glb_nhitsPixB->at(mu_index) + muons_glb_nhitsPixE->at(mu_index)) > MIN_nhits_pixel-1 && muons_glb_nhitsPix1Hit->at(mu_index) == 1)) && 
     (muons_glb_tkIsoR03->at(mu_index)+muons_glb_emIsoR03->at(mu_index))/mu_4mom->Pt() < MAX_muisol){
    hMuPtGlb->Fill(mu_4mom->Pt());
    hMuEtaGlb->Fill(mu_4mom->Eta()); 
    if(fabs(mu_4mom->Eta()) > 1.1){
      hMuPGlb->Fill(mu_4mom->Rho());
      hMuPGlb->Fill(mu_4mom->Rho()); 
    }
    return true;
  }
    
  return false;
}

bool MuMuLooper::accept_trk_mu(const int mu_index) const
{
  TLorentzVector *mu_4mom = (TLorentzVector*)muons_trk_4mom->At(mu_index);
  if(mu_4mom->Eta() > 1.1 && mu_4mom->Rho() < MIN_muP) return false;

  if(muons_trk_nhitstrack->at(mu_index) > MIN_nhits_trk     &&
     muons_trk_normChi2->at(mu_index)   < MAX_normchi2_trk  &&
     fabs(muons_trk_d0->at(mu_index))   < MAX_d0_trk        &&
     fabs(muons_trk_dz->at(mu_index))   < MAX_dz_trk        &&
     ((muons_trk_nhitsPixB->at(mu_index) + muons_trk_nhitsPixE->at(mu_index)) > MIN_nhits_pixel) &&
     ((((int)muons_trk_PIDmask->at(mu_index)) & (int)pow(2,5))/(int)pow(2,5) > 0 || (((int)muons_trk_PIDmask->at(mu_index)) & (int)pow(2,8))/(int)pow(2,8) > 0) && 
     (muons_trk_tkIsoR03->at(mu_index)+muons_trk_emIsoR03->at(mu_index))/mu_4mom->Pt() < MAX_muisol){
    hMuPtTk->Fill(mu_4mom->Pt());
    hMuEtaTk->Fill(mu_4mom->Eta());
    if(fabs(mu_4mom->Eta()) > 1.1){
      hMuPTk->Fill(mu_4mom->Rho());
      hMuPTk->Fill(mu_4mom->Rho()); 
    }
    return true;
  }
  
  return false;
}

int MuMuLooper::theBestQQ() const
{
  int theBest = -1;
  float thehighestPt = -1.;
  
  for (int iqq=0; iqq<QQ_size->at(0); iqq++) {
    
    if (QQ_sign->at(iqq) == 0 && QQ_type->at(iqq) == 1 ) {//change here for opposite sign ==0, for same sign !=0 

      int thehptMu = QQ_lepone->at(iqq);    if (thehptMu >= muons_glb_charge->size()) continue;
      int thelptMu = QQ_leptwo->at(iqq);    if (thelptMu >= muons_glb_charge->size()) continue;
      
      if( ((TLorentzVector*)muons_glb_4mom->At(QQ_lepone->at(iqq))) -> Pt() < ((TLorentzVector*)muons_glb_4mom->At(QQ_leptwo->at(iqq))) -> Pt() )
	{
	  int tempiMu = thelptMu ;
	  thelptMu = thehptMu ;
	  thehptMu = tempiMu ;
	}
      if (QQ_probChi2->at(iqq) > MIN_vtxprob && QQ_S3Dip->at(iqq) < MAX_S3Dip && accept_glb_mu(thehptMu) && accept_glb_mu(thelptMu))
	{
	  const float invMass = ((TLorentzVector*)QQ_4mom->At(iqq))->M();
	  TLorentzVector Dummy = *((TLorentzVector*)muons_glb_4mom->At(QQ_lepone->at(iqq)))
	    + *((TLorentzVector*)muons_glb_4mom->At(QQ_leptwo->at(iqq)));
	  
	  std::cout << "mass 1 " <<  invMass << " vs mass 2 " << Dummy.M() << std::endl;
	  
	  return iqq;
	}
    }
  }

  //GLB-TRK case
  for (int iqq=0; iqq<QQ_size->at(0); iqq++) {

    if (QQ_sign->at(iqq) == 0 && QQ_type->at(iqq) == 2 ) {//change here for opposite sign ==0, for same sign !=0
      
      int thehptMu = QQ_lepone->at(iqq);    if (thehptMu >= muons_glb_charge->size()) continue;
      int thelptMu = QQ_leptwo->at(iqq);    if (thelptMu >= muons_trk_charge->size()) continue; 

      if (QQ_probChi2->at(iqq) > MIN_vtxprob && QQ_S3Dip->at(iqq) < MAX_S3Dip && accept_glb_mu(thehptMu) && accept_trk_mu(thelptMu)) {
	
        TLorentzVector *theTrMumom = (TLorentzVector*)muons_trk_4mom->At(thelptMu);
        if (theTrMumom->Perp() > thehighestPt) {
	  thehighestPt = theTrMumom->Perp();
          theBest = iqq;
	}
      }
    }
  }
  
  if (theBest >= 0){
    const float invMass = ((TLorentzVector*)QQ_4mom->At(theBest))->M();
    TLorentzVector Dummy = *((TLorentzVector*)muons_glb_4mom->At(QQ_lepone->at(theBest)))
      + *((TLorentzVector*)muons_glb_4mom->At(QQ_leptwo->at(theBest)));
    
    std::cout << "mass 1 " <<  invMass << " vs mass 2 " << Dummy.M() << std::endl;
    return theBest;
  }
  return theBest;
} 			       
