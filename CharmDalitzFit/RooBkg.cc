 /****************************************************************************
 * Package: CharmDalitzFit                                                   *
 *    File: $Id: RooBkg.cc,v 1.13 2008/06/10 17:08:25 pellicci Exp $         * 
 * Authors:                                                                  *
 *   MP, Mario Pelliccioni, Univ Torino, pellicci@slac.stanford.edu          *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
          
#include <iostream>
#include <math.h>

#include "RooFitCore/RooRandom.hh"
#include "CharmDalitzFit/RooBkg.hh"
#include "EvtGenBase/EvtDalitzPoint.hh"

ClassImp(RooBkg)

// constructor
RooBkg::RooBkg(const char *name, const char *title,
			 RooAbsReal& m12, RooAbsReal& m13, EvtDalitzPlot *dalitzSpace):
  RooAbsPdf(name,title),
  _m12("m12","Invariant Mass square of M12",this,m12),
  _m13("m13","Invariant Mass square of M13",this,m13)
{
  _dalitzSpace = dalitzSpace;
  _dpManager = new RooDPbkg(_dalitzSpace);
  _pdfmax = -1;

  _prxyList   = new RooListProxy("prxyList","prxyList",this);
  RooArgList* obsList = _dpManager->getObsList();
  TIterator*  tIter   = obsList->createIterator();
  RooAbsArg*  coef;
  while(coef = (RooAbsArg*)tIter->Next()) {
    if (!dynamic_cast<RooAbsReal*>(coef)) assert(0);
    _prxyList->add(*coef);
  }
  delete tIter;
}

//Copy Constructor
RooBkg::RooBkg(const RooBkg& other, const char* name) :
  RooAbsPdf(other,name),
  _m12("m12",this,other._m12),
  _m13("m13",this,other._m13),
  _dpManager(other._dpManager),
  _prxyList(other._prxyList),
  _dalitzSpace(other._dalitzSpace)
{
  _pdfmax = other._pdfmax;
}

Double_t RooBkg::evaluate() const
{
  const Double_t _m23 = getm23();
  const EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),_m12,_m23,_m13);
  if(!_dalitzPoint.isValid()) return 0.;
  return _dpManager->getamp(&_dalitzPoint);
}

Int_t RooBkg::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const 
{
  allVars.Print();
  if(matchArgs(allVars,analVars,_m12,_m13)) return 1 ;
  return 0 ;
}

Double_t RooBkg::analyticalIntegral(Int_t code, const char* rangeName) const 
{
  assert(code==1);
  return _dpManager->getNormalization();
}

///////////////////////////////////////////////////////////////////////
//
//                 Event generation
//
//////////////////////////////////////////////////////////////////////

Int_t RooBkg::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK) const {
  if (matchArgs(directVars,generateVars,_m12,_m13)) return 1;
  cout <<"No matched vars for RooBkg, this should mean somewhere there is a problem!"<<endl;
  return 0 ;
}

void RooBkg::initGenerator(Int_t code)
{
  assert(code==1);
  if (_pdfmax > 0.) return;

  // sample Dalitz space to find the highest pdf
  _pdfmax=-1;
  Int_t nsample=0;
  while (nsample++<20000){
    const Double_t pdftmp = sampleEvent();
    if(pdftmp > _pdfmax) _pdfmax=pdftmp;
  }
  _pdfmax *= 1.1; // increase for safety
  cout << GetName() << ": pdfmax = " << _pdfmax << endl;
}

Double_t RooBkg::sampleEvent()
{
  // Sample m12,m13 distribution
  while (1) {
    _m12 = _m12.min() + (_m12.max() - _m12.min())*RooRandom::uniform();
    _m13 = _m13.min() + (_m13.max() - _m13.min())*RooRandom::uniform();

    const Double_t _m23 = getm23();
    const EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),_m12,_m23,_m13);
    if(!_dalitzPoint.isValid()) continue;
    return _dpManager->getamp(&_dalitzPoint);
  }
  return 0.;
}

void RooBkg::generateEvent(Int_t code) {
  // Generate event
  assert(code==1);
  _totGen++;

  while (1){
    const Double_t acceptProb = sampleEvent();
    if(acceptProb > _pdfmax){
      cout << Class_Name()
           << ": probability = " << acceptProb << " > max. probability(DP) = " << _pdfmax << endl;
      assert(0);
    }
    if (_pdfmax*RooRandom::uniform() > acceptProb) continue;
    if(fmod((Double_t)_totGen,100.)==0) cout << "So far generated " << _totGen << " events of combinatoric background" << endl;
    break;
  }
}
