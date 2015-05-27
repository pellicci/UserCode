 /****************************************************************************
 * Package: CharmDalitzFit                                                   *
 *    File: $Id: RooPoly.cc,v 1.3 2008/06/10 17:08:26 pellicci Exp $         * 
 * Authors:                                                                  *
 *   MP, Mario Pelliccioni, Univ Torino, pellicci@slac.stanford.edu
 *****************************************************************************/
          
#include <iostream>
#include <math.h>
#include "CharmDalitzFit/RooPoly.hh"

#include "RooFitCore/RooAbsReal.hh"

using namespace std;

ClassImp(RooPoly)

// constructor
RooPoly::RooPoly(const char *name, const char *title, RooAbsReal& _m12, RooAbsReal& _m13,
  RooAbsReal& _a1, RooAbsReal& _a2, RooAbsReal& _a3,
  RooAbsReal& _a4, RooAbsReal& _a5, RooAbsReal& _a6,
  RooAbsReal& _a7, RooAbsReal& _a8, RooAbsReal& _a9):
  RooAbsPdf(name,title),
  m12("m12","Invariant Mass square of M12",this,_m12),
  m13("m13","Invariant Mass square of M13",this,_m13),
  a1("a1","a1",this,_a1),
  a2("a2","a2",this,_a2),
  a3("a3","a3",this,_a3),
  a4("a4","a4",this,_a4),  
  a5("a5","a5",this,_a5),
  a6("a6","a6",this,_a6),
  a7("a7","a7",this,_a7),
  a8("a8","a8",this,_a8),
  a9("a9","a9",this,_a9)
{
}

//Copy Constructor

RooPoly::RooPoly(const RooPoly& other, const char* name) :
  RooAbsPdf(other,name),
  m12("m12",this,other.m12),
  m13("m13",this,other.m13),
  a1("a1",this,other.a1),
  a2("a2",this,other.a2),
  a3("a3",this,other.a3),
  a4("a4",this,other.a4),
  a5("a5",this,other.a5),
  a6("a6",this,other.a6),
  a7("a7",this,other.a7),
  a8("a8",this,other.a8),
  a9("a9",this,other.a9)
{
}

Double_t RooPoly::evaluate() const
{
  if (inDalitz(m12,m13)) {
    //    return pdf(_m12,_m13);

 return 1.0+a1*m12+a2*m13+a3*m12*m12+a4*m13*m13+a5*m12*m13
   +a6*m12*m12*m12+a7*m13*m13*m13+a8*m12*m13*m13+a9*m12*m12*m13;
  }
  else {
    return pow(10.,-10);
  }
}

//Function to check if the events are inside the physical dalitz region
Bool_t RooPoly::inDalitz(Double_t mass12, Double_t mass13) const
{
  const Double_t M = 1.8645;
  const Double_t m1 = 0.493677;
  const Double_t m2 = 0.13957018;
  const Double_t m3 = 0.1349766;

  //return true if within kinematic Dalitz region
  const Double_t e2star = (mass12 - m1*m1 + m2*m2) / (2.0*sqrt(mass12));
  const Double_t e3star = (M*M - mass12 - m3*m3  ) / (2.0*sqrt(mass12));

  if (e2star < m2) return kFALSE;
  if (e3star < m3) return kFALSE;

  // kinematic limits
  const Double_t m23Max = pow( e2star + e3star, 2 ) 
    - pow( sqrt(e2star*e2star - m2*m2) - sqrt(e3star*e3star - m3*m3), 2 );

  const Double_t m23Min = pow( e2star + e3star, 2 ) 
    - pow( sqrt(e2star*e2star - m2*m2) + sqrt(e3star*e3star - m3*m3), 2 );
  
  // Now determine the min and max of m13 using momentum and energy relationship:
  const Double_t m13Min = M*M + m1*m1 + m2*m2 + m3*m3 - mass12 - m23Max;
  const Double_t m13Max =  M*M + m1*m1 + m2*m2 + m3*m3 - mass12 - m23Min;

  // decide
  if ( (mass13 > m13Min) && (mass13 < m13Max)) return kTRUE;
  return kFALSE;
}

