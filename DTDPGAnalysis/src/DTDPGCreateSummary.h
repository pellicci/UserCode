#ifndef DTDPGCreateSummary_H
#define DTDPGCreateSummary_H


/** \classDTDPGCreateSummary
 * *
 *  DQM Test Client
 *
 *  $Date: 2010/12/15 11:52:26 $
 *  $Revision: 1.4 $
 *  \author  G. Mila - INFN Torino
 *   
 */


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include "DataFormats/Common/interface/Handle.h"
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/MakerMacros.h>
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "FWCore/ServiceRegistry/interface/Service.h"


#include <string>

class DTGeometry;
class TCanvas;
class TFile;

class DTDPGCreateSummary: public edm::EDAnalyzer{

 public:

  /// Constructor
  DTDPGCreateSummary(const edm::ParameterSet& ps);
  
  /// Destructor
  virtual ~DTDPGCreateSummary();

 protected:

  /// BeginJob
  void beginJob();

  /// BeginRun    
  void beginRun(const edm::Run& r,const edm::EventSetup& c);

  /// Analyze
  void analyze(const edm::Event& e, const edm::EventSetup& c);

  /// Endjob
  void endJob();

  /// Create Trigger Plots
  void createTriggerPlots(int wh, int sec);

  /// Create Reco Plots
  void createRecoPlots(int wh, int sec);

  /// Create Digi Plots
  void createDigiPlots(int wh, int sec);

  /// Create Data Integrity Plots
  void createDataIntegrityPlots(int wh, int sec);

  /// Create Resolution Plots
  void createResoPlots(int wh, int sec);

  /// Create Efficiency Plots
  void createEfficiencyPlots(int wh, int sec);

  /// Create TestPulse Plots
  void createTestPulsePlots(int wh, int sec);

  /// Create and save the gif files
  void createGifFile(std::string fileName, int wh, int sec);

  /// get DDU number from wheel num
  inline int wheelToDDU(int wheel) { return 770+wheel+2; }

 private:

  TCanvas *myCanvas;
  std::string myMainFolder;
  edm::ESHandle<DTGeometry> myMuonGeom;

  edm::ParameterSet myParameters;

  TFile *myFile;
  int myRunNumber;

};

#endif
  
