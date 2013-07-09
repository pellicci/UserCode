import FWCore.ParameterSet.Config as cms

process = cms.Process("SkimMC")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/Services_cff')

process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.load("EventFilter.DTTFRawToDigi.dttfunpacker_cfi")
process.load("EventFilter.DTRawToDigi.dtunpackerDDUGlobal_cfi")
process.dtunpacker.readOutParameters.debug = False
process.dtunpacker.readOutParameters.rosParameters.debug = False

process.dttfunpacker.DTTF_FED_Source = 'rawDataCollector'
process.dtunpacker.inputLabel = 'rawDataCollector'

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "START39_V8::All"

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/data/p/pellicci/Root/B0ToJpsiMuMu.root'
    )
)

process.DTMuonSelection = cms.EDFilter("DTMuonSelection",
                                 src = cms.InputTag('muons'),
                                 dtSegmentLabel = cms.InputTag('dt4DSegments'),
                                 etaMin = cms.double(-1.25),
                                 etaMax = cms.double(1.25),
                                 ptMin = cms.double(3.)
)

process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *', 
        'keep *_dt4DSegments_*_*',
        'keep *_dt2DSegments_*_*',
        'keep *_dt1DRecHits_*_*',
#        'keep *_dttfunpacker_*_*',
#        'keep *_dtunpacker_*_*',
#        'keep *_gtDigis_*_*',
        'keep *_offlinePrimaryVertices_*_*',
        'keep *_cscSegments_*_*',
        'keep *_rpcRecHits_*_*',
        'keep *_muons_*_*',
        'keep recoTracks_standAloneMuons_*_*',
        'keep recoTrackExtras_standAloneMuons_*_*',
        'keep TrackingRecHitsOwned_standAloneMuons_*_*', 
        'keep recoTracks_globalMuons_*_*',
        'keep recoTrackExtras_globalMuons_*_*',
        'keep TrackingRecHitsOwned_globalMuons_*_*',
        'keep recoTracks_generalTracks_*_*',
        'keep *_offlineBeamSpot_*_*',
        'keep *_TriggerResults_*_*',
	'keep *_MEtoEDMConverter_*_*'),
    fileName = cms.untracked.string('DTFiltered.root'),
     # put this if you have a filter
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    ),
                                 
)

process.p = cms.Path(process.DTMuonSelection) # * process.dtunpacker * process.dttfunpacker)
process.e = cms.EndPath(process.output)
