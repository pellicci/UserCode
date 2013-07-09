#include<iostream>

#include "TFile.h"
#include "TTree.h"
#include "TVectorF.h"
#include "TClonesArray.h"

#include "UserCode/DTDPGAnalysis/interface/DefineTreeVariables.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "TrackingTools/GeomPropagators/interface/Propagator.h"


//
// class declaration
//
class TTreeGenerator : public edm::EDAnalyzer {
  
public:
  explicit TTreeGenerator(const edm::ParameterSet&);
  ~TTreeGenerator() {};
  
  
private:

  virtual void beginJob() ;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&) {};
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  void initialize_Tree_variables();
  inline void clear_Arrays();

  void fill_digi_variables(edm::Handle<DTDigiCollection> dtdigis);
  void fill_dtsegments_variables(edm::Handle<DTRecSegment4DCollection> segments4D);
  void fill_cscsegments_variables(edm::Handle<CSCSegmentCollection> cscsegments);
  void fill_dcc_variables(edm::Handle<L1MuDTChambPhContainer> localTriggerDCC);
  void fill_dccth_variables(edm::Handle<L1MuDTChambThContainer> localTriggerDCC_Th);
  void fill_simdcc_variables(edm::Handle<L1MuDTChambPhContainer> localTriggerDCC);
  void fill_simdccth_variables(edm::Handle<L1MuDTChambThContainer> localTriggerDCC_Th);
  void fill_ddu_variables(edm::Handle<DTLocalTriggerCollection> localTriggerDDU);
  void fill_muons_variables(edm::Handle<reco::MuonCollection> MuList);
  void fill_gmt_variables(edm::Handle<L1MuGMTReadoutCollection> gmtrc);
  void fill_gt_variables(edm::Handle<L1GlobalTriggerReadoutRecord> gtrr, const L1GtTriggerMenu* menu);
  void fill_hlt_variables(const edm::Event& e, edm::Handle<edm::TriggerResults> hltresults);
  void fill_rpc_variables(const edm::Event &e, edm::Handle<RPCRecHitCollection> rpcrechits);
  void fill_dtphi_info(const DTChamberRecSegment2D* phiSeg,const GeomDet* geomDet);
  void fill_dtz_info(const DTSLRecSegment2D* zSeg, const GeomDet* geomDet);

  std::vector<L1MuRegionalCand> getBXCands(const L1MuGMTReadoutRecord* igmtrr, const int DetectorType) const;

  TrajectoryStateOnSurface cylExtrapTrkSam(reco::TrackRef track, const float rho) const;
  FreeTrajectoryState freeTrajStateMuon(const reco::TrackRef track) const;

  edm::InputTag dtDigiLabel_;
  edm::InputTag dtSegmentLabel_;
  edm::InputTag cscSegmentLabel_;
  edm::InputTag dtTrigDCCLabel_;
  edm::InputTag dtTrigSimDCCLabel_;
  edm::InputTag dtTrigDDULabel_;
  edm::InputTag staMuLabel_;
  edm::InputTag gmtLabel_;
  edm::InputTag gtLabel_;
  edm::InputTag rpcRecHitLabel_;

  edm::InputTag PrimaryVertexTag_;
  edm::InputTag beamSpotTag_;
  edm::InputTag scalersSource_;

  edm::InputTag triggerTag_;

  bool runOnRaw_;
  bool runOnSimulation_;

  std::string outFile_;

  edm::ESHandle<MagneticField> theBField;
  edm::ESHandle<Propagator> propagatorAlong;
  edm::ESHandle<Propagator> propagatorOpposite;

  edm::ESHandle<GlobalTrackingGeometry> theTrackingGeometry;

  int digisSize_;
  int dtsegmentsSize_;
  int cscsegmentsSize_;
  int dtltDCCSize_;
  int dtltDCCThSize_;
  int dtltSimDCCSize_;
  int dtltSimDCCThSize_;
  int dtltDDUSize_;
  int gmtSize_;
  int STAMuSize_;
  int rpcRecHitSize_;

  //counters
  short idigis;
  short idtsegments;
  short icscsegments;
  short idtltDCC;
  short idtltDCC_th;
  short idtltSimDCC;
  short idtltSimDCC_th;
  short idtltDDU;
  short imuons;
  short igmtdt;
  short igmtcands;
  short igtalgo;
  short igttt;
  short ihlt;
  short irpcrechits;

  reco::BeamSpot beamspot;

  TFile *outFile;
  TTree *tree_;

};
