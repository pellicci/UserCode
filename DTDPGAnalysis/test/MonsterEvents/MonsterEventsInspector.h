#ifndef MONSTEREVENTSINSPECTOR_H
#define MONSTEREVENTSINSPECTOR_H 1

/*
 *=========================================================================
 *
 * MAIN CLASS: MonsterEventsInspector
 * DESCRIPTION: Provides an interface to correlate the information on
 *              instantaneous luminosity stored in a root file and the 
 *              happening of monster events stored in a plain text file
 *  DEVELOPERS: Isidro Gonzalez Caballero (U. Oviedo)
 *  
 *     UPDATES: [WHEN] - [WHO] - [WHAT]
 *=========================================================================
 */



///////////////////////////////////////////////////////////////////////////
// INCLUDES
//
// + ROOT 
#include "TString.h"
#include "TTimeStamp.h"
#include "TFile.h"
#include "TBranch.h"
#include "TH1F.h"
#include "TTree.h"
//
// + C++ includes
#include <vector>



//-------------------------------------------------------------------------
// HELPER CLASSES
//
//
/////////////////////////////////////////////
//
// + Fill: Groups information on a given fill
//
class Fill {
public:
  Fill() {NFill = -1, start = -1; end = -1;}
  void Reset() {NFill = -1, start = -1; end = -1;}

  int   NFill;
  float start;
  float end;
};

//
/////////////////////////////////////////////
//
// + MonsterEvent: Group information about a monster event
//
class MonsterEvent {
public:
  MonsterEvent():EventTime(), InstLumi(-1), MinDeltaT(-1), IsInBeam(false){}
  ~MonsterEvent(){}

  TTimeStamp EventTime;
  Float_t    InstLumi;
  Float_t    MinDeltaT; //In seconds
  bool       IsInBeam;
};

std::ostream& operator<<(std::ostream& os, const MonsterEvent& me);

//
//-------------------------------------------------------------------------






//-------------------------------------------------------------------------
// MAIN CLASS
//
class MonsterEventsInspector {

public:
  MonsterEventsInspector(unsigned int debug = 0);
  ~MonsterEventsInspector();


  // This method reads the ROOT file with the instantaneous luminosity 
  // storing the starting and finishing time for each fill.
  TFile* ReadLumiFile(const char* lumiFileName = "DTLTuple_lumi.root", 
		      const char* treeName = "DT_lumi",
		      bool doChecks=true);

  // This method reads and stores monster events for a given wheel
  int ReadMonsterEvents(int wheel = 0);


  // Find the closest instant lumi (in a beam) at a given time dt and
  // store it in ME
  Float_t GetInstantLumi(const TTimeStamp& dt, MonsterEvent& ME);


  // Convert a time stamp to Ignacio's float
  float ConvertDateToFloat(const TTimeStamp& datetime) const;

  // Time difference between to time stamps in seconds
  time_t DeltaT(const TTimeStamp& d1, const TTimeStamp& d2) const {return d2.GetSec() - d1.GetSec();}

  // True if dt is in a fill, 
  // --> i.e. there was beam, 
  //     --> i.e. it is not in cosmics
  bool IsInBeam(const TTimeStamp& dt) const;


  // Setters
  void SetMEFileBaseName(const char* me) {fMEFileBaseName = me;}
  void SetDebug(unsigned int debug = 0) { fDebug = debug;}

  // Getters
  // + For histograms
  TH1F* GetLumi2010() const {return hCheckLumi2010;}
  TH1F* GetLumi2011() const {return hCheckLumi2011;}
  TH1F* GetLumi2012() const {return hCheckLumi2012;}

  // + For collections and elements in collections
  //   - This is not working very well because of ROOT
  vector<Fill>* GetTheFills() { return fTheFills;}
  //   - Get a Fill and the number of fills stored
  Fill GetFill(unsigned int i) { return fTheFills->at(i);}
  unsigned int GetNFills() const {return fTheFills->size();}
  //   - This is not working very well because of ROOT
  vector<MonsterEvent>* GetTheMonsterEvents() { return fTheMEs;}
  //   - Get a Monster Event and the number of Monster Events stored
  MonsterEvent GetMonsterEvent(unsigned int i) {return fTheMEs->at(i);}
  unsigned int GetNMonsterEvents() const {return fTheMEs->size();}





private:
  // Monster Event file base name
  TString fMEFileBaseName;

  // Debug level
  unsigned int fDebug;

  // A vector to store the fills
  vector<Fill>* fTheFills;

  // A vector to store the Monster Events
  vector<MonsterEvent>* fTheMEs;

  // Related to luminosity ntuples
  TFile*   fLumiFile; //The Luminosity file
  Float_t  fTime;     //Variable holding the time in ntuple for current event TIME
  Int_t    fFill;     //Variable holding the time in ntuple for current event FILL
  Float_t  fInstLumi; //Variable holding the instlumi in ntuple for current event INST_LUMI or CALC2_LUMI
  TBranch* bTime;     //Branch for time
  TBranch* bFill;     //Branch for fill
  TBranch* bInstLumi; //Branch for instant luminosity
  TTree*   fLumiTree; //The Tree in the lumi ntuple
  int fInitialEvent;  //Awfull hack to speed searches - Initially is the last entry before 17/05/2012


  // Histograms
  TH1F* hCheckLumi2010;  //Inst Lumi distribution in luminosity file for 2010
  TH1F* hCheckLumi2011;  //Inst Lumi distribution in luminosity file for 2011
  TH1F* hCheckLumi2012;  //Inst Lumi distribution in luminosity file after 17/05/2012
};

#endif
