import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGAnalyis")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.source = cms.Source("PoolSource",
                            firstEvent = cms.untracked.uint32(0),
                            skipEvents = cms.untracked.uint32(0),
                            fileNames = cms.untracked.vstring('/store/data/Commissioning08/BarrelMuon/RAW/CRUZET4_v1/000/058/630/0010F51F-B771-DD11-AD2D-000423D99EEE.root')
                            )

from CondCore.DBCommon.CondDBSetup_cfi import *
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
process.load("Configuration.StandardSequences.MagneticField_2T_cff")





process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring('drop *', 
                                                                      'keep *_MEtoEDMConverter_*_*'),
                               fileName = cms.untracked.string('DQMOfflineDTDPG.root')
                               )



process.p = cms.Path( process.unpackers * process.reco * process.globalreco + process.sources + process.MEtoEDMConverter +process.analysis )
process.ep = cms.EndPath( process.out )


