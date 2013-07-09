import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGAnalyis")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.source = cms.Source("PoolSource",
                            firstEvent = cms.untracked.uint32(0),
                            skipEvents = cms.untracked.uint32(0),
                            fileNames = cms.untracked.vstring('/store/data/Commissioning08/BarrelMuon/RAW/CRUZET4_v1/000/058/630/0010F51F-B771-DD11-AD2D-000423D99EEE.root')
                            )

process.ttrigsource = cms.ESSource("PoolDBESSource",
                                   CondDBSetup,
                                   timetype = cms.string('runnumber'),
                                   toGet = cms.VPSet(cms.PSet(record = cms.string('DTTtrigRcd'),
                                                              tag = cms.string('tTrig_CRAFT_081021_1614_offline')
                                                              )
                                                     ),
                                   connect = cms.string('frontier://Frontier/CMS_COND_21X_DT'),
                                   authenticationMethod = cms.untracked.uint32(0)
                                   )

process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
                                    destinations = cms.untracked.vstring('cout')
                                    )

#------------------
# DT Analyisis
#------------------

# MAGNETIC FIELD
# 3.8T 
process.load("MagneticField.Engine.volumeBasedMagneticField_1103l_cfi") ##
# 3.0T
# process.VolumeBasedMagneticFieldESProducer.version = 'grid_1103l_071212_3t'
# process.ParametrizedMagneticFieldProducer.parameters.BValue = '3_0T'
# 2.0T
# process.VolumeBasedMagneticFieldESProducer.version = 'grid_1103l_071212_2t'
# process.ParametrizedMagneticFieldProducer.parameters.BValue = '2_0T'
# 0.0T
# process.load("MagneticField.Engine.uniformMagneticField_cfi")

process.load("UserCode.DTDPGAnalysis.DTOfflineAnalyzer_cfi")
process.DTOfflineAnalyzer.rootFileName = 'DTAnalyzerTest_r58553.root'

process.load("UserCode.DTDPGAnalysis.STAOfflineAnalyzer_cfi")
process.STAOfflineAnalyzer.rootFileName = 'DTAnalyzerSTA_r58553.root'

process.load("UserCode.DTDPGAnalysis.DTEffOfflineAnalyzer_cfi")
process.DTEffOfflineAnalyzer.rootFileName = 'DTEffAnalyzer_r58553.root'


#------------
# DT DQM
#------------

process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Core.DQM_cfg")

process.load("DQM.DTMonitorModule.dtDataIntegrityTask_cfi")
process.DTDataIntegrityTask.hltMode = False

process.load("DQM.DTMonitorModule.dtDigiTask_cfi")
process.dtDigiMonitor.readDB = True
process.dtDigiMonitor.doNoiseOccupancies = True

process.load("DQM.DTMonitorModule.dtTriggerTask_cfi")
process.dtTriggerMonitor.process_dcc = True
process.dtTriggerMonitor.dcc_label   = 'dttfunpacker'
process.dtTriggerMonitor.process_seg = True

process.load("DQM.DTMonitorModule.dtEfficiencyTask_cfi")
process.load("DQM.DTMonitorModule.dtChamberEfficiencyTask_cfi")
process.load("DQM.DTMonitorModule.dtResolutionTask_cfi")

process.load("DQM.DTMonitorModule.dtSegmentTask_cfi")
process.dtSegmentAnalysisMonitor.detailedAnalysis = True


process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring('drop *', 
                                                                      'keep *_MEtoEDMConverter_*_*'),
                               fileName = cms.untracked.string('DQMOfflineDTDPG.root')
                               )


process.sources = cms.Sequence( process.dtDigiMonitor + process.dtTriggerMonitor + process.dtEfficiencyMonitor + process.dtChamberEfficiencyMonitor + process.dtSegmentAnalysisMonitor + process.dtResolutionAnalysisMonitor)

process.analysis = cms.Sequence(process.DTOfflineAnalyzer + process.DTEffOfflineAnalyzer + process.STAOfflineAnalyzer)


process.p = cms.Path( process.unpackers * process.reco * process.globalreco + process.sources + process.MEtoEDMConverter +process.analysis )
process.ep = cms.EndPath( process.out )


