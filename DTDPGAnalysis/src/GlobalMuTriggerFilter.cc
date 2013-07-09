//
// Original Author:  Maria Fouz Iglesias
//         Created:  Thu Oct 30 12:08:09 CEST 2010
//


// system include files
#include <memory>

// user include files
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutRecord.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UserCode/DTDPGAnalysis/src/GlobalMuTriggerFilter.h"



//
// constructors and destructor
//
GlobalMuTriggerFilter::GlobalMuTriggerFilter(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   theL1MuonGlobalTriggerLabel = iConfig.getParameter<edm::InputTag>("L1MuGlobalTriggeLabel");


}


GlobalMuTriggerFilter::~GlobalMuTriggerFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
bool
GlobalMuTriggerFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool result = false;

  edm::Handle<L1MuGMTReadoutCollection> pCollection;
  iEvent.getByLabel(theL1MuonGlobalTriggerLabel,pCollection);

  if (!pCollection.isValid()) {
    cout << "can't find L1MuGMTReadoutCollection with label " << theL1MuonGlobalTriggerLabel ;
    return false;
  }

  int nSUBSAllBX[5] = {0, 0, 0, 0, 0};

  // get GMT readout collection
  L1MuGMTReadoutCollection const* gmtrc = pCollection.product();
  // get record vector
  vector<L1MuGMTReadoutRecord> gmt_records = gmtrc->getRecords();
  // loop over records of individual bx's
  vector<L1MuGMTReadoutRecord>::const_iterator RRItr;
  for( RRItr = gmt_records.begin(); RRItr != gmt_records.end(); RRItr++ )
  {

    /*
    cout << " BxNr: " << RRItr->getBxNr();
    cout << " BxInEvent: " << RRItr->getBxInEvent(); 
    cout << " EvNr:  "  << RRItr->getEvNr();
    cout << " BCErr: " << RRItr->getBCERR() << endl;
    */
   
    vector<L1MuRegionalCand> INPCands[4] = {
        RRItr->getDTBXCands(),
        RRItr->getBrlRPCCands(),
        RRItr->getCSCCands(),
        RRItr->getFwdRPCCands()
     };

    vector<L1MuGMTExtendedCand> GMTCands   = RRItr->getGMTCands();
    vector<L1MuRegionalCand>::const_iterator INPItr;
    vector<L1MuGMTExtendedCand>::const_iterator GMTItr;
    vector<L1MuGMTExtendedCand>::const_iterator GMTItr2;

    //int BxInEvent = RRItr->getBxInEvent();

    // count non-empty candidates
    int nSUBS[5] = {0, 0, 0, 0, 0};
    for(int i=0; i<4; i++) 
      for( INPItr = INPCands[i].begin(); INPItr != INPCands[i].end(); ++INPItr )
      {
        if(!INPItr->empty()) nSUBS[i]++;
        if(!INPItr->empty()) nSUBSAllBX[i]++;
        if(!INPItr->empty())
         {
           if( INPItr->type_idx() != unsigned(i) )
             cout << "[GlobalMuTriggerFilter] Warning missmatch on regional candidate code" << endl;
             // i=0  DTTF
             // i=1  RPCb
             // i=2  CSCTF
             // i=3  RPCf
           //cout << INPItr->bx();
           //cout << INPItr->quality();
           //cout << INPItr->phiValue() << "," << INPItr->etaValue();
         }
      }
    /*
    if(nSUBS[0]+nSUBS[1]+nSUBS[2]+nSUBS[3]> 0)
    cout << "[GlobalMuTriggerFilter] : #candidates DTTF " << nSUBS[0] << " RPC " <<  nSUBS[1] 
         << " CSC "  << nSUBS[2] << " RPC_Forward "   << nSUBS[3] << endl ;

    if(nSUBS[1]>0)for(int ii=0;ii<100;ii++)cout << " EEEEEEEEEE  RPC!!!! =" << nSUBS[1] << endl;
    */

  }

  //if(nSUBSAllBX[0]+nSUBSAllBX[1]+nSUBSAllBX[2]+nSUBSAllBX[3]>0)result=true; // if any muon
  //if(nSUBSAllBX[0]>0 && nSUBSAllBX[1]+nSUBSAllBX[2]+nSUBSAllBX[3]==0)result=true; // Barrel Muon Only. NO RPC 
  //if(nSUBSAllBX[0]>0 && nSUBSAllBX[1]>0 && nSUBSAllBX[2]+nSUBSAllBX[3]==0)result=true; // Barrel Muon Only. DT & RPC 
  //if(nSUBSAllBX[1]>0 && nSUBSAllBX[0]+nSUBSAllBX[2]+nSUBSAllBX[3]==0)result=true; // Barrel Muon Only. RPC 
  //if(nSUBSAllBX[0]+nSUBSAllBX[1]>0 && nSUBSAllBX[2]+nSUBSAllBX[3]==0)result=true; // Barrel Muon Only. DT or RPC 
  //if(nSUBSAllBX[0]+nSUBSAllBX[1]==0 && nSUBSAllBX[2]+nSUBSAllBX[3]>0)result=true; // Endcap Muon Only. CSC or RPC 
  if(nSUBSAllBX[0]+nSUBSAllBX[1]+nSUBSAllBX[2]+nSUBSAllBX[3]==0)result=true; //  Not Muons 

  return result;
}


// ------------ method called once each job just before starting event loop  ------------
void 
GlobalMuTriggerFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GlobalMuTriggerFilter::endJob() {
}



