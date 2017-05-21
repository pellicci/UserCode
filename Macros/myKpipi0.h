#ifndef myKpipi0_h
#define myKpipi0_h
#include <TString.h>
#include <TVector3.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <string>
#include <vector>
#include <Kpipi0Base.h>
#ifdef SINGLE_TREE
#else
#endif

class myKpipi0 : public Kpipi0Base
{
 
 protected:
   
  //counters

  Int_t nbytes, nb, nentries;

  TTree *RecoTree;
  void HistoDef();
  void HistoWrite();

  inline Bool_t isGoodEvent() const;
  inline Bool_t tag_k() const;
  inline Bool_t tag_pi() const;
  inline Bool_t tag_e() const;
  inline Bool_t tag_mu() const;

  void checkMCbools();
  void getFrac();

  TH1F *deltamRS, *deltamWS, *mD0RS, *mD0WS, *lifeErrRS, *lifeErrWS;
  TH1F *m2Kpi_RS, *m2Kpi0_RS, *m2pipi0_RS, *t_RS;

  TH1F *deltamRSbkg1005, *deltamWSbkg1005, *mD0RSbkg1005, *mD0WSbkg1005;
  TH1F *deltamRSbkg1235, *deltamWSbkg1235, *mD0RSbkg1235, *mD0WSbkg1235;
  TH1F *deltamRSbkg1237, *deltamWSbkg1237, *mD0RSbkg1237, *mD0WSbkg1237;
  TH1F *deltamRSbkg998, *deltamWSbkg998, *mD0RSbkg998, *mD0WSbkg998;
  TH1F *deltamRSbkg3429, *deltamWSbkg3429, *mD0RSbkg3429, *mD0WSbkg3429;
  TH1F *lifeErrRSbkg, *lifeErrWSbkg;
  TH1F *deltamcombRS, *deltamcombWS, *deltambadRS, *deltambadWS, *deltammisRS, *deltammisWS;
  TH1F *mD0combRS, *mD0combWS, *mD0badRS, *mD0badWS, *mD0misRS, *mD0misWS;
  TH1F *m2Kpi_leftRS, *m2Kpi0_leftRS, *m2pipi0_leftRS, *m2Kpi_rightRS, *m2Kpi0_rightRS, *m2pipi0_rightRS;
  TH1F *m2Kpi_leftWS, *m2Kpi0_leftWS, *m2pipi0_leftWS, *m2Kpi_rightWS, *m2Kpi0_rightWS, *m2pipi0_rightWS;
  TH1F *part_m2Kpi_leftWS[5], *part_m2Kpi0_leftWS[5], *part_m2pipi0_leftWS[5], *part_m2Kpi_rightWS[5], *part_m2Kpi0_rightWS[5], *part_m2pipi0_rightWS[5];
  TH1F *m2Kpi_sigregRS, *m2Kpi0_sigregRS, *m2pipi0_sigregRS, *m2Kpi_sigregWS, *m2Kpi0_sigregWS, *m2pipi0_sigregWS;
  TH1F *part_m2Kpi_sigregWS[5], *part_m2Kpi0_sigregWS[5], *part_m2pipi0_sigregWS[5];
  TH1F *t_leftRS, *t_rightRS, *t_sigregRS;
  TH1F *t_leftWS, *t_rightWS, *t_sigregWS;
  TH1F *lifeErr_leftRS, *lifeErr_rightRS, *lifeErr_sigregRS;
  TH1F *lifeErr_leftWS, *lifeErr_rightWS, *lifeErr_sigregWS;
  TH1F *swapRS, *swapWS;
  TH1F *p_K, *p_pi, *p_pis;

  TH1F *m2Kpi_misWS, *m2Kpi0_misWS, *m2pipi0_misWS, *t_misWS;

  TH2F *mdmBADWS, *mdmBADRS;

  Bool_t isMC;
  Bool_t isccbar, isbpbm, isbzbzb, isuds, istautau;
  Float_t frac;

 public:

  myKpipi0(TTree *tree=0);
  virtual ~myKpipi0();

  Float_t mass_swap();
  void Loop();
  void HistoFill();
};

#endif


