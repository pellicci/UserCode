#ifndef CheckDeadChannels_H
#define CheckDeadChannels_H


/* class CheckDeadChannels 
 Oct. 13, 2011
 Francesca R. Cavallo 
 */

#include <FWCore/Framework/interface/EDAnalyzer.h>
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


class CheckDeadChannels: public edm::EDAnalyzer{

public:

  /// Constructor
  CheckDeadChannels(const edm::ParameterSet& ps);
  
  /// Destructor
  virtual ~CheckDeadChannels();

protected:

  /// BeginJob
  void beginJob();

  /// BeginRun
  void beginRun(const edm::Run& r, const edm::EventSetup& c);

  /// Analyze
  void analyze(const edm::Event& e, const edm::EventSetup& c);

  /// Endjob
  void endJob();

  std::ofstream* DeadComp;

 private:

  //  int nevents;
  std::string myMainFolder;

  edm::ParameterSet myParameters;


  // The run number
  int myRunNumber;
  int ReferenceRun;

};

#endif
  
  
