/*****************************************************************************
 * Project: BaBar detector at the SLAC PEP-II B-factory
 * Package: CharmDalitzFit
 *    File: $Id: RooDPbkg.cc,v 1.17 2008/06/10 17:08:25 pellicci Exp $
 * Authors:
 *   MP, Mario Pelliccioni, Universita' di Torino, pellicci@slac.stanford.edu
 *   GC, GIanluca Cavoto, Universita' di Roma, cavoto@slac.stanford.edu
 *****************************************************************************/

using namespace::std;

#include <iostream>
#include <fstream>
#include <math.h>
#include "RooFitCore/RooArgSet.hh"
#include "CharmDalitzFit/RooDPbkg.hh"
#include "EvtGenBase/EvtPropBreitWignerRel.hh"
#include "EvtGenBase/EvtPto3PAmp.hh"

ClassImp(RooDPbkg);

// Constructor
RooDPbkg::RooDPbkg(EvtDalitzPlot *dalitzSpace)
{
  _dalitzSpace = dalitzSpace;
  initResonance();
}

//Return the normalization
Double_t RooDPbkg::getNormalization() const
{
  Double_t norm = 0.;

  const Double_t nstepx = 600.;
  const Double_t nstepy = 600.;
  
  const Double_t xmin = _dalitzSpace->qAbsMin(EvtCyclic3::AB);
  const Double_t xmax = _dalitzSpace->qAbsMax(EvtCyclic3::AB);
  const Double_t ymin = _dalitzSpace->qAbsMin(EvtCyclic3::AC);
  const Double_t ymax = _dalitzSpace->qAbsMax(EvtCyclic3::AC);

  for(Int_t ii=0;ii<(nstepx-1);ii++){
    const Double_t xstep = xmin + ((ii+0.5)*((xmax-xmin)/nstepx));
    for(Int_t jj=0;jj<(nstepy-1);jj++){
      const Double_t ystep = ymin + ((jj+0.5)*((ymax-ymin)/nstepy));      
 
      const Double_t zstep = getm23(xstep,ystep);
      const EvtDalitzPoint _dalitzPoint(_dalitzSpace->mA(),_dalitzSpace->mB(),_dalitzSpace->mC(),xstep,zstep,ystep);
      if(!_dalitzPoint.isValid()) continue;
      const Double_t tmpamp = getamp(&_dalitzPoint);
      norm += tmpamp*((xmax-xmin)/nstepx)*((ymax-ymin)/nstepy);
    }
  }
  return norm;
}

Double_t RooDPbkg::getamp(const EvtDalitzPoint *point) const
{
  //This return the f(m+^2,m-^2)
  Double_t dalitzamplitude = 0.;

  for (Int_t i=0; i<nRes; i++) {    
    const Double_t coeff = pow(_ampRes[i]->getVal(),2); 
    const EvtComplex matrixelement = ResAmp(point,i);
    dalitzamplitude += abs2(matrixelement)*coeff;    
  }
  
  const Double_t m12 = point->q(EvtCyclic3::AB); 
  const Double_t m13 = point->q(EvtCyclic3::AC);

  const Double_t tmp=fabs(1+_a1->getVal()*m12+_a2->getVal()*m13+_a3->getVal()*pow(m12,2)+_a4->getVal()*pow(m13,2)+_a5->getVal()*m12*m13+_a6->getVal()*pow(m12,3)+_a7->getVal()*pow(m13,3)+_a8->getVal()*m12*pow(m13,2)+_a9->getVal()*m13*pow(m12,2));

 return _fra->getVal()*(dalitzamplitude) + (1-_fra->getVal())*tmp;
}

void RooDPbkg::initResonance() 
{
  _obs_list = new RooArgList() ;
 
 //Define all RooRealVar floating observables
  _ampRes.push_back(new RooRealVar("Kstzero_ampBkg","Kstzero_ampBkg",0.10,0,100));
  _ampRes.push_back(new RooRealVar("Rho_ampBkg","Rho_ampBkg",1.0));
  _ampRes.push_back(new RooRealVar("Kstminus_ampBkg","Kstminus_ampBkg",0.0,0,100));
  _ampRes.push_back(new RooRealVar("Kstm1430_ampBkg","Kstm1430_ampBkg",2.85,0,100));
  _ampRes.push_back(new RooRealVar("Kstz1430_ampBkg","Kstz1430_ampBkg",2.85,0,100));

  _mRes.push_back(new RooRealVar("Kstzero_mass","Ksplus_mass",0.89166,0.7,1));
  _mRes.push_back(new RooRealVar("Rho_mass","Rho_mass",0.7755,0.1,1));
  _mRes.push_back(new RooRealVar("Kstminus_mass","Kstminus_mass",0.896,0.7,2));
  _mRes.push_back(new RooRealVar("Kstm1430_mass","Kstm1430_mass",1.412,1.,3.));
  _mRes.push_back(new RooRealVar("Kstz1430_mass","Kstz1430_mass",1.412,1.,3.));

  _widthRes.push_back(new RooRealVar("Kstzero_width","Ksplus_width",0.0508,0.01,2.));
  _widthRes.push_back(new RooRealVar("Rho_width","Rho_width",0.1494,0.01,2.));
  _widthRes.push_back(new RooRealVar("Kstminus_width","Kstminus_width",0.0503,0.01,1));
  _widthRes.push_back(new RooRealVar("Kstm1430_width","Kstm1430_width",294.0/1000.0,0.01,2.));
  _widthRes.push_back(new RooRealVar("Kstz1430_width","Kstz1430_width",294.0/1000.0,0.01,2.));

  _spinRes.push_back(EvtSpinType::VECTOR);
  _spinRes.push_back(EvtSpinType::VECTOR);
  _spinRes.push_back(EvtSpinType::VECTOR);
  _spinRes.push_back(EvtSpinType::VECTOR);
  _spinRes.push_back(EvtSpinType::VECTOR);

  _trackinfo.push_back(EvtCyclic3::AB);
  _trackinfo.push_back(EvtCyclic3::BC);
  _trackinfo.push_back(EvtCyclic3::AC);
  _trackinfo.push_back(EvtCyclic3::AC);
  _trackinfo.push_back(EvtCyclic3::AB);

  _nameRes.push_back(TString("KstzeroBkg"));
  _nameRes.push_back(TString("RhoBkg"));
  _nameRes.push_back(TString("KstminusBkg"));
  _nameRes.push_back(TString("Kstm1430Bkg"));
  _nameRes.push_back(TString("Kstz1430Bkg"));

  _a1=new RooRealVar("a1","a1",0,-1000.,1000.);
  _a2=new RooRealVar("a2","a2",0,-1000.,1000.);
  _a3=new RooRealVar("a3","a3",0,-1000.,1000.);
  _a4=new RooRealVar("a4","a4",0,-1000.,1000.);
  _a5=new RooRealVar("a5","a5",0,-1000.,1000.);
  _a6=new RooRealVar("a6","a6",0,-1000.,1000.);
  _a7=new RooRealVar("a7","a7",0,-1000.,1000.);
  _a8=new RooRealVar("a8","a8",0,-1000.,1000.);
  _a9=new RooRealVar("a9","a9",0,-1000.,1000.);

  _fra=new RooRealVar("fra","fra",0.12873,0.,1.);

  nRes = _ampRes.size();

  //Now readin the initial values from config3.txt
  RooArgSet parameters;
  for (Int_t dummy=0;dummy<nRes;dummy++)
    {
      parameters.add(*_ampRes[dummy]);
      parameters.add(*_mRes[dummy]);
      parameters.add(*_widthRes[dummy]);
    }
  parameters.add(*_a1);
  parameters.add(*_a2);
  parameters.add(*_a3);
  parameters.add(*_a4);
  parameters.add(*_a5);
  parameters.add(*_a6);
  parameters.add(*_a7);
  parameters.add(*_a8);
  parameters.add(*_a9);
  parameters.add(*_fra);
  parameters.readFromFile("configBkg.txt");

  //put all RooRealVar into the observable list
  for (Int_t dummy=0;dummy<nRes;dummy++){
    cout << "Now adding " << _nameRes[dummy] << endl;
    _obs_list->add(*_ampRes[dummy]);
    _obs_list->add(*_mRes[dummy]);	
    _obs_list->add(*_widthRes[dummy]);
  }
   _obs_list->add(*_a1);
   _obs_list->add(*_a2);
   _obs_list->add(*_a3);
   _obs_list->add(*_a4);
   _obs_list->add(*_a5);
   _obs_list->add(*_a6);
   _obs_list->add(*_a7);
   _obs_list->add(*_a8);
   _obs_list->add(*_a9);
   _obs_list->add(*_fra);
}

//This returns our Form Factor
//In most of the case, we return relativistic Breit-Wigner
EvtComplex RooDPbkg::ResAmp(const EvtDalitzPoint *_dalitzPoint, const Int_t i) const
{
  //retrieve the informations about the resonance
  const Double_t res_Mass = _mRes[i]->getVal();
  const Double_t res_Gamma = _widthRes[i]->getVal();
  const EvtSpinType::spintype res_Spin  = _spinRes[i];
  const EvtCyclic3::Pair res_Pair  = _trackinfo[i];
  EvtCyclic3::Pair hel_Pair  = EvtCyclic3::next( res_Pair );

  if(i==2) hel_Pair = EvtCyclic3::prev( res_Pair );

  if(!_dalitzPoint->isValid()) {
    _dalitzPoint->print();
    assert (_dalitzPoint->isValid()); // no physics reason to fail
  }

  EvtPropBreitWignerRel evtProp(res_Mass,res_Gamma);
  EvtPto3PAmp amplitude(*_dalitzSpace,hel_Pair,res_Pair,res_Spin,evtProp,EvtPto3PAmp::RBW_CLEO);

  //set the Blatt factor
  amplitude.set_fd(1.5);
  amplitude.set_fb(5.);

  return amplitude.evaluate(*_dalitzPoint);
}
