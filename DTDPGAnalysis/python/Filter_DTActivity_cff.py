import FWCore.ParameterSet.Config as cms

hltFilterDTActivity = cms.EDFilter( "HLTHighLevel",
        TriggerResultsTag  = cms.InputTag( 'TriggerResults', '', 'HLT' ),
        HLTPaths = cms.vstring(
            'HLT_Activity_DT',
            ),
        eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
        andOr = cms.bool( False ),  #True==> OR, False==> AND
        throw = cms.bool( True )  # throw exception on unknown path names
)
