//
// Original Author:  Mario Pelliccioni
//         Created:  Tue May 4 15:56:24 CEST 2010

// user include files
#include "UserCode/DTDPGAnalysis/interface/DTMuonSelection.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"

DTMuonSelection::DTMuonSelection(const edm::ParameterSet& iConfig)
{
  muonList        = iConfig.getParameter<edm::InputTag>("src");
  etaMin          = iConfig.getParameter<double>("etaMin");
  etaMax          = iConfig.getParameter<double>("etaMax");
  ptMin           = iConfig.getParameter<double>("ptMin");

  rng = new TRandom3(0);
}


DTMuonSelection::~DTMuonSelection() { }


bool DTMuonSelection::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool result = false;

  //Retrieve the muons list
  edm::Handle<reco::MuonCollection> MuHandle;
  iEvent.getByLabel(muonList,MuHandle);

  for (reco::MuonCollection::const_iterator nmuon = MuHandle->begin(); nmuon != MuHandle->end(); ++nmuon){

    double ptMuon(0.);
    double etaMuon(-999.);

    if(!(nmuon->isGlobalMuon())) continue;

    ptMuon = nmuon->globalTrack()->pt();
    etaMuon = nmuon->globalTrack()->eta();

    if(ptMuon > ptMin && etaMuon > etaMin && etaMuon < etaMax){
      result = true;
      break;
    }

  }

  //too many events in the dataset, throw away half of them
  //const Double_t rng_choice = rng->Uniform();
  //if(rng_choice < 0.5) return false;

  return result;
}



// ------------ method called once each job just before starting event loop  ------------
void  DTMuonSelection::beginJob() {
}



// ------------ method called once each job just after ending the event loop  ------------
void  DTMuonSelection::endJob() {
}
