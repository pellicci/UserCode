/******* \class DTOfflineAnalyzer ***********************************************
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
 *     February 2008.  
 *       To include the plots used on Commissioning
 *       To extend programs for running ALL wheels
 *     March 2008: Histo Modifications To allow run over the root files  
 *                 And all DTRecSegment2DCollection plots out (not in RECO)
 *
 *******************************i*****************************************/


/* This Class Header */
#include "UserCode/DTDPGAnalysis/src/DTOfflineAnalyzer.h"

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

#include "CalibMuon/DTDigiSync/interface/DTTTrigBaseSync.h"
#include "CalibMuon/DTDigiSync/interface/DTTTrigSyncFactory.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"
#include "DataFormats/DTRecHit/interface/DTRangeMapAccessor.h"
#include "UserCode/DTDPGAnalysis/src/DTMeanTimer.h"
#include "UserCode/DTDPGAnalysis/src/DTSegmentResidual.h"


#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoMuon/TrackingTools/interface/MuonPatternRecoDumper.h"

// this is to handle extrapolations
#include "DataFormats/GeometrySurface/interface/Cylinder.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"


// this is to retrieve digi's
#include "DataFormats/DTDigi/interface/DTDigiCollection.h"
#include "DataFormats/MuonDetId/interface/DTWireId.h"

#include "DataFormats/DTDigi/interface/DTLocalTriggerCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"

#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"

/* C++ Headers */
#include <iostream>
#include <cmath>
using namespace std;

/* ====================================================================== */

/* Constructor */ 
DTOfflineAnalyzer::DTOfflineAnalyzer(const ParameterSet& pset) : _ev(0){

  theSync =
    DTTTrigSyncFactory::get()->create(pset.getUntrackedParameter<string>("tTrigMode"),
                                      pset.getUntrackedParameter<ParameterSet>("tTrigModeConfig"));
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

  // the name of the 4D rec hits collection
  theSTAMuonLabel = pset.getParameter<string>("SALabel");

  // the name of the propagator
  thePropagatorName = pset.getParameter<std::string>("PropagatorName");
  thePropagator = 0;

  // if MC
  mc = pset.getParameter<bool>("isMC");

  LCT_RPC = pset.getParameter<bool>("LCT_RPC");
  LCT_DT = pset.getParameter<bool>("LCT_DT");
  LCT_CSC = pset.getParameter<bool>("LCT_CSC");


  doTrig = pset.getParameter<bool>("doTrig");
  doHits = pset.getParameter<bool>("doHits");
  doTBox = pset.getParameter<bool>("doTBox");
  doSegs = pset.getParameter<bool>("doSegs");
  doSA = pset.getParameter<bool>("doSA");

  doWheel[0] = pset.getParameter<bool>("doWheelm2");
  doWheel[1] = pset.getParameter<bool>("doWheelm1");
  doWheel[2] = pset.getParameter<bool>("doWheel0");
  doWheel[3] = pset.getParameter<bool>("doWheel1");
  doWheel[4] = pset.getParameter<bool>("doWheel2");

  doTBoxWheel[0] = pset.getParameter<bool>("doTBoxWhm2");
  doTBoxWheel[1] = pset.getParameter<bool>("doTBoxWhm1");
  doTBoxWheel[2] = pset.getParameter<bool>("doTBoxWh0");
  doTBoxWheel[3] = pset.getParameter<bool>("doTBoxWh1");
  doTBoxWheel[4] = pset.getParameter<bool>("doTBoxWh2");


  doTBoxSector = pset.getParameter<int>("doTBoxSector");
  doTBoxChamber= pset.getParameter<int>("doTBoxChamber");
  doTBoxSuperLayer= pset.getParameter<int>("doTBoxSuperLayer");
  doTBoxLayer= pset.getParameter<int>("doTBoxLayer");

   

  for(int iw=0;iw<5;iw++)
   if(doWheel[iw])
     cout<< "Wheeel "<< iw-2 << " will be analyzed "<< endl;


  // Create the root file
  //theFile = new TFile(theRootFileName.c_str(), "RECREATE");

  theDQMStore = edm::Service<DQMStore>().operator->();    
  
  init=false;

// ==================
// histogram booking
// ==================
  char Whname[5][20]={"Wm2","Wm1","W0","W1","W2"};


// global histos...------------
// 1d recHits (in whole detector)
  if(doHits) createTH1F("hnHitDT","Num 1d hits DT","", 200,0.,200.);
// 1d recHits Sector by Sector 
  if(doHits){
    for(int iw=0;iw<5;iw++)
    {
      if(doWheel[iw]){
         stringstream hname;
         stringstream hTitle;
         hname  << "hnHitDT" << Whname[iw]  ;
         hTitle << "Num 1d hits DT " <<  Whname[iw] ;
         createTH1F(hname.str(),hTitle.str(),"",200,0.,200.);
      }
    }
  }
// segments (in whole detector)
  if(doSegs) {
    createTH1F("hnSegDT","Num of DT segs","", 50,0.,50.);
    createTH1F("hnHSegDT","Num of high qual. DT segs","", 50,0.,50.);
    histo("hnHSegDT")->SetLineColor(2);

    createTH1F("hnSegMB1","Num of MB1 segs","", 50,0.,50.);
    createTH1F("hnHSegMB1","Num of high qual. MB1 segs","", 50,0.,50.);
    histo("hnHSegMB1")->SetLineColor(2);

    createTH1F("segphi","phi of segment position","",72,-180.,180.);
    createTH2F("segphivsz","phi vs z of segment position","",160,-800,800,180,-180.,180.); 

    for (int iMB=0; iMB<4; iMB++) {
     stringstream histoobj1; stringstream histoname1;
     histoobj1<<"segphiMB"<<iMB+1;
     histoname1<<"phi of segment position in MB"<<iMB+1;
     createTH1F(histoobj1.str(),histoname1.str(),"",72,-180.,180.); 
     histo(histoobj1.str())->GetXaxis()->SetTitle("deg.");
     histo(histoobj1.str())->SetLineColor(iMB+1);

     stringstream histoobj2; stringstream histoname2;  
     histoobj2<<"segzMB"<<iMB+1;
     histoname2<<"z of segment position in MB"<<iMB+1;
     createTH1F(histoobj2.str(),histoname2.str(),"",64,-800,800.);   
     histo(histoobj2.str())->GetXaxis()->SetTitle("cm");
     histo(histoobj2.str())->SetLineColor(iMB+1);
    } 

    createTH1F("DifPhi4_1_top","phi pos. in MB4 - MB1, top sects","",40,-40.,40.);
    createTH1F("DifPhi4_1_bot","phi pos. in MB4 - MB1, bottom sects","",40,-40.,40.);
    createTH1F("DifPhi4_1","phi pos. in MB4 - MB1","",40,-40.,40.);
    histo("DifPhi4_1_top")->GetXaxis()->SetTitle("deg.");
    histo("DifPhi4_1_bot")->GetXaxis()->SetTitle("deg.");
    histo("DifPhi4_1")->GetXaxis()->SetTitle("deg.");
    histo("DifPhi4_1_bot")->SetLineColor(2);
  }
// segments Sector by Secto
  if(doSegs){
    for(int iw=0;iw<5;iw++)
    {
      if(doWheel[iw]){
         stringstream hname;
         stringstream hTitle;
         hname  << "hnSegDT" << Whname[iw]  ;
         hTitle << "Num seg DT " << Whname[iw]  ;
         createTH1F(hname.str(),hTitle.str(),"",50,0.,50.);  
      }
    }
  }


// Trigger:
  if(doTrig)
  {
    createTH1F("TriggerQuality","Local Trigger quality","",8,-0.5,7.5);
    createTH1F("TriggerQualityMB4","Local Trigger quality, MB4","",8,-0.5,7.5);
    histo("TriggerQualityMB4")->SetLineColor(2);

    for(int iw=0;iw<5;iw++)
    {
      if(doWheel[iw]){
        stringstream hname;
        stringstream hTitle;
        hname << "TriggerInclusive" << Whname[iw]  ;
        hTitle << "Trigger Inclusive " << Whname[iw]  ;
        createTH1F (hname.str(),hTitle.str(),"",60,0.5,60.5);

        stringstream hname2;
        stringstream hTitle2;
        hname2 << "SectorTriggerMatrix" << Whname[iw]  ;
        hTitle2 << "SectorTrigger Matrix " << Whname[iw]  ;
        for (int ise=0; ise<12; ise++) sects[iw][ise]=0;
        createTH1F (hname2.str(),hTitle2.str(),"",21,-0.5,20.5);
      }
    }
  }//end if doTrig
  
// plots per Sector/CHambers / SL ------------------

 for ( int iw = 0; iw < 5; iw++) {   //Wheel  loop
  if(doWheel[iw]){ 
   for ( int sect = 1; sect < 15; sect++) {   // Sector loop

//   occupancy digi scatter plots
   if(doHits){
     stringstream hNameOcc; 
     stringstream hTitleOcc; 
     hNameOcc  << "hDigiXY_"  << Whname[iw] << "_S"  << sect ;
     hTitleOcc << "Digis in "  << Whname[iw] << " Sect" << sect ;
     createTH2F(hNameOcc.str(),hTitleOcc.str(),"",100, 0.,100.,80,0.,80.); // ** histos hDigiXY_S1, ecc... ********
   }//end if doHits

//   sectors trigger matrix
   if(doTrig)
   {
     stringstream hTitleTrigMat;
     stringstream hNameTrigMat;
     hNameTrigMat << "TriggerMatrix"  << Whname[iw] << "_S" << sect ;
     hTitleTrigMat << "Trigger Matrix, "  << Whname[iw] << " Sector " << sect ;
     createTH1F (hNameTrigMat.str(),hTitleTrigMat.str(),"",20,-0.5,19.5);

   }//end if doTrig


     for  ( int jst = 1; jst < 5; jst++ ) {   // station loop

//   trigger Histos: quality & bxID ----------------------
    if(doTrig)
    {
     stringstream hNameTrigg; 
     stringstream hTitleTrigg; 
     hNameTrigg  << "hTrigBits_"  << Whname[iw] << "_S" << sect << "_MB" << jst ;
     hTitleTrigg << "Highest trigg qual,"  << Whname[iw] << "S" << sect << "/MB" << jst ;
     createTH1F(hNameTrigg.str(),hTitleTrigg.str(),"",11,-1.,10.); // *** histos: hTrigBits_S1_MB1, ecc... **********
     for  ( int iqual = 1; iqual < 7; iqual++ ) { 
       stringstream hNameTriggBX; 
       stringstream hTitleTriggBX; 
       if (iqual == 1 || iqual > 3) {  // book histos for qual=1 (== all uncorrelated trigger), 4=LL, 5=HL, 6=HH
        hNameTriggBX  << "hTrigBX_"  << Whname[iw] << "_S" << sect << "_MB" << jst << "_qual" << iqual ;
        hTitleTriggBX << "Highest qual BXid,"  << Whname[iw] << "S" << sect << "/MB" << jst  << " qual=" << iqual;
        createTH1F(hNameTriggBX.str(),hTitleTriggBX.str(),"",40,0.,40.); // *** histos: hTrigBX_S1_MB1_qual1, ecc... **********
       }
     } // next quality flag 
    }//end if doTrig

        
//   Digi histos: ------------------------
//   time boxes per chamber....
//     float tmin = 3500., tmax = 4500.;  // full YB0, local Runs 25946,25602,...
//     float tmin = 2000., tmax = 3000.;  // Sept Global Runs
     float tmin = -200., tmax = 800.;  // for tbox ttrigger-subtracted
    if(doHits){
     stringstream hNameDigi; 
     stringstream hTitleDigi; 
     hNameDigi << "htime_"  << Whname[iw] << "_S" << sect << "_MB" << jst  ;
     hTitleDigi << "Tbox "  << Whname[iw] << " S" << sect << "/MB" << jst  ;
     createTH1F(hNameDigi.str(),hTitleDigi.str(),"",100,tmin, tmax); // *** histos: htime_S1_MB1, ecc... **********
    }//end if doHits  
     for (int sl = 1; sl < 4; sl++ ) {  // histograms per SL
//     time boxes per SL....
      if(doHits){
       stringstream hNameDigiSL; 
       stringstream hTitleDigiSL; 
       hNameDigiSL << "htime_"  << Whname[iw] << "_S" << sect << "_MB" << jst << "_SL" << sl  ;
       hTitleDigiSL << "TBox "  << Whname[iw] << " S" << sect << " MB" << jst << " SL" << sl  ;
       createTH1F(hNameDigiSL.str(),hTitleDigiSL.str(),"",100,tmin, tmax); // *** histos: htime_S1_MB1_SL1, ecc... **********
       for (int il = 1; il < 5; il++ ) {  // histograms per Layer
         stringstream hNameDigiL; 
         stringstream hTitleDigiL; 
         hNameDigiL << "htime_"  << Whname[iw] << "_S" << sect << "_MB" << jst << "_SL" << sl  << "_L" <<il;
         hTitleDigiL << "TBox "  << Whname[iw] << " S" << sect << " MB" << jst << " SL" << sl  << " L" <<il;
         createTH1F(hNameDigiL.str(),hTitleDigiL.str(),"",100,tmin, tmax); // *** histos: htime_S1_MB1_SL1, ecc... **********
         if(doTBox && doTBoxWheel[iw]) //make single tbox histos cell by cell
         if(doTBoxSector==0 || doTBoxSector== sect)   
         if(doTBoxChamber==0 || doTBoxChamber== jst)
         if(doTBoxSuperLayer==0 || doTBoxSuperLayer==sl )
         if(doTBoxLayer==0 || doTBoxLayer==il )
         {
           int icmax=100;
           if(sl==2)icmax=57;
           else if(jst==1)icmax=49;  
           else if(jst==2)icmax=60;  
           else if(jst==3)icmax=73;  
           for (int ic = 1; ic < icmax+1; ic++ ) {  // histograms per Cell 
             stringstream hNameDigiC; 
             stringstream hTitleDigiC; 
             hNameDigiC << "htime_"  << Whname[iw] << "_S" << sect << "_MB" << jst << "_SL" << sl  << "_L" <<il <<"_C" << ic;
             hTitleDigiC << "TBox "  << Whname[iw] << " S" << sect << " MB" << jst << " SL" << sl  << " L" <<il <<"_C" << ic;
             createTH1F(hNameDigiC.str(),hTitleDigiC.str(),"",100,tmin, tmax); // *** histos: htime_S1_MB1_SL1_C1, ecc... **********
             //cout << " Produccing TBox:   " << hNameDigiC.str() <<  endl ; 
           }
         }
       }//end Layer 
      }//end if doHits  
      if(doSegs)
      {
//     tmax plots per SL...
       float t1 = 300., t2 = 450. ;
       stringstream hNameTmax; 
       stringstream hTitleTmax; 
       hNameTmax  << "htmax_"  << Whname[iw] << "_S" << sect << "_MB" << jst << "_SL" << sl  ;
       hTitleTmax << "Tmax "  << Whname[iw] << " S" << sect << "/MB" << jst << "/SL" << sl  ;
       createTH1F(hNameTmax.str(),hTitleTmax.str(),"",100,t1, t2); // *** histos: htmaxYB0_S1_MB1_SL1, ecc... **********
      }// end if doSegs
     } // next SL

    if(doSegs)
    {
//   hit residuals in segments -------------
     float xmin = -0.25, xmax = 0.25 ; // cm
     stringstream hNameRes; 
     stringstream hTitleRes; 
     hNameRes << "hResX_"  << Whname[iw] << "_S" << sect << "_MB" << jst ;
     hTitleRes << "Hit residuals "  << Whname[iw] << " S" << sect << "/MB" << jst ;
     createTH1F(hNameRes.str(),hTitleRes.str(),"",100,xmin, xmax); // *** histos: hResX_S1_MB1, ecc... **********

//   philocal of rec segments
     float phimin = -50., phimax = 50.;
     stringstream hNamePhi; 
     stringstream hTitlePhi; 
     hNamePhi  << "hPhi_"  << Whname[iw] << "_S" << sect << "_MB" << jst ;
     hTitlePhi << "Phi local "  << Whname[iw] << " S" << sect << "/MB" << jst ;
     createTH1F(hNamePhi.str(),hTitlePhi.str(),"",100,phimin, phimax); // *** histos: hPhi_S1_MB1, ecc... **********

//   philocal of rec segments HH/HL
     phimin = -90., phimax = 90.;
     stringstream hNamePhiHL; 
     stringstream hTitlePhiHL; 
     hNamePhiHL  << "hPhiHL_"  << Whname[iw] << "_S" << sect << "_MB" << jst ;
     hTitlePhiHL << "Phi local "  << Whname[iw] << " S" << sect << "/MB" << jst << "(>7 hits)";
     createTH1F(hNamePhiHL.str(),hTitlePhiHL.str(),"",90,phimin, phimax); // *** histos: hPhiHL_S1_MB1, ecc... **********
//   localposition of phi rec segments HH/HL
     float xposmin = -150., xposmax = 150.;
     stringstream hNamePosHL; 
     stringstream hTitlePosHL; 
     hNamePosHL  << "hTrg_effdenum_"  << Whname[iw] << "_S" << sect << "_MB" << jst ;
     hTitlePosHL << "Phi local Position "  << Whname[iw] << " S" << sect << "/MB" << jst << "(>7 hits)";
     createTH1F(hNamePosHL.str(),hTitlePosHL.str(),"",50,xposmin, xposmax); // *** histos: hTrg_effdenum_S1_MB1, ecc... **********
  
//   localposition of HH/HL Triggers for phi rec segments HH/HL
     stringstream hNamePosTrigHL; 
     stringstream hTitlePosTrigHL; 
     hNamePosTrigHL  << "hTrg_effnum_"  << Whname[iw] << "_S" << sect << "_MB" << jst ;
     hTitlePosTrigHL << "Phi local Position "  << Whname[iw] << " S" << sect << "/MB" << jst << "(>7 hits & HH/HL trig)";
     createTH1F(hNamePosTrigHL.str(),hTitlePosTrigHL.str(),"",50,xposmin, xposmax); // *** histos: hTrg_effnum_S1_MB1, ecc... **********
//    hits in track segments
     stringstream hNameHits; 
     stringstream hTitleHits; 
     hNameHits  << "hNhits_"  << Whname[iw] << "_S" << sect << "_MB" << jst ;
     hTitleHits << "Nr.hits in segment, "  << Whname[iw] << " S" << sect << "/MB" << jst ;
     createTH1F(hNameHits.str(),hTitleHits.str(),"",15,0, 15); // *** histos: hNhits_S1_MB1, ecc... **********
    }// end if doSegs

   }   // next station ===========================

  if(doSegs)
  {
// segments in Sector
   stringstream hNameNsegm; 
   stringstream hTitleNsegm; 
   hNameNsegm << "hNsegs_"  << Whname[iw] << "_S" << sect  ;
   hTitleNsegm << "Segments in "  << Whname[iw] << " sect " << sect  ;
   createTH1F(hNameNsegm.str(),hTitleNsegm.str(),"",10, 0, 10); // *** histos: hNsegs_S1 ecc... **********
  }// end if doSegs

// associated hits to global track per sector
  if(doSA)
  {
   stringstream hNameNassH; 
   stringstream hTitleNassH; 
   hNameNassH<< "hNhass_"  << Whname[iw] << "_S" << sect  ;
   hTitleNassH<< "Associated hits in "  << Whname[iw] << " sect." << sect  ;
   createTH1F(hNameNassH.str(),hTitleNassH.str(),"",50, 0, 50); // *** histos: hNhass_S1 ecc... **********
  }// end if doSegs
 
  } // next sector ============================
 }
} // next wheel  ============================
          

	  
 if(doSA)
 {
  // STA Muon plots
  createTH1F("hNSA","Num SA tracks in events","", 6, -0.5, 5.5);
  createTH1F("hNhitsSA","Num hits in SA tracks","", 50, .5, 50.5);
  createTH1F("hChi2SA","#chi^{2}/NDoF for SA tracks","", 100, 0, 100.);
  createTH1F("hPIPSA","p for SA tracks @ IP","", 100, 0., 100);
  createTH1F("hPtIPSA","pt for SA tracks @ IP","", 100, 0., 100);
  createTH1F("hPhiIPSA","#phi for SA tracks @ IP","", 100, -3.14, 3.14);
  createTH1F("hEtaIPSA","#eta for SA tracks @ IP","", 100, -2.5, 2.5);
  createTH1F("hrIPSA"," r at IP","",100,0.,500.);
  createTH1F("hzIPSA"," z at IP","",100,-750.,750.);
  createTH2F("hrVszIPSA"," r vs z at IP","",100,-750.,750.,100,0.,500.);

  createTH1F("hPInnerTSOSSA","p for SA tracks @ innermost TSOS","", 100, 0., 100);
  createTH1F("hPtInnerTSOSSA","pt for SA tracks @ innermost TSOS","", 100, 0., 100);
  createTH1F("hPhiInnerTSOSSA","#phi for SA tracks @ innermost TSOS","", 100, -3.14, 3.14);
  createTH1F("hEtaInnerTSOSSA","#eta for SA tracks @ innermost TSOS","", 100, -2.5, 2.5);
  createTH1F("hInnerRSA","Radius of innermost TSOS for SA tracks","", 100, 400, 1000.);
  createTH1F("hOuterRSA","Radius of outermost TSOS for SA tracks","", 100, 400, 1000.);
  createTH2F("hInnerOuterRSA","Radius of outermost TSOS vs innermost one for SA tracks","",
           40, 400, 1000.,40, 400, 1000.);

                  
  createTH2F("hNSAVsNHits",  "Nr.SA tracks vs Nr.1d Hits","", 100,-0.5,39.5, 5,-0.5, 4.5);
  createTH2F("hNSAVsNSegs2D","Nr.SA tracks vs Nr.2d Segs","", 20,-0.5,19.5, 5,-0.5, 4.5);
  createTH2F("hNSAVsNSegs4D","Nr.SA tracks vs Nr.4d Segs","", 10,-0.5,9.5, 5,-0.5, 4.5);

  createTH2F("hNHitsSAVsNHits",  "N Hits SA vs Nr. 1d Hits","", 40,-0.5,39.5,100,0,100);
  createTH2F("hNHitsSAVsNSegs2D","N Hits SA vs Nr. 2d Segs","", 20,-0.5,19.5,100,0,100);
  createTH2F("hNHitsSAVsNSegs4D","N Hits SA vs Nr. 4d Segs","", 10,-0.5,9.5, 100,0,100);

  createTH2F("hHitsPosXYSA","Hits position (x,y) SA","",150,-750,750,150,-750,750);
  createTH2F("hHitsPosXYSA_1","Hits position (x,y) SA","",150,0,750,150,0,750);
  createTH2F("hHitsPosXYSA_2","Hits position (x,y) SA","",150,-750,0,150,0,750);
  createTH2F("hHitsPosXYSA_3","Hits position (x,y) SA","",150,-750,0,150,-750,0);
  createTH2F("hHitsPosXYSA_4","Hits position (x,y) SA","",150,0,750,150,-750,0);
  createTH2F("hHitsPosXZSA","Hits position (x,z) SA","",100,-700,700,100,-800,800);
  createTH2F("hHitsPosYZSA","Hits position (y,z) SA","",100,-700,700,100,-800,800);
  for ( int iw = 0; iw < 5; iw++) {   //Wheel  loop
   if(doWheel[iw]){ 
     stringstream hTitlePhihit;
     stringstream hNamePhihit;
     hNamePhihit << "hHitsPosXYSA_" << Whname[iw] ;
     hTitlePhihit << "Hits position (x,y) SA " << Whname[iw] ;
     createTH2F(hNamePhihit.str(),hTitlePhihit.str(),"",150,-750,750,150,-750,750);
     stringstream hNamePhihit2;
     hNamePhihit2 << "hHitsPosXYSA_1_" << Whname[iw] ;
     createTH2F(hNamePhihit2.str(),hTitlePhihit.str(),"",150,0,750,150,0,750);
     stringstream hNamePhihit3;
     hNamePhihit3 << "hHitsPosXYSA_2_" << Whname[iw] ;
     createTH2F(hNamePhihit3.str(),hTitlePhihit.str(),"",150,-750,0,150,0,750);
     stringstream hNamePhihit4;
     hNamePhihit4 << "hHitsPosXYSA_3_" << Whname[iw] ;
     createTH2F(hNamePhihit4.str(),hTitlePhihit.str(),"",150,-750,0,150,-750,0);
     stringstream hNamePhihit5;
     hNamePhihit5 << "hHitsPosXYSA_4_" << Whname[iw] ;
     createTH2F(hNamePhihit5.str(),hTitlePhihit.str(),"",150,0,750,150,-750,0);
     stringstream hNamePhihitXZ;
     stringstream hTitlePhihitXZ;
     hNamePhihitXZ << "hHitsPosXZSA_" << Whname[iw] ;
     hTitlePhihitXZ << "Hits position (x,z) SA " << Whname[iw] ;
     createTH2F(hNamePhihitXZ.str(),hTitlePhihitXZ.str(),"",100,-700,700,100,-800,800);
     stringstream hNamePhihitYZ;
     stringstream hTitlePhihitYZ;
     hNamePhihitYZ << "hHitsPosYZSA_" << Whname[iw] ;
     hTitlePhihitYZ << "Hits position (y,z) SA " << Whname[iw] ;
     createTH2F(hNamePhihitYZ.str(),hTitlePhihitYZ.str(),"",100,-700,700,100,-800,800);
   }
  }

 }//end if doSA

// Global Phi of associated rechits  
 for ( int iw = 0; iw < 5; iw++) {   //Wheel  loop
 if(doWheel[iw]){ 
  for  ( int jst = 1; jst < 5; jst++ ) {   // station loop
    if(doSA)
    {
     stringstream hTitlePhihit;
     stringstream hNamePhihit;
     hNamePhihit << "hPhiHit_" << Whname[iw] << "_MB" << jst ;
     hTitlePhihit << "Phi of ass.hit," << Whname[iw] << " MB" << jst ;
     createTH1F(hNamePhihit.str(),hTitlePhihit.str(),"",180,-180., 180.); // *** histos: hPhiHit_MB1 ecc... **********
    }//end if doSA
    if(doSegs)
    {
     stringstream hNamePhiGlob;
     stringstream hTitlePhiGlob;
     hNamePhiGlob << "hPhiGlob_" << Whname[iw] << "_MB" << jst;
     hTitlePhiGlob << "Phi-Trigger eff," << Whname[iw] << " MB" << jst;
     createTH1F(hNamePhiGlob.str(),hTitlePhiGlob.str(),"",180,-180., 180.); // *** histos: hPhiGlob_MB1 ecc... **********
     stringstream hNamePhiTrigg;
     stringstream hTitlePhiTrigg;
     hNamePhiTrigg << "hPhiTrigg_" << Whname[iw] << "_MB" << jst;
     hTitlePhiTrigg << "Phi-Trigger eff," << Whname[iw] << " MB"  << jst;
     createTH1F(hNamePhiTrigg.str(),hTitlePhiTrigg.str(),"",180,-180., 180.); // *** histos: hPhiTrigg_MB1 ecc... **********
    }//end if doSegs
  } // nest station
 }
 }

 if(doSegs)
 { // DigiTime of hits associated to segments
   for ( int iw = 0; iw < 5; iw++) {   //Wheel  loop
   if(doWheel[iw]){ 
   for (int isc=1;isc<15;isc++){// Sector Loop
    for  ( int jst = 1; jst < 5; jst++ ) {   // station loop
      stringstream hNameSegTimeMB;
      stringstream hTitleSegTimeMB;
      hNameSegTimeMB << "SegTimeBox_"  << Whname[iw] << "_S"  << isc << "_MB" << jst;
      hTitleSegTimeMB << "Time Hits (Segment) " << Whname[iw] << "_S"  << isc << "_MB" << jst;
      createTH1F(hNameSegTimeMB.str(),hTitleSegTimeMB.str(),"",100,-200., 800.); // *** histos: 
      for (int isl=1;isl<4;isl++){// SuperLayer Loop
         stringstream hNameSegTimeSL;
         stringstream hTitleSegTimeSL;
         hNameSegTimeSL << "SegTimeBox_"  << Whname[iw] << "_S"  << isc << "_MB" << jst << "_SL"<< isl;
         hTitleSegTimeSL << "Time Hits (Segment) " << Whname[iw] << "_S"  << isc << "_MB" << jst << "_SL"<< isl;
         createTH1F(hNameSegTimeSL.str(),hTitleSegTimeSL.str(),"",100,-200., 800.); // *** histos: 
         for (int il=1;il<5;il++){// Layer Loop
            stringstream hNameSegTime;
            stringstream hTitleSegTime;
            hNameSegTime << "SegTimeBox_"  << Whname[iw] << "_S"  << isc << "_MB" << jst << "_SL"<< isl << "_L" << il;
            hTitleSegTime << "Time Hits (Segment) " << Whname[iw] << "_S"  << isc << "_MB" << jst << "_SL"<< isl << "_L" << il;
            createTH1F(hNameSegTime.str(),hTitleSegTime.str(),"",100,-200., 800.); // *** histos: 
         }//Layer loop
      }//Layer Superloop
     } // Station loop        
    } // Sector loop        
    } // If doWheel 
   } // Wheel loop        

 }


  
//  extrapolations to ECAL, HCAL  
  float zmin = -400., zmax = 400.;
  if(doSA){
   createTH2F("hphivszECAL","Extrap.position phi-vs-z to ECAL ","",100,zmin,zmax,90,-180,180);
   createTH2F("hphivszHCAL","Extrap.position phi-vs-z to HCAL ","",100,zmin,zmax,90,-180,180);
  }//end if doSA


} // end constructor =================================================================

/* Destructor */ 
DTOfflineAnalyzer::~DTOfflineAnalyzer() {
  if(doTrig)LabelTriggerMatrix(); // Trigger Matrix Labels
  theDQMStore->rmdir("DT/DTOfflineAnalyzer");
    cout << " END Destructor " << endl;
} // end destructor ================================================================

// tools for trigger analysis.....==============================================
void DTOfflineAnalyzer::LabelTriggerMatrix() {
  char Whname[5][20]={"Wm2","Wm1","W0","W1","W2"};

  //Labels for SectorTriggerMatrix:

 for(int iw=0;iw<5;iw++)
 {
  if(doWheel[iw])
 {
   char A[3]; char B[3]; char C[3]; char D[3];
  sprintf (A,"%u",sects[iw][0]);  sprintf (B,"%u",sects[iw][1]);  sprintf (C,"%u",sects[iw][2]); sprintf (D,"%u",sects[iw][3]);
  std::string lab1[] = {" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "};
  
  lab1[0]="no trig";
  lab1[1]="other sects";
  lab1[3]= lab1[3] + "Sect" + A;
  if (sects[iw][1]) {
   lab1[4]= lab1[4] + "Sect" + B;
   lab1[8]=lab1[8] + A + " & " + B;
   if (sects[iw][2]) {
    lab1[5]=lab1[5] + "Sect" + C;
    lab1[9]=lab1[9] + A + " & " + C;
    lab1[11]=lab1[11] + B +" & " + C;
    lab1[15]=lab1[15] + A + " & " + B +" & " + C;
    if (sects[iw][3]) {
     lab1[6]=lab1[6] + "Sect" + D;
     lab1[10]=lab1[10] + A + " & " + D;
     lab1[12]=lab1[12] + B + " & " + D;
     lab1[13]=lab1[13] + C + " & " + D;

     lab1[16]=lab1[16] + A + " & " + B + " & " + D;
     lab1[17]=lab1[17] + A + " & " + C + " & " + D;
     lab1[18]=lab1[18] + B + " & " + C + " & " + D;

     lab1[20]=lab1[20] + A + " & " + B + " & " + C + " & " + D;
    }
   }
  }

    stringstream hname;
     hname << "SectorTriggerMatrix" << Whname[iw]  ;
    // for (int ibin=1; ibin<21; ibin++) histo(hname.str())->GetXaxis()->SetBinLabel(ibin,lab1[ibin-1].c_str()); 
   }
  }

// Labels for TriggerMatrix:

 //char * lab[]={"no trig"," ","MB1","MB2","MB3","MB4"," ","1 & 2","1 & 3","1 & 4","2 & 3","2 & 4",
 //             "3 & 4"," ","1 & 2 & 3","1 & 2 & 4","1 & 3 & 4","2 & 3 & 4"," ","1 & 2 & 3 & 4"};
 //char  lab[20][100]={"no trig"," ","MB1","MB2","MB3","MB4"," ","1 & 2","1 & 3","1 & 4","2 & 3","2 & 4",
 //             "3 & 4"," ","1 & 2 & 3","1 & 2 & 4","1 & 3 & 4","2 & 3 & 4"," ","1 & 2 & 3 & 4"};
 for(int iw=0;iw<5;iw++){
 if(doWheel[iw]){
  for (int ise=1; ise<13; ise++) {
   stringstream hName; 
   hName  << "TriggerMatrix"  << Whname[iw] << "_S" << ise ;
   //for (int ibin=1; ibin<21; ibin++) histo(hName.str())->GetXaxis()->SetBinLabel(ibin,lab[ibin-1]); 
  }
 }}

// Labels for TriggerInclusive:
  char label[10];
 for(int iw=0;iw<5;iw++){
 if(doWheel[iw]){
  for (int ise=1; ise<13; ise++) {
   for (int ibin=1; ibin<5; ibin++) {
    sprintf (label,"S%uMB%u",ise,ibin);
    stringstream hname;
    hname << "TriggerInclusive" << Whname[iw]  ;
  //  histo(hname.str())->GetXaxis()->SetBinLabel((ise-1)*5+ibin,label);
   } 
   stringstream hname2;
   hname2 << "TriggerInclusive" << Whname[iw]  ;
//   histo(hname2.str())->GetXaxis()->SetBinLabel(ise*5," ");
  }
 }
 }

}

// Operations : main module ======================================================================
void DTOfflineAnalyzer::analyze(const Event & event,
                         const EventSetup& eventSetup) {
// ===============================================================================================

  theSync->setES(eventSetup);

  int nprt = event.id().event() - 100*(event.id().event()/100);
  if( nprt == 1000)
    cout << "Run:Event analyzed " << event.id().run() << ":" << event.id().event() <<
    " Num " << _ev++ << endl;

  if (debug) cout << endl<<"--- [DTOfflineAnalyzer] Event analysed #Run: " <<
    event.id().run() << " #Event: " << event.id().event() << " =====================================" <<  endl;

  float nrun=event.id().run();
  if(!init)  
  {
     createTH1F("RunInfo_RunNumbers","RunInfo_RunNumbers","",23,nrun-11.5,nrun+11.5);
     init=true;
  }
  histo("RunInfo_RunNumbers")->Fill(nrun); 
                      
// go on with the rest of analysis: DIGI/RecHits, Segments, STAmuons... ============
  if (selectEvent()) {
    if (doTrig) analyzeTrigger(event, eventSetup);
    if (doHits) analyzeDTHits(event, eventSetup);
    if (doSegs) analyzeDTSegments(event, eventSetup);
    if (doSA) analyzeSATrack(event, eventSetup);
  }

} // end main =========================================================================================== 

bool DTOfflineAnalyzer::selectEvent() const {
  bool trigger=true;
//  if( qual[0] > 3 ) trigger = true ; // HH,HL,LL trigger in MB1
  return trigger;
}

// ============================================================================================================
// Hits & RecHits analysis 
void DTOfflineAnalyzer::analyzeDTHits(const Event & event,
                               const EventSetup& eventSetup){
// ============================================================================================================
 
  char Whname[5][20]={"Wm2","Wm1","W0","W1","W2"};

 // Get the DT Geometry
  ESHandle<DTGeometry> dtGeom;
  eventSetup.get<MuonGeometryRecord>().get(dtGeom);


   // Get the digis from the event ======================
  Handle<DTDigiCollection> digis; 
//  event.getByLabel(digiLabel, digis);
  event.getByLabel(theDTLocalTriggerLabel, digis);
  
 // Iterate through all digi collections ordered by LayerId  -------------------  

  DTDigiCollection::DigiRangeIterator dtLayerIt;
  for (dtLayerIt = digis->begin();
       dtLayerIt != digis->end();  ++dtLayerIt){   // loop on layerID -------
    // The layerId
    const DTLayerId layerId = (*dtLayerIt).first;
//    const DTSuperLayerId slId = layerId.superlayerId();
   int iw=2+layerId.wheel();
   if(doWheel[iw])
   {
    // Get the iterators over the digis associated with this LayerId
    const DTDigiCollection::Range& digiRange = (*dtLayerIt).second;
    // Loop over all digis in the given range
    for (DTDigiCollection::const_iterator digi = digiRange.first;   // loop on digi --------
	 digi != digiRange.second;
	 digi++) {                                        
      const DTWireId wireId(layerId, (*digi).wire());
      int ix = wireId.wire();
      int iy = 20*(wireId.station()-1) + 4*(wireId.superlayer()-1) + wireId.layer();
      int se = wireId.sector();
//    occupancy scatter plot -----------------------------------
      stringstream hTitleDigi; 
      hTitleDigi  << "hDigiXY_"  << Whname[iw] << "_S"  << se ;
      histo2d(hTitleDigi.str())->Fill( ix,iy ); // *** histos: hDigiXY_S1, ecc... **********


// the ttrigg used for this channel
   float ttrig = theSync->offset(wireId);
                                 
   float TDCtime = (*digi).time() - ttrig ; // plot the TDC times ttrigg-subtracted....


//   if ( wireId.wheel() == 0 ) {  // YB0 =========================
        stringstream hTitle, hTitleSL, hTitleL, hTitleC; 
        hTitle << "htime_"  << Whname[iw] << "_S" << wireId.sector() << "_MB" << wireId.station() ;
        histo(hTitle.str())->Fill( TDCtime ); // *** histos: htime_1_MB1, ecc... **********
        hTitleSL << "htime_"  << Whname[iw] << "_S" << wireId.sector() << "_MB" << wireId.station() << "_SL"<< wireId.superlayer() ;
        histo(hTitleSL.str())->Fill( TDCtime ); // *** histos: htime_S1_MB1_SL1, ecc... **********		
        hTitleL << "htime_"  << Whname[iw] << "_S" << wireId.sector() << "_MB" << wireId.station() << "_SL"<< wireId.superlayer() 
                              << "_L"<< wireId.layer() ;
        histo(hTitleL.str())->Fill( TDCtime ); // *** histos: htime_S1_MB1_SL1_L1, ecc... **********		
        if(doTBox && doTBoxWheel[iw]) 
        if(doTBoxSector==0 || doTBoxSector== wireId.sector())    
        if(doTBoxChamber==0 || doTBoxChamber== wireId.station() )
        if(doTBoxSuperLayer==0 || doTBoxSuperLayer==wireId.superlayer() ) 
        if(doTBoxLayer==0 || doTBoxLayer==wireId.layer() )
        {
          hTitleC << "htime_"  << Whname[iw] << "_S" << wireId.sector() << "_MB" << wireId.station() << "_SL"<< wireId.superlayer() 
                                << "_L"<< wireId.layer() << "_C"<< wireId.wire() ;
          histo(hTitleC.str())->Fill( TDCtime ); // *** histos: htime_S1_MB1_SL1_L1_C1, ecc... **********		
          //cout << " Filling TBox:    " << hTitleC.str() <<  endl ; 
        }
//    } // endif YB0 ==============================================

    
   } // next digi --------------------
   }// End if doWheel
  } // next LayerId -----------------


//  get the tracking geometry
  ESHandle<GlobalTrackingGeometry> theTrackingGeometry;
  eventSetup.get<GlobalTrackingGeometryRecord>().get(theTrackingGeometry);


  // Get the 1D rechits from the event --------------
  Handle<DTRecHitCollection> dtRecHits; 
  event.getByLabel(theRecHits1DLabel, dtRecHits);

  int nHitDT = dtRecHits->size();
  histo("hnHitDT")->Fill(nHitDT);

  int nHitDTWh[5]={0,0,0,0,0};
// ********* recHits loop ***********************
  for (DTRecHitCollection::const_iterator hit = dtRecHits->begin();
       hit!=dtRecHits->end();  ++hit) {
    // Get the wireId of the rechit
    DTWireId wireId = (*hit).wireId();
    int iwI=2+wireId.wheel();
    if(doWheel[iwI])nHitDTWh[iwI]++;
  } // ********* end recHits loop  *******************

  for(int iw=0;iw<5;iw++){
   if(doWheel[iw]){
      stringstream hname;
      hname  << "hnHitDT" << Whname[iw]  ;
      histo(hname.str())->Fill(nHitDTWh[iw]);
   }
  }

} // end DTHits analyzer ===============================================



// ==========================================================================================================
// Segment analysis:
void DTOfflineAnalyzer::analyzeDTSegments(const Event & event,
                                   const EventSetup& eventSetup){
// ==========================================================================================================

  if (debug) cout << " analyzeDTSegments: " << " Run/Event " << event.id().run() << ":" << event.id().event() << endl;

  char Whname[5][20]={"Wm2","Wm1","W0","W1","W2"};

  // Get the DT Geometry
  ESHandle<DTGeometry> dtGeom;
  eventSetup.get<MuonGeometryRecord>().get(dtGeom);

  // Get the digis from the event
  Handle<DTLocalTriggerCollection> digis; 
  if (!mc) event.getByLabel(theDTLocalTriggerLabel, digis);

  // Get the 4D rechit collection from the event -------------------
  edm::Handle<DTRecSegment4DCollection> segs;
  event.getByLabel(theRecHits4DLabel, segs);
  if (debug) cout << "4d segments: " << segs->size() << endl;

  // Get the 1D rechits from the event --------------
  Handle<DTRecHitCollection> dtRecHits; 
  event.getByLabel(theRecHits1DLabel, dtRecHits);
  if (debug) cout << "1d rechits: " << dtRecHits->size() << endl;

  int nsegs = segs->size();
  histo("hnSegDT")->Fill(nsegs);
  const std::vector<DTChamber*> & chs = dtGeom->chambers();


 int qual[5][4][14];
 for (int iw=0; iw<5; iw++)   // Wheel 1-5         
  for (int sec=1; sec<15; ++sec)   // section 1 to 14
    for (int ist=0; ist<4; ++ist) { 
      qual[iw][ist][sec-1] = -1;
    }    

 if(doTrig)
 {
// ======================================
//  local trigger analysis
//=======================================
  // get the DT local trigger collection =======================
  edm::Handle<DTLocalTriggerCollection> allLocalTriggers;
  event.getByLabel(theDTLocalTriggerLabel, allLocalTriggers); 
 DTLocalTriggerCollection::DigiRangeIterator chambIt;
// Loop over chambers present in DTLocalTriggerCollection
  int SCsect=0; int SCst=0;
  for (chambIt=allLocalTriggers->begin();chambIt!=allLocalTriggers->end();++chambIt){ // loop on chambers ------
   const DTChamberId& id = (*chambIt).first;
   SCst=id.station();
   SCsect=id.sector();
   int iw=2+id.wheel();

   if(doWheel[iw]){
    const DTLocalTriggerCollection::Range& range = (*chambIt).second;    
    int ntrCh=0;
//  loop over triggers of this chamber
    for (DTLocalTriggerCollection::const_iterator trigtrack = range.first;trigtrack!=range.second;++trigtrack){
      if (trigtrack->quality()<7) {
       ntrCh++; 
       if (ntrCh>4) break;
       if (qual[iw][SCst-1][SCsect-1]!=-2) { 
         int iQual=trigtrack->quality();
         if( iQual > qual[iw][SCst-1][SCsect-1] ) qual[iw][SCst-1][SCsect-1]= iQual;  // store the best trigger quality for this station
       } //end if qual != -2
      } //  quality <7 
    } // end loop on triggers in this chambers -------------    
   } // end if(doWheel[iw])

  } //end loop on chambers -------  
 }
// ===== end local trigger analysis =========================================   

// counters for segments in sectors
   int nSegSect[5][15];
    for (int iw=0; iw<5; iw++)   // Wheel -2 (0) to 2 (4)
    for (int sec=1; sec<=15; ++sec) { // section 1 to 14
      nSegSect[iw][sec] = 0;
    }


  int NsegmH=0; int NsMB1=0; int NsHMB1=0;
  double phi1[10]; double phi4[10]; int where1[10][2]; int where4[10][2]; int N1=0; int N4=0;  

// loop on chambers ==============================================
  for (std::vector<DTChamber*>::const_iterator ch = chs.begin();
       ch!=chs.end() ; ++ch) {
   DTChamberId chid((*ch)->id());
   int iw= 2+chid.wheel();
   DTRecSegment4DCollection::range segsch= segs->get(chid);

   if(doWheel[iw])
   {
   

// ********** loop on 4D segments *********************************


    for (DTRecSegment4DCollection::const_iterator seg=segsch.first ;
         seg!=segsch.second ; ++seg ) {

      int ist    = seg->chamberId().station();
      if (ist==1) NsMB1++;
 //   int iwheel = seg->chamberId().wheel() + 3;  // Wheel -2,.+2  => 1,...5
      int isect  = seg->chamberId().sector();
      int iisect = isect;
      if (isect == 13 ) isect = 4;
      if (isect == 14 ) isect = 10;
      
      const DTChamber* ch = dtGeom->chamber(seg->chamberId());
      GlobalPoint   glbPoint = ch->toGlobal((*seg).localPosition());
      //GlobalVector  glbDir   = ch->toGlobal((*seg).localDirection());  // Not being used and in 62X gives erors for being set but not used

      float radtodeg = 57.296;

      float phiglobal =  glbPoint.phi(); // phi position of reco segments
      float zglobal =    glbPoint.z(); // zed position of reco segments
      histo2d("segphivsz")->Fill(zglobal,radtodeg*phiglobal);
      histo("segphi")->Fill(radtodeg*phiglobal);
      stringstream histoobj1;
      histoobj1<<"segphiMB"<<ist;
      histo(histoobj1.str())->Fill(radtodeg*phiglobal);
      stringstream histoobj2;
      histoobj2<<"segzMB"<<ist;
      histo(histoobj2.str())->Fill(zglobal);     

      if (ist==1) {
	if (N1<10) { 
            phi1[N1]=radtodeg*phiglobal;
            where1[N1][0]=iw;
            where1[N1][1]=isect;
            N1++;
        } 
      }
      else if (ist==4) {
        if (N4<10) {
            phi4[N4]=radtodeg*phiglobal;
            where4[N4][0]=iw;
            where4[N4][1]=isect;
            N4++;
        }
      } 

      // first the the two projection separately -----------------
      // phi segment
      if(debug) cout  << seg->chamberId() << endl;
      if(debug) cout  << " 4D  segm: x " << glbPoint.x() << " y " << glbPoint.y() << " z " << glbPoint.z() << endl;
      const DTChamberRecSegment2D* phiSeg= (*seg).phiSegment();
//      cout <<  -atan(glbDir.x()/ glbDir.y()) << endl;
      float localPhi = (*seg).localDirection().x();
      float localPhideg = radtodeg * atan(localPhi);
      std::vector<DTRecHit1D> phiHits; 
      int NtkHit = 0;    
      if (phiSeg) {
        phiHits = phiSeg->specificRecHits();
        if(debug) cout << " Nhits in Phi-segment " << phiHits.size() << endl;
        NtkHit = phiHits.size();
        if (phiHits.size()>=6)      { // Nhits > 6
        stringstream hTitlePhi;
        hTitlePhi << "hPhi_"  << Whname[iw] << "_S" << isect << "_MB" << ist;
        histo(hTitlePhi.str())->Fill( localPhideg ); // *** histos: hPhiS1_MB1, ecc... **********

        float  phiLocal= 57.296*atan((*seg).localDirection().x()/(*seg).localDirection().z());
        if (phiHits.size()>6)
        {
          stringstream hTitlePhiHL;
          hTitlePhiHL << "hPhiHL_"  << Whname[iw] << "_S" << iisect << "_MB" << ist;
          histo(hTitlePhiHL.str())->Fill( phiLocal );
          NsegmH++;
          if (ist==1) NsHMB1++;

        }
        int MBeffSec = 0;  // don't use this station [ist,isec ]
        for ( int ist1=1; ist1 < 5; ++ist1)
           if (ist1 != ist && qual[iw][ist1-1][iisect-1] > -1 ) MBeffSec = 1;
        if(MBeffSec)   // event triggered also by other stations on same sector;
        if (phiHits.size()>6 && abs(phiLocal) < 40. )
        { 
             stringstream hNamePosHL;
             hNamePosHL  << "hTrg_effdenum_"  << Whname[iw] << "_S" << iisect << "_MB" << ist ;
             histo(hNamePosHL.str())->Fill((*seg).localPosition().x()); 

             if(qual[iw][ist-1][iisect-1] > 4 ){
               stringstream hNamePosTrigHL;
               hNamePosTrigHL  << "hTrg_effnum_"  << Whname[iw] << "_S"<< iisect << "_MB" << ist ; 
               histo(hNamePosTrigHL.str())->Fill((*seg).localPosition().x()); 
             }
        }

//        if (abs(localPhi)< 0.36 )   { //  phi < 20 deg
        if (abs(localPhideg)< 30. )   { //  phi < 30 deg

//        ---- trigger efficiency analysis -----------
// set flag for trigger efficiency study: 1= use it (event triggered by other stations), 0= don't use it
          int MBeff = 0;  // don't use this station [ist,isec ]
          for (int sec1=1; sec1<15; ++sec1)       {
           for ( int ist1=1; ist1 < 5; ++ist1) { 
              if( ist1 != ist  || sec1 != iisect ) {
                if ( qual[iw][ist1-1][sec1-1] > 4 ) MBeff = 1; // event triggered also by other stations
                                                              // in the SAME Wheel; use this station
 	        }  
            } // next station
          } // next sector

          if( MBeff == 1) { // event triggered by other stations
            float phiglobal =  glbPoint.phi(); // phi position of reco segments
	      if (phiHits.size()>=7) {  // HH & HL potential candidates
              stringstream hTitlePhiGlob;
              hTitlePhiGlob << "hPhiGlob_" << Whname[iw] << "_MB"  << ist;
              stringstream hTitlePhiTrigg;
              hTitlePhiTrigg << "hPhiTrigg_"<< Whname[iw] << "_MB"  << ist;
              histo(hTitlePhiGlob.str())->Fill( phiglobal*radtodeg  ); // *** histos: hPhiGlob_MB1, ecc... **********
              if( qual[iw][ist-1][iisect-1] > 4) histo(hTitlePhiTrigg.str())->Fill( phiglobal*radtodeg  ); // *** hPhiTrigg_MB1, ...
	      }
	    }
//       end trigger efficiency analysis ------------
	// prepare vectors for re-fitting
         //float xfit[12], yfit [12];  // Not being used and in 62X gives erors for being set but not used
         //float sfit[12]; // flag (-1 or +1) for left/right semicell, input to fitline_t0 function   // Not being used and in 62X gives erors for being set but not used
          DTSuperLayerId slid1(phiSeg->chamberId(),1);
          /// Mean timer analysis
          DTMeanTimer meanTimer1(dtGeom->superLayer(slid1), phiHits, eventSetup, theSync);
          vector<double> tMaxs1=meanTimer1.run();	
//        refit: prepare the input vectors	  
          DTChamberId chId = phiSeg->chamberId();
          const DTChamber* chamb = dtGeom->chamber(chId);
          int nhitfit = 0;  // nr. of hits in the re-fit
	    float tmax123[] = {0.,0.,0.,0.};
          for (int isl=1; isl<4; isl=isl+2) {  // loop on SL 1 & 3
            for (int il=1; il<5; il++) {        // loop on layers
              DTLayerId layId = DTLayerId(chId,isl,il);
              const DTLayer* lay = chamb->layer(layId);  
              GlobalPoint laypos =  lay->position();   
              LocalPoint laylocal = chamb->toLocal(laypos);
              double xextr = phiSeg->localPosition().x() +   // segment extrap. to this layer
     	                   ( phiSeg->localDirection().x()/phiSeg->localDirection().z() ) * laylocal.z();		     
              std::vector< DTRecHit1D > specificHits =  phiSeg->specificRecHits();
              for (unsigned int sphit = 0; sphit <  specificHits.size(); ++sphit){  // loop on segment hits
               if ((specificHits[sphit]).wireId().layerId().superlayerId().superLayer() == isl &&
                  (specificHits[sphit]).wireId().layer() == il ) {
                 float xhit = (specificHits[sphit]).localPosition().x() + laylocal.x() ; // localPosition is in the layer (not in the cell)
                 DTWireId wireId = (specificHits[sphit]).wireId();
                 float ttrig = theSync->offset(wireId);
	         //int ill = il;  // Not being used and in 62X gives erors for being set but not used
	         //if ( isl > 1) ill = il + 4;  // Not being used and in 62X gives erors for being set but not used
	         if (il == 1 || il == 3 ) tmax123[isl] = tmax123[isl] + 0.5*( (specificHits[sphit]).digiTime() - ttrig );
                 if (il == 2)             tmax123[isl] = tmax123[isl] + (specificHits[sphit]).digiTime() - ttrig;
	         //xfit[nhitfit] = laylocal.z(); // input to fitline function  // Not being used and in 62X gives erors for being set but not used
	         //yfit[nhitfit] = xhit;         // input to fitline function  // Not being used and in 62X gives erors for being set but not used
               //sfit[nhitfit] = 1.;         // mark left/right semi-cell (1=Right) input to fitline_t0 function )  // Not being used and in 62X gives erors for being set but not used
               //if( (specificHits[sphit]).lrSide() == 2 ) sfit[nhitfit] = -1.; // -1 = Left  // Not being used and in 62X gives erors for being set but not used
	         nhitfit++; 
// ============== histograms of residuals ======================
  	         stringstream hTitle;
                 hTitle << "hResX_"  << Whname[iw] << "_S"  << isect << "_MB" << ist ;
                 histo(hTitle.str())->Fill( xhit-xextr); // *** histos: hResX_S1_MB1, ecc... **********		    
// ==============================================================
	       }  // endif hitlayer == layer 
             } // end loop on hits
           } // end loop on layers	      
         } // end loop on SL

// ======= tmax plots =======================================
          stringstream hTitle1, hTitle2, hTitle3;
          hTitle1 << "htmax_"  << Whname[iw] << "_S"  << isect << "_MB" << ist << "_SL1";
          histo(hTitle1.str())->Fill( tmax123[1]);
          hTitle2 << "htmax_"  << Whname[iw] << "_S"<< isect << "_MB" << ist << "_SL3";  
          histo(hTitle2.str())->Fill( tmax123[3]);
// ===========================================================
	} // endif abs(phiLocal) < 35 deg	  
	} // endif phiHts.size() >= 6

        //Time of associated hits
        //cout << " Hits Wh" << iw-2 << " Sector "<<  iisect << " MB " << ist << endl; 
        std::vector<DTRecHit1D> ListTheRecHits=phiSeg->specificRecHits();
        vector<DTRecHit1D>::iterator TheRecHitAdd;
        for (TheRecHitAdd = ListTheRecHits.begin(); TheRecHitAdd != ListTheRecHits.end();
                            ++TheRecHitAdd)
        {
            DTRecHit1D  TheRecHit =*TheRecHitAdd;
            DTWireId wireId = TheRecHit.wireId();
            int id_sl=wireId.superlayer();
            int Layer=wireId.layer();
            //int Wire=wireId.wire();  // Not being used and in 62X gives erors for being set but not used
            float TDCtime=TheRecHit.digiTime();
            float ttrig = theSync->offset(wireId);
            float ltime = TDCtime - ttrig ; // plot the TDC times ttrigg-subtracted....
            //cout << "SL " << id_sl << " L " << Layer << " C " << Wire << "  Time " << ltime << " ... " << TDCtime << "  " << endl;  

  	       stringstream hTitle;
             hTitle << "SegTimeBox_"  << Whname[iw] << "_S"  << iisect << "_MB" << ist << "_SL"<< id_sl << "_L" << Layer;
             histo(hTitle.str())->Fill(ltime); 

  	       stringstream hTitleSL;
             hTitleSL << "SegTimeBox_"  << Whname[iw] << "_S"  << iisect << "_MB" << ist << "_SL"<< id_sl;
             histo(hTitleSL.str())->Fill(ltime); 

  	       stringstream hTitleMB;
             hTitleMB << "SegTimeBox_"  << Whname[iw] << "_S"  << iisect << "_MB" << ist ;
             histo(hTitleMB.str())->Fill(ltime); 
        }


      } // endif phiseg ---------------------------

      // zed segment
      const DTSLRecSegment2D* zedSeg =(*seg).zSegment();
      //cout << "zedSeg " << zedSeg << endl;
      vector<DTRecHit1D> zedHits;
      if (zedSeg) {
        zedHits = zedSeg->specificRecHits();
        if(debug) cout << " Nhits in z-segment " << zedHits.size() << endl;
        NtkHit = NtkHit + zedHits.size();

        //Time of associated hits

        //cout << " Hits Wh" << iw-2 << " Sector "<<  iisect << " MB " << ist << endl; 
        DTSuperLayerId  SLId=zedSeg->superLayerId();
        int id_sl=SLId.superlayer();
        std::vector<DTRecHit1D> ListTheRecHits=zedSeg->specificRecHits();
        vector<DTRecHit1D>::iterator TheRecHitAdd;
        for (TheRecHitAdd = ListTheRecHits.begin(); TheRecHitAdd != ListTheRecHits.end();
                            ++TheRecHitAdd)
        {
            DTRecHit1D  TheRecHit =*TheRecHitAdd;
            DTWireId wireId = TheRecHit.wireId();
            int Layer=wireId.layer();
            //int Wire=wireId.wire();  // Not being used and in 62X gives erors for being set but not used
            float TDCtime=TheRecHit.digiTime();
            float ttrig = theSync->offset(wireId);
            float ltime = TDCtime - ttrig ; // plot the TDC times ttrigg-subtracted....
            //cout << "SL " << id_sl << " L " << Layer << " C " << Wire << "  Time " << ltime << " ... " << TDCtime << "  " << endl;  

  	       stringstream hTitle;
             hTitle << "SegTimeBox_"  << Whname[iw] << "_S"  << iisect << "_MB" << ist << "_SL"<< id_sl << "_L" << Layer;
             histo(hTitle.str())->Fill(ltime); 

  	       stringstream hTitleSL;
             hTitleSL << "SegTimeBox_"  << Whname[iw] << "_S"  << iisect << "_MB" << ist << "_SL"<< id_sl;
             histo(hTitleSL.str())->Fill(ltime); 

  	       stringstream hTitleMB;
             hTitleMB << "SegTimeBox_"  << Whname[iw] << "_S"  << iisect << "_MB" << ist ;
             histo(hTitleMB.str())->Fill(ltime); 
        }
      } // endif zedSeg


// ==== fill  hit multiplicity histos per sector ===============
      stringstream hTitle;
      hTitle << "hNhits_"  << Whname[iw] << "_S"  << isect << "_MB" << ist ;
      histo(hTitle.str())->Fill( NtkHit ); // hNhits_S1_MB1, ....ecc
	  
      if (phiSeg && zedSeg) nSegSect[iw][isect]++;

           
    } // end loop 4D segment in chamber ========================
   } // end if(doWheel[iw])

  } // end loop on all chambers =========================

  histo("hnHSegDT")->Fill(float(NsegmH));
  histo("hnSegMB1")->Fill(float(NsMB1));
  histo("hnHSegMB1")->Fill(float(NsHMB1));

  for (int iph4=0; iph4<N4; iph4++) { 
    for (int iph1=0; iph1<N1; iph1++) {

      if (where1[iph1][0]<where4[iph4][0]+2 && where1[iph1][0]>where4[iph4][0]-2 &&
          where1[iph1][1]<where4[iph4][1]+2 && where1[iph1][1]>where4[iph4][1]-2  ) {
	    if (where4[iph4][1]<7 && where4[iph4][1]>1) histo("DifPhi4_1_top")->Fill(phi4[iph4]-phi1[iph1]); 
	    else if (where4[iph4][1]>7) histo("DifPhi4_1_bot")->Fill(phi4[iph4]-phi1[iph1]); 
            histo("DifPhi4_1")->Fill(phi4[iph4]-phi1[iph1]);            
      }
    }
  }  


// ==== fill segment multiplicity histos per sector ===============
  for (int iw=0; iw<5; iw++)   // Wheels -2 (0) to  2 (4)
  {
   if(doWheel[iw])
   {
    for (int sec=1; sec<=12; ++sec) { // section 1 to 12
         stringstream hTitle;
          hTitle << "hNsegs_"  << Whname[iw] << "_S" << sec;
         if( nSegSect[sec] > 0 )  histo(hTitle.str())->Fill( nSegSect[iw][sec]); // hNsegs_Sect1, ....ecc
    }
   }
  }
// ================================================================ 

} // end DTsegments analyzer =============================================

  
// ==========================================================================================================
// StanAlone Track muon analysis
void DTOfflineAnalyzer::analyzeSATrack(const Event & event,
                                const EventSetup& eventSetup){
// ==========================================================================================================

  if (debug) cout << " analyzeSATracks : ------------------------------------------" << endl;
  char Whname[5][20]={"Wm2","Wm1","W0","W1","W2"};

  MuonPatternRecoDumper muonDumper;

  // Get the DT Geometry
  ESHandle<DTGeometry> dtGeom;
  eventSetup.get<MuonGeometryRecord>().get(dtGeom);
//  const std::vector<DTChamber*> & chs = dtGeom->chambers();

  // Get the 4D rechit collection from the event -------------------
  edm::Handle<DTRecSegment4DCollection> segs;
  event.getByLabel(theRecHits4DLabel, segs);

  // Get the 1D rechits from the event --------------
  Handle<DTRecHitCollection> dtRecHits; 
  event.getByLabel(theRecHits1DLabel, dtRecHits);

  // Get the RecTrack collection from the event
  Handle<reco::TrackCollection> staTracks;
  event.getByLabel(theSTAMuonLabel, staTracks);

  ESHandle<MagneticField> theMGField;
  eventSetup.get<IdealMagneticFieldRecord>().get(theMGField);

  ESHandle<GlobalTrackingGeometry> theTrackingGeometry;
  eventSetup.get<GlobalTrackingGeometryRecord>().get(theTrackingGeometry);


  reco::TrackCollection::const_iterator staTrack;

  double recPt=0.;
  histo("hNSA")->Fill(staTracks->size());
  histo2d("hNSAVsNHits")->Fill(dtRecHits->size(),staTracks->size());
  histo2d("hNSAVsNSegs4D")->Fill(segs->size(),staTracks->size());

  if (debug && staTracks->size() ) 
    cout << endl<<"Run/Event " << event.id().run() << ":" << event.id().event() << 
      " SA tracks " << staTracks->size() << endl;

// ********* loop on SA tracks ************************************************

  for (staTrack = staTracks->begin(); staTrack != staTracks->end(); ++staTrack){
    reco::TransientTrack track(*staTrack,&*theMGField,theTrackingGeometry); 

    if (debug) {
      cout << muonDumper.dumpFTS(track.impactPointTSCP().theState());

      recPt = track.impactPointTSCP().momentum().perp(); 
      cout<<" p: "<<track.impactPointTSCP().momentum().mag()<< " pT: "<<recPt<<endl;
      cout<<" normalized chi2: "<<track.normalizedChi2()<<endl;
    }


    if (debug) cout<<" Associated RecHits:"<<endl;

    trackingRecHit_iterator rhbegin = staTrack->recHitsBegin();
    trackingRecHit_iterator rhend = staTrack->recHitsEnd();

//  loop on associated rechits ----------------------------------------------------------
    int NHass = 0;
    int sect = 0;
    int iw=0;
    for(trackingRecHit_iterator recHit = rhbegin; recHit != rhend; ++recHit){
      const GeomDet* geomDet = theTrackingGeometry->idToDet((*recHit)->geographicalId());
      GlobalPoint gpos=geomDet->toGlobal((*recHit)->localPosition());

     DetId theDetector=(*recHit)->geographicalId();
     if (theDetector.det() == 2 && theDetector.subdetId() == 1) // MUON && DT 
     {
      NHass++;
      DTWireId wireId ;
      if ( const DTRecHit1D* dthit = dynamic_cast< const DTRecHit1D*> ((*recHit)->clone()) ) {
       wireId = dthit ->wireId();
     }
      if (NHass == 1 || sect==0) sect = wireId.sector(); // SomeTimes problems with hits, to recover if first is bad 
      if (NHass == 1 || iw==-1) iw = 2+wireId.wheel(); // SomeTimes problems with hits, to recover if first is bad 
      if (debug)  cout<< wireId << " r: "<< gpos.perp() <<" x,y,z: "<< gpos.x() << " " << gpos.y() << " " << gpos.z() << " " << gpos.phi() << endl;
      histo2d("hHitsPosXYSA")->Fill(gpos.x(),gpos.y());
      histo2d("hHitsPosXYSA_1")->Fill(gpos.x(),gpos.y());
      histo2d("hHitsPosXYSA_2")->Fill(gpos.x(),gpos.y());
      histo2d("hHitsPosXYSA_3")->Fill(gpos.x(),gpos.y());
      histo2d("hHitsPosXYSA_4")->Fill(gpos.x(),gpos.y());
      histo2d("hHitsPosXZSA")->Fill(gpos.z(),gpos.x());
      histo2d("hHitsPosYZSA")->Fill(gpos.z(),gpos.y());
      if(doWheel[2+wireId.wheel()])
      {
         stringstream htit1, htit2, htit3, htit4, htit5, htit6, htit7;
         htit1 << "hHitsPosXYSA_"  << Whname[iw] ; histo2d(htit1.str())->Fill(gpos.x(),gpos.y());
         htit2 << "hHitsPosXYSA_1_"<< Whname[iw] ; histo2d(htit2.str())->Fill(gpos.x(),gpos.y());
         htit3 << "hHitsPosXYSA_2_"<< Whname[iw] ; histo2d(htit3.str())->Fill(gpos.x(),gpos.y());
         htit4 << "hHitsPosXYSA_3_"<< Whname[iw] ; histo2d(htit4.str())->Fill(gpos.x(),gpos.y());
         htit5 << "hHitsPosXYSA_4_"<< Whname[iw] ; histo2d(htit5.str())->Fill(gpos.x(),gpos.y());
         htit6 << "hHitsPosXZSA_"  << Whname[iw] ; histo2d(htit6.str())->Fill(gpos.z(),gpos.x());
         htit7 << "hHitsPosYZSA_"  << Whname[iw] ; histo2d(htit7.str())->Fill(gpos.z(),gpos.y());
      }
      float radtodeg = 57.296 ;
      float phi =  gpos.phi();
      stringstream hTitlePhihit;
      hTitlePhihit << "hPhiHit_" << Whname[iw] << "_MB"  << wireId.station() ;
      if(doWheel[iw])if(wireId.superlayer() != 2) histo(hTitlePhihit.str())->Fill( radtodeg*phi); // hPhiHit_MB1, ....ecc                 
     }// if Rechit = MUON && DT
    } // next associated rechit --------------------------------
  
// ==== fill ass hit multiplicity histos per sector ===============
    if(NHass>0 && iw>-1) // Only Fill Tracks with DT Hits and containing hits with wire info
    {
     stringstream hTitle;
     hTitle << "hNhass_"  << Whname[iw] << "_S" << sect  ;
     if(doWheel[iw])histo(hTitle.str())->Fill( NHass); // hNhass_S1_MB1, ....ecc

       double radius = 0;
       double posz = 0;
       if(track.impactPointTSCP().isValid())
       {
         double posx = track.impactPointTSCP().position().x();
         double posy = track.impactPointTSCP().position().y();
         posz = track.impactPointTSCP().position().z();
         radius = sqrt( posx*posx + posy*posy );
       }
       
//     total hits in STA
       histo("hNhitsSA")->Fill(staTrack->recHitsSize());
       histo2d("hNHitsSAVsNHits")->Fill(dtRecHits->size(),staTrack->recHitsSize());
       histo2d("hNHitsSAVsNSegs4D")->Fill(segs->size(),staTrack->recHitsSize());
       
//     chi2...
       histo("hChi2SA")->Fill(track.normalizedChi2());
       
//      plots at Impact Point
       if(track.impactPointTSCP().isValid())
       {
       histo("hPIPSA")->Fill(track.impactPointTSCP().momentum().mag());
       histo("hPtIPSA")->Fill(recPt);
       histo("hPhiIPSA")->Fill(track.impactPointTSCP().momentum().phi());
       histo("hEtaIPSA")->Fill(track.impactPointTSCP().momentum().eta());
       histo("hrIPSA")->Fill(radius);
       histo("hzIPSA")->Fill(posz);
       histo2d("hrVszIPSA")->Fill(posz,radius);
       }
       //else
       //  cout << "[DTOfflineAnalyzer]track.impactPointTSCP() not valid!!! Skiping the fill of histograms Ev:"
       //       << event.id().event() << endl;
       
       TrajectoryStateOnSurface innerTSOS = track.innermostMeasurementState();
       if (debug) {
         cout << "Inner TSOS:"<<endl;
         cout << muonDumper.dumpTSOS(innerTSOS);
         cout<<" p: "<<innerTSOS.globalMomentum().mag()<< " pT: "<<innerTSOS.globalMomentum().perp()<<endl;
       }
       
       histo("hPInnerTSOSSA")->Fill(innerTSOS.globalMomentum().mag());
       histo("hPtInnerTSOSSA")->Fill(innerTSOS.globalMomentum().perp());
       histo("hPhiInnerTSOSSA")->Fill(innerTSOS.globalMomentum().phi());
       histo("hEtaInnerTSOSSA")->Fill(innerTSOS.globalMomentum().eta());
       
       histo("hInnerRSA")->Fill(sqrt(staTrack->innerPosition().perp2()));
       histo("hOuterRSA")->Fill(sqrt(staTrack->outerPosition().perp2()));
       histo2d("hInnerOuterRSA")->Fill(sqrt(staTrack->innerPosition().perp2()),
                                       sqrt(staTrack->outerPosition().perp2()));


//   ---- start extrapolation analysis ------------------
      // try to extrapolate using thePropagator ------
     if (!thePropagator){
       ESHandle<Propagator> prop;
       eventSetup.get<TrackingComponentsRecord>().get(thePropagatorName, prop);
       thePropagator = prop->clone();
       thePropagator->setPropagationDirection(anyDirection);
     }
     
      float radtodeg = 57.296 ;
      // Get a surface (here a cylinder of radius 1290mm) : ECAL
      float radiusECAL = 129.0; // radius in centimeter
      Cylinder::PositionType pos0;
      Cylinder::RotationType rot0;
      const Cylinder::CylinderPointer ecal = Cylinder::build(pos0, rot0,radiusECAL);
      TrajectoryStateOnSurface tsosAtEcal =
        thePropagator->propagate(*innerTSOS.freeState(), *ecal);
      if (tsosAtEcal.isValid()) {
        float phiEcal = -radtodeg*acos(tsosAtEcal.globalPosition().x()/tsosAtEcal.globalPosition().perp());
        float zEcal = tsosAtEcal.globalPosition().z();
          if (abs(zEcal) < 290. ) histo2d("hphivszECAL")->Fill(zEcal,phiEcal);
        }
//      else 
//        cout << "Extrapolation to ECAL failed" << endl;
     
      // Get a surface (here a cylinder of radius 1811 mm): HCAL
      float radiusHCAL = 181.1; // radius in centimeter
      const Cylinder::CylinderPointer hcal = Cylinder::build(pos0, rot0,radiusHCAL);
      TrajectoryStateOnSurface tsosAtHcal =
        thePropagator->propagate(*innerTSOS.freeState(), *hcal);
      if (tsosAtHcal.isValid()) {
//        cout << "extrap to HCAL : " << tsosAtHcal.globalPosition() << " r " <<
//          tsosAtHcal.globalPosition().perp() << endl;
        float phiHcal = -radtodeg*acos(tsosAtHcal.globalPosition().x()/tsosAtHcal.globalPosition().perp());
        float zHcal = tsosAtHcal.globalPosition().z();
          if (abs(zHcal) < 390. ) histo2d("hphivszHCAL")->Fill(zHcal,phiHcal);
         }
//      else 
//        cout << "Extrapolation to HCAL failed" << endl;
//   --- end extraploation analysis -------------------------
    }
    else
     if (debug)cout << " [DTOfflineAnalyzer]: Track has not DT Triggers"  << endl;

        
  } // next SA track ============================================
  
  if (debug) cout<<"---  end event ------------------------------"<<endl;  
}

// ==========================================================================================================
// trigger analysis
void DTOfflineAnalyzer::analyzeTrigger(const Event & event,
                                const EventSetup& eventSetup){
// ==========================================================================================================
  char Whname[5][20]={"Wm2","Wm1","W0","W1","W2"};

  if (debug) cout << " analyzeTrigger : ------------------------------------------" << endl;


  // Get the DT Geometry
  ESHandle<DTGeometry> dtGeom;
  eventSetup.get<MuonGeometryRecord>().get(dtGeom);
//  const std::vector<DTChamber*> & chs = dtGeom->chambers();

  // get the DT local trigger collection =======================
  edm::Handle<DTLocalTriggerCollection> allLocalTriggers;
  event.getByLabel(theDTLocalTriggerLabel, allLocalTriggers); 

  bool hasTr[5][12][4];
  for (int iw=0;iw<5;iw++) 
    for (int ise=0;ise<12;ise++) 
      for(int ist=0;ist<4;ist++) hasTr[iw][ise][ist]=false;
  //bool SecthasTr[]={false,false,false,false,false,false,false,false,false,false,false,false};
  bool SecthasTr[5][12]={{false,false,false,false,false,false,false,false,false,false,false,false}
                        ,{false,false,false,false,false,false,false,false,false,false,false,false}
                        ,{false,false,false,false,false,false,false,false,false,false,false,false}
                        ,{false,false,false,false,false,false,false,false,false,false,false,false}
                        ,{false,false,false,false,false,false,false,false,false,false,false,false}};

  int SCsect=0; int SCst=0;


  //int bx[5][4][5];  // Not being used and in 62X gives erors for being set but not used 
  float bxbest[5][4][14];
//  float qual[]={-1,-1,-1,-1};  
  int qual[5][4][14];
 for (int iw=0; iw<5; iw++)   // Wheel -2 (0) to 2 (5)
  for (int sec=1; sec<15; ++sec)   // section 1 to 14
    for (int ist=0; ist<4; ++ist) { 
      qual[iw][ist][sec-1] = -1;
      bxbest[iw][ist][sec-1] = -1;
    }    
    
  
  DTLocalTriggerCollection::DigiRangeIterator chambIt;

  for (chambIt=allLocalTriggers->begin();chambIt!=allLocalTriggers->end();++chambIt){ // loop on chambers ------

   const DTChamberId& id = (*chambIt).first;
   SCst=id.station();
   SCsect=id.sector();
   int iw=2+id.wheel();

   if(doWheel[iw])
   {
    //bx[iw][SCst-1][0]=0;     bx[iw][SCst-1][1]=0;  // Not being used and in 62X gives erors for being set but not used

    int countsec=-1;
    for (int ns=0; ns<12; ns++) {
     if (SCsect == sects[iw][ns] ) {
       countsec=ns;
       break;
     }
     else if (sects[iw][ns]==0) {
      sects[iw][ns]=SCsect;
      countsec=ns;
      break;
     }
    }

    int ntrCh=0;

    const DTLocalTriggerCollection::Range& range = (*chambIt).second;

  
   // Loop over triggers of this chamber -----------------------------------------------
    for (DTLocalTriggerCollection::const_iterator trigtrack = range.first;trigtrack!=range.second;++trigtrack){
       //if (trigtrack->quality()<7 && trigtrack->quality()>1) {
       if (trigtrack->quality()<7) {
       SecthasTr[iw][countsec]=true;    
       hasTr[iw][SCsect-1][SCst-1]=true;
      }
      if (trigtrack->quality()<7) {
       //bx[iw][SCst-1][ntrCh]=trigtrack->bx();  // dice a che bx c'e' stato trigger    // Not being used and in 62X gives erors for being set but not used
       float ibx=trigtrack->bx();
       ntrCh++; 
       if (ntrCh>4) break;
       int iQual=trigtrack->quality();
       if (SCst==4) histo("TriggerQualityMB4")->Fill(iQual);
       else histo("TriggerQuality")->Fill(iQual);


        if( iQual > qual[iw][SCst-1][SCsect-1] ) {
	   qual[iw][SCst-1][SCsect-1]= iQual;  // store the quality for this station
	   bxbest[iw][SCst-1][SCsect-1] = ibx;
	  } 
      } //  endif quality <7 
    } // end loop on triggers in this chamber --------------------------

//    plot the highest quality phi-trigger
      stringstream hTitleTrigg; 
      hTitleTrigg << "hTrigBits_"  << Whname[iw] << "_S" << SCsect << "_MB" << SCst ; 
      if(SCsect != 0) histo(hTitleTrigg.str())->Fill( qual[iw][SCst-1][SCsect-1] ); // *** histos: hTrigBits_S1_MB1, ecc... **********
//    plot the BXid of highest quality
      int iqual = qual[iw][SCst-1][SCsect-1];
      if(iqual < 4) iqual = 1; // flag for all uncorrelated phi trigger
      stringstream hTitleTriggBX; 
      hTitleTriggBX << "hTrigBX_"  << Whname[iw] << "_S"  << SCsect << "_MB" << SCst  << "_qual" << iqual;
      if(SCsect != 0) histo(hTitleTriggBX.str())->Fill( bxbest[iw][SCst-1][SCsect-1] ); // *** histos: hTrigBX_S1_MB1_qual1, ecc... **********

   }// end doWheel
  } // end loop on chambers ----------------------------------------------

  // Now let's Fill summary plots !

 for(int iw=0;iw<5;iw++)
 {
 if(doWheel[iw])
 {
  int SectrigMFill=0;
  if (sects[iw][4]) SectrigMFill=1;

  if (SecthasTr[iw][0] && !SecthasTr[iw][1] && !SecthasTr[iw][2] && !SecthasTr[iw][3] ) SectrigMFill = 3;
  if (!SecthasTr[iw][0] && SecthasTr[iw][1] && !SecthasTr[iw][2] && !SecthasTr[iw][3] ) SectrigMFill = 4;
  if (!SecthasTr[iw][0] && !SecthasTr[iw][1] && SecthasTr[iw][2] && !SecthasTr[iw][3] ) SectrigMFill = 5;
  if (!SecthasTr[iw][0] && !SecthasTr[iw][1] && !SecthasTr[iw][2] && SecthasTr[iw][3] ) SectrigMFill = 6;


  if (SecthasTr[iw][0] && SecthasTr[iw][1] && !SecthasTr[iw][2] && !SecthasTr[iw][3] ) SectrigMFill = 8;
  if (SecthasTr[iw][0] && !SecthasTr[iw][1] && SecthasTr[iw][2] && !SecthasTr[iw][3] ) SectrigMFill = 9;
  if (SecthasTr[iw][0] && !SecthasTr[iw][1] && !SecthasTr[iw][2] && SecthasTr[iw][3] ) SectrigMFill = 10;
  if (!SecthasTr[iw][0] && SecthasTr[iw][1] && SecthasTr[iw][2] && !SecthasTr[iw][3] ) SectrigMFill = 11;
  if (!SecthasTr[iw][0] && SecthasTr[iw][1] && !SecthasTr[iw][2] && SecthasTr[iw][3] ) SectrigMFill = 12;
  if (!SecthasTr[iw][0] && !SecthasTr[iw][1] && SecthasTr[iw][2] && SecthasTr[iw][3] ) SectrigMFill = 13;

  if (SecthasTr[iw][0] && SecthasTr[iw][1] && SecthasTr[iw][2] && !SecthasTr[iw][3] ) SectrigMFill = 15;
  if (SecthasTr[iw][0] && SecthasTr[iw][1] && !SecthasTr[iw][2] && SecthasTr[iw][3] ) SectrigMFill = 16;
  if (SecthasTr[iw][0] && !SecthasTr[iw][1] && SecthasTr[iw][2] && SecthasTr[iw][3] ) SectrigMFill = 17;
  if (!SecthasTr[iw][0] && SecthasTr[iw][1] && SecthasTr[iw][2] && SecthasTr[iw][3] ) SectrigMFill = 18;

  if (SecthasTr[iw][0] && SecthasTr[iw][1] && SecthasTr[iw][2] && SecthasTr[iw][3] ) SectrigMFill = 20;

  stringstream hname;
  hname << "SectorTriggerMatrix" << Whname[iw]  ;
  histo(hname.str())->Fill(SectrigMFill);

  for (int ns=0; ns<12; ns++) {

   int sector=sects[iw][ns];

   if (!sector) continue;

   if (SecthasTr[iw][ns]){

     
   for (int ist=0; ist<4; ist++){
     stringstream hname2;
     hname2 << "TriggerInclusive" << Whname[iw]  ;
     if (hasTr[iw][sector-1][ist]) histo(hname2.str())->Fill((sector-1)*5+ist+1);
    }

 
    int trigMFill=0;

    if (hasTr[iw][sector-1][0] && !hasTr[iw][sector-1][1] && !hasTr[iw][sector-1][2] && !hasTr[iw][sector-1][3]) trigMFill = 2;
    if (!hasTr[iw][sector-1][0] && hasTr[iw][sector-1][1] && !hasTr[iw][sector-1][2] && !hasTr[iw][sector-1][3]) trigMFill = 3;
    if (!hasTr[iw][sector-1][0] && !hasTr[iw][sector-1][1] && hasTr[iw][sector-1][2] && !hasTr[iw][sector-1][3]) trigMFill = 4;
    if (!hasTr[iw][sector-1][0] && !hasTr[iw][sector-1][1] && !hasTr[iw][sector-1][2] && hasTr[iw][sector-1][3]) trigMFill = 5;
    if (hasTr[iw][sector-1][0] && hasTr[iw][sector-1][1] && !hasTr[iw][sector-1][2] && !hasTr[iw][sector-1][3]) trigMFill = 7;
    if (hasTr[iw][sector-1][0] && !hasTr[iw][sector-1][1] && hasTr[iw][sector-1][2] && !hasTr[iw][sector-1][3]) trigMFill = 8;
    if (hasTr[iw][sector-1][0] && !hasTr[iw][sector-1][1] && !hasTr[iw][sector-1][2] && hasTr[iw][sector-1][3]) trigMFill = 9;
    if (!hasTr[iw][sector-1][0] && hasTr[iw][sector-1][1] && hasTr[iw][sector-1][2] && !hasTr[iw][sector-1][3]) trigMFill = 10;
    if (!hasTr[iw][sector-1][0] && hasTr[iw][sector-1][1] && !hasTr[iw][sector-1][2] && hasTr[iw][sector-1][3]) trigMFill = 11;
    if (!hasTr[iw][sector-1][0] && !hasTr[iw][sector-1][1] && hasTr[iw][sector-1][2] && hasTr[iw][sector-1][3]) trigMFill = 12;
    if (hasTr[iw][sector-1][0] && hasTr[iw][sector-1][1] && hasTr[iw][sector-1][2] && !hasTr[iw][sector-1][3]) trigMFill = 14;
    if (hasTr[iw][sector-1][0] && hasTr[iw][sector-1][1] && !hasTr[iw][sector-1][2] && hasTr[iw][sector-1][3]) trigMFill = 15;
    if (hasTr[iw][sector-1][0] && !hasTr[iw][sector-1][1] && hasTr[iw][sector-1][2] && hasTr[iw][sector-1][3]) trigMFill = 16;
    if (!hasTr[iw][sector-1][0] && hasTr[iw][sector-1][1] && hasTr[iw][sector-1][2] && hasTr[iw][sector-1][3]) trigMFill = 17;
    if (hasTr[iw][sector-1][0] && hasTr[iw][sector-1][1] && hasTr[iw][sector-1][2] && hasTr[iw][sector-1][3]) trigMFill = 19;

    stringstream hNameTrigMat; 
    hNameTrigMat << "TriggerMatrix"  << Whname[iw] << "_S" << sector ;
    histo(hNameTrigMat.str())->Fill(trigMFill);

   } // if the sector has trigger
  } // loop on sectors
  } // If doWheel      
 } // loop on wheels


}



//  utilities ###########################################

TH1F* DTOfflineAnalyzer::histo(const string& name) const{
  MonitorElement* me = theDQMStore->get(("DT/DTOfflineAnalyzer/"+name).c_str());
  if (!me) throw cms::Exception("DTOfflineAnalyzer") << " ME not existing " << name;
  TH1F* histo = me->getTH1F();
  if (!histo)cms::Exception("DTOfflineAnalyzer") << " Not a TH1F " << name;
  return histo;
}

TH2F* DTOfflineAnalyzer::histo2d(const string& name) const{
  MonitorElement* me = theDQMStore->get(("DT/DTOfflineAnalyzer/"+name).c_str());
  if (!me) throw cms::Exception("DTOfflineAnalyzer") << " ME not existing " << name;
  TH2F* histo = me->getTH2F();
  if (!histo)cms::Exception("DTOfflineAnalyzer") << " Not a TH2F " << name;
  return histo;
}

bool DTOfflineAnalyzer::getLCT(LCTType t) const {
  return LCT.test(t);
}

string DTOfflineAnalyzer::toString(const DTLayerId& id) const {
  stringstream result;
  result << "_Wh" << id.wheel() 
    << "_Sec" << id.sector() 
    << "_St" << id.station()
    << "_Sl" << id.superLayer()
    << "_Lay" << id.layer();
  return result.str();
}

string DTOfflineAnalyzer::toString(const DTSuperLayerId& id) const {
  stringstream result;
  result << "_Wh" << id.wheel() 
    << "_Sec" << id.sector() 
    << "_St" << id.station()
    << "_Sl" << id.superLayer();
  return result.str();
}

string DTOfflineAnalyzer::toString(const DTChamberId& id) const {
  stringstream result;
  result << "_Wh" << id.wheel() 
    << "_Sec" << id.sector() 
    << "_St" << id.station();
  return result.str();
}

template<class T> string DTOfflineAnalyzer::hName(const string& s, const T& id) const {
  string name(toString(id));
  stringstream hName;
  hName << s << name;
  return hName.str();
}

void DTOfflineAnalyzer::createTH1F(const std::string& name,
                            const std::string& title,
                            const std::string& suffix,
                            int nbin,
                            const double& binMin,
                            const double& binMax) const {
  stringstream hName;
  stringstream hTitle;
  hName << name << suffix;
  hTitle << title << suffix;
  theDQMStore->setCurrentFolder("DT/DTOfflineAnalyzer");
  theDQMStore->book1D(hName.str().c_str(), hTitle.str().c_str(), nbin,binMin,binMax);
  //cout << "pasa  ....." << endl;
  //TH1F * _h=new TH1F(hName.str().c_str(), hTitle.str().c_str(), nbin,binMin,binMax);
  //_h->SetDirectory(theFile); // Needed when the input is a root file
}

void DTOfflineAnalyzer::createTH2F(const std::string& name,
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
  theDQMStore->setCurrentFolder("DT/DTOfflineAnalyzer");
  theDQMStore->book2D(hName.str().c_str(), hTitle.str().c_str(), nBinX,binXMin,binXMax, nBinY,binYMin,binYMax);
  //TH2F * _h=new TH2F(hName.str().c_str(), hTitle.str().c_str(), nBinX,binXMin,binXMax, nBinY,binYMin,binYMax);
  //_h->SetDirectory(theFile); // Needed when the input is a root file
}

    
//  end utilities ...#######################################################   
