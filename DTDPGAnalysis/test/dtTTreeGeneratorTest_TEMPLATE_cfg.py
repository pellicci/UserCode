import FWCore.ParameterSet.Config as cms

process = cms.Process("myDTNtuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load("RecoMuon.TrackingTools.MuonServiceProxy_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "GR_R_38X_V14::All"

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring('FINALNAME')
)

process.load("UserCode/DTDPGAnalysis/DTTTreGenerator_cfi")

process.p = cms.Path(process.myDTNtuple)


