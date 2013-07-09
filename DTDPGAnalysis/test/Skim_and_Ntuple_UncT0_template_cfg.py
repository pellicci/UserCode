import FWCore.ParameterSet.Config as cms

process = cms.Process("Skim")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/Services_cff')

process.load('Configuration/StandardSequences/Geometry_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cff")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')

process.load("EventFilter.DTTFRawToDigi.dttfunpacker_cfi")
process.load("EventFilter.DTTFRawToDigi.dttfpacker_cfi")
process.load("EventFilter.DTRawToDigi.dtunpackerDDUGlobal_cfi")
process.dtunpacker.readOutParameters.debug = False
process.dtunpacker.readOutParameters.rosParameters.debug = False
process.dttfunpacker.DTTF_FED_Source = "rawDataCollector"

#for RAW
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load("RecoMuon.TrackingTools.MuonServiceProxy_cff")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "GR_P_V32::All"

# for the emulator
process.load("L1TriggerConfig.DTTPGConfigProducers.L1DTTPGConfigFromDB_cff")
process.load("L1Trigger.DTTrigger.dtTriggerPrimitiveDigis_cfi")

process.load('EventFilter.ScalersRawToDigi.ScalersRawToDigi_cfi')
process.load('RecoLuminosity.LumiProducer.lumiProducer_cfi')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",

    fileNames = cms.untracked.vstring(
    RECOFILES
    ),
                           secondaryFileNames = cms.untracked.vstring(
    RAWFILES
    )

)

#this is to select collisions
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

process.noscraping = cms.EDFilter("FilterOutScraping",
                                  applyfilter = cms.untracked.bool(True),
                                  debugOn = cms.untracked.bool(False),
                                  numtrack = cms.untracked.uint32(10),
                                  thresh = cms.untracked.double(0.25)
)

process.DTMuonSelection = cms.EDFilter("DTMuonSelection",
                                 src = cms.InputTag('muons'),
                                 dtSegmentLabel = cms.InputTag('dt4DSegments'),
                                 etaMin = cms.double(-1.25),
                                 etaMax = cms.double(1.25),
                                 ptMin = cms.double(3.)
)

process.load("RecoLocalMuon.DTRecHit.DTLinearDriftFromDBAlgo_cfi")
process.DTLinearDriftFromDBAlgo.recAlgoConfig.tTrigModeConfig.doTOFCorrection = cms.bool(False)
process.DTLinearDriftFromDBAlgo.recAlgoConfig.tTrigModeConfig.doWirePropCorrection = cms.bool(False)

process.load("RecoLocalMuon.DTSegment.dt4DSegments_CombPatternReco4D_LinearDriftFromDB_cfi")
process.mySegments = process.dt4DSegments.clone()
process.mySegments.Reco4DAlgoConfig.perform_delta_rejecting = cms.bool(False)
process.mySegments.Reco4DAlgoConfig.Reco2DAlgoConfig.recAlgoConfig.tTrigModeConfig.doWirePropCorrection = cms.bool(False)
process.mySegments.Reco4DAlgoConfig.Reco2DAlgoConfig.recAlgoConfig.tTrigModeConfig.doTOFCorrection = cms.bool(False)
process.mySegments.Reco4DAlgoConfig.recAlgoConfig.tTrigModeConfig.doWirePropCorrection = cms.bool(False)
process.mySegments.Reco4DAlgoConfig.recAlgoConfig.tTrigModeConfig.doTOFCorrection = cms.bool(False)



process.load("UserCode/DTDPGAnalysis/DTTTreGenerator_cfi")
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.myDTNtuple.outputFile = "FILENAME"
process.myDTNtuple.dtTrigSimDCCLabel = cms.InputTag("dtTriggerPrimitiveDigis")
process.myDTNtuple.dtSegmentLabel = cms.InputTag("mySegments")
process.p = cms.Path(process.DTMuonSelection *  process.dtunpacker * process.dttfunpacker * process.scalersRawToDigi * process.muonDTDigis * process.mySegments * process.dtTriggerPrimitiveDigis + process.myDTNtuple)

