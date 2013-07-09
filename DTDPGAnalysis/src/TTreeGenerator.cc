// -*- C++ -*-
//
// Package:    TTreeGenerator
// Class:      TTreeGenerator
// 
/**\class TTreeGenerator TTreeGenerator.cc MyTools/TTreeGenerator/src/TTreeGenerator.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Carlo BATTILANA, Mario PELLICCIONI
//         Created:  Mon Jan 11 14:59:51 CET 2010
// $Id: TTreeGenerator.cc,v 1.33 2012/07/02 16:43:36 guiducci Exp $
//
//

// user include files
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"

#include "DataFormats/DTDigi/interface/DTDigi.h"
#include "DataFormats/DTDigi/interface/DTDigiCollection.h"
#include "DataFormats/DTDigi/interface/DTLocalTriggerCollection.h"

#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"

#include "DataFormats/GeometrySurface/interface/Cylinder.h"

#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/Luminosity/interface/LumiDetails.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"

#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/Scalers/interface/LumiScalers.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"

#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"

#include "MagneticField/Engine/interface/MagneticField.h"

#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"

#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"

#include <DataFormats/RPCDigi/interface/RPCDigiCollection.h>
#include <DataFormats/RPCRecHit/interface/RPCRecHitCollection.h>
#include <DataFormats/MuonDetId/interface/RPCDetId.h>


#include "UserCode/DTDPGAnalysis/interface/TTreeGenerator.h"
#include <iostream>


TTreeGenerator::TTreeGenerator(const edm::ParameterSet& pset)
{
  //get parameters from the configuration file
  //names of the different event collections
  dtDigiLabel_     = pset.getParameter<edm::InputTag>("dtDigiLabel");
  dtSegmentLabel_  = pset.getParameter<edm::InputTag>("dtSegmentLabel");
  cscSegmentLabel_ = pset.getParameter<edm::InputTag>("cscSegmentLabel");
  dtTrigDCCLabel_  = pset.getParameter<edm::InputTag>("dtTrigDCCLabel");
  dtTrigSimDCCLabel_  = pset.getParameter<edm::InputTag>("dtTrigSimDCCLabel");
  dtTrigDDULabel_  = pset.getParameter<edm::InputTag>("dtTrigDDULabel");
  staMuLabel_      = pset.getParameter<edm::InputTag>("staMuLabel");
  gmtLabel_        = pset.getParameter<edm::InputTag>("gmtLabel");
  triggerTag_      = pset.getParameter<edm::InputTag>("TriggerTag");
  gtLabel_         = pset.getParameter<edm::InputTag>("gtLabel");
  rpcRecHitLabel_  = pset.getParameter<edm::InputTag>("rpcRecHitLabel");

  //max size of the different saved objects (per event)
  digisSize_       = pset.getParameter<int>("dtDigiSize");
  dtsegmentsSize_  = pset.getParameter<int>("dtSegmentSize");
  cscsegmentsSize_ = pset.getParameter<int>("cscSegmentSize");
  dtltDCCSize_     = pset.getParameter<int>("dtTrigDCCSize");
  dtltDCCThSize_   = pset.getParameter<int>("dtTrigDCCThSize");
  dtltSimDCCSize_     = pset.getParameter<int>("dtTrigSimDCCSize");
  dtltSimDCCThSize_   = pset.getParameter<int>("dtTrigSimDCCThSize");
  dtltDDUSize_     = pset.getParameter<int>("dtTrigDDUSize");
  gmtSize_         = pset.getParameter<int>("gmtSize");
  STAMuSize_       = pset.getParameter<int>("STAMuSize");
  rpcRecHitSize_   = pset.getParameter<int>("rpcRecHitSize");

  PrimaryVertexTag_ = pset.getParameter<edm::InputTag>("PrimaryVertexTag");
  beamSpotTag_      = pset.getParameter<edm::InputTag>("beamSpotTag");
  scalersSource_    = pset.getParameter<edm::InputTag>("scalersResults");

  runOnRaw_        = pset.getParameter<bool>("runOnRaw");
  runOnSimulation_ = pset.getParameter<bool>("runOnSimulation");

  outFile_         = pset.getParameter<std::string>("outputFile");

  initialize_Tree_variables();

  //counters
  idigis       = 0;
  idtsegments  = 0;
  icscsegments = 0;
  idtltDCC     = 0;
  idtltDCC_th  = 0;
  idtltSimDCC     = 0;
  idtltSimDCC_th  = 0;
  idtltDDU     = 0;
  imuons       = 0;
  igmtdt       = 0;
  igmtcands    = 0;
  igtalgo      = 0;
  igttt        = 0;
  ihlt         = 0;
}

void TTreeGenerator::analyze(const edm::Event& event, const edm::EventSetup& context)
{
  //retrieve the beamspot info
  edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
  event.getByLabel(beamSpotTag_ ,recoBeamSpotHandle);
  beamspot = *recoBeamSpotHandle; 

  //retrieve the luminosity
  edm::Handle<LumiScalersCollection> lumiScalers;
  event.getByLabel(scalersSource_, lumiScalers);
  LumiScalersCollection::const_iterator lumiIt = lumiScalers->begin();
  lumiperblock = lumiIt->instantLumi();

  //retrieve the collections you are interested on in the event
  edm::Handle<DTDigiCollection> dtdigis;
  if(runOnRaw_ && !runOnSimulation_) event.getByLabel(dtDigiLabel_, dtdigis);

  edm::Handle<DTRecSegment4DCollection> dtsegments4D;
  event.getByLabel(dtSegmentLabel_, dtsegments4D);

  context.get<GlobalTrackingGeometryRecord>().get(theTrackingGeometry);

  edm::Handle<reco::VertexCollection> privtxs;
  event.getByLabel(PrimaryVertexTag_, privtxs);

  edm::Handle<CSCSegmentCollection> cscsegments;
  event.getByLabel(cscSegmentLabel_, cscsegments);

  edm::Handle<L1MuDTChambPhContainer> localTriggerDCC;
  if(runOnRaw_) event.getByLabel(dtTrigDCCLabel_,localTriggerDCC);

  edm::Handle<L1MuDTChambThContainer> localTriggerDCC_Th;
  if(runOnRaw_) event.getByLabel(dtTrigDCCLabel_,localTriggerDCC_Th);

  edm::Handle<L1MuDTChambPhContainer> localTriggerSimDCC;
  if(runOnRaw_) event.getByLabel(dtTrigSimDCCLabel_,localTriggerSimDCC);

  edm::Handle<L1MuDTChambThContainer> localTriggerSimDCC_Th;
  if(runOnRaw_) event.getByLabel(dtTrigSimDCCLabel_,localTriggerSimDCC_Th);

  edm::Handle<DTLocalTriggerCollection> localTriggerDDU;
  if(runOnRaw_ && !runOnSimulation_) event.getByLabel(dtTrigDDULabel_,localTriggerDDU);

  edm::Handle<reco::MuonCollection> MuList;
  event.getByLabel(staMuLabel_,MuList);

  edm::Handle<L1MuGMTReadoutCollection> gmtrc;
  if(runOnRaw_) event.getByLabel(gmtLabel_,gmtrc);

  edm::Handle< L1GlobalTriggerReadoutRecord > gtrc;
  if(runOnRaw_) event.getByLabel(gtLabel_, gtrc);

  edm::ESHandle<L1GtTriggerMenu> menuRcd;
  context.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
  const L1GtTriggerMenu* menu = menuRcd.product();

  edm::Handle<edm::TriggerResults>  hltresults;
  event.getByLabel(triggerTag_, hltresults);

  edm::Handle<RPCRecHitCollection> rpcHits;
  event.getByLabel(rpcRecHitLabel_,rpcHits);

  //clear the containers
  clear_Arrays();

  // Get the propagators
  context.get<TrackingComponentsRecord>().get("SmartPropagatorAny",propagatorAlong);
  context.get<TrackingComponentsRecord>().get("SmartPropagatorAnyOpposite", propagatorOpposite);

//get the magnetic field
  context.get<IdealMagneticFieldRecord>().get(theBField);

  //Fill the event info block
  runnumber = event.run();
  lumiblock = event.getLuminosityBlock().luminosityBlock();
  eventNumber = event.eventAuxiliary().event();
  timestamp = event.eventAuxiliary().time().value();
  bunchXing = event.eventAuxiliary().bunchCrossing();
  orbitNum = event.eventAuxiliary().orbitNumber();

  edm::Handle<LumiDetails> lumiDetails;
  event.getLuminosityBlock().getByLabel("lumiProducer", lumiDetails);
  if(lumiDetails->isValid()){
    beam1Intensity = lumiDetails->lumiBeam1Intensity(bunchXing);
    beam2Intensity = lumiDetails->lumiBeam2Intensity(bunchXing);
  }

  //Primary vertex
  if((*privtxs).size() != 0){
    PV_x = (*privtxs)[0].position().x();
    PV_y = (*privtxs)[0].position().y();
    PV_z = (*privtxs)[0].position().z();

    PV_xxE = (*privtxs)[0].covariance(0,0);
    PV_yyE = (*privtxs)[0].covariance(1,1);
    PV_zzE = (*privtxs)[0].covariance(2,2);
    PV_xyE = (*privtxs)[0].covariance(0,1);
    PV_xzE = (*privtxs)[0].covariance(0,2);
    PV_yzE = (*privtxs)[0].covariance(1,2);

    PV_normchi2 = (*privtxs)[0].chi2()/(*privtxs)[0].ndof();

    PV_Nvtx = (*privtxs).size();
  }
  else{
    PV_x   = -999.;
    PV_y   = -999.;
    PV_z   = -999.;
    PV_xxE = -999.;
    PV_yyE = -999.;
    PV_zzE = -999.;
    PV_xyE = -999.;
    PV_xzE = -999.;
    PV_yzE = -999.;
    PV_normchi2 = -999.;
    PV_Nvtx = -999;
  }

  //DIGIS
  if(runOnRaw_ && !runOnSimulation_) fill_digi_variables(dtdigis);

  //DT SEGMENTS
  fill_dtsegments_variables(dtsegments4D);

  //CSC SEGMENTS
  fill_cscsegments_variables(cscsegments);

  //DCC
  if(runOnRaw_) fill_dcc_variables(localTriggerDCC);
  if(runOnRaw_) fill_dccth_variables(localTriggerDCC_Th);
  if(runOnRaw_) fill_simdcc_variables(localTriggerSimDCC);
  if(runOnRaw_) fill_simdccth_variables(localTriggerSimDCC_Th);

  //DDU
  if(runOnRaw_ && !runOnSimulation_) fill_ddu_variables(localTriggerDDU);

  //MUONS
  fill_muons_variables(MuList);

  //GMT
  if(runOnRaw_) fill_gmt_variables(gmtrc);

  //GT
  if(runOnRaw_) fill_gt_variables(gtrc,menu);
    
  //HLT
  fill_hlt_variables(event,hltresults);

  // RPC
  fill_rpc_variables(event,rpcHits);
  
  tree_->Fill();

  return;
}

void TTreeGenerator::fill_digi_variables(edm::Handle<DTDigiCollection> dtdigis)
{
  idigis = 0;

  for (DTDigiCollection::DigiRangeIterator dtLayerIdIt = dtdigis->begin(); dtLayerIdIt!=dtdigis->end(); dtLayerIdIt++){

    for (DTDigiCollection::const_iterator digiIt = ((*dtLayerIdIt).second).first;digiIt!=((*dtLayerIdIt).second).second; ++digiIt){

      if(idigis >= digisSize_) return;

      digi_wheel.push_back((*dtLayerIdIt).first.wheel());
      digi_sector.push_back((*dtLayerIdIt).first.sector());
      digi_station.push_back((*dtLayerIdIt).first.station());
      digi_sl.push_back((*dtLayerIdIt).first.superLayer());
      digi_layer.push_back((*dtLayerIdIt).first.layer());

      digi_wire.push_back((*digiIt).wire());
      digi_time.push_back((*digiIt).time());

      idigis++;
    }
  }

  return;
}

void TTreeGenerator::fill_dtsegments_variables(edm::Handle<DTRecSegment4DCollection> segments4D)
{
  idtsegments = 0;

  static TVectorF dummyfloat(1); dummyfloat(0) = -999.;

  for (DTRecSegment4DCollection::id_iterator chambIt = segments4D->id_begin(); chambIt != segments4D->id_end(); ++chambIt){

    DTRecSegment4DCollection::range  range = segments4D->get(*chambIt);
    for (DTRecSegment4DCollection::const_iterator segment4D = range.first; segment4D!=range.second; ++segment4D){

      if(idtsegments >= dtsegmentsSize_) return;

      segm4D_wheel.push_back((*chambIt).wheel());
      segm4D_sector.push_back((*chambIt).sector());
      segm4D_station.push_back((*chambIt).station());

      const bool hasPhi = segment4D->hasPhi();
      const bool hasZed = segment4D->hasZed();
      segm4D_hasPhi.push_back(hasPhi);
      segm4D_hasZed.push_back(hasZed);

      segm4D_x_pos_loc.push_back(segment4D->localPosition().x());
      segm4D_y_pos_loc.push_back(segment4D->localPosition().y());
      segm4D_z_pos_loc.push_back(segment4D->localPosition().x());
      segm4D_x_dir_loc.push_back(segment4D->localDirection().x());
      segm4D_y_dir_loc.push_back(segment4D->localDirection().y());
      segm4D_z_dir_loc.push_back(segment4D->localDirection().z());

      const GeomDet* geomDet = theTrackingGeometry->idToDet(segment4D->geographicalId());
      const GlobalVector point_glb = geomDet->toGlobal(segment4D->localDirection());

      segm4D_cosx.push_back(point_glb.x());
      segm4D_cosy.push_back(point_glb.y());
      segm4D_cosz.push_back(point_glb.z());
      segm4D_phi.push_back(point_glb.phi());
      segm4D_theta.push_back(point_glb.theta());
      segm4D_eta.push_back(point_glb.eta());

      if(hasPhi) fill_dtphi_info(segment4D->phiSegment(),geomDet);
      else{
	segm4D_t0.push_back(-999.);
	segm4D_vdrift.push_back(-999.);
	segm4D_phinormchi2.push_back(-999.);
	segm4D_phinhits.push_back(-999);

	new ((*segm4D_phiHits_Pos)[idtsegments])    TVectorF(dummyfloat);
	new ((*segm4D_phiHits_PosCh)[idtsegments])  TVectorF(dummyfloat);
	new ((*segm4D_phiHits_PosErr)[idtsegments]) TVectorF(dummyfloat);
	new ((*segm4D_phiHits_Side)[idtsegments])   TVectorF(dummyfloat);
 	new ((*segm4D_phiHits_Wire)[idtsegments])   TVectorF(dummyfloat);
 	new ((*segm4D_phiHits_Layer)[idtsegments])  TVectorF(dummyfloat);
    }

      if(hasZed) fill_dtz_info(segment4D->zSegment(),geomDet);
      else{
	segm4D_znormchi2.push_back(-999.);
	segm4D_znhits.push_back(-999);

	new ((*segm4D_zHits_Pos)[idtsegments])    TVectorF(dummyfloat);
	new ((*segm4D_zHits_PosCh)[idtsegments])  TVectorF(dummyfloat);
	new ((*segm4D_zHits_PosErr)[idtsegments]) TVectorF(dummyfloat);
	new ((*segm4D_zHits_Side)[idtsegments])   TVectorF(dummyfloat);
	new ((*segm4D_zHits_Wire)[idtsegments])   TVectorF(dummyfloat);
	new ((*segm4D_zHits_Layer)[idtsegments])  TVectorF(dummyfloat);
      }

      idtsegments++;
    }
  }

  return;
}

void TTreeGenerator::fill_dtphi_info(const DTChamberRecSegment2D* phiSeg, const GeomDet* chamb)
{
  std::vector<DTRecHit1D> phirecHitslist = phiSeg->specificRecHits();

  //segment information
  segm4D_t0.push_back(phiSeg->t0());
  segm4D_vdrift.push_back(phiSeg->vDrift());

  segm4D_phinormchi2.push_back(phiSeg->chi2()/phiSeg->degreesOfFreedom());

  //rechits information
  const int nphirecHits = phirecHitslist.size();
  segm4D_phinhits.push_back(nphirecHits);

  TVectorF phiPosRechits(nphirecHits);
  TVectorF phiPosChRechits(nphirecHits);
  TVectorF phiPosErrRechits(nphirecHits);
  TVectorF phiSideRechits(nphirecHits);
  TVectorF phiwireRechits(nphirecHits);
  TVectorF philayerRechits(nphirecHits);

  int rechitscounter = 0;
  for(std::vector<DTRecHit1D>::const_iterator recHitsIt = phirecHitslist.begin(); recHitsIt!=phirecHitslist.end(); ++recHitsIt){
    const GeomDet * layer = theTrackingGeometry->idToDet(recHitsIt->wireId().layerId());
    phiPosRechits(rechitscounter)    = recHitsIt->localPosition().x();
    phiPosChRechits(rechitscounter)  = chamb->toLocal(layer->toGlobal(recHitsIt->localPosition())).x();
    phiPosErrRechits(rechitscounter) = recHitsIt->localPositionError().xx();
    phiSideRechits(rechitscounter)   = recHitsIt->lrSide();
    phiwireRechits(rechitscounter)   = recHitsIt->wireId().wire();
    philayerRechits(rechitscounter)  = recHitsIt->wireId().layerId().layer();
    rechitscounter++;
  }

  new ((*segm4D_phiHits_Pos)[idtsegments])    TVectorF(phiPosRechits);
  new ((*segm4D_phiHits_PosCh)[idtsegments])  TVectorF(phiPosChRechits);
  new ((*segm4D_phiHits_PosErr)[idtsegments]) TVectorF(phiPosErrRechits);
  new ((*segm4D_phiHits_Side)[idtsegments])   TVectorF(phiSideRechits);
  new ((*segm4D_phiHits_Wire)[idtsegments])   TVectorF(phiwireRechits);
  new ((*segm4D_phiHits_Layer)[idtsegments])  TVectorF(philayerRechits);

  return;
}

void TTreeGenerator::fill_dtz_info(const DTSLRecSegment2D* zSeg,  const GeomDet* chamb)
{
  std::vector<DTRecHit1D> zrecHitslist = zSeg->specificRecHits();

  segm4D_znormchi2.push_back(zSeg->chi2()/zSeg->degreesOfFreedom());

  //rechits information
  const int nzrecHits = zrecHitslist.size();
  segm4D_znhits.push_back(nzrecHits);

  TVectorF zPosRechits(nzrecHits);
  TVectorF zPosChRechits(nzrecHits);
  TVectorF zPosErrRechits(nzrecHits);
  TVectorF zSideRechits(nzrecHits);
  TVectorF zwireRechits(nzrecHits);
  TVectorF zlayerRechits(nzrecHits);

  int rechitscounter = 0;
  for(std::vector<DTRecHit1D>::const_iterator recHitsIt = zrecHitslist.begin(); recHitsIt!=zrecHitslist.end(); ++recHitsIt){
    const GeomDet * layer = theTrackingGeometry->idToDet(recHitsIt->wireId().layerId());
    zPosRechits(rechitscounter)    = recHitsIt->localPosition().y();
    zPosChRechits(rechitscounter)  = chamb->toLocal(layer->toGlobal(recHitsIt->localPosition())).y();
    zPosErrRechits(rechitscounter) = recHitsIt->localPositionError().yy();
    zSideRechits(rechitscounter)   = recHitsIt->lrSide();
    zwireRechits(rechitscounter)   = recHitsIt->wireId().wire();
    zlayerRechits(rechitscounter)  = recHitsIt->wireId().layerId().layer();
    rechitscounter++;
  }

  new ((*segm4D_zHits_Pos)[idtsegments])    TVectorF(zPosRechits);
  new ((*segm4D_zHits_PosCh)[idtsegments])  TVectorF(zPosChRechits);
  new ((*segm4D_zHits_PosErr)[idtsegments]) TVectorF(zPosErrRechits);
  new ((*segm4D_zHits_Side)[idtsegments])   TVectorF(zSideRechits);
  new ((*segm4D_zHits_Wire)[idtsegments])   TVectorF(zwireRechits);
  new ((*segm4D_zHits_Layer)[idtsegments])  TVectorF(zlayerRechits);

  return;
}

void TTreeGenerator::fill_cscsegments_variables(edm::Handle<CSCSegmentCollection> cscsegments)
{
  icscsegments = 0;
  for (CSCSegmentCollection::id_iterator chambIt = cscsegments->id_begin(); chambIt != cscsegments->id_end(); ++chambIt){

    CSCSegmentCollection::range  range = cscsegments->get(*chambIt);
    for (CSCSegmentCollection::const_iterator cscsegment = range.first; cscsegment!=range.second; ++cscsegment){

      if(icscsegments >= cscsegmentsSize_) return;

      cscsegm_ring.push_back((*chambIt).ring());
      cscsegm_chamber.push_back((*chambIt).chamber());
      cscsegm_station.push_back((*chambIt).station());

      const GeomDet* geomDet = theTrackingGeometry->idToDet(cscsegment->geographicalId());

      const GlobalVector point_glb = geomDet->toGlobal(cscsegment->localDirection());

      cscsegm_cosx.push_back(point_glb.x());
      cscsegm_cosy.push_back(point_glb.y());
      cscsegm_cosz.push_back(point_glb.y());


      cscsegm_normchi2.push_back(cscsegment->chi2()/cscsegment->degreesOfFreedom());
      cscsegm_nRecHits.push_back(cscsegment->nRecHits());

      icscsegments++;
    }
  }

  return;
}

void TTreeGenerator::fill_dcc_variables(edm::Handle<L1MuDTChambPhContainer> localTriggerDCC)
{

  idtltDCC = 0;
  std::vector<L1MuDTChambPhDigi>*  phTrigs = localTriggerDCC->getContainer();
  for(std::vector<L1MuDTChambPhDigi>::const_iterator iph = phTrigs->begin(); iph != phTrigs->end() ; ++iph){
    if(idtltDCC >= dtltDCCSize_) break;
    ltDCC_wheel.push_back(iph->whNum());
    ltDCC_sector.push_back(iph->scNum() + 1); // DTTF[0-11] -> DT[1-12] Sector Numbering
    ltDCC_station.push_back(iph->stNum());
    ltDCC_quality.push_back(iph->code());
    ltDCC_bx.push_back(iph->bxNum());
    ltDCC_phi.push_back(iph->phi());
    ltDCC_phiB.push_back(iph->phiB());
    ltDCC_is2nd.push_back(iph->Ts2Tag());
    idtltDCC++;
  }
  //std::cout<<"Filled "<<idtltDCC<<" phi trigger segments from DCC data"<<std::endl;
  return;
}
void TTreeGenerator::fill_simdcc_variables(edm::Handle<L1MuDTChambPhContainer> localTriggerDCC)
{
  idtltSimDCC = 0;
  std::vector<L1MuDTChambPhDigi>*  phTrigs = localTriggerDCC->getContainer();
  for(std::vector<L1MuDTChambPhDigi>::const_iterator iph = phTrigs->begin(); iph != phTrigs->end() ; ++iph){
    if(idtltSimDCC >= dtltSimDCCSize_) break;
    ltDCCemu_wheel.push_back(iph->whNum());
    ltDCCemu_sector.push_back(iph->scNum() + 1); // DTTF[0-11] -> DT[1-12] Sector Numbering
    ltDCCemu_station.push_back(iph->stNum());
    ltDCCemu_quality.push_back(iph->code());
    ltDCCemu_bx.push_back(iph->bxNum());
    ltDCCemu_phi.push_back(iph->phi());
    ltDCCemu_phiB.push_back(iph->phiB());
    ltDCCemu_is2nd.push_back(iph->Ts2Tag());
    idtltSimDCC++;
  }
  //std::cout<<"Filled "<<idtltSimDCC<<" phi trigger segments from emulator"<<std::endl;
  return;
}

void TTreeGenerator::fill_dccth_variables(edm::Handle<L1MuDTChambThContainer> localTriggerDCC_Th)
{
  idtltDCC_th = 0;
  std::vector<L1MuDTChambThDigi>*  thTrigs = localTriggerDCC_Th->getContainer();
  for(std::vector<L1MuDTChambThDigi>::const_iterator ith = thTrigs->begin(); ith != thTrigs->end() ; ++ith){
    if(idtltDCC_th >= dtltDCCThSize_) break;
    ltDCC_thWheel.push_back(ith->whNum());
    ltDCC_thSector.push_back(ith->scNum() + 1); // DTTF[0-11] -> DT[1-12] Sector Numbering
    ltDCC_thStation.push_back(ith->stNum());
    ltDCC_thBx.push_back(ith->bxNum());
    unsigned short int thcode=0;
    for (int pos=0; pos<7; pos++)
      if (ith->code(pos))
	thcode=thcode | (0x1<<pos);
    ltDCC_thHits.push_back(thcode);
    idtltDCC_th++;
  }
  return;
}
void TTreeGenerator::fill_simdccth_variables(edm::Handle<L1MuDTChambThContainer> localTriggerDCC_Th)
{
  idtltSimDCC_th = 0;
  std::vector<L1MuDTChambThDigi>*  thTrigs = localTriggerDCC_Th->getContainer();
  for(std::vector<L1MuDTChambThDigi>::const_iterator ith = thTrigs->begin(); ith != thTrigs->end() ; ++ith){
    if(idtltSimDCC_th >= dtltSimDCCThSize_) break;
    ltDCCemu_thWheel.push_back(ith->whNum());
    ltDCCemu_thSector.push_back(ith->scNum() + 1); // DTTF[0-11] -> DT[1-12] Sector Numbering
    ltDCCemu_thStation.push_back(ith->stNum());
    ltDCCemu_thBx.push_back(ith->bxNum());
    unsigned short int thcode=0;
    for (int pos=0; pos<7; pos++)
      if (ith->code(pos))
	thcode=thcode | (0x1<<pos);
    ltDCCemu_thHits.push_back(thcode);
    idtltSimDCC_th++;
  }
  return;
}

void TTreeGenerator::fill_ddu_variables(edm::Handle<DTLocalTriggerCollection> localTriggerDDU)
{
  idtltDDU = 0;
  for (DTLocalTriggerCollection::DigiRangeIterator trigUnitIt  = localTriggerDDU->begin();trigUnitIt!=localTriggerDDU->end();++trigUnitIt){

    const DTChamberId& chambId = (*trigUnitIt).first;
    const DTLocalTriggerCollection::Range& range = (*trigUnitIt).second;

    for (DTLocalTriggerCollection::const_iterator trigIt = range.first; trigIt!=range.second;++trigIt){	

      if(idtltDDU >= dtltDDUSize_) return;

      ltDDU_wheel.push_back(chambId.wheel());
      ltDDU_sector.push_back(chambId.sector());
      ltDDU_station.push_back(chambId.station());
      ltDDU_bx.push_back(trigIt->bx());
      ltDDU_phiQual.push_back(trigIt->quality());
      ltDDU_thQual.push_back(trigIt->trTheta());
      ltDDU_is2nd.push_back(trigIt->secondTrack()); 

      idtltDDU++;
    }
  }

  return;
}

void TTreeGenerator::fill_muons_variables(edm::Handle<reco::MuonCollection> MuList)
{
  imuons = 0;
  for (reco::MuonCollection::const_iterator nmuon = MuList->begin(); nmuon != MuList->end(); ++nmuon){

    if(!(nmuon->isStandAloneMuon())) continue;

    if(imuons >= STAMuSize_) break;

    const reco::TrackRef mutrackref = nmuon->outerTrack();

    STAMu_isMuGlobal.push_back(nmuon->isGlobalMuon());
    STAMu_isMuTracker.push_back(nmuon->isTrackerMuon());
    STAMu_numberOfChambers.push_back(nmuon->numberOfChambers());
    STAMu_numberOfMatches.push_back(nmuon->numberOfMatches());
    STAMu_numberOfHits.push_back(mutrackref->numberOfValidHits());

    Mu_px_mu.push_back(nmuon->px());
    Mu_py_mu.push_back(nmuon->py());
    Mu_pz_mu.push_back(nmuon->pz());
    Mu_phi_mu.push_back(nmuon->phi());
    Mu_eta_mu.push_back(nmuon->eta());

    STAMu_recHitsSize.push_back(mutrackref->recHitsSize());
    STAMu_normchi2Mu.push_back(mutrackref->chi2()/mutrackref->ndof());
    STAMu_chargeMu.push_back(mutrackref->charge());
    STAMu_dxyMu.push_back(mutrackref->dxy(beamspot.position()));
    STAMu_dzMu.push_back(mutrackref->dz(beamspot.position()));

    int segmIndex = 0;
    int segmWord = 0;

    std::vector<int> segmIndex_container;

    for (trackingRecHit_iterator recMu = mutrackref->recHitsBegin(); recMu!=mutrackref->recHitsEnd(); recMu++){
      DetId detid = (*recMu)->geographicalId(); 
      if(detid.subdetId() != MuonSubdetId::DT) continue;

      DTChamberId recChamb(detid);

      const short recWheel   = recChamb.wheel();
      const short recSector  = recChamb.sector();
      const short recStation = recChamb.station();

      //loop over the saved segments and find the position of the rechits
      //This is the quickest way to do this search: find the sector (highest number of
      //combinations), loop over the find iterator, and search for wheel and stations
      std::vector<short>::iterator sectorIt = std::find(segm4D_sector.begin(),segm4D_sector.end(),recSector);
      while(sectorIt != segm4D_sector.end()){

	segmIndex = (short) distance(segm4D_sector.begin(),sectorIt);

	if(recWheel == segm4D_wheel.at(segmIndex) && recStation == segm4D_station.at(segmIndex))
	  if(find(segmIndex_container.begin(),segmIndex_container.end(),segmIndex) == segmIndex_container.end()){
	    segmIndex_container.push_back(segmIndex);
	    segmWord |= (1 << segmIndex);
	  }
	sectorIt = std::find(sectorIt+1,segm4D_sector.end(),recSector);
      }
    }

    STAMu_segmIndex.push_back(segmWord);

    if(nmuon->isGlobalMuon()){
      const reco::TrackRef glbmutrackref = nmuon->innerTrack();
      GLBMu_normchi2Mu.push_back(glbmutrackref->chi2()/glbmutrackref->ndof());
      GLBMu_dxyMu.push_back(glbmutrackref->dxy(beamspot.position()));
      GLBMu_dzMu.push_back(glbmutrackref->dz(beamspot.position()));

      GLBMu_numberOfPixelHits.push_back(glbmutrackref->hitPattern().numberOfValidPixelHits());
      GLBMu_numberOfTrackerHits.push_back(glbmutrackref->hitPattern().numberOfValidTrackerHits());

      GLBMu_tkIsoR03.push_back(nmuon->isolationR03().sumPt);
      GLBMu_ntkIsoR03.push_back(nmuon->isolationR03().nTracks);
      GLBMu_emIsoR03.push_back(nmuon->isolationR03().emEt);
      GLBMu_hadIsoR03.push_back(nmuon->isolationR03().hadEt);
    }
    else{
      GLBMu_normchi2Mu.push_back(-999.);
      GLBMu_dxyMu.push_back(-999.);
      GLBMu_dzMu.push_back(-999.);

      GLBMu_numberOfPixelHits.push_back(-999);
      GLBMu_numberOfTrackerHits.push_back(-999);

      GLBMu_tkIsoR03.push_back(-999.);
      GLBMu_ntkIsoR03.push_back(-999.);
      GLBMu_emIsoR03.push_back(-999.);
      GLBMu_hadIsoR03.push_back(-999.);
    }

    if(nmuon->isCaloCompatibilityValid()) STAMu_caloCompatibility.push_back(nmuon->caloCompatibility());
    else STAMu_caloCompatibility.push_back(-999.);

    //extrapolate the muon to the MB2
    TrajectoryStateOnSurface tsos;
    tsos = cylExtrapTrkSam(mutrackref,500.);  // track at MB2 radius - extrapolation

    if (tsos.isValid()){
      static const float pig = acos(-1.);

      const double xx = tsos.globalPosition().x();
      const double yy = tsos.globalPosition().y();
      const double zz = tsos.globalPosition().z();

      const double rr       = sqrt(xx*xx + yy*yy);
      const double cosphi   = xx/rr;
      const double abspseta = -log(tan(atan(fabs(rr/zz))/2.));

      STAMu_z_mb2.push_back(zz);

      if (yy>=0) STAMu_phi_mb2.push_back(acos(cosphi));
      else       STAMu_phi_mb2.push_back(2*pig-acos(cosphi));
	

      if (zz>=0) STAMu_pseta_mb2.push_back(abspseta);
      else       STAMu_pseta_mb2.push_back(-abspseta);
    }
    else{
      STAMu_z_mb2.push_back(-999.);
      STAMu_phi_mb2.push_back(-999.);
      STAMu_pseta_mb2.push_back(-999.);
    }

    imuons++;
  }

  return;
}

void TTreeGenerator::fill_gmt_variables(edm::Handle<L1MuGMTReadoutCollection> gmtrc)
{
  igmtdt = 0;
  igmtcands = 0;

  std::vector<L1MuGMTReadoutRecord> gmt_records = gmtrc->getRecords();
  for(std::vector<L1MuGMTReadoutRecord>::const_iterator igmtrr=gmt_records.begin(); igmtrr!=gmt_records.end(); igmtrr++) {

    //loop over the different subdetector cands
    for(int i=0;i<4;i++){

      std::vector<L1MuRegionalCand> cands = getBXCands(&(*igmtrr),i);

      for(std::vector<L1MuRegionalCand>::const_iterator candIt = cands.begin(); candIt!=cands.end(); ++candIt){

	if(igmtdt >= gmtSize_) break;

	if(!candIt->empty()){
	  gmt_bx.push_back((*candIt).bx());
	  gmt_phi.push_back((*candIt).phiValue());
	  gmt_eta.push_back((*candIt).etaValue());
	  gmt_pt.push_back((*candIt).ptValue());
	  gmt_qual.push_back((*candIt).quality());
	  gmt_detector.push_back(i);

	  igmtdt++;
	}
      }
    }

    std::vector<L1MuGMTExtendedCand> candsOut = igmtrr->getGMTCands();
    for(std::vector<L1MuGMTExtendedCand>::const_iterator candOutIt  = candsOut.begin(); candOutIt!=candsOut.end(); ++candOutIt){

      if(igmtcands >= gmtSize_) break;

      if(!candOutIt->empty()){
	gmt_cands_fwd.push_back((*candOutIt).isFwd());
	gmt_cands_isRpc.push_back((*candOutIt).isRPC());
	gmt_cands_bx.push_back((*candOutIt).bx());
	gmt_cands_phi.push_back((*candOutIt).phiValue());
	gmt_cands_eta.push_back((*candOutIt).etaValue());
	gmt_cands_pt.push_back((*candOutIt).ptValue());
	gmt_cands_qual.push_back((*candOutIt).quality());
	gmt_cands_ismatched.push_back((*candOutIt).isMatchedCand());

	igmtcands++;
      }
    }

  }

  return;
}

void TTreeGenerator::fill_gt_variables(edm::Handle<L1GlobalTriggerReadoutRecord> gtrr, const L1GtTriggerMenu* menu) // CB FIXME speedup
{
  igtalgo = 0;
  igttt   = 0;

  const AlgorithmMap algoMap = menu->gtAlgorithmMap();
  const AlgorithmMap ttMap   = menu->gtTechnicalTriggerMap();

  for(int ibx=0; ibx<5; ibx++) {
    DecisionWord gtDecisionWord = gtrr->decisionWord(ibx-2);
    
    if (!gtDecisionWord.empty()) {

      CItAlgo algoMapIt  = algoMap.begin();
      CItAlgo algoMapEnd = algoMap.end();

      for(; algoMapIt!=algoMapEnd; ++algoMapIt) {
	if( menu->gtAlgorithmResult((*algoMapIt).first, gtDecisionWord) ) {
	  // gt_algo_bit.push_back(TString((*algoMapIt).first));
	  gt_algo_bit.push_back((algoMapIt->second).algoBitNumber());
	  gt_algo_bx.push_back(ibx-2);
	  igtalgo++;
	}
      }
    }

    TechnicalTriggerWord gtTTWord = gtrr->technicalTriggerWord(ibx-2);

    if (!gtTTWord.empty()) {
      
      CItAlgo ttMapIt  = ttMap.begin();
      CItAlgo ttMapEnd = ttMap.end();

      for(; ttMapIt!=ttMapEnd; ++ttMapIt) {

	int bitNumber = (ttMapIt->second).algoBitNumber();
	if (gtTTWord.at(bitNumber)) {
	  //	  gt_tt_bit.push_back(TString(ttMapIt->first));
	  gt_tt_bit.push_back((ttMapIt->second).algoBitNumber());
	  gt_tt_bx.push_back(ibx-2);
	  igttt++;
	}
	
      }
    }
 
  }
   
  return;
}

void TTreeGenerator::fill_hlt_variables(const edm::Event &e, edm::Handle<edm::TriggerResults> hltresults)
{
  ihlt = 0; 
  const edm::TriggerNames TrigNames_ = e.triggerNames(*hltresults);
  const int ntrigs = hltresults->size();

  for (int itr=0; itr<ntrigs; itr++){
    TString trigName=TrigNames_.triggerName(itr);
    if (hltresults->accept(itr)) {
      hlt_path.push_back(trigName);
      ihlt++;
    }
  }

  return;
}

void TTreeGenerator::fill_rpc_variables(const edm::Event &e, edm::Handle<RPCRecHitCollection> rpcrechits){
  RPCRecHitCollection::const_iterator recHit;
  irpcrechits=0;
  for(recHit = rpcrechits->begin(); recHit != rpcrechits->end(); recHit++){ 
    int cls = recHit->clusterSize();
    int firststrip = recHit->firstClusterStrip();
    int bx = recHit->BunchX();
    RPCDetId rpcId = recHit->rpcId();
    int region = rpcId.region();
    int stat = rpcId.station();
    int sect = rpcId.sector();
    int layer = rpcId.layer();
    int subsector = rpcId.subsector();
    int roll = rpcId.roll();
    int ring = rpcId.ring();
    rpc_region.push_back(region);
    rpc_clusterSize.push_back(cls);
    rpc_strip.push_back(firststrip);
    rpc_bx.push_back(bx);
    rpc_station.push_back(stat);
    rpc_sector.push_back(sect);
    rpc_layer.push_back(layer);
    rpc_subsector.push_back(subsector);
    rpc_roll.push_back(roll);
    rpc_ring.push_back(ring);
    irpcrechits++;
  }


  return;
}





std::vector<L1MuRegionalCand> TTreeGenerator::getBXCands(const L1MuGMTReadoutRecord* igmtrr, const int DetectorType) const
{
  if(DetectorType == 0) return igmtrr->getDTBXCands();
  else if(DetectorType == 1) return igmtrr->getCSCCands();
  else if(DetectorType == 2) return igmtrr->getBrlRPCCands();
  else if(DetectorType == 3) return igmtrr->getFwdRPCCands();

  return igmtrr->getDTBXCands();
}


void TTreeGenerator::beginJob()
{
  outFile = new TFile(outFile_.c_str(), "RECREATE", "");
  outFile->cd();

  tree_ = new TTree ("DTTree", "CMSSW DT tree");

  //Event info
  tree_->Branch("runnumber",&runnumber,"runnumber/I");
  tree_->Branch("lumiblock",&lumiblock,"lumiblock/I");
  tree_->Branch("eventNumber",&eventNumber,"eventNumber/I");
  tree_->Branch("timestamp",&timestamp,"timestamp/F");
  tree_->Branch("bunchXing",&bunchXing,"bunchXing/I");
  tree_->Branch("orbitNum",&orbitNum,"orbitNum/I");

  //Primary vertex
  tree_->Branch("PV_x",&PV_x,"PV_x/F");
  tree_->Branch("PV_y",&PV_y,"PV_y/F");
  tree_->Branch("PV_z",&PV_z,"PV_z/F");

  tree_->Branch("PV_xxE",&PV_xxE,"PV_xxE/F");
  tree_->Branch("PV_yyE",&PV_yyE,"PV_yyE/F");
  tree_->Branch("PV_zzE",&PV_zzE,"PV_zzE/F");
  tree_->Branch("PV_xyE",&PV_xyE,"PV_xyE/F");
  tree_->Branch("PV_xzE",&PV_xzE,"PV_xzE/F");
  tree_->Branch("PV_yzE",&PV_yzE,"PV_yzE/F");

  tree_->Branch("PV_normchi2",&PV_normchi2,"PV_normch2/F");
  tree_->Branch("PV_Nvtx",&PV_Nvtx,"PV_Nvtx/F");

  //luminosity
  tree_->Branch("lumiperblock",&lumiperblock,"lumiperblock/F");
  tree_->Branch("beam1Intensity",&beam1Intensity,"beam1Intensity/F");
  tree_->Branch("beam2Intensity",&beam2Intensity,"beam2Intensity/F");

  //HLT
  tree_->Branch("hlt_path",&hlt_path,32000,-1);

  //digi variables
  tree_->Branch("digi_wheel",&digi_wheel);
  tree_->Branch("digi_sector",&digi_sector);
  tree_->Branch("digi_station",&digi_station);
  tree_->Branch("digi_sl",&digi_sl);
  tree_->Branch("digi_layer",&digi_layer);
  tree_->Branch("digi_wire",&digi_wire);
  tree_->Branch("digi_time",&digi_time);

  //DT segment variables
  tree_->Branch("dtsegm4D_wheel",&segm4D_wheel);
  tree_->Branch("dtsegm4D_sector",&segm4D_sector);
  tree_->Branch("dtsegm4D_station",&segm4D_station);

  tree_->Branch("dtsegm4D_hasPhi",&segm4D_hasPhi);
  tree_->Branch("dtsegm4D_hasZed",&segm4D_hasZed);
  tree_->Branch("dtsegm4D_x_pos_loc",&segm4D_x_pos_loc);
  tree_->Branch("dtsegm4D_y_pos_loc",&segm4D_y_pos_loc);
  tree_->Branch("dtsegm4D_z_pos_loc",&segm4D_z_pos_loc);
  tree_->Branch("dtsegm4D_x_dir_loc",&segm4D_x_dir_loc);
  tree_->Branch("dtsegm4D_y_dir_loc",&segm4D_y_dir_loc);
  tree_->Branch("dtsegm4D_z_dir_loc",&segm4D_z_dir_loc);
  tree_->Branch("dtsegm4D_cosx",&segm4D_cosx);
  tree_->Branch("dtsegm4D_cosy",&segm4D_cosy);
  tree_->Branch("dtsegm4D_cosz",&segm4D_cosz);
  tree_->Branch("dtsegm4D_phi",&segm4D_phi);
  tree_->Branch("dtsegm4D_theta",&segm4D_theta);
  tree_->Branch("dtsegm4D_eta",&segm4D_eta);
  tree_->Branch("dtsegm4D_t0",&segm4D_t0);
  tree_->Branch("dtsegm4D_vdrift",&segm4D_vdrift);
  tree_->Branch("dtsegm4D_phinormchisq",&segm4D_phinormchi2);
  tree_->Branch("dtsegm4D_phinhits",&segm4D_phinhits);
  tree_->Branch("dtsegm4D_znormchisq",&segm4D_znormchi2);
  tree_->Branch("dtsegm4D_znhits",&segm4D_znhits);

  //rechits info
  tree_->Branch("dtsegm4D_phi_hitsPos",&segm4D_phiHits_Pos,2048000,0);
  tree_->Branch("dtsegm4D_phi_hitsPosCh",&segm4D_phiHits_PosCh,2048000,0);
  tree_->Branch("dtsegm4D_phi_hitsPosErr",&segm4D_phiHits_PosErr,2048000,0);
  tree_->Branch("dtsegm4D_phi_hitsSide",&segm4D_phiHits_Side,2048000,0);
  tree_->Branch("dtsegm4D_phi_hitsWire",&segm4D_phiHits_Wire,2048000,0);
  tree_->Branch("dtsegm4D_phi_hitsLayer",&segm4D_phiHits_Layer,2048000,0);

  tree_->Branch("dtsegm4D_z_hitsPos",&segm4D_zHits_Pos,2048000,0);
  tree_->Branch("dtsegm4D_z_hitsPosCh",&segm4D_zHits_PosCh,2048000,0);
  tree_->Branch("dtsegm4D_z_hitsPosErr",&segm4D_zHits_PosErr,2048000,0);
  tree_->Branch("dtsegm4D_z_hitsSide",&segm4D_zHits_Side,2048000,0);
  tree_->Branch("dtsegm4D_z_hitsWire",&segm4D_zHits_Wire,2048000,0);
  tree_->Branch("dtsegm4D_z_hitsLayer",&segm4D_zHits_Layer,2048000,0);

  //CSC segment variables
  tree_->Branch("cscsegm_ring",&cscsegm_ring);
  tree_->Branch("cscsegm_chamber",&cscsegm_chamber);
  tree_->Branch("cscsegm_station",&cscsegm_station);
  tree_->Branch("cscsegm_cosx",&cscsegm_cosx);
  tree_->Branch("cscsegm_cosy",&cscsegm_cosy);
  tree_->Branch("cscsegm_cosz",&cscsegm_cosz);
  tree_->Branch("cscsegm_phi",&cscsegm_phi);
  tree_->Branch("cscsegm_eta",&cscsegm_eta);
  tree_->Branch("cscsegm_normchisq",&cscsegm_normchi2);
  tree_->Branch("cscsegm_nRecHits",&cscsegm_nRecHits);

  //DCC variables
  tree_->Branch("ltDCC_wheel",&ltDCC_wheel);
  tree_->Branch("ltDCC_sector",&ltDCC_sector);
  tree_->Branch("ltDCC_station",&ltDCC_station);
  tree_->Branch("ltDCC_quality",&ltDCC_quality);
  tree_->Branch("ltDCC_bx",&ltDCC_bx);
  tree_->Branch("ltDCC_phi",&ltDCC_phi);
  tree_->Branch("ltDCC_phiB",&ltDCC_phiB);
  tree_->Branch("ltDCC_is2nd",&ltDCC_is2nd);

  tree_->Branch("ltDCC_thWheel",&ltDCC_thWheel);
  tree_->Branch("ltDCC_thSector",&ltDCC_thSector);
  tree_->Branch("ltDCC_thStation",&ltDCC_thStation);
  tree_->Branch("ltDCC_thBx",&ltDCC_thBx);
  tree_->Branch("ltDCC_thHits",&ltDCC_thHits);

  tree_->Branch("ltDCCemu_wheel",&ltDCCemu_wheel);
  tree_->Branch("ltDCCemu_sector",&ltDCCemu_sector);
  tree_->Branch("ltDCCemu_station",&ltDCCemu_station);
  tree_->Branch("ltDCCemu_quality",&ltDCCemu_quality);
  tree_->Branch("ltDCCemu_bx",&ltDCCemu_bx);
  tree_->Branch("ltDCCemu_phi",&ltDCCemu_phi);
  tree_->Branch("ltDCCemu_phiB",&ltDCCemu_phiB);
  tree_->Branch("ltDCCemu_is2nd",&ltDCCemu_is2nd);

  tree_->Branch("ltDCCemu_thWheel",&ltDCCemu_thWheel);
  tree_->Branch("ltDCCemu_thSector",&ltDCCemu_thSector);
  tree_->Branch("ltDCCemu_thStation",&ltDCCemu_thStation);
  tree_->Branch("ltDCCemu_thBx",&ltDCCemu_thBx);
  tree_->Branch("ltDCCemu_thHits",&ltDCCemu_thHits);

  //DDU variables
  tree_->Branch("ltDDU_wheel",&ltDDU_wheel);
  tree_->Branch("ltDDU_sector",&ltDDU_sector);
  tree_->Branch("ltDDU_station",&ltDDU_station);
  tree_->Branch("ltDDU_bx",&ltDDU_bx);
  tree_->Branch("ltDDU_phiQual",&ltDDU_phiQual);
  tree_->Branch("ltDDU_thQual",&ltDDU_thQual);
  tree_->Branch("ltDDU_is2nd",&ltDDU_is2nd);

  //muon variables
  tree_->Branch("Mu_isMuGlobal",&STAMu_isMuGlobal);
  tree_->Branch("Mu_isMuTracker",&STAMu_isMuTracker);
  tree_->Branch("Mu_numberOfChambers_sta",&STAMu_numberOfChambers);
  tree_->Branch("Mu_numberOfMatches_sta",&STAMu_numberOfMatches);
  tree_->Branch("Mu_numberOfHits_sta",&STAMu_numberOfHits);
  tree_->Branch("Mu_segmentIndex_sta",&STAMu_segmIndex);

  tree_->Branch("Mu_px",&Mu_px_mu);
  tree_->Branch("Mu_py",&Mu_py_mu);
  tree_->Branch("Mu_pz",&Mu_pz_mu);
  tree_->Branch("Mu_phi",&Mu_phi_mu);
  tree_->Branch("Mu_eta",&Mu_eta_mu);
  tree_->Branch("Mu_recHitsSize",&STAMu_recHitsSize);
  tree_->Branch("Mu_normchi2_sta",&STAMu_normchi2Mu);
  tree_->Branch("Mu_charge",&STAMu_chargeMu);
  tree_->Branch("Mu_dxy_sta",&STAMu_dxyMu);
  tree_->Branch("Mu_dz_sta",&STAMu_dzMu);

  tree_->Branch("Mu_normchi2_glb",&GLBMu_normchi2Mu);
  tree_->Branch("Mu_dxy_glb",&GLBMu_dxyMu);
  tree_->Branch("Mu_dz_glb",&GLBMu_dzMu);

  tree_->Branch("Mu_numberOfPixelHits_glb",&GLBMu_numberOfPixelHits);
  tree_->Branch("Mu_numberOfTrackerHits_glb",&GLBMu_numberOfTrackerHits);

  tree_->Branch("Mu_tkIsoR03_glb",&GLBMu_tkIsoR03);
  tree_->Branch("Mu_ntkIsoR03_glb",&GLBMu_ntkIsoR03);
  tree_->Branch("Mu_emIsoR03_glb",&GLBMu_emIsoR03);
  tree_->Branch("Mu_hadIsoR03_glb",&GLBMu_hadIsoR03);

  tree_->Branch("STAMu_caloCompatibility",&STAMu_caloCompatibility);

  tree_->Branch("Mu_z_mb2_mu",&STAMu_z_mb2);
  tree_->Branch("Mu_phi_mb2_mu",&STAMu_phi_mb2);
  tree_->Branch("Mu_pseta_mb2_mu",&STAMu_pseta_mb2);

  //GMT
  tree_->Branch("gmt_bx",&gmt_bx);
  tree_->Branch("gmt_phi",&gmt_phi);
  tree_->Branch("gmt_eta",&gmt_eta);
  tree_->Branch("gmt_pt",&gmt_pt);
  tree_->Branch("gmt_qual",&gmt_qual);
  tree_->Branch("gmt_detector",&gmt_detector);

  tree_->Branch("gmt_cands_fwd",&gmt_cands_fwd);
  tree_->Branch("gmt_cands_isRpc",&gmt_cands_isRpc);
  tree_->Branch("gmt_cands_bx",&gmt_cands_bx);
  tree_->Branch("gmt_cands_phi",&gmt_cands_phi);
  tree_->Branch("gmt_cands_eta",&gmt_cands_eta);
  tree_->Branch("gmt_cands_pt",&gmt_cands_pt);
  tree_->Branch("gmt_cands_qual",&gmt_cands_qual);
  tree_->Branch("gmt_cands_ismatched",&gmt_cands_ismatched);

  //GT
  tree_->Branch("gt_algo_bit",&gt_algo_bit);
  tree_->Branch("gt_algo_bx",&gt_algo_bx);
  tree_->Branch("gt_tt_bit",&gt_tt_bit);
  tree_->Branch("gt_tt_bx",&gt_tt_bx);

  //RPC









     
  tree_->Branch(  "rpc_region",&rpc_region);			   
  tree_->Branch(  "rpc_clusterSize",&rpc_clusterSize);		   
  tree_->Branch(  "rpc_strip",&rpc_strip);			   
  tree_->Branch(  "rpc_bx",&rpc_bx);			   
  tree_->Branch(  "rpc_station",&rpc_station);		   
  tree_->Branch(  "rpc_sector",&rpc_sector);		   
  tree_->Branch(  "rpc_layer",&rpc_layer);			   
  tree_->Branch(  "rpc_subsector",&rpc_subsector);		   
  tree_->Branch(  "rpc_roll",&rpc_roll);			   
  tree_->Branch(  "rpc_ring",&rpc_ring);                     
  //counters
  tree_->Branch("Ndigis",&idigis,"Ndigis/S");
  tree_->Branch("Ndtsegments",&idtsegments,"Ndtsegments/S");
  tree_->Branch("Ncscsegments",&icscsegments,"Ncscsegments/S");
  tree_->Branch("NdtltDCC_th",&idtltDCC_th,"NdtltDCC_th/S");
  tree_->Branch("NdtltDCC",&idtltDCC,"NdtltDCC/S");
  tree_->Branch("NdtltSimDCC_th",&idtltSimDCC_th,"NdtltSimDCC_th/S");
  tree_->Branch("NdtltSimDCC",&idtltSimDCC,"NdtltSimDCC/S");
  tree_->Branch("NdtltDDU",&idtltDDU,"NdtltDDU/S");
  tree_->Branch("Nmuons",&imuons,"Nmuons/S");
  tree_->Branch("Ngmt",&igmtdt,"Ngmt/S");
  tree_->Branch("Ngmtcands",&igmtcands,"Ngmtcands/S");
  tree_->Branch("Ngtalgo",&igtalgo,"Ngtalgo/S");
  tree_->Branch("Ngttechtrig",&igttt,"Ngttt/S");
  tree_->Branch("Nhlt",&ihlt,"Nhlt/S");
  tree_->Branch("NrpcRecHits",&irpcrechits,"NrpcRecHits/S");

  return;
}

void TTreeGenerator::endJob()
{
  outFile->cd();
  tree_->Write();
  outFile->Close();

  return;
}

inline void TTreeGenerator::clear_Arrays()
{
  //digi variables
  digi_wheel.clear();
  digi_sector.clear();
  digi_station.clear();
  digi_sl.clear();
  digi_layer.clear();
  digi_wire.clear();
  digi_time.clear();

  //DT segment variables 
  segm4D_wheel.clear();
  segm4D_sector.clear();
  segm4D_station.clear();
  segm4D_hasPhi.clear();
  segm4D_hasZed.clear();
  segm4D_x_pos_loc.clear();
  segm4D_y_pos_loc.clear();
  segm4D_z_pos_loc.clear();
  segm4D_x_dir_loc.clear();
  segm4D_y_dir_loc.clear();
  segm4D_z_dir_loc.clear();
  segm4D_cosx.clear();
  segm4D_cosy.clear();
  segm4D_cosz.clear();
  segm4D_phi.clear();
  segm4D_theta.clear();
  segm4D_eta.clear();
  segm4D_t0.clear();
  segm4D_vdrift.clear();
  segm4D_phinormchi2.clear();
  segm4D_phinhits.clear();
  segm4D_znormchi2.clear();
  segm4D_znhits.clear();

  segm4D_phiHits_Pos->Clear();
  segm4D_phiHits_PosCh->Clear();
  segm4D_phiHits_PosErr->Clear();
  segm4D_phiHits_Side->Clear();
  segm4D_phiHits_Wire->Clear();
  segm4D_phiHits_Layer->Clear();

  segm4D_zHits_Pos->Clear();
  segm4D_zHits_PosCh->Clear();
  segm4D_zHits_PosErr->Clear();
  segm4D_zHits_Side->Clear();
  segm4D_zHits_Wire->Clear();
  segm4D_zHits_Layer->Clear();

  //CSC segment variables 
  cscsegm_ring.clear();
  cscsegm_chamber.clear();
  cscsegm_station.clear();
  cscsegm_cosx.clear();
  cscsegm_cosy.clear();
  cscsegm_cosz.clear();
  cscsegm_phi.clear();
  cscsegm_eta.clear();
  cscsegm_normchi2.clear();
  cscsegm_nRecHits.clear();

  //DCC variables
  ltDCC_wheel.clear();
  ltDCC_sector.clear();
  ltDCC_station.clear();
  ltDCC_quality.clear();
  ltDCC_bx.clear();
  ltDCC_phi.clear();
  ltDCC_phiB.clear();
  ltDCC_is2nd.clear();

  ltDCC_thWheel.clear();
  ltDCC_thSector.clear();
  ltDCC_thStation.clear();
  ltDCC_thBx.clear();
  ltDCC_thHits.clear();

  ltDCCemu_wheel.clear();
  ltDCCemu_sector.clear();
  ltDCCemu_station.clear();
  ltDCCemu_quality.clear();
  ltDCCemu_bx.clear();
  ltDCCemu_phi.clear();
  ltDCCemu_phiB.clear();
  ltDCCemu_is2nd.clear();

  ltDCCemu_thWheel.clear();
  ltDCCemu_thSector.clear();
  ltDCCemu_thStation.clear();
  ltDCCemu_thBx.clear();
  ltDCCemu_thHits.clear();


  //DDU variables
  ltDDU_wheel.clear();
  ltDDU_sector.clear();
  ltDDU_station.clear();
  ltDDU_bx.clear();
  ltDDU_phiQual.clear();
  ltDDU_thQual.clear();
  ltDDU_is2nd.clear();

  //muon variables
  STAMu_isMuGlobal.clear();
  STAMu_isMuTracker.clear();
  STAMu_numberOfChambers.clear();
  STAMu_numberOfMatches.clear();
  STAMu_numberOfHits.clear();
  STAMu_segmIndex.clear();

  Mu_px_mu.clear();
  Mu_py_mu.clear();
  Mu_pz_mu.clear();
  Mu_phi_mu.clear();
  Mu_eta_mu.clear();
  STAMu_recHitsSize.clear();
  STAMu_normchi2Mu.clear();
  STAMu_chargeMu.clear();
  STAMu_dxyMu.clear();
  STAMu_dzMu.clear();

  GLBMu_normchi2Mu.clear();
  GLBMu_dxyMu.clear();
  GLBMu_dzMu.clear();

  GLBMu_numberOfPixelHits.clear();
  GLBMu_numberOfTrackerHits.clear();

  GLBMu_tkIsoR03.clear();
  GLBMu_ntkIsoR03.clear();
  GLBMu_emIsoR03.clear();
  GLBMu_hadIsoR03.clear();

  STAMu_caloCompatibility.clear();

  STAMu_z_mb2.clear();
  STAMu_phi_mb2.clear();
  STAMu_pseta_mb2.clear();

  //GMT
  gmt_bx.clear();
  gmt_phi.clear();
  gmt_eta.clear();
  gmt_pt.clear();
  gmt_qual.clear();
  gmt_detector.clear();

  gmt_cands_fwd.clear();
  gmt_cands_isRpc.clear();
  gmt_cands_bx.clear();
  gmt_cands_phi.clear();
  gmt_cands_eta.clear();
  gmt_cands_pt.clear();
  gmt_cands_qual.clear();
  gmt_cands_ismatched.clear();

  //GT
  gt_algo_bit.clear();
  gt_algo_bx.clear();
  gt_tt_bit.clear();
  gt_tt_bx.clear();

  //HLT
  hlt_path.clear();

  // RPC rec hits
  rpc_region.clear();
  rpc_clusterSize.clear();
  rpc_strip.clear();
  rpc_bx.clear();
  rpc_station.clear();
  rpc_sector.clear();
  rpc_layer.clear();
  rpc_subsector.clear();
  rpc_roll.clear();
  rpc_ring.clear();
  
  return;
}

void TTreeGenerator::initialize_Tree_variables()
{
  //Event variables
  runnumber   = 0;
  lumiblock   = 0;
  eventNumber = 0;
  timestamp   = 0.;
  bunchXing   = 0;
  orbitNum    = 0;

  PV_x = 0.;
  PV_y = 0.;
  PV_z = 0.;
  PV_xxE = 0.;
  PV_yyE = 0.;
  PV_zzE = 0.;
  PV_xyE = 0.;
  PV_xzE = 0.;
  PV_yzE = 0.;
  PV_normchi2 = 0.;
  PV_Nvtx = 0.;

  lumiperblock = 0.;
  beam1Intensity = 0.;
  beam2Intensity = 0.;

  segm4D_phiHits_Pos    = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_phiHits_PosCh  = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_phiHits_PosErr = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_phiHits_Side   = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_phiHits_Wire   = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_phiHits_Layer  = new TClonesArray("TVectorF",dtsegmentsSize_);

  segm4D_zHits_Pos    = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_zHits_PosCh  = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_zHits_PosErr = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_zHits_Side   = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_zHits_Wire   = new TClonesArray("TVectorF",dtsegmentsSize_);
  segm4D_zHits_Layer  = new TClonesArray("TVectorF",dtsegmentsSize_);

  return;
}

TrajectoryStateOnSurface TTreeGenerator::cylExtrapTrkSam(reco::TrackRef track, const float rho) const
{
  Cylinder::PositionType pos(0.,0.,0.);
  Cylinder::RotationType rot;
  Cylinder::CylinderPointer myCylinder = Cylinder::build(pos, rot, rho);

  FreeTrajectoryState recoStart = freeTrajStateMuon(track);
  TrajectoryStateOnSurface recoProp;
  recoProp = propagatorAlong->propagate(recoStart, *myCylinder);
  if (!recoProp.isValid()) {
    recoProp = propagatorOpposite->propagate(recoStart, *myCylinder);
  }
  return recoProp;
}

FreeTrajectoryState TTreeGenerator::freeTrajStateMuon(const reco::TrackRef track) const
{
  const GlobalPoint  innerPoint(track->innerPosition().x(),track->innerPosition().y(),track->innerPosition().z());
  const GlobalVector innerVec  (track->innerMomentum().x(),track->innerMomentum().y(),track->innerMomentum().z());  
  
  FreeTrajectoryState recoStart(innerPoint, innerVec, track->charge(), &*theBField);
  
  return recoStart;
}


//define this as a plug-in
DEFINE_FWK_MODULE(TTreeGenerator);
 
