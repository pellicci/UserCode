/******* \class DTEffOfflineAnalyzer *******
 *
 * Description:
 *  
 *  detailed description
 *
 * \author : Stefano Lacaprara - INFN LNL <stefano.lacaprara@pd.infn.it>
 * $date   : 20/11/2006 16:50:57 CET $
 *
 * Modification:
 *     Mary-Cruz Fouz 
 *     March 2008: Histo Modifications To allow run over the root files
 *     Carlo Battilana
 *     October 2008: switched to DQMStore  
 *
 ************************************************************************/

/* This Class Header */
#include "UserCode/DTDPGAnalysis/src/DTEffOfflineAnalyzer.h"

/* Collaborating Class Header */
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

using namespace edm;

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

#include "DataFormats/LTCDigi/interface/LTCDigi.h"

#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"
#include "DataFormats/DTRecHit/interface/DTRangeMapAccessor.h"

#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"

/* C++ Headers */
#include <iostream>
#include <cmath>
using namespace std;

/* ====================================================================== */

/* Constructor */ 
DTEffOfflineAnalyzer::DTEffOfflineAnalyzer(const ParameterSet& pset) {

  // Get the debug parameter for verbose output
  debug = pset.getUntrackedParameter<bool>("debug");
  theRootFileName = pset.getUntrackedParameter<string>("rootFileName");

  // the name of the digis collection
  theDTLocalTriggerLabel = pset.getParameter<string>("DTLocalTriggerLabel");

  // the name of the 1D rec hits collection
  theRecHits1DLabel = pset.getParameter<string>("recHits1DLabel");

  // the name of the 2D rec hits collection
  theRecHits2DLabel = pset.getParameter<string>("recHits2DLabel");

  // the name of the 4D rec hits collection
  theRecHits4DLabel = pset.getParameter<string>("recHits4DLabel");

  // if MC
  mc = pset.getParameter<bool>("isMC");

  theMinHitsSegment = static_cast<unsigned int>(pset.getParameter<int>("minHitsSegment"));
  theMinChi2NormSegment = pset.getParameter<double>("minChi2NormSegment");
  theMinCloseDist = pset.getParameter<double>("minCloseDist");

  // trigger selection
  LCT_RPC = pset.getParameter<bool>("LCT_RPC");
  LCT_DT = pset.getParameter<bool>("LCT_DT");
  LCT_CSC = pset.getParameter<bool>("LCT_CSC");

  init=false;
}

void DTEffOfflineAnalyzer::beginJob(const EventSetup& eventSetup) {
  if(debug) cout << "beginOfJob" << endl;
  // Get the DT Geometry
  eventSetup.get<MuonGeometryRecord>().get(dtGeom);

  // Create the root file
  // theFile = new TFile(theRootFileName.c_str(), "RECREATE");

  theDQMStore = edm::Service<DQMStore>().operator->();

  // trigger Histos
  createTH1F("hTrigBits","All trigger bits","", 10,0.,10.);

  for (int w=-2; w<=2; ++w) {
    stringstream nameWheel;
    nameWheel << "_Wh"<< w ;
    for (int sec=1; sec<=14; ++sec) { // section 1 to 14
      stringstream nameSector;
      nameSector << nameWheel.str() << "_Sec" << sec;
      for (int st=1; st<=4; ++st) { // station 1 to 4

          stringstream nameChamber;
          nameChamber << nameSector.str() << "_St" << st;

          createTH1F("hDistSegFromExtrap",
                     "Distance segments from extrap position ",nameChamber.str(), 200,0.,200.);
          createTH1F("hNaiveEffSeg","Naive eff ",nameChamber.str(), 10,0.,10.);
          createTH2F("hEffSegVsPosDen", "Eff vs local position (all) ", nameChamber.str(),
                     25,-250.,250., 25,-250.,250.);
          createTH2F("hEffGoodSegVsPosDen", "Eff vs local position (good) ", nameChamber.str(),
                     25,-250.,250., 25,-250.,250.);
          createTH2F("hEffSegVsPosNum", "Eff vs local position ", nameChamber.str(),
                     25,-250.,250., 25,-250.,250.);
          createTH2F("hEffGoodSegVsPosNum", "Eff vs local position (good segs) ", nameChamber.str(),
                     25,-250.,250., 25,-250.,250.);
          createTH2F("hEffGoodCloseSegVsPosNum",
                     "Eff vs local position (good aand close segs) ", nameChamber.str(),
                     25,-250.,250., 25,-250.,250.);
      }
    }
  }
}

/* Destructor */ 
DTEffOfflineAnalyzer::~DTEffOfflineAnalyzer() {
  theDQMStore->rmdir("DT/DTEffOfflineAnalyzer");
}

/* Operations */ 
void DTEffOfflineAnalyzer::analyze(const Event & event,
                            const EventSetup& eventSetup) {
  if (debug) cout << endl<<"--- [DTEffOfflineAnalyzer] Event analysed #Run: " <<
    event.id().run() << " #Event: " << event.id().event() << endl;

  float nrun=event.id().run();
  if(!init)
  {
     createTH1F("RunNumbers","RunNumbers","",23,nrun-11.5,nrun+11.5);
     init=true;
  }
  histo("RunNumbers")->Fill(nrun);

  
  // Trigger analysis
  if (debug) cout << "Is MC " << mc << endl;

  if (!mc) {
    Handle<LTCDigiCollection> ltcdigis;
    //event.getByType(ltcdigis); // Doesn't work after 62X
    event.getByLabel("none",ltcdigis);

    for (std::vector<LTCDigi>::const_iterator ltc= ltcdigis->begin(); ltc!=
         ltcdigis->end(); ++ltc) {
      for (int i = 0; i < 6; i++) 
        if ((*ltc).HasTriggered(i)) {
          LCT.set(i);
          histo("hTrigBits")->Fill(i);
        }
    }
  } else {
    for (int i = 0; i < 6; i++) 
      LCT.set(i);
  }

  if (selectEvent()) {
    effSegments(event, eventSetup);
  }
}

bool DTEffOfflineAnalyzer::selectEvent() const {
  bool trigger=false;
  if (LCT_DT) trigger = trigger || getLCT(DT);
  if (LCT_RPC) trigger = trigger || (getLCT(RPC_W1) || getLCT(RPC_W2));
  if (LCT_CSC) trigger = trigger || getLCT(CSC);
  if (debug) cout << "LCT " << trigger << endl;
  return trigger;
}

void DTEffOfflineAnalyzer::effSegments(const Event & event,
                                const EventSetup& eventSetup){

  event.getByLabel(theRecHits4DLabel, segs);
  if (debug) {
    cout << "4d " << segs->size() << endl;
    for (DTRecSegment4DCollection::const_iterator seg=segs->begin() ;
         seg!=segs->end() ; ++seg ) 
      cout << *seg << endl;
  }



  // Get events with 3 segments in different station and look what happen on
  // the other station. Note, must take into account geometrical acceptance

  // trivial pattern recognition: get 3 segments in 3 different station of a
  // given wheel, sector

  for (int wheel = -2; wheel <=2; ++wheel) {
    for (int sector = 1; sector <=12; ++sector) {
      evaluateEff(DTChamberId(wheel, 1, sector),2,3 ); // get efficiency for MB1 using MB2 and MB3
      evaluateEff(DTChamberId(wheel, 2, sector),1,3 ); // get efficiency for MB2 using MB1 and MB3
      evaluateEff(DTChamberId(wheel, 3, sector),2,4 ); // get efficiency for MB3 using MB2 and MB4
      evaluateEff(DTChamberId(wheel, 4, sector),2,3 ); // get efficiency for MB4 using MB2 and MB3

    }
  }
}

void DTEffOfflineAnalyzer::evaluateEff(const DTChamberId& MidId, int bottom, int top) const {
  if (debug) cout << "evaluateEff " << MidId << " bott/top " << bottom << "/"<< top << endl;
  // Select events with (good) segments in Bot and Top
  DTChamberId BotId(MidId.wheel(), bottom, MidId.sector());
  DTChamberId TopId(MidId.wheel(), top, MidId.sector());

  // Get segments in the bottom chambers (if any)
  DTRecSegment4DCollection::range segsBot= segs->get(BotId);
  int nSegsBot=segsBot.second-segsBot.first;
  // check if any segments is there
  if (nSegsBot==0) return;

  // Get segments in the top chambers (if any)
  DTRecSegment4DCollection::range segsTop= segs->get(TopId);
  int nSegsTop=segsTop.second-segsTop.first;

  // something more sophisticate check quality of segments
  const DTRecSegment4D& bestBotSeg= getBestSegment(segsBot);
  //cout << "BestBotSeg " << bestBotSeg << endl;

  DTRecSegment4D* pBestTopSeg=0;
  if (nSegsTop>0) pBestTopSeg=
    const_cast<DTRecSegment4D*>(&getBestSegment(segsTop));
  //if top chamber is MB4 sector 10, consider also sector 14
  if (TopId.station()==4 && TopId.sector()==10) {
    DTChamberId TopId14(MidId.wheel(), top, 14);
    DTRecSegment4DCollection::range segsTop14= segs->get(TopId14);
    int nSegsTop14=segsTop14.second-segsTop14.first;
    nSegsTop+=nSegsTop;
    if (nSegsTop14) {
      DTRecSegment4D* pBestTopSeg14=
        const_cast<DTRecSegment4D*>(&getBestSegment(segsTop14));

      // get best between sector 10 and 14
      pBestTopSeg =
        const_cast<DTRecSegment4D*>(getBestSegment(pBestTopSeg, pBestTopSeg14));
    }
  }
  if (!pBestTopSeg) return;
  const DTRecSegment4D& bestTopSeg= *pBestTopSeg;

  DTRecSegment4DCollection::range segsMid= segs->get(MidId);
  int nSegsMid=segsMid.second-segsMid.first;

  // very trivial efficiency, just count segments
  histo(hName("hNaiveEffSeg",MidId))->Fill(0);
  if (nSegsMid>0) histo(hName("hNaiveEffSeg",MidId))->Fill(1);

  // get position at Mid by interpolating the position (not direction) of best
  // segment in Bot and Top to Mid surface
  LocalPoint posAtMid = interpolate(bestBotSeg, bestTopSeg, MidId);

  // is best segment good enough?
  if (isGoodSegment(bestBotSeg) && isGoodSegment(bestTopSeg)) {
    histo2d(hName("hEffSegVsPosDen",MidId))->Fill(posAtMid.x(),posAtMid.y());
    //check if interpolation fall inside middle chamber
    if ((dtGeom->chamber(MidId))->surface().bounds().inside(posAtMid)) {

      histo2d(hName("hEffGoodSegVsPosDen",MidId))->Fill(posAtMid.x(),posAtMid.y());

      if (nSegsMid>0) {
        histo(hName("hNaiveEffSeg",MidId))->Fill(2);
        histo2d(hName("hEffSegVsPosNum",MidId))->Fill(posAtMid.x(),posAtMid.y());
        const DTRecSegment4D& bestMidSeg= getBestSegment(segsMid);
        // check if middle segments is good enough
        if (isGoodSegment(bestMidSeg)) {
          histo2d(hName("hEffGoodSegVsPosNum",MidId))->Fill(posAtMid.x(),posAtMid.y());
          LocalPoint midSegPos=bestMidSeg.localPosition();
          // check if middle segments is also close enough
          double dist;
          if (bestMidSeg.hasPhi()) { 
            if (bestTopSeg.hasZed() && bestBotSeg.hasZed() && bestMidSeg.hasZed()) { 
              dist = (midSegPos-posAtMid).mag();
            } else {
              dist = fabs((midSegPos-posAtMid).x());
            }
          } else {
            dist = fabs((midSegPos-posAtMid).y());
          }
          if (dist < theMinCloseDist ) {
            histo2d(hName("hEffGoodCloseSegVsPosNum",MidId))->Fill(posAtMid.x(),posAtMid.y());
          }
          histo(hName("hDistSegFromExtrap",MidId))->Fill(dist);
        }

      }
    }
  }
  // else cout << "Outside " << endl;
}

// as usual max number of hits and min chi2
const DTRecSegment4D& DTEffOfflineAnalyzer::getBestSegment(const DTRecSegment4DCollection::range& segs) const{
  DTRecSegment4DCollection::const_iterator bestIter;
  unsigned int nHitBest=0;
  double chi2Best=99999.;
  for (DTRecSegment4DCollection::const_iterator seg=segs.first ;
       seg!=segs.second ; ++seg ) {
    unsigned int nHits= ((*seg).hasPhi() ? (*seg).phiSegment()->recHits().size() : 0 ) ;
    nHits+= ((*seg).hasZed() ?  (*seg).zSegment()->recHits().size() : 0 );

    if (nHits==nHitBest) {
      if ((*seg).chi2()/(*seg).degreesOfFreedom() < chi2Best ) {
        chi2Best=(*seg).chi2()/(*seg).degreesOfFreedom();
        bestIter = seg;
      }
    }
    else if (nHits>nHitBest) {
      nHitBest=nHits;
      bestIter = seg;
    }
  }
  return *bestIter;
}

const DTRecSegment4D* DTEffOfflineAnalyzer::getBestSegment(const DTRecSegment4D* s1,
                                                    const DTRecSegment4D* s2) const{

  if (!s1) return s2;
  if (!s2) return s1;
  unsigned int nHits1= (s1->hasPhi() ? s1->phiSegment()->recHits().size() : 0 ) ;
  nHits1+= (s1->hasZed() ?  s1->zSegment()->recHits().size() : 0 );

  unsigned int nHits2= (s2->hasPhi() ? s2->phiSegment()->recHits().size() : 0 ) ;
  nHits2+= (s2->hasZed() ?  s2->zSegment()->recHits().size() : 0 );

  if (nHits1==nHits2) {
    if (s1->chi2()/s1->degreesOfFreedom() < s2->chi2()/s2->degreesOfFreedom() ) 
      return s1;
    else
      return s2;
  }
  else if (nHits1>nHits2) return s1;
  return s2;
}

bool DTEffOfflineAnalyzer::isGoodSegment(const DTRecSegment4D& seg) const {
  if (seg.chamberId().station()!=4 && !seg.hasZed()) return false;
  unsigned int nHits= (seg.hasPhi() ? seg.phiSegment()->recHits().size() : 0 ) ;
  nHits+= (seg.hasZed() ?  seg.zSegment()->recHits().size() : 0 );
  return ( nHits >= theMinHitsSegment &&
    seg.chi2()/seg.degreesOfFreedom() < theMinChi2NormSegment );
}

LocalPoint DTEffOfflineAnalyzer::interpolate(const DTRecSegment4D& seg1,
                                      const DTRecSegment4D& seg3,
                                      const DTChamberId& id2) const {
  // Get GlobalPoition of Seg in MB1
  GlobalPoint
    gpos1=(dtGeom->chamber(seg1.chamberId()))->toGlobal(seg1.localPosition());

  // Get GlobalPoition of Seg in MB3
  GlobalPoint
    gpos3=(dtGeom->chamber(seg3.chamberId()))->toGlobal(seg3.localPosition());

  // interpolate
  // get all in MB2 frame
  LocalPoint pos1=(dtGeom->chamber(id2))->toLocal(gpos1);
  LocalPoint pos3=(dtGeom->chamber(id2))->toLocal(gpos3);

  // case 1: 1 and 3 has both projection. No problem

  // case 2: one projection is missing for one of the segments. Keep the other's
  // segment position
  if (!seg1.hasZed()) pos1=LocalPoint(pos1.x(),pos3.y(),pos1.z());
  if (!seg3.hasZed()) pos3=LocalPoint(pos3.x(),pos1.y(),pos3.z());

  if (!seg1.hasPhi()) pos1=LocalPoint(pos3.x(),pos1.y(),pos1.z());
  if (!seg3.hasPhi()) pos3=LocalPoint(pos1.x(),pos3.y(),pos3.z());

  // direction
  LocalVector dir = (pos3-pos1).unit(); // z points inward!
  LocalPoint pos2 = pos1+dir*pos1.z()/(-dir.z());


  return pos2;
}

TH1F* DTEffOfflineAnalyzer::histo(const string& name) const{
  MonitorElement* me = theDQMStore->get(("DT/DTEffOfflineAnalyzer/"+name).c_str());
  if (!me) throw cms::Exception("DTEffOfflineAnalyzer") << " ME not existing " << name;
  TH1F* histo = me->getTH1F();
  if (!histo)cms::Exception("DTEffOfflineAnalyzer") << " Not a TH1F " << name;
  return histo;
}

TH2F* DTEffOfflineAnalyzer::histo2d(const string& name) const{
  MonitorElement* me = theDQMStore->get(("DT/DTEffOfflineAnalyzer/"+name).c_str());
  if (!me) throw cms::Exception("DTEffOfflineAnalyzer") << " ME not existing " << name;
  TH2F* histo = me->getTH2F();
  if (!histo)cms::Exception("DTEffOfflineAnalyzer") << " Not a TH2F " << name;
  return histo;
}

string DTEffOfflineAnalyzer::toString(const DTChamberId& id) const {
  stringstream result;
  result << "_Wh" << id.wheel() 
    << "_Sec" << id.sector() 
    << "_St" << id.station();
  return result.str();
}

template<class T> string DTEffOfflineAnalyzer::hName(const string& s, const T& id) const {
  string name(toString(id));
  stringstream hName;
  hName << s << name;
  return hName.str();
}

void DTEffOfflineAnalyzer::createTH1F(const std::string& name,
                               const std::string& title,
                               const std::string& suffix,
                               int nbin,
                               const double& binMin,
                               const double& binMax) const {
  stringstream hName;
  stringstream hTitle;
  hName << name << suffix;
  hTitle << title << suffix;
  theDQMStore->setCurrentFolder("DT/DTEffOfflineAnalyzer");
  theDQMStore->book1D(hName.str().c_str(), hTitle.str().c_str(), nbin,binMin,binMax);
//   TH1F * _h = new TH1F(hName.str().c_str(), hTitle.str().c_str(), nbin,binMin,binMax);
//   _h->SetDirectory(theFile); // Needed when the input is a root file
}

void DTEffOfflineAnalyzer::createTH2F(const std::string& name,
                               const std::string& title,
                               const std::string& suffix,
                               int nBinX,
                               const double& binXMin,
                               const double& binXMax,
                               int nBinY,
                               const double& binYMin,
                               const double& binYMax) const {
  stringstream hName;
  stringstream hTitle;
  hName << name << suffix;
  hTitle << title << suffix;
  theDQMStore->setCurrentFolder("DT/DTEffOfflineAnalyzer");
  theDQMStore->book2D(hName.str().c_str(), hTitle.str().c_str(), nBinX,binXMin,binXMax, nBinY,binYMin,binYMax);
  // TH2F * _h = new TH2F(hName.str().c_str(), hTitle.str().c_str(), nBinX,binXMin,binXMax, nBinY,binYMin,binYMax);
  // _h->SetDirectory(theFile); // Needed when the input is a root file

}

bool DTEffOfflineAnalyzer::getLCT(LCTType t) const {
  return LCT.test(t);
}
