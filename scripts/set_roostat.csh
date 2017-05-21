#setenv ROOTSYS /afs/cern.ch/sw/lcg/external/root/5.21.02/slc4_ia32_gcc34/root/
setenv ROOTSYS /afs/cern.ch/sw/lcg/app/releases/ROOT/5.22.00/slc4_ia32_gcc34/root/

setenv LD_LIBRARY_PATH $ROOTSYS/lib
set path=($path $ROOTSYS/bin)

setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/afs/cern.ch/user/p/pellicci/scratch0/RooStatCms/RooStat/HiggsAnalysis/RooStatsCms/lib/
