#include "MonsterEventsInspector.h"

// ROOT includes
#include "TCanvas.h"

// C++ includes
#include <fstream>
#include <iostream>

using namespace std;


const int SECONDSINADAY = 86400;


MonsterEventsInspector:: MonsterEventsInspector(unsigned int debug):
  fMEFileBaseName("thresh_event_size_YB"),
  fDebug(debug),
  fLumiFile(0), fTime(-1), fInstLumi(-1),
  fInitialEvent(19816), //Awfull hack to speed searches
  hCheckLumi2010(0),hCheckLumi2011(0),hCheckLumi2012(0)

{
  fTheFills = new vector<Fill>;
  fTheMEs   = new vector<MonsterEvent>;
  
}

MonsterEventsInspector::~MonsterEventsInspector() {
  // The following code causes problems when quiting root

  /*
  if (fLumiFile)
    fLumiFile->Close();
  */
}




///////////////////////
// This method reads the ROOT file with the instantaneous luminosity 
// storing the starting and finishing time for each fill.
//
TFile* MonsterEventsInspector::ReadLumiFile(const char* lumiFileName,  
					    const char* treeName, 
					    bool doChecks) {

  //Open the file
  cout << ">> Opening luminosity file " << lumiFileName << endl;
  fLumiFile = TFile::Open(lumiFileName);
  
  //Check if everything went fine
  if (!fLumiFile) {
    cerr << "ERROR: Could not find " << lumiFileName << "!" << endl;
    cerr << "       Exiting!" << endl;
    return 0;
  }
  
  
  cout << "   + Looking for " << treeName << " tree..." << endl;
  fLumiTree = (TTree*) fLumiFile->Get(treeName);
  
  //Count entries in the file
  cout << "   + Found " << fLumiTree->GetEntries() << " entries" << endl;
  
  
  
  cout << "   + Setting branch addresses..." << endl;
  bTime = fLumiTree->GetBranch("TIME");
  bFill = fLumiTree->GetBranch("FILL");
  bInstLumi = fLumiTree->GetBranch("CALC2_LUMI");
  bTime->SetAddress(&fTime);
  bFill->SetAddress(&fFill);
  bInstLumi->SetAddress(&fInstLumi);
  
  if (doChecks) {
    cout << "   + Creating some histograms for checks" << endl;
    hCheckLumi2010 = new TH1F("hCheckLumi2010", "Instantaneous luminosity 2010", 150, 0, 150000);
    hCheckLumi2011 = new TH1F("hCheckLumi2011", "Instantaneous luminosity 2011 and to 17/05/2012", 150, 0, 150000);
    hCheckLumi2012 = new TH1F("hCheckLumi2012", "Instantaneous luminosity from 17/05/2012", 150, 0, 150000);
    
    Float_t ts2010 = ConvertDateToFloat(TTimeStamp(2010,01,01,00,00,00));
    Float_t ts2011 = ConvertDateToFloat(TTimeStamp(2011,01,01,00,00,00));
    Float_t ts2012 = ConvertDateToFloat(TTimeStamp(2012,05,17,00,00,00));
    
    
    // Loop on events
    cout << "   + Looping on events: 00000" << flush;
    Fill currentFill;
    Float_t previousTime = -1;
    Float_t previousFill = -1;
    
    for (unsigned int iread = 0; iread < fLumiTree->GetEntries(); iread++) {
      if (iread%100 == 0)
	cout << "\b\b\b\b\b" << Form("%05i", iread) << flush;
      fLumiTree->GetEvent(iread);

      
      // Fill luminosity plots
      if (fTime > ts2012)
	hCheckLumi2012->Fill(fInstLumi);
      else if (fTime > ts2011)
	hCheckLumi2011->Fill(fInstLumi);
      else if (fTime > ts2010)
	hCheckLumi2010->Fill(fInstLumi);
      

      //Check if we have a change in fill
      // - Yes: Check if we are moving from X to Y
      //        - 0 to X: New Fill
      //        - X to 0: End Fill -> Fill vector
      //        - X to Y: End previous fill -> Fill vector -> Start new fill
      // - No: Go on

      if (fFill != previousFill) {
	bool newfill = false;
	bool endfill = false;
	if (previousFill == 0) {
	  newfill = true;
	}
	else if (fFill == 0) {
	  endfill = true;
	}
	else {
	  newfill = true;
	  endfill = true;
	}

	if (endfill) {
	  if (fDebug > 0)
	    cout << "DEBUG: Ending fill " << currentFill.NFill << " for time " << previousTime << endl;
	  currentFill.end = previousTime;
	  fTheFills->push_back(currentFill);
	  currentFill.Reset();
	}
	if (newfill) {
	  if (fDebug > 0)
	    cout << "DEBUG: Starting fill " << fFill << " for time " << fTime << endl;
	  currentFill.NFill = fFill;
	  currentFill.start = fTime;
	}
      }
	  
      previousTime = fTime;
      previousFill = fFill;
    }
    
    cout << endl;
    
  } //if do checks
  
  return fLumiFile;
}





///////////////////////
// This method reads and stores monster events for a given wheel
//
int MonsterEventsInspector::ReadMonsterEvents(int wheel) {
  fTheMEs->clear();
  fInitialEvent = 19816;

  cout << ">> Loading wheel " << wheel << "..." << endl;


  //Construct monster events file name
  char wsign[2]="\0";
  if (wheel< 0)
    wsign[0] = 'm';
  else if (wheel> 0)
    wsign[0] = 'p';
  
  TString MEFileName = Form("%s%s%i.txt", fMEFileBaseName.Data(), wsign,TMath::Abs(wheel));
  
  
  // Go for the opening of the monster events file
  cout << "   + Monster Events file " << MEFileName << endl;

  cout << "   + Opening file..." << endl;
  ifstream is(MEFileName);

  if (!is) {
    cerr << "ERROR: Could not find " << MEFileName << "!" << endl;
    cerr << "       Exiting!" << endl;
    return 0;
  }

  // Read file
  cout << "   + Looping: 00000" << flush;
  unsigned int imonster = 0;
  TTimeStamp datetime0(2012, 12, 17, 00, 00, 00);
  while (is) {
    //for (unsigned int nread = 0; nread < 10; nread++) {
    imonster++;
    if (imonster%100 == 0) {
      cout << "\b\b\b\b\b" << Form("%05i",imonster) << flush;
    }



    // Read date and time
    int day    = -1;
    int month  = -1;
    int year   = -1;
    int hour   = -1;
    int minute = -1;
    int second = -1;

    int dummy = -1;
    is >> day >> month >> year >> hour >> minute >> second;
    

    // Read the rest of the line
    for (unsigned int i = 0; i < 12; i++)
      is >> dummy;
     
    // Convert the data and time to our float in days
    TTimeStamp datetime(year, month, day, hour, minute, second);
    if (fDebug > 0)
      cout << "DEBUG: Time: " <<  datetime.AsString() << endl;

    MonsterEvent ME;
    GetInstantLumi(datetime, ME);
    fTheMEs->push_back(ME);
  } //while reading file

  cout << "\b\b\b\b\b" << Form("%05i",imonster) << endl;

  is.close();
  return imonster;


}


///////////////////
// Find the closest instant lumi (in a beam) at a given time dt and
// store it in ME
//
Float_t MonsterEventsInspector::GetInstantLumi(const TTimeStamp& dt, 
					       MonsterEvent& ME) {


  ME.EventTime = dt;

  if (!IsInBeam(dt)) {
    ME.InstLumi  = 0;
    ME.MinDeltaT = -1;
    ME.IsInBeam  = false;
    return 0;
  }


  ME.IsInBeam = true;

  Float_t dtf = ConvertDateToFloat(dt);
  Float_t time0 = ConvertDateToFloat(TTimeStamp(2012,05,16,0,0,0));
  Float_t lumi0 = 0;

  for (int iev = fInitialEvent; iev < fLumiTree->GetEntries(); iev++) {
    fLumiTree->GetEvent(iev);
    
    //The luminosity is in this interval
    if (dtf > time0 && dtf < fTime) {
      //If one of the edges is 0 take the other one as good
      //otherwise use minimum
      if (lumi0 == 0) {
	ME.InstLumi = fInstLumi;
	ME.MinDeltaT = (fTime - dtf) * SECONDSINADAY;
      }
      else if (fInstLumi == 0) {
	ME.InstLumi = lumi0;
	ME.MinDeltaT = (dtf - time0) * SECONDSINADAY;
      }
      else {
	if ((dtf - time0) < (fTime - dtf)) {
	  ME.InstLumi = lumi0;
	  ME.MinDeltaT = (dtf - time0) * SECONDSINADAY;
	}
	else {
	  ME.InstLumi = fInstLumi;
	  ME.MinDeltaT = (fTime - dtf) * SECONDSINADAY;
	}
      }

      fInitialEvent = iev;
      return ME.InstLumi;
    }

    time0 = fTime;
    lumi0 = fInstLumi;
  }

  return -2;
}



///////////////////
// Convert a time stamp to Ignacio's float
//
float MonsterEventsInspector::ConvertDateToFloat(const TTimeStamp& datetime) const {
  unsigned int t0 = TTimeStamp(2010, 01, 01, 00, 00, 00).GetSec();
  unsigned int t = datetime.GetSec();
  unsigned int seconds = t - t0;
  
  if (fDebug > 1)
    cerr << endl << "DEBUG: t0: " << t0 << " - t: " << t << " - Seconds: " << seconds << endl;

  float result = 1.0* seconds/SECONDSINADAY;

  return result;
}


///////////////////
// True if dt is in a fill, 
// --> i.e. there was beam, 
//     --> i.e. it is not in cosmics
//
bool MonsterEventsInspector::IsInBeam(const TTimeStamp& dt) const {
  if (fDebug > 0)
    cout << "DEBUG: IsInBeam(" << dt.AsString() << ")" << endl;
  Float_t dtf =  ConvertDateToFloat(dt);
  if (fDebug > 0)
    cout << "DEBUG:  + As float: " << dtf << endl;
  for (unsigned int i = 0; i < fTheFills->size(); i++) {
    if (dtf < (*fTheFills)[i].start) {
      return false;
    }
    if (dtf > (*fTheFills)[i].start && dtf < (*fTheFills)[i].end)
      return true;
  }
  return false;
}




///////////////////
// Output operator for MonsterEvent objects
//
std::ostream& operator<<(std::ostream& os, const MonsterEvent& me) {
  os << " - Time: " << me.EventTime 
     << ", I.Lumi: " << me.InstLumi 
     << ", DT: " << me.MinDeltaT
     << ", beam= " << me.IsInBeam;

  return os;

}
