/****************************************************************************
 * Project: Kpipipdf                                                         *
 * Package: CharmDalitzFit                                                   *
 *    File: $Id: RooTimepdf.cc,v 1.27 2008/06/10 17:08:26 pellicci Exp $      * 
 * Authors:                                                                  *
 *   MP, Mario Pelliccioni, Univerista di Torino, pellicci@slac.stanford.edu *
 *   GC, Gianluca Cavoto, Universita di Roma, cavoto@slac.stanford.edu       *
 *****************************************************************************/

#include <iostream>
#include <math.h>
#include <iomanip>

#include "CharmDalitzFit/RooTimepdf.hh"
#include "EvtGenBase/EvtDalitzPoint.hh"

#include "RooFitCore/RooRandom.hh"
#include "RooFitCore/RooRealConstant.hh"

using std::cout;
using std::endl;
using std::flush;
using std::setw;

ClassImp(RooTimepdf);

// constructors

//first constructor: just temporal part, no need of Dalitz
RooTimepdf::RooTimepdf(const char *name, const char *title, RooRealVar& d0Lifetime, const RooResolutionModel& model, RooAbsReal& tau):
  RooAbsAnaConvPdf(name,title,model,d0Lifetime),
  _d0Lifetime("d0Lifetime","The D0 lifetime",this,d0Lifetime),
  _tau("tau","tau",this,tau),
  _m12("m12","m12",this,(RooRealVar&)RooRealConstant::value(0)),
  _m13("m13","m13",this,(RooRealVar&)RooRealConstant::value(0)),
  _c1("c1","c1",this,(RooRealVar&)RooRealConstant::value(0)),
  _c2("c2","c2",this,(RooRealVar&)RooRealConstant::value(0))
{
  _pi = acos(-1.);
  _pdfmax = -1.;
  _noDalitz = kTRUE;
  _isWS = kFALSE;

  //define a proxy list to float the variables in the fit
  _prxyList   = new RooListProxy("prxyList","prxyList",this);

  //declare the temporal dependence for the convolution
  _basisExp = declareBasis("exp(-@0/@1)",RooArgList(tau));
}

//one constructor is for the RS fit (so no mixing). Note: this is good also for WS mistag parametrization!
RooTimepdf::RooTimepdf(const char *name, const char *title, RooRealVar& d0Lifetime, RooAbsReal& m12, RooAbsReal& m13, const RooResolutionModel& model, EvtDalitzPlot* dalitzSpace, RooAbsReal& tau, const string dirname):
  RooAbsAnaConvPdf(name,title,model,d0Lifetime),
  _d0Lifetime("d0Lifetime","The D0 lifetime",this,d0Lifetime),
  _tau("tau","tau",this,tau),
  _m12("m12","m12",this,m12),
  _m13("m13","m13",this,m13),
  _c1("c1","c1",this,(RooRealVar&)RooRealConstant::value(0)),
  _c2("c2","c2",this,(RooRealVar&)RooRealConstant::value(0))
{
  _dalitzSpace = dalitzSpace;
  _pi = acos(-1.);
  _pdfmax = -1.;
  _noDalitz = kFALSE;
  _isWS = kFALSE;

  basepdf = new RooIsobar(-1,0,_dalitzSpace,dirname);
  nResbase = basepdf->getnRes();

  //define a proxy list to float the variables in the fit
  _prxyList   = new RooListProxy("prxyList","prxyList",this);

  //retrieve proxies from the Dalitz manager
  obsList = new RooArgList();
  obsList = basepdf->getObsList();

  //add to the list observables from this class
  TIterator*  tIter   = obsList->createIterator();
  RooAbsArg*  coef;
  if(!_noDalitz){
    while(coef = (RooAbsArg*)tIter->Next()) {
      if (!dynamic_cast<RooAbsReal*>(coef)) assert(0);
      _prxyList->add(*coef);
    }
  }
  delete tIter;

  getNormarray();

  //declare the temporal dependence for the convolution
  _basisExp = declareBasis("exp(-@0/@1)",RooArgList(tau));
}

RooTimepdf::RooTimepdf(const char *name, const char *title, RooRealVar& d0Lifetime, RooAbsReal& m12, RooAbsReal& m13,
                       const RooResolutionModel& model, EvtDalitzPlot* dalitzSpace, RooAbsReal& tau, RooAbsReal& c1, RooAbsReal& c2, Int_t D0flav, const string dirname):
  RooAbsAnaConvPdf(name,title,model,d0Lifetime),
  _d0Lifetime("d0Lifetime","The D0 lifetime",this,d0Lifetime),
  _tau("tau","tau",this,tau),
  _m12("m12","m12",this,m12),
  _m13("m13","m13",this,m13),
  _c1("c1","c1",this,c1),
  _c2("c2","c1",this,c2)
{
  _dalitzSpace = dalitzSpace;
  _pi = acos(-1.);
  _pdfmax = -1.;
  _isWS = kTRUE;
  _noDalitz = kFALSE;
  _D0flav = -1*D0flav;

  cout << Class_Name() << ": D0flav is " << _D0flav << endl;

  basepdf = new RooIsobar(_D0flav,1,_dalitzSpace,dirname);
  quadpdf = new RooIsobar(-1*_D0flav,0,_dalitzSpace,dirname);       // 0 means RS
  nResbase = basepdf->getnRes();
  nResquad = quadpdf->getnRes();

  //uncomment the next two lines if you want to recalculate normalization
  //basepdf->calNorm();
  //quadpdf->calNorm();

  I3value = quadpdf->getNormalization();
  assert(I3value != 0.);

  //define a proxy list to float the variables in the fit
  _prxyList   = new RooListProxy("prxyList","prxyList",this);

  //retrieve proxies from the Dalitz manager
  obsList = new RooArgList();
  obsList = basepdf->getObsList();

  //add to the list observables from this class

  TIterator*  tIter   = obsList->createIterator();
  RooAbsArg*  coef;
  while(coef = (RooAbsArg*)tIter->Next()) {
    if (!dynamic_cast<RooAbsReal*>(coef)) assert(0);
    _prxyList->add(*coef);
  }

  delete tIter;
  getNormarray();

  //declare the temporal dependence for the convolution
  _basisExp = declareBasis("exp(-@0/@1)",RooArgList(tau));
  _linearExp = declareBasis("(@0/@1)*exp(-@0/@1)",RooArgList(tau));
  _quadExp = declareBasis("(@0/@1)*(@0/@1)*exp(-@0/@1)",RooArgList(tau));
}

//Copy Constructor
RooTimepdf::RooTimepdf(const RooTimepdf& other, const char* name) :
  RooAbsAnaConvPdf(other,name),
  _d0Lifetime("d0Lifetime",this,other._d0Lifetime),
  _m12("m12",this,other._m12),
  _m13("m13",this,other._m13),
  _basisExp(other._basisExp),
  _linearExp(other._linearExp),
  _quadExp(other._quadExp)
{
  _pdfmax = other._pdfmax;
  _pi = other._pi;
  _isWS = other._isWS;
  _c1 = other._c1;
  _c2 = other._c2;
  _tau = other._tau;
  _prxyList = other._prxyList;
  _noDalitz = other._noDalitz;
  _D0flav = other._D0flav;
  if(!_noDalitz && _isWS){
    _dalitzSpace = other._dalitzSpace;
    basepdf = other.basepdf;
    quadpdf = other.quadpdf;
    I3value = other.I3value;
    nResbase = other.nResbase;
    nResquad = other.nResquad;
    getNormarray();
  }
  else if(!_noDalitz && !_isWS){
    _dalitzSpace = other._dalitzSpace;
    basepdf = other.basepdf;
    nResbase = other.nResbase;
    getNormarray();
  }
}

//calculate the coefficients for the constant, linear and quadratic terms
//of the temporal dependence
Double_t RooTimepdf::coefficient(Int_t basisIndex) const
{
  if(_noDalitz) return 1.;

  const Double_t _m23 = getm23();
  const EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),_m12,_m23,_m13);
  if(!_dalitzPoint.isValid()) return 0.;

  if(!_isWS) return abs2(basepdf->getamp(&_dalitzPoint));

  if(basisIndex == _basisExp) return abs2(basepdf->getamp(&_dalitzPoint))/basepdf->getNormalization();
 
  if(basisIndex == _linearExp){
    const EvtComplex WSampNorm = basepdf->getamp(&_dalitzPoint)/EvtComplex(sqrt(basepdf->getNormalization()),0.);
    const EvtComplex RSampNorm = quadpdf->getamp(&_dalitzPoint)/EvtComplex(sqrt(I3value),0.);
    const EvtComplex prodAmpl = conj(WSampNorm)*RSampNorm;
    return _c1*real(prodAmpl) - _c2*imag(prodAmpl);
  }
  else if(basisIndex == _quadExp){
    return ((pow(_c1,2.) + pow(_c2,2.))/4.)*abs2(quadpdf->getamp(&_dalitzPoint))/I3value;
  }
  else assert(0);

  return 0.;
}

Int_t RooTimepdf::getCoefAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const
{
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << GetName() << ": Requested integration over these variables: " << endl;
  allVars.Print("V");
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  if(!_noDalitz) if (matchArgs(allVars,analVars,_m12,_m13)) return 1;
  return 0 ;
}

Double_t RooTimepdf::coefAnalyticalIntegral(Int_t basisIndex, Int_t code, const char* /*rangeName*/) const 
{
  assert(!_noDalitz);

  switch(code) {
    // No integration
  case 0: return coefficient(basisIndex) ;

    // Integration over 'm12' and 'm13' 
  case 1:
    if(basisIndex == _basisExp) return 1.;
    if(_isWS) {
      if(basisIndex == _linearExp) return getI2();
      else if(basisIndex == _quadExp) return (pow(_c1,2.) + pow(_c2,2.))/4.;
      else assert(0);
    }
  }
  return 0.;
}

void RooTimepdf::getNormarray()
{
  //read the integral value from the cache file.
  char int_name[50];
  basepdf->getFileName(int_name);

  ifstream f;
  f.open(int_name);
  if (!f){
    cout << "Error opening file " << endl;
    assert(0);
  }
  
  Double_t re = 0.,im = 0.;
  //Read in the cache file and store back to array
  for(Int_t j=1;j<=nResbase;j++) {
    for(Int_t k=1;k<=nResbase;k++){
      f >> re >> im; 
      normarray[j][k] = EvtComplex(re,im);
    }
  }
}

//integral of the interference coefficient
Double_t RooTimepdf::getI2() const
{
  EvtComplex I_2prime(0.,0.);
  
  for(Int_t dummyRS=1;dummyRS<=nResquad;dummyRS++){
    const EvtComplex coeff_RS(quadpdf->_ampRes[dummyRS]->getVal()*cos(quadpdf->_phaseRes[dummyRS]->getVal()*_pi/180.0),quadpdf->_ampRes[dummyRS]->getVal()*sin(quadpdf->_phaseRes[dummyRS]->getVal()*_pi/180.0));

    for(Int_t dummyWS=1;dummyWS<=nResbase;dummyWS++){
      const EvtComplex coeff_WS(basepdf->_ampRes[dummyWS]->getVal()*cos(basepdf->_phaseRes[dummyWS]->getVal()*_pi/180.0),basepdf->_ampRes[dummyWS]->getVal()*sin(basepdf->_phaseRes[dummyWS]->getVal()*_pi/180.0));

      I_2prime += coeff_RS*conj(coeff_WS)*normarray[dummyRS][dummyWS];
    }
  }
  const Double_t normy = sqrt(I3value*basepdf->getNormalization());
  return (_c1*real(I_2prime) - _c2*imag(I_2prime))/normy;
}

///////////////////////////////////////////////////////////////////////
//
//                 Event generation
//
//////////////////////////////////////////////////////////////////////

Int_t RooTimepdf::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK) const {
  // Advertise own event generator.
  cout << "==============================================================" << endl;
  cout << GetName() << ": Requested generation of these variables:" << endl;
  directVars.Print("V");
  cout << "==============================================================" << endl << endl;

  if (matchArgs(directVars,generateVars,_m12,_m13,_d0Lifetime)) return 2;
  else if (matchArgs(directVars,generateVars,_d0Lifetime)) return 1;
  cout << "Not matched" << endl;
  return 0 ;
}

void RooTimepdf::initGenerator(Int_t code)
{
  if(code==2){

  cout << "Dalitz Limits used for generation:" << endl;
  cout << "m12 -> " << _dalitzSpace->qAbsMin(EvtCyclic3::AB)+1e-6 << " " << _dalitzSpace->qAbsMax(EvtCyclic3::AB)+1e-6 << endl;
  cout << "m13 -> " << _dalitzSpace->qAbsMin(EvtCyclic3::AC)+1e-6 << " " << _dalitzSpace->qAbsMax(EvtCyclic3::AC)+1e-6 << endl;

  if(_pdfmax > 0.) return;

  // sample Dalitz space to find the highest pdf
  _pdfmax=-1.;
  Int_t nsample = 0;

  cout << GetName() << ": Searching for PDF maximum" << flush;
  while (nsample++ < 20000){
    const Double_t pdftmp = sampleEvent();
    if (pdftmp>_pdfmax) _pdfmax=pdftmp;
  }

  _pdfmax*=1.15; // increase for safety 
  cout << " = " << _pdfmax << endl;
  }
}

Double_t RooTimepdf::sampleEvent()
{
  // Sample time-integrated m12,m13 distribution
  while (1){
    _m12 = _m12.min() + (_m12.max() - _m12.min())*RooRandom::uniform();
    _m13 = _m13.min() + (_m13.max() - _m13.min())*RooRandom::uniform();

    const Double_t _m23 = getm23();
    const EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),_m12,_m23,_m13);
    if(!_dalitzPoint.isValid()) continue;
    return coefficient(_basisExp) + coefficient(_linearExp) + 2*coefficient(_quadExp);
  }
  return 0.;
}

void RooTimepdf::generateEvent(Int_t code) 
{
  // Generate event
  if(code==1){
    while(1){
      _totGen++;
      Double_t rand = RooRandom::uniform();
      Double_t dtval = -_tau*log(rand);
      if (dtval<0. || dtval> 4.) continue;
      _d0Lifetime = dtval;
      return;
    }
  }

  assert(code==2);

  while (1){
    const Double_t acceptProb = sampleEvent();
    if (acceptProb > _pdfmax){
      cout << Class_Name() << ": probability = " << acceptProb << " > max. probability(DP) = " << _pdfmax << endl;
      assert(0);
    }
    if (_pdfmax*RooRandom::uniform() > acceptProb) continue;
    assert (coefficient(_basisExp)>0.);
    break;
  }

  _totGen++;
  if(_isWS) genLifetime();
  else {
    while(1){
      Double_t rand = RooRandom::uniform();
      Double_t dtval = -_tau*log(rand);
      if (dtval<0. || dtval> 4.) continue;
      _d0Lifetime = dtval;
      return;
    }
  }
  return;
}

void RooTimepdf::genLifetime() 
{
  while(1){
    const Double_t a1 = coefficient(_linearExp)/coefficient(_basisExp);
    const Double_t a2 = coefficient(_quadExp)/coefficient(_basisExp);

    Double_t P_MaxFunc = 0.;

    if(a2 == 0. && a1 != 0.) P_MaxFunc = (a1 - 1.)/(a1*_tau);

    if(a2 != 0.){
    const Double_t rad = a1*a1-4*a2+4*a2*a2;
    if ((rad) >= 0.) P_MaxFunc = (2*a2-a1+sqrt(rad))/(2*a2);
    }

    if(P_MaxFunc < 0.) P_MaxFunc = 0.;
    Double_t MaxFunc = exp(-P_MaxFunc)* (1. + a1*P_MaxFunc + a2*P_MaxFunc*P_MaxFunc);
    if(MaxFunc < 1.) MaxFunc = 1.; 

    const Double_t rand_f = RooRandom::uniform()*MaxFunc;
    const Double_t rand_t = RooRandom::uniform()*4.0;
    const Double_t t1 = rand_t/_tau;
    const Double_t target = (1.0 + a1*t1 + a2*t1*t1)*exp(-t1);
    if(rand_f > target) continue;

    if(fmod((Double_t)_totGen,100.) == 0) cout << GetName() << ": so far generated " << _totGen << " events" << endl;

    _d0Lifetime = rand_t;

    return;
  }
}
