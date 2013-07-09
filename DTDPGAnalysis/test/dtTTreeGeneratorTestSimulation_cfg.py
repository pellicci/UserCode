import FWCore.ParameterSet.Config as cms

process = cms.Process("myDTNtuple")

#only for RAW-RECO
process.load("EventFilter.DTRawToDigi.dtunpackerDDUGlobal_cfi")
process.dtunpacker.readOutParameters.debug = False
process.dtunpacker.readOutParameters.rosParameters.debug = False
process.load("EventFilter.DTTFRawToDigi.dttfunpacker_cfi")

#for RAW
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.load("RecoMuon.TrackingTools.MuonServiceProxy_cff")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

process.GlobalTag.globaltag = "START38_V13::All"

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_10_1_JCn.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_12_1_DSs.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_13_1_7aC.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_13_2_Mra.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_14_1_Cj9.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_15_1_IYn.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_17_1_ara.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_19_1_0nQ.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_1_1_wFC.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_20_1_Dk7.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_21_1_Gc8.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_22_1_B6U.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_23_1_Qkc.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_24_1_wWJ.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_25_1_DKS.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_26_1_Shf.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_2_1_jfl.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_31_1_vYB.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_37_1_BO1.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_38_1_uL8.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_3_1_wlk.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_41_1_p5M.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_47_1_YCo.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_48_1_fWC.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_49_1_WsN.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_4_1_jh5.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_51_1_u0O.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_52_1_NC1.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_53_1_Bfh.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_54_1_JD4.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_59_1_pvg.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_5_1_SRP.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_62_1_e2Y.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_6_1_q58.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_7_1_rMK.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_8_1_rNa.root',
'castor:/castor/cern.ch/user/p/pellicci/DPG/Dumper/MC/DTFiltered_9_1_OnF.root'
    )
)

process.load("UserCode/DTDPGAnalysis/DTTTreGenerator_cfi")
process.myDTNtuple.runOnSimulation = True
process.myDTNtuple.outputFile = "/data/p/pellicci/DPG/Dumper/rootuples/DTTree_MC.root"

#for RAW
#process.p = cms.Path(process.RawToDigi * process.dtunpacker * process.dttfunpacker * process.reconstruction * process.myDTNtuple)

#for RAW-RECO
process.p = cms.Path(process.muonDTDigis * process.myDTNtuple)

#for RECO and SKIM
process.p = cms.Path(process.myDTNtuple)
