//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tyhu Jul 15 15:49:40 2010 by ROOT version 5.22/00d
// from TTree DTTree/CMSSW DT tree
// found on file: /afs/cern.ch/user/p/pellicci/data/DPG/Dumper/rootuples/DTTree.root
//////////////////////////////////////////////////////////

#ifndef AnalyzeNtuple_h
#define AnalyzeNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>

class AnalyzeNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runnumber;
   Int_t           lumiblock;
   Int_t           eventNumber;
   Float_t         timestamp;
   Int_t           bunchXing;
   Int_t           orbitNum;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         PV_xxE;
   Float_t         PV_yyE;
   Float_t         PV_zzE;
   Float_t         PV_xyE;
   Float_t         PV_xzE;
   Float_t         PV_yzE;
   Float_t         PV_normchi2;
   Int_t           triggerWord;
   vector<short>   *digi_wheel;
   vector<short>   *digi_sector;
   vector<short>   *digi_station;
   vector<short>   *digi_sl;
   vector<short>   *digi_layer;
   vector<short>   *digi_wire;
   vector<float>   *digi_time;
   vector<short>   *dtsegm4D_wheel;
   vector<short>   *dtsegm4D_sector;
   vector<short>   *dtsegm4D_station;
   vector<short>   *dtsegm4D_hasPhi;
   vector<short>   *dtsegm4D_hasZed;
   vector<float>   *dtsegm4D_x_pos_loc;
   vector<float>   *dtsegm4D_y_pos_loc;
   vector<float>   *dtsegm4D_z_pos_loc;
   vector<float>   *dtsegm4D_x_dir_loc;
   vector<float>   *dtsegm4D_y_dir_loc;
   vector<float>   *dtsegm4D_z_dir_loc;
   vector<float>   *dtsegm4D_cosx;
   vector<float>   *dtsegm4D_cosy;
   vector<float>   *dtsegm4D_cosz;
   vector<float>   *dtsegm4D_phi;
   vector<float>   *dtsegm4D_theta;
   vector<float>   *dtsegm4D_eta;
   vector<float>   *dtsegm4D_t0;
   vector<float>   *dtsegm4D_phinormchisq;
   vector<short>   *dtsegm4D_phinhits;
   vector<float>   *dtsegm4D_znormchisq;
   vector<short>   *dtsegm4D_znhits;
   TClonesArray    *dtsegm4D_phi_hitsPos;
   TClonesArray    *dtsegm4D_phi_hitsPosErr;
   TClonesArray    *dtsegm4D_phi_hitsSide;
   TClonesArray    *dtsegm4D_z_hitsPos;
   TClonesArray    *dtsegm4D_z_hitsPosErr;
   TClonesArray    *dtsegm4D_z_hitsSide;
   vector<short>   *cscsegm_ring;
   vector<short>   *cscsegm_chamber;
   vector<short>   *cscsegm_station;
   vector<float>   *cscsegm_cosx;
   vector<float>   *cscsegm_cosy;
   vector<float>   *cscsegm_cosz;
   vector<float>   *cscsegm_phi;
   vector<float>   *cscsegm_eta;
   vector<float>   *cscsegm_normchisq;
   vector<short>   *cscsegm_nRecHits;
   vector<short>   *ltDCC_wheel;
   vector<short>   *ltDCC_sector;
   vector<short>   *ltDCC_station;
   vector<short>   *ltDCC_quality;
   vector<short>   *ltDCC_bx;
   vector<float>   *ltDCC_phi;
   vector<float>   *ltDCC_phiB;
   vector<short>   *ltDCC_is2nd;
   vector<short>   *ltDDU_wheel;
   vector<short>   *ltDDU_sector;
   vector<short>   *ltDDU_station;
   vector<short>   *ltDDU_bx;
   vector<short>   *ltDDU_phiQual;
   vector<short>   *ltDDU_thQual;
   vector<short>   *ltDDU_is2nd;
   vector<short>   *Mu_isMuGlobal;
   vector<short>   *Mu_isMuTracker;
   vector<int>     *Mu_numberOfChambers_sta;
   vector<int>     *Mu_numberOfMatches_sta;
   vector<int>     *Mu_numberOfHits_sta;
   vector<Long64_t>    *Mu_segmentIndex_sta;
   vector<float>   *Mu_px;
   vector<float>   *Mu_py;
   vector<float>   *Mu_pz;
   vector<float>   *Mu_phi;
   vector<float>   *Mu_eta;
   vector<short>   *Mu_recHitsSize;
   vector<float>   *Mu_normchi2_sta;
   vector<short>   *Mu_charge;
   vector<float>   *Mu_dxy_sta;
   vector<float>   *Mu_dz_sta;
   vector<float>   *Mu_normchi2_glb;
   vector<float>   *Mu_dxy_glb;
   vector<float>   *Mu_dz_glb;
   vector<float>   *Mu_tkIsoR03_glb;
   vector<float>   *Mu_ntkIsoR03_glb;
   vector<float>   *Mu_emIsoR03_glb;
   vector<float>   *Mu_hadIsoR03_glb;
   vector<float>   *STAMu_caloCompatibility;
   vector<float>   *Mu_z_mb2_mu;
   vector<float>   *Mu_phi_mb2_mu;
   vector<float>   *Mu_pseta_mb2_mu;
   vector<short>   *gmt_bx;
   vector<float>   *gmt_phi;
   vector<float>   *gmt_eta;
   vector<float>   *gmt_pt;
   vector<short>   *gmt_qual;
   vector<short>   *gmt_detector;
   vector<short>   *gmt_cands_fwd;
   vector<short>   *gmt_cands_isRpc;
   vector<short>   *gmt_cands_bx;
   vector<float>   *gmt_cands_phi;
   vector<float>   *gmt_cands_eta;
   vector<float>   *gmt_cands_pt;
   vector<short>   *gmt_cands_qual;
   vector<short>   *gmt_cands_ismatched;
   Short_t         Ndigis;
   Short_t         Ndtsegments;
   Short_t         Ncscsegments;
   Short_t         NdtltDCC;
   Short_t         NdtltDDU;
   Short_t         Nmuons;
   Short_t         Ngmt;
   Short_t         Ngmtcands;

   // List of branches
   TBranch        *b_runnumber;   //!
   TBranch        *b_lumiblock;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_timestamp;   //!
   TBranch        *b_bunchXing;   //!
   TBranch        *b_orbitNum;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_PV_xxE;   //!
   TBranch        *b_PV_yyE;   //!
   TBranch        *b_PV_zzE;   //!
   TBranch        *b_PV_xyE;   //!
   TBranch        *b_PV_xzE;   //!
   TBranch        *b_PV_yzE;   //!
   TBranch        *b_PV_normch2;   //!
   TBranch        *b_triggerWord;   //!
   TBranch        *b_digi_wheel;   //!
   TBranch        *b_digi_sector;   //!
   TBranch        *b_digi_station;   //!
   TBranch        *b_digi_sl;   //!
   TBranch        *b_digi_layer;   //!
   TBranch        *b_digi_wire;   //!
   TBranch        *b_digi_time;   //!
   TBranch        *b_dtsegm4D_wheel;   //!
   TBranch        *b_dtsegm4D_sector;   //!
   TBranch        *b_dtsegm4D_station;   //!
   TBranch        *b_dtsegm4D_hasPhi;   //!
   TBranch        *b_dtsegm4D_hasZed;   //!
   TBranch        *b_dtsegm4D_x_pos_loc;   //!
   TBranch        *b_dtsegm4D_y_pos_loc;   //!
   TBranch        *b_dtsegm4D_z_pos_loc;   //!
   TBranch        *b_dtsegm4D_x_dir_loc;   //!
   TBranch        *b_dtsegm4D_y_dir_loc;   //!
   TBranch        *b_dtsegm4D_z_dir_loc;   //!
   TBranch        *b_dtsegm4D_cosx;   //!
   TBranch        *b_dtsegm4D_cosy;   //!
   TBranch        *b_dtsegm4D_cosz;   //!
   TBranch        *b_dtsegm4D_phi;   //!
   TBranch        *b_dtsegm4D_theta;   //!
   TBranch        *b_dtsegm4D_eta;   //!
   TBranch        *b_dtsegm4D_t0;   //!
   TBranch        *b_dtsegm4D_phinormchisq;   //!
   TBranch        *b_dtsegm4D_phinhits;   //!
   TBranch        *b_dtsegm4D_znormchisq;   //!
   TBranch        *b_dtsegm4D_znhits;   //!
   TBranch        *b_dtsegm4D_phi_hitsPos;   //!
   TBranch        *b_dtsegm4D_phi_hitsPosErr;   //!
   TBranch        *b_dtsegm4D_phi_hitsSide;   //!
   TBranch        *b_dtsegm4D_z_hitsPos;   //!
   TBranch        *b_dtsegm4D_z_hitsPosErr;   //!
   TBranch        *b_dtsegm4D_z_hitsSide;   //!
   TBranch        *b_cscsegm_ring;   //!
   TBranch        *b_cscsegm_chamber;   //!
   TBranch        *b_cscsegm_station;   //!
   TBranch        *b_cscsegm_cosx;   //!
   TBranch        *b_cscsegm_cosy;   //!
   TBranch        *b_cscsegm_cosz;   //!
   TBranch        *b_cscsegm_phi;   //!
   TBranch        *b_cscsegm_eta;   //!
   TBranch        *b_cscsegm_normchisq;   //!
   TBranch        *b_cscsegm_nRecHits;   //!
   TBranch        *b_ltDCC_wheel;   //!
   TBranch        *b_ltDCC_sector;   //!
   TBranch        *b_ltDCC_station;   //!
   TBranch        *b_ltDCC_quality;   //!
   TBranch        *b_ltDCC_bx;   //!
   TBranch        *b_ltDCC_phi;   //!
   TBranch        *b_ltDCC_phiB;   //!
   TBranch        *b_ltDCC_is2nd;   //!
   TBranch        *b_ltDDU_wheel;   //!
   TBranch        *b_ltDDU_sector;   //!
   TBranch        *b_ltDDU_station;   //!
   TBranch        *b_ltDDU_bx;   //!
   TBranch        *b_ltDDU_phiQual;   //!
   TBranch        *b_ltDDU_thQual;   //!
   TBranch        *b_ltDDU_is2nd;   //!
   TBranch        *b_Mu_isMuGlobal;   //!
   TBranch        *b_Mu_isMuTracker;   //!
   TBranch        *b_Mu_numberOfChambers_sta;   //!
   TBranch        *b_Mu_numberOfMatches_sta;   //!
   TBranch        *b_Mu_numberOfHits_sta;   //!
   TBranch        *b_Mu_segmentIndex_sta;   //!
   TBranch        *b_Mu_px;   //!
   TBranch        *b_Mu_py;   //!
   TBranch        *b_Mu_pz;   //!
   TBranch        *b_Mu_phi;   //!
   TBranch        *b_Mu_eta;   //!
   TBranch        *b_Mu_recHitsSize;   //!
   TBranch        *b_Mu_normchi2_sta;   //!
   TBranch        *b_Mu_charge;   //!
   TBranch        *b_Mu_dxy_sta;   //!
   TBranch        *b_Mu_dz_sta;   //!
   TBranch        *b_Mu_normchi2_glb;   //!
   TBranch        *b_Mu_dxy_glb;   //!
   TBranch        *b_Mu_dz_glb;   //!
   TBranch        *b_Mu_tkIsoR03_glb;   //!
   TBranch        *b_Mu_ntkIsoR03_glb;   //!
   TBranch        *b_Mu_emIsoR03_glb;   //!
   TBranch        *b_Mu_hadIsoR03_glb;   //!
   TBranch        *b_STAMu_caloCompatibility;   //!
   TBranch        *b_Mu_z_mb2_mu;   //!
   TBranch        *b_Mu_phi_mb2_mu;   //!
   TBranch        *b_Mu_pseta_mb2_mu;   //!
   TBranch        *b_gmt_bx;   //!
   TBranch        *b_gmt_phi;   //!
   TBranch        *b_gmt_eta;   //!
   TBranch        *b_gmt_pt;   //!
   TBranch        *b_gmt_qual;   //!
   TBranch        *b_gmt_detector;   //!
   TBranch        *b_gmt_cands_fwd;   //!
   TBranch        *b_gmt_cands_isRpc;   //!
   TBranch        *b_gmt_cands_bx;   //!
   TBranch        *b_gmt_cands_phi;   //!
   TBranch        *b_gmt_cands_eta;   //!
   TBranch        *b_gmt_cands_pt;   //!
   TBranch        *b_gmt_cands_qual;   //!
   TBranch        *b_gmt_cands_ismatched;   //!
   TBranch        *b_Ndigis;   //!
   TBranch        *b_Ndtsegments;   //!
   TBranch        *b_Ncscsegments;   //!
   TBranch        *b_NdtltDCC;   //!
   TBranch        *b_NdtltDDU;   //!
   TBranch        *b_Nmuons;   //!
   TBranch        *b_Ngmt;   //!
   TBranch        *b_Ngmtcands;   //!

   AnalyzeNtuple(TTree *tree=0);
   virtual ~AnalyzeNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalyzeNtuple_cxx
AnalyzeNtuple::AnalyzeNtuple(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/user/p/pellicci/data/DPG/Dumper/rootuples/DTTree.root");
      if (!f) {
         f = new TFile("/afs/cern.ch/user/p/pellicci/data/DPG/Dumper/rootuples/DTTree.root");
      }
      tree = (TTree*)gDirectory->Get("DTTree");

   }
   Init(tree);
}

AnalyzeNtuple::~AnalyzeNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalyzeNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalyzeNtuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AnalyzeNtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   digi_wheel = 0;
   digi_sector = 0;
   digi_station = 0;
   digi_sl = 0;
   digi_layer = 0;
   digi_wire = 0;
   digi_time = 0;
   dtsegm4D_wheel = 0;
   dtsegm4D_sector = 0;
   dtsegm4D_station = 0;
   dtsegm4D_hasPhi = 0;
   dtsegm4D_hasZed = 0;
   dtsegm4D_x_pos_loc = 0;
   dtsegm4D_y_pos_loc = 0;
   dtsegm4D_z_pos_loc = 0;
   dtsegm4D_x_dir_loc = 0;
   dtsegm4D_y_dir_loc = 0;
   dtsegm4D_z_dir_loc = 0;
   dtsegm4D_cosx = 0;
   dtsegm4D_cosy = 0;
   dtsegm4D_cosz = 0;
   dtsegm4D_phi = 0;
   dtsegm4D_theta = 0;
   dtsegm4D_eta = 0;
   dtsegm4D_t0 = 0;
   dtsegm4D_phinormchisq = 0;
   dtsegm4D_phinhits = 0;
   dtsegm4D_znormchisq = 0;
   dtsegm4D_znhits = 0;
   dtsegm4D_phi_hitsPos = 0;
   dtsegm4D_phi_hitsPosErr = 0;
   dtsegm4D_phi_hitsSide = 0;
   dtsegm4D_z_hitsPos = 0;
   dtsegm4D_z_hitsPosErr = 0;
   dtsegm4D_z_hitsSide = 0;
   cscsegm_ring = 0;
   cscsegm_chamber = 0;
   cscsegm_station = 0;
   cscsegm_cosx = 0;
   cscsegm_cosy = 0;
   cscsegm_cosz = 0;
   cscsegm_phi = 0;
   cscsegm_eta = 0;
   cscsegm_normchisq = 0;
   cscsegm_nRecHits = 0;
   ltDCC_wheel = 0;
   ltDCC_sector = 0;
   ltDCC_station = 0;
   ltDCC_quality = 0;
   ltDCC_bx = 0;
   ltDCC_phi = 0;
   ltDCC_phiB = 0;
   ltDCC_is2nd = 0;
   ltDDU_wheel = 0;
   ltDDU_sector = 0;
   ltDDU_station = 0;
   ltDDU_bx = 0;
   ltDDU_phiQual = 0;
   ltDDU_thQual = 0;
   ltDDU_is2nd = 0;
   Mu_isMuGlobal = 0;
   Mu_isMuTracker = 0;
   Mu_numberOfChambers_sta = 0;
   Mu_numberOfMatches_sta = 0;
   Mu_numberOfHits_sta = 0;
   Mu_segmentIndex_sta = 0;
   Mu_px = 0;
   Mu_py = 0;
   Mu_pz = 0;
   Mu_phi = 0;
   Mu_eta = 0;
   Mu_recHitsSize = 0;
   Mu_normchi2_sta = 0;
   Mu_charge = 0;
   Mu_dxy_sta = 0;
   Mu_dz_sta = 0;
   Mu_normchi2_glb = 0;
   Mu_dxy_glb = 0;
   Mu_dz_glb = 0;
   Mu_tkIsoR03_glb = 0;
   Mu_ntkIsoR03_glb = 0;
   Mu_emIsoR03_glb = 0;
   Mu_hadIsoR03_glb = 0;
   STAMu_caloCompatibility = 0;
   Mu_z_mb2_mu = 0;
   Mu_phi_mb2_mu = 0;
   Mu_pseta_mb2_mu = 0;
   gmt_bx = 0;
   gmt_phi = 0;
   gmt_eta = 0;
   gmt_pt = 0;
   gmt_qual = 0;
   gmt_detector = 0;
   gmt_cands_fwd = 0;
   gmt_cands_isRpc = 0;
   gmt_cands_bx = 0;
   gmt_cands_phi = 0;
   gmt_cands_eta = 0;
   gmt_cands_pt = 0;
   gmt_cands_qual = 0;
   gmt_cands_ismatched = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
   fChain->SetBranchAddress("lumiblock", &lumiblock, &b_lumiblock);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("timestamp", &timestamp, &b_timestamp);
   fChain->SetBranchAddress("bunchXing", &bunchXing, &b_bunchXing);
   fChain->SetBranchAddress("orbitNum", &orbitNum, &b_orbitNum);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("PV_xxE", &PV_xxE, &b_PV_xxE);
   fChain->SetBranchAddress("PV_yyE", &PV_yyE, &b_PV_yyE);
   fChain->SetBranchAddress("PV_zzE", &PV_zzE, &b_PV_zzE);
   fChain->SetBranchAddress("PV_xyE", &PV_xyE, &b_PV_xyE);
   fChain->SetBranchAddress("PV_xzE", &PV_xzE, &b_PV_xzE);
   fChain->SetBranchAddress("PV_yzE", &PV_yzE, &b_PV_yzE);
   fChain->SetBranchAddress("PV_normchi2", &PV_normchi2, &b_PV_normch2);
   fChain->SetBranchAddress("triggerWord", &triggerWord, &b_triggerWord);
   fChain->SetBranchAddress("digi_wheel", &digi_wheel, &b_digi_wheel);
   fChain->SetBranchAddress("digi_sector", &digi_sector, &b_digi_sector);
   fChain->SetBranchAddress("digi_station", &digi_station, &b_digi_station);
   fChain->SetBranchAddress("digi_sl", &digi_sl, &b_digi_sl);
   fChain->SetBranchAddress("digi_layer", &digi_layer, &b_digi_layer);
   fChain->SetBranchAddress("digi_wire", &digi_wire, &b_digi_wire);
   fChain->SetBranchAddress("digi_time", &digi_time, &b_digi_time);
   fChain->SetBranchAddress("dtsegm4D_wheel", &dtsegm4D_wheel, &b_dtsegm4D_wheel);
   fChain->SetBranchAddress("dtsegm4D_sector", &dtsegm4D_sector, &b_dtsegm4D_sector);
   fChain->SetBranchAddress("dtsegm4D_station", &dtsegm4D_station, &b_dtsegm4D_station);
   fChain->SetBranchAddress("dtsegm4D_hasPhi", &dtsegm4D_hasPhi, &b_dtsegm4D_hasPhi);
   fChain->SetBranchAddress("dtsegm4D_hasZed", &dtsegm4D_hasZed, &b_dtsegm4D_hasZed);
   fChain->SetBranchAddress("dtsegm4D_x_pos_loc", &dtsegm4D_x_pos_loc, &b_dtsegm4D_x_pos_loc);
   fChain->SetBranchAddress("dtsegm4D_y_pos_loc", &dtsegm4D_y_pos_loc, &b_dtsegm4D_y_pos_loc);
   fChain->SetBranchAddress("dtsegm4D_z_pos_loc", &dtsegm4D_z_pos_loc, &b_dtsegm4D_z_pos_loc);
   fChain->SetBranchAddress("dtsegm4D_x_dir_loc", &dtsegm4D_x_dir_loc, &b_dtsegm4D_x_dir_loc);
   fChain->SetBranchAddress("dtsegm4D_y_dir_loc", &dtsegm4D_y_dir_loc, &b_dtsegm4D_y_dir_loc);
   fChain->SetBranchAddress("dtsegm4D_z_dir_loc", &dtsegm4D_z_dir_loc, &b_dtsegm4D_z_dir_loc);
   fChain->SetBranchAddress("dtsegm4D_cosx", &dtsegm4D_cosx, &b_dtsegm4D_cosx);
   fChain->SetBranchAddress("dtsegm4D_cosy", &dtsegm4D_cosy, &b_dtsegm4D_cosy);
   fChain->SetBranchAddress("dtsegm4D_cosz", &dtsegm4D_cosz, &b_dtsegm4D_cosz);
   fChain->SetBranchAddress("dtsegm4D_phi", &dtsegm4D_phi, &b_dtsegm4D_phi);
   fChain->SetBranchAddress("dtsegm4D_theta", &dtsegm4D_theta, &b_dtsegm4D_theta);
   fChain->SetBranchAddress("dtsegm4D_eta", &dtsegm4D_eta, &b_dtsegm4D_eta);
   fChain->SetBranchAddress("dtsegm4D_t0", &dtsegm4D_t0, &b_dtsegm4D_t0);
   fChain->SetBranchAddress("dtsegm4D_phinormchisq", &dtsegm4D_phinormchisq, &b_dtsegm4D_phinormchisq);
   fChain->SetBranchAddress("dtsegm4D_phinhits", &dtsegm4D_phinhits, &b_dtsegm4D_phinhits);
   fChain->SetBranchAddress("dtsegm4D_znormchisq", &dtsegm4D_znormchisq, &b_dtsegm4D_znormchisq);
   fChain->SetBranchAddress("dtsegm4D_znhits", &dtsegm4D_znhits, &b_dtsegm4D_znhits);
   fChain->SetBranchAddress("dtsegm4D_phi_hitsPos", &dtsegm4D_phi_hitsPos, &b_dtsegm4D_phi_hitsPos);
   fChain->SetBranchAddress("dtsegm4D_phi_hitsPosErr", &dtsegm4D_phi_hitsPosErr, &b_dtsegm4D_phi_hitsPosErr);
   fChain->SetBranchAddress("dtsegm4D_phi_hitsSide", &dtsegm4D_phi_hitsSide, &b_dtsegm4D_phi_hitsSide);
   fChain->SetBranchAddress("dtsegm4D_z_hitsPos", &dtsegm4D_z_hitsPos, &b_dtsegm4D_z_hitsPos);
   fChain->SetBranchAddress("dtsegm4D_z_hitsPosErr", &dtsegm4D_z_hitsPosErr, &b_dtsegm4D_z_hitsPosErr);
   fChain->SetBranchAddress("dtsegm4D_z_hitsSide", &dtsegm4D_z_hitsSide, &b_dtsegm4D_z_hitsSide);
   fChain->SetBranchAddress("cscsegm_ring", &cscsegm_ring, &b_cscsegm_ring);
   fChain->SetBranchAddress("cscsegm_chamber", &cscsegm_chamber, &b_cscsegm_chamber);
   fChain->SetBranchAddress("cscsegm_station", &cscsegm_station, &b_cscsegm_station);
   fChain->SetBranchAddress("cscsegm_cosx", &cscsegm_cosx, &b_cscsegm_cosx);
   fChain->SetBranchAddress("cscsegm_cosy", &cscsegm_cosy, &b_cscsegm_cosy);
   fChain->SetBranchAddress("cscsegm_cosz", &cscsegm_cosz, &b_cscsegm_cosz);
   fChain->SetBranchAddress("cscsegm_phi", &cscsegm_phi, &b_cscsegm_phi);
   fChain->SetBranchAddress("cscsegm_eta", &cscsegm_eta, &b_cscsegm_eta);
   fChain->SetBranchAddress("cscsegm_normchisq", &cscsegm_normchisq, &b_cscsegm_normchisq);
   fChain->SetBranchAddress("cscsegm_nRecHits", &cscsegm_nRecHits, &b_cscsegm_nRecHits);
   fChain->SetBranchAddress("ltDCC_wheel", &ltDCC_wheel, &b_ltDCC_wheel);
   fChain->SetBranchAddress("ltDCC_sector", &ltDCC_sector, &b_ltDCC_sector);
   fChain->SetBranchAddress("ltDCC_station", &ltDCC_station, &b_ltDCC_station);
   fChain->SetBranchAddress("ltDCC_quality", &ltDCC_quality, &b_ltDCC_quality);
   fChain->SetBranchAddress("ltDCC_bx", &ltDCC_bx, &b_ltDCC_bx);
   fChain->SetBranchAddress("ltDCC_phi", &ltDCC_phi, &b_ltDCC_phi);
   fChain->SetBranchAddress("ltDCC_phiB", &ltDCC_phiB, &b_ltDCC_phiB);
   fChain->SetBranchAddress("ltDCC_is2nd", &ltDCC_is2nd, &b_ltDCC_is2nd);
   fChain->SetBranchAddress("ltDDU_wheel", &ltDDU_wheel, &b_ltDDU_wheel);
   fChain->SetBranchAddress("ltDDU_sector", &ltDDU_sector, &b_ltDDU_sector);
   fChain->SetBranchAddress("ltDDU_station", &ltDDU_station, &b_ltDDU_station);
   fChain->SetBranchAddress("ltDDU_bx", &ltDDU_bx, &b_ltDDU_bx);
   fChain->SetBranchAddress("ltDDU_phiQual", &ltDDU_phiQual, &b_ltDDU_phiQual);
   fChain->SetBranchAddress("ltDDU_thQual", &ltDDU_thQual, &b_ltDDU_thQual);
   fChain->SetBranchAddress("ltDDU_is2nd", &ltDDU_is2nd, &b_ltDDU_is2nd);
   fChain->SetBranchAddress("Mu_isMuGlobal", &Mu_isMuGlobal, &b_Mu_isMuGlobal);
   fChain->SetBranchAddress("Mu_isMuTracker", &Mu_isMuTracker, &b_Mu_isMuTracker);
   fChain->SetBranchAddress("Mu_numberOfChambers_sta", &Mu_numberOfChambers_sta, &b_Mu_numberOfChambers_sta);
   fChain->SetBranchAddress("Mu_numberOfMatches_sta", &Mu_numberOfMatches_sta, &b_Mu_numberOfMatches_sta);
   fChain->SetBranchAddress("Mu_numberOfHits_sta", &Mu_numberOfHits_sta, &b_Mu_numberOfHits_sta);
   fChain->SetBranchAddress("Mu_segmentIndex_sta", &Mu_segmentIndex_sta, &b_Mu_segmentIndex_sta);
   fChain->SetBranchAddress("Mu_px", &Mu_px, &b_Mu_px);
   fChain->SetBranchAddress("Mu_py", &Mu_py, &b_Mu_py);
   fChain->SetBranchAddress("Mu_pz", &Mu_pz, &b_Mu_pz);
   fChain->SetBranchAddress("Mu_phi", &Mu_phi, &b_Mu_phi);
   fChain->SetBranchAddress("Mu_eta", &Mu_eta, &b_Mu_eta);
   fChain->SetBranchAddress("Mu_recHitsSize", &Mu_recHitsSize, &b_Mu_recHitsSize);
   fChain->SetBranchAddress("Mu_normchi2_sta", &Mu_normchi2_sta, &b_Mu_normchi2_sta);
   fChain->SetBranchAddress("Mu_charge", &Mu_charge, &b_Mu_charge);
   fChain->SetBranchAddress("Mu_dxy_sta", &Mu_dxy_sta, &b_Mu_dxy_sta);
   fChain->SetBranchAddress("Mu_dz_sta", &Mu_dz_sta, &b_Mu_dz_sta);
   fChain->SetBranchAddress("Mu_normchi2_glb", &Mu_normchi2_glb, &b_Mu_normchi2_glb);
   fChain->SetBranchAddress("Mu_dxy_glb", &Mu_dxy_glb, &b_Mu_dxy_glb);
   fChain->SetBranchAddress("Mu_dz_glb", &Mu_dz_glb, &b_Mu_dz_glb);
   fChain->SetBranchAddress("Mu_tkIsoR03_glb", &Mu_tkIsoR03_glb, &b_Mu_tkIsoR03_glb);
   fChain->SetBranchAddress("Mu_ntkIsoR03_glb", &Mu_ntkIsoR03_glb, &b_Mu_ntkIsoR03_glb);
   fChain->SetBranchAddress("Mu_emIsoR03_glb", &Mu_emIsoR03_glb, &b_Mu_emIsoR03_glb);
   fChain->SetBranchAddress("Mu_hadIsoR03_glb", &Mu_hadIsoR03_glb, &b_Mu_hadIsoR03_glb);
   fChain->SetBranchAddress("STAMu_caloCompatibility", &STAMu_caloCompatibility, &b_STAMu_caloCompatibility);
   fChain->SetBranchAddress("Mu_z_mb2_mu", &Mu_z_mb2_mu, &b_Mu_z_mb2_mu);
   fChain->SetBranchAddress("Mu_phi_mb2_mu", &Mu_phi_mb2_mu, &b_Mu_phi_mb2_mu);
   fChain->SetBranchAddress("Mu_pseta_mb2_mu", &Mu_pseta_mb2_mu, &b_Mu_pseta_mb2_mu);
   fChain->SetBranchAddress("gmt_bx", &gmt_bx, &b_gmt_bx);
   fChain->SetBranchAddress("gmt_phi", &gmt_phi, &b_gmt_phi);
   fChain->SetBranchAddress("gmt_eta", &gmt_eta, &b_gmt_eta);
   fChain->SetBranchAddress("gmt_pt", &gmt_pt, &b_gmt_pt);
   fChain->SetBranchAddress("gmt_qual", &gmt_qual, &b_gmt_qual);
   fChain->SetBranchAddress("gmt_detector", &gmt_detector, &b_gmt_detector);
   fChain->SetBranchAddress("gmt_cands_fwd", &gmt_cands_fwd, &b_gmt_cands_fwd);
   fChain->SetBranchAddress("gmt_cands_isRpc", &gmt_cands_isRpc, &b_gmt_cands_isRpc);
   fChain->SetBranchAddress("gmt_cands_bx", &gmt_cands_bx, &b_gmt_cands_bx);
   fChain->SetBranchAddress("gmt_cands_phi", &gmt_cands_phi, &b_gmt_cands_phi);
   fChain->SetBranchAddress("gmt_cands_eta", &gmt_cands_eta, &b_gmt_cands_eta);
   fChain->SetBranchAddress("gmt_cands_pt", &gmt_cands_pt, &b_gmt_cands_pt);
   fChain->SetBranchAddress("gmt_cands_qual", &gmt_cands_qual, &b_gmt_cands_qual);
   fChain->SetBranchAddress("gmt_cands_ismatched", &gmt_cands_ismatched, &b_gmt_cands_ismatched);
   fChain->SetBranchAddress("Ndigis", &Ndigis, &b_Ndigis);
   fChain->SetBranchAddress("Ndtsegments", &Ndtsegments, &b_Ndtsegments);
   fChain->SetBranchAddress("Ncscsegments", &Ncscsegments, &b_Ncscsegments);
   fChain->SetBranchAddress("NdtltDCC", &NdtltDCC, &b_NdtltDCC);
   fChain->SetBranchAddress("NdtltDDU", &NdtltDDU, &b_NdtltDDU);
   fChain->SetBranchAddress("Nmuons", &Nmuons, &b_Nmuons);
   fChain->SetBranchAddress("Ngmt", &Ngmt, &b_Ngmt);
   fChain->SetBranchAddress("Ngmtcands", &Ngmtcands, &b_Ngmtcands);
   Notify();
}

Bool_t AnalyzeNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnalyzeNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnalyzeNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AnalyzeNtuple_cxx
