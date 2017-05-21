//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 24 08:36:28 2007 by ROOT version 5.14/00e
// from TChain fitParData/
//////////////////////////////////////////////////////////

#ifndef SumToys_h
#define SumToys_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class SumToys {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Double_t        BMinus;
   Double_t        BMinus_err;
   Double_t        BMinus_aerr_lo;
   Double_t        BMinus_aerr_hi;
   Double_t        BZero;
   Double_t        BZero_err;
   Double_t        BZero_aerr_lo;
   Double_t        BZero_aerr_hi;
   Double_t        Kst1680_amp;
   Double_t        Kst1680_amp_err;
   Double_t        Kst1680_amp_aerr_lo;
   Double_t        Kst1680_amp_aerr_hi;
   Double_t        Kst1680_phase;
   Double_t        Kst1680_phase_err;
   Double_t        Kst1680_phase_aerr_lo;
   Double_t        Kst1680_phase_aerr_hi;
   Double_t        Kst2m1430_amp;
   Double_t        Kst2m1430_amp_err;
   Double_t        Kst2m1430_amp_aerr_lo;
   Double_t        Kst2m1430_amp_aerr_hi;
   Double_t        Kst2m1430_phase;
   Double_t        Kst2m1430_phase_err;
   Double_t        Kst2m1430_phase_aerr_lo;
   Double_t        Kst2m1430_phase_aerr_hi;
   Double_t        Kst2z1430_amp;
   Double_t        Kst2z1430_amp_err;
   Double_t        Kst2z1430_amp_aerr_lo;
   Double_t        Kst2z1430_amp_aerr_hi;
   Double_t        Kst2z1430_phase;
   Double_t        Kst2z1430_phase_err;
   Double_t        Kst2z1430_phase_aerr_lo;
   Double_t        Kst2z1430_phase_aerr_hi;
   Double_t        Kstm1410_amp;
   Double_t        Kstm1410_amp_err;
   Double_t        Kstm1410_amp_aerr_lo;
   Double_t        Kstm1410_amp_aerr_hi;
   Double_t        Kstm1410_phase;
   Double_t        Kstm1410_phase_err;
   Double_t        Kstm1410_phase_aerr_lo;
   Double_t        Kstm1410_phase_aerr_hi;
   Double_t        Kstm1430_CLEO_amp;
   Double_t        Kstm1430_CLEO_amp_err;
   Double_t        Kstm1430_CLEO_amp_aerr_lo;
   Double_t        Kstm1430_CLEO_amp_aerr_hi;
   Double_t        Kstm1430_CLEO_phase;
   Double_t        Kstm1430_CLEO_phase_err;
   Double_t        Kstm1430_CLEO_phase_aerr_lo;
   Double_t        Kstm1430_CLEO_phase_aerr_hi;
   Double_t        Kstm1430_amp;
   Double_t        Kstm1430_amp_err;
   Double_t        Kstm1430_amp_aerr_lo;
   Double_t        Kstm1430_amp_aerr_hi;
   Double_t        Kstm1430_mass;
   Double_t        Kstm1430_mass_err;
   Double_t        Kstm1430_mass_aerr_lo;
   Double_t        Kstm1430_mass_aerr_hi;
   Double_t        Kstm1430_phase;
   Double_t        Kstm1430_phase_err;
   Double_t        Kstm1430_phase_aerr_lo;
   Double_t        Kstm1430_phase_aerr_hi;
   Double_t        Kstm1430_width;
   Double_t        Kstm1430_width_err;
   Double_t        Kstm1430_width_aerr_lo;
   Double_t        Kstm1430_width_aerr_hi;
   Double_t        Kstminus_amp;
   Double_t        Kstminus_amp_err;
   Double_t        Kstminus_amp_aerr_lo;
   Double_t        Kstminus_amp_aerr_hi;
   Double_t        Kstminus_mass;
   Double_t        Kstminus_mass_err;
   Double_t        Kstminus_mass_aerr_lo;
   Double_t        Kstminus_mass_aerr_hi;
   Double_t        Kstminus_phase;
   Double_t        Kstminus_phase_err;
   Double_t        Kstminus_phase_aerr_lo;
   Double_t        Kstminus_phase_aerr_hi;
   Double_t        Kstminus_width;
   Double_t        Kstminus_width_err;
   Double_t        Kstminus_width_aerr_lo;
   Double_t        Kstminus_width_aerr_hi;
   Double_t        Kstz1410_amp;
   Double_t        Kstz1410_amp_err;
   Double_t        Kstz1410_amp_aerr_lo;
   Double_t        Kstz1410_amp_aerr_hi;
   Double_t        Kstz1410_phase;
   Double_t        Kstz1410_phase_err;
   Double_t        Kstz1410_phase_aerr_lo;
   Double_t        Kstz1410_phase_aerr_hi;
   Double_t        Kstz1430_CLEO_amp;
   Double_t        Kstz1430_CLEO_amp_err;
   Double_t        Kstz1430_CLEO_amp_aerr_lo;
   Double_t        Kstz1430_CLEO_amp_aerr_hi;
   Double_t        Kstz1430_CLEO_phase;
   Double_t        Kstz1430_CLEO_phase_err;
   Double_t        Kstz1430_CLEO_phase_aerr_lo;
   Double_t        Kstz1430_CLEO_phase_aerr_hi;
   Double_t        Kstz1430_amp;
   Double_t        Kstz1430_amp_err;
   Double_t        Kstz1430_amp_aerr_lo;
   Double_t        Kstz1430_amp_aerr_hi;
   Double_t        Kstz1430_mass;
   Double_t        Kstz1430_mass_err;
   Double_t        Kstz1430_mass_aerr_lo;
   Double_t        Kstz1430_mass_aerr_hi;
   Double_t        Kstz1430_phase;
   Double_t        Kstz1430_phase_err;
   Double_t        Kstz1430_phase_aerr_lo;
   Double_t        Kstz1430_phase_aerr_hi;
   Double_t        Kstz1430_width;
   Double_t        Kstz1430_width_err;
   Double_t        Kstz1430_width_aerr_lo;
   Double_t        Kstz1430_width_aerr_hi;
   Double_t        Kstz1680_amp;
   Double_t        Kstz1680_amp_err;
   Double_t        Kstz1680_amp_aerr_lo;
   Double_t        Kstz1680_amp_aerr_hi;
   Double_t        Kstz1680_phase;
   Double_t        Kstz1680_phase_err;
   Double_t        Kstz1680_phase_aerr_lo;
   Double_t        Kstz1680_phase_aerr_hi;
   Double_t        Kstzero_amp;
   Double_t        Kstzero_amp_err;
   Double_t        Kstzero_amp_aerr_lo;
   Double_t        Kstzero_amp_aerr_hi;
   Double_t        Kstzero_mass;
   Double_t        Kstzero_mass_err;
   Double_t        Kstzero_mass_aerr_lo;
   Double_t        Kstzero_mass_aerr_hi;
   Double_t        Kstzero_phase;
   Double_t        Kstzero_phase_err;
   Double_t        Kstzero_phase_aerr_lo;
   Double_t        Kstzero_phase_aerr_hi;
   Double_t        Kstzero_width;
   Double_t        Kstzero_width_err;
   Double_t        Kstzero_width_aerr_lo;
   Double_t        Kstzero_width_aerr_hi;
   Double_t        N1;
   Double_t        N1_err;
   Double_t        N1_aerr_lo;
   Double_t        N1_aerr_hi;
   Double_t        N2;
   Double_t        N2_err;
   Double_t        N2_aerr_lo;
   Double_t        N2_aerr_hi;
   Double_t        Ncomb;
   Double_t        Ncomb_err;
   Double_t        Ncomb_aerr_lo;
   Double_t        Ncomb_aerr_hi;
   Double_t        Nmis;
   Double_t        Nmis_err;
   Double_t        Nmis_aerr_lo;
   Double_t        Nmis_aerr_hi;
   Double_t        NonReson_amp;
   Double_t        NonReson_amp_err;
   Double_t        NonReson_amp_aerr_lo;
   Double_t        NonReson_amp_aerr_hi;
   Double_t        NonReson_phase;
   Double_t        NonReson_phase_err;
   Double_t        NonReson_phase_aerr_lo;
   Double_t        NonReson_phase_aerr_hi;
   Double_t        Nsig;
   Double_t        Nsig_err;
   Double_t        Nsig_aerr_lo;
   Double_t        Nsig_aerr_hi;
   Double_t        RMinus;
   Double_t        RMinus_err;
   Double_t        RMinus_aerr_lo;
   Double_t        RMinus_aerr_hi;
   Double_t        RZero;
   Double_t        RZero_err;
   Double_t        RZero_aerr_lo;
   Double_t        RZero_aerr_hi;
   Double_t        Rho1450_amp;
   Double_t        Rho1450_amp_err;
   Double_t        Rho1450_amp_aerr_lo;
   Double_t        Rho1450_amp_aerr_hi;
   Double_t        Rho1450_phase;
   Double_t        Rho1450_phase_err;
   Double_t        Rho1450_phase_aerr_lo;
   Double_t        Rho1450_phase_aerr_hi;
   Double_t        Rho1700_amp;
   Double_t        Rho1700_amp_err;
   Double_t        Rho1700_amp_aerr_lo;
   Double_t        Rho1700_amp_aerr_hi;
   Double_t        Rho1700_mass;
   Double_t        Rho1700_mass_err;
   Double_t        Rho1700_mass_aerr_lo;
   Double_t        Rho1700_mass_aerr_hi;
   Double_t        Rho1700_phase;
   Double_t        Rho1700_phase_err;
   Double_t        Rho1700_phase_aerr_lo;
   Double_t        Rho1700_phase_aerr_hi;
   Double_t        Rho1700_width;
   Double_t        Rho1700_width_err;
   Double_t        Rho1700_width_aerr_lo;
   Double_t        Rho1700_width_aerr_hi;
   Double_t        Rho_amp;
   Double_t        Rho_amp_err;
   Double_t        Rho_amp_aerr_lo;
   Double_t        Rho_amp_aerr_hi;
   Double_t        Rho_mass;
   Double_t        Rho_mass_err;
   Double_t        Rho_mass_aerr_lo;
   Double_t        Rho_mass_aerr_hi;
   Double_t        Rho_phase;
   Double_t        Rho_phase_err;
   Double_t        Rho_phase_aerr_lo;
   Double_t        Rho_phase_aerr_hi;
   Double_t        Rho_width;
   Double_t        Rho_width_err;
   Double_t        Rho_width_aerr_lo;
   Double_t        Rho_width_aerr_hi;
   Double_t        aMinus;
   Double_t        aMinus_err;
   Double_t        aMinus_aerr_lo;
   Double_t        aMinus_aerr_hi;
   Double_t        aZero;
   Double_t        aZero_err;
   Double_t        aZero_aerr_lo;
   Double_t        aZero_aerr_hi;
   Double_t        bias;
   Double_t        bias_err;
   Double_t        bias_aerr_lo;
   Double_t        bias_aerr_hi;
   Double_t        c1;
   Double_t        c1_err;
   Double_t        c1_aerr_lo;
   Double_t        c1_aerr_hi;
   Double_t        c1err;
   Double_t        c1pull;
   Double_t        c2;
   Double_t        c2_err;
   Double_t        c2_aerr_lo;
   Double_t        c2_aerr_hi;
   Double_t        c2err;
   Double_t        c2pull;
   Double_t        c1m;
   Double_t        c1m_err;
   Double_t        c1m_aerr_lo;
   Double_t        c1m_aerr_hi;
   Double_t        c1p;
   Double_t        c1p_err;
   Double_t        c1p_aerr_lo;
   Double_t        c1p_aerr_hi;
   Double_t        c2m;
   Double_t        c2m_err;
   Double_t        c2m_aerr_lo;
   Double_t        c2m_aerr_hi;
   Double_t        c2p;
   Double_t        c2p_err;
   Double_t        c2p_aerr_lo;
   Double_t        c2p_aerr_hi;
   Double_t        one;
   Double_t        one_err;
   Double_t        one_aerr_lo;
   Double_t        one_aerr_hi;
   Double_t        phiBMinus;
   Double_t        phiBMinus_err;
   Double_t        phiBMinus_aerr_lo;
   Double_t        phiBMinus_aerr_hi;
   Double_t        phiBZero;
   Double_t        phiBZero_err;
   Double_t        phiBZero_aerr_lo;
   Double_t        phiBZero_aerr_hi;
   Double_t        phiRMinus;
   Double_t        phiRMinus_err;
   Double_t        phiRMinus_aerr_lo;
   Double_t        phiRMinus_aerr_hi;
   Double_t        phiRZero;
   Double_t        phiRZero_err;
   Double_t        phiRZero_aerr_lo;
   Double_t        phiRZero_aerr_hi;
   Double_t        rMinus;
   Double_t        rMinus_err;
   Double_t        rMinus_aerr_lo;
   Double_t        rMinus_aerr_hi;
   Double_t        rZero;
   Double_t        rZero_err;
   Double_t        rZero_aerr_lo;
   Double_t        rZero_aerr_hi;
   Double_t        scalefact1;
   Double_t        scalefact1_err;
   Double_t        scalefact1_aerr_lo;
   Double_t        scalefact1_aerr_hi;
   Double_t        scalefact2;
   Double_t        scalefact2_err;
   Double_t        scalefact2_aerr_lo;
   Double_t        scalefact2_aerr_hi;
   Double_t        scalefact3;
   Double_t        scalefact3_err;
   Double_t        scalefact3_aerr_lo;
   Double_t        scalefact3_aerr_hi;
   Double_t        tau;
   Double_t        tau_err;
   Double_t        tau_aerr_lo;
   Double_t        tau_aerr_hi;
   Double_t        NLL;
   Double_t        NLL_err;
   Double_t        NLL_aerr_lo;
   Double_t        NLL_aerr_hi;
   Double_t        BMinuserr;
   Double_t        BMinuspull;
   Double_t        BZeroerr;
   Double_t        BZeropull;
   Double_t        Kst1680_amperr;
   Double_t        Kst1680_amppull;
   Double_t        Kst1680_phaseerr;
   Double_t        Kst1680_phasepull;
   Double_t        Kst2m1430_amperr;
   Double_t        Kst2m1430_amppull;
   Double_t        Kst2m1430_phaseerr;
   Double_t        Kst2m1430_phasepull;
   Double_t        Kst2z1430_amperr;
   Double_t        Kst2z1430_amppull;
   Double_t        Kst2z1430_phaseerr;
   Double_t        Kst2z1430_phasepull;
   Double_t        Kstm1410_amperr;
   Double_t        Kstm1410_amppull;
   Double_t        Kstm1410_phaseerr;
   Double_t        Kstm1410_phasepull;
   Double_t        Kstm1430_CLEO_amperr;
   Double_t        Kstm1430_CLEO_amppull;
   Double_t        Kstm1430_CLEO_phaseerr;
   Double_t        Kstm1430_CLEO_phasepull;
   Double_t        Kstm1430_amperr;
   Double_t        Kstm1430_amppull;
   Double_t        Kstm1430_masserr;
   Double_t        Kstm1430_masspull;
   Double_t        Kstm1430_phaseerr;
   Double_t        Kstm1430_phasepull;
   Double_t        Kstm1430_widtherr;
   Double_t        Kstm1430_widthpull;
   Double_t        Kstminus_amperr;
   Double_t        Kstminus_amppull;
   Double_t        Kstminus_masserr;
   Double_t        Kstminus_masspull;
   Double_t        Kstminus_phaseerr;
   Double_t        Kstminus_phasepull;
   Double_t        Kstminus_widtherr;
   Double_t        Kstminus_widthpull;
   Double_t        Kstz1410_amperr;
   Double_t        Kstz1410_amppull;
   Double_t        Kstz1410_phaseerr;
   Double_t        Kstz1410_phasepull;
   Double_t        Kstz1430_CLEO_amperr;
   Double_t        Kstz1430_CLEO_amppull;
   Double_t        Kstz1430_CLEO_phaseerr;
   Double_t        Kstz1430_CLEO_phasepull;
   Double_t        Kstz1430_amperr;
   Double_t        Kstz1430_amppull;
   Double_t        Kstz1430_masserr;
   Double_t        Kstz1430_masspull;
   Double_t        Kstz1430_phaseerr;
   Double_t        Kstz1430_phasepull;
   Double_t        Kstz1430_widtherr;
   Double_t        Kstz1430_widthpull;
   Double_t        Kstz1680_amperr;
   Double_t        Kstz1680_amppull;
   Double_t        Kstz1680_phaseerr;
   Double_t        Kstz1680_phasepull;
   Double_t        Kstzero_amperr;
   Double_t        Kstzero_amppull;
   Double_t        Kstzero_masserr;
   Double_t        Kstzero_masspull;
   Double_t        Kstzero_phaseerr;
   Double_t        Kstzero_phasepull;
   Double_t        Kstzero_widtherr;
   Double_t        Kstzero_widthpull;
   Double_t        N1err;
   Double_t        N1pull;
   Double_t        N2err;
   Double_t        N2pull;
   Double_t        Ncomberr;
   Double_t        Ncombpull;
   Double_t        Nmiserr;
   Double_t        Nmispull;
   Double_t        NonReson_amperr;
   Double_t        NonReson_amppull;
   Double_t        NonReson_phaseerr;
   Double_t        NonReson_phasepull;
   Double_t        Nsigerr;
   Double_t        Nsigpull;
   Double_t        RMinuserr;
   Double_t        RMinuspull;
   Double_t        RZeroerr;
   Double_t        RZeropull;
   Double_t        Rho1450_amperr;
   Double_t        Rho1450_amppull;
   Double_t        Rho1450_phaseerr;
   Double_t        Rho1450_phasepull;
   Double_t        Rho1700_amperr;
   Double_t        Rho1700_amppull;
   Double_t        Rho1700_masserr;
   Double_t        Rho1700_masspull;
   Double_t        Rho1700_phaseerr;
   Double_t        Rho1700_phasepull;
   Double_t        Rho1700_widtherr;
   Double_t        Rho1700_widthpull;
   Double_t        Rho_amperr;
   Double_t        Rho_amppull;
   Double_t        Rho_masserr;
   Double_t        Rho_masspull;
   Double_t        Rho_phaseerr;
   Double_t        Rho_phasepull;
   Double_t        Rho_widtherr;
   Double_t        Rho_widthpull;
   Double_t        aMinuserr;
   Double_t        aMinuspull;
   Double_t        aZeroerr;
   Double_t        aZeropull;
   Double_t        biaserr;
   Double_t        biaspull;
   Double_t        c1merr;
   Double_t        c1mpull;
   Double_t        c1perr;
   Double_t        c1ppull;
   Double_t        c2merr;
   Double_t        c2mpull;
   Double_t        c2perr;
   Double_t        c2ppull;
   Double_t        oneerr;
   Double_t        onepull;
   Double_t        phiBMinuserr;
   Double_t        phiBMinuspull;
   Double_t        phiBZeroerr;
   Double_t        phiBZeropull;
   Double_t        phiRMinuserr;
   Double_t        phiRMinuspull;
   Double_t        phiRZeroerr;
   Double_t        phiRZeropull;
   Double_t        rMinuserr;
   Double_t        rMinuspull;
   Double_t        rZeroerr;
   Double_t        rZeropull;
   Double_t        scalefact1err;
   Double_t        scalefact1pull;
   Double_t        scalefact2err;
   Double_t        scalefact2pull;
   Double_t        scalefact3err;
   Double_t        scalefact3pull;
   Double_t        tauerr;
   Double_t        taupull;

   // List of branches
   TBranch        *b_BMinus;   //!
   TBranch        *b_BMinus_err;   //!
   TBranch        *b_BMinus_aerr_lo;   //!
   TBranch        *b_BMinus_aerr_hi;   //!
   TBranch        *b_BZero;   //!
   TBranch        *b_BZero_err;   //!
   TBranch        *b_BZero_aerr_lo;   //!
   TBranch        *b_BZero_aerr_hi;   //!
   TBranch        *b_Kst1680_amp;   //!
   TBranch        *b_Kst1680_amp_err;   //!
   TBranch        *b_Kst1680_amp_aerr_lo;   //!
   TBranch        *b_Kst1680_amp_aerr_hi;   //!
   TBranch        *b_Kst1680_phase;   //!
   TBranch        *b_Kst1680_phase_err;   //!
   TBranch        *b_Kst1680_phase_aerr_lo;   //!
   TBranch        *b_Kst1680_phase_aerr_hi;   //!
   TBranch        *b_Kst2m1430_amp;   //!
   TBranch        *b_Kst2m1430_amp_err;   //!
   TBranch        *b_Kst2m1430_amp_aerr_lo;   //!
   TBranch        *b_Kst2m1430_amp_aerr_hi;   //!
   TBranch        *b_Kst2m1430_phase;   //!
   TBranch        *b_Kst2m1430_phase_err;   //!
   TBranch        *b_Kst2m1430_phase_aerr_lo;   //!
   TBranch        *b_Kst2m1430_phase_aerr_hi;   //!
   TBranch        *b_Kst2z1430_amp;   //!
   TBranch        *b_Kst2z1430_amp_err;   //!
   TBranch        *b_Kst2z1430_amp_aerr_lo;   //!
   TBranch        *b_Kst2z1430_amp_aerr_hi;   //!
   TBranch        *b_Kst2z1430_phase;   //!
   TBranch        *b_Kst2z1430_phase_err;   //!
   TBranch        *b_Kst2z1430_phase_aerr_lo;   //!
   TBranch        *b_Kst2z1430_phase_aerr_hi;   //!
   TBranch        *b_Kstm1410_amp;   //!
   TBranch        *b_Kstm1410_amp_err;   //!
   TBranch        *b_Kstm1410_amp_aerr_lo;   //!
   TBranch        *b_Kstm1410_amp_aerr_hi;   //!
   TBranch        *b_Kstm1410_phase;   //!
   TBranch        *b_Kstm1410_phase_err;   //!
   TBranch        *b_Kstm1410_phase_aerr_lo;   //!
   TBranch        *b_Kstm1410_phase_aerr_hi;   //!
   TBranch        *b_Kstm1430_CLEO_amp;   //!
   TBranch        *b_Kstm1430_CLEO_amp_err;   //!
   TBranch        *b_Kstm1430_CLEO_amp_aerr_lo;   //!
   TBranch        *b_Kstm1430_CLEO_amp_aerr_hi;   //!
   TBranch        *b_Kstm1430_CLEO_phase;   //!
   TBranch        *b_Kstm1430_CLEO_phase_err;   //!
   TBranch        *b_Kstm1430_CLEO_phase_aerr_lo;   //!
   TBranch        *b_Kstm1430_CLEO_phase_aerr_hi;   //!
   TBranch        *b_Kstm1430_amp;   //!
   TBranch        *b_Kstm1430_amp_err;   //!
   TBranch        *b_Kstm1430_amp_aerr_lo;   //!
   TBranch        *b_Kstm1430_amp_aerr_hi;   //!
   TBranch        *b_Kstm1430_mass;   //!
   TBranch        *b_Kstm1430_mass_err;   //!
   TBranch        *b_Kstm1430_mass_aerr_lo;   //!
   TBranch        *b_Kstm1430_mass_aerr_hi;   //!
   TBranch        *b_Kstm1430_phase;   //!
   TBranch        *b_Kstm1430_phase_err;   //!
   TBranch        *b_Kstm1430_phase_aerr_lo;   //!
   TBranch        *b_Kstm1430_phase_aerr_hi;   //!
   TBranch        *b_Kstm1430_width;   //!
   TBranch        *b_Kstm1430_width_err;   //!
   TBranch        *b_Kstm1430_width_aerr_lo;   //!
   TBranch        *b_Kstm1430_width_aerr_hi;   //!
   TBranch        *b_Kstminus_amp;   //!
   TBranch        *b_Kstminus_amp_err;   //!
   TBranch        *b_Kstminus_amp_aerr_lo;   //!
   TBranch        *b_Kstminus_amp_aerr_hi;   //!
   TBranch        *b_Kstminus_mass;   //!
   TBranch        *b_Kstminus_mass_err;   //!
   TBranch        *b_Kstminus_mass_aerr_lo;   //!
   TBranch        *b_Kstminus_mass_aerr_hi;   //!
   TBranch        *b_Kstminus_phase;   //!
   TBranch        *b_Kstminus_phase_err;   //!
   TBranch        *b_Kstminus_phase_aerr_lo;   //!
   TBranch        *b_Kstminus_phase_aerr_hi;   //!
   TBranch        *b_Kstminus_width;   //!
   TBranch        *b_Kstminus_width_err;   //!
   TBranch        *b_Kstminus_width_aerr_lo;   //!
   TBranch        *b_Kstminus_width_aerr_hi;   //!
   TBranch        *b_Kstz1410_amp;   //!
   TBranch        *b_Kstz1410_amp_err;   //!
   TBranch        *b_Kstz1410_amp_aerr_lo;   //!
   TBranch        *b_Kstz1410_amp_aerr_hi;   //!
   TBranch        *b_Kstz1410_phase;   //!
   TBranch        *b_Kstz1410_phase_err;   //!
   TBranch        *b_Kstz1410_phase_aerr_lo;   //!
   TBranch        *b_Kstz1410_phase_aerr_hi;   //!
   TBranch        *b_Kstz1430_CLEO_amp;   //!
   TBranch        *b_Kstz1430_CLEO_amp_err;   //!
   TBranch        *b_Kstz1430_CLEO_amp_aerr_lo;   //!
   TBranch        *b_Kstz1430_CLEO_amp_aerr_hi;   //!
   TBranch        *b_Kstz1430_CLEO_phase;   //!
   TBranch        *b_Kstz1430_CLEO_phase_err;   //!
   TBranch        *b_Kstz1430_CLEO_phase_aerr_lo;   //!
   TBranch        *b_Kstz1430_CLEO_phase_aerr_hi;   //!
   TBranch        *b_Kstz1430_amp;   //!
   TBranch        *b_Kstz1430_amp_err;   //!
   TBranch        *b_Kstz1430_amp_aerr_lo;   //!
   TBranch        *b_Kstz1430_amp_aerr_hi;   //!
   TBranch        *b_Kstz1430_mass;   //!
   TBranch        *b_Kstz1430_mass_err;   //!
   TBranch        *b_Kstz1430_mass_aerr_lo;   //!
   TBranch        *b_Kstz1430_mass_aerr_hi;   //!
   TBranch        *b_Kstz1430_phase;   //!
   TBranch        *b_Kstz1430_phase_err;   //!
   TBranch        *b_Kstz1430_phase_aerr_lo;   //!
   TBranch        *b_Kstz1430_phase_aerr_hi;   //!
   TBranch        *b_Kstz1430_width;   //!
   TBranch        *b_Kstz1430_width_err;   //!
   TBranch        *b_Kstz1430_width_aerr_lo;   //!
   TBranch        *b_Kstz1430_width_aerr_hi;   //!
   TBranch        *b_Kstz1680_amp;   //!
   TBranch        *b_Kstz1680_amp_err;   //!
   TBranch        *b_Kstz1680_amp_aerr_lo;   //!
   TBranch        *b_Kstz1680_amp_aerr_hi;   //!
   TBranch        *b_Kstz1680_phase;   //!
   TBranch        *b_Kstz1680_phase_err;   //!
   TBranch        *b_Kstz1680_phase_aerr_lo;   //!
   TBranch        *b_Kstz1680_phase_aerr_hi;   //!
   TBranch        *b_Kstzero_amp;   //!
   TBranch        *b_Kstzero_amp_err;   //!
   TBranch        *b_Kstzero_amp_aerr_lo;   //!
   TBranch        *b_Kstzero_amp_aerr_hi;   //!
   TBranch        *b_Kstzero_mass;   //!
   TBranch        *b_Kstzero_mass_err;   //!
   TBranch        *b_Kstzero_mass_aerr_lo;   //!
   TBranch        *b_Kstzero_mass_aerr_hi;   //!
   TBranch        *b_Kstzero_phase;   //!
   TBranch        *b_Kstzero_phase_err;   //!
   TBranch        *b_Kstzero_phase_aerr_lo;   //!
   TBranch        *b_Kstzero_phase_aerr_hi;   //!
   TBranch        *b_Kstzero_width;   //!
   TBranch        *b_Kstzero_width_err;   //!
   TBranch        *b_Kstzero_width_aerr_lo;   //!
   TBranch        *b_Kstzero_width_aerr_hi;   //!
   TBranch        *b_N1;   //!
   TBranch        *b_N1_err;   //!
   TBranch        *b_N1_aerr_lo;   //!
   TBranch        *b_N1_aerr_hi;   //!
   TBranch        *b_N2;   //!
   TBranch        *b_N2_err;   //!
   TBranch        *b_N2_aerr_lo;   //!
   TBranch        *b_N2_aerr_hi;   //!
   TBranch        *b_Ncomb;   //!
   TBranch        *b_Ncomb_err;   //!
   TBranch        *b_Ncomb_aerr_lo;   //!
   TBranch        *b_Ncomb_aerr_hi;   //!
   TBranch        *b_Nmis;   //!
   TBranch        *b_Nmis_err;   //!
   TBranch        *b_Nmis_aerr_lo;   //!
   TBranch        *b_Nmis_aerr_hi;   //!
   TBranch        *b_NonReson_amp;   //!
   TBranch        *b_NonReson_amp_err;   //!
   TBranch        *b_NonReson_amp_aerr_lo;   //!
   TBranch        *b_NonReson_amp_aerr_hi;   //!
   TBranch        *b_NonReson_phase;   //!
   TBranch        *b_NonReson_phase_err;   //!
   TBranch        *b_NonReson_phase_aerr_lo;   //!
   TBranch        *b_NonReson_phase_aerr_hi;   //!
   TBranch        *b_Nsig;   //!
   TBranch        *b_Nsig_err;   //!
   TBranch        *b_Nsig_aerr_lo;   //!
   TBranch        *b_Nsig_aerr_hi;   //!
   TBranch        *b_RMinus;   //!
   TBranch        *b_RMinus_err;   //!
   TBranch        *b_RMinus_aerr_lo;   //!
   TBranch        *b_RMinus_aerr_hi;   //!
   TBranch        *b_RZero;   //!
   TBranch        *b_RZero_err;   //!
   TBranch        *b_RZero_aerr_lo;   //!
   TBranch        *b_RZero_aerr_hi;   //!
   TBranch        *b_Rho1450_amp;   //!
   TBranch        *b_Rho1450_amp_err;   //!
   TBranch        *b_Rho1450_amp_aerr_lo;   //!
   TBranch        *b_Rho1450_amp_aerr_hi;   //!
   TBranch        *b_Rho1450_phase;   //!
   TBranch        *b_Rho1450_phase_err;   //!
   TBranch        *b_Rho1450_phase_aerr_lo;   //!
   TBranch        *b_Rho1450_phase_aerr_hi;   //!
   TBranch        *b_Rho1700_amp;   //!
   TBranch        *b_Rho1700_amp_err;   //!
   TBranch        *b_Rho1700_amp_aerr_lo;   //!
   TBranch        *b_Rho1700_amp_aerr_hi;   //!
   TBranch        *b_Rho1700_mass;   //!
   TBranch        *b_Rho1700_mass_err;   //!
   TBranch        *b_Rho1700_mass_aerr_lo;   //!
   TBranch        *b_Rho1700_mass_aerr_hi;   //!
   TBranch        *b_Rho1700_phase;   //!
   TBranch        *b_Rho1700_phase_err;   //!
   TBranch        *b_Rho1700_phase_aerr_lo;   //!
   TBranch        *b_Rho1700_phase_aerr_hi;   //!
   TBranch        *b_Rho1700_width;   //!
   TBranch        *b_Rho1700_width_err;   //!
   TBranch        *b_Rho1700_width_aerr_lo;   //!
   TBranch        *b_Rho1700_width_aerr_hi;   //!
   TBranch        *b_Rho_amp;   //!
   TBranch        *b_Rho_amp_err;   //!
   TBranch        *b_Rho_amp_aerr_lo;   //!
   TBranch        *b_Rho_amp_aerr_hi;   //!
   TBranch        *b_Rho_mass;   //!
   TBranch        *b_Rho_mass_err;   //!
   TBranch        *b_Rho_mass_aerr_lo;   //!
   TBranch        *b_Rho_mass_aerr_hi;   //!
   TBranch        *b_Rho_phase;   //!
   TBranch        *b_Rho_phase_err;   //!
   TBranch        *b_Rho_phase_aerr_lo;   //!
   TBranch        *b_Rho_phase_aerr_hi;   //!
   TBranch        *b_Rho_width;   //!
   TBranch        *b_Rho_width_err;   //!
   TBranch        *b_Rho_width_aerr_lo;   //!
   TBranch        *b_Rho_width_aerr_hi;   //!
   TBranch        *b_aMinus;   //!
   TBranch        *b_aMinus_err;   //!
   TBranch        *b_aMinus_aerr_lo;   //!
   TBranch        *b_aMinus_aerr_hi;   //!
   TBranch        *b_aZero;   //!
   TBranch        *b_aZero_err;   //!
   TBranch        *b_aZero_aerr_lo;   //!
   TBranch        *b_aZero_aerr_hi;   //!
   TBranch        *b_bias;   //!
   TBranch        *b_bias_err;   //!
   TBranch        *b_bias_aerr_lo;   //!
   TBranch        *b_bias_aerr_hi;   //!
   TBranch        *b_c1;   //!
   TBranch        *b_c1_err;   //!
   TBranch        *b_c1_aerr_lo;   //!
   TBranch        *b_c1_aerr_hi;   //!
   TBranch        *b_c1err;   //!
   TBranch        *b_c1pull;   //!
   TBranch        *b_c2;   //!
   TBranch        *b_c2_err;   //!
   TBranch        *b_c2_aerr_lo;   //!
   TBranch        *b_c2_aerr_hi;   //!
   TBranch        *b_c2err;   //!
   TBranch        *b_c2pull;   //!
   TBranch        *b_c1m;   //!
   TBranch        *b_c1m_err;   //!
   TBranch        *b_c1m_aerr_lo;   //!
   TBranch        *b_c1m_aerr_hi;   //!
   TBranch        *b_c1p;   //!
   TBranch        *b_c1p_err;   //!
   TBranch        *b_c1p_aerr_lo;   //!
   TBranch        *b_c1p_aerr_hi;   //!
   TBranch        *b_c2m;   //!
   TBranch        *b_c2m_err;   //!
   TBranch        *b_c2m_aerr_lo;   //!
   TBranch        *b_c2m_aerr_hi;   //!
   TBranch        *b_c2p;   //!
   TBranch        *b_c2p_err;   //!
   TBranch        *b_c2p_aerr_lo;   //!
   TBranch        *b_c2p_aerr_hi;   //!
   TBranch        *b_one;   //!
   TBranch        *b_one_err;   //!
   TBranch        *b_one_aerr_lo;   //!
   TBranch        *b_one_aerr_hi;   //!
   TBranch        *b_phiBMinus;   //!
   TBranch        *b_phiBMinus_err;   //!
   TBranch        *b_phiBMinus_aerr_lo;   //!
   TBranch        *b_phiBMinus_aerr_hi;   //!
   TBranch        *b_phiBZero;   //!
   TBranch        *b_phiBZero_err;   //!
   TBranch        *b_phiBZero_aerr_lo;   //!
   TBranch        *b_phiBZero_aerr_hi;   //!
   TBranch        *b_phiRMinus;   //!
   TBranch        *b_phiRMinus_err;   //!
   TBranch        *b_phiRMinus_aerr_lo;   //!
   TBranch        *b_phiRMinus_aerr_hi;   //!
   TBranch        *b_phiRZero;   //!
   TBranch        *b_phiRZero_err;   //!
   TBranch        *b_phiRZero_aerr_lo;   //!
   TBranch        *b_phiRZero_aerr_hi;   //!
   TBranch        *b_rMinus;   //!
   TBranch        *b_rMinus_err;   //!
   TBranch        *b_rMinus_aerr_lo;   //!
   TBranch        *b_rMinus_aerr_hi;   //!
   TBranch        *b_rZero;   //!
   TBranch        *b_rZero_err;   //!
   TBranch        *b_rZero_aerr_lo;   //!
   TBranch        *b_rZero_aerr_hi;   //!
   TBranch        *b_scalefact1;   //!
   TBranch        *b_scalefact1_err;   //!
   TBranch        *b_scalefact1_aerr_lo;   //!
   TBranch        *b_scalefact1_aerr_hi;   //!
   TBranch        *b_scalefact2;   //!
   TBranch        *b_scalefact2_err;   //!
   TBranch        *b_scalefact2_aerr_lo;   //!
   TBranch        *b_scalefact2_aerr_hi;   //!
   TBranch        *b_scalefact3;   //!
   TBranch        *b_scalefact3_err;   //!
   TBranch        *b_scalefact3_aerr_lo;   //!
   TBranch        *b_scalefact3_aerr_hi;   //!
   TBranch        *b_tau;   //!
   TBranch        *b_tau_err;   //!
   TBranch        *b_tau_aerr_lo;   //!
   TBranch        *b_tau_aerr_hi;   //!
   TBranch        *b_NLL;   //!
   TBranch        *b_NLL_err;   //!
   TBranch        *b_NLL_aerr_lo;   //!
   TBranch        *b_NLL_aerr_hi;   //!
   TBranch        *b_BMinuserr;   //!
   TBranch        *b_BMinuspull;   //!
   TBranch        *b_BZeroerr;   //!
   TBranch        *b_BZeropull;   //!
   TBranch        *b_Kst1680_amperr;   //!
   TBranch        *b_Kst1680_amppull;   //!
   TBranch        *b_Kst1680_phaseerr;   //!
   TBranch        *b_Kst1680_phasepull;   //!
   TBranch        *b_Kst2m1430_amperr;   //!
   TBranch        *b_Kst2m1430_amppull;   //!
   TBranch        *b_Kst2m1430_phaseerr;   //!
   TBranch        *b_Kst2m1430_phasepull;   //!
   TBranch        *b_Kst2z1430_amperr;   //!
   TBranch        *b_Kst2z1430_amppull;   //!
   TBranch        *b_Kst2z1430_phaseerr;   //!
   TBranch        *b_Kst2z1430_phasepull;   //!
   TBranch        *b_Kstm1410_amperr;   //!
   TBranch        *b_Kstm1410_amppull;   //!
   TBranch        *b_Kstm1410_phaseerr;   //!
   TBranch        *b_Kstm1410_phasepull;   //!
   TBranch        *b_Kstm1430_CLEO_amperr;   //!
   TBranch        *b_Kstm1430_CLEO_amppull;   //!
   TBranch        *b_Kstm1430_CLEO_phaseerr;   //!
   TBranch        *b_Kstm1430_CLEO_phasepull;   //!
   TBranch        *b_Kstm1430_amperr;   //!
   TBranch        *b_Kstm1430_amppull;   //!
   TBranch        *b_Kstm1430_masserr;   //!
   TBranch        *b_Kstm1430_masspull;   //!
   TBranch        *b_Kstm1430_phaseerr;   //!
   TBranch        *b_Kstm1430_phasepull;   //!
   TBranch        *b_Kstm1430_widtherr;   //!
   TBranch        *b_Kstm1430_widthpull;   //!
   TBranch        *b_Kstminus_amperr;   //!
   TBranch        *b_Kstminus_amppull;   //!
   TBranch        *b_Kstminus_masserr;   //!
   TBranch        *b_Kstminus_masspull;   //!
   TBranch        *b_Kstminus_phaseerr;   //!
   TBranch        *b_Kstminus_phasepull;   //!
   TBranch        *b_Kstminus_widtherr;   //!
   TBranch        *b_Kstminus_widthpull;   //!
   TBranch        *b_Kstz1410_amperr;   //!
   TBranch        *b_Kstz1410_amppull;   //!
   TBranch        *b_Kstz1410_phaseerr;   //!
   TBranch        *b_Kstz1410_phasepull;   //!
   TBranch        *b_Kstz1430_CLEO_amperr;   //!
   TBranch        *b_Kstz1430_CLEO_amppull;   //!
   TBranch        *b_Kstz1430_CLEO_phaseerr;   //!
   TBranch        *b_Kstz1430_CLEO_phasepull;   //!
   TBranch        *b_Kstz1430_amperr;   //!
   TBranch        *b_Kstz1430_amppull;   //!
   TBranch        *b_Kstz1430_masserr;   //!
   TBranch        *b_Kstz1430_masspull;   //!
   TBranch        *b_Kstz1430_phaseerr;   //!
   TBranch        *b_Kstz1430_phasepull;   //!
   TBranch        *b_Kstz1430_widtherr;   //!
   TBranch        *b_Kstz1430_widthpull;   //!
   TBranch        *b_Kstz1680_amperr;   //!
   TBranch        *b_Kstz1680_amppull;   //!
   TBranch        *b_Kstz1680_phaseerr;   //!
   TBranch        *b_Kstz1680_phasepull;   //!
   TBranch        *b_Kstzero_amperr;   //!
   TBranch        *b_Kstzero_amppull;   //!
   TBranch        *b_Kstzero_masserr;   //!
   TBranch        *b_Kstzero_masspull;   //!
   TBranch        *b_Kstzero_phaseerr;   //!
   TBranch        *b_Kstzero_phasepull;   //!
   TBranch        *b_Kstzero_widtherr;   //!
   TBranch        *b_Kstzero_widthpull;   //!
   TBranch        *b_N1err;   //!
   TBranch        *b_N1pull;   //!
   TBranch        *b_N2err;   //!
   TBranch        *b_N2pull;   //!
   TBranch        *b_Ncomberr;   //!
   TBranch        *b_Ncombpull;   //!
   TBranch        *b_Nmiserr;   //!
   TBranch        *b_Nmispull;   //!
   TBranch        *b_NonReson_amperr;   //!
   TBranch        *b_NonReson_amppull;   //!
   TBranch        *b_NonReson_phaseerr;   //!
   TBranch        *b_NonReson_phasepull;   //!
   TBranch        *b_Nsigerr;   //!
   TBranch        *b_Nsigpull;   //!
   TBranch        *b_RMinuserr;   //!
   TBranch        *b_RMinuspull;   //!
   TBranch        *b_RZeroerr;   //!
   TBranch        *b_RZeropull;   //!
   TBranch        *b_Rho1450_amperr;   //!
   TBranch        *b_Rho1450_amppull;   //!
   TBranch        *b_Rho1450_phaseerr;   //!
   TBranch        *b_Rho1450_phasepull;   //!
   TBranch        *b_Rho1700_amperr;   //!
   TBranch        *b_Rho1700_amppull;   //!
   TBranch        *b_Rho1700_masserr;   //!
   TBranch        *b_Rho1700_masspull;   //!
   TBranch        *b_Rho1700_phaseerr;   //!
   TBranch        *b_Rho1700_phasepull;   //!
   TBranch        *b_Rho1700_widtherr;   //!
   TBranch        *b_Rho1700_widthpull;   //!
   TBranch        *b_Rho_amperr;   //!
   TBranch        *b_Rho_amppull;   //!
   TBranch        *b_Rho_masserr;   //!
   TBranch        *b_Rho_masspull;   //!
   TBranch        *b_Rho_phaseerr;   //!
   TBranch        *b_Rho_phasepull;   //!
   TBranch        *b_Rho_widtherr;   //!
   TBranch        *b_Rho_widthpull;   //!
   TBranch        *b_aMinuserr;   //!
   TBranch        *b_aMinuspull;   //!
   TBranch        *b_aZeroerr;   //!
   TBranch        *b_aZeropull;   //!
   TBranch        *b_biaserr;   //!
   TBranch        *b_biaspull;   //!
   TBranch        *b_c1merr;   //!
   TBranch        *b_c1mpull;   //!
   TBranch        *b_c1perr;   //!
   TBranch        *b_c1ppull;   //!
   TBranch        *b_c2merr;   //!
   TBranch        *b_c2mpull;   //!
   TBranch        *b_c2perr;   //!
   TBranch        *b_c2ppull;   //!
   TBranch        *b_oneerr;   //!
   TBranch        *b_onepull;   //!
   TBranch        *b_phiBMinuserr;   //!
   TBranch        *b_phiBMinuspull;   //!
   TBranch        *b_phiBZeroerr;   //!
   TBranch        *b_phiBZeropull;   //!
   TBranch        *b_phiRMinuserr;   //!
   TBranch        *b_phiRMinuspull;   //!
   TBranch        *b_phiRZeroerr;   //!
   TBranch        *b_phiRZeropull;   //!
   TBranch        *b_rMinuserr;   //!
   TBranch        *b_rMinuspull;   //!
   TBranch        *b_rZeroerr;   //!
   TBranch        *b_rZeropull;   //!
   TBranch        *b_scalefact1err;   //!
   TBranch        *b_scalefact1pull;   //!
   TBranch        *b_scalefact2err;   //!
   TBranch        *b_scalefact2pull;   //!
   TBranch        *b_scalefact3err;   //!
   TBranch        *b_scalefact3pull;   //!
   TBranch        *b_tauerr;   //!
   TBranch        *b_taupull;   //!

   SumToys(TTree *tree=0);
   virtual ~SumToys();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SumToys_cxx
SumToys::SumToys(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f) {
         f = new TFile("Memory Directory");
         f->cd("Rint:/");
      }
      tree = (TTree*)gDirectory->Get("fitParData");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("fitParData","");
      chain->Add("Toy_results/toy_CP/toy_1.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_10.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_100.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1000.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1001.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1002.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1003.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1004.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1005.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1006.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1007.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1008.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1009.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_101.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1010.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1011.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1012.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1013.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1014.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1015.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1016.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1017.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1018.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1019.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_102.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1020.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1021.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1022.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1023.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1024.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1025.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1026.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1027.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1028.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1029.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_103.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1030.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1031.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1032.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1033.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1034.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1035.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1036.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1037.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1038.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1039.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_104.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1040.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1041.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1042.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1043.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1044.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1045.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1046.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1047.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1048.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1049.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_105.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1050.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1051.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1052.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1053.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1054.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1055.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1056.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1057.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1058.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1059.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_106.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1060.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1061.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1062.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1063.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1064.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1065.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1066.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1067.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1068.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1069.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_107.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1070.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1071.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1072.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1073.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1074.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1075.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1076.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1077.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1078.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1079.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_108.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1080.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1081.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1082.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1083.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1084.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1085.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1086.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1087.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1088.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1089.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_109.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1090.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1091.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1092.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1093.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1094.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1095.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1096.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1097.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1098.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1099.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_11.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_110.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1100.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1101.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1102.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1103.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1104.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1105.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1106.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1107.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1108.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1109.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_111.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1110.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1111.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1112.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1113.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1114.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1115.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1116.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1117.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1118.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1119.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_112.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1120.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1121.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1122.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1123.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1124.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1125.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1126.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1127.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1128.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1129.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_113.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1130.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1131.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1132.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1133.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1134.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1135.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1136.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1137.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1138.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1139.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_114.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1140.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1141.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1142.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1143.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1144.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1145.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1146.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1147.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1148.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1149.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_115.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1150.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1151.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1152.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1153.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1154.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1155.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1156.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1157.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1158.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1159.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_116.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1160.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1161.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1162.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1163.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1164.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1165.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1166.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1167.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1168.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1169.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_117.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1170.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1171.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1172.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1173.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1174.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1175.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1176.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1177.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1178.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1179.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_118.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1180.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1181.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1182.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1183.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1184.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1185.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1186.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1187.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1188.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1189.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_119.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1190.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1191.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1192.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1193.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1194.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1195.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1196.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1197.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1198.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1199.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_12.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_120.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1200.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1201.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1202.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1203.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1204.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1205.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1206.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1207.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1208.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1209.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_121.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1210.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1211.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1212.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1213.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1214.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1215.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1216.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1217.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1218.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1219.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_122.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1220.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1221.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1222.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1223.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1224.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1225.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1226.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1227.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1228.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1229.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_123.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1230.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1231.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1232.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1233.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1234.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1235.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1236.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1237.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1238.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1239.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_124.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1240.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1241.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1242.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1243.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1244.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1245.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1246.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1247.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1248.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1249.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_125.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1250.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1251.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1252.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1253.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1254.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1255.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1256.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1257.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1258.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1259.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_126.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1260.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1261.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1262.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1263.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1264.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1265.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1266.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1267.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1268.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1269.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_127.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1270.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1271.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1272.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1273.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1274.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1275.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1276.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1277.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1278.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1279.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_128.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1280.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1281.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1282.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1283.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1284.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1285.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1286.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1287.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1288.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1289.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_129.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1290.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1291.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1292.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1293.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1294.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1295.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1296.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1297.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1298.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1299.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_13.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_130.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1300.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1301.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1302.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1303.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1304.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1305.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1306.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1307.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1308.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1309.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_131.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1310.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1311.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1312.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1313.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1314.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1315.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1316.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1317.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1318.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1319.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_132.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1320.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1321.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1322.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1323.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1324.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1325.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1326.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1327.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1328.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1329.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_133.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1330.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1331.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1332.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1333.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1334.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1335.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1336.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1337.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1338.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1339.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_134.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1340.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1341.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1342.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1343.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1344.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1345.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1346.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1347.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1348.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1349.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_135.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1350.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1351.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1352.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1353.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1354.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1355.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1356.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1357.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1358.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1359.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_136.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1360.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1361.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1362.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1363.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1364.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1365.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1366.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1367.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1368.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1369.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_137.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1370.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1371.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1372.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1373.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1374.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1375.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1376.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1377.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1378.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1379.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_138.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1380.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1381.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1382.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1383.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1384.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1385.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1386.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1387.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1388.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1389.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_139.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1390.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1391.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1392.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1393.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1394.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1395.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1396.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1397.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1398.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1399.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_14.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_140.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1400.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1401.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1402.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1403.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1404.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1405.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1406.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1407.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1408.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1409.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_141.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1410.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1411.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1412.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1413.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1414.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1415.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1416.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1417.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1418.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1419.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_142.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1420.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1421.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1422.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1423.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1424.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1425.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1426.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1427.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1428.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1429.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_143.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1430.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1431.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1432.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1433.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1434.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1435.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1436.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1437.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1438.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1439.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_144.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1440.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1441.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1442.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1443.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1444.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1445.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1446.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1447.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1448.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1449.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_145.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1450.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1451.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1452.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1453.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1454.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1455.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1456.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1457.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1458.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1459.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_146.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1460.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1461.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1462.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1463.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1464.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1465.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1466.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1467.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1468.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1469.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_147.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1470.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1471.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1472.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1473.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1474.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1475.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1476.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1477.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1478.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1479.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_148.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1480.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1481.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1482.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1483.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1484.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1485.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1486.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1487.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1488.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1489.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_149.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1490.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1491.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1492.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1493.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1494.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1495.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1496.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1497.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1498.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1499.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_15.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_150.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1500.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1501.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1502.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1503.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1504.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1505.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1506.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1507.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1508.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1509.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_151.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1510.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1511.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1512.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1513.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1514.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1515.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1516.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1517.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1518.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1519.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_152.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1520.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1521.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1522.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1523.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1524.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1525.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1526.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1527.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1528.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1529.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_153.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1530.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1531.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1532.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1533.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1534.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1535.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1536.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1537.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1538.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1539.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_154.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1540.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1541.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1542.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1543.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1544.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1545.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1546.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1547.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1548.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1549.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_155.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1550.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1551.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1552.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1553.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1554.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1555.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1556.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1557.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1558.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1559.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_156.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1560.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1561.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1562.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1563.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1564.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1565.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1566.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1567.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1568.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1569.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_157.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1570.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1571.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1572.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1573.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1574.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1575.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1576.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1577.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1578.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1579.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_158.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1580.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1581.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1582.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1583.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1584.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1585.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1586.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1587.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1588.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1589.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_159.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1590.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1591.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1592.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1593.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1594.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1595.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1596.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1597.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1598.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1599.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_16.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_160.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1600.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1601.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1602.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1603.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1604.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1605.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1606.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1607.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1608.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1609.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_161.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1610.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1611.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1612.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1613.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1614.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1615.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1616.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1617.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1618.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1619.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_162.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1620.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1621.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1622.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1623.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1624.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1625.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1626.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1627.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1628.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1629.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_163.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1630.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1631.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1632.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1633.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1634.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1635.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1636.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1637.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1638.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1639.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_164.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1640.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1641.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1642.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1643.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1644.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1645.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1646.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1647.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1648.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1649.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_165.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1650.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1651.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1652.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1653.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1654.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1655.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1656.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1657.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1658.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1659.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_166.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1660.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1661.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1662.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1663.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1664.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1665.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1666.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1667.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1668.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1669.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_167.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1670.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1671.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1672.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1673.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1674.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1675.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1676.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1677.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1678.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1679.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_168.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1680.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1681.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1682.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1683.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1684.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1685.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1686.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1687.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1688.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1689.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_169.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1690.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1691.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1692.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1693.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1694.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1695.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1696.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1697.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1698.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1699.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_17.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_170.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1700.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1701.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1702.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1703.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1704.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1705.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1706.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1707.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1708.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1709.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_171.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1710.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1711.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1712.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1713.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1714.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1715.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1716.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1717.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1718.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1719.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_172.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1720.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1721.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1722.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1723.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1724.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1725.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1726.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1727.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1728.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1729.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_173.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1730.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1731.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1732.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1733.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1734.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1735.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1736.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1737.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1738.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1739.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_174.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1740.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1741.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1742.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1743.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1744.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1745.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1746.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1747.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1748.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1749.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_175.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1750.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1751.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1752.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1753.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1754.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1755.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1756.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1757.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1758.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1759.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_176.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1760.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1761.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1762.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1763.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1764.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1765.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1766.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1767.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1768.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1769.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_177.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1770.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1771.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1772.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1773.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1774.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1775.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1776.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1777.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1778.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1779.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_178.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1780.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1781.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1782.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1783.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1784.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1785.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1786.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1787.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1788.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1789.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_179.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1790.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1791.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1792.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1793.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1794.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1795.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1796.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1797.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1798.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1799.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_18.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_180.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1800.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1801.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1802.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1803.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1804.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1805.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1806.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1807.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1808.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1809.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_181.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1810.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1811.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1812.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1813.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1814.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1815.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1816.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1817.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1818.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1819.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_182.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1820.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1821.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1822.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1823.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1824.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1825.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1826.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1827.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1828.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1829.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_183.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1830.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1831.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1832.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1833.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1834.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1835.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1836.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1837.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1838.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1839.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_184.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1840.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1841.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1842.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1843.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1844.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1845.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1846.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1847.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1848.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1849.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_185.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1850.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1851.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1852.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1853.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1854.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1855.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1856.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1857.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1858.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1859.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_186.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1860.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1861.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1862.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1863.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1864.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1865.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1866.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1867.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1868.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1869.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_187.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1870.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1871.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1872.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1873.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1874.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1875.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1876.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1877.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1878.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1879.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_188.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1880.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1881.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1882.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1883.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1884.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1885.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1886.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1887.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1888.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1889.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_189.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1890.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1891.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1892.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1893.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1894.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1895.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1896.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1897.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1898.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1899.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_19.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_190.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1900.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1901.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1902.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1903.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1904.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1905.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1906.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1907.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1908.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1909.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_191.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1910.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1911.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1912.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1913.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1914.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1915.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1916.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1917.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1918.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1919.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_192.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1920.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1921.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1922.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1923.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1924.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1925.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1926.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1927.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1928.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1929.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_193.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1930.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1931.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1932.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1934.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1935.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1936.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1938.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1939.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_194.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1940.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1941.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1942.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1943.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1944.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1945.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1946.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1948.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1949.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_195.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1950.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1951.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1952.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1953.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1954.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1955.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1956.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1957.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1958.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1959.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_196.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1960.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1961.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1962.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1964.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1965.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1966.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1967.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1968.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1969.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_197.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1970.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1971.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1972.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1973.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1974.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1975.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1976.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1977.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1978.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1979.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_198.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1980.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1981.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1982.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1983.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1984.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1985.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1986.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1987.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1988.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1989.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_199.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1990.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1991.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1992.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1993.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1994.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1995.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1996.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1997.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1998.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_1999.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_2.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_20.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_200.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_2000.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_201.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_202.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_203.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_204.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_205.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_206.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_207.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_208.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_209.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_21.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_210.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_211.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_212.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_213.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_214.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_215.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_216.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_217.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_218.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_219.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_22.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_220.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_221.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_222.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_223.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_224.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_225.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_226.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_227.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_228.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_229.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_23.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_230.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_231.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_232.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_233.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_234.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_235.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_236.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_237.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_238.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_239.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_24.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_240.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_241.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_242.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_243.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_244.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_245.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_246.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_247.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_248.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_249.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_25.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_250.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_251.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_252.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_253.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_254.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_255.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_256.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_257.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_258.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_259.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_26.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_260.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_261.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_262.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_263.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_264.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_265.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_266.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_267.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_268.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_269.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_27.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_270.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_271.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_272.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_273.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_274.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_275.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_276.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_277.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_278.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_279.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_28.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_280.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_281.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_282.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_283.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_284.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_285.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_286.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_287.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_288.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_289.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_29.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_290.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_291.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_292.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_293.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_294.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_295.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_296.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_297.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_298.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_299.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_3.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_30.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_300.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_301.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_302.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_303.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_304.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_305.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_306.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_307.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_308.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_309.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_31.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_310.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_311.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_312.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_313.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_314.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_315.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_316.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_317.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_318.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_319.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_32.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_320.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_321.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_322.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_323.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_324.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_325.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_326.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_327.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_328.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_329.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_33.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_330.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_331.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_332.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_333.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_334.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_335.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_336.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_337.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_338.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_339.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_34.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_340.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_341.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_342.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_343.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_344.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_345.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_346.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_347.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_348.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_349.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_35.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_350.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_351.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_352.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_353.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_354.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_355.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_356.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_357.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_358.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_359.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_36.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_360.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_361.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_362.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_363.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_364.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_365.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_366.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_367.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_368.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_369.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_37.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_370.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_371.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_372.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_373.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_374.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_375.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_376.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_377.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_378.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_379.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_38.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_380.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_381.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_382.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_383.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_384.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_385.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_386.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_387.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_388.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_389.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_39.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_390.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_391.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_392.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_393.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_394.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_395.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_396.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_397.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_398.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_399.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_4.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_40.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_400.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_401.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_402.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_403.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_404.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_405.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_406.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_407.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_408.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_409.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_41.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_410.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_411.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_412.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_413.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_414.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_415.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_416.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_417.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_418.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_419.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_42.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_420.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_421.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_422.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_423.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_424.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_425.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_426.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_427.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_428.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_429.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_43.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_430.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_431.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_432.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_433.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_434.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_435.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_436.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_437.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_438.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_439.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_44.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_440.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_441.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_442.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_443.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_444.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_445.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_446.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_447.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_448.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_449.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_45.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_450.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_451.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_452.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_453.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_454.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_455.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_456.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_457.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_458.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_459.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_46.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_460.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_461.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_462.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_463.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_464.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_465.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_466.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_467.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_468.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_469.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_47.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_470.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_471.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_472.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_473.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_474.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_475.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_476.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_477.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_478.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_479.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_48.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_480.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_481.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_482.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_483.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_484.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_485.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_486.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_487.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_488.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_489.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_49.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_490.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_491.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_492.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_493.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_494.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_495.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_496.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_497.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_498.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_499.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_5.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_50.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_500.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_501.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_502.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_503.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_504.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_505.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_506.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_507.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_508.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_509.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_51.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_510.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_511.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_512.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_513.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_514.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_515.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_516.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_517.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_518.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_519.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_52.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_520.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_521.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_522.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_523.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_524.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_525.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_526.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_527.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_528.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_529.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_53.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_530.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_531.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_532.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_533.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_534.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_535.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_536.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_537.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_538.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_539.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_54.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_540.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_541.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_542.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_543.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_544.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_545.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_546.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_547.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_548.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_549.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_55.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_550.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_551.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_552.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_553.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_554.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_555.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_556.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_557.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_558.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_559.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_56.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_560.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_561.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_562.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_563.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_564.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_565.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_566.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_567.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_568.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_569.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_57.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_570.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_571.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_572.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_573.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_574.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_575.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_576.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_577.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_578.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_579.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_58.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_580.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_581.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_582.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_583.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_584.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_585.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_586.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_587.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_588.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_589.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_59.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_590.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_591.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_592.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_593.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_594.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_595.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_596.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_597.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_598.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_599.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_6.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_60.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_600.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_601.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_602.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_603.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_604.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_605.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_606.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_607.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_608.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_609.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_61.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_610.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_611.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_612.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_613.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_614.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_615.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_616.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_617.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_618.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_619.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_62.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_620.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_621.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_622.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_623.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_624.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_625.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_626.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_627.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_628.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_629.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_63.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_630.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_631.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_632.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_633.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_634.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_635.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_636.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_637.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_638.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_639.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_64.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_640.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_641.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_642.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_643.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_644.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_645.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_646.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_647.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_648.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_649.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_65.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_650.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_651.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_652.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_653.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_654.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_655.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_656.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_657.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_658.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_659.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_66.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_660.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_661.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_662.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_663.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_664.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_665.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_666.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_667.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_668.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_669.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_67.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_670.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_671.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_672.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_673.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_674.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_675.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_676.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_677.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_678.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_679.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_68.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_680.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_681.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_682.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_683.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_684.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_685.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_686.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_687.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_688.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_689.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_69.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_690.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_691.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_692.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_693.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_694.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_695.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_696.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_697.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_698.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_699.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_7.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_70.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_700.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_701.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_702.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_703.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_704.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_705.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_706.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_707.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_708.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_709.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_71.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_710.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_711.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_712.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_713.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_714.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_715.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_716.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_717.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_718.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_719.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_72.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_720.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_721.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_722.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_723.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_724.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_725.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_726.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_727.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_728.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_729.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_73.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_730.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_731.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_732.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_733.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_734.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_735.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_736.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_737.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_738.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_739.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_74.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_740.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_741.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_742.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_743.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_744.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_745.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_746.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_747.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_748.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_749.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_75.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_750.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_751.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_752.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_753.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_754.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_755.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_756.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_757.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_758.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_759.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_76.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_760.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_761.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_762.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_763.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_764.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_765.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_766.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_767.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_768.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_769.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_77.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_770.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_771.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_772.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_773.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_774.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_775.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_776.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_777.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_778.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_779.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_78.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_780.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_781.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_782.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_783.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_784.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_785.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_786.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_787.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_788.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_789.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_79.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_790.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_791.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_792.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_793.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_794.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_795.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_796.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_797.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_798.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_799.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_8.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_80.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_800.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_801.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_802.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_803.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_804.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_805.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_806.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_807.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_808.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_809.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_81.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_810.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_811.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_812.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_813.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_814.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_815.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_816.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_817.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_818.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_819.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_82.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_820.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_821.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_822.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_823.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_824.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_825.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_826.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_827.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_828.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_829.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_83.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_830.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_831.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_832.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_833.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_834.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_835.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_836.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_837.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_838.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_839.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_84.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_840.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_841.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_842.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_843.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_844.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_845.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_846.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_847.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_848.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_849.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_85.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_850.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_851.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_852.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_853.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_854.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_855.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_856.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_857.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_858.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_859.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_86.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_860.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_861.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_862.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_863.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_864.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_865.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_866.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_867.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_868.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_869.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_87.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_870.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_871.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_872.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_873.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_874.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_875.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_876.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_877.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_878.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_879.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_88.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_880.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_881.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_882.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_883.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_884.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_885.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_886.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_887.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_888.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_889.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_89.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_890.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_891.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_892.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_893.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_894.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_895.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_896.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_897.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_898.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_899.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_9.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_90.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_900.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_901.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_902.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_903.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_904.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_905.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_906.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_907.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_908.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_909.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_91.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_910.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_911.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_912.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_913.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_914.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_915.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_916.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_917.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_918.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_919.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_92.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_920.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_921.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_922.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_923.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_924.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_925.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_926.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_927.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_928.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_929.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_93.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_930.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_931.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_932.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_933.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_934.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_935.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_936.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_937.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_938.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_939.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_94.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_940.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_941.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_942.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_943.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_944.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_945.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_946.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_947.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_948.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_949.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_95.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_950.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_951.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_952.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_953.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_954.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_955.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_956.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_957.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_958.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_959.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_96.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_960.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_961.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_962.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_963.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_964.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_965.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_966.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_967.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_968.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_969.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_97.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_970.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_971.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_972.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_973.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_974.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_975.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_976.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_977.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_978.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_979.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_98.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_980.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_981.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_982.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_983.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_984.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_985.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_986.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_987.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_988.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_989.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_99.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_990.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_991.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_992.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_993.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_994.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_995.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_996.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_997.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_998.root/fitParData");
      chain->Add("Toy_results/toy_CP/toy_999.root/fitParData");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

SumToys::~SumToys()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SumToys::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SumToys::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SumToys::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normaly not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("BMinus", &BMinus, &b_BMinus);
   fChain->SetBranchAddress("BMinus_err", &BMinus_err, &b_BMinus_err);
   fChain->SetBranchAddress("BMinus_aerr_lo", &BMinus_aerr_lo, &b_BMinus_aerr_lo);
   fChain->SetBranchAddress("BMinus_aerr_hi", &BMinus_aerr_hi, &b_BMinus_aerr_hi);
   fChain->SetBranchAddress("BZero", &BZero, &b_BZero);
   fChain->SetBranchAddress("BZero_err", &BZero_err, &b_BZero_err);
   fChain->SetBranchAddress("BZero_aerr_lo", &BZero_aerr_lo, &b_BZero_aerr_lo);
   fChain->SetBranchAddress("BZero_aerr_hi", &BZero_aerr_hi, &b_BZero_aerr_hi);
   fChain->SetBranchAddress("Kst1680_amp", &Kst1680_amp, &b_Kst1680_amp);
   fChain->SetBranchAddress("Kst1680_amp_err", &Kst1680_amp_err, &b_Kst1680_amp_err);
   fChain->SetBranchAddress("Kst1680_amp_aerr_lo", &Kst1680_amp_aerr_lo, &b_Kst1680_amp_aerr_lo);
   fChain->SetBranchAddress("Kst1680_amp_aerr_hi", &Kst1680_amp_aerr_hi, &b_Kst1680_amp_aerr_hi);
   fChain->SetBranchAddress("Kst1680_phase", &Kst1680_phase, &b_Kst1680_phase);
   fChain->SetBranchAddress("Kst1680_phase_err", &Kst1680_phase_err, &b_Kst1680_phase_err);
   fChain->SetBranchAddress("Kst1680_phase_aerr_lo", &Kst1680_phase_aerr_lo, &b_Kst1680_phase_aerr_lo);
   fChain->SetBranchAddress("Kst1680_phase_aerr_hi", &Kst1680_phase_aerr_hi, &b_Kst1680_phase_aerr_hi);
   fChain->SetBranchAddress("Kst2m1430_amp", &Kst2m1430_amp, &b_Kst2m1430_amp);
   fChain->SetBranchAddress("Kst2m1430_amp_err", &Kst2m1430_amp_err, &b_Kst2m1430_amp_err);
   fChain->SetBranchAddress("Kst2m1430_amp_aerr_lo", &Kst2m1430_amp_aerr_lo, &b_Kst2m1430_amp_aerr_lo);
   fChain->SetBranchAddress("Kst2m1430_amp_aerr_hi", &Kst2m1430_amp_aerr_hi, &b_Kst2m1430_amp_aerr_hi);
   fChain->SetBranchAddress("Kst2m1430_phase", &Kst2m1430_phase, &b_Kst2m1430_phase);
   fChain->SetBranchAddress("Kst2m1430_phase_err", &Kst2m1430_phase_err, &b_Kst2m1430_phase_err);
   fChain->SetBranchAddress("Kst2m1430_phase_aerr_lo", &Kst2m1430_phase_aerr_lo, &b_Kst2m1430_phase_aerr_lo);
   fChain->SetBranchAddress("Kst2m1430_phase_aerr_hi", &Kst2m1430_phase_aerr_hi, &b_Kst2m1430_phase_aerr_hi);
   fChain->SetBranchAddress("Kst2z1430_amp", &Kst2z1430_amp, &b_Kst2z1430_amp);
   fChain->SetBranchAddress("Kst2z1430_amp_err", &Kst2z1430_amp_err, &b_Kst2z1430_amp_err);
   fChain->SetBranchAddress("Kst2z1430_amp_aerr_lo", &Kst2z1430_amp_aerr_lo, &b_Kst2z1430_amp_aerr_lo);
   fChain->SetBranchAddress("Kst2z1430_amp_aerr_hi", &Kst2z1430_amp_aerr_hi, &b_Kst2z1430_amp_aerr_hi);
   fChain->SetBranchAddress("Kst2z1430_phase", &Kst2z1430_phase, &b_Kst2z1430_phase);
   fChain->SetBranchAddress("Kst2z1430_phase_err", &Kst2z1430_phase_err, &b_Kst2z1430_phase_err);
   fChain->SetBranchAddress("Kst2z1430_phase_aerr_lo", &Kst2z1430_phase_aerr_lo, &b_Kst2z1430_phase_aerr_lo);
   fChain->SetBranchAddress("Kst2z1430_phase_aerr_hi", &Kst2z1430_phase_aerr_hi, &b_Kst2z1430_phase_aerr_hi);
   fChain->SetBranchAddress("Kstm1410_amp", &Kstm1410_amp, &b_Kstm1410_amp);
   fChain->SetBranchAddress("Kstm1410_amp_err", &Kstm1410_amp_err, &b_Kstm1410_amp_err);
   fChain->SetBranchAddress("Kstm1410_amp_aerr_lo", &Kstm1410_amp_aerr_lo, &b_Kstm1410_amp_aerr_lo);
   fChain->SetBranchAddress("Kstm1410_amp_aerr_hi", &Kstm1410_amp_aerr_hi, &b_Kstm1410_amp_aerr_hi);
   fChain->SetBranchAddress("Kstm1410_phase", &Kstm1410_phase, &b_Kstm1410_phase);
   fChain->SetBranchAddress("Kstm1410_phase_err", &Kstm1410_phase_err, &b_Kstm1410_phase_err);
   fChain->SetBranchAddress("Kstm1410_phase_aerr_lo", &Kstm1410_phase_aerr_lo, &b_Kstm1410_phase_aerr_lo);
   fChain->SetBranchAddress("Kstm1410_phase_aerr_hi", &Kstm1410_phase_aerr_hi, &b_Kstm1410_phase_aerr_hi);
   fChain->SetBranchAddress("Kstm1430_CLEO_amp", &Kstm1430_CLEO_amp, &b_Kstm1430_CLEO_amp);
   fChain->SetBranchAddress("Kstm1430_CLEO_amp_err", &Kstm1430_CLEO_amp_err, &b_Kstm1430_CLEO_amp_err);
   fChain->SetBranchAddress("Kstm1430_CLEO_amp_aerr_lo", &Kstm1430_CLEO_amp_aerr_lo, &b_Kstm1430_CLEO_amp_aerr_lo);
   fChain->SetBranchAddress("Kstm1430_CLEO_amp_aerr_hi", &Kstm1430_CLEO_amp_aerr_hi, &b_Kstm1430_CLEO_amp_aerr_hi);
   fChain->SetBranchAddress("Kstm1430_CLEO_phase", &Kstm1430_CLEO_phase, &b_Kstm1430_CLEO_phase);
   fChain->SetBranchAddress("Kstm1430_CLEO_phase_err", &Kstm1430_CLEO_phase_err, &b_Kstm1430_CLEO_phase_err);
   fChain->SetBranchAddress("Kstm1430_CLEO_phase_aerr_lo", &Kstm1430_CLEO_phase_aerr_lo, &b_Kstm1430_CLEO_phase_aerr_lo);
   fChain->SetBranchAddress("Kstm1430_CLEO_phase_aerr_hi", &Kstm1430_CLEO_phase_aerr_hi, &b_Kstm1430_CLEO_phase_aerr_hi);
   fChain->SetBranchAddress("Kstm1430_amp", &Kstm1430_amp, &b_Kstm1430_amp);
   fChain->SetBranchAddress("Kstm1430_amp_err", &Kstm1430_amp_err, &b_Kstm1430_amp_err);
   fChain->SetBranchAddress("Kstm1430_amp_aerr_lo", &Kstm1430_amp_aerr_lo, &b_Kstm1430_amp_aerr_lo);
   fChain->SetBranchAddress("Kstm1430_amp_aerr_hi", &Kstm1430_amp_aerr_hi, &b_Kstm1430_amp_aerr_hi);
   fChain->SetBranchAddress("Kstm1430_mass", &Kstm1430_mass, &b_Kstm1430_mass);
   fChain->SetBranchAddress("Kstm1430_mass_err", &Kstm1430_mass_err, &b_Kstm1430_mass_err);
   fChain->SetBranchAddress("Kstm1430_mass_aerr_lo", &Kstm1430_mass_aerr_lo, &b_Kstm1430_mass_aerr_lo);
   fChain->SetBranchAddress("Kstm1430_mass_aerr_hi", &Kstm1430_mass_aerr_hi, &b_Kstm1430_mass_aerr_hi);
   fChain->SetBranchAddress("Kstm1430_phase", &Kstm1430_phase, &b_Kstm1430_phase);
   fChain->SetBranchAddress("Kstm1430_phase_err", &Kstm1430_phase_err, &b_Kstm1430_phase_err);
   fChain->SetBranchAddress("Kstm1430_phase_aerr_lo", &Kstm1430_phase_aerr_lo, &b_Kstm1430_phase_aerr_lo);
   fChain->SetBranchAddress("Kstm1430_phase_aerr_hi", &Kstm1430_phase_aerr_hi, &b_Kstm1430_phase_aerr_hi);
   fChain->SetBranchAddress("Kstm1430_width", &Kstm1430_width, &b_Kstm1430_width);
   fChain->SetBranchAddress("Kstm1430_width_err", &Kstm1430_width_err, &b_Kstm1430_width_err);
   fChain->SetBranchAddress("Kstm1430_width_aerr_lo", &Kstm1430_width_aerr_lo, &b_Kstm1430_width_aerr_lo);
   fChain->SetBranchAddress("Kstm1430_width_aerr_hi", &Kstm1430_width_aerr_hi, &b_Kstm1430_width_aerr_hi);
   fChain->SetBranchAddress("Kstminus_amp", &Kstminus_amp, &b_Kstminus_amp);
   fChain->SetBranchAddress("Kstminus_amp_err", &Kstminus_amp_err, &b_Kstminus_amp_err);
   fChain->SetBranchAddress("Kstminus_amp_aerr_lo", &Kstminus_amp_aerr_lo, &b_Kstminus_amp_aerr_lo);
   fChain->SetBranchAddress("Kstminus_amp_aerr_hi", &Kstminus_amp_aerr_hi, &b_Kstminus_amp_aerr_hi);
   fChain->SetBranchAddress("Kstminus_mass", &Kstminus_mass, &b_Kstminus_mass);
   fChain->SetBranchAddress("Kstminus_mass_err", &Kstminus_mass_err, &b_Kstminus_mass_err);
   fChain->SetBranchAddress("Kstminus_mass_aerr_lo", &Kstminus_mass_aerr_lo, &b_Kstminus_mass_aerr_lo);
   fChain->SetBranchAddress("Kstminus_mass_aerr_hi", &Kstminus_mass_aerr_hi, &b_Kstminus_mass_aerr_hi);
   fChain->SetBranchAddress("Kstminus_phase", &Kstminus_phase, &b_Kstminus_phase);
   fChain->SetBranchAddress("Kstminus_phase_err", &Kstminus_phase_err, &b_Kstminus_phase_err);
   fChain->SetBranchAddress("Kstminus_phase_aerr_lo", &Kstminus_phase_aerr_lo, &b_Kstminus_phase_aerr_lo);
   fChain->SetBranchAddress("Kstminus_phase_aerr_hi", &Kstminus_phase_aerr_hi, &b_Kstminus_phase_aerr_hi);
   fChain->SetBranchAddress("Kstminus_width", &Kstminus_width, &b_Kstminus_width);
   fChain->SetBranchAddress("Kstminus_width_err", &Kstminus_width_err, &b_Kstminus_width_err);
   fChain->SetBranchAddress("Kstminus_width_aerr_lo", &Kstminus_width_aerr_lo, &b_Kstminus_width_aerr_lo);
   fChain->SetBranchAddress("Kstminus_width_aerr_hi", &Kstminus_width_aerr_hi, &b_Kstminus_width_aerr_hi);
   fChain->SetBranchAddress("Kstz1410_amp", &Kstz1410_amp, &b_Kstz1410_amp);
   fChain->SetBranchAddress("Kstz1410_amp_err", &Kstz1410_amp_err, &b_Kstz1410_amp_err);
   fChain->SetBranchAddress("Kstz1410_amp_aerr_lo", &Kstz1410_amp_aerr_lo, &b_Kstz1410_amp_aerr_lo);
   fChain->SetBranchAddress("Kstz1410_amp_aerr_hi", &Kstz1410_amp_aerr_hi, &b_Kstz1410_amp_aerr_hi);
   fChain->SetBranchAddress("Kstz1410_phase", &Kstz1410_phase, &b_Kstz1410_phase);
   fChain->SetBranchAddress("Kstz1410_phase_err", &Kstz1410_phase_err, &b_Kstz1410_phase_err);
   fChain->SetBranchAddress("Kstz1410_phase_aerr_lo", &Kstz1410_phase_aerr_lo, &b_Kstz1410_phase_aerr_lo);
   fChain->SetBranchAddress("Kstz1410_phase_aerr_hi", &Kstz1410_phase_aerr_hi, &b_Kstz1410_phase_aerr_hi);
   fChain->SetBranchAddress("Kstz1430_CLEO_amp", &Kstz1430_CLEO_amp, &b_Kstz1430_CLEO_amp);
   fChain->SetBranchAddress("Kstz1430_CLEO_amp_err", &Kstz1430_CLEO_amp_err, &b_Kstz1430_CLEO_amp_err);
   fChain->SetBranchAddress("Kstz1430_CLEO_amp_aerr_lo", &Kstz1430_CLEO_amp_aerr_lo, &b_Kstz1430_CLEO_amp_aerr_lo);
   fChain->SetBranchAddress("Kstz1430_CLEO_amp_aerr_hi", &Kstz1430_CLEO_amp_aerr_hi, &b_Kstz1430_CLEO_amp_aerr_hi);
   fChain->SetBranchAddress("Kstz1430_CLEO_phase", &Kstz1430_CLEO_phase, &b_Kstz1430_CLEO_phase);
   fChain->SetBranchAddress("Kstz1430_CLEO_phase_err", &Kstz1430_CLEO_phase_err, &b_Kstz1430_CLEO_phase_err);
   fChain->SetBranchAddress("Kstz1430_CLEO_phase_aerr_lo", &Kstz1430_CLEO_phase_aerr_lo, &b_Kstz1430_CLEO_phase_aerr_lo);
   fChain->SetBranchAddress("Kstz1430_CLEO_phase_aerr_hi", &Kstz1430_CLEO_phase_aerr_hi, &b_Kstz1430_CLEO_phase_aerr_hi);
   fChain->SetBranchAddress("Kstz1430_amp", &Kstz1430_amp, &b_Kstz1430_amp);
   fChain->SetBranchAddress("Kstz1430_amp_err", &Kstz1430_amp_err, &b_Kstz1430_amp_err);
   fChain->SetBranchAddress("Kstz1430_amp_aerr_lo", &Kstz1430_amp_aerr_lo, &b_Kstz1430_amp_aerr_lo);
   fChain->SetBranchAddress("Kstz1430_amp_aerr_hi", &Kstz1430_amp_aerr_hi, &b_Kstz1430_amp_aerr_hi);
   fChain->SetBranchAddress("Kstz1430_mass", &Kstz1430_mass, &b_Kstz1430_mass);
   fChain->SetBranchAddress("Kstz1430_mass_err", &Kstz1430_mass_err, &b_Kstz1430_mass_err);
   fChain->SetBranchAddress("Kstz1430_mass_aerr_lo", &Kstz1430_mass_aerr_lo, &b_Kstz1430_mass_aerr_lo);
   fChain->SetBranchAddress("Kstz1430_mass_aerr_hi", &Kstz1430_mass_aerr_hi, &b_Kstz1430_mass_aerr_hi);
   fChain->SetBranchAddress("Kstz1430_phase", &Kstz1430_phase, &b_Kstz1430_phase);
   fChain->SetBranchAddress("Kstz1430_phase_err", &Kstz1430_phase_err, &b_Kstz1430_phase_err);
   fChain->SetBranchAddress("Kstz1430_phase_aerr_lo", &Kstz1430_phase_aerr_lo, &b_Kstz1430_phase_aerr_lo);
   fChain->SetBranchAddress("Kstz1430_phase_aerr_hi", &Kstz1430_phase_aerr_hi, &b_Kstz1430_phase_aerr_hi);
   fChain->SetBranchAddress("Kstz1430_width", &Kstz1430_width, &b_Kstz1430_width);
   fChain->SetBranchAddress("Kstz1430_width_err", &Kstz1430_width_err, &b_Kstz1430_width_err);
   fChain->SetBranchAddress("Kstz1430_width_aerr_lo", &Kstz1430_width_aerr_lo, &b_Kstz1430_width_aerr_lo);
   fChain->SetBranchAddress("Kstz1430_width_aerr_hi", &Kstz1430_width_aerr_hi, &b_Kstz1430_width_aerr_hi);
   fChain->SetBranchAddress("Kstz1680_amp", &Kstz1680_amp, &b_Kstz1680_amp);
   fChain->SetBranchAddress("Kstz1680_amp_err", &Kstz1680_amp_err, &b_Kstz1680_amp_err);
   fChain->SetBranchAddress("Kstz1680_amp_aerr_lo", &Kstz1680_amp_aerr_lo, &b_Kstz1680_amp_aerr_lo);
   fChain->SetBranchAddress("Kstz1680_amp_aerr_hi", &Kstz1680_amp_aerr_hi, &b_Kstz1680_amp_aerr_hi);
   fChain->SetBranchAddress("Kstz1680_phase", &Kstz1680_phase, &b_Kstz1680_phase);
   fChain->SetBranchAddress("Kstz1680_phase_err", &Kstz1680_phase_err, &b_Kstz1680_phase_err);
   fChain->SetBranchAddress("Kstz1680_phase_aerr_lo", &Kstz1680_phase_aerr_lo, &b_Kstz1680_phase_aerr_lo);
   fChain->SetBranchAddress("Kstz1680_phase_aerr_hi", &Kstz1680_phase_aerr_hi, &b_Kstz1680_phase_aerr_hi);
   fChain->SetBranchAddress("Kstzero_amp", &Kstzero_amp, &b_Kstzero_amp);
   fChain->SetBranchAddress("Kstzero_amp_err", &Kstzero_amp_err, &b_Kstzero_amp_err);
   fChain->SetBranchAddress("Kstzero_amp_aerr_lo", &Kstzero_amp_aerr_lo, &b_Kstzero_amp_aerr_lo);
   fChain->SetBranchAddress("Kstzero_amp_aerr_hi", &Kstzero_amp_aerr_hi, &b_Kstzero_amp_aerr_hi);
   fChain->SetBranchAddress("Kstzero_mass", &Kstzero_mass, &b_Kstzero_mass);
   fChain->SetBranchAddress("Kstzero_mass_err", &Kstzero_mass_err, &b_Kstzero_mass_err);
   fChain->SetBranchAddress("Kstzero_mass_aerr_lo", &Kstzero_mass_aerr_lo, &b_Kstzero_mass_aerr_lo);
   fChain->SetBranchAddress("Kstzero_mass_aerr_hi", &Kstzero_mass_aerr_hi, &b_Kstzero_mass_aerr_hi);
   fChain->SetBranchAddress("Kstzero_phase", &Kstzero_phase, &b_Kstzero_phase);
   fChain->SetBranchAddress("Kstzero_phase_err", &Kstzero_phase_err, &b_Kstzero_phase_err);
   fChain->SetBranchAddress("Kstzero_phase_aerr_lo", &Kstzero_phase_aerr_lo, &b_Kstzero_phase_aerr_lo);
   fChain->SetBranchAddress("Kstzero_phase_aerr_hi", &Kstzero_phase_aerr_hi, &b_Kstzero_phase_aerr_hi);
   fChain->SetBranchAddress("Kstzero_width", &Kstzero_width, &b_Kstzero_width);
   fChain->SetBranchAddress("Kstzero_width_err", &Kstzero_width_err, &b_Kstzero_width_err);
   fChain->SetBranchAddress("Kstzero_width_aerr_lo", &Kstzero_width_aerr_lo, &b_Kstzero_width_aerr_lo);
   fChain->SetBranchAddress("Kstzero_width_aerr_hi", &Kstzero_width_aerr_hi, &b_Kstzero_width_aerr_hi);
   fChain->SetBranchAddress("N1", &N1, &b_N1);
   fChain->SetBranchAddress("N1_err", &N1_err, &b_N1_err);
   fChain->SetBranchAddress("N1_aerr_lo", &N1_aerr_lo, &b_N1_aerr_lo);
   fChain->SetBranchAddress("N1_aerr_hi", &N1_aerr_hi, &b_N1_aerr_hi);
   fChain->SetBranchAddress("N2", &N2, &b_N2);
   fChain->SetBranchAddress("N2_err", &N2_err, &b_N2_err);
   fChain->SetBranchAddress("N2_aerr_lo", &N2_aerr_lo, &b_N2_aerr_lo);
   fChain->SetBranchAddress("N2_aerr_hi", &N2_aerr_hi, &b_N2_aerr_hi);
   fChain->SetBranchAddress("Ncomb", &Ncomb, &b_Ncomb);
   fChain->SetBranchAddress("Ncomb_err", &Ncomb_err, &b_Ncomb_err);
   fChain->SetBranchAddress("Ncomb_aerr_lo", &Ncomb_aerr_lo, &b_Ncomb_aerr_lo);
   fChain->SetBranchAddress("Ncomb_aerr_hi", &Ncomb_aerr_hi, &b_Ncomb_aerr_hi);
   fChain->SetBranchAddress("Nmis", &Nmis, &b_Nmis);
   fChain->SetBranchAddress("Nmis_err", &Nmis_err, &b_Nmis_err);
   fChain->SetBranchAddress("Nmis_aerr_lo", &Nmis_aerr_lo, &b_Nmis_aerr_lo);
   fChain->SetBranchAddress("Nmis_aerr_hi", &Nmis_aerr_hi, &b_Nmis_aerr_hi);
   fChain->SetBranchAddress("NonReson_amp", &NonReson_amp, &b_NonReson_amp);
   fChain->SetBranchAddress("NonReson_amp_err", &NonReson_amp_err, &b_NonReson_amp_err);
   fChain->SetBranchAddress("NonReson_amp_aerr_lo", &NonReson_amp_aerr_lo, &b_NonReson_amp_aerr_lo);
   fChain->SetBranchAddress("NonReson_amp_aerr_hi", &NonReson_amp_aerr_hi, &b_NonReson_amp_aerr_hi);
   fChain->SetBranchAddress("NonReson_phase", &NonReson_phase, &b_NonReson_phase);
   fChain->SetBranchAddress("NonReson_phase_err", &NonReson_phase_err, &b_NonReson_phase_err);
   fChain->SetBranchAddress("NonReson_phase_aerr_lo", &NonReson_phase_aerr_lo, &b_NonReson_phase_aerr_lo);
   fChain->SetBranchAddress("NonReson_phase_aerr_hi", &NonReson_phase_aerr_hi, &b_NonReson_phase_aerr_hi);
   fChain->SetBranchAddress("Nsig", &Nsig, &b_Nsig);
   fChain->SetBranchAddress("Nsig_err", &Nsig_err, &b_Nsig_err);
   fChain->SetBranchAddress("Nsig_aerr_lo", &Nsig_aerr_lo, &b_Nsig_aerr_lo);
   fChain->SetBranchAddress("Nsig_aerr_hi", &Nsig_aerr_hi, &b_Nsig_aerr_hi);
   fChain->SetBranchAddress("RMinus", &RMinus, &b_RMinus);
   fChain->SetBranchAddress("RMinus_err", &RMinus_err, &b_RMinus_err);
   fChain->SetBranchAddress("RMinus_aerr_lo", &RMinus_aerr_lo, &b_RMinus_aerr_lo);
   fChain->SetBranchAddress("RMinus_aerr_hi", &RMinus_aerr_hi, &b_RMinus_aerr_hi);
   fChain->SetBranchAddress("RZero", &RZero, &b_RZero);
   fChain->SetBranchAddress("RZero_err", &RZero_err, &b_RZero_err);
   fChain->SetBranchAddress("RZero_aerr_lo", &RZero_aerr_lo, &b_RZero_aerr_lo);
   fChain->SetBranchAddress("RZero_aerr_hi", &RZero_aerr_hi, &b_RZero_aerr_hi);
   fChain->SetBranchAddress("Rho1450_amp", &Rho1450_amp, &b_Rho1450_amp);
   fChain->SetBranchAddress("Rho1450_amp_err", &Rho1450_amp_err, &b_Rho1450_amp_err);
   fChain->SetBranchAddress("Rho1450_amp_aerr_lo", &Rho1450_amp_aerr_lo, &b_Rho1450_amp_aerr_lo);
   fChain->SetBranchAddress("Rho1450_amp_aerr_hi", &Rho1450_amp_aerr_hi, &b_Rho1450_amp_aerr_hi);
   fChain->SetBranchAddress("Rho1450_phase", &Rho1450_phase, &b_Rho1450_phase);
   fChain->SetBranchAddress("Rho1450_phase_err", &Rho1450_phase_err, &b_Rho1450_phase_err);
   fChain->SetBranchAddress("Rho1450_phase_aerr_lo", &Rho1450_phase_aerr_lo, &b_Rho1450_phase_aerr_lo);
   fChain->SetBranchAddress("Rho1450_phase_aerr_hi", &Rho1450_phase_aerr_hi, &b_Rho1450_phase_aerr_hi);
   fChain->SetBranchAddress("Rho1700_amp", &Rho1700_amp, &b_Rho1700_amp);
   fChain->SetBranchAddress("Rho1700_amp_err", &Rho1700_amp_err, &b_Rho1700_amp_err);
   fChain->SetBranchAddress("Rho1700_amp_aerr_lo", &Rho1700_amp_aerr_lo, &b_Rho1700_amp_aerr_lo);
   fChain->SetBranchAddress("Rho1700_amp_aerr_hi", &Rho1700_amp_aerr_hi, &b_Rho1700_amp_aerr_hi);
   fChain->SetBranchAddress("Rho1700_mass", &Rho1700_mass, &b_Rho1700_mass);
   fChain->SetBranchAddress("Rho1700_mass_err", &Rho1700_mass_err, &b_Rho1700_mass_err);
   fChain->SetBranchAddress("Rho1700_mass_aerr_lo", &Rho1700_mass_aerr_lo, &b_Rho1700_mass_aerr_lo);
   fChain->SetBranchAddress("Rho1700_mass_aerr_hi", &Rho1700_mass_aerr_hi, &b_Rho1700_mass_aerr_hi);
   fChain->SetBranchAddress("Rho1700_phase", &Rho1700_phase, &b_Rho1700_phase);
   fChain->SetBranchAddress("Rho1700_phase_err", &Rho1700_phase_err, &b_Rho1700_phase_err);
   fChain->SetBranchAddress("Rho1700_phase_aerr_lo", &Rho1700_phase_aerr_lo, &b_Rho1700_phase_aerr_lo);
   fChain->SetBranchAddress("Rho1700_phase_aerr_hi", &Rho1700_phase_aerr_hi, &b_Rho1700_phase_aerr_hi);
   fChain->SetBranchAddress("Rho1700_width", &Rho1700_width, &b_Rho1700_width);
   fChain->SetBranchAddress("Rho1700_width_err", &Rho1700_width_err, &b_Rho1700_width_err);
   fChain->SetBranchAddress("Rho1700_width_aerr_lo", &Rho1700_width_aerr_lo, &b_Rho1700_width_aerr_lo);
   fChain->SetBranchAddress("Rho1700_width_aerr_hi", &Rho1700_width_aerr_hi, &b_Rho1700_width_aerr_hi);
   fChain->SetBranchAddress("Rho_amp", &Rho_amp, &b_Rho_amp);
   fChain->SetBranchAddress("Rho_amp_err", &Rho_amp_err, &b_Rho_amp_err);
   fChain->SetBranchAddress("Rho_amp_aerr_lo", &Rho_amp_aerr_lo, &b_Rho_amp_aerr_lo);
   fChain->SetBranchAddress("Rho_amp_aerr_hi", &Rho_amp_aerr_hi, &b_Rho_amp_aerr_hi);
   fChain->SetBranchAddress("Rho_mass", &Rho_mass, &b_Rho_mass);
   fChain->SetBranchAddress("Rho_mass_err", &Rho_mass_err, &b_Rho_mass_err);
   fChain->SetBranchAddress("Rho_mass_aerr_lo", &Rho_mass_aerr_lo, &b_Rho_mass_aerr_lo);
   fChain->SetBranchAddress("Rho_mass_aerr_hi", &Rho_mass_aerr_hi, &b_Rho_mass_aerr_hi);
   fChain->SetBranchAddress("Rho_phase", &Rho_phase, &b_Rho_phase);
   fChain->SetBranchAddress("Rho_phase_err", &Rho_phase_err, &b_Rho_phase_err);
   fChain->SetBranchAddress("Rho_phase_aerr_lo", &Rho_phase_aerr_lo, &b_Rho_phase_aerr_lo);
   fChain->SetBranchAddress("Rho_phase_aerr_hi", &Rho_phase_aerr_hi, &b_Rho_phase_aerr_hi);
   fChain->SetBranchAddress("Rho_width", &Rho_width, &b_Rho_width);
   fChain->SetBranchAddress("Rho_width_err", &Rho_width_err, &b_Rho_width_err);
   fChain->SetBranchAddress("Rho_width_aerr_lo", &Rho_width_aerr_lo, &b_Rho_width_aerr_lo);
   fChain->SetBranchAddress("Rho_width_aerr_hi", &Rho_width_aerr_hi, &b_Rho_width_aerr_hi);
   fChain->SetBranchAddress("aMinus", &aMinus, &b_aMinus);
   fChain->SetBranchAddress("aMinus_err", &aMinus_err, &b_aMinus_err);
   fChain->SetBranchAddress("aMinus_aerr_lo", &aMinus_aerr_lo, &b_aMinus_aerr_lo);
   fChain->SetBranchAddress("aMinus_aerr_hi", &aMinus_aerr_hi, &b_aMinus_aerr_hi);
   fChain->SetBranchAddress("aZero", &aZero, &b_aZero);
   fChain->SetBranchAddress("aZero_err", &aZero_err, &b_aZero_err);
   fChain->SetBranchAddress("aZero_aerr_lo", &aZero_aerr_lo, &b_aZero_aerr_lo);
   fChain->SetBranchAddress("aZero_aerr_hi", &aZero_aerr_hi, &b_aZero_aerr_hi);
   fChain->SetBranchAddress("bias", &bias, &b_bias);
   fChain->SetBranchAddress("bias_err", &bias_err, &b_bias_err);
   fChain->SetBranchAddress("bias_aerr_lo", &bias_aerr_lo, &b_bias_aerr_lo);
   fChain->SetBranchAddress("bias_aerr_hi", &bias_aerr_hi, &b_bias_aerr_hi);
   fChain->SetBranchAddress("c1", &c1, &b_c1);
   fChain->SetBranchAddress("c1_err", &c1_err, &b_c1_err);
   fChain->SetBranchAddress("c1_aerr_lo", &c1_aerr_lo, &b_c1_aerr_lo);
   fChain->SetBranchAddress("c1_aerr_hi", &c1_aerr_hi, &b_c1_aerr_hi);
   fChain->SetBranchAddress("c1err", &c1err, &b_c1err);
   fChain->SetBranchAddress("c1pull", &c1pull, &b_c1pull);
   fChain->SetBranchAddress("c2", &c2, &b_c2);
   fChain->SetBranchAddress("c2_err", &c2_err, &b_c2_err);
   fChain->SetBranchAddress("c2_aerr_lo", &c2_aerr_lo, &b_c2_aerr_lo);
   fChain->SetBranchAddress("c2_aerr_hi", &c2_aerr_hi, &b_c2_aerr_hi);
   fChain->SetBranchAddress("c2err", &c2err, &b_c2err);
   fChain->SetBranchAddress("c2pull", &c2pull, &b_c2pull);
   fChain->SetBranchAddress("c1m", &c1m, &b_c1m);
   fChain->SetBranchAddress("c1m_err", &c1m_err, &b_c1m_err);
   fChain->SetBranchAddress("c1m_aerr_lo", &c1m_aerr_lo, &b_c1m_aerr_lo);
   fChain->SetBranchAddress("c1m_aerr_hi", &c1m_aerr_hi, &b_c1m_aerr_hi);
   fChain->SetBranchAddress("c1p", &c1p, &b_c1p);
   fChain->SetBranchAddress("c1p_err", &c1p_err, &b_c1p_err);
   fChain->SetBranchAddress("c1p_aerr_lo", &c1p_aerr_lo, &b_c1p_aerr_lo);
   fChain->SetBranchAddress("c1p_aerr_hi", &c1p_aerr_hi, &b_c1p_aerr_hi);
   fChain->SetBranchAddress("c2m", &c2m, &b_c2m);
   fChain->SetBranchAddress("c2m_err", &c2m_err, &b_c2m_err);
   fChain->SetBranchAddress("c2m_aerr_lo", &c2m_aerr_lo, &b_c2m_aerr_lo);
   fChain->SetBranchAddress("c2m_aerr_hi", &c2m_aerr_hi, &b_c2m_aerr_hi);
   fChain->SetBranchAddress("c2p", &c2p, &b_c2p);
   fChain->SetBranchAddress("c2p_err", &c2p_err, &b_c2p_err);
   fChain->SetBranchAddress("c2p_aerr_lo", &c2p_aerr_lo, &b_c2p_aerr_lo);
   fChain->SetBranchAddress("c2p_aerr_hi", &c2p_aerr_hi, &b_c2p_aerr_hi);
   fChain->SetBranchAddress("one", &one, &b_one);
   fChain->SetBranchAddress("one_err", &one_err, &b_one_err);
   fChain->SetBranchAddress("one_aerr_lo", &one_aerr_lo, &b_one_aerr_lo);
   fChain->SetBranchAddress("one_aerr_hi", &one_aerr_hi, &b_one_aerr_hi);
   fChain->SetBranchAddress("phiBMinus", &phiBMinus, &b_phiBMinus);
   fChain->SetBranchAddress("phiBMinus_err", &phiBMinus_err, &b_phiBMinus_err);
   fChain->SetBranchAddress("phiBMinus_aerr_lo", &phiBMinus_aerr_lo, &b_phiBMinus_aerr_lo);
   fChain->SetBranchAddress("phiBMinus_aerr_hi", &phiBMinus_aerr_hi, &b_phiBMinus_aerr_hi);
   fChain->SetBranchAddress("phiBZero", &phiBZero, &b_phiBZero);
   fChain->SetBranchAddress("phiBZero_err", &phiBZero_err, &b_phiBZero_err);
   fChain->SetBranchAddress("phiBZero_aerr_lo", &phiBZero_aerr_lo, &b_phiBZero_aerr_lo);
   fChain->SetBranchAddress("phiBZero_aerr_hi", &phiBZero_aerr_hi, &b_phiBZero_aerr_hi);
   fChain->SetBranchAddress("phiRMinus", &phiRMinus, &b_phiRMinus);
   fChain->SetBranchAddress("phiRMinus_err", &phiRMinus_err, &b_phiRMinus_err);
   fChain->SetBranchAddress("phiRMinus_aerr_lo", &phiRMinus_aerr_lo, &b_phiRMinus_aerr_lo);
   fChain->SetBranchAddress("phiRMinus_aerr_hi", &phiRMinus_aerr_hi, &b_phiRMinus_aerr_hi);
   fChain->SetBranchAddress("phiRZero", &phiRZero, &b_phiRZero);
   fChain->SetBranchAddress("phiRZero_err", &phiRZero_err, &b_phiRZero_err);
   fChain->SetBranchAddress("phiRZero_aerr_lo", &phiRZero_aerr_lo, &b_phiRZero_aerr_lo);
   fChain->SetBranchAddress("phiRZero_aerr_hi", &phiRZero_aerr_hi, &b_phiRZero_aerr_hi);
   fChain->SetBranchAddress("rMinus", &rMinus, &b_rMinus);
   fChain->SetBranchAddress("rMinus_err", &rMinus_err, &b_rMinus_err);
   fChain->SetBranchAddress("rMinus_aerr_lo", &rMinus_aerr_lo, &b_rMinus_aerr_lo);
   fChain->SetBranchAddress("rMinus_aerr_hi", &rMinus_aerr_hi, &b_rMinus_aerr_hi);
   fChain->SetBranchAddress("rZero", &rZero, &b_rZero);
   fChain->SetBranchAddress("rZero_err", &rZero_err, &b_rZero_err);
   fChain->SetBranchAddress("rZero_aerr_lo", &rZero_aerr_lo, &b_rZero_aerr_lo);
   fChain->SetBranchAddress("rZero_aerr_hi", &rZero_aerr_hi, &b_rZero_aerr_hi);
   fChain->SetBranchAddress("scalefact1", &scalefact1, &b_scalefact1);
   fChain->SetBranchAddress("scalefact1_err", &scalefact1_err, &b_scalefact1_err);
   fChain->SetBranchAddress("scalefact1_aerr_lo", &scalefact1_aerr_lo, &b_scalefact1_aerr_lo);
   fChain->SetBranchAddress("scalefact1_aerr_hi", &scalefact1_aerr_hi, &b_scalefact1_aerr_hi);
   fChain->SetBranchAddress("scalefact2", &scalefact2, &b_scalefact2);
   fChain->SetBranchAddress("scalefact2_err", &scalefact2_err, &b_scalefact2_err);
   fChain->SetBranchAddress("scalefact2_aerr_lo", &scalefact2_aerr_lo, &b_scalefact2_aerr_lo);
   fChain->SetBranchAddress("scalefact2_aerr_hi", &scalefact2_aerr_hi, &b_scalefact2_aerr_hi);
   fChain->SetBranchAddress("scalefact3", &scalefact3, &b_scalefact3);
   fChain->SetBranchAddress("scalefact3_err", &scalefact3_err, &b_scalefact3_err);
   fChain->SetBranchAddress("scalefact3_aerr_lo", &scalefact3_aerr_lo, &b_scalefact3_aerr_lo);
   fChain->SetBranchAddress("scalefact3_aerr_hi", &scalefact3_aerr_hi, &b_scalefact3_aerr_hi);
   fChain->SetBranchAddress("tau", &tau, &b_tau);
   fChain->SetBranchAddress("tau_err", &tau_err, &b_tau_err);
   fChain->SetBranchAddress("tau_aerr_lo", &tau_aerr_lo, &b_tau_aerr_lo);
   fChain->SetBranchAddress("tau_aerr_hi", &tau_aerr_hi, &b_tau_aerr_hi);
   fChain->SetBranchAddress("NLL", &NLL, &b_NLL);
   fChain->SetBranchAddress("NLL_err", &NLL_err, &b_NLL_err);
   fChain->SetBranchAddress("NLL_aerr_lo", &NLL_aerr_lo, &b_NLL_aerr_lo);
   fChain->SetBranchAddress("NLL_aerr_hi", &NLL_aerr_hi, &b_NLL_aerr_hi);
   fChain->SetBranchAddress("BMinuserr", &BMinuserr, &b_BMinuserr);
   fChain->SetBranchAddress("BMinuspull", &BMinuspull, &b_BMinuspull);
   fChain->SetBranchAddress("BZeroerr", &BZeroerr, &b_BZeroerr);
   fChain->SetBranchAddress("BZeropull", &BZeropull, &b_BZeropull);
   fChain->SetBranchAddress("Kst1680_amperr", &Kst1680_amperr, &b_Kst1680_amperr);
   fChain->SetBranchAddress("Kst1680_amppull", &Kst1680_amppull, &b_Kst1680_amppull);
   fChain->SetBranchAddress("Kst1680_phaseerr", &Kst1680_phaseerr, &b_Kst1680_phaseerr);
   fChain->SetBranchAddress("Kst1680_phasepull", &Kst1680_phasepull, &b_Kst1680_phasepull);
   fChain->SetBranchAddress("Kst2m1430_amperr", &Kst2m1430_amperr, &b_Kst2m1430_amperr);
   fChain->SetBranchAddress("Kst2m1430_amppull", &Kst2m1430_amppull, &b_Kst2m1430_amppull);
   fChain->SetBranchAddress("Kst2m1430_phaseerr", &Kst2m1430_phaseerr, &b_Kst2m1430_phaseerr);
   fChain->SetBranchAddress("Kst2m1430_phasepull", &Kst2m1430_phasepull, &b_Kst2m1430_phasepull);
   fChain->SetBranchAddress("Kst2z1430_amperr", &Kst2z1430_amperr, &b_Kst2z1430_amperr);
   fChain->SetBranchAddress("Kst2z1430_amppull", &Kst2z1430_amppull, &b_Kst2z1430_amppull);
   fChain->SetBranchAddress("Kst2z1430_phaseerr", &Kst2z1430_phaseerr, &b_Kst2z1430_phaseerr);
   fChain->SetBranchAddress("Kst2z1430_phasepull", &Kst2z1430_phasepull, &b_Kst2z1430_phasepull);
   fChain->SetBranchAddress("Kstm1410_amperr", &Kstm1410_amperr, &b_Kstm1410_amperr);
   fChain->SetBranchAddress("Kstm1410_amppull", &Kstm1410_amppull, &b_Kstm1410_amppull);
   fChain->SetBranchAddress("Kstm1410_phaseerr", &Kstm1410_phaseerr, &b_Kstm1410_phaseerr);
   fChain->SetBranchAddress("Kstm1410_phasepull", &Kstm1410_phasepull, &b_Kstm1410_phasepull);
   fChain->SetBranchAddress("Kstm1430_CLEO_amperr", &Kstm1430_CLEO_amperr, &b_Kstm1430_CLEO_amperr);
   fChain->SetBranchAddress("Kstm1430_CLEO_amppull", &Kstm1430_CLEO_amppull, &b_Kstm1430_CLEO_amppull);
   fChain->SetBranchAddress("Kstm1430_CLEO_phaseerr", &Kstm1430_CLEO_phaseerr, &b_Kstm1430_CLEO_phaseerr);
   fChain->SetBranchAddress("Kstm1430_CLEO_phasepull", &Kstm1430_CLEO_phasepull, &b_Kstm1430_CLEO_phasepull);
   fChain->SetBranchAddress("Kstm1430_amperr", &Kstm1430_amperr, &b_Kstm1430_amperr);
   fChain->SetBranchAddress("Kstm1430_amppull", &Kstm1430_amppull, &b_Kstm1430_amppull);
   fChain->SetBranchAddress("Kstm1430_masserr", &Kstm1430_masserr, &b_Kstm1430_masserr);
   fChain->SetBranchAddress("Kstm1430_masspull", &Kstm1430_masspull, &b_Kstm1430_masspull);
   fChain->SetBranchAddress("Kstm1430_phaseerr", &Kstm1430_phaseerr, &b_Kstm1430_phaseerr);
   fChain->SetBranchAddress("Kstm1430_phasepull", &Kstm1430_phasepull, &b_Kstm1430_phasepull);
   fChain->SetBranchAddress("Kstm1430_widtherr", &Kstm1430_widtherr, &b_Kstm1430_widtherr);
   fChain->SetBranchAddress("Kstm1430_widthpull", &Kstm1430_widthpull, &b_Kstm1430_widthpull);
   fChain->SetBranchAddress("Kstminus_amperr", &Kstminus_amperr, &b_Kstminus_amperr);
   fChain->SetBranchAddress("Kstminus_amppull", &Kstminus_amppull, &b_Kstminus_amppull);
   fChain->SetBranchAddress("Kstminus_masserr", &Kstminus_masserr, &b_Kstminus_masserr);
   fChain->SetBranchAddress("Kstminus_masspull", &Kstminus_masspull, &b_Kstminus_masspull);
   fChain->SetBranchAddress("Kstminus_phaseerr", &Kstminus_phaseerr, &b_Kstminus_phaseerr);
   fChain->SetBranchAddress("Kstminus_phasepull", &Kstminus_phasepull, &b_Kstminus_phasepull);
   fChain->SetBranchAddress("Kstminus_widtherr", &Kstminus_widtherr, &b_Kstminus_widtherr);
   fChain->SetBranchAddress("Kstminus_widthpull", &Kstminus_widthpull, &b_Kstminus_widthpull);
   fChain->SetBranchAddress("Kstz1410_amperr", &Kstz1410_amperr, &b_Kstz1410_amperr);
   fChain->SetBranchAddress("Kstz1410_amppull", &Kstz1410_amppull, &b_Kstz1410_amppull);
   fChain->SetBranchAddress("Kstz1410_phaseerr", &Kstz1410_phaseerr, &b_Kstz1410_phaseerr);
   fChain->SetBranchAddress("Kstz1410_phasepull", &Kstz1410_phasepull, &b_Kstz1410_phasepull);
   fChain->SetBranchAddress("Kstz1430_CLEO_amperr", &Kstz1430_CLEO_amperr, &b_Kstz1430_CLEO_amperr);
   fChain->SetBranchAddress("Kstz1430_CLEO_amppull", &Kstz1430_CLEO_amppull, &b_Kstz1430_CLEO_amppull);
   fChain->SetBranchAddress("Kstz1430_CLEO_phaseerr", &Kstz1430_CLEO_phaseerr, &b_Kstz1430_CLEO_phaseerr);
   fChain->SetBranchAddress("Kstz1430_CLEO_phasepull", &Kstz1430_CLEO_phasepull, &b_Kstz1430_CLEO_phasepull);
   fChain->SetBranchAddress("Kstz1430_amperr", &Kstz1430_amperr, &b_Kstz1430_amperr);
   fChain->SetBranchAddress("Kstz1430_amppull", &Kstz1430_amppull, &b_Kstz1430_amppull);
   fChain->SetBranchAddress("Kstz1430_masserr", &Kstz1430_masserr, &b_Kstz1430_masserr);
   fChain->SetBranchAddress("Kstz1430_masspull", &Kstz1430_masspull, &b_Kstz1430_masspull);
   fChain->SetBranchAddress("Kstz1430_phaseerr", &Kstz1430_phaseerr, &b_Kstz1430_phaseerr);
   fChain->SetBranchAddress("Kstz1430_phasepull", &Kstz1430_phasepull, &b_Kstz1430_phasepull);
   fChain->SetBranchAddress("Kstz1430_widtherr", &Kstz1430_widtherr, &b_Kstz1430_widtherr);
   fChain->SetBranchAddress("Kstz1430_widthpull", &Kstz1430_widthpull, &b_Kstz1430_widthpull);
   fChain->SetBranchAddress("Kstz1680_amperr", &Kstz1680_amperr, &b_Kstz1680_amperr);
   fChain->SetBranchAddress("Kstz1680_amppull", &Kstz1680_amppull, &b_Kstz1680_amppull);
   fChain->SetBranchAddress("Kstz1680_phaseerr", &Kstz1680_phaseerr, &b_Kstz1680_phaseerr);
   fChain->SetBranchAddress("Kstz1680_phasepull", &Kstz1680_phasepull, &b_Kstz1680_phasepull);
   fChain->SetBranchAddress("Kstzero_amperr", &Kstzero_amperr, &b_Kstzero_amperr);
   fChain->SetBranchAddress("Kstzero_amppull", &Kstzero_amppull, &b_Kstzero_amppull);
   fChain->SetBranchAddress("Kstzero_masserr", &Kstzero_masserr, &b_Kstzero_masserr);
   fChain->SetBranchAddress("Kstzero_masspull", &Kstzero_masspull, &b_Kstzero_masspull);
   fChain->SetBranchAddress("Kstzero_phaseerr", &Kstzero_phaseerr, &b_Kstzero_phaseerr);
   fChain->SetBranchAddress("Kstzero_phasepull", &Kstzero_phasepull, &b_Kstzero_phasepull);
   fChain->SetBranchAddress("Kstzero_widtherr", &Kstzero_widtherr, &b_Kstzero_widtherr);
   fChain->SetBranchAddress("Kstzero_widthpull", &Kstzero_widthpull, &b_Kstzero_widthpull);
   fChain->SetBranchAddress("N1err", &N1err, &b_N1err);
   fChain->SetBranchAddress("N1pull", &N1pull, &b_N1pull);
   fChain->SetBranchAddress("N2err", &N2err, &b_N2err);
   fChain->SetBranchAddress("N2pull", &N2pull, &b_N2pull);
   fChain->SetBranchAddress("Ncomberr", &Ncomberr, &b_Ncomberr);
   fChain->SetBranchAddress("Ncombpull", &Ncombpull, &b_Ncombpull);
   fChain->SetBranchAddress("Nmiserr", &Nmiserr, &b_Nmiserr);
   fChain->SetBranchAddress("Nmispull", &Nmispull, &b_Nmispull);
   fChain->SetBranchAddress("NonReson_amperr", &NonReson_amperr, &b_NonReson_amperr);
   fChain->SetBranchAddress("NonReson_amppull", &NonReson_amppull, &b_NonReson_amppull);
   fChain->SetBranchAddress("NonReson_phaseerr", &NonReson_phaseerr, &b_NonReson_phaseerr);
   fChain->SetBranchAddress("NonReson_phasepull", &NonReson_phasepull, &b_NonReson_phasepull);
   fChain->SetBranchAddress("Nsigerr", &Nsigerr, &b_Nsigerr);
   fChain->SetBranchAddress("Nsigpull", &Nsigpull, &b_Nsigpull);
   fChain->SetBranchAddress("RMinuserr", &RMinuserr, &b_RMinuserr);
   fChain->SetBranchAddress("RMinuspull", &RMinuspull, &b_RMinuspull);
   fChain->SetBranchAddress("RZeroerr", &RZeroerr, &b_RZeroerr);
   fChain->SetBranchAddress("RZeropull", &RZeropull, &b_RZeropull);
   fChain->SetBranchAddress("Rho1450_amperr", &Rho1450_amperr, &b_Rho1450_amperr);
   fChain->SetBranchAddress("Rho1450_amppull", &Rho1450_amppull, &b_Rho1450_amppull);
   fChain->SetBranchAddress("Rho1450_phaseerr", &Rho1450_phaseerr, &b_Rho1450_phaseerr);
   fChain->SetBranchAddress("Rho1450_phasepull", &Rho1450_phasepull, &b_Rho1450_phasepull);
   fChain->SetBranchAddress("Rho1700_amperr", &Rho1700_amperr, &b_Rho1700_amperr);
   fChain->SetBranchAddress("Rho1700_amppull", &Rho1700_amppull, &b_Rho1700_amppull);
   fChain->SetBranchAddress("Rho1700_masserr", &Rho1700_masserr, &b_Rho1700_masserr);
   fChain->SetBranchAddress("Rho1700_masspull", &Rho1700_masspull, &b_Rho1700_masspull);
   fChain->SetBranchAddress("Rho1700_phaseerr", &Rho1700_phaseerr, &b_Rho1700_phaseerr);
   fChain->SetBranchAddress("Rho1700_phasepull", &Rho1700_phasepull, &b_Rho1700_phasepull);
   fChain->SetBranchAddress("Rho1700_widtherr", &Rho1700_widtherr, &b_Rho1700_widtherr);
   fChain->SetBranchAddress("Rho1700_widthpull", &Rho1700_widthpull, &b_Rho1700_widthpull);
   fChain->SetBranchAddress("Rho_amperr", &Rho_amperr, &b_Rho_amperr);
   fChain->SetBranchAddress("Rho_amppull", &Rho_amppull, &b_Rho_amppull);
   fChain->SetBranchAddress("Rho_masserr", &Rho_masserr, &b_Rho_masserr);
   fChain->SetBranchAddress("Rho_masspull", &Rho_masspull, &b_Rho_masspull);
   fChain->SetBranchAddress("Rho_phaseerr", &Rho_phaseerr, &b_Rho_phaseerr);
   fChain->SetBranchAddress("Rho_phasepull", &Rho_phasepull, &b_Rho_phasepull);
   fChain->SetBranchAddress("Rho_widtherr", &Rho_widtherr, &b_Rho_widtherr);
   fChain->SetBranchAddress("Rho_widthpull", &Rho_widthpull, &b_Rho_widthpull);
   fChain->SetBranchAddress("aMinuserr", &aMinuserr, &b_aMinuserr);
   fChain->SetBranchAddress("aMinuspull", &aMinuspull, &b_aMinuspull);
   fChain->SetBranchAddress("aZeroerr", &aZeroerr, &b_aZeroerr);
   fChain->SetBranchAddress("aZeropull", &aZeropull, &b_aZeropull);
   fChain->SetBranchAddress("biaserr", &biaserr, &b_biaserr);
   fChain->SetBranchAddress("biaspull", &biaspull, &b_biaspull);
   fChain->SetBranchAddress("c1merr", &c1merr, &b_c1merr);
   fChain->SetBranchAddress("c1mpull", &c1mpull, &b_c1mpull);
   fChain->SetBranchAddress("c1perr", &c1perr, &b_c1perr);
   fChain->SetBranchAddress("c1ppull", &c1ppull, &b_c1ppull);
   fChain->SetBranchAddress("c2merr", &c2merr, &b_c2merr);
   fChain->SetBranchAddress("c2mpull", &c2mpull, &b_c2mpull);
   fChain->SetBranchAddress("c2perr", &c2perr, &b_c2perr);
   fChain->SetBranchAddress("c2ppull", &c2ppull, &b_c2ppull);
   fChain->SetBranchAddress("oneerr", &oneerr, &b_oneerr);
   fChain->SetBranchAddress("onepull", &onepull, &b_onepull);
   fChain->SetBranchAddress("phiBMinuserr", &phiBMinuserr, &b_phiBMinuserr);
   fChain->SetBranchAddress("phiBMinuspull", &phiBMinuspull, &b_phiBMinuspull);
   fChain->SetBranchAddress("phiBZeroerr", &phiBZeroerr, &b_phiBZeroerr);
   fChain->SetBranchAddress("phiBZeropull", &phiBZeropull, &b_phiBZeropull);
   fChain->SetBranchAddress("phiRMinuserr", &phiRMinuserr, &b_phiRMinuserr);
   fChain->SetBranchAddress("phiRMinuspull", &phiRMinuspull, &b_phiRMinuspull);
   fChain->SetBranchAddress("phiRZeroerr", &phiRZeroerr, &b_phiRZeroerr);
   fChain->SetBranchAddress("phiRZeropull", &phiRZeropull, &b_phiRZeropull);
   fChain->SetBranchAddress("rMinuserr", &rMinuserr, &b_rMinuserr);
   fChain->SetBranchAddress("rMinuspull", &rMinuspull, &b_rMinuspull);
   fChain->SetBranchAddress("rZeroerr", &rZeroerr, &b_rZeroerr);
   fChain->SetBranchAddress("rZeropull", &rZeropull, &b_rZeropull);
   fChain->SetBranchAddress("scalefact1err", &scalefact1err, &b_scalefact1err);
   fChain->SetBranchAddress("scalefact1pull", &scalefact1pull, &b_scalefact1pull);
   fChain->SetBranchAddress("scalefact2err", &scalefact2err, &b_scalefact2err);
   fChain->SetBranchAddress("scalefact2pull", &scalefact2pull, &b_scalefact2pull);
   fChain->SetBranchAddress("scalefact3err", &scalefact3err, &b_scalefact3err);
   fChain->SetBranchAddress("scalefact3pull", &scalefact3pull, &b_scalefact3pull);
   fChain->SetBranchAddress("tauerr", &tauerr, &b_tauerr);
   fChain->SetBranchAddress("taupull", &taupull, &b_taupull);
   Notify();
}

Bool_t SumToys::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SumToys::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SumToys::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SumToys_cxx
