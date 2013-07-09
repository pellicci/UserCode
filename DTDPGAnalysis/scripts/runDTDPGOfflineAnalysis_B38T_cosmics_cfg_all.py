import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGAnalyis")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )
###process.source = cms.Source("DaqSource",
###   readerPluginName = cms.untracked.string("DTDDUFileReader"),
###   evtsPerLS = cms.untracked.uint32(1000),
###   readerPset = cms.untracked.PSet( 
###    fileName = cms.untracked.string("/data/c/cerminar/data/local/testYB0_S2S3_vmepcs2g18-16_r72328.i0"))
###   # skipEvents = cms.untracked.int32(),
###   # numberOfHeaderWords = cms.untracked.int32(10)
###)

###process.source = cms.Source("NewEventStreamFileReader",
###    fileNames = cms.untracked.vstring(
###    '/store/data/PrivMuon/A/000/076/428/PrivMuon.00076428.0001.A.storageManager.00.0000.dat', 
###    '/store/data/PrivMuon/A/000/076/428/PrivMuon.00076428.0002.A.storageManager.00.0000.dat'
###    )
###)
process.source = cms.Source("PoolSource",
    firstEvent = cms.untracked.uint32(0),
    skipEvents = cms.untracked.uint32(0),
    firstRun = cms.untracked.uint32(0),
    ###fileMatchMode = cms.untracked.string('permissive'),
    parametersMustMatch = cms.untracked.string('permissive'),
    #      untracked uint32 skipEvents = 1070
   fileNames = cms.untracked.vstring(
        ##'/store/data/Commissioning09/Cosmics/RAW/v1/000/084/191/088669E3-4F3B-DE11-8DB3-0019DB2F3F9A.root'
        '/store/data/Run2010A/Cosmics/RAW/v1/000/139/667/F8A58EA8-6E8A-DF11-8F16-0030487D0D3A.root',
        '/store/data/Run2010A/Cosmics/RAW/v1/000/139/667/FAB93C56-528A-DF11-8A47-0030487CD6D2.root'
   )
)                                                



from CondCore.DBCommon.CondDBSetup_cfi import *
process.ttrigsource = cms.ESSource("PoolDBESSource",
    CondDBSetup,
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(cms.PSet(record = cms.string('DTTtrigRcd'),
                               ###tag = cms.string('DT_tTrig_CRAFT31X_V01_offline')
                               ###tag = cms.string('ttrig')
                               tag = cms.string('DT_tTrig_cosmic2009_V02_hlt')
                               )
                      ),
    connect = cms.string('frontier://Frontier/CMS_COND_31X_DT'),
    ###connect = cms.string('sqlite_file:/afs/cern.ch/cms/CAF/CMSALCA/ALCA_MUONCALIB/DTCALIB/COMM09/ttrig/ttrig_ResidCorr_100850.db'),
    authenticationMethod = cms.untracked.uint32(0)
    )

process.es_prefer_ttrigsource = cms.ESPrefer('PoolDBESSource','ttrigsource')



###process.MessageLogger = cms.Service("MessageLogger",
###                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
###                                    destinations = cms.untracked.vstring('cout')
###                                    )


#### replace unpacker's parameters to run on local ROS25 data
######import EventFilter.DTRawToDigi.dtunpackerDDULocal_cfi as dtunpacker_module
###import EventFilter.DTRawToDigi.dtunpackerDDUGlobal_cfi as dtunpacker_module
#########process.dtunpackerDDU = dtunpacker_module.dtunpacker.clone()
#########process.dtunpackerDDU.readOutParameters.debug = True
###process.dtunpacker.readOutParameters.performDataIntegrityMonitor = True
###process.dtunpacker.readOutParameters.rosParameters.performDataIntegrityMonitor = True
###process.dt1DRecHits.dtDigiLabel = "dtunpacker"
###process.dtDigiMonitor.dtDigiLabel = 'dtunpacker'

#------------------
# DT Analyisis
#------------------

# MAGNETIC FIELD
#### B = 0 Tesla
##process.load("Configuration.StandardSequences.MagneticField_0T_cff")
##process.SteppingHelixPropagator.useInTeslaFromMagField = True
##process.SteppingHelixPropagator.SetVBFPointer = True
#### B = 3.8 Tesla
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

#--------------------------------------------------------

process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.EDMtoMEConverter_cff")
##process.EDMtoMEConverter.convertOnEndLumi = True
##process.EDMtoMEConverter.convertOnEndRun  = False
process.EDMtoMEConverter.convertOnEndLumi = False
process.EDMtoMEConverter.convertOnEndRun  = True
process.DQMStore.collateHistograms = True
process.DQMStore.referenceFileName = ''
process.dqmSaver.convention = 'Offline'
process.dqmSaver.workflow = '/DT/Offline/DPG'
process.dqmSaver.saveByRun = 1


from UserCode.DTDPGAnalysis.DTOfflineAnalyzer_cfi import *
process.DTOfflineAnalyzer.DTLocalTriggerLabel = 'dtunpacker'
process.DTOfflineAnalyzer.doSA = True
##process.DTOfflineAnalyzer.doTBox = True
##process.DTOfflineAnalyzer.doWheelm2 = False
##process.DTOfflineAnalyzer.doWheelm1 = False
##process.DTOfflineAnalyzer.doWheel0 = False
##process.DTOfflineAnalyzer.doWheel1 = False
##process.DTOfflineAnalyzer.doWheel2 = False

process.load("DQM.DTMonitorModule.dtTriggerTask_cfi")
process.dtTriggerMonitor.process_dcc = True
process.dtTriggerMonitor.dcc_label   = 'dttfunpacker'
process.dtTriggerMonitor.process_seg = True

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
process.createDTDPGDQMSummary.runNumber    = 139667
process.createDTDPGDQMSummary.rootFileName = "DQM_V0001_R000139667__DT__Offline__DPG.root"
process.createDTDPGDQMWheelSummary.runNumber    = 139667
process.createDTDPGDQMWheelSummary.rootFileName = "DQM_V0001_R000139667__DT__Offline__DPG.root"
process.createDTDPGAnalyzerSummary.runNumber    = 139667
process.createDTDPGAnalyzerSummary.rootFileName = "DQM_V0001_R000139667__DT__Offline__DPG.root"
process.createDTDPGAnalyzerSummary.SummaryWheelHistos = True
process.createDTDPGAnalyzerSummary.SummaryAllHistos = True

process.clients = cms.Sequence( process.triggerTest + process.triggerEfficiencyTest +process.efficiencyTest + process.segmentTest + process.chamberEfficiencyTest )
#process.p = cms.Path( process.EDMtoMEConverter + process.clients + process.dqmSaver + process.createDQMSummaries )

#--------------------------------------------------------
process.UpdaterService = cms.Service("UpdaterService")

#--------------------------------------------------------


process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring('drop *', 
                                                                      'keep *_MEtoEDMConverter_*_*'),
                               fileName = cms.untracked.string('DQMOfflineDTDPG.root')
                               )


###process.p = cms.Path( process.dtunpacker * process.reco + process.sources + process.MEtoEDMConverter  * process.DTOfflineAnalyzer +  process.clients + process.dqmSaver + process.createSummaries)
##process.p = cms.Path( process.dtunpacker * process.dttfunpacker * process.reco + process.sources + process.MEtoEDMConverter  * process.DTOfflineAnalyzer +  process.clients + process.dqmSaver + process.createSummaries)
##process.p = cms.Path( process.dtunpacker * process.dttfunpacker * process.reco * process.globalreco + process.sources + process.MEtoEDMConverter  * process.DTOfflineAnalyzer +  process.clients + process.dqmSaver + process.createDTDPGDQMWheelSummary)
process.p = cms.Path( process.dtunpacker * process.dttfunpacker * process.reco * process.globalreco + process.sources + process.MEtoEDMConverter  + process.DTOfflineAnalyzer +  process.clients + process.dqmSaver + process.createSummaries)

process.ep = cms.EndPath( process.out )

