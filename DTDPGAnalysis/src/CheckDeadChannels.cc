/*
Compare dead channels found in this run with a reference one
Oct. 13, 2011
Francesca R. Cavallo  
*/


#include <UserCode/DTDPGAnalysis/src/CheckDeadChannels.h>



#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <math.h>

#include "boost/filesystem.hpp"

using namespace boost::filesystem;
using namespace edm;
using namespace std;


CheckDeadChannels::CheckDeadChannels(const edm::ParameterSet& ps){

  edm::LogVerbatim ("DTDPGSummary") << "[CheckDeadChannels]: Constructor";

  myParameters = ps;
  myRunNumber  = ps.getUntrackedParameter<int>("runNumber",0);
  // 06-12-2011 take the reference run from the txt files mantained to this purpose in the /COMM_DT/OfflineCode/Scripts area
  //ReferenceRun  = ps.getUntrackedParameter<int>("referenceRun",0);

}

CheckDeadChannels::~CheckDeadChannels(){

  edm::LogVerbatim ("DTDPGSummary") << "[CheckDeadChannels]: Destructor called";

  char deadname[100];  string deadnameRef; char comparison[100]; string RefDir;

  ifstream  refRun ("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DT/OfflineCode/Scripts/referenceRun.txt");

  refRun>>ReferenceRun;
  refRun>>RefDir;
  refRun>>RefDir; //skipping unwanted string
  refRun.close();

  sprintf (deadname, "Run%i/DeadChannelList_r%i.txt",myRunNumber,myRunNumber);

  // 06-12-2011 distinguish HeavyIons from Beam (pp) folders


  char filen[100];
  sprintf (filen, "DeadChannelList_r%i.txt",ReferenceRun);
  deadnameRef = RefDir + filen;
  sprintf (comparison, "Run%i/DeadChannelCheck_r%i_to_r%i.txt",myRunNumber, myRunNumber,ReferenceRun);

  ifstream  DeadChannelList (deadname);
  ifstream  DeadChannelRef  (deadnameRef.c_str());
  cout<<" opened "<<deadname<<" and "<<deadnameRef<<endl;

  DeadComp = new ofstream(comparison);

  int wheel,  station, sector, sl, lay, wire; float effi; float deffi;
  int wheelref[200000], stationref[200000], sectorref[200000], slref[200000], layref[200000], wireref[200000]; float effiref; float deffiref;

  char printline[50];

  int nref=0;

  while (DeadChannelRef>>wheelref[nref]>>stationref[nref]>>sectorref[nref]>>slref[nref]>>layref[nref]>>wireref[nref]>>effiref>>deffiref) {
    if (effiref>=0) nref++;
    if (nref>199999) {
      *DeadComp<<" WARNING !! more than 200000 dead channels in reference run! "<<endl<<endl;
      break;
    }
  }

  cout<<nref<<" lines read in reference "<<endl;

  // search for "new" dead channels
  *DeadComp<<" New dead channels (wheel, station, sector, superlayer, layer, wire, meas.efficiency, error)"<<endl<<endl;

  int ncheck=0; int nnew=0;
  while (DeadChannelList>>wheel>>station>>sector>>sl>>lay>>wire>>effi>>deffi){
    int ip=0;
    while(  effi>=0 && 
	    !(wheel==wheelref[ip]  && station==stationref[ip] && sector==sectorref[ip] && sl==slref[ip]  && lay==layref[ip]  && wire==wireref[ip]) && 
            wheel>=wheelref[ip] &&
            ip<nref) ip++;
      if (ip==nref || wheelref[ip]>wheel) {
       nnew++;

       sprintf (printline,"%3i%3u%4u%3u%3u%4u%7.2f%7.2f",wheel,station,sector,sl,lay,wire,effi,deffi);
       *DeadComp<<printline<<endl; 
      }
      if (effi>=0) {ncheck++;
      }
  }
  cout<<ncheck<<" lines read in this run from "<<deadname<<endl;
  cout<<" ncheck "<<ncheck<<" nnew "<<nnew<<" nref "<<nref<<endl;

  if (ncheck < (nref+nnew)) { // resurrections?

    *DeadComp<<endl<<" Resurrected channels (wheel, station, sector, superlayer, layer, wire, previous.efficiency, error)"<<endl<<endl;

    DeadChannelList.close();
    DeadChannelList.open(deadname);
    DeadChannelRef.close();
    DeadChannelRef.open(deadnameRef.c_str());
    *DeadComp<<endl;
    nref=0; int nres=0;

    while (DeadChannelList>>wheelref[nref]>>stationref[nref]>>sectorref[nref]>>slref[nref]>>layref[nref]>>wireref[nref]>>effiref>>deffiref) {
      //if (effiref>=0) nref++; // effiref<0 --> undetermined
      nref++;
      if (nref>199999) {
        *DeadComp<<" WARNING !! more than 200000 dead channels in this run! "<<endl<<endl;
        break;
      }
    }

    while (DeadChannelRef>>wheel>>station>>sector>>sl>>lay>>wire>>effi>>deffi){

      int ip=0;
      while( effi>=0 &&  // effi<0 --> undetermined 
           !(wheel==wheelref[ip] && station==stationref[ip] && sector==sectorref[ip] && sl==slref[ip]  && lay==layref[ip]  && wire==wireref[ip]) && 
             wheel>=wheelref[ip] && 
             ip<nref) ip++; 
      if (ip==nref || wheelref[ip]>wheel) {
        nres++;
        sprintf (printline,"%3i%3u%4u%3u%3u%4u%7.2f%7.2f",wheel,station,sector,sl,lay,wire,effi,deffi);
        *DeadComp<<printline<<endl; 
      }
    } 

// investigate on (groups of) cells without segments or zero efficiency

    *DeadComp<<endl<<" Rows of 4 or more channels with no segments or zero efficiency"<<endl
                   <<"(wheel, station, sector, superlayer, layer, group of wires)"<<endl<<endl;
    DeadChannelList.close();
    DeadChannelList.open(deadname);
    int ndrow=0;
    int curwh=0, curse=0, curst=0, cursl=0, curlay=0, curwi=0;

    while (DeadChannelList>>wheel>>station>>sector>>sl>>lay>>wire>>effi>>deffi){

      if (effi<-1 || (effi>=0.&&effi<0.01)) {
	if (wheel==curwh && station==curst && sector==curse && sl==cursl && lay==curlay && wire==curwi+1){
	  ndrow++;
	}
        else { // new possible row of dead channels

          if (ndrow>=3)  {
	    sprintf (printline,"%3i%3u%4u%3u%3u%4u - %4u",curwh,curst,curse,cursl,curlay,curwi-ndrow,curwi);
           *DeadComp<<printline<<endl;
	  }
	  ndrow=0;
          curwh=wheel;
          curst=station;
          curse=sector;
          cursl=sl;
          curlay=lay;
	}
        curwi=wire;
      }
    }

    if (ndrow>=3)  { // last row
      sprintf (printline,"%3i%3u%4u%3u%3u%4u - %4u",curwh,curst,curse,cursl,curlay,curwi-ndrow,curwi);
      *DeadComp<<printline<<endl;
    }   

  }

  DeadComp->close();
}


void CheckDeadChannels::beginJob(){

  edm::LogVerbatim ("DTDPGSummary") << "[CheckDeadChannels]: beginJob";

}


void CheckDeadChannels::beginRun(const edm::Run& run,const edm::EventSetup& context){

  edm::LogVerbatim ("DTDPGSummary") << "[CheckDeadChannels]: beginRun";

}

void CheckDeadChannels::analyze(const edm::Event& e, const edm::EventSetup& context){
  
}

void CheckDeadChannels::endJob(){

  edm::LogVerbatim ("DTDPGSummary") << "[CheckDeadChannels] endJob called!";

}
