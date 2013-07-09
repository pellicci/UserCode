import FWCore.ParameterSet.Config as cms

createDTDPGSummary = cms.EDAnalyzer("DTDPGCreateSummary",
    # Histo generation flasg
    DataIntegrityHistos = cms.untracked.bool(True),
    DigiHistos = cms.untracked.bool(True),
    RecoHistos = cms.untracked.bool(True),
    ResoHistos = cms.untracked.bool(True),
    TriggerHistos = cms.untracked.bool(True),
    EfficiencyHistos = cms.untracked.bool(True),
    TestPulseHistos = cms.untracked.bool(False),
    # Input File Name
    rootFileName = cms.untracked.string(""),
    # Run Number
    runNumber = cms.untracked.int32(1)
)

createDTDPGWheelSummary = cms.EDAnalyzer("DTDPGCreateWheelSummary",
    # Input File Name
    rootFileName = cms.untracked.string(""),
    # Run Number
    runNumber = cms.untracked.int32(1)
)

createSummary = cms.Sequence( createDTDPGSummary + createDTDPGWheelSummary)
