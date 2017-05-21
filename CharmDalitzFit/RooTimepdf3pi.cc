/****************************************************************************
 * Project: Kpipipdf                                                         *
 * Package: CharmDalitzFit                                                   *
 *    File: $Id: RooTimepdf3pi.cc,v 1.3 2008/06/11 21:03:50 pellicci Exp $      * 
 * Authors:                                                                  *
 *   MP, Mario Pelliccioni, Univerista di Torino, pellicci@slac.stanford.edu *
 *   GC, Gianluca Cavoto, Universita di Roma, cavoto@slac.stanford.edu       *
 *                                                                           *
 * Copyright (c) 2000-2002, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 *****************************************************************************/

#include <iostream>
#include <math.h>
#include <iomanip>

#include "CharmDalitzFit/RooTimepdf3pi.hh"

#include "RooFitCore/RooRandom.hh"

using std::cout;
using std::endl;
using std::flush;

ClassImp(RooTimepdf3pi);

double _pdfmax(-1.);

const double _pi = acos(-1.);

// constructor
//Define our constructor, we need m12^2 and m13^2, as our dalitz variable
RooTimepdf3pi::RooTimepdf3pi(const char *name, const char *title, RooRealVar& d0Lifetime, RooAbsReal& m13, RooAbsReal& m23, const RooResolutionModel& model,
			     EvtDalitzPlot* dalitzSpace, RooAbsReal& tau, RooAbsReal& qp, RooAbsReal& phi, RooAbsReal& c1, RooAbsReal& c2, RooAbsReal& c3,
			     const Int_t D0flav, const string dirname):
  RooAbsAnaConvPdf(name,title,model,d0Lifetime),
  _d0Lifetime("d0Lifetime","The D0 lifetime",this,d0Lifetime),
  _m13("m13","m13",this,m13),
  _m23("m23","m23",this,m23),
  _tau("tau","tau",this,tau),
  _qp("qp","qp",this,qp),
  _phi("phi","phi",this,phi),
  _c1("c1","c1",this,c1),
  _c2("c2","c2",this,c2),
  _c3("c3","c3",this,c3)
{
  _dalitzSpace = dalitzSpace;
  _D0flav = D0flav;

  Apdf = new RooIsobar3Pi(1,_dalitzSpace,dirname);
  Abarpdf = new RooIsobar3Pi(-1,_dalitzSpace,dirname);
  nResA = Apdf->getnRes();

  //Here I compute the normalization over the Dalitz
  //Apdf->calNorm();
  //Abarpdf->calNorm();
 
  //define a proxy list to float the variables in the fit
  _prxyList   = new RooListProxy("prxyList","prxyList",this);

  //retrieve proxies from the Dalitz manager
  obsList = new RooArgList();
  obsList = Apdf->getObsList();

  //add to the list observables from this class
  TIterator*  tIter   = obsList->createIterator();
  RooAbsArg*  coef;
  while(coef = (RooAbsArg*)tIter->Next()) {
    if (!dynamic_cast<RooAbsReal*>(coef)) assert(0);
    _prxyList->add(*coef);
  }

  delete tIter;

  getNormarray();

   _plusExp = declareBasis("exp(-@0/@1)",RooArgList(c2));
   _minusExp = declareBasis("exp(-@0/@1)",RooArgList(c3));
   _cosExp = declareBasis("exp(-@0/@1)*cos(@0*@2)",RooArgList(tau,c1));
   _sinExp = declareBasis("exp(-@0/@1)*sin(@0*@2)",RooArgList(tau,c1));
}

//Copy Constructor
RooTimepdf3pi::RooTimepdf3pi(const RooTimepdf3pi& other, const char* name) :
  RooAbsAnaConvPdf(other,name),
  _d0Lifetime("d0Lifetime",this,other._d0Lifetime),
  _m13("m13",this,other._m13),
  _m23("m23",this,other._m23),
  _plusExp(other._plusExp),
  _minusExp(other._minusExp),
  _cosExp(other._cosExp),
  _sinExp(other._sinExp)
   {
  _dalitzSpace = other._dalitzSpace;
  _c1 = other._c1;
  _c2 = other._c2;
  _c3 = other._c3;
  _tau = other._tau;
  _qp = other._qp;
  _phi = other._phi;
   Apdf = other.Apdf;
   Abarpdf = other.Abarpdf;
  _prxyList = other._prxyList;
   nResA = other.nResA; 
  _D0flav = other._D0flav;

  getNormarray();
}

//calculate the coefficients for the constant, linear and quadratic terms of the temporal dependence
double RooTimepdf3pi::coefficient(Int_t basisIndex) const
{
  if(!Apdf->inDalitz(_m13,_m23)) return 0.;

  static double cachedm13 = _m13;
  static double cachedm23 = _m23;

  static EvtComplex A1 = Apdf->getamp(_m13,_m23);
  static EvtComplex A2 = Abarpdf->getamp(_m13,_m23);
  const EvtComplex qoverp = EvtComplex(_qp*cos(_phi),_qp*sin(_phi));

  if ((cachedm13 != _m13) || (cachedm23 != _m23)) {
    A1 = Apdf->getamp(_m13,_m23);
    A2 = Abarpdf->getamp(_m13,_m23);
    cachedm13 = _m13;
    cachedm23 = _m23;
  }

  const double Asquare =  abs2(A1);
  const double Abarsquare =  abs2(A2);
  const EvtComplex prod = qoverp*A2*conj(A1);

  if(basisIndex == _plusExp)       return Asquare + pow(_qp,2.)*Abarsquare - 2.*real(prod);
  else if(basisIndex == _minusExp) return Asquare + pow(_qp,2.)*Abarsquare + 2.*real(prod); 
  else if(basisIndex == _cosExp)   return 2.*(Asquare - pow(_qp,2.)*Abarsquare);
  else if(basisIndex == _sinExp)   return 4.*imag(prod);
  else assert(0);
  
  return 0.;
}

Int_t RooTimepdf3pi::getCoefAnalyticalIntegral(Int_t /*code*/, RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const
{
  //Advertize existence of own integration over the Dalitz plot.
  //no need to show any temporal integration, RooAbsAnaConv takes care of it
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << GetName() << ": Requested integration over these variables: " << endl;
  allVars.Print("V");
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;

  if (matchArgs(allVars,analVars,_m13,_m23)) return 1;
  cout << "Not matched" << endl;
  return 0 ;
}

double RooTimepdf3pi::coefAnalyticalIntegral(Int_t basisIndex, Int_t code, const char* /*rangeName*/) const 
{
  switch(code) {
    // No integration
  case 0: return coefficient(basisIndex) ;

    // Integration over 'm13' and 'm23' 
  case 1:
     const EvtComplex qoverp = EvtComplex(_qp*cos(_phi),_qp*sin(_phi));

     if(basisIndex == _plusExp)       return Apdf->getNormalization() + pow(_qp,2.)*Abarpdf->getNormalization() - 2.*real(qoverp*getI1());
     else if(basisIndex == _minusExp) return Apdf->getNormalization() + pow(_qp,2.)*Abarpdf->getNormalization() + 2.*real(qoverp*getI1());
     else if(basisIndex == _cosExp)   return 2.*(Apdf->getNormalization() - pow(_qp,2.)*Abarpdf->getNormalization());
     else if(basisIndex == _sinExp)   return 4.*imag(qoverp*getI1());
     else assert(0);
  }
  return 0.;
}

void RooTimepdf3pi::getNormarray()
{
  //read the integral value from the cache file.
  static string int_name = Apdf->get_crossInt_name();

  ifstream f;
  f.open(int_name.c_str());
  if (!f){
    cout << "Error opening file " << endl;
    assert(0);
  }

  double re = 0., im = 0.;
  //Read in the cache file and store back to array
  for(Int_t j=1;j<=nResA;j++) {
    for(Int_t k=1;k<=nResA;k++){
      f >> re >> im; 
      normarray[j][k] = EvtComplex(re,im);
    }
  }
}

EvtComplex RooTimepdf3pi::getI1() const
{
  EvtComplex I_1prime(0.,0.);

  for(Int_t dummyRS=1;dummyRS<=nResA;dummyRS++){
    const EvtComplex coeff_RS(Apdf->_ampRes[dummyRS]->getVal()*cos(Apdf->_phaseRes[dummyRS]->getVal()*_pi/180.),Apdf->_ampRes[dummyRS]->getVal()*sin(Apdf->_phaseRes[dummyRS]->getVal()*_pi/180.));

    for(Int_t dummyWS=1;dummyWS<=nResA;dummyWS++){
      const EvtComplex coeff_WS(Abarpdf->_ampRes[dummyWS]->getVal()*cos(Abarpdf->_phaseRes[dummyWS]->getVal()*_pi/180.),Abarpdf->_ampRes[dummyWS]->getVal()*sin(Abarpdf->_phaseRes[dummyWS]->getVal()*_pi/180.));
      I_1prime += conj(coeff_RS)*coeff_WS*normarray[dummyRS][dummyWS];
    }
  }
  return I_1prime;
}

///////////////////////////////////////////////////////////////////////
//
//                 Event generation
//
//////////////////////////////////////////////////////////////////////

Int_t RooTimepdf3pi::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK) const {
  // Advertise own event generator.
  cout << "==============================================================" << endl;
  cout << GetName() << ": Requested generation of these variables:" << endl;
  directVars.Print("V");
  cout << "==============================================================" << endl << endl;
  
  if (staticInitOK) {
  if (matchArgs(directVars,generateVars,_m13,_m23,_d0Lifetime)) return 3;
  else if (matchArgs(directVars,generateVars,_d0Lifetime)) return 2;
  }

  if (matchArgs(directVars,generateVars,_m13,_m23)) return 1;

  cout << "Not matched" << endl;
  return 0 ;
}

void RooTimepdf3pi::initGenerator(Int_t code)
{
  assert(code==3);

  _x = _tau*_c1;
  _y = _tau/_c2 - 1.;

  if(_pdfmax > 0.) return;

  cout << "Dalitz Limits used for generation:" << endl;
  cout << "m13 -> " << _dalitzSpace->qAbsMin(EvtCyclic3::AC)+1e-6 << " " << _dalitzSpace->qAbsMax(EvtCyclic3::AC)+1e-6 << endl;
  cout << "m23 -> " << _dalitzSpace->qAbsMin(EvtCyclic3::BC)+1e-6 << " " << _dalitzSpace->qAbsMax(EvtCyclic3::BC)+1e-6 << endl;

  // sample Dalitz space to find the highest pdf
  _pdfmax = -1.;

  Int_t nsample(0);

  cout << GetName() << ": Searching for PDF maximum" << flush;
  while (nsample++ < 200000){
    double pdftmp = sampleEvent();
    if (pdftmp > _pdfmax) _pdfmax = pdftmp;
  }
  _pdfmax*=1.07;      // increase for safety 

  cout << " = " << _pdfmax << endl;
}

double RooTimepdf3pi::sampleEvent()
{
  static const double _m13min = _m13.min();
  static const double _m13max = _m13.max();
  static const double _m23min = _m23.min();
  static const double _m23max = _m23.max();

  // Sample time-integrated m13,m23 distribution
  while (1){
    _m13 = _m13min + (_m13max - _m13min)*RooRandom::uniform();
    _m23 = _m23min + (_m23max - _m23min)*RooRandom::uniform();

    if(!Apdf->inDalitz(_m13,_m23)) continue;

    return _c2*coefficient(_plusExp) + _c3*coefficient(_minusExp) + ((_tau)/(1+(_c1*_c1)*(_tau*_tau)))*(coefficient(_cosExp)+(_c1*_tau)*coefficient(_sinExp));
  }
  return 0.;
}

void RooTimepdf3pi::generateEvent(Int_t code) 
{
  // Generate event
  assert(code==3);

  static int numDalitzGenerated(0);

  while (1){
    double acceptProb = sampleEvent();

    if (++numDalitzGenerated == 1000000) {
      cout << "Generated one million Dalitz events. Parameters are " << _m13 << ", " << _m23 << ", " << acceptProb << ", " << _pdfmax << endl;
      numDalitzGenerated = 0;
    }

    if (_pdfmax*RooRandom::uniform() > acceptProb) continue;

    if (acceptProb > _pdfmax){
      cout << Class_Name() << ": probability = " << acceptProb << " > max. probability(DP) = " << _pdfmax << endl;
      assert(0);
    }

    break;
  }

  _totGen++;

  genLifetime();

  if(fmod((double)_totGen,1000.) == 0) cout << "So far generated " << _totGen << " events" << endl;
  return;
}

void RooTimepdf3pi::genLifetime() 
{
  static int numTimeGenerated(0);

  // Now get time distribution at this particular point. 
  _d0Lifetime = 0.;
  double analyticMaxValue = evaluate();

  const double a1square = coefficient(_plusExp) * (1 + _y);
  const double a2square = coefficient(_minusExp) * (1 - _y);
  const double a1a2re = coefficient(_cosExp);
  const double a1a2im = coefficient(_sinExp);

  const double squareCoeff = a1square * _y*_y*0.5 + a2square*_y*_y*0.5 - (a1a2re -_x*a1a2im)*_x*_x;
  const double linearCoeff = a1square * (-_y) + a2square*_y + 2*_x*(_x*a1a2re + a1a2im);
  const double constantTrm = a1square + a2square + 2*(a1a2re - _x*a1a2im);
  const double radicand = linearCoeff*linearCoeff - 4*squareCoeff*constantTrm;

  if (radicand > 0.){   // If no extrema, maximum occurs at t = 0, which we already have calculated. 

    // Need to check both solutions and 0 for maximum
    const double firstSolution = (-linearCoeff+sqrt(radicand))/(2*squareCoeff);
    const double secondSolution = (-linearCoeff-sqrt(radicand))/(2*squareCoeff);
  
    if (firstSolution > 0.) {
      _d0Lifetime = firstSolution*_tau;
      const double value = evaluate();
      if (value > analyticMaxValue) analyticMaxValue = value;
    }

    if (secondSolution > 0.) {
      _d0Lifetime = secondSolution*_tau;
      const double value = evaluate();  // ACK! The inefficiency! It hurts!
      if (value > analyticMaxValue) analyticMaxValue = value;
    }
  }

  while(1){

    const double randomPoint = RooRandom::uniform() * 4.;
    _d0Lifetime = randomPoint;
    const double valueAtPoint = evaluate();

    if (valueAtPoint > analyticMaxValue) assert(0);
    if (++numTimeGenerated == 1000000) {  
      cout << "Generated one million time events. Parameters are " << _m13 << ", " << _m23 << ", " << randomPoint << ", " << valueAtPoint  << ", " << analyticMaxValue << endl;   
      numTimeGenerated = 0;
    }

    const double randomHeight = RooRandom::uniform() * analyticMaxValue;
    if (randomHeight > valueAtPoint) continue;

    break;

  }
  return;
}
