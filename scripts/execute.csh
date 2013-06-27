#!/bin/tcsh

source /afs/cern.ch/cms/sw/cmsset_default.csh
cd /afs/cern.ch/user/p/pellicci/scratch0/HH_rulez/CMSSW_2_2_4/src/GeneratorInterface/AlpgenInterface/test
project CMSSW
cmsenv
cmsRun $argv
#cmsRun /afs/cern.ch/user/p/pellicci/scratch0/HH_rulez/CMSSW_2_2_4/src/GeneratorInterface/AlpgenInterface/test/Alpgen_cfg.py
