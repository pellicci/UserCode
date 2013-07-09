import FWCore.ParameterSet.Config as cms

DTEffOfflineAnalyzer = cms.EDAnalyzer("DTEffOfflineAnalyzer",
    LCT_RPC = cms.bool(True),
    DTLocalTriggerLabel = cms.string('dtunpacker'),
    recHits2DLabel = cms.string('dt2DSegments'),
    LCT_CSC = cms.bool(True),
    minHitsSegment = cms.int32(5),
    minCloseDist = cms.double(20.0),
    LCT_DT = cms.bool(True),
    recHits4DLabel = cms.string('dt4DSegments'),
    debug = cms.untracked.bool(False),
    rootFileName = cms.untracked.string('DTEffAnalyzer.root'),
    isMC = cms.bool(True),
    recHits1DLabel = cms.string('dt1DRecHits'),
    minChi2NormSegment = cms.double(20.0)
)
