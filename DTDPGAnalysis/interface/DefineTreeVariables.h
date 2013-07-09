//This is the list and types of the variables saved in the TTree;
//New variables must be declared here

#include "TString.h"

//event variables
int runnumber;
int lumiblock;
int eventNumber;
float timestamp;
int bunchXing;
int orbitNum;

//primary vertex
float PV_x;
float PV_y;
float PV_z;

float PV_xxE;
float PV_yyE;
float PV_zzE;
float PV_xyE;
float PV_xzE;
float PV_yzE;

float PV_normchi2;
float PV_Nvtx;

//luminosity
float lumiperblock;
float beam1Intensity;
float beam2Intensity;

// HLT
std::vector<TString> hlt_path;

//digi variables
std::vector<short> digi_wheel;
std::vector<short> digi_sector;
std::vector<short> digi_station;
std::vector<short> digi_sl;
std::vector<short> digi_layer;
std::vector<short> digi_wire;
std::vector<float> digi_time;

//DT segment variables
std::vector<short> segm4D_wheel;
std::vector<short> segm4D_sector;
std::vector<short> segm4D_station;

std::vector<short> segm4D_hasPhi;
std::vector<short> segm4D_hasZed;

std::vector<float> segm4D_x_pos_loc;
std::vector<float> segm4D_y_pos_loc;
std::vector<float> segm4D_z_pos_loc;
std::vector<float> segm4D_x_dir_loc;
std::vector<float> segm4D_y_dir_loc;
std::vector<float> segm4D_z_dir_loc;

std::vector<float> segm4D_cosx;
std::vector<float> segm4D_cosy;
std::vector<float> segm4D_cosz;
std::vector<float> segm4D_phi;
std::vector<float> segm4D_theta;
std::vector<float> segm4D_eta;

std::vector<float> segm4D_t0;
std::vector<float> segm4D_vdrift;
std::vector<float> segm4D_phinormchi2;
std::vector<short> segm4D_phinhits;

std::vector<float> segm4D_znormchi2;
std::vector<short> segm4D_znhits;

TClonesArray *segm4D_phiHits_Pos;
TClonesArray *segm4D_phiHits_PosCh;
TClonesArray *segm4D_phiHits_PosErr;
TClonesArray *segm4D_phiHits_Side;
TClonesArray *segm4D_phiHits_Wire;
TClonesArray *segm4D_phiHits_Layer;

TClonesArray *segm4D_zHits_Pos;
TClonesArray *segm4D_zHits_PosCh;
TClonesArray *segm4D_zHits_PosErr;
TClonesArray *segm4D_zHits_Side;
TClonesArray *segm4D_zHits_Wire;
TClonesArray *segm4D_zHits_Layer;

//CSC segment variables
std::vector<short> cscsegm_ring;
std::vector<short> cscsegm_chamber;
std::vector<short> cscsegm_station;
std::vector<float> cscsegm_cosx;
std::vector<float> cscsegm_cosy;
std::vector<float> cscsegm_cosz;
std::vector<float> cscsegm_phi;
std::vector<float> cscsegm_eta;
std::vector<float> cscsegm_normchi2;
std::vector<short> cscsegm_nRecHits;

//DCC variables
std::vector<short> ltDCC_wheel;
std::vector<short> ltDCC_sector;
std::vector<short> ltDCC_station;
std::vector<short> ltDCC_quality;
std::vector<short> ltDCC_bx;
std::vector<float> ltDCC_phi;
std::vector<float> ltDCC_phiB;
std::vector<short> ltDCC_is2nd;

std::vector<short> ltDCC_thBx;
std::vector<short> ltDCC_thWheel;
std::vector<short> ltDCC_thSector;
std::vector<short> ltDCC_thStation;
std::vector<short> ltDCC_thHits;


// Simuation (emulator) DCC variables
std::vector<short> ltDCCemu_wheel;
std::vector<short> ltDCCemu_sector;
std::vector<short> ltDCCemu_station;
std::vector<short> ltDCCemu_quality;
std::vector<short> ltDCCemu_bx;
std::vector<float> ltDCCemu_phi;
std::vector<float> ltDCCemu_phiB;
std::vector<short> ltDCCemu_is2nd;

std::vector<short> ltDCCemu_thBx;
std::vector<short> ltDCCemu_thWheel;
std::vector<short> ltDCCemu_thSector;
std::vector<short> ltDCCemu_thStation;
std::vector<short> ltDCCemu_thHits;


//DDU variables
std::vector<short> ltDDU_wheel;
std::vector<short> ltDDU_sector;
std::vector<short> ltDDU_station;
std::vector<short> ltDDU_bx;
std::vector<short> ltDDU_phiQual;
std::vector<short> ltDDU_thQual;
std::vector<short> ltDDU_is2nd;

//muon variables
std::vector<short> STAMu_isMuGlobal;
std::vector<short> STAMu_isMuTracker;
std::vector<int>   STAMu_numberOfChambers;
std::vector<int>   STAMu_numberOfMatches;
std::vector<int>   STAMu_numberOfHits;
std::vector<int>   STAMu_segmIndex;

std::vector<float> Mu_px_mu;
std::vector<float> Mu_py_mu;
std::vector<float> Mu_pz_mu;
std::vector<float> Mu_phi_mu;
std::vector<float> Mu_eta_mu;
std::vector<short> STAMu_recHitsSize;
std::vector<float> STAMu_normchi2Mu;
std::vector<short> STAMu_chargeMu;
std::vector<float> STAMu_dxyMu;
std::vector<float> STAMu_dzMu;

std::vector<float> GLBMu_normchi2Mu;
std::vector<float> GLBMu_dxyMu;
std::vector<float> GLBMu_dzMu;

std::vector<int> GLBMu_numberOfPixelHits;
std::vector<int> GLBMu_numberOfTrackerHits;

std::vector<float> GLBMu_tkIsoR03;
std::vector<float> GLBMu_ntkIsoR03;
std::vector<float> GLBMu_emIsoR03;
std::vector<float> GLBMu_hadIsoR03;

std::vector<float> STAMu_caloCompatibility;

std::vector<float> STAMu_z_mb2;
std::vector<float> STAMu_phi_mb2;
std::vector<float> STAMu_pseta_mb2;

//GMT
std::vector<short> gmt_bx;
std::vector<float> gmt_phi;
std::vector<float> gmt_eta;
std::vector<float> gmt_pt;
std::vector<short> gmt_qual;
std::vector<short> gmt_detector;

std::vector<short> gmt_cands_fwd;
std::vector<short> gmt_cands_isRpc;
std::vector<short> gmt_cands_bx;
std::vector<float> gmt_cands_phi;
std::vector<float> gmt_cands_eta;
std::vector<float> gmt_cands_pt;
std::vector<short> gmt_cands_qual;
std::vector<short> gmt_cands_ismatched;

//GT
std::vector<short> gt_algo_bx;
std::vector<short> gt_algo_bit;
std::vector<short> gt_tt_bx;
std::vector<short> gt_tt_bit;

//RPC
std::vector<int>   rpc_region;
std::vector<int>   rpc_clusterSize;
std::vector<int>   rpc_strip;
std::vector<int>   rpc_bx;
std::vector<int>   rpc_station;
std::vector<int>   rpc_sector;
std::vector<int>   rpc_layer;
std::vector<int>   rpc_subsector;
std::vector<int>   rpc_roll;
std::vector<int>   rpc_ring;
