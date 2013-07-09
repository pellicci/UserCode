import FWCore.ParameterSet.Config as cms

STAOfflineAnalyzer = cms.EDAnalyzer("STAOfflineAnalyzer",
    LCT_RPC = cms.bool(True),
    DTLocalTriggerLabel = cms.string('dtunpacker'),
    recHits2DLabel = cms.string('dt2DSegments'),
    LCT_CSC = cms.bool(True),
    doSA = cms.bool(True),
    PropagatorName = cms.string('SteppingHelixPropagator'),
    LCT_DT = cms.bool(True),
    recHits4DLabel = cms.string('dt4DSegments'),
    debug = cms.untracked.bool(False),
    rootFileName = cms.untracked.string('DTAnalyzerSTA.root'),
    SALabel = cms.string('cosmicMuonsBarrelOnly'),
    isMC = cms.bool(True),
    tTrigModeConfig = cms.untracked.PSet(
        vPropWire = cms.double(24.4),
        doTOFCorrection = cms.bool(False),
        ##tofCorrType = cms.int32(2),   ## old
        tofCorrType = cms.int32(0),
        ##kFactor = cms.double(-1.3),
        wirePropCorrType = cms.int32(0),
        doWirePropCorrection = cms.bool(False),
        doT0Correction = cms.bool(True),
        ##tTrigLabel = cms.string(''),   ##For Collisions
        tTrigLabel = cms.string('cosmics'),   ##For Cosmics
        debug = cms.untracked.bool(False)
    ),
    tTrigMode = cms.untracked.string('DTTTrigSyncFromDB'),
    recHits1DLabel = cms.string('dt1DRecHits')
)
