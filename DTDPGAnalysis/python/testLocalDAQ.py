from EventFilter.DTTFRawToDigi.dttfunpacker_cfi import *

dttfunpacker.DTTF_FED_Source = 'rawDataCollector'  ## MWGR Feb12 

dtunpacker = cms.EDProducer("DTUnpackingModule",
     dataType = cms.string('DDU'),
     useStandardFEDid = cms.bool(True),
     inputLabel = cms.InputTag('rawDataCollector'), ## MWGR Feb12
     ##fedbyType = cms.bool(True),
     fedbyType = cms.bool(False), #Mini DAQ 
     dqmOnly = cms.bool(False),   ## needed for new versions, at least >356  
     readOutParameters = cms.PSet(
                         debug = cms.untracked.bool(True),
                         rosParameters = cms.PSet(
                             writeSC = cms.untracked.bool(True),
                             readingDDU = cms.untracked.bool(True),
                             performDataIntegrityMonitor = cms.untracked.bool(True),
                             readDDUIDfromDDU = cms.untracked.bool(True),
                             debug = cms.untracked.bool(False),
                             localDAQ = cms.untracked.bool(True)
                             ),
                         localDAQ = cms.untracked.bool(True),
                         performDataIntegrityMonitor = cms.untracked.bool(True) 
     )
)


###from Configuration.StandardSequences.Geometry_cff import *  ##  Deprecated in new versions > 53X
from Configuration.Geometry.GeometryIdeal_cff import *
from RecoLocalMuon.Configuration.RecoLocalMuonCosmics_cff import *
dt1DRecHits.dtDigiLabel = 'dtunpacker'

from RecoMuon.MuonSeedGenerator.CosmicMuonSeedProducer_cfi import *
CosmicMuonSeed.EnableCSCMeasurement=False

from RecoMuon.Configuration.RecoMuonCosmics_cff import *
##from RecoMuon.Configuration.RecoMuon_cff import *
from RecoVertex.BeamSpotProducer.BeamSpot_cff import *
from TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi import *


##cosmicMuonsBarrelOnly.TrajectoryBuilderParameters.EnableRPCMeasurement = False
## cosmicMuonsBarrelOnly doesn't exist on 44X, the only barrel used is 1leg
cosmicMuons.TrajectoryBuilderParameters.EnableRPCMeasurement = False
cosmicMuons.TrajectoryBuilderParameters.EnableCSCMeasurement = False

from CondCore.DBCommon.CondDBSetup_cfi import *

from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
####GlobalTag.globaltag = 'GR09_31X_V4P::All'  ## During CRAFT
####GlobalTag.globaltag = 'CRAFT09_R_V3::All'  ## For reprocessing with 327 (Sep09)
####GlobalTag.globaltag = 'GR09_P_V7COS::All'  ## for prompt reco on Cosmics PD
##GlobalTag.globaltag = 'GR09_P_V8_34X::All'  ## for prompt reco on Cosmics PD
##GlobalTag.globaltag = 'GR_P_V26::All'  ## For prompt data 44X 
##GlobalTag.globaltag = 'GR_E_V23::All'  ## For Express 50X 2012 data
##GlobalTag.globaltag = 'GR_E_V25::All'  ## For Express 52X 2012 data
##GlobalTag.globaltag = 'GR_E_V26::All'  ## For Express 53X 2012 data
##GlobalTag.globaltag = 'GR_E_V31::All'  ## For Express 53X 2012 data -need extra conf in the python file for Elec not used for the moment 
GlobalTag.globaltag = 'GR_E_V33A::All'  ## For Express 53X>=538HI 



unpackers  = cms.Sequence(dtunpacker + dttfunpacker)
reco       = cms.Sequence(dt1DRecHits * dt2DSegments * dt4DSegments)
###globalreco = cms.Sequence(CosmicMuonSeedBarrelOnly * offlineBeamSpot * cosmicMuonsBarrelOnly)
### Doesn't work we are not using the global for the moment to be fixed if needed. 
globalreco = cms.Sequence(CosmicMuonSeed*offlineBeamSpot*cosmicMuons)
##globalreco = cms.Sequence(standAloneMuonSeeds * offlineBeamSpot * standAloneMuons)
##globalreco = cms.Sequence(STAmuonrecoforcosmics)


#######################################################################################
# DT DPG DQM modules follow

from UserCode.DTDPGAnalysis.DTOfflineAnalyzer_Cosmics_cfi import *
DTOfflineAnalyzer.SALabel = 'cosmicMuons'
from UserCode.DTDPGAnalysis.STAOfflineAnalyzer_Cosmics_cfi import *
STAOfflineAnalyzer.SALabel = 'cosmicMuons'
from UserCode.DTDPGAnalysis.DTEffOfflineAnalyzer_cfi import *


from DQMServices.Components.MEtoEDMConverter_cfi import *
from DQMServices.Core.DQM_cfg import *

from DQM.DTMonitorModule.dtDataIntegrityTask_cfi import *

from DQM.DTMonitorModule.dtDigiTask_cfi import *
dtDigiMonitor.readDB = True
dtDigiMonitor.doNoiseOccupancies = True
dtDigiMonitor.doInTimeOccupancies = True

from DQM.DTMonitorModule.dtTriggerTask_cfi import *
dtTriggerMonitor.process_dcc = True
dtTriggerMonitor.dcc_label   = 'dttfunpacker'
dtTriggerMonitor.process_seg = True

from DQM.DTMonitorModule.dtEfficiencyTask_cfi import *
from DQM.DTMonitorModule.dtChamberEfficiencyTask_cfi import *
from DQM.DTMonitorModule.dtResolutionTask_cfi import *

from DQM.DTMonitorModule.dtSegmentTask_cfi import *
dtSegmentAnalysisMonitor.detailedAnalysis = True

dummyProducer = cms.EDProducer("ThingWithMergeProducer")

from DQM.L1TMonitor.L1TGMT_cfi import *

sources = cms.Sequence( dummyProducer + dtDigiMonitor + dtTriggerMonitor + dtEfficiencyMonitor + dtChamberEfficiencyMonitor + dtSegmentAnalysisMonitor + dtResolutionAnalysisMonitor + l1tGmt)

##analysis = cms.Sequence(DTOfflineAnalyzer + DTEffOfflineAnalyzer + STAOfflineAnalyzer)
analysis = cms.Sequence(DTOfflineAnalyzer + DTEffOfflineAnalyzer )

