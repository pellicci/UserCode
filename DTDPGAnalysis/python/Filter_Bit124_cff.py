import FWCore.ParameterSet.Config as cms

### For HLT, but problems when we prescale the HLT
###hltFilterL1_BscMinBiasOR_BtpxPlusORMinus = cms.EDFilter( "HLTHighLevel",
###        TriggerResultsTag  = cms.InputTag( 'TriggerResults', '', 'HLT' ),
###        HLTPaths = cms.vstring(
###            ##'HLT_L1Mu',
###            ##'HLT_L1MuOpen',
###            ##'HLT_Activity_DT',
###            ##'HLT_Activity_PixelClusters',
###            'HLT_L1_BscMinBiasOR_BptxPlusORMinus',
###            ),
###        eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
###        andOr = cms.bool( False ),  #True==> OR, False==> AND
###        throw = cms.bool( True )  # throw exception on unknown path names
###)

### From: L1Trigger.Skimmer.l1Filter_cfi
hltFilterL1_BscMinBiasOR_BtpxPlusORMinus = cms.EDFilter(
    "L1Filter",
    inputTag = cms.InputTag("gtDigis"),
    useAODRecord = cms.bool(False),
    useFinalDecision = cms.bool(False),
    algorithms = cms.vstring("L1_BscMinBiasOR_BptxPlusORMinus")
)


