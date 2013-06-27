 /****************************************************************************
 * Project: Kpipipdf                                                         *
 * Package: CharmDalitzFit                                                   *
 *    File: $Id: RooKpipi0pdf.cc,v 1.19 2009/08/24 08:47:32 pellicci Exp $    * 
 * Authors:                                                                  *
 *   MP, Mario Pelliccioni, Univerista di Torino, pellicci@slac.stanford.edu *
 *   GC, Gianluca Cavoto, Universita di Roma, cavoto@slac.stanford.edu       *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
          
#include <iostream>
#include <math.h>
#include "CharmDalitzFit/RooKpipi0pdf.hh"
#include <RooAbsReal.h>
#include <RooRandom.h>
#include "EvtGenBase/EvtComplex.hh"
#include "EvtGenBase/EvtDalitzPoint.hh"

using namespace std;

ClassImp(RooKpipi0pdf)

// constructor
//Define our constructor, we need m12^2 and m13^2, as our dalitz variable
RooKpipi0pdf::RooKpipi0pdf(const char *name, const char *title, RooAbsReal& m12, RooAbsReal& m13, EvtDalitzPlot *dalitzSpace, const string dirname, Int_t isD0):
  RooAbsPdf(name,title),
  _m12("m12","Invariant Mass square of M12",this,m12),
  _m13("m13","Invariant Mass square of M13",this,m13)
{
  _dalitzSpace = dalitzSpace;
  _pdfmax = -1.;

  //Create and initalize our isobar model
  _dpManager = new RooIsobar(isD0,0,_dalitzSpace,dirname);

  //define a proxy list to float the amplitude and phase
  _prxyList   = new RooListProxy("prxyList","prxyList",this);

  //Create a observable list and get the list from _dpManager  
  obsList = new RooArgList();
  obsList = _dpManager->getObsList();

  TIterator*  tIter   = obsList->createIterator();
  RooAbsArg*  coef;
  while(coef = (RooAbsArg*)tIter->Next()) {
    if (!dynamic_cast<RooAbsReal*>(coef)) assert(0);
    _prxyList->add(*coef);
  }
  delete tIter;
}

//Copy Constructor
RooKpipi0pdf::RooKpipi0pdf(const RooKpipi0pdf& other, const char* name) :
  RooAbsPdf(other,name),
  _m12("m12",this,other._m12),
  _m13("m13",this,other._m13),
  _prxyList(other._prxyList),
  _dpManager(other._dpManager),
  _dalitzSpace(other._dalitzSpace),
  _pdfmax(other._pdfmax)
{}

Double_t RooKpipi0pdf::evaluate() const
{
  const Double_t _m23 = getm23();
  EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),_m12,_m23,_m13);
  if(!_dalitzPoint.isValid()) return 0.00000000000001;

  return abs2(_dpManager->getamp(&_dalitzPoint));
}

//We don't use RooFit normalization engine.
//2 reason. 1. RooFit integral is too slow
//2nd. We need to pre-calculate the integral first before we start the fit
Int_t RooKpipi0pdf::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const 
{
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << GetName() << ": Requested integration over these variables: " << endl;
  allVars.Print("V");
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
  //if (matchArgs(allVars,analVars,_m12,_m13)) return 1 ;
  return 0;
}

//the normalization is calculated in _dpManager
Double_t RooKpipi0pdf::analyticalIntegral(Int_t code, const char* rangeName) const 
{
  assert(code==1);
  return _dpManager->getNormalization();
} 

///////////////////////////////////////////////////////////////////////
//
//                 Event generation
//
//////////////////////////////////////////////////////////////////////

Int_t RooKpipi0pdf::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK) const {
  if (matchArgs(directVars,generateVars,_m12,_m13)) return 1;
  cout <<"No matched vars for RooKpipi0pdf, this should mean somewhere there is a problem!"<<endl;
  return 0 ;
}

void RooKpipi0pdf::initGenerator(Int_t code)
{
  assert(code==1);

  cout << GetName() << ": Dalitz Limits used for generation:" << endl;
  cout << "m12 -> " << _dalitzSpace->qAbsMin(EvtCyclic3::AB)+1e-6 << " " << _dalitzSpace->qAbsMax(EvtCyclic3::AB)-1e-6 << endl;
  cout << "m13 -> " << _dalitzSpace->qAbsMin(EvtCyclic3::AC)+1e-6 << " " << _dalitzSpace->qAbsMax(EvtCyclic3::AC)-1e-6 << endl;

  if (_pdfmax > 0.) return;

  // sample Dalitz space to find the highest pdf
  _pdfmax=-1.;
  Int_t nsample = 0;
  while (nsample++ < 20000){
    const Double_t pdftmp = sampleEvent();
    if(pdftmp > _pdfmax) _pdfmax = pdftmp;
  }
  _pdfmax *= 1.1; // increase for safety
  cout << " = " << _pdfmax << endl;
}

Double_t RooKpipi0pdf::sampleEvent()
{
  // Sample m12,m13 distribution
  while (1) {
    _m12 = _m12.min() + (_m12.max() - _m12.min())*RooRandom::uniform();
    _m13 = _m13.min() + (_m13.max() - _m13.min())*RooRandom::uniform();

    const Double_t _m23 = getm23();
    EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),_m12,_m23,_m13);
    if(!_dalitzPoint.isValid()) continue;
    return abs2(_dpManager->getamp(&_dalitzPoint));
  }
  return 0.;
}

void RooKpipi0pdf::generateEvent(Int_t code) {
  // Generate event
  assert(code==1);

  while (1){
    const Double_t acceptProb = sampleEvent();
    if(acceptProb > _pdfmax){
      cout << Class_Name()
           << ": probability = " << acceptProb << " > max. probability(DP) = " << _pdfmax << endl;
      assert(0);
    }
    if (_pdfmax*RooRandom::uniform() > acceptProb) continue;
    break;
  }
  return;
}
