#ifndef BABARSTYLE_H
#define BABARSTYLE_H

#include "TROOT.h"

class BaBarStyle
{
 public:
  BaBarStyle();
  void SetBaBarStyle();
  void SetBaBarLabel(Double_t xpos=0.9, Double_t ypos=0.9, Double_t scale=1.0, TString str="null", Double_t scale2=0.5, TString align="R");

 private:
  void BABARLabel(Double_t xpos, Double_t ypos, Double_t scale);

};

#endif
