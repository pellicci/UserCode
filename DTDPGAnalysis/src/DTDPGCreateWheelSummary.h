#ifndef DTDPGCreateWheelSummary_H
#define DTDPGCreateWheelSummary_H


/** \class DTDPGCreateWheelSummary 
 * *
 *
 *  $Date: 2013/07/04 17:16:33 $
 *  \author M.C Fouz   
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


#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class DTGeometry;
class TCanvas;

class DTDPGCreateWheelSummary: public edm::EDAnalyzer{

public:

  /// Constructor
  DTDPGCreateWheelSummary(const edm::ParameterSet& ps);
  
  /// Destructor
  virtual ~DTDPGCreateWheelSummary();

protected:

  /// BeginJob
  void beginJob();

  /// BeginRun
  void beginRun(const edm::Run& r, const edm::EventSetup& c);

  /// Analyze
  void analyze(const edm::Event& e, const edm::EventSetup& c);

  /// Endjob
  void endJob();

  /// get DDU number from wheel num
  inline int wheelToDDU(int wheel) { return 770+wheel+2; }

  /// Create and save the gif files
  void createGifFile(std::string fileName,TCanvas *canvas, bool isExtraFile = false);

  /// Create and save the gif files (per wheel)
  void createGifFile(std::string fileName,TCanvas *canvas, int wh, bool isExtraFile = false);

  std::ofstream* DeadChannelList;

 private:

  //  int nevents;
  std::string myMainFolder;
  std::string myL1TFolder;

  edm::ParameterSet myParameters;
  edm::ESHandle<DTGeometry> myMuonGeom;

  // The file which contain the occupancy plot and the digi event plot
  TFile *myFile;
  
/*   // The DDUId */
/*   int DDUId[5]; */

  // The run number
  int myRunNumber;

  //histos summary
  std::map< std::string , MonitorElement* > RecoHistos; // CB x+ MEs e non Histos???


};

#endif
  
  
