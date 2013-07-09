import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGAnalyis")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")
process.DTOfflineAnalyzer.doSA = False
process.DTOfflineAnalyzer.DTLocalTriggerLabel = 'dtunpackerROS25'
##process.DTOfflineAnalyzer.doTBox = False
##process.DTOfflineAnalyzer.doWheelm2 = False
##process.DTOfflineAnalyzer.doWheelm1 = False
##process.DTOfflineAnalyzer.doWheel0 = False
##process.DTOfflineAnalyzer.doWheel1 = False
##process.DTOfflineAnalyzer.doWheel2 = False




process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )

process.source = cms.Source("DaqSource",
                            readerPluginName = cms.untracked.string("DTROS25FileReader"),
                            evtsPerLS = cms.untracked.uint32(1000),
                            readerPset = cms.untracked.PSet( 
    fileName = cms.untracked.string("/data/c/cerminar/data/local/mb4_0_3_25mv_3_ros25.txt"))
                            # skipEvents = cms.untracked.int32(),
                            # numberOfHeaderWords = cms.untracked.int32(10)
                            )


from CondCore.DBCommon.CondDBSetup_cfi import *
process.ttrigsource = cms.ESSource("PoolDBESSource",
                                   CondDBSetup,
                                   timetype = cms.string('runnumber'),
                                   toGet = cms.VPSet(cms.PSet(record = cms.string('DTTtrigRcd'),
#                                                              tag = cms.string('ttrig')
                                                              tag = cms.string('tTrig_CRAFT_081021_1614_offline')
                                                              )
                                                     ),
                                   connect = cms.string('frontier://Frontier/CMS_COND_21X_DT'),
#                                   connect = cms.string('sqlite_file:ttrig_ROS25Local.db'),
                                   authenticationMethod = cms.untracked.uint32(0)
                                   )




# replace unpacker's parameters to run on local ROS25 data
import EventFilter.DTRawToDigi.dtunpackerROS25Local_cfi as dtunpacker_module
process.dtunpackerROS25 = dtunpacker_module.dtunpacker.clone()
process.dtunpackerROS25.readOutParameters.performDataIntegrityMonitor = True
process.dtunpackerROS25.readOutParameters.rosParameters.performDataIntegrityMonitor = True
process.dt1DRecHits.dtDigiLabel = "dtunpackerROS25"
process.dtDigiMonitor.dtDigiLabel = 'dtunpackerROS25'

process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
                                    destinations = cms.untracked.vstring('cout')
                                    )

#------------------
# DT Analyisis
#------------------

# MAGNETIC FIELD
process.load("Configuration.StandardSequences.MagneticField_0T_cff")
process.SteppingHelixPropagator.useInTeslaFromMagField = True
process.SteppingHelixPropagator.SetVBFPointer = True




#--------------------------------------------------------


process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.EDMtoMEConverter_cff")
process.EDMtoMEConverter.convertOnEndLumi = True
process.EDMtoMEConverter.convertOnEndRun  = False
process.DQMStore.collateHistograms = True
process.DQMStore.referenceFileName = ''
process.dqmSaver.convention = 'Offline'
process.dqmSaver.workflow = '/DT/Offline/DPG'
process.dqmSaver.saveByRun = 1


# process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
# process.source = cms.Source("PoolSource",
#                             firstEvent = cms.untracked.uint32(0),
#                             skipEvents = cms.untracked.uint32(0),
#                             fileNames = cms.untracked.vstring('file:DQMOfflineDTDPG.root')
#                             )


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
process.createDTDPGDQMSummary.runNumber    = 1
process.createDTDPGDQMSummary.rootFileName = "DQM_V0001_R000000001__DT__Offline__DPG.root"
process.createDTDPGDQMWheelSummary.runNumber    = 1
process.createDTDPGDQMWheelSummary.rootFileName = "DQM_V0001_R000000001__DT__Offline__DPG.root"
process.createDTDPGAnalyzerSummary.runNumber    = 1
process.createDTDPGAnalyzerSummary.rootFileName = "DQM_V0001_R000000001__DT__Offline__DPG.root"
process.createDTDPGAnalyzerSummary.SummaryWheelHistos = False
process.createDTDPGAnalyzerSummary.SummaryAllHistos = False

process.clients = cms.Sequence( process.triggerTest + process.triggerEfficiencyTest +process.efficiencyTest + process.segmentTest + process.chamberEfficiencyTest )
#process.p = cms.Path( process.EDMtoMEConverter + process.clients + process.dqmSaver + process.createDQMSummaries )

#--------------------------------------------------------


process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring('drop *', 
                                                                      'keep *_MEtoEDMConverter_*_*'),
                               fileName = cms.untracked.string('DQMOfflineDTDPG.root')
                               )


process.p = cms.Path( process.dtunpackerROS25 * process.reco + process.sources +  process.DTOfflineAnalyzer + process.clients + process.dqmSaver + process.createSummaries)
#process.ep = cms.EndPath( process.out )


