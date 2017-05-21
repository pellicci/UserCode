#ifndef MuMuCutOptimizer_h
#define MuMuCutOptimizer_h

#include <TVector3.h>
#include <TH1F.h>

#include "smallHBaseClass.h"
#include <vector>

class MuMuCutOptimizer : public smallHBaseClass{
public:
  
  MuMuCutOptimizer(TChain *tree=0);
  virtual ~MuMuCutOptimizer() {};
  void Loop(TString optVar);
  bool accept_glb_mu(const int mu_index, float cut, float cut2, TString optVar) const;
  bool accept_trk_mu(const int mu_index, float cut, float cut2, TString optVar) const;

private:

  int MIN_nhits_trk;
  float MAX_normchi2_trk;
  float MAX_normchi2_glb;
  int MIN_nhits_pixel;
  float MAX_d0_trk;
  float MAX_dz_trk;

  float MIN_P;
  float MIN_PtBar;
  float MIN_PtEndc;
  float MAX_S3Dip;
  float MIN_Chi2;
  float MAX_iso;

  int n_step;
  int n_signal;

  bool optCond;
  TString optVar;
  float weight;

};
#endif

