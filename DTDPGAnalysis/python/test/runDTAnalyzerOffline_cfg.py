import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDPGDTAnalyzer")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")
process.dtunpacker.readOutParameters.rosParameters.performDataIntegrityMonitor = False
process.dtunpacker.readOutParameters.performDataIntegrityMonitor = False

# MAGNETIC FIELD
# 3.8T 
#process.load("MagneticField.Engine.volumeBasedMagneticField_1103l_cfi") ##
# 3.0T
# process.VolumeBasedMagneticFieldESProducer.version = 'grid_1103l_071212_3t'
# process.ParametrizedMagneticFieldProducer.parameters.BValue = '3_0T'
# 2.0T
# process.VolumeBasedMagneticFieldESProducer.version = 'grid_1103l_071212_2t'
# process.ParametrizedMagneticFieldProducer.parameters.BValue = '2_0T'
# 0.0T
process.load("MagneticField.Engine.uniformMagneticField_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )
process.source = cms.Source("PoolSource",
                            firstEvent = cms.untracked.uint32(0),
                            skipEvents = cms.untracked.uint32(0),
                            fileNames = cms.untracked.vstring('/store/data/Commissioning08/Cosmics/RAW/v1/000/066/748/000FB8AC-7C9E-DD11-A844-001D09F24637.root')
                            )

                                                 
process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('INFO')),
                                    destinations = cms.untracked.vstring('cout')
                                    )

process.load("UserCode.DTDPGAnalysis.DTOfflineAnalyzer_cfi")
process.DTOfflineAnalyzer.rootFileName = 'DTAnalyzerTest_r58553.root'

process.load("UserCode.DTDPGAnalysis.STAOfflineAnalyzer_cfi")
process.STAOfflineAnalyzer.rootFileName = 'DTAnalyzerSTA_r58553.root'

process.load("UserCode.DTDPGAnalysis.DTEffOfflineAnalyzer_cfi")
process.DTEffOfflineAnalyzer.rootFileName = 'DTEffAnalyzer_r58553.root'


process.analysis = cms.Sequence(process.DTOfflineAnalyzer*process.DTEffOfflineAnalyzer*process.STAOfflineAnalyzer)
process.p        = cms.Path(process.dtunpacker*process.reco*process.globalreco*process.analysis)


