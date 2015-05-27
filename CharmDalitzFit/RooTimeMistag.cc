 /****************************************************************************
 * Project: Kpipipdf                                                         *
 * Package: CharmDalitzFit                                                   *
 *    File: $Id: RooTimeMistag.cc,v 1.11 2008/06/10 17:08:26 pellicci Exp $      * 
 * Authors:                                                                  *
 *   MP, Mario Pelliccioni, Univerista di Torino, pellicci@slac.stanford.edu *
 *   GC, Gianluca Cavoto, Universita di Roma, cavoto@slac.stanford.edu       *
 *****************************************************************************/

#include <iostream>
#include <math.h>
#include "CharmDalitzFit/RooTimeMistag.hh"

#include "RooFitCore/RooRandom.hh"
#include "RooFitCore/RooRealConstant.hh"

#include "EvtGenBase/EvtComplex.hh"
#include "EvtGenBase/EvtDalitzPoint.hh"

using namespace std;

ClassImp(RooTimeMistag);

// constructor
//Define our constructor, we need m12^2 and m13^2, as our dalitz variable
RooTimeMistag::RooTimeMistag(const char *name, const char *title, RooRealVar& d0Lifetime, RooAbsReal& tau,
			     RooAbsReal& m12, RooAbsReal& m13, const Int_t D0flav, const RooResolutionModel& model, EvtDalitzPlot* dalitzSpace, const string dirname):
  RooAbsAnaConvPdf(name,title,model,d0Lifetime),
  _d0Lifetime("d0Lifetime","The D0 lifetime",this,d0Lifetime),
  _tau("tau","Mixing life time",this,tau),
  _m12("m12","m12",this,m12),
  _m13("m13","m13",this,m13)
{
  //define a proxy list to float the amplitude and phase
  _prxyList   = new RooListProxy("prxyList","prxyList",this);

  //initialize our dalitz model and retrieve the informations about the dalitz
  _dalitzSpace = dalitzSpace;
  RSpdf = new RooIsobar((-1*D0flav),0,_dalitzSpace,dirname);
  I3value = RSpdf->getNormalization();
  assert(I3value!=0.);
  _pdfmax = -1.;

  _noDalitz = kFALSE;

  //declare the temporal dependence for the convolution
  _basisExp = declareBasis("exp(-@0/@1)",RooArgList(tau));
}

//Secondary constructor, does not consider the Dalitz
RooTimeMistag::RooTimeMistag(const char *name, const char *title, RooRealVar& d0Lifetime, RooAbsReal& tau, const RooResolutionModel& model, EvtDalitzPlot* dalitzSpace, const string dirname):
  RooAbsAnaConvPdf(name,title,model,d0Lifetime),
  _d0Lifetime("d0Lifetime","The D0 lifetime",this,d0Lifetime),
  _tau("tau","Mixing life time",this,tau),
  _m12("m12","m12",this,(RooRealVar&)RooRealConstant::value(1)),
  _m13("m13","m13",this,(RooRealVar&)RooRealConstant::value(1))
{
  //define a proxy list to float the amplitude and phase
  _prxyList   = new RooListProxy("prxyList","prxyList",this);
  _dalitzSpace = dalitzSpace;
  RSpdf = new RooIsobar(-1,0,_dalitzSpace,dirname);

  _pdfmax = -1.;

  _noDalitz = kTRUE;

  //declare the temporal dependence for the convolution
  _basisExp = declareBasis("exp(-@0/@1)",RooArgList(tau));
}

//Copy Constructor
RooTimeMistag::RooTimeMistag(const RooTimeMistag& other, const char* name) :
  RooAbsAnaConvPdf(other,name),
  _d0Lifetime("d0Lifetime",this,other._d0Lifetime),
  _tau("tau",this,other._tau),
  _m12("m12",this,other._m12),
  _m13("m13",this,other._m13),
  _prxyList(other._prxyList),
  _basisExp(other._basisExp)
{
  _dalitzSpace = other._dalitzSpace;
  _pdfmax = other._pdfmax;
  RSpdf = other.RSpdf;
  I3value = other.I3value;
  _noDalitz = other._noDalitz;
}

//calculate the coefficients for the constant, linear and quadratic terms
//of the temporal dependence
Double_t RooTimeMistag::coefficient(Int_t basisIndex) const
{
  if(_noDalitz) return 1.;
  const Double_t _m23 = getm23();
  EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),_m12,_m23,_m13);
  if(!_dalitzPoint.isValid()) return 0.;

  if(basisIndex == _basisExp) return abs2(RSpdf->getamp(&_dalitzPoint))/I3value;
  assert(0);
  return 0.;
}

Int_t RooTimeMistag::getCoefAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const
{
  // Advertize existence of own integration over the Dalitz plot.
  //no need to show any temporal integration, RooAbsAnaConv takes care of it
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << GetName() << ": Requested integration over these variables: " << endl;
  allVars.Print("V");
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
  if (matchArgs(allVars,analVars,_m12,_m13)) return 1 ;
  return 0 ;
}

Double_t RooTimeMistag::coefAnalyticalIntegral(Int_t basisIndex, Int_t code, const char* /*rangeName*/) const 
{
  switch(code) {
    // No integration
  case 0: return coefficient(basisIndex) ;

    // Integration over 'm12' and 'm13' 
  case 1:
    if(basisIndex == _basisExp) return 1.;
    else assert(0);
  }
  return 0.;
}

///////////////////////////////////////////////////////////////////////
//
//                 Event generation
//
//////////////////////////////////////////////////////////////////////
Int_t RooTimeMistag::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK) const {
  // Advertise own event generator.
  cout << "==============================================================" << endl;
  cout << GetName() << ": Requested generation of these variables:" << endl;
  directVars.Print("V");
  cout << "==============================================================" << endl << endl;

  if (matchArgs(directVars,generateVars,_m12,_m13,_d0Lifetime)) return 2;
  if (matchArgs(directVars,generateVars,_d0Lifetime)) return 1;
  cout << "Not matched" << endl;
  return 0 ;
}

void RooTimeMistag::initGenerator(Int_t code)
{
  if(code==2){

  if (_pdfmax > 0.) return;

  // sample Dalitz space to find the highest pdf
  _pdfmax=-1.;
  Int_t nsample = 0;

  cout << GetName() << ": Searching for PDF maximum" << flush;
  while (nsample++ < 20000){
    Double_t pdftmp = sampleEvent();
    if (pdftmp>_pdfmax) _pdfmax=pdftmp;
  }
  _pdfmax*=1.1; // increase for safety 
  cout << " = " << _pdfmax << endl;
  }
}

Double_t RooTimeMistag::sampleEvent()
{
  // Sample time-integrated m12,m13 distribution
  while (1){
    _m12 = _m12.min() + (_m12.max() - _m12.min())*RooRandom::uniform();
    _m13 = _m13.min() + (_m13.max() - _m13.min())*RooRandom::uniform();

    const Double_t _m23 = getm23();
    EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),_m12,_m23,_m13);
    if(!_dalitzPoint.isValid()) continue;
    return coefficient(_basisExp);
  }
  return 0.;
}

void RooTimeMistag::generateEvent(Int_t code) 
{
  if(code==1){
    while(1){
      _totGen++;
      Double_t rand = RooRandom::uniform();
      Double_t dtval = -_tau*log(rand);
      if (dtval<0. || dtval> 4.) continue;
      _d0Lifetime = dtval;
      break;
    }
    return;
  }

  assert(code==2);
  _totGen++;
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

  while(1){
    Double_t rand = RooRandom::uniform();
    Double_t dtval = -_tau*log(rand);
    if (dtval<0. || dtval> 4.) continue;
    _d0Lifetime = dtval;
    if(fmod((Double_t)_totGen,100.)==0) cout << "So far generated " << _totGen << " events of mistag background" << endl;
    return;
  }
  return;
}
