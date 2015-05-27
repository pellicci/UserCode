/*****************************************************************************
 * Project: BaBar detector at the SLAC PEP-II B-factory
 * Package: CharmDalitzFit
 * File: $Id: RooIsobar.cc,v 1.37 2008/06/10 17:08:25 pellicci Exp $
 * Authors:
 *   Mario Pelliccioni, pellicci@slac.stanford.edu
 *****************************************************************************/

// -- CLASS DESCRIPTION --
// RooIsobar represents a general dalitz plot class.
// it contains member functions to load all the D-decay
// dalitz dynamics. Declare the amplitude and phase of
// the resonance etc.

//Note: The DPManger class consturct the pdf for D0->K- pi+ pi0
//Here I specific the phase convention:
//m12 -> K- pi+    A(K-,pi+,pi0)
//m13 -> K- pi0 

using namespace::std;

#include <iostream>
#include <fstream>
#include <math.h>

#include "CharmDalitzFit/RooIsobar.hh"
#include "EvtGenBase/EvtPropBreitWignerRel.hh"
#include "EvtGenBase/EvtBlattWeisskopf.hh"

ClassImp(RooIsobar);
// Constructor
RooIsobar::RooIsobar(const Int_t D0flav, const Int_t isWS, EvtDalitzPlot *dalitzSpace, const string dirname)
{
  _isWS = isWS;
  _D0flav = D0flav;
  _pi = acos(-1.0);
  _dalitzSpace = dalitzSpace;
  ndiv_eff = 40;

  assert(_isWS == 0 || _isWS == 1);
  assert(_D0flav == -1 || _D0flav == 1);

  name = dirname;

  cout << Class_Name() << ": flags for the amplitude -> D0flav = " << _D0flav << " isWS = " << _isWS << endl;

  //initialize the resonance parameters in the constructor
  //initialize the resonance parameters in the constructor
  initResonance();
  getNormvalues();
  readefficiency();

  mA = _dalitzSpace->mA();
  mB = _dalitzSpace->mB();
  mC = _dalitzSpace->mC();
}

void RooIsobar::getNormvalues()
{
  //read the integral value from the cache file.
  //In this way we don't need to compute the normalization everytime during MIGRAD
  char int_name[50];
  getFileName(int_name);

  ifstream f;
  f.open(int_name);
  if (!f){
    cout << "Error opening file " << endl;
    assert(0);
  }

  Double_t re = 0., im = 0.;
  //Read in the cache file and store back to array
  for(Int_t j=1;j<=nRes;j++) {
    for(Int_t k=1;k<=nRes;k++){
      f >> re >> im;       
      normarray[j][k] = new EvtComplex(re,im);
    }
  }   
}

//Return the normalization
Double_t RooIsobar::getNormalization() const
{
  Double_t norm = 0.;

  //Read the integral values of  BW_j*conj(BW_k) 
  EvtComplex coeff_j(0.,0.), coeff_k(0.,0.);
  for(Int_t j=1;j<=nRes;j++){
    for(Int_t k=1;k<=nRes;k++){
      coeff_j = EvtComplex(_ampRes[j]->getVal()*cos(_phaseRes[j]->getVal()*_pi/180.0),_ampRes[j]->getVal()*sin(_phaseRes[j]->getVal()*_pi/180.0));
      coeff_k = EvtComplex(_ampRes[k]->getVal()*cos(_phaseRes[k]->getVal()*_pi/180.0),_ampRes[k]->getVal()*sin(_phaseRes[k]->getVal()*_pi/180.0));
      norm += real(coeff_j*conj(coeff_k)*(*normarray[j][k]));
    }
  }  
  return norm;
}

void RooIsobar::calNorm() 
{
  //Calculate the normalization value of the pdf
  cout << "RooIsobar::calNorm() Now perform GRID integration to obtain those intergrals and dump into a cache file" << endl;

  const Int_t _nBins = 700;
  cout << "We will do the GRID integral using bin size: " << _nBins << endl;  

 //re-set the normarray
  for(Int_t j=1;j<=nRes;j++){
    for(Int_t k=1;k<=nRes;k++){
      *normarray[j][k] = EvtComplex(0.,0.);
    }
  }

  //Define the area
  const Double_t xmin = _dalitzSpace->qAbsMin(EvtCyclic3::AB)+1e-6;
  const Double_t ymin = _dalitzSpace->qAbsMin(EvtCyclic3::AC)+1e-6;
  const Double_t xmax = _dalitzSpace->qAbsMax(EvtCyclic3::AB)-1e-6;
  const Double_t ymax = _dalitzSpace->qAbsMax(EvtCyclic3::AC)-1e-6;

  const Double_t dhx = (xmax - xmin)/_nBins;
  const Double_t dhy = (ymax - ymin)/_nBins;

  cout << "////////////////////////////" << endl;
  cout << "Integration limits:" << endl;
  cout << "m12 -> " << xmin << " " << xmax << endl;
  cout << "m13 -> " << ymin << " " << ymax << endl;
  cout << "////////////////////////////" << endl;

  //Now scan over the dalitz plot
  for (Int_t dx=0;dx<_nBins;dx++) {
    const Double_t m12gen = xmin + dx*dhx + dhx/2.0;
    for (Int_t dy=0;dy<_nBins;dy++) {
      const Double_t m13gen = ymin + dy*dhy + dhy/2.0;

      const Double_t m23gen = getm23(m12gen,m13gen);

      EvtDalitzPoint _dalitzPoint(mA,mB,mC,m12gen,m23gen,m13gen);
      if(!_dalitzPoint.isValid()) continue;

      for(Int_t j=1;j<=nRes;j++) {
	for(Int_t k=1;k<=nRes;k++){
	  //Get the Breit-Wigner terms
	  const EvtComplex BW_j = ResAmp(&_dalitzPoint,j);
	  const EvtComplex BW_k = ResAmp(&_dalitzPoint,k);
	  //Get the spin terms
	  const EvtComplex integral = BW_j*conj(BW_k)/*abs2(efficiency(&_dalitzPoint))*/;
	  //do the sum
	  *normarray[j][k] += integral;
	}
      }
    }  //end the for loop
  } //end the for loop     
  //********************************************************************************

  //write out the integral to a file
  char int_name[50];
  getFileName(int_name);

  ofstream ofs(int_name);
  if (ofs.fail()){
    cout << "RooDPManger::calNorm(): error opening file " << endl;
    assert(0);
  }

  for(Int_t j=1;j<=nRes;j++) {
    for(Int_t k=1;k<=nRes;k++){
      ofs << real(*normarray[j][k])*dhx*dhy << " " << imag(*normarray[j][k])*dhx*dhy << endl;
    }
  }
  //**********************************************************************************
  getNormvalues();
}

inline void RooIsobar::getFileName(char int_name[50]) const
{
  string filename;
  if(!_isWS){
    if(_D0flav==-1) filename = name + "RooIntegralD0_RS.dat";
    else filename = name + "RooIntegralD0bar_RS.dat";
  }
  else{
    if(_D0flav==-1) filename = name + "RooIntegralD0bar_RS.dat";
    else filename = name + "RooIntegralD0_RS.dat";
  }

  sprintf(int_name,filename.c_str());

  cout << int_name << endl;
}

EvtComplex RooIsobar::getamp(const EvtDalitzPoint *point) const
{
  //This return the f(m+^2,m-^2)
  //The Isobar amplitude!!!!!
  EvtComplex dalitzamplitude(0.,0.);

  for (Int_t i=1; i<=nRes; i++) {    
    //get the coefficient
    const EvtComplex coeff = EvtComplex(_ampRes[i]->getVal()*cos(_phaseRes[i]->getVal()*_pi/180.0),_ampRes[i]->getVal()*sin(_phaseRes[i]->getVal()*_pi/180.0));
    //get the matrix element (aka Breit-Wigner term)
    const EvtComplex matrixelement = ResAmp(point,i);

    //the isobar is sum all the BW term
    dalitzamplitude += coeff*matrixelement;    
  }  
  return /*efficiency(point)*/dalitzamplitude;
}

Double_t RooIsobar::getamp_tanPhase(const EvtDalitzPoint *point) const
{
return imag(getamp(point))/real(getamp(point));
}

//A brief comments here:
//The Right Sign(RS) decay here is rhoplus,
//which imply we are studying D0->K- pi+ pi0   (Not D0bar)
// Our convention for the _trackinfo (K-,pi+,pi0)
void RooIsobar::initResonance()
{
  nRes = 16;

  //Define all RooRealVar floating observables
  _ampRes[1] = new RooRealVar("Rho_amp","Rho_amp",1.0,0.,100.);
  _ampRes[2] = new RooRealVar("Rho1450_amp","Rho1450_amp",0.1,0,100);
  _ampRes[3] = new RooRealVar("Rho1700_amp","Rho1700_amp",0.1,0,100);
  _ampRes[4] = new RooRealVar("Kstminus_amp","Kstminus_amp",0.1,0,100);
  _ampRes[5] = new RooRealVar("Kstm1410_amp","Kstm1410_amp",0.1,0,100);
  _ampRes[6] = new RooRealVar("Kstm1430_amp","Kstm1430_amp",2.85,0,100);
  _ampRes[7] = new RooRealVar("Kst2m1430_amp","Kst2m1430_amp",0.1,0,100);
  _ampRes[8] = new RooRealVar("Kst1680_amp","Kst1680_amp",0.1,0,100);
  _ampRes[9] = new RooRealVar("Kstzero_amp","Kstzero_amp",0.10,0,100);
  _ampRes[10] = new RooRealVar("Kstz1410_amp","Kstz1410_amp",0.1,0,100);
  _ampRes[11] = new RooRealVar("Kstz1430_amp","Kstz1430_amp",2.85,0,100);
  _ampRes[12] = new RooRealVar("Kst2z1430_amp","Kst2z1430_amp",0.1,0,100);
  _ampRes[13] = new RooRealVar("Kstz1680_amp","Kstz1680_amp",0.1,0,100);
  _ampRes[14] = new RooRealVar("NonReson_amp","NonReson_amp",4.0,0.,100.);
  _ampRes[15] = new RooRealVar("Kstm1430_CLEO_amp","Kstm1430_CLEO_amp",2.85,0,100);
  _ampRes[16] = new RooRealVar("Kstz1430_CLEO_amp","Kstz1430_CLEO_amp",2.85,0,100);

  _phaseRes[1] = new RooRealVar("Rho_phase","Rho_phase",0.0,-360.,360);
  _phaseRes[2] = new RooRealVar("Rho1450_phase","Rho1450_phase",0.1,-360,360);
  _phaseRes[3] = new RooRealVar("Rho1700_phase","Rho1700_phase",0.1,-360,360);
  _phaseRes[4] = new RooRealVar("Kstminus_phase","Kstminus_phase",136.639,-360,360);
  _phaseRes[5] = new RooRealVar("Kstm1410_phase","Kstm1410_phase",0.1,-360,360);
  _phaseRes[6] = new RooRealVar("Kstm1430_phase","Kstm1430_phase",70.290,-360,360);
  _phaseRes[7] = new RooRealVar("Kst2m1430_phase","Kst2m1430_phase",0.1,-360,360);
  _phaseRes[8] = new RooRealVar("Kst1680_phase","Kst1680_phase",0.1,-360,360);
  _phaseRes[9] = new RooRealVar("Kstzero_phase","Kstzero_phase",32.807,-360,360);
  _phaseRes[10] = new RooRealVar("Kstz1410_phase","Kstz1410_phase",0.1,-360,360);
  _phaseRes[11] = new RooRealVar("Kstz1430_phase","Kstz1430_phase",370.290,-360,360);
  _phaseRes[12] = new RooRealVar("Kst2z1430_phase","Kst2z1430_phase",0.1,-360,360);
  _phaseRes[13] = new RooRealVar("Kstz1680_phase","Kstz1680_phase",0.1,-360,360);
  _phaseRes[14] = new RooRealVar("NonReson_phase","NonReson_phase",108.999,-360.,360.);
  _phaseRes[15] = new RooRealVar("Kstm1430_CLEO_phase","Kstm1430_CLEO_phase",70.290,-360,360);
  _phaseRes[16] = new RooRealVar("Kstz1430_CLEO_phase","Kstz1430_CLEO_phase",370.290,-360,360);

  _massRes[1] = new RooRealVar("Rho_mass","Rho_mass",0.77670);
  _massRes[2] = new RooRealVar("Rho1450_mass","Rho1450_mass",1.465);
  _massRes[3] = new RooRealVar("Rho1700_mass","rho1700_mass",1.720);
  _massRes[4] = new RooRealVar("Kstminus_mass","Kstminus_mass",0.89166);
  _massRes[5] = new RooRealVar("Kstm1410_mass","Kstm1410_mass",1.414);
  _massRes[6] = new RooRealVar("Kstm1430_mass","Kstm1430_mass",1.414);
  _massRes[7] = new RooRealVar("Kst2m1430_mass","Kst2m1430_mass",1.4256);
  _massRes[8] = new RooRealVar("Kst1680_mass","Kst1680_mass",1.717);
  _massRes[9] = new RooRealVar("Kstzero_mass","Kstzero_mass",0.896);
  _massRes[10] = new RooRealVar("Kstz1410_mass","Kstz1410_mass",1.414);
  _massRes[11] = new RooRealVar("Kstz1430_mass","Kstz1430_mass",1.414);
  _massRes[12] = new RooRealVar("Kst2z1430_mass","Kst2z1430_mass",1.4324);
  _massRes[13] = new RooRealVar("Kstz1680_mass","Kstz1680_mass",1.717);
  _massRes[14] = new RooRealVar("NonReson_mass","NonReson_mass",0.);
  _massRes[15] = new RooRealVar("Kstm1430_CLEO_mass","Kstm1430_CLEO_mass",1.414);
  _massRes[16] = new RooRealVar("Kstz1430_CLEO_mass","Kstz1430_CLEO_mass",1.414);

  _gammRes[1] = new RooRealVar("Rho_width","Rho_width",151.12/1000.0);
  _gammRes[2] = new RooRealVar("Rho1450_width","Rho1450_width",400.0/1000.0);
  _gammRes[3] = new RooRealVar("Rho1700_width","rho1700_width",250.0/1000.0);
  _gammRes[4] = new RooRealVar("Kstminus_width","Kstminus_width",50.8/1000.0);
  _gammRes[5] = new RooRealVar("Kstm1410_width","Kstm1410_width",232.0/1000.0);
  _gammRes[6] = new RooRealVar("Kstm1430_width","Kstm1430_width",290.0/1000.0);
  _gammRes[7] = new RooRealVar("Kst2m1430_width","Kst2m1430_width",98.5/1000.0);
  _gammRes[8] = new RooRealVar("Kst1680_width","Kst1680_width",322.0/1000.0);
  _gammRes[9] = new RooRealVar("Kstzero_width","Kstzero_width",50.3/1000.0);
  _gammRes[10] = new RooRealVar("Kstz1410_width","Kstz1410_width",232.0/1000.0);
  _gammRes[11] = new RooRealVar("Kstz1430_width","Kstz1430_width",290.0/1000.0);
  _gammRes[12] = new RooRealVar("Kst2z1430_width","Kst2z1430_width",109.0/1000.0);
  _gammRes[13] = new RooRealVar("Kstz1680_width","Kstz1680_width",322.0/1000.0);
  _gammRes[14] = new RooRealVar("NonReson_width","NonReson_width",0.);
  _gammRes[15] = new RooRealVar("Kstm1430_CLEO_width","Kstm1430_CLEO_width",290.0/1000.0);
  _gammRes[16] = new RooRealVar("Kstz1430_CLEO_width","Kstz1430_CLEO_width",290.0/1000.0);

  _typeRes[1] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[2] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[3] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[4] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[5] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[6] = EvtPto3PAmp::LASS;
  _typeRes[7] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[8] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[9] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[10] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[11] = EvtPto3PAmp::LASS;
  _typeRes[12] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[13] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[14] = EvtPto3PAmp::NONRES;
  _typeRes[15] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[16] = EvtPto3PAmp::RBW_CLEO;

  _spinRes[1] = EvtSpinType::VECTOR;
  _spinRes[2] = EvtSpinType::VECTOR;
  _spinRes[3] = EvtSpinType::VECTOR;
  _spinRes[4] = EvtSpinType::VECTOR;
  _spinRes[5] = EvtSpinType::VECTOR;
  _spinRes[6] = EvtSpinType::SCALAR;
  _spinRes[7] = EvtSpinType::TENSOR;
  _spinRes[8] = EvtSpinType::VECTOR;
  _spinRes[9] = EvtSpinType::VECTOR;
  _spinRes[10] = EvtSpinType::VECTOR;
  _spinRes[11] = EvtSpinType::SCALAR;
  _spinRes[12] = EvtSpinType::TENSOR;
  _spinRes[13] = EvtSpinType::VECTOR;
  _spinRes[14] = EvtSpinType::SCALAR;
  _spinRes[15] = EvtSpinType::SCALAR;
  _spinRes[16] = EvtSpinType::SCALAR;

  _trackinfo[1] = EvtCyclic3::BC;
  _trackinfo[2] = EvtCyclic3::BC;
  _trackinfo[3] = EvtCyclic3::BC;
  _trackinfo[4] = EvtCyclic3::AC;
  _trackinfo[5] = EvtCyclic3::AC;
  _trackinfo[6] = EvtCyclic3::AC;
  _trackinfo[7] = EvtCyclic3::AC;
  _trackinfo[8] = EvtCyclic3::AC;
  _trackinfo[9] = EvtCyclic3::AB;
  _trackinfo[10] = EvtCyclic3::AB;
  _trackinfo[11] = EvtCyclic3::AB;
  _trackinfo[12] = EvtCyclic3::AB;
  _trackinfo[13] = EvtCyclic3::AB;
  _trackinfo[14] = EvtCyclic3::BC;
  _trackinfo[15] = EvtCyclic3::AC;
  _trackinfo[16] = EvtCyclic3::AB;

  _aLASS[1] = new RooRealVar("aZero","aZero",2.,-10,10.);
  _aLASS[2] = new RooRealVar("aMinus","aMinus",2.,-10,10.);

  _rLASS[1] = new RooRealVar("rZero","rZero",3.,-10,10.);
  _rLASS[2] = new RooRealVar("rMinus","rMinus",3.,-10,10.);

  _BLASS[1] = new RooRealVar("BZero","BZero",-0.96,-10,10.);
  _BLASS[2] = new RooRealVar("BMinus","BMinus",1.,-10,10.);

  _RLASS[1] = new RooRealVar("RZero","RZero",1.,-10,10.);
  _RLASS[2] = new RooRealVar("RMinus","RMinus",1.,-10,10.);

  _phiBLASS[1] = new RooRealVar("phiBZero","phiBZero",-0.96,-10,10.);
  _phiBLASS[2] = new RooRealVar("phiBMinus","phiBMinus",1.,-10,10.);

  _phiRLASS[1] = new RooRealVar("phiRZero","phiRZero",1.,-10,10.);
  _phiRLASS[2] = new RooRealVar("phiRMinus","phiRMinus",1.,-10,10.);

  // setup Daugther type
  _nameRes[1] = TString("Rho");
  _nameRes[2] = TString("Rho1400");
  _nameRes[3] = TString("Rho1700");
  _nameRes[4] = TString("Kstarminus");
  _nameRes[5] = TString("Kstm1410");
  _nameRes[6] = TString("Kstm1430");
  _nameRes[7] = TString("Kst2m1430");
  _nameRes[8] = TString("Kstar1680");
  _nameRes[9] = TString("Kstarzero");
  _nameRes[10] = TString("Kstz1410");
  _nameRes[11] = TString("Kstz1430");
  _nameRes[12] = TString("Kst2z1430");
  _nameRes[13] = TString("Kstz1680");
  _nameRes[14] = TString("Non resonant");
  _nameRes[15] = TString("Kstm1430_CLEO");
  _nameRes[16] = TString("Kstm1430_CLEO");

  //put all RooRealVar into the observable list
  //We only float the amplitude and phase
  //For the time-dependent fit, this should be modified
  //Now readin the initial values from isobar_XS.txt
  RooArgSet parameters;
  for (Int_t dummy=1;dummy<=nRes;dummy++)
    {
      //cout << "RooIsobar::Now we are reading resonance information   " << dummy << endl;    
      //adding the rho width too to let roofit float it
      parameters.add(*_gammRes[dummy]);
      parameters.add(*_massRes[dummy]);
      if(dummy == 1 || dummy == 2){
	parameters.add(*_aLASS[dummy]);
	parameters.add(*_rLASS[dummy]);
	parameters.add(*_BLASS[dummy]);
	parameters.add(*_RLASS[dummy]);
	parameters.add(*_phiBLASS[dummy]);
	parameters.add(*_phiRLASS[dummy]);
      }
      parameters.add(*_ampRes[dummy]);
      parameters.add(*_phaseRes[dummy]);
    }

  string configname;

  if(!_isWS) configname = name + "isobar_RS.txt";
  else configname = name + "isobar_WS.txt";

  parameters.readFromFile(configname.c_str());

  //define the list of observables(which is our floating parameters)
  _obs_list = new RooArgList();
  for (Int_t dummy=1;dummy<=nRes;dummy++)
    {
      //cout << "Now adding " << _nameRes[dummy] << endl;
      _obs_list->add(*_phaseRes[dummy]); 
      _obs_list->add(*_ampRes[dummy]);
      if(dummy==1 || dummy==3 || dummy == 4 || dummy == 9 || dummy == 6 || dummy == 11) _obs_list->add(*_gammRes[dummy]);
      if(dummy==1 || dummy==3 || dummy == 4 || dummy == 9 || dummy == 6 || dummy == 11) _obs_list->add(*_massRes[dummy]);
      if(dummy == 1 || dummy == 2){
	_obs_list->add(*_aLASS[dummy]);
	_obs_list->add(*_rLASS[dummy]);
	_obs_list->add(*_RLASS[dummy]);
	_obs_list->add(*_BLASS[dummy]);
	_obs_list->add(*_phiRLASS[dummy]);
	_obs_list->add(*_phiBLASS[dummy]);
      }
    }
  //end the initalization
}

//This returns our Form Factor
//In most of the case, we return relativistic Breit-Wigner
EvtComplex RooIsobar::ResAmp(const EvtDalitzPoint *_dalitzPoint, const Int_t i) const
{
  if(!_dalitzPoint->isValid()) assert (0); // no physics reason to fail

  //retrieve the informations about the resonance
  const Double_t res_Mass = _massRes[i]->getVal();
  const EvtSpinType::spintype res_Spin  = _spinRes[i];
  const EvtCyclic3::Pair res_Pair  = _trackinfo[i];

  EvtCyclic3::Pair hel_Pair  = EvtCyclic3::next( res_Pair );
  const EvtPto3PAmp::NumType res_Type = _typeRes[i];
  if(res_Pair==EvtCyclic3::AC) hel_Pair  = EvtCyclic3::prev( res_Pair );

  if (res_Type==EvtPto3PAmp::NONRES) return  EvtComplex(1.,0.);

  else if(res_Type==EvtPto3PAmp::LASS)  return LASS(_dalitzPoint,i);

  else if(res_Type == EvtPto3PAmp::RBW_ZEMACH){
    const Double_t res_gamma_running = runningWidth(_dalitzPoint->q(res_Pair),i);
    const EvtPropBreitWignerRel evtProp(res_Mass,res_gamma_running);
    EvtPto3PAmp amplitude(*_dalitzSpace,hel_Pair,res_Pair,res_Spin,evtProp,EvtPto3PAmp::RBW_ZEMACH);

    //set the Blatt factor
    amplitude.set_fd(1.5);
    amplitude.set_fb(5.);

    return amplitude.evaluate(*_dalitzPoint);
  }
  else if(res_Type == EvtPto3PAmp::RBW_CLEO){

    const Double_t res_gamma_running = runningWidth(_dalitzPoint->q(res_Pair),i);
    const EvtPropBreitWignerRel evtProp(res_Mass,res_gamma_running);
    EvtPto3PAmp amplitude(*_dalitzSpace,hel_Pair,res_Pair,res_Spin,evtProp,EvtPto3PAmp::RBW_CLEO);

    //set the Blatt factor
    amplitude.set_fd(1.5);
    amplitude.set_fb(5.0);

    return amplitude.evaluate(*_dalitzPoint);
  }
  else assert(0);
  return 0.;
}

EvtComplex RooIsobar::LASS(const EvtDalitzPoint *_dalitzPoint, const Int_t i) const
{
  const Double_t _mass = _massRes[i]->getVal();
  const Double_t _width = _gammRes[i]->getVal();
  const EvtCyclic3::Pair res_Pair  = _trackinfo[i];

  Int_t Kidx(0);
  Double_t _m1 = 0., _m2 = 0.;
  if(res_Pair==EvtCyclic3::AB){
    _m1 = mA;
    _m2 = mB;
    Kidx = 1;
  }
  if(res_Pair==EvtCyclic3::AC){
    _m1 = mA;
    _m2 = mC;
    Kidx = 2;
  }

  const Double_t _a = _aLASS[Kidx]->getVal();   //need to be float
  const Double_t _r = _rLASS[Kidx]->getVal();   //need to be float
  const Double_t _B = _BLASS[Kidx]->getVal();   //need to be float
  const Double_t _R = _RLASS[Kidx]->getVal();   //need to be float
  const Double_t _phiB = _phiBLASS[Kidx]->getVal();   //need to be float
  const Double_t _phiR = _phiRLASS[Kidx]->getVal();   //need to be float

  const Double_t s = _dalitzPoint->q(res_Pair);

  if (s < 4.) {
    const Double_t m0Square = pow(_mass,2.);
    const Double_t m        = sqrt(_dalitzPoint->q(res_Pair));
    const Double_t q0     = pionCMmom(m0Square, _m1, _m2);
    const Double_t q      = pionCMmom(s, _m1, _m2);
    const Double_t GammaM = runningWidth(s,i);

    if(q == 0.) {
      //this should not happen
      cout << "Hold on.....the q is zero ! " << endl;
      return EvtComplex(m*_a + m0Square*_width/q0/(m0Square - s), 0.);
    }
 
    const Double_t cot_deltaB = 1./(_a*q) + 0.5*_r*q;
    const Double_t _deltaB = atan( 1./cot_deltaB);
    const Double_t totalB = (_deltaB + _phiB*_pi/180.) ;
    const Double_t deltaR = atan((_mass*GammaM/(m0Square - s)));
    const Double_t totalR = deltaR + _phiR*_pi/180.;
 
    EvtComplex bkgB = EvtComplex(_B*sin(totalB),0.)*EvtComplex(cos(totalB),sin(totalB));
    EvtComplex resT = EvtComplex(_R*sin(deltaR),0.)*EvtComplex(cos(totalR),sin(totalR))*EvtComplex(cos(2*totalB),sin(2*totalB));
    //EvtComplex bkgB = EvtComplex(_B*sin(totalB),0.);
    //EvtComplex resT = EvtComplex(_R*sin(deltaR),0.)*EvtComplex(cos(totalR),sin(totalR))*EvtComplex(cos(totalB),sin(totalB));
                                                                                                                                                             
    return bkgB + resT;
  }
  else return EvtComplex(0.,0.);
}

//this is only for the rho parametrization
Double_t RooIsobar::runningWidth(const Double_t s, const Int_t i) const
{
  const Double_t width = _gammRes[i]->getVal();
  const Double_t mass2  = pow(_massRes[i]->getVal(),2);
  const EvtCyclic3::Pair res_Pair  = _trackinfo[i];
  const EvtSpinType::spintype res_Spin  = _spinRes[i];
  Double_t _m1 = 0., _m2 = 0.;

  if(res_Pair==EvtCyclic3::AB){
    _m1 = mA;
    _m2 = mB;
  }
  if(res_Pair==EvtCyclic3::AC){
    _m1 = mA;
    _m2 = mC;
  }
  if(res_Pair==EvtCyclic3::BC){
    _m1 = mB;
    _m2 = mC;
  }
  const Double_t k_s  = pionCMmom(s,_m1,_m2);
  const Double_t k_m0 = pionCMmom(mass2,_m1,_m2);

  const EvtBlattWeisskopf fr(1,1.5,mass2);
  //return width * sqrt(mass2/s) * pow( k_s/k_m0, 3 ) * pow( (fr)(s), 2);
  return width * sqrt(mass2/s) * pow( k_s/k_m0, EvtSpinType::getSpinStates(res_Spin)) * pow( (fr)(s), 2);
}

EvtComplex RooIsobar::efficiency(const EvtDalitzPoint *point) const
{
  //need cos12 and mAB to determine efficiency
  const Double_t mAB = point->q(EvtCyclic3::AB);
  const Double_t mAC = point->q(EvtCyclic3::AC);
  const Double_t cos12 = _dalitzSpace->cosTh(EvtCyclic3::AC,mAC,EvtCyclic3::AB,mAB);
  //const Double_t cos12 = _dalitzSpace->cosTh(EvtCyclic3::AB,mAB,EvtCyclic3::AC,mAC);

  const Double_t m12min = _dalitzSpace->qAbsMin(EvtCyclic3::AB);
  const Double_t m12max = _dalitzSpace->qAbsMax(EvtCyclic3::AB);
  const Double_t dm12 = (m12max-m12min)/ndiv_eff;

  for(Int_t i=0;i<ndiv_eff;i++){
    if(floor((mAB-m12min)/dm12) == i){
      const Double_t n0 = _n0[i]->getVal();
      const Double_t n1 = _n1[i]->getVal();
      const Double_t c1 = _c1[i]->getVal();
      const Double_t c2 = _c2[i]->getVal();
      const Double_t c3 = _c3[i]->getVal();
      const Double_t c4 = _c4[i]->getVal();
      const Double_t c5 = _c5[i]->getVal();
      const Double_t eff = 0.5*(n1/n0)*(1. + c1*cos12 + c2*(3.*pow(cos12,2.)-1.) + c3*(5.*pow(cos12,3.)-3.*cos12) + c4*(35.*pow(cos12,4.)-30.*pow(cos12,2.)+3.) + c5*(63.*pow(cos12,5.)-70.*pow(cos12,3.)+15.*cos12));
      return EvtComplex(sqrt(eff),0.);
    }
  }
  assert(0);
  return EvtComplex(0.,0.);
}

void RooIsobar::readefficiency()
{
  RooRealVar n0("n0","n0",1.);
  RooRealVar n1("n1","n1",1.);
  RooRealVar c1("c1","c1",1.);
  RooRealVar c2("c2","c2",1.);
  RooRealVar c3("c3","c3",1.);
  RooRealVar c4("c4","c4",1.);
  RooRealVar c5("c5","c5",1.);
  RooArgSet varlist;
  varlist.add(n0);
  varlist.add(n1);
  varlist.add(c1);
  varlist.add(c2);
  varlist.add(c3);
  varlist.add(c4);
  varlist.add(c5);

  for(Int_t i=0;i<ndiv_eff;i++){

    char map[100];
    if(!_isWS){
      if(_D0flav==-1) sprintf(map,"effmap_%d.txt",i);
      else sprintf(map,"effmap_bar_%d.txt",i);
    }
    else{
      if(_D0flav==-1) sprintf(map,"effmap_bar_%d.txt",i);
      else sprintf(map,"effmap_%d.txt",i);
    }
    string map2(map);

    string mapfile = name + map2;
    cout << "reading efficiency map file " << mapfile << endl;
    varlist.readFromFile(mapfile.c_str());
    _n0.push_back(new RooRealVar("_n0","_n0",n0.getVal()));
    _n1.push_back(new RooRealVar("_n0","_n0",n1.getVal()));
    _c1.push_back(new RooRealVar("_n0","_n0",c1.getVal()));
    _c2.push_back(new RooRealVar("_n0","_n0",c2.getVal()));
    _c3.push_back(new RooRealVar("_n0","_n0",c3.getVal()));
    _c4.push_back(new RooRealVar("_n0","_n0",c4.getVal()));
    _c5.push_back(new RooRealVar("_n0","_n0",c5.getVal()));
  }
}

void RooIsobar::helicityangle(RooDataSet *data) const
{
  RooRealVar *cos12 = new RooRealVar("cos12","cos12",-1,1);
  RooRealVar *cos13 = new RooRealVar("cos13","cos13",-1,1);
  RooRealVar *cos23 = new RooRealVar("cos23","cos23",-1,1);
  RooDataSet *data2 = new RooDataSet("data2","data2",RooArgSet(*cos12,*cos13,*cos23));

  for(Int_t i=0;i<data->numEntries();i++ ){

    const RooArgSet* row = data->get(i);
    RooRealVar* mass12 =(RooRealVar*) row->find("m2Kpi_d0mass");   //recall! mass12 is the peaking one!
    RooRealVar* mass13 =(RooRealVar*) row->find("m2Kpi0_d0mass");

    const Double_t m13=mass13->getVal();   //good, m13 is peaking
    const Double_t m12=mass12->getVal();
    Double_t cFromM(0.);

    for(Int_t n=1;n<=3;n++) {

      switch (n) {  //n is the _trackinfo
      case 1: //pi+ pi- is resonace pair
        cFromM = _dalitzSpace->cosTh(EvtCyclic3::AC,m13,EvtCyclic3::AB,m12);
        cos23->setVal(cFromM);
        break;

      case 2: //Ks pi- is the resonance pair (Cabibbo allow decay)
        cFromM = _dalitzSpace->cosTh(EvtCyclic3::AB,m12,EvtCyclic3::AC,m13);
        cos13->setVal(cFromM);
        break;

      case 3: //ks pi+ is the resonace pair (Cabibbo suppress decay)
        cFromM = _dalitzSpace->cosTh(EvtCyclic3::AC,m13,EvtCyclic3::AB,m12);
        cos12->setVal(cFromM);
        break;
      }
    }  //end the small for loop
    data2->add(RooArgList(*cos12,*cos13,*cos23));
  } //end the for loop

  cout << "Finished ! no problem " << endl;
  data->merge(data2);
}

Double_t RooIsobar::pionCMmom(const Double_t s, const Double_t m1, const Double_t m2) const
{
  const Double_t mprime = pow(m1 + m2,2);
  const Double_t msecond = pow(m1 - m2,2);

  const Double_t rad1 = 1.0 - mprime/s;
  const Double_t rad2 = 1.0 - msecond/s;

  const Double_t betakin1 = (rad1 > 0.) ? sqrt( rad1 ) : 1.;
  const Double_t betakin2 = (rad2 > 0.) ? sqrt( rad2 ) : 1.;

  return 0.5*sqrt(s)*betakin1*betakin2;
}
