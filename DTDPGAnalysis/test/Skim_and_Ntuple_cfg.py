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
process.GlobalTag.globaltag = "GR_P_V39::All"

# for the emulator
process.load("L1TriggerConfig.DTTPGConfigProducers.L1DTTPGConfigFromDB_cff")
process.load("L1Trigger.DTTrigger.dtTriggerPrimitiveDigis_cfi")

process.load('EventFilter.ScalersRawToDigi.ScalersRawToDigi_cfi')
process.load('RecoLuminosity.LumiProducer.lumiProducer_cfi')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",

    fileNames = cms.untracked.vstring(
    '/store/data/Run2012B/SingleMu/RAW-RECO/ZMu-PromptSkim-v2/000/196/239/0000/6073CE2F-18BA-E111-86E5-90E6BA442F0F.root'
    #RECOFILES
    ),
#                           secondaryFileNames = cms.untracked.vstring(
#    RAWFILES
#    )

)
process.DTMuonSelection = cms.EDFilter("DTMuonSelection",
                                 src = cms.InputTag('muons'),
                                 dtSegmentLabel = cms.InputTag('dt4DSegments'),
                                 etaMin = cms.double(-1.25),
                                 etaMax = cms.double(1.25),
                                 ptMin = cms.double(3.)
                                       )


process.load("UserCode/DTDPGAnalysis/DTTTreGenerator_cfi")
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.myDTNtuple.outputFile = "DTntuple.root"
process.myDTNtuple.dtTrigSimDCCLabel = cms.InputTag("dtTriggerPrimitiveDigis")

process.p = cms.Path(process.DTMuonSelection *  process.dtunpacker * process.dttfunpacker * process.scalersRawToDigi * process.muonDTDigis * process.dtTriggerPrimitiveDigis + process.myDTNtuple)
