#ifndef DTOFFLINEANALYZER_H
#define DTOFFLINEANALYZER_H

/** \class DTOfflineAnalyzer
 *
 * Description:
 *  
 *  detailed description
 *
 * \author : Stefano Lacaprara - INFN Padova <stefano.lacaprara@pd.infn.it>
 * $date   : 20/11/2006 16:51:04 CET $
 *
 * Modification:
 *
 */

/* Base Class Headers */
#include "FWCore/Framework/interface/EDAnalyzer.h"
namespace edm {
  class ParameterSet;
  class Event;
  class EventSetup;
}

/* Collaborating Class Declarations */
#include "DataFormats/Common/interface/Handle.h"
class TFile;
class DQMStore;
class TH1F;
class TH2F;
class DTLayerId;
class DTSuperLayerId;
class DTChamberId;
class DTTTrigBaseSync;
class Propagator;

/* C++ Headers */
#include <iosfwd>
#include <bitset>

/* ====================================================================== */

/* Class DTOfflineAnalyzer Interface */

class DTOfflineAnalyzer : public edm::EDAnalyzer {

  public:

/* Constructor */ 
    DTOfflineAnalyzer(const edm::ParameterSet& pset) ;

/* Destructor */ 
    ~DTOfflineAnalyzer() ;

/* Operations */ 
    void analyze(const edm::Event & event, const edm::EventSetup& eventSetup);

  private:
    void analyzeDTHits(const edm::Event & event, const edm::EventSetup& eventSetup);
    void analyzeDTSegments(const edm::Event & event, const edm::EventSetup& eventSetup);
    void analyzeSATrack(const edm::Event & event, const edm::EventSetup& eventSetup);
    void analyzeTrigger(const edm::Event & event, const edm::EventSetup& eventSetup);
    void LabelTriggerMatrix();
    
    TH1F* histo(const std::string& name) const;
    TH2F* histo2d(const std::string& name) const;

    void createTH1F(const std::string& name,
                    const std::string& title,
                    const std::string& suffix,
                    int nbin, const double& binMin, const double& binMax) const;

    void createTH2F(const std::string& name,
                    const std::string& title,
                    const std::string& suffix,
                    int nBinX,
                    const double& binXMin,
                    const double& binXMax,
                    int nBinY,
                    const double& binYMin,
                    const double& binYMax) const ;

    enum LCTType { DT, CSC, RPC_W1, RPC_W2 };
    bool getLCT(LCTType) const;
    bool selectEvent() const ;

    std::string toString(const DTLayerId& id) const;
    std::string toString(const DTSuperLayerId& id) const;
    std::string toString(const DTChamberId& id) const;
    template<class T> std::string hName(const std::string& s, const T& id) const;
  private:
    bool LCT_RPC, LCT_DT, LCT_CSC;
    bool debug;
    int _ev;
    std::string theRootFileName;
    // TFile* theFile;
    DQMStore *theDQMStore;
    //static std::string theAlgoName;
    int sects[5][12];
    std::string theDTLocalTriggerLabel;
    std::string theRecHits4DLabel;
    std::string theRecHits2DLabel;     
    std::string theRecHits1DLabel;     
    std::string theSTAMuonLabel;
    std::string thePropagatorName;
 
    mutable Propagator* thePropagator;

    bool mc;

    bool doHits;
    bool doSegs;
    bool doSA;
    bool doTrig;
    bool doTBox;
    bool doTBoxWhm2;
    bool doTBoxWhm1;
    bool doTBoxWh0;
    bool doTBoxWh1;
    bool doTBoxWh2;

    bool doWheel[5];
    bool doTBoxWheel[5];
    int doTBoxSector; 
    int doTBoxChamber; 
    int doTBoxSuperLayer; 
    int doTBoxLayer; 
    
    bool init;
    std::bitset<6> LCT;

    DTTTrigBaseSync *theSync;

  protected:

};
#endif // DTOFFLINEANALYZER_H

