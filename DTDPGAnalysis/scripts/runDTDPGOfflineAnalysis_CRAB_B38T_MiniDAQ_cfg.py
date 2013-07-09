import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGAnalyis")


process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff_cosmics_miniDAQ")



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    firstEvent = cms.untracked.uint32(0),
    skipEvents = cms.untracked.uint32(0),
    firstRun = cms.untracked.uint32(0),
    ##fileMatchMode = cms.untracked.string('permissive'),
    parametersMustMatch = cms.untracked.string('permissive'),
    #      untracked uint32 skipEvents = 1070
   fileNames = cms.untracked.vstring(
     ##'file:/afs/cern.ch/work/m/marycruz/private/MiniDaqRuns/621FA8AD-6E0D-E211-855F-001D09F24D67_Run204209.root'
     ##'/store/data/Run2012C/MiniDaq/RAW//v1/000/203/540/AA9053D9-F306-E211-80A4-001D09F248F8.root'
   )
)                                                



##from CondCore.DBCommon.CondDBSetup_cfi import *
##process.ttrigsource = cms.ESSource("PoolDBESSource",
##    CondDBSetup,
##    timetype = cms.string('runnumber'),
##    toGet = cms.VPSet(cms.PSet(record = cms.string('DTTtrigRcd'),
##                               ###tag = cms.string('DT_tTrig_CRAFT31X_V01_offline')
##                               ###tag = cms.string('ttrig')
##                               ###tag = cms.string('DT_tTrig_cosmic2009_V02_hlt')
##                               ###tag = cms.string('DT_tTrig_cosmic2009_V02_prompt')
##                               tag = cms.string('DT_tTrig_cosmics_2009_v3_prompt')
##                               )
##                      ),
##    connect = cms.string('frontier://Frontier/CMS_COND_31X_DT'),
##    ###connect = cms.string('sqlite_file:/afs/cern.ch/cms/CAF/CMSALCA/ALCA_MUONCALIB/DTCALIB/COMM09/ttrig/ttrig_ResidCorr_100850.db'),
##
##    authenticationMethod = cms.untracked.uint32(0)
##    )
##
##process.es_prefer_ttrigsource = cms.ESPrefer('PoolDBESSource','ttrigsource')

process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
                                    destinations = cms.untracked.vstring('cout')
                                    )

#------------------
# DT Analyisis
#------------------

# MAGNETIC FIELD
#### B = 0 Tesla ###############################################################
##process.load("Configuration.StandardSequences.MagneticField_0T_cff")
##process.SteppingHelixPropagator.useInTeslaFromMagField = True
##process.SteppingHelixPropagator.SetVBFPointer = True
#### B = 3.8 Tesla #############################################################
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

#--------------------------------------------------------

from UserCode.DTDPGAnalysis.DTOfflineAnalyzer_cfi import *
process.DTOfflineAnalyzer.DTLocalTriggerLabel = 'dtunpacker'
process.DTOfflineAnalyzer.doSA = True
##process.DTOfflineAnalyzer.doWheelm2 = False
##process.DTOfflineAnalyzer.doWheelm1 = False
##process.DTOfflineAnalyzer.doWheel0 = False
##process.DTOfflineAnalyzer.doWheel1 = False
##process.DTOfflineAnalyzer.doWheel2 = False

##process.DTOfflineAnalyzer.doTBox = True
##process.DTOfflineAnalyzer.doTBoxWhm2 = True
##process.DTOfflineAnalyzer.doTBoxWhm1 = False
##process.DTOfflineAnalyzer.doTBoxWh0 = False
##process.DTOfflineAnalyzer.doTBoxWh1 = False
##process.DTOfflineAnalyzer.doTBoxWh2 = True
##process.DTOfflineAnalyzer.doTBoxSector  = 0 ## =0 => All Sectors, =N => Sector N 
##process.DTOfflineAnalyzer.doTBoxChamber = 0 ## =0 => All Chambers,=N => Chamber N 
##process.DTOfflineAnalyzer.doTBoxSuperLayer = 1 ## =0 => All SuperLayers,=N => SuperLayer N 
##process.DTOfflineAnalyzer.doTBoxLayer = 1 ## =0 => All Layers,=N => Layer N 

process.load("DQM.DTMonitorModule.dtTriggerTask_cfi")
process.dtTriggerMonitor.process_dcc = True
process.dtTriggerMonitor.dcc_label   = 'dttfunpacker'
process.dtTriggerMonitor.process_seg = True

#--------------------------------------------------------
process.UpdaterService = cms.Service("UpdaterService")  ###  Only needed for STA reco
#--------------------------------------------------------


process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring('drop *', 
                                                                      'keep *_MEtoEDMConverter_*_*'),
                               fileName = cms.untracked.string('DQMOfflineDTDPG.root')
                               )

### IF ONLY RAW, RECO NEEDED
process.p = cms.Path( process.dtunpacker * process.dttfunpacker * process.reco * process.globalreco + process.sources + process.MEtoEDMConverter  + process.DTOfflineAnalyzer ) 
### RAW+RECO DATASET
###process.p = cms.Path( process.dtunpacker * process.dttfunpacker + process.sources + process.MEtoEDMConverter  + process.DTOfflineAnalyzer ) 

process.ep = cms.EndPath( process.out )

