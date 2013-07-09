import FWCore.ParameterSet.Config as cms

process = cms.Process("HFA")

# ----------------------------------------------------------------------
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


# ----------------------------------------------------------------------
process.source = cms.Source(
    "PoolSource", 
    fileNames = cms.untracked.vstring(
    "/store/user/starodumov/bsmm/reco/reco-10000.root", 
    "/store/user/starodumov/bsmm/reco/reco-10001.root"
    )
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


# ----------------------------------------------------------------------
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR_R_42_V18::All')
#process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

# ----------------------------------------------------------------------
process.HepPDTESSource = cms.ESSource("HepPDTESSource",
    pdtFileName = cms.FileInPath('SimGeneral/HepPDTESSource/data/particle.tbl')
)

# ---------------------------------------------------------------------
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")

# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
process.bmmDump = cms.EDFilter(
    "HFDimuons",
    verbose = cms.untracked.int32(0), 
    muonsLabel = cms.untracked.InputTag("globalMuons"),
    tracksLabel = cms.untracked.string('generalTracks'),
    muonPt = cms.untracked.double(3.),
    massLow  = cms.untracked.double(60.), 
    massHigh = cms.untracked.double(120.)
)


# ----------------------------------------------------------------------
process.p = cms.Path(
    process.bmmDump
)
