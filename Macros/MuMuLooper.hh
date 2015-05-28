#ifndef MuMuLooper_h
#define MuMuLooper_h

#include <TVector3.h>
#include <TH1F.h>
#include <TH2F.h>

#include "smallHBaseClass.h"
#include <vector>

class MuMuLooper : public smallHBaseClass{
public:
  
  MuMuLooper(TChain *tree=0);
  virtual ~MuMuLooper() {};
  void bookHistos();
  void saveHistos(TFile *f1);
  void Loop();
  int theBestQQ() const;
  bool accept_glb_mu(const int mu_index) const;
  bool accept_trk_mu(const int mu_index) const;

private:

  int MIN_nhits_trk;
  float MAX_normchi2_trk;
  float MAX_normchi2_glb;
  int MIN_nhits_pixel;
  float MAX_d0_trk;
  float MAX_dz_trk;
  float MIN_vtxprob;
  float MAX_S3Dip;
  float MAX_muisol;
  float MIN_muP;

  float weight;
  bool onlyTheBest;
              
  TH1F *hInvMass;
//   TH1F *hIsoVar03_glb_TKECAL1;
//   TH1F *hIsoVar03_glb_TKECAL2;
//   TH1F *hIsoVar03_glb_TK;
//   TH1F *hIsoVar03_glb_ECAL;
//   TH1F *hIsoVar03_trk_TKECAL1;
//   TH1F *hIsoVar03_trk_TKECAL2;
//   TH1F *hIsoVar03_trk_TK;
//   TH1F *hIsoVar03_trk_ECAL;

  TH1F * hQQProbChi2;
  TH1F *hQQS3Dip; 
  TH1F *hQQSTip ;
  TH1F *hQQEta   ;
  TH1F *hQQPt    ;
  TH1F *hMuEtaTk   ;
  TH1F * hMuPtTk    ;
  TH1F *hMuEtaGlb   ;
  TH1F * hMuPtGlb    ;
  TH1F * hMuPGlb    ;
  TH1F * hMuPTk    ;

};
#endif

