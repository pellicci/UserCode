from EventFilter.DTTFRawToDigi.dttfunpacker_cfi import *
dttfunpacker.DTTF_FED_Source = 'rawDataCollector'  ## MWGR Feb12 

dtunpacker = cms.EDFilter("DTUnpackingModule",
                          dataType = cms.string('DDU'),
                          ##inputLabel = cms.InputTag('source'), ## needed for new versions, at least >356  
                          inputLabel = cms.InputTag('rawDataCollector'), ## MWGR Feb12
                          ###useStandardFEDid = cms.untracked.bool(True),
                          useStandardFEDid = cms.bool(True),
                          ###fedbyType = cms.untracked.bool(True),
                          fedbyType = cms.bool(False), ## tracked for new versions, at least >356, and also false ???? 
                          dqmOnly = cms.bool(False),   ## needed for new versions, at least >356  
                          readOutParameters = cms.PSet(debug = cms.untracked.bool(False),
                                                       rosParameters = cms.PSet(writeSC = cms.untracked.bool(True),
                                                                                readingDDU = cms.untracked.bool(True),
                                                                                performDataIntegrityMonitor = cms.untracked.bool(True),
                                                                                readDDUIDfromDDU = cms.untracked.bool(True),
                                                                                debug = cms.untracked.bool(False),
                                                                                localDAQ = cms.untracked.bool(False)
                                                                                ),
                                                       localDAQ = cms.untracked.bool(False),
                                                       performDataIntegrityMonitor = cms.untracked.bool(True)
                                                       )
                          )



###from Configuration.StandardSequences.Geometry_cff import *  ##  Deprecated in new versions > 53X
from Configuration.Geometry.GeometryIdeal_cff import *
from RecoLocalMuon.Configuration.RecoLocalMuon_cff import *
##dt1DRecHits.dtDigiLabel = 'dtunpacker'
dt1DRecHits.dtDigiLabel = 'muonDTDigis'

from RecoMuon.Configuration.RecoMuon_cff import *
from RecoVertex.BeamSpotProducer.BeamSpot_cff import *
from TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi import *

###cosmicMuonsBarrelOnly.TrajectoryBuilderParameters.EnableRPCMeasurement = False
ancientMuonSeed.EnableCSCMeasurement = False
###ancientMuonSeed.EnableRPCMeasurement = False

standAloneMuons.STATrajBuilderParameters.FilterParameters.EnableCSCMeasurement = False
standAloneMuons.STATrajBuilderParameters.FilterParameters.EnableRPCMeasurement = False
standAloneMuons.STATrajBuilderParameters.BWFilterParameters.EnableCSCMeasurement = False
standAloneMuons.STATrajBuilderParameters.BWFilterParameters.EnableRPCMeasurement = False


from CondCore.DBCommon.CondDBSetup_cfi import *

from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
####GlobalTag.globaltag = 'GR09_31X_V4P::All'  ## During CRAFT
####GlobalTag.globaltag = 'CRAFT09_R_V3::All'  ## For reprocessing with 327 (Sep09)
####GlobalTag.globaltag = 'GR09_P_V7::All'  ## For prompt reco on all PD's except Cosmics
##GlobalTag.globaltag = 'GR10_P_V2::All'  ## For prompt reco on all PD's except Cosmics
##GlobalTag.globaltag = 'GR10_P_V5::All'  ## For prompt reco on all PD's except Cosmics
##GlobalTag.globaltag = 'GR10_P_V6::All'  ## For prompt reco on all PD's except Cosmics
##GlobalTag.globaltag = 'GR_E_V23::All'  ## For Express 50X 2012 data
##GlobalTag.globaltag = 'GR_E_V25::All'  ## For Express 52X 2012 data
##GlobalTag.globaltag = 'GR_E_V26::All'  ## For Express 53X 2012 data
##GlobalTag.globaltag = 'GR_E_V31::All'  ## For Express 53X 2012 data -need extra conf in the python file for Elec not used for the moment 
GlobalTag.globaltag = 'GR_E_V33A::All'  ## For Express 53X>=538HI 



unpackers  = cms.Sequence(dtunpacker + dttfunpacker)
recoonly1D = cms.Sequence(dt1DRecHits)
reco       = cms.Sequence(dt1DRecHits * dt2DSegments * dt4DSegments)
##globalreco = cms.Sequence(CosmicMuonSeedBarrelOnly * offlineBeamSpot * cosmicMuonsBarrelOnly)
globalreco = cms.Sequence(standAloneMuonSeeds * offlineBeamSpot * standAloneMuons)

#######################################################################################
# DT DPG DQM modules follow

from UserCode.DTDPGAnalysis.DTOfflineAnalyzer_cfi import *
DTOfflineAnalyzer.SALabel = 'standAloneMuons'
from UserCode.DTDPGAnalysis.STAOfflineAnalyzer_cfi import *
STAOfflineAnalyzer.SALabel = 'standAloneMuons'

from UserCode.DTDPGAnalysis.DTEffOfflineAnalyzer_cfi import *


from DQMServices.Components.MEtoEDMConverter_cfi import *
from DQMServices.Core.DQM_cfg import *

from DQM.DTMonitorModule.dtDataIntegrityTask_cfi import *

from DQM.DTMonitorModule.dtDigiTask_cfi import *
dtDigiMonitor.readDB = True
dtDigiMonitor.doNoiseOccupancies = True
dtDigiMonitor.doInTimeOccupancies = True
dtDigiMonitor.dtDigiLabel='muonDTDigis'

from DQM.DTMonitorModule.dtTriggerTask_cfi import *
dtTriggerMonitor.process_dcc = True
dtTriggerMonitor.dcc_label   = 'dttfunpacker'
dtTriggerMonitor.process_seg = True
dtTriggerMonitor.ros_label = 'muonDTDigis'

from DQM.DTMonitorModule.dtEfficiencyTask_cfi import *
from DQM.DTMonitorModule.dtChamberEfficiencyTask_cfi import *
from DQM.DTMonitorModule.dtResolutionTask_cfi import *


from DQM.DTMonitorModule.dtSegmentTask_cfi import *
dtSegmentAnalysisMonitor.detailedAnalysis = True

dummyProducer = cms.EDProducer("ThingWithMergeProducer")


sources = cms.Sequence( dummyProducer + dtDigiMonitor + dtTriggerMonitor + dtEfficiencyMonitor + dtChamberEfficiencyMonitor + dtSegmentAnalysisMonitor + dtResolutionAnalysisMonitor)

analysis = cms.Sequence(DTOfflineAnalyzer + DTEffOfflineAnalyzer + STAOfflineAnalyzer)

