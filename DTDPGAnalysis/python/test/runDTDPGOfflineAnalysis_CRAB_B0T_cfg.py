import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGAnalyis")


process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    firstEvent = cms.untracked.uint32(0),
    skipEvents = cms.untracked.uint32(0),
    firstRun = cms.untracked.uint32(0),
    fileMatchMode = cms.untracked.string('permissive'),
    #      untracked uint32 skipEvents = 1070
   fileNames = cms.untracked.vstring(
    '/store/data/CRUZET09/Cosmics/RAW/v1/000/098/310/FEF916DA-9550-DE11-BC4A-000423D992DC.root'
   )
)                                                



from CondCore.DBCommon.CondDBSetup_cfi import *
process.ttrigsource = cms.ESSource("PoolDBESSource",
    CondDBSetup,
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(cms.PSet(record = cms.string('DTTtrigRcd'),
                               tag = cms.string('DT_tTrig_CRAFT31X_V01_offline')
                               ###tag = cms.string('ttrig')

                               )
                      ),
    connect = cms.string('frontier://Frontier/CMS_COND_31X_DT'),
    ###connect = cms.string('sqlite_file:/afs/cern.ch/cms/CAF/CMSALCA/ALCA_MUONCALIB/DTCALIB/COMM09/ttrig/ttrig_ResidCorr_100850.db'),

    authenticationMethod = cms.untracked.uint32(0)
    )

process.es_prefer_ttrigsource = cms.ESPrefer('PoolDBESSource','ttrigsource')

process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
                                    destinations = cms.untracked.vstring('cout')
                                    )

#------------------
# DT Analyisis
#------------------

# MAGNETIC FIELD
#### B = 0 Tesla ###############################################################
process.load("Configuration.StandardSequences.MagneticField_0T_cff")
process.SteppingHelixPropagator.useInTeslaFromMagField = True
process.SteppingHelixPropagator.SetVBFPointer = True
#### B = 3.8 Tesla #############################################################
##process.load("Configuration.StandardSequences.MagneticField_38T_cff")

#--------------------------------------------------------

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

#--------------------------------------------------------


process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring('drop *', 
                                                                      'keep *_MEtoEDMConverter_*_*'),
                               fileName = cms.untracked.string('DQMOfflineDTDPG.root')
                               )

process.p = cms.Path( process.dtunpacker * process.dttfunpacker * process.reco * process.globalreco + process.sources + process.MEtoEDMConverter  * process.DTOfflineAnalyzer ) 

process.ep = cms.EndPath( process.out )

