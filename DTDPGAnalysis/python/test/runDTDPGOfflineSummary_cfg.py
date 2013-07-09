import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGDQM2")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")

process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.EDMtoMEConverter_cff")
process.EDMtoMEConverter.convertOnEndLumi = True
process.EDMtoMEConverter.convertOnEndRun  = False
process.DQMStore.collateHistograms = True
process.DQMStore.referenceFileName = ''
process.dqmSaver.convention = 'Offline'
process.dqmSaver.workflow = '/DT/Offline/DPG'
process.dqmSaver.saveByRun = 1


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
                            firstEvent = cms.untracked.uint32(0),
                            skipEvents = cms.untracked.uint32(0),
                            fileNames = cms.untracked.vstring('file:DQMOfflineDTDPG.root')
                            )


process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
                                    destinations = cms.untracked.vstring('cout')
                                    )


process.load("DQM.DTMonitorClient.dtLocalTriggerTest_cfi")
process.load("DQM.DTMonitorClient.dtLocalTriggerEfficiencyTest_cfi")

process.load("DQM.DTMonitorClient.dtEfficiencyTest_cfi")

process.load("DQM.DTMonitorClient.dtChamberEfficiencyTest_cfi")

process.load("DQM.DTMonitorClient.dtSegmentAnalysisTest_cfi")
process.segmentTest.detailedAnalysis = True

process.load("UserCode.DTDPGAnalysis.dtCreateSummaries_cff")
#process.createDTDPGSummary.DigiHistos   = False
process.createDTDPGDQMSummary.runNumber    = 58630
process.createDTDPGDQMSummary.rootFileName = "DQM_V0001_R000058630__DT__Offline__DPG.root"
process.createDTDPGDQMWheelSummary.runNumber    = 58630
process.createDTDPGDQMWheelSummary.rootFileName = "DQM_V0001_R000058630__DT__Offline__DPG.root"
process.createDTDPGAnalyzerSummary.runNumber    = 58630
process.createDTDPGAnalyzerSummary.rootFileName = "DQM_V0001_R000058630__DT__Offline__DPG.root"


process.clients = cms.Sequence( process.triggerTest + process.triggerEfficiencyTest +process.efficiencyTest + process.segmentTest + process.chamberEfficiencyTest )
process.p = cms.Path( process.EDMtoMEConverter + process.clients + process.dqmSaver + process.createSummaries )

