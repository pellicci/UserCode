import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGDQM2")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_Colisions_cff")

process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.EDMtoMEConverter_cff")
###process.EDMtoMEConverter.convertOnEndLumi = True
###process.EDMtoMEConverter.convertOnEndRun  = False
process.EDMtoMEConverter.convertOnEndLumi = False
process.EDMtoMEConverter.convertOnEndRun  = True
process.DQMStore.collateHistograms = False
process.DQMStore.referenceFileName = ''
process.dqmSaver.convention = 'Offline'
process.dqmSaver.workflow = '/DT/Offline/DPG'
process.dqmSaver.saveByRun = 1

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    firstEvent = cms.untracked.uint32(0),
    skipEvents = cms.untracked.uint32(0),
    firstRun = cms.untracked.uint32(0),
    ###fileMatchMode = cms.untracked.string('permissive'),
    parametersMustMatch = cms.untracked.string('permissive'),
    #      untracked uint32 skipEvents = 1070
   fileNames = cms.untracked.vstring(
        ##'file:/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DT/tmpanalysis/marycruz/testversion226/tmp3/DQMOfflineDTDPG.root'
        INPUT
   )
)                                                

process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
                                    destinations = cms.untracked.vstring('cout')
                                    )

#--------------------------------------------------------

process.load("DQM.DTMonitorClient.dtLocalTriggerTest_cfi")
process.load("DQM.DTMonitorClient.dtLocalTriggerEfficiencyTest_cfi")
process.load("DQM.DTMonitorClient.dtLocalTriggerLutTest_cfi")
process.triggerTest.runOnline = False
process.triggerEfficiencyTest.runOnline = False
process.triggerLutTest.runOnline = False

process.load("DQM.DTMonitorClient.dtEfficiencyTest_cfi")

process.load("DQM.DTMonitorClient.dtChamberEfficiencyTest_cfi")

process.load("DQM.DTMonitorClient.dtSegmentAnalysisTest_cfi")
process.segmentTest.detailedAnalysis = True

process.load("UserCode.DTDPGAnalysis.dtCreateSummaries_cff")
###process.createDTDPGDQMSummary.DigiHistos   = False
process.createDTDPGDQMSummary.runNumber    = INSERTRUN
process.createDTDPGDQMSummary.rootFileName = "DQM_V0001_R000INSERTRUN__DT__Offline__DPG.root"
process.createDTDPGDQMWheelSummary.runNumber    = INSERTRUN
process.createDTDPGDQMWheelSummary.rootFileName = "DQM_V0001_R000INSERTRUN__DT__Offline__DPG.root"
process.createCheckDeadChannels.runNumber    = INSERTRUN
process.createCheckDeadChannels.referenceRun   = 0 # from 06-12-2011 it is read from file
process.createDTDPGAnalyzerSummary.runNumber    = INSERTRUN
process.createDTDPGAnalyzerSummary.rootFileName = "DQM_V0001_R000INSERTRUN__DT__Offline__DPG.root"
process.createDTDPGAnalyzerSummary.SummaryWheelHistos = True
process.createDTDPGAnalyzerSummary.SummaryAllHistos = True

process.clients = cms.Sequence( process.triggerTest + process.triggerEfficiencyTest + process.triggerLutTest + process.efficiencyTest + process.segmentTest + process.chamberEfficiencyTest )
###process.p = cms.Path( process.EDMtoMEConverter + process.clients + process.dqmSaver + process.createDQMSummaries )
process.p = cms.Path( process.EDMtoMEConverter + process.clients + process.dqmSaver + process.createSummaries)
process.outpath = cms.EndPath(process.createCheckDeadChannels)

#--------------------------------------------------------


