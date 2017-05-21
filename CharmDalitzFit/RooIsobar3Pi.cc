/*****************************************************************************
 * Project: BaBar detector at the SLAC PEP-II B-factory
 * Package: CharmDalitzFit
 * File: $Id: RooIsobar3Pi.cc,v 1.1 2008/03/12 15:07:48 pellicci Exp $
 * Authors:
 *   Mario Pelliccioni, pellicci@slac.stanford.edu
 *****************************************************************************/
// -- CLASS DESCRIPTION --
// RooIsobar3Pi represents a general dalitz plot class.
// it contains member functions to load all the D-decay
// dalitz dynamics. Declare the amplitude and phase of
// the resonance etc.

using namespace::std;

#include <fstream>

#include "CharmDalitzFit/RooIsobar3Pi.hh"
#include "EvtGenBase/EvtPropBreitWignerRel.hh"
#include "EvtGenBase/EvtBlattWeisskopf.hh"
#include "EvtGenBase/EvtDalitzPoint.hh"

const EvtComplex zero(0.,0.);
const EvtComplex one(1.,0.);

const double _pi = acos(-1.);

const double mA = 0.13957018;
const double mB = 0.13957018;
const double mC = 0.1349766;
const double MD0 = 1.8645;

ClassImp(RooIsobar3Pi);
// Constructor
RooIsobar3Pi::RooIsobar3Pi(const int Asign, EvtDalitzPlot *dalitzSpace, const string dirname)
{
  _Asign = Asign;
  _dalitzSpace = dalitzSpace;
  _ndiv_eff = 40;

  assert(_Asign == 1 || _Asign == -1);

  name = dirname;

  //initialize the resonance parameters in the constructor
  initResonance();
  getNormvalues();
  readefficiency();

  _dalitzamplitude = zero;
  _coeff_j = zero;
  _coeff_k = zero;
}

void RooIsobar3Pi::getNormvalues()
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

  double re = 0., im = 0.;
  //Read in the cache file and store back to array
  for(int j=1;j<=nRes;j++) {
    for(int k=1;k<=nRes;k++){
      f >> re >> im;       
      normarray[j][k] = new EvtComplex(re,im);
      normarray2[j][k] = new EvtComplex(re,im);
    }
  }
}

//Return the normalization
double RooIsobar3Pi::getNormalization() const
{
  double norm(0.);

  //Read the integral values of  BW_j*conj(BW_k) 

  for(int j=1;j<=nRes;j++){
    for(int k=1;k<=nRes;k++){
      _coeff_j = EvtComplex(_ampRes[j]->getVal()*cos(_phaseRes[j]->getVal()*_pi/180.),_ampRes[j]->getVal()*sin(_phaseRes[j]->getVal()*_pi/180.));
      _coeff_k = EvtComplex(_ampRes[k]->getVal()*cos(_phaseRes[k]->getVal()*_pi/180.),_ampRes[k]->getVal()*sin(_phaseRes[k]->getVal()*_pi/180.));
      norm += real(_coeff_j*conj(_coeff_k)*(*normarray[j][k]));
    }
  }  
  return norm;
}

inline double RooIsobar3Pi::getm12(const double m13, const double m23) const
{
return MD0*MD0 + mA*mA + mB*mB + mC*mC - m13 - m23;
}

void RooIsobar3Pi::calNorm() 
{
  //Calculate the normalization value of the pdf
  cout << "RooIsobar3Pi::calNorm() Now perform GRID integration to obtain those intergrals and dump into a cache file" << endl;

  static const int nBins = 700;
  cout << "We will do the GRID integral using bin size: " << nBins << endl;  

 //re-set the normarray
  for(int j=1;j<=nRes;j++){
    for(int k=1;k<=nRes;k++){
      *normarray[j][k] = zero;
      *normarray2[j][k] = zero;
    }
  }

  //Define the area
  static const double xmin = _dalitzSpace->qAbsMin(EvtCyclic3::AC)+1e-6;
  static const double ymin = _dalitzSpace->qAbsMin(EvtCyclic3::BC)+1e-6;
  static const double xmax = _dalitzSpace->qAbsMax(EvtCyclic3::AC)-1e-6;
  static const double ymax = _dalitzSpace->qAbsMax(EvtCyclic3::BC)-1e-6;

  static const double dhx = (xmax - xmin)/nBins;
  static const double dhy = (ymax - ymin)/nBins;

  cout << "////////////////////////////" << endl;
  cout << "Integration limits:" << endl;
  cout << "m13 -> " << xmin << " " << xmax << endl;
  cout << "m23 -> " << ymin << " " << ymax << endl;
  cout << "////////////////////////////" << endl;

  //Now scan over the dalitz plot
  for (int dx=0;dx<nBins;dx++) {
    const double m13gen = xmin + dx*dhx + dhx/2.0;
    for (int dy=0;dy<nBins;dy++) {
      const double m23gen = ymin + dy*dhy + dhy/2.0;

      if(!inDalitz(m13gen,m23gen)) continue;

      const double eff = abs2(efficiency(m13gen,m23gen));

      for(int j=1;j<=nRes;j++){
	for(int k=1;k<=nRes;k++){
	  //Get the Breit-Wigner terms
	  const EvtComplex BW_j = ResAmp(m13gen,m23gen,j);
          const EvtComplex BW_k = ResAmp(m13gen,m23gen,k);

          const EvtComplex BW_j_2 = ResAmp(m23gen,m13gen,j);
          const EvtComplex BW_k_2 = ResAmp(m23gen,m13gen,k);

          const EvtComplex integral = BW_j*conj(BW_k)*eff;
          const EvtComplex integral_2 = BW_j_2*conj(BW_k_2)*eff;
	  const EvtComplex integral_cross = conj(BW_j)*BW_k_2*eff;

	  //do the sum
	  if(_Asign == 1) *normarray[j][k] += integral;
	  else *normarray[j][k] += integral_2;
	  *normarray2[j][k] += integral_cross;
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

  for(int j=1;j<=nRes;j++) {
    for(int k=1;k<=nRes;k++){
      ofs << real(*normarray[j][k])*dhx*dhy << " " << imag(*normarray[j][k])*dhx*dhy << endl;
    }
  }
  //**********************************************************************************

  if(_Asign == 1){
    string cross_name = name + "CrossIntegralD0_RS.dat";

    ofstream ofs2(cross_name.c_str());
    if (ofs2.fail()){
      cout << "RooDPManger::calNorm(): error opening file " << endl;
      assert(0);
    }

    for(int j=1;j<=nRes;j++) {
      for(int k=1;k<=nRes;k++){
	ofs2 << real(*normarray2[j][k])*dhx*dhy << " " << imag(*normarray2[j][k])*dhx*dhy << endl;
      }
    }
  }
  //**********************************************************************************

  getNormvalues();
}

inline void RooIsobar3Pi::getFileName(char int_name[50]) const
{
  string filename;

  if(_Asign == -1) filename = name + "RooIntegralD0_Abar.dat";
  else filename = name + "RooIntegralD0_A.dat";
  sprintf(int_name,filename.c_str());

  cout << int_name << endl;
}

EvtComplex RooIsobar3Pi::getamp(const double m13, const double m23) const
{
  if(!inDalitz(m13,m23)) return zero;

  //This return the f(m+^2,m-^2)
  //The Isobar amplitude!!!!!
  _dalitzamplitude = zero;

  for (int i=1; i<=nRes; i++) {
    //get the coefficient
    _coeff_j = EvtComplex(_ampRes[i]->getVal()*cos(_phaseRes[i]->getVal()*_pi/180.0),_ampRes[i]->getVal()*sin(_phaseRes[i]->getVal()*_pi/180.0));

    if(_Asign == 1)  _dalitzamplitude += _coeff_j*ResAmp(m13,m23,i);
    else _dalitzamplitude += _coeff_j*ResAmp(m23,m13,i);
  }  

  return efficiency(m13,m23)*_dalitzamplitude;
}

double RooIsobar3Pi::getamp2(const double m13, const double m23) const
{
  return abs2(getamp(m13,m23));
}


//A brief comment here: our convention for the _trackinfo is (pi+,pi-,pi0)
void RooIsobar3Pi::initResonance()
{
  nRes = 18;

  //Define all RooRealVar floating observables
  _ampRes[1] = new RooRealVar("Rhop_amp","Rhop_amp",1.0,0.,100.);
  _ampRes[2] = new RooRealVar("Rhom_amp","Rhom_amp",1.0,0.,100.);
  _ampRes[3] = new RooRealVar("Rhoz_amp","Rhoz_amp",1.0,0.,100.);
  _ampRes[4] = new RooRealVar("Rhop_1450_amp","Rhop_1450_amp",1.0,0.,100.);
  _ampRes[5] = new RooRealVar("Rhom_1450_amp","Rhom_1450_amp",1.0,0.,100.);
  _ampRes[6] = new RooRealVar("Rhoz_1450_amp","Rhoz_1450_amp",1.0,0.,100.);
  _ampRes[7] = new RooRealVar("Rhop_1700_amp","Rhop_1700_amp",1.0,0.,100.);
  _ampRes[8] = new RooRealVar("Rhom_1700_amp","Rhom_1700_amp",1.0,0.,100.);
  _ampRes[9] = new RooRealVar("Rhoz_1700_amp","Rhoz_1700_amp",1.0,0.,100.);
  _ampRes[10] = new RooRealVar("f0_980_amp","f0_980_amp",1.0,0.,100.);
  _ampRes[11] = new RooRealVar("f0_1370_amp","f0_1370_amp",1.0,0.,100.);
  _ampRes[12] = new RooRealVar("f0_1500_amp","f0_1500_amp",1.0,0.,100.);
  _ampRes[13] = new RooRealVar("f0_1710_amp","f0_1710_amp",1.0,0.,100.);
  _ampRes[14] = new RooRealVar("f2_1270_amp","f2_1270_amp",1.0,0.,100.);
  _ampRes[15] = new RooRealVar("sigma_amp","sigma_amp",1.0,0.,100.);
  _ampRes[16] = new RooRealVar("sigmap_amp","sigmap_amp",1.0,0.,100.);
  _ampRes[17] = new RooRealVar("NonReson_amp","NonReson_amp",1.,0.,100.);
  _ampRes[18] = new RooRealVar("f2_1950_amp","f2_1950_amp",1.0,0.,100.);

  _phaseRes[1] = new RooRealVar("Rhop_phase","Rhop_phase",0.,-360.,360.);
  _phaseRes[2] = new RooRealVar("Rhom_phase","Rhom_phase",0.,-360.,360.);
  _phaseRes[3] = new RooRealVar("Rhoz_phase","Rhoz_phase",0.,-360.,360.);
  _phaseRes[4] = new RooRealVar("Rhop_1450_phase","Rhop_1450_phase",0.,-360.,360);
  _phaseRes[5] = new RooRealVar("Rhom_1450_phase","Rhom_1450_phase",0.,-360.,360);
  _phaseRes[6] = new RooRealVar("Rhoz_1450_phase","Rhoz_1450_phase",0.,-360.,360);
  _phaseRes[7] = new RooRealVar("Rhop_1700_phase","Rhop_1700_phase",0.,-360.,360);
  _phaseRes[8] = new RooRealVar("Rhom_1700_phase","Rhom_1700_phase",0.,-360.,360);
  _phaseRes[9] = new RooRealVar("Rhoz_1700_phase","Rhoz_1700_phase",0.,-360.,360);
  _phaseRes[10] = new RooRealVar("f0_980_phase","f0_980_phase",0.,-360.,360);
  _phaseRes[11] = new RooRealVar("f0_1370_phase","f0_1370_phase",0.,-360.,360);
  _phaseRes[12] = new RooRealVar("f0_1500_phase","f0_1500_phase",0.,-360.,360);
  _phaseRes[13] = new RooRealVar("f0_1710_phase","f0_1710_phase",0.,-360.,360);
  _phaseRes[14] = new RooRealVar("f2_1270_phase","f2_1270_phase",0.,-360.,360);
  _phaseRes[15] = new RooRealVar("sigma_phase","sigma_phase",0.,-360.,360.);
  _phaseRes[16] = new RooRealVar("sigmap_phase","sigmap_phase",0.,-360.,360.);
  _phaseRes[17] = new RooRealVar("NonReson_phase","NonReson_phase",0.,-360.,360.);
  _phaseRes[18] = new RooRealVar("f2_1950_phase","f2_1950_phase",0.,-360.,360);

  _massRes[1] = new RooRealVar("Rhop_mass","Rhop_mass",0.77549);
  _massRes[2] = _massRes[1];
  _massRes[3] = new RooRealVar("Rhoz_mass","Rhoz_mass",0.77549);
  _massRes[4] = new RooRealVar("Rhop_1450_mass","Rhop_1450_mass",1.465);
  _massRes[5] = _massRes[4];
  _massRes[6] = new RooRealVar("Rhoz_1450_mass","Rhoz_1450_mass",1.465);
  _massRes[7] = new RooRealVar("Rhop_1700_mass","Rhop_1700_mass",1.72);
  _massRes[8] = _massRes[7];
  _massRes[9] = new RooRealVar("Rhoz_1700_mass","Rhoz_1700_mass",1.72);
  _massRes[10] = new RooRealVar("f0_980_mass","f0_980_mass",0.980);
  _massRes[11] = new RooRealVar("f0_1370_mass","f0_1370_mass",1.370);
  _massRes[12] = new RooRealVar("f0_1500_mass","f0_1500_mass",1.505);
  _massRes[13] = new RooRealVar("f0_1710_mass","f0_1710_mass",1.724);
  _massRes[14] = new RooRealVar("f2_1270_mass","f2_1270_mass",1.2751);
  _massRes[15] = new RooRealVar("sigma_mass","sigma_mass",0.490);
  _massRes[16] = new RooRealVar("sigmap_mass","sigmap_mass",1.024);
  _massRes[17] = new RooRealVar("NonReson_mass","NonReson_mass",0.);
  _massRes[18] = new RooRealVar("f2_1950_mass","f2_1950_mass",1.944);

  _gammRes[1] = new RooRealVar("Rhop_width","Rhop_width",149.4/1000.);
  _gammRes[2] = _gammRes[1];
  _gammRes[3] = new RooRealVar("Rhoz_width","Rhoz_width",149.4/1000.);
  _gammRes[4] = new RooRealVar("Rhop_1450_width","Rhop_1450_width",400./1000.);
  _gammRes[5] = _gammRes[4];
  _gammRes[6] = new RooRealVar("Rhoz_1450_width","Rhoz_1450_width",400./1000.);
  _gammRes[7] = new RooRealVar("Rhop_1700_width","Rhop_1700_width",250./1000.);
  _gammRes[8] = _gammRes[7];
  _gammRes[9] = new RooRealVar("Rhoz_1700_width","Rhoz_1700_width",250./1000.);
  _gammRes[10] = new RooRealVar("f0_980_width","f0_980_width",100./1000.);
  _gammRes[11] = new RooRealVar("f0_1370_width","f0_1370_width",500./1000.);
  _gammRes[12] = new RooRealVar("f0_1500_width","f0_1500_width",109./1000.);
  _gammRes[13] = new RooRealVar("f0_1710_width","f0_1710_width",137./1000.);
  _gammRes[14] = new RooRealVar("f2_1270_width","f2_1270_width",185./1000.);
  _gammRes[15] = new RooRealVar("sigma_width","sigma_width",406./1000.);
  _gammRes[16] = new RooRealVar("sigmap_width","sigmap_width",89./1000.);
  _gammRes[17] = new RooRealVar("NonReson_width","NonReson_width",0.);
  _gammRes[18] = new RooRealVar("f2_1950_width","f0_1950_width",472./1000.);

  _typeRes[1] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[2] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[3] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[4] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[5] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[6] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[7] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[8] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[9] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[10] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[11] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[12] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[13] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[14] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[15] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[16] = EvtPto3PAmp::RBW_CLEO;
  _typeRes[17] = EvtPto3PAmp::NONRES;
  _typeRes[18] = EvtPto3PAmp::RBW_CLEO;

  _spinRes[1] = EvtSpinType::VECTOR;
  _spinRes[2] = EvtSpinType::VECTOR;
  _spinRes[3] = EvtSpinType::VECTOR;
  _spinRes[4] = EvtSpinType::VECTOR;
  _spinRes[5] = EvtSpinType::VECTOR;
  _spinRes[6] = EvtSpinType::VECTOR;
  _spinRes[7] = EvtSpinType::VECTOR;
  _spinRes[8] = EvtSpinType::VECTOR;
  _spinRes[9] = EvtSpinType::VECTOR;
  _spinRes[10] = EvtSpinType::SCALAR;
  _spinRes[11] = EvtSpinType::SCALAR;
  _spinRes[12] = EvtSpinType::SCALAR;
  _spinRes[13] = EvtSpinType::SCALAR;
  _spinRes[14] = EvtSpinType::TENSOR;
  _spinRes[15] = EvtSpinType::SCALAR;
  _spinRes[16] = EvtSpinType::SCALAR;
  _spinRes[17] = EvtSpinType::SCALAR;
  _spinRes[18] = EvtSpinType::TENSOR;

  _trackinfo[1] = EvtCyclic3::AC;
  _trackinfo[2] = EvtCyclic3::BC;
  _trackinfo[3] = EvtCyclic3::AB;
  _trackinfo[4] = EvtCyclic3::AC;
  _trackinfo[5] = EvtCyclic3::BC;
  _trackinfo[6] = EvtCyclic3::AB;
  _trackinfo[7] = EvtCyclic3::AC;
  _trackinfo[8] = EvtCyclic3::BC;
  _trackinfo[9] = EvtCyclic3::AB;
  _trackinfo[10] = EvtCyclic3::AB;
  _trackinfo[11] = EvtCyclic3::AB;
  _trackinfo[12] = EvtCyclic3::AB;
  _trackinfo[13] = EvtCyclic3::AB;
  _trackinfo[14] = EvtCyclic3::AB;
  _trackinfo[15] = EvtCyclic3::AB;
  _trackinfo[16] = EvtCyclic3::AB;
  _trackinfo[17] = EvtCyclic3::BC;
  _trackinfo[18] = EvtCyclic3::AB;

  //put all RooRealVar into the observable list
  //We only float the amplitude and phase
  //For the time-dependent fit, this should be modified
  //Now readin the initial values from isobar_whatever.txt
  RooArgSet parameters;
  for (int dummy=1;dummy<=nRes;dummy++)
    {
      parameters.add(*_gammRes[dummy]);
      parameters.add(*_massRes[dummy]);
      parameters.add(*_ampRes[dummy]);
      parameters.add(*_phaseRes[dummy]);
    }

  string configname;
  if(_Asign == 1) configname = name + "isobar_3pi_A.txt";
  else configname = name + "isobar_3pi_Abar.txt";
  parameters.readFromFile(configname.c_str());

  //define the list of observables(which is our floating parameters)
  _obs_list = new RooArgList();
  for (int dummy=1;dummy<=nRes;dummy++)
    {
      //cout << "Now adding " << _nameRes[dummy] << endl;
      _obs_list->add(*_phaseRes[dummy]); 
      _obs_list->add(*_ampRes[dummy]);
      if(dummy < 17){
      _obs_list->add(*_gammRes[dummy]);
      _obs_list->add(*_massRes[dummy]);
      }
     }
  //end the initalization
}

//This returns our Form Factor
//In most of the case, we return relativistic Breit-Wigner
EvtComplex RooIsobar3Pi::ResAmp(const double m13, const double m23, const int i) const
{
  //retrieve the informations about the resonance
  const EvtPto3PAmp::NumType res_Type = _typeRes[i];
  if (res_Type == EvtPto3PAmp::NONRES) return one;

  const double res_Mass = _massRes[i]->getVal();
  const EvtSpinType::spintype res_Spin  = _spinRes[i];
  const EvtCyclic3::Pair res_Pair  = _trackinfo[i];

  EvtCyclic3::Pair hel_Pair  = EvtCyclic3::next( res_Pair );
  if(res_Pair == EvtCyclic3::AC) hel_Pair  = EvtCyclic3::prev( res_Pair );

  const double m12 = getm12(m13,m23);
  const EvtDalitzPoint _dalitzPoint(mA,mB,mC,m12,m23,m13);

  const double res_gamma_running = runningWidth(_dalitzPoint.q(res_Pair),i);
  const EvtPropBreitWignerRel evtProp(res_Mass,res_gamma_running);
  EvtPto3PAmp amplitude(*_dalitzSpace,hel_Pair,res_Pair,res_Spin,evtProp,res_Type);

  //set the Blatt factor
  amplitude.set_fd(1.5);
  amplitude.set_fb(5.0);

  return amplitude.evaluate(_dalitzPoint);
}

double RooIsobar3Pi::runningWidth(const double s, const int i) const
{
  const double width = _gammRes[i]->getVal();
  const double mass2  = pow(_massRes[i]->getVal(),2);
  const EvtCyclic3::Pair res_Pair  = _trackinfo[i];
  double _m1 = 0., _m2 = 0.;

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
  const double k_s  = pionCMmom(s,_m1,_m2);
  const double k_m0 = pionCMmom(mass2,_m1,_m2);

  const EvtBlattWeisskopf fr(1,1.5,mass2);
  return width * sqrt(mass2/s) * pow( k_s/k_m0, EvtSpinType::getSpinStates(_spinRes[i])) * pow( (fr)(s), 2);
}

EvtComplex RooIsobar3Pi::efficiency(const double mAC, const double mBC) const
{
  const double mAB = getm12(mAC,mBC);

  //return 0 if it is in the Kspi0 bin
  if(mAB > 0.23309 && mAB < 0.26269) return zero;

  //need cos12 and mAB to determine efficiency
  const double cos12 = _dalitzSpace->cosTh(EvtCyclic3::AC,mAC,EvtCyclic3::AB,mAB);
  //const double cos12 = _dalitzSpace->cosTh(EvtCyclic3::AB,mAB,EvtCyclic3::AC,mAC);

  static const double m12min = _dalitzSpace->qAbsMin(EvtCyclic3::AB);
  static const double m12max = _dalitzSpace->qAbsMax(EvtCyclic3::AB);
  static const double dm12 = (m12max-m12min)/_ndiv_eff;

  for(int i=0;i<_ndiv_eff;i++){
    if(floor((mAB-m12min)/dm12) == i){
      const double n0 = _n0[i]->getVal();
      const double n1 = _n1[i]->getVal();
      const double c1 = _c1[i]->getVal();
      const double c2 = _c2[i]->getVal();
      const double c3 = _c3[i]->getVal();
      const double c4 = _c4[i]->getVal();
      const double c5 = _c5[i]->getVal();
      const double eff = 0.5*(n1/n0)*(1. + c1*cos12 + c2*(3.*pow(cos12,2.)-1.) + c3*(5.*pow(cos12,3.)-3.*cos12) + c4*(35.*pow(cos12,4.)-30.*pow(cos12,2.)+3.) + c5*(63.*pow(cos12,5.)-70.*pow(cos12,3.)+15.*cos12));
      return EvtComplex(sqrt(eff),0.);
    }
  }
  assert(0);
  return zero;
}

void RooIsobar3Pi::readefficiency()
{
  RooRealVar n0("n0","n0",1.);
  RooRealVar n1("n1","n1",1.);
  RooRealVar c1("c1","c1",0.);
  RooRealVar c2("c2","c2",0.);
  RooRealVar c3("c3","c3",0.);
  RooRealVar c4("c4","c4",0.);
  RooRealVar c5("c5","c5",0.);
  RooArgSet varlist;
  varlist.add(n0);
  varlist.add(n1);
  varlist.add(c1);
  varlist.add(c2);
  varlist.add(c3);
  varlist.add(c4);
  varlist.add(c5);

  for(int i=0;i<_ndiv_eff;i++){

    char map[100];
    sprintf(map,"effmap_%d.txt",i);
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

void RooIsobar3Pi::helicityangle(RooDataSet *data) const
{
  RooRealVar *cos12 = new RooRealVar("cos12","cos12",-1,1);
  RooRealVar *cos13 = new RooRealVar("cos13","cos13",-1,1);
  RooRealVar *cos23 = new RooRealVar("cos23","cos23",-1,1);
  RooDataSet *data2 = new RooDataSet("data2","data2",RooArgSet(*cos12,*cos13,*cos23));

  for(int i=0;i<data->numEntries();i++ ){

    const RooArgSet* row = data->get(i);
    RooRealVar* mass12 =(RooRealVar*) row->find("m2_12_d0mass");   //recall! mass12 is the peaking one!
    RooRealVar* mass13 =(RooRealVar*) row->find("m2_13_d0mass");

    const double m13=mass13->getVal();   //good, m13 is peaking
    const double m12=mass12->getVal();
    double cFromM(0.);

    for(int n=1;n<=3;n++) {

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

double RooIsobar3Pi::pionCMmom(const double s, const double m1, const double m2) const
{
  const double rad1 = 1. - pow(m1 + m2,2)/s;
  const double rad2 = 1. - pow(m1 - m2,2)/s;

  const double betakin1 = (rad1 > 0.) ? sqrt( rad1 ) : 1.;
  const double betakin2 = (rad2 > 0.) ? sqrt( rad2 ) : 1.;

  return 0.5*sqrt(s)*betakin1*betakin2;
}

//return true if within kinematic Dalitz region
bool RooIsobar3Pi::inDalitz(const double mass13, const double mass23) const
{
  const double mass12 = getm12(mass13,mass23);

  const double e2star = (mass12 - mA*mA + mB*mB) / (2.0*sqrt(mass12));
  const double e3star = (MD0*MD0 - mass12 - mC*mC  ) / (2.0*sqrt(mass12));

  if (e2star < mB || e3star < mC) return kFALSE;

  // kinematic limits
  const double m23Max = pow( e2star + e3star, 2 ) - pow( sqrt(e2star*e2star - mB*mB) - sqrt(e3star*e3star - mC*mC), 2 );
  const double m23Min = pow( e2star + e3star, 2 ) - pow( sqrt(e2star*e2star - mB*mB) + sqrt(e3star*e3star - mC*mC), 2 );

  if ( mass23 < m23Max && mass23 > m23Min) return kTRUE;
  return kFALSE;
}
