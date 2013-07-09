import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGDQM1")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")


process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Core.DQM_cfg")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
                            firstEvent = cms.untracked.uint32(0),
                            skipEvents = cms.untracked.uint32(0),
                            fileNames = cms.untracked.vstring('/store/data/Commissioning08/BarrelMuon/RAW/CRUZET4_v1/000/058/630/0010F51F-B771-DD11-AD2D-000423D99EEE.root')
                            )

#process.source.fileNames = ('/store/data/Commissioning08/BarrelMuon/RAW/CRUZET4_v1/000/058/630/0010F51F-B771-DD11-AD2D-000423D99EEE.root',
#                            '/store/data/Commissioning08/BarrelMuon/RAW/CRUZET4_v1/000/058/630/001B16FC-9A71-DD11-86A1-001617E30F4C.root'
#                            )


process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
                                    destinations = cms.untracked.vstring('cout')
                                    )


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


process.p = cms.Path( process.unpackers * process.reco * process.sources + process.MEtoEDMConverter )
process.ep = cms.EndPath( process.out )


