//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 30 02:58:48 2007 by ROOT version 4.04/02b
// from TChain ntp3/
//////////////////////////////////////////////////////////

#ifndef reduceData_h
#define reduceData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class reduceData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Int_t           runnumber;
   Double_t        pi0Chi2ProbPre;
   Double_t        d0Chi2ProbPre;
   Double_t        dstarChi2ProbPre;
   Double_t        pi0MassUnfit;
   Double_t        pi0PmagUnfit;
   Double_t        pi0Chi2Prob;
   Double_t        d0pstar;
   Double_t        d0Mass;
   Double_t        d0MassErr;
   Double_t        d0MassPull;
   Double_t        d0Chi2Prob;
   Double_t        m2Kpi;
   Double_t        m2pipi0;
   Double_t        m2Kpi0;
   Double_t        m2Kpi_d0mass;
   Double_t        m2pipi0_d0mass;
   Double_t        m2Kpi0_d0mass;
   Double_t        m_Kpi_d0mass;
   Double_t        m_pipi0_d0mass;
   Double_t        m_Kpi0_d0mass;
   Double_t        d0P_phi;
   Double_t        d0P_theta;
   Double_t        d0P_mag;
   Double_t        kPmag;
   Double_t        piPmag;
   Double_t        pi0Pmag;
   Double_t        kE;
   Double_t        piE;
   Double_t        pi0E;
   Double_t        kPx;
   Double_t        piPx;
   Double_t        pi0Px;
   Double_t        kPy;
   Double_t        piPy;
   Double_t        pi0Py;
   Double_t        kPz;
   Double_t        piPz;
   Double_t        pi0Pz;
   Double_t        kPmag_d0frame;
   Double_t        piPmag_d0frame;
   Double_t        pi0Pmag_d0frame;
   Double_t        kE_d0frame;
   Double_t        piE_d0frame;
   Double_t        pi0E_d0frame;
   Double_t        kPx_d0frame;
   Double_t        piPx_d0frame;
   Double_t        pi0Px_d0frame;
   Double_t        kPy_d0frame;
   Double_t        piPy_d0frame;
   Double_t        pi0Py_d0frame;
   Double_t        kPz_d0frame;
   Double_t        piPz_d0frame;
   Double_t        pi0Pz_d0frame;
   Double_t        dstarChi2Prob;
   Double_t        epem_m2;
   Double_t        pi0conv_m;
   Double_t        dedx_meas;
   Double_t        dedx_teo;
   Double_t        dedx_teo_e;
   Double_t        pisoft_mom;
   Double_t        deltaMass;
   Double_t        deltaMassErr;
   Double_t        deltaMassPull;
   Double_t        d0Lifetime;
   Double_t        d0LifetimeErr;
   Double_t        d0LifetimePull;
   UChar_t         isWS;
   UChar_t         isAntiD0;
   Double_t        d0Lifetime_d0only;
   Double_t        d0LifetimeErr_d0only;
   Double_t        d0LifetimePull_d0only;
   UChar_t         truthIsSignal;
   UChar_t         truthIsBkg_FakePiSlow;
   UChar_t         truthIsBkg_BadSignalD0;
   UChar_t         truthIsBkg_BadOtherD0;
   UChar_t         truthIsBkg_BadDplus;
   UChar_t         truthIsBkg_SwappedKpi;
   UChar_t         truthIsBkg_Comb;
   UChar_t         truthHasMisIDKaon;
   UChar_t         truthHasMisIDPion;
   UChar_t         truthHasKpiCommonParent;
   Int_t           truthNRecoD0Daug;
   Double_t        tag_spi_dss_p;
   Double_t        tag_spi_dss_pt;
   Double_t        tag_spi_dss_pl;
   Double_t        tag_spi_pchi2;
   Double_t        tag_spi_dss_p_WS;
   Double_t        tag_spi_dss_pt_WS;
   Double_t        tag_spi_dss_pl_WS;
   Double_t        tag_spi_pchi2_WS;
   UChar_t         truthTagGoodPiSlow;
   Double_t        truthTagPiSlowCosThDiff;
   Int_t           tag_k_nK;
   Double_t        tag_k_cms_p;
   Double_t        tag_k_doca;
   Double_t        tag_k_cms_p_WS;
   Double_t        tag_k_doca_WS;
   UChar_t         truthTagGoodK;
   Double_t        tag_e_cms_p;
   Double_t        tag_e_doca;
   Double_t        tag_e_hel;
   Double_t        tag_e_etop;
   Double_t        tag_e_dedx;
   Double_t        tag_e_m2;
   Double_t        tag_e_cms_p_WS;
   Double_t        tag_e_doca_WS;
   Double_t        tag_e_hel_WS;
   Double_t        tag_e_etop_WS;
   Double_t        tag_e_dedx_WS;
   Double_t        tag_e_m2_WS;
   UChar_t         truthTagGoodE;
   Double_t        tag_mu_cms_p;
   Double_t        tag_mu_doca;
   Double_t        tag_mu_hel;
   Double_t        tag_mu_etop;
   Double_t        tag_mu_dedx;
   Double_t        tag_mu_m2;
   Double_t        tag_mu_cms_p_WS;
   Double_t        tag_mu_doca_WS;
   Double_t        tag_mu_hel_WS;
   Double_t        tag_mu_etop_WS;
   Double_t        tag_mu_dedx_WS;
   Double_t        tag_mu_m2_WS;
   UChar_t         truthTagGoodMu;
   Int_t           tag_chg_all;
   Int_t           tag_chg_250;
   Int_t           tag_chg_400;
   Int_t           tag_chg_550;
   Int_t           truth_tag_chg_all;
   Int_t           truth_tag_chg_250;
   Int_t           truth_tag_chg_400;
   Int_t           truth_tag_chg_550;
   UChar_t         tag_opp_side;
   UChar_t         tag_opp_withveto;

   // List of branches
   TBranch        *b_runnumber;   //!
   TBranch        *b_pi0Chi2ProbPre;   //!
   TBranch        *b_d0Chi2ProbPre;   //!
   TBranch        *b_dstarChi2ProbPre;   //!
   TBranch        *b_pi0MassUnfit;   //!
   TBranch        *b_pi0PmagUnfit;   //!
   TBranch        *b_pi0Chi2Prob;   //!
   TBranch        *b_d0pstar;   //!
   TBranch        *b_d0Mass;   //!
   TBranch        *b_d0MassErr;   //!
   TBranch        *b_d0MassPull;   //!
   TBranch        *b_d0Chi2Prob;   //!
   TBranch        *b_m2Kpi;   //!
   TBranch        *b_m2pipi0;   //!
   TBranch        *b_m2Kpi0;   //!
   TBranch        *b_m2Kpi_d0mass;   //!
   TBranch        *b_m2pipi0_d0mass;   //!
   TBranch        *b_m2Kpi0_d0mass;   //!
   TBranch        *b_m_Kpi_d0mass;   //!
   TBranch        *b_m_pipi0_d0mass;   //!
   TBranch        *b_m_Kpi0_d0mass;   //!
   TBranch        *b_d0P_phi;   //!
   TBranch        *b_d0P_theta;   //!
   TBranch        *b_d0P_mag;   //!
   TBranch        *b_kPmag;   //!
   TBranch        *b_piPmag;   //!
   TBranch        *b_pi0Pmag;   //!
   TBranch        *b_kE;   //!
   TBranch        *b_piE;   //!
   TBranch        *b_pi0E;   //!
   TBranch        *b_kPx;   //!
   TBranch        *b_piPx;   //!
   TBranch        *b_pi0Px;   //!
   TBranch        *b_kPy;   //!
   TBranch        *b_piPy;   //!
   TBranch        *b_pi0Py;   //!
   TBranch        *b_kPz;   //!
   TBranch        *b_piPz;   //!
   TBranch        *b_pi0Pz;   //!
   TBranch        *b_kPmag_d0frame;   //!
   TBranch        *b_piPmag_d0frame;   //!
   TBranch        *b_pi0Pmag_d0frame;   //!
   TBranch        *b_kE_d0frame;   //!
   TBranch        *b_piE_d0frame;   //!
   TBranch        *b_pi0E_d0frame;   //!
   TBranch        *b_kPx_d0frame;   //!
   TBranch        *b_piPx_d0frame;   //!
   TBranch        *b_pi0Px_d0frame;   //!
   TBranch        *b_kPy_d0frame;   //!
   TBranch        *b_piPy_d0frame;   //!
   TBranch        *b_pi0Py_d0frame;   //!
   TBranch        *b_kPz_d0frame;   //!
   TBranch        *b_piPz_d0frame;   //!
   TBranch        *b_pi0Pz_d0frame;   //!
   TBranch        *b_dstarChi2Prob;   //!
   TBranch        *b_epem_m2;   //!
   TBranch        *b_pi0conv_m;   //!
   TBranch        *b_dedx_meas;   //!
   TBranch        *b_dedx_teo;   //!
   TBranch        *b_dedx_teo_e;   //!
   TBranch        *b_pisoft_mom;   //!
   TBranch        *b_deltaMass;   //!
   TBranch        *b_deltaMassErr;   //!
   TBranch        *b_deltaMassPull;   //!
   TBranch        *b_d0Lifetime;   //!
   TBranch        *b_d0LifetimeErr;   //!
   TBranch        *b_d0LifetimePull;   //!
   TBranch        *b_isWS;   //!
   TBranch        *b_isAntiD0;   //!
   TBranch        *b_d0Lifetime_d0only;   //!
   TBranch        *b_d0LifetimeErr_d0only;   //!
   TBranch        *b_d0LifetimePull_d0only;   //!
   TBranch        *b_truthIsSignal;   //!
   TBranch        *b_truthIsBkg_FakePiSlow;   //!
   TBranch        *b_truthIsBkg_BadSignalD0;   //!
   TBranch        *b_truthIsBkg_BadOtherD0;   //!
   TBranch        *b_truthIsBkg_BadDplus;   //!
   TBranch        *b_truthIsBkg_SwappedKpi;   //!
   TBranch        *b_truthIsBkg_Comb;   //!
   TBranch        *b_truthHasMisIDKaon;   //!
   TBranch        *b_truthHasMisIDPion;   //!
   TBranch        *b_truthHasKpiCommonParent;   //!
   TBranch        *b_truthNRecoD0Daug;   //!
   TBranch        *b_tag_spi_dss_p;   //!
   TBranch        *b_tag_spi_dss_pt;   //!
   TBranch        *b_tag_spi_dss_pl;   //!
   TBranch        *b_tag_spi_pchi2;   //!
   TBranch        *b_tag_spi_dss_p_WS;   //!
   TBranch        *b_tag_spi_dss_pt_WS;   //!
   TBranch        *b_tag_spi_dss_pl_WS;   //!
   TBranch        *b_tag_spi_pchi2_WS;   //!
   TBranch        *b_truthTagGoodPiSlow;   //!
   TBranch        *b_truthTagPiSlowCosThDiff;   //!
   TBranch        *b_tag_k_nK;   //!
   TBranch        *b_tag_k_cms_p;   //!
   TBranch        *b_tag_k_doca;   //!
   TBranch        *b_tag_k_cms_p_WS;   //!
   TBranch        *b_tag_k_doca_WS;   //!
   TBranch        *b_truthTagGoodK;   //!
   TBranch        *b_tag_e_cms_p;   //!
   TBranch        *b_tag_e_doca;   //!
   TBranch        *b_tag_e_hel;   //!
   TBranch        *b_tag_e_etop;   //!
   TBranch        *b_tag_e_dedx;   //!
   TBranch        *b_tag_e_m2;   //!
   TBranch        *b_tag_e_cms_p_WS;   //!
   TBranch        *b_tag_e_doca_WS;   //!
   TBranch        *b_tag_e_hel_WS;   //!
   TBranch        *b_tag_e_etop_WS;   //!
   TBranch        *b_tag_e_dedx_WS;   //!
   TBranch        *b_tag_e_m2_WS;   //!
   TBranch        *b_truthTagGoodE;   //!
   TBranch        *b_tag_mu_cms_p;   //!
   TBranch        *b_tag_mu_doca;   //!
   TBranch        *b_tag_mu_hel;   //!
   TBranch        *b_tag_mu_etop;   //!
   TBranch        *b_tag_mu_dedx;   //!
   TBranch        *b_tag_mu_m2;   //!
   TBranch        *b_tag_mu_cms_p_WS;   //!
   TBranch        *b_tag_mu_doca_WS;   //!
   TBranch        *b_tag_mu_hel_WS;   //!
   TBranch        *b_tag_mu_etop_WS;   //!
   TBranch        *b_tag_mu_dedx_WS;   //!
   TBranch        *b_tag_mu_m2_WS;   //!
   TBranch        *b_truthTagGoodMu;   //!
   TBranch        *b_tag_chg_all;   //!
   TBranch        *b_tag_chg_250;   //!
   TBranch        *b_tag_chg_400;   //!
   TBranch        *b_tag_chg_550;   //!
   TBranch        *b_truth_tag_chg_all;   //!
   TBranch        *b_truth_tag_chg_250;   //!
   TBranch        *b_truth_tag_chg_400;   //!
   TBranch        *b_truth_tag_chg_550;   //!
   TBranch        *b_tag_opp_side;   //!
   TBranch        *b_tag_opp_withveto;   //!

   reduceData(TTree *tree=0);
   virtual ~reduceData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef reduceData_cxx
reduceData::reduceData(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f) {
         f = new TFile("Memory Directory");
         f->cd("Rint:/");
      }
      tree = (TTree*)gDirectory->Get("ntp3");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("ntp3","");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-10.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-11.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-12.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-13.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-14.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-15.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-16.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-17.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-18.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-19.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-20.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-21.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-22.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-23.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-24.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-25.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-26.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-27.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-28.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run1-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-10.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-11.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-12.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-13.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-14.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-15.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-16.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-17.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-18.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-19.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-20.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-21.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-22.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-23.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-24.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-25.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-26.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-27.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-28.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-29.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-30.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-31.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-32.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-33.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-34.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-35.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-36.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-37.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-38.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-39.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-40.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-41.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-42.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-43.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-44.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-45.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-46.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-47.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-48.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-49.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-50.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-51.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-52.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-53.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run2-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-10.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-11.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-12.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-13.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-14.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-15.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-16.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-17.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-18.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-19.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-20.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-21.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-22.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-23.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-24.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-25.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-26.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run3-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-10.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-11.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-12.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-13.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-14.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-15.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-16.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-17.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-18.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-19.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-20.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-21.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-22.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-23.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-24.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-25.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-26.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-27.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-28.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-29.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-30.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-31.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-32.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-33.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-34.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-35.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-36.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-37.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-38.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-39.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-40.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-41.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-42.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-43.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-44.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-45.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-46.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-47.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-48.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-49.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-50.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-51.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run4-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-10.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-11.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-12.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-13.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-14.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-15.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-16.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-17.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-18.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-19.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-20.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-21.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-22.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-23.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-24.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-25.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-26.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-27.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-28.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-29.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-30.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-31.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-32.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-33.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-34.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-35.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-36.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-37.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-38.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-39.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-40.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1005-DmixD0ToKPiPi0-Run5-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run1-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run1-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run1-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run1-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run2-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run2-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run2-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run2-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run2-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run3-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run3-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run3-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run4-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run5-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run5-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run5-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run5-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run5-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run5-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run5-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1235-DmixD0ToKPiPi0-Run5-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run1-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run1-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run1-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run1-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run2-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run2-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run2-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run2-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run2-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run2-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run3-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run3-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run3-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run4-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-1237-DmixD0ToKPiPi0-Run5-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-3429-DmixD0ToKPiPi0-Run1-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-3429-DmixD0ToKPiPi0-Run3-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-3429-DmixD0ToKPiPi0-Run4-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-3429-DmixD0ToKPiPi0-Run5-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run1-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run1-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run1-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run1-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run1-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run1-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run2-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run2-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run2-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run2-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run2-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run2-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run2-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run2-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run3-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run3-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run3-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run3-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run3-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-10.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-11.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-12.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-13.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-14.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run4-R18b-9.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-1.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-10.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-11.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-12.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-13.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-14.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-2.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-3.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-4.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-5.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-6.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-7.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-8.root/ntp3");
      chain->Add("dataR18/SP-998-DmixD0ToKPiPi0-Run5-R18b-9.root/ntp3");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

reduceData::~reduceData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t reduceData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t reduceData::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void reduceData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runnumber",&runnumber);
   fChain->SetBranchAddress("pi0Chi2ProbPre",&pi0Chi2ProbPre);
   fChain->SetBranchAddress("d0Chi2ProbPre",&d0Chi2ProbPre);
   fChain->SetBranchAddress("dstarChi2ProbPre",&dstarChi2ProbPre);
   fChain->SetBranchAddress("pi0MassUnfit",&pi0MassUnfit);
   fChain->SetBranchAddress("pi0PmagUnfit",&pi0PmagUnfit);
   fChain->SetBranchAddress("pi0Chi2Prob",&pi0Chi2Prob);
   fChain->SetBranchAddress("d0pstar",&d0pstar);
   fChain->SetBranchAddress("d0Mass",&d0Mass);
   fChain->SetBranchAddress("d0MassErr",&d0MassErr);
   fChain->SetBranchAddress("d0MassPull",&d0MassPull);
   fChain->SetBranchAddress("d0Chi2Prob",&d0Chi2Prob);
   fChain->SetBranchAddress("m2Kpi",&m2Kpi);
   fChain->SetBranchAddress("m2pipi0",&m2pipi0);
   fChain->SetBranchAddress("m2Kpi0",&m2Kpi0);
   fChain->SetBranchAddress("m2Kpi_d0mass",&m2Kpi_d0mass);
   fChain->SetBranchAddress("m2pipi0_d0mass",&m2pipi0_d0mass);
   fChain->SetBranchAddress("m2Kpi0_d0mass",&m2Kpi0_d0mass);
   fChain->SetBranchAddress("m_Kpi_d0mass",&m_Kpi_d0mass);
   fChain->SetBranchAddress("m_pipi0_d0mass",&m_pipi0_d0mass);
   fChain->SetBranchAddress("m_Kpi0_d0mass",&m_Kpi0_d0mass);
   fChain->SetBranchAddress("d0P_phi",&d0P_phi);
   fChain->SetBranchAddress("d0P_theta",&d0P_theta);
   fChain->SetBranchAddress("d0P_mag",&d0P_mag);
   fChain->SetBranchAddress("kPmag",&kPmag);
   fChain->SetBranchAddress("piPmag",&piPmag);
   fChain->SetBranchAddress("pi0Pmag",&pi0Pmag);
   fChain->SetBranchAddress("kE",&kE);
   fChain->SetBranchAddress("piE",&piE);
   fChain->SetBranchAddress("pi0E",&pi0E);
   fChain->SetBranchAddress("kPx",&kPx);
   fChain->SetBranchAddress("piPx",&piPx);
   fChain->SetBranchAddress("pi0Px",&pi0Px);
   fChain->SetBranchAddress("kPy",&kPy);
   fChain->SetBranchAddress("piPy",&piPy);
   fChain->SetBranchAddress("pi0Py",&pi0Py);
   fChain->SetBranchAddress("kPz",&kPz);
   fChain->SetBranchAddress("piPz",&piPz);
   fChain->SetBranchAddress("pi0Pz",&pi0Pz);
   fChain->SetBranchAddress("kPmag_d0frame",&kPmag_d0frame);
   fChain->SetBranchAddress("piPmag_d0frame",&piPmag_d0frame);
   fChain->SetBranchAddress("pi0Pmag_d0frame",&pi0Pmag_d0frame);
   fChain->SetBranchAddress("kE_d0frame",&kE_d0frame);
   fChain->SetBranchAddress("piE_d0frame",&piE_d0frame);
   fChain->SetBranchAddress("pi0E_d0frame",&pi0E_d0frame);
   fChain->SetBranchAddress("kPx_d0frame",&kPx_d0frame);
   fChain->SetBranchAddress("piPx_d0frame",&piPx_d0frame);
   fChain->SetBranchAddress("pi0Px_d0frame",&pi0Px_d0frame);
   fChain->SetBranchAddress("kPy_d0frame",&kPy_d0frame);
   fChain->SetBranchAddress("piPy_d0frame",&piPy_d0frame);
   fChain->SetBranchAddress("pi0Py_d0frame",&pi0Py_d0frame);
   fChain->SetBranchAddress("kPz_d0frame",&kPz_d0frame);
   fChain->SetBranchAddress("piPz_d0frame",&piPz_d0frame);
   fChain->SetBranchAddress("pi0Pz_d0frame",&pi0Pz_d0frame);
   fChain->SetBranchAddress("dstarChi2Prob",&dstarChi2Prob);
   fChain->SetBranchAddress("epem_m2",&epem_m2);
   fChain->SetBranchAddress("pi0conv_m",&pi0conv_m);
   fChain->SetBranchAddress("dedx_meas",&dedx_meas);
   fChain->SetBranchAddress("dedx_teo",&dedx_teo);
   fChain->SetBranchAddress("dedx_teo_e",&dedx_teo_e);
   fChain->SetBranchAddress("pisoft_mom",&pisoft_mom);
   fChain->SetBranchAddress("deltaMass",&deltaMass);
   fChain->SetBranchAddress("deltaMassErr",&deltaMassErr);
   fChain->SetBranchAddress("deltaMassPull",&deltaMassPull);
   fChain->SetBranchAddress("d0Lifetime",&d0Lifetime);
   fChain->SetBranchAddress("d0LifetimeErr",&d0LifetimeErr);
   fChain->SetBranchAddress("d0LifetimePull",&d0LifetimePull);
   fChain->SetBranchAddress("isWS",&isWS);
   fChain->SetBranchAddress("isAntiD0",&isAntiD0);
   fChain->SetBranchAddress("d0Lifetime_d0only",&d0Lifetime_d0only);
   fChain->SetBranchAddress("d0LifetimeErr_d0only",&d0LifetimeErr_d0only);
   fChain->SetBranchAddress("d0LifetimePull_d0only",&d0LifetimePull_d0only);
   fChain->SetBranchAddress("truthIsSignal",&truthIsSignal);
   fChain->SetBranchAddress("truthIsBkg_FakePiSlow",&truthIsBkg_FakePiSlow);
   fChain->SetBranchAddress("truthIsBkg_BadSignalD0",&truthIsBkg_BadSignalD0);
   fChain->SetBranchAddress("truthIsBkg_BadOtherD0",&truthIsBkg_BadOtherD0);
   fChain->SetBranchAddress("truthIsBkg_BadDplus",&truthIsBkg_BadDplus);
   fChain->SetBranchAddress("truthIsBkg_SwappedKpi",&truthIsBkg_SwappedKpi);
   fChain->SetBranchAddress("truthIsBkg_Comb",&truthIsBkg_Comb);
   fChain->SetBranchAddress("truthHasMisIDKaon",&truthHasMisIDKaon);
   fChain->SetBranchAddress("truthHasMisIDPion",&truthHasMisIDPion);
   fChain->SetBranchAddress("truthHasKpiCommonParent",&truthHasKpiCommonParent);
   fChain->SetBranchAddress("truthNRecoD0Daug",&truthNRecoD0Daug);
   fChain->SetBranchAddress("tag_spi_dss_p",&tag_spi_dss_p);
   fChain->SetBranchAddress("tag_spi_dss_pt",&tag_spi_dss_pt);
   fChain->SetBranchAddress("tag_spi_dss_pl",&tag_spi_dss_pl);
   fChain->SetBranchAddress("tag_spi_pchi2",&tag_spi_pchi2);
   fChain->SetBranchAddress("tag_spi_dss_p_WS",&tag_spi_dss_p_WS);
   fChain->SetBranchAddress("tag_spi_dss_pt_WS",&tag_spi_dss_pt_WS);
   fChain->SetBranchAddress("tag_spi_dss_pl_WS",&tag_spi_dss_pl_WS);
   fChain->SetBranchAddress("tag_spi_pchi2_WS",&tag_spi_pchi2_WS);
   fChain->SetBranchAddress("truthTagGoodPiSlow",&truthTagGoodPiSlow);
   fChain->SetBranchAddress("truthTagPiSlowCosThDiff",&truthTagPiSlowCosThDiff);
   fChain->SetBranchAddress("tag_k_nK",&tag_k_nK);
   fChain->SetBranchAddress("tag_k_cms_p",&tag_k_cms_p);
   fChain->SetBranchAddress("tag_k_doca",&tag_k_doca);
   fChain->SetBranchAddress("tag_k_cms_p_WS",&tag_k_cms_p_WS);
   fChain->SetBranchAddress("tag_k_doca_WS",&tag_k_doca_WS);
   fChain->SetBranchAddress("truthTagGoodK",&truthTagGoodK);
   fChain->SetBranchAddress("tag_e_cms_p",&tag_e_cms_p);
   fChain->SetBranchAddress("tag_e_doca",&tag_e_doca);
   fChain->SetBranchAddress("tag_e_hel",&tag_e_hel);
   fChain->SetBranchAddress("tag_e_etop",&tag_e_etop);
   fChain->SetBranchAddress("tag_e_dedx",&tag_e_dedx);
   fChain->SetBranchAddress("tag_e_m2",&tag_e_m2);
   fChain->SetBranchAddress("tag_e_cms_p_WS",&tag_e_cms_p_WS);
   fChain->SetBranchAddress("tag_e_doca_WS",&tag_e_doca_WS);
   fChain->SetBranchAddress("tag_e_hel_WS",&tag_e_hel_WS);
   fChain->SetBranchAddress("tag_e_etop_WS",&tag_e_etop_WS);
   fChain->SetBranchAddress("tag_e_dedx_WS",&tag_e_dedx_WS);
   fChain->SetBranchAddress("tag_e_m2_WS",&tag_e_m2_WS);
   fChain->SetBranchAddress("truthTagGoodE",&truthTagGoodE);
   fChain->SetBranchAddress("tag_mu_cms_p",&tag_mu_cms_p);
   fChain->SetBranchAddress("tag_mu_doca",&tag_mu_doca);
   fChain->SetBranchAddress("tag_mu_hel",&tag_mu_hel);
   fChain->SetBranchAddress("tag_mu_etop",&tag_mu_etop);
   fChain->SetBranchAddress("tag_mu_dedx",&tag_mu_dedx);
   fChain->SetBranchAddress("tag_mu_m2",&tag_mu_m2);
   fChain->SetBranchAddress("tag_mu_cms_p_WS",&tag_mu_cms_p_WS);
   fChain->SetBranchAddress("tag_mu_doca_WS",&tag_mu_doca_WS);
   fChain->SetBranchAddress("tag_mu_hel_WS",&tag_mu_hel_WS);
   fChain->SetBranchAddress("tag_mu_etop_WS",&tag_mu_etop_WS);
   fChain->SetBranchAddress("tag_mu_dedx_WS",&tag_mu_dedx_WS);
   fChain->SetBranchAddress("tag_mu_m2_WS",&tag_mu_m2_WS);
   fChain->SetBranchAddress("truthTagGoodMu",&truthTagGoodMu);
   fChain->SetBranchAddress("tag_chg_all",&tag_chg_all);
   fChain->SetBranchAddress("tag_chg_250",&tag_chg_250);
   fChain->SetBranchAddress("tag_chg_400",&tag_chg_400);
   fChain->SetBranchAddress("tag_chg_550",&tag_chg_550);
   fChain->SetBranchAddress("truth_tag_chg_all",&truth_tag_chg_all);
   fChain->SetBranchAddress("truth_tag_chg_250",&truth_tag_chg_250);
   fChain->SetBranchAddress("truth_tag_chg_400",&truth_tag_chg_400);
   fChain->SetBranchAddress("truth_tag_chg_550",&truth_tag_chg_550);
   fChain->SetBranchAddress("tag_opp_side",&tag_opp_side);
   fChain->SetBranchAddress("tag_opp_withveto",&tag_opp_withveto);
   Notify();
}

Bool_t reduceData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_runnumber = fChain->GetBranch("runnumber");
   b_pi0Chi2ProbPre = fChain->GetBranch("pi0Chi2ProbPre");
   b_d0Chi2ProbPre = fChain->GetBranch("d0Chi2ProbPre");
   b_dstarChi2ProbPre = fChain->GetBranch("dstarChi2ProbPre");
   b_pi0MassUnfit = fChain->GetBranch("pi0MassUnfit");
   b_pi0PmagUnfit = fChain->GetBranch("pi0PmagUnfit");
   b_pi0Chi2Prob = fChain->GetBranch("pi0Chi2Prob");
   b_d0pstar = fChain->GetBranch("d0pstar");
   b_d0Mass = fChain->GetBranch("d0Mass");
   b_d0MassErr = fChain->GetBranch("d0MassErr");
   b_d0MassPull = fChain->GetBranch("d0MassPull");
   b_d0Chi2Prob = fChain->GetBranch("d0Chi2Prob");
   b_m2Kpi = fChain->GetBranch("m2Kpi");
   b_m2pipi0 = fChain->GetBranch("m2pipi0");
   b_m2Kpi0 = fChain->GetBranch("m2Kpi0");
   b_m2Kpi_d0mass = fChain->GetBranch("m2Kpi_d0mass");
   b_m2pipi0_d0mass = fChain->GetBranch("m2pipi0_d0mass");
   b_m2Kpi0_d0mass = fChain->GetBranch("m2Kpi0_d0mass");
   b_m_Kpi_d0mass = fChain->GetBranch("m_Kpi_d0mass");
   b_m_pipi0_d0mass = fChain->GetBranch("m_pipi0_d0mass");
   b_m_Kpi0_d0mass = fChain->GetBranch("m_Kpi0_d0mass");
   b_d0P_phi = fChain->GetBranch("d0P_phi");
   b_d0P_theta = fChain->GetBranch("d0P_theta");
   b_d0P_mag = fChain->GetBranch("d0P_mag");
   b_kPmag = fChain->GetBranch("kPmag");
   b_piPmag = fChain->GetBranch("piPmag");
   b_pi0Pmag = fChain->GetBranch("pi0Pmag");
   b_kE = fChain->GetBranch("kE");
   b_piE = fChain->GetBranch("piE");
   b_pi0E = fChain->GetBranch("pi0E");
   b_kPx = fChain->GetBranch("kPx");
   b_piPx = fChain->GetBranch("piPx");
   b_pi0Px = fChain->GetBranch("pi0Px");
   b_kPy = fChain->GetBranch("kPy");
   b_piPy = fChain->GetBranch("piPy");
   b_pi0Py = fChain->GetBranch("pi0Py");
   b_kPz = fChain->GetBranch("kPz");
   b_piPz = fChain->GetBranch("piPz");
   b_pi0Pz = fChain->GetBranch("pi0Pz");
   b_kPmag_d0frame = fChain->GetBranch("kPmag_d0frame");
   b_piPmag_d0frame = fChain->GetBranch("piPmag_d0frame");
   b_pi0Pmag_d0frame = fChain->GetBranch("pi0Pmag_d0frame");
   b_kE_d0frame = fChain->GetBranch("kE_d0frame");
   b_piE_d0frame = fChain->GetBranch("piE_d0frame");
   b_pi0E_d0frame = fChain->GetBranch("pi0E_d0frame");
   b_kPx_d0frame = fChain->GetBranch("kPx_d0frame");
   b_piPx_d0frame = fChain->GetBranch("piPx_d0frame");
   b_pi0Px_d0frame = fChain->GetBranch("pi0Px_d0frame");
   b_kPy_d0frame = fChain->GetBranch("kPy_d0frame");
   b_piPy_d0frame = fChain->GetBranch("piPy_d0frame");
   b_pi0Py_d0frame = fChain->GetBranch("pi0Py_d0frame");
   b_kPz_d0frame = fChain->GetBranch("kPz_d0frame");
   b_piPz_d0frame = fChain->GetBranch("piPz_d0frame");
   b_pi0Pz_d0frame = fChain->GetBranch("pi0Pz_d0frame");
   b_dstarChi2Prob = fChain->GetBranch("dstarChi2Prob");
   b_epem_m2 = fChain->GetBranch("epem_m2");
   b_pi0conv_m = fChain->GetBranch("pi0conv_m");
   b_dedx_meas = fChain->GetBranch("dedx_meas");
   b_dedx_teo = fChain->GetBranch("dedx_teo");
   b_dedx_teo_e = fChain->GetBranch("dedx_teo_e");
   b_pisoft_mom = fChain->GetBranch("pisoft_mom");
   b_deltaMass = fChain->GetBranch("deltaMass");
   b_deltaMassErr = fChain->GetBranch("deltaMassErr");
   b_deltaMassPull = fChain->GetBranch("deltaMassPull");
   b_d0Lifetime = fChain->GetBranch("d0Lifetime");
   b_d0LifetimeErr = fChain->GetBranch("d0LifetimeErr");
   b_d0LifetimePull = fChain->GetBranch("d0LifetimePull");
   b_isWS = fChain->GetBranch("isWS");
   b_isAntiD0 = fChain->GetBranch("isAntiD0");
   b_d0Lifetime_d0only = fChain->GetBranch("d0Lifetime_d0only");
   b_d0LifetimeErr_d0only = fChain->GetBranch("d0LifetimeErr_d0only");
   b_d0LifetimePull_d0only = fChain->GetBranch("d0LifetimePull_d0only");
   b_truthIsSignal = fChain->GetBranch("truthIsSignal");
   b_truthIsBkg_FakePiSlow = fChain->GetBranch("truthIsBkg_FakePiSlow");
   b_truthIsBkg_BadSignalD0 = fChain->GetBranch("truthIsBkg_BadSignalD0");
   b_truthIsBkg_BadOtherD0 = fChain->GetBranch("truthIsBkg_BadOtherD0");
   b_truthIsBkg_BadDplus = fChain->GetBranch("truthIsBkg_BadDplus");
   b_truthIsBkg_SwappedKpi = fChain->GetBranch("truthIsBkg_SwappedKpi");
   b_truthIsBkg_Comb = fChain->GetBranch("truthIsBkg_Comb");
   b_truthHasMisIDKaon = fChain->GetBranch("truthHasMisIDKaon");
   b_truthHasMisIDPion = fChain->GetBranch("truthHasMisIDPion");
   b_truthHasKpiCommonParent = fChain->GetBranch("truthHasKpiCommonParent");
   b_truthNRecoD0Daug = fChain->GetBranch("truthNRecoD0Daug");
   b_tag_spi_dss_p = fChain->GetBranch("tag_spi_dss_p");
   b_tag_spi_dss_pt = fChain->GetBranch("tag_spi_dss_pt");
   b_tag_spi_dss_pl = fChain->GetBranch("tag_spi_dss_pl");
   b_tag_spi_pchi2 = fChain->GetBranch("tag_spi_pchi2");
   b_tag_spi_dss_p_WS = fChain->GetBranch("tag_spi_dss_p_WS");
   b_tag_spi_dss_pt_WS = fChain->GetBranch("tag_spi_dss_pt_WS");
   b_tag_spi_dss_pl_WS = fChain->GetBranch("tag_spi_dss_pl_WS");
   b_tag_spi_pchi2_WS = fChain->GetBranch("tag_spi_pchi2_WS");
   b_truthTagGoodPiSlow = fChain->GetBranch("truthTagGoodPiSlow");
   b_truthTagPiSlowCosThDiff = fChain->GetBranch("truthTagPiSlowCosThDiff");
   b_tag_k_nK = fChain->GetBranch("tag_k_nK");
   b_tag_k_cms_p = fChain->GetBranch("tag_k_cms_p");
   b_tag_k_doca = fChain->GetBranch("tag_k_doca");
   b_tag_k_cms_p_WS = fChain->GetBranch("tag_k_cms_p_WS");
   b_tag_k_doca_WS = fChain->GetBranch("tag_k_doca_WS");
   b_truthTagGoodK = fChain->GetBranch("truthTagGoodK");
   b_tag_e_cms_p = fChain->GetBranch("tag_e_cms_p");
   b_tag_e_doca = fChain->GetBranch("tag_e_doca");
   b_tag_e_hel = fChain->GetBranch("tag_e_hel");
   b_tag_e_etop = fChain->GetBranch("tag_e_etop");
   b_tag_e_dedx = fChain->GetBranch("tag_e_dedx");
   b_tag_e_m2 = fChain->GetBranch("tag_e_m2");
   b_tag_e_cms_p_WS = fChain->GetBranch("tag_e_cms_p_WS");
   b_tag_e_doca_WS = fChain->GetBranch("tag_e_doca_WS");
   b_tag_e_hel_WS = fChain->GetBranch("tag_e_hel_WS");
   b_tag_e_etop_WS = fChain->GetBranch("tag_e_etop_WS");
   b_tag_e_dedx_WS = fChain->GetBranch("tag_e_dedx_WS");
   b_tag_e_m2_WS = fChain->GetBranch("tag_e_m2_WS");
   b_truthTagGoodE = fChain->GetBranch("truthTagGoodE");
   b_tag_mu_cms_p = fChain->GetBranch("tag_mu_cms_p");
   b_tag_mu_doca = fChain->GetBranch("tag_mu_doca");
   b_tag_mu_hel = fChain->GetBranch("tag_mu_hel");
   b_tag_mu_etop = fChain->GetBranch("tag_mu_etop");
   b_tag_mu_dedx = fChain->GetBranch("tag_mu_dedx");
   b_tag_mu_m2 = fChain->GetBranch("tag_mu_m2");
   b_tag_mu_cms_p_WS = fChain->GetBranch("tag_mu_cms_p_WS");
   b_tag_mu_doca_WS = fChain->GetBranch("tag_mu_doca_WS");
   b_tag_mu_hel_WS = fChain->GetBranch("tag_mu_hel_WS");
   b_tag_mu_etop_WS = fChain->GetBranch("tag_mu_etop_WS");
   b_tag_mu_dedx_WS = fChain->GetBranch("tag_mu_dedx_WS");
   b_tag_mu_m2_WS = fChain->GetBranch("tag_mu_m2_WS");
   b_truthTagGoodMu = fChain->GetBranch("truthTagGoodMu");
   b_tag_chg_all = fChain->GetBranch("tag_chg_all");
   b_tag_chg_250 = fChain->GetBranch("tag_chg_250");
   b_tag_chg_400 = fChain->GetBranch("tag_chg_400");
   b_tag_chg_550 = fChain->GetBranch("tag_chg_550");
   b_truth_tag_chg_all = fChain->GetBranch("truth_tag_chg_all");
   b_truth_tag_chg_250 = fChain->GetBranch("truth_tag_chg_250");
   b_truth_tag_chg_400 = fChain->GetBranch("truth_tag_chg_400");
   b_truth_tag_chg_550 = fChain->GetBranch("truth_tag_chg_550");
   b_tag_opp_side = fChain->GetBranch("tag_opp_side");
   b_tag_opp_withveto = fChain->GetBranch("tag_opp_withveto");

   return kTRUE;
}

void reduceData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t reduceData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef reduceData_cxx
