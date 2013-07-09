
#ifndef DTDPGCreateAnalyzerSummary_H
#define DTDPGCreateAnalyzerSummary_H


/** \classDTDPGCreateAnalyzerSummary
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
#include <FWCore/Utilities/interface/Exception.h>

#include "DQMServices/Core/interface/DQMStore.h"
#include "FWCore/ServiceRegistry/interface/Service.h"


#include "TFile.h"
#include <iostream>
#include <string>

class DTGeometry;
class TCanvas;

class DTDPGCreateAnalyzerSummary: public edm::EDAnalyzer{

 public:

  /// Constructor
  DTDPGCreateAnalyzerSummary(const edm::ParameterSet& ps);
  
  /// Destructor
  virtual ~DTDPGCreateAnalyzerSummary();

 protected:

  /// BeginJob
  void beginJob();

  /// Analyze
  void analyze(const edm::Event& e, const edm::EventSetup& c);

  /// Endjob
  void endJob();

  /// Create Summary Plots
  void createSummaryPlots();

  /// Create SummaryWheel Plots
  void createSummaryWheelPlots();

  /// Create SummaryAll Plots
  void createSummaryAllPlots();

  /// Get the histos
  template <class T> T* getHisto(std::string name);
  template <class T> T* force_getHisto(std::string name);

  /// Create and save the gif files
  void createGifFile(std::string fileName, int wh, int sec, std::string tag, TCanvas *canvas, bool isExtraFile = false);

  /// Create and save the gif files
  void createGifFile(std::string fileName, int wh, std::string tag, TCanvas *canvas, bool isExtraFile = false);

  /// Create and save the gif files
  void createGifFile(std::string fileName, std::string tag, TCanvas *canvas, bool isExtraFile = false);

 private:

  std::string myMainFolder;
  edm::ParameterSet myParameters;
  TFile *myFile;
  int myRunNumber;
  std::map<int,std::vector<int> > mySectors;

};

#endif

template <class T>
T* DTDPGCreateAnalyzerSummary::getHisto(std::string name) {
  T* t = static_cast<T*>(myFile->Get((myMainFolder+name).c_str()));
  if(!t) {
//    throw cms::Exception("DTDPGCreateAnalyzerSummaryError")<< "[DTDPGCreateAnalyzerSummary]: Cannot get and convert histo " << name << " check for existence and correctness of the type" << std::endl;
   std::cout << "[DTDPGCreateAnalyzerSummary]: Cannot get and convert histo " << name << " check for existence and correctness of the type" << std::endl;
   return NULL;
  }
  return t;
}


template <class T>
T* DTDPGCreateAnalyzerSummary::force_getHisto(std::string name) {
  T* t = static_cast<T*>(myFile->Get((myMainFolder+name).c_str()));
  return t;
}

