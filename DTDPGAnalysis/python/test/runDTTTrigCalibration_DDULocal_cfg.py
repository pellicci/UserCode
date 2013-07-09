import FWCore.ParameterSet.Config as cms

process = cms.Process("DTTTrigCalib")

process.load("UserCode.DTDPGAnalysis.dt_dpganalysis_common_cff")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("DaqSource",
                            readerPluginName = cms.untracked.string("DTDDUFileReader"),
                            evtsPerLS = cms.untracked.uint32(1000),
                            readerPset = cms.untracked.PSet( 
    fileName = cms.untracked.string("/data/c/cerminar/data/local/testYB0_S2S3_vmepcs2g18-16_r72328.i0"))
                            # skipEvents = cms.untracked.int32(),
                            # numberOfHeaderWords = cms.untracked.int32(10)
                            )

# replace unpacker's parameters to run on local DDU data
import EventFilter.DTRawToDigi.dtunpackerDDULocal_cfi as dtunpacker_module
process.dtunpackerDDU = dtunpacker_module.dtunpacker.clone()
process.dtunpackerDDU.readOutParameters.performDataIntegrityMonitor = True
process.dtunpackerDDU.readOutParameters.rosParameters.performDataIntegrityMonitor = True

process.MessageLogger = cms.Service("MessageLogger",
                                    debugModules = cms.untracked.vstring('*'),
                                    destinations = cms.untracked.vstring('cout'),
                                    categories = cms.untracked.vstring('DTDigiTask'), 
                                    cout = cms.untracked.PSet(threshold = cms.untracked.string('WARNING'),
                                                              noLineBreaks = cms.untracked.bool(False),
                                                              DEBUG = cms.untracked.PSet(
                                                                      limit = cms.untracked.int32(0)),
                                                              INFO = cms.untracked.PSet(
                                                                      limit = cms.untracked.int32(0)),
                                                              DTDigiTask = cms.untracked.PSet(
                                                                      limit = cms.untracked.int32(-1))
                                                              )
                                    )

 
process.PoolDBOutputService = cms.Service("PoolDBOutputService",
                                          DBParameters = cms.PSet(authenticationPath
                                                                  = cms.untracked.string('/afs/cern.ch/cms/DB/conddb')
                                                                  ),
                                          authenticationMethod = cms.untracked.uint32(0),
                                          connect = cms.string('sqlite_file:ttrig_DDULocal.db'),
                                          toPut = cms.VPSet(cms.PSet(record = cms.string('DTTtrigRcd'),
                                                                     tag = cms.string('ttrig')
                                                                     ))
                                          )

#Module to calibrate ttrig
process.ttrigcalib = cms.EDAnalyzer("DTTTrigCalibration",
                                    # Switch on/off the verbosity
                                    debug = cms.untracked.bool(False),
                                    # Label to retrieve DT digis from the event
                                    digiLabel = cms.untracked.string("dtunpackerDDU"),
                                    # Name of the ROOT file which will contain the time boxes
                                    rootFileName = cms.untracked.string("DTTimeBoxes.root"),
                                    # Switch on/off the subtraction of t0 from pulses
                                    doSubtractT0 = cms.untracked.bool(True),
                                    # Switch on/off the DB writing
                                    fitAndWrite = cms.untracked.bool(True),
                                    # Switch on/off the check of noisy channels
                                    checkNoisyChannels = cms.untracked.bool(True),
                                    # Max number of digi per layer to reject a chamber
                                    maxDigiPerLayer = cms.untracked.int32(10),
                                    # Module for t0 subtraction
                                    tTrigMode = cms.untracked.string('DTTTrigSyncT0Only'),
                                    # Parameter set for t0 subtraction module
                                    tTrigModeConfig = cms.untracked.PSet(debug = cms.untracked.bool(False))
                                    )    

process.p = cms.Path( process.dtunpackerDDU+ process.ttrigcalib)
