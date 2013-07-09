#include "FWCore/Framework/interface/MakerMacros.h"

#include "UserCode/DTDPGAnalysis/src/DTDPGCreateSummary.h"
DEFINE_FWK_MODULE(DTDPGCreateSummary);

#include "UserCode/DTDPGAnalysis/src/DTDPGCreateWheelSummary.h"
DEFINE_FWK_MODULE(DTDPGCreateWheelSummary);

#include "UserCode/DTDPGAnalysis/src/CheckDeadChannels.h"
DEFINE_FWK_MODULE(CheckDeadChannels);

#include "UserCode/DTDPGAnalysis/src/DTDPGCreateAnalyzerSummary.h"
DEFINE_FWK_MODULE(DTDPGCreateAnalyzerSummary);

#include "UserCode/DTDPGAnalysis/interface/DTMuonSelection.h"
DEFINE_FWK_MODULE(DTMuonSelection);

#include "UserCode/DTDPGAnalysis/src/DTOfflineAnalyzer.h"
DEFINE_FWK_MODULE(DTOfflineAnalyzer);

#include "UserCode/DTDPGAnalysis/src/DTEffOfflineAnalyzer.h"
DEFINE_FWK_MODULE(DTEffOfflineAnalyzer);

#include "UserCode/DTDPGAnalysis/src/STAOfflineAnalyzer.h"
DEFINE_FWK_MODULE(STAOfflineAnalyzer);

#include "UserCode/DTDPGAnalysis/src/GlobalMuTriggerFilter.h"
DEFINE_FWK_MODULE(GlobalMuTriggerFilter);

