import FWCore.ParameterSet.Config as cms

createDTDPGDQMSummary = cms.EDAnalyzer("DTDPGCreateSummary",
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

createDTDPGDQMWheelSummary = cms.EDAnalyzer("DTDPGCreateWheelSummary",
    # Input File Name
    rootFileName = cms.untracked.string(""),
    # Run Number
    runNumber = cms.untracked.int32(1)
)
createCheckDeadChannels = cms.EDAnalyzer("CheckDeadChannels",
    # Run Number
    runNumber = cms.untracked.int32(1),                                         
    # Reference Run for dead channels check  
    referenceRun = cms.untracked.int32(1) # from 06-12-2011 this is read from file                                 
)

createDTDPGAnalyzerSummary = cms.EDAnalyzer("DTDPGCreateAnalyzerSummary",
    # Histo generation flasg
    SummaryHistos    = cms.untracked.bool(True),
    SummaryWheelHistos = cms.untracked.bool(True),
    SummaryAllHistos   = cms.untracked.bool(True),
    # Input File Name
    rootFileName = cms.untracked.string(""),
    # Run Number
    runNumber = cms.untracked.int32(1)
)

createDQMSummaries = cms.Sequence( createDTDPGDQMSummary + createDTDPGDQMWheelSummary)
createSummaries = cms.Sequence( createDQMSummaries + createDTDPGAnalyzerSummary  )

