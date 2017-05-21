#include <TStyle.h>
#include <myKpipi0.h>
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <TVector3.h>
#include "TCanvas.h"
#include "TGraph.h"
#include <TLorentzVector.h>
#include <TLorentzRotation.h>
#include <TH1.h>
#include <TH2F.h>
#include <TF1.h>
#include <fstream>
#include <stdio.h>
#include <TROOT.h>
#include <Riostream.h>
#include <TProfile.h>
#include <BaBarStyle.h>

const Float_t lumi1005 = 1330346000./(1.3*pow(10.,6.));
const Float_t lumi1235 = 605400000./(1.05*0.5*pow(10.,6.));
const Float_t lumi1237 = 611262000./(1.05*0.5*pow(10.,6.));
const Float_t lumi998 = 852414000./((0.35 + 1.39 + 0.35)*pow(10.,6.));
const Float_t lumi3429 = 242810000./((0.94)*pow(10.,6.));

myKpipi0::myKpipi0(TTree *tree) : Kpipi0Base(tree) {
  nentries = Int_t(fChain->GetEntriesFast());
  nb = 0;
  nbytes = 0;

  frac = 1.;
}

void myKpipi0::HistoDef(){
  RecoTree = new TTree("reco","The Reconstruction Tree");

  deltamRS = new TH1F("deltamRS","deltamRS",700,0.138,0.155);
  deltamWS = new TH1F("deltamWS","deltamWS",200,0.138,0.155);
  mD0RS = new TH1F("mD0RS","mD0RS",700,1.74,1.98);
  mD0WS = new TH1F("mD0WS","mD0WS",200,1.74,1.98);
  lifeErrRS = new TH1F("lifeErrRS","lifeErrRS",700,0.,2.);
  lifeErrWS = new TH1F("lifeErrWS","lifeErrWS",200,0.,2.);

  m2Kpi_RS = new TH1F("m2Kpi_RS","m2Kpi_RS",150,0.3,3.1);
  m2Kpi0_RS = new TH1F("m2Kpi0_RS","m2Kpi0_RS",150,0.3,3.1);
  m2pipi0_RS = new TH1F("m2pipi0_RS","m2pipi0_RS",150,0.1,2.);
  t_RS = new TH1F("t_RS","t_RS",150,-2.,4.);

  //only fill them if is MC
  lifeErrRSbkg = new TH1F("lifeErrRSbkg","lifeErrRSbkg",700,0.,2.);
  lifeErrWSbkg = new TH1F("lifeErrWSbkg","lifeErrWSbkg",200,0.,2.);

  deltamRSbkg1005 = new TH1F("deltamRSbkg1005","deltamRSbkg1005",700,0.138,0.155);
  deltamWSbkg1005 = new TH1F("deltamWSbkg1005","deltamWSbkg1005",200,0.138,0.155);
  mD0RSbkg1005 = new TH1F("mD0RSbkg1005","mD0RSbkg1005",700,1.74,1.98);
  mD0WSbkg1005 = new TH1F("mD0WSbkg1005","mD0WSbkg1005",200,1.74,1.98);

  deltamRSbkg1235 = new TH1F("deltamRSbkg1235","deltamRSbkg1235",700,0.138,0.155);
  deltamWSbkg1235 = new TH1F("deltamWSbkg1235","deltamWSbkg1235",200,0.138,0.155);
  mD0RSbkg1235 = new TH1F("mD0RSbkg1235","mD0RSbkg1235",700,1.74,1.98);
  mD0WSbkg1235 = new TH1F("mD0WSbkg1235","mD0WSbkg1235",200,1.74,1.98);

  deltamRSbkg1237 = new TH1F("deltamRSbkg1237","deltamRSbkg1237",700,0.138,0.155);
  deltamWSbkg1237 = new TH1F("deltamWSbkg1237","deltamWSbkg1237",200,0.138,0.155);
  mD0RSbkg1237 = new TH1F("mD0RSbkg1237","mD0RSbkg1237",700,1.74,1.98);
  mD0WSbkg1237 = new TH1F("mD0WSbkg1237","mD0WSbkg1237",200,1.74,1.98);

  deltamRSbkg998 = new TH1F("deltamRSbkg998","deltamRSbkg998",700,0.138,0.155);
  deltamWSbkg998 = new TH1F("deltamWSbkg998","deltamWSbkg998",200,0.138,0.155);
  mD0RSbkg998 = new TH1F("mD0RSbkg998","mD0RSbkg998",700,1.74,1.98);
  mD0WSbkg998 = new TH1F("mD0WSbkg998","mD0WSbkg998",200,1.74,1.98);

  deltamRSbkg3429 = new TH1F("deltamRSbkg3429","deltamRSbkg3429",700,0.138,0.155);
  deltamWSbkg3429 = new TH1F("deltamWSbkg3429","deltamWSbkg3429",200,0.138,0.155);
  mD0RSbkg3429 = new TH1F("mD0RSbkg3429","mD0RSbkg3429",700,1.74,1.98);
  mD0WSbkg3429 = new TH1F("mD0WSbkg3429","mD0WSbkg3429",200,1.74,1.98);

  deltammisRS = new TH1F("deltammisRS","deltammisRS",700,0.138,0.155);
  deltammisWS = new TH1F("deltammisWS","deltammisWS",200,0.138,0.155);
  mD0misRS = new TH1F("mD0misRS","mD0misRS",700,1.74,1.98);
  mD0misWS = new TH1F("mD0misWS","mD0misWS",200,1.74,1.98);

  deltamcombRS = new TH1F("deltamcombRS","deltamcombRS",700,0.138,0.155);
  deltamcombWS = new TH1F("deltamcombWS","deltamcombWS",200,0.138,0.155);
  mD0combRS = new TH1F("mD0combRS","mD0combRS",700,1.74,1.98);
  mD0combWS = new TH1F("mD0combWS","mD0combWS",200,1.74,1.98);

  deltambadRS = new TH1F("deltambadRS","deltambadRS",700,0.138,0.155);
  deltambadWS = new TH1F("deltambadWS","deltambadWS",200,0.138,0.155);
  mD0badRS = new TH1F("mD0badRS","mD0badRS",700,1.74,1.98);
  mD0badWS = new TH1F("mD0badWS","mD0badWS",200,1.74,1.98);

  mdmBADWS = new TH2F("mdmBADWS","mdmBADWS",40,1.74,1.98,40,0.13923,0.155);
  mdmBADRS = new TH2F("mdmBADRS","mdmBADRS",40,1.74,1.98,40,0.13923,0.155);

  m2Kpi_leftRS = new TH1F("m2Kpi_leftRS","m2Kpi_leftRS",150,0.3,3.1);
  m2Kpi0_leftRS = new TH1F("m2Kpi0_leftRS","m2Kpi0_leftRS",150,0.3,3.1);
  m2pipi0_leftRS = new TH1F("m2pipi0_leftRS","m2pipi0_leftRS",150,0.1,2.);
  m2Kpi_rightRS = new TH1F("m2Kpi_rightRS","m2Kpi_rightRS",150,0.3,3.1);
  m2Kpi0_rightRS = new TH1F("m2Kpi0_rightRS","m2Kpi0_rightRS",150,0.3,3.1);
  m2pipi0_rightRS = new TH1F("m2pipi0_rightRS","m2pipi0_rightRS",150,0.1,2.);

  m2Kpi_sigregRS = new TH1F("m2Kpi_sigregRS","m2Kpi_sigregRS",150,0.3,3.1);
  m2Kpi0_sigregRS = new TH1F("m2Kpi0_sigregRS","m2Kpi0_sigregRS",150,0.3,3.1);
  m2pipi0_sigregRS = new TH1F("m2pipi0_sigregRS","m2pipi0_sigregRS",150,0.1,2.);

  m2Kpi_leftWS = new TH1F("m2Kpi_leftWS","m2Kpi_leftWS",150,0.3,3.1);
  m2Kpi0_leftWS = new TH1F("m2Kpi0_leftWS","m2Kpi0_leftWS",150,0.3,3.1);
  m2pipi0_leftWS = new TH1F("m2pipi0_leftWS","m2pipi0_leftWS",150,0.1,2.);
  m2Kpi_rightWS = new TH1F("m2Kpi_rightWS","m2Kpi_rightWS",150,0.3,3.1);
  m2Kpi0_rightWS = new TH1F("m2Kpi0_rightWS","m2Kpi0_rightWS",150,0.3,3.1);
  m2pipi0_rightWS = new TH1F("m2pipi0_rightWS","m2pipi0_rightWS",150,0.1,2.);

  m2Kpi_sigregWS = new TH1F("m2Kpi_sigregWS","m2Kpi_sigregWS",150,0.3,3.1);
  m2Kpi0_sigregWS = new TH1F("m2Kpi0_sigregWS","m2Kpi0_sigregWS",150,0.3,3.1);
  m2pipi0_sigregWS = new TH1F("m2pipi0_sigregWS","m2pipi0_sigregWS",150,0.1,2.);

  m2Kpi_misWS = new TH1F("m2Kpi_misWS","m2Kpi_misWS",150,0.3,3.1);
  m2Kpi0_misWS = new TH1F("m2Kpi0_misWS","m2Kpi0_misWS",150,0.3,3.1);
  m2pipi0_misWS = new TH1F("m2pipi0_misWS","m2pipi0_misWS",150,0.1,2.);
  t_misWS = new TH1F("t_misWS","t_misWS",150,-2.,4.);

  for(Int_t i=0;i<5;i++){
    char left12[100];
    sprintf(left12,"m2Kpi_leftWS_%d",i);
    char left13[100];
    sprintf(left13,"m2Kpi0_leftWS_%d",i);
    char left23[100];
    sprintf(left23,"m2pipi0_leftWS_%d",i);

    char right12[100];
    sprintf(right12,"m2Kpi_rightWS_%d",i);
    char right13[100];
    sprintf(right13,"m2Kpi0_rightWS_%d",i);
    char right23[100];
    sprintf(right23,"m2pipi0_rightWS_%d",i);

    char sigreg12[100];
    sprintf(sigreg12,"m2Kpi_sigregWS_%d",i);
    char sigreg13[100];
    sprintf(sigreg13,"m2Kpi0_sigregWS_%d",i);
    char sigreg23[100];
    sprintf(sigreg23,"m2pipi0_sigregWS_%d",i);

  part_m2Kpi_leftWS[i] = new TH1F(left12,left12,150,0.3,3.1);
  part_m2Kpi0_leftWS[i] = new TH1F(left13,left13,150,0.3,3.1);
  part_m2pipi0_leftWS[i] = new TH1F(left23,left23,150,0.1,2.);
  part_m2Kpi_rightWS[i] = new TH1F(right12,right12,150,0.3,3.1);
  part_m2Kpi0_rightWS[i] = new TH1F(right13,right13,150,0.3,3.1);
  part_m2pipi0_rightWS[i] = new TH1F(right23,right23,150,0.1,2.);

  part_m2Kpi_sigregWS[i] = new TH1F(sigreg12,sigreg12,150,0.3,3.1);
  part_m2Kpi0_sigregWS[i] = new TH1F(sigreg13,sigreg13,150,0.3,3.1);
  part_m2pipi0_sigregWS[i] = new TH1F(sigreg23,sigreg23,150,0.1,2.);
  }

  lifeErr_leftRS = new TH1F("lifeErr_leftRS","lifeErr_leftRS",200,0.,0.5);
  lifeErr_rightRS = new TH1F("lifeErr_rightRS","lifeErr_rightRS",200,0.,0.5);
  lifeErr_sigregRS = new TH1F("lifeErr_sigregRS","lifeErr_sigregRS",200,0.,0.5);

  lifeErr_leftWS = new TH1F("lifeErr_leftWS","lifeErr_leftWS",200,0.,0.5);
  lifeErr_rightWS = new TH1F("lifeErr_rightWS","lifeErr_rightWS",200,0.,0.5);
  lifeErr_sigregWS = new TH1F("lifeErr_sigregWS","lifeErr_sigregWS",200,0.,0.5);

  t_leftRS = new TH1F("t_leftRS","t_leftRS",80,-2.,4.);
  t_rightRS = new TH1F("t_rightRS","t_rightRS",80,-2.,4.);
  t_sigregRS = new TH1F("t_sigregRS","t_sigregRS",80,-2.,4.);

  t_leftWS = new TH1F("t_leftWS","t_leftWS",80,-2.,4.);
  t_rightWS = new TH1F("t_rightWS","t_rightWS",80,-2.,4.);
  t_sigregWS = new TH1F("t_sigregWS","t_sigregWS",80,-2.,4.);

  swapRS = new TH1F("swapRS","swapRS",50,0.,3.);
  swapWS = new TH1F("swapWS","swapWS",50,0.,3.);

  p_K = new TH1F("p_K","p_K",50,0.,4.);
  p_pi = new TH1F("p_pi","p_pi",50,0.,4.);
  p_pis = new TH1F("p_pis","p_pis",50,0.,1.);
}

void myKpipi0::HistoFill(){
  RecoTree->Fill();

  if(!isMC || (isMC && truthIsSignal)){
    if(!isWS){
      deltamRS->Fill(deltaMass);
      mD0RS->Fill(d0Mass);
      swapRS->Fill(mass_swap());
      if(deltaMass > 0.1449 && deltaMass < 0.1459)
	if(d0Mass > 1.8495 && d0Mass < 1.8795) lifeErrRS->Fill(d0LifetimeErr);
      p_K->Fill(kPmag);
      p_pi->Fill(piPmag);
      p_pis->Fill(pisoft_mom);
    }
    else if(isWS){
      deltamWS->Fill(deltaMass);
      mD0WS->Fill(d0Mass);
      swapWS->Fill(mass_swap());
      if(deltaMass > 0.1449 && deltaMass < 0.1459)
	if(d0Mass > 1.8495 && d0Mass < 1.8795) lifeErrWS->Fill(d0LifetimeErr); 
    }
  }

  else if(isMC && !truthIsSignal){

    if(!isWS){
      if(!truthIsBkg_FakePiSlow && !truthIsBkg_BadOtherD0 && !truthIsBkg_BadSignalD0){
	deltamcombRS->Fill(deltaMass,frac);
	mD0combRS->Fill(d0Mass,frac);
      }
      else if(truthIsBkg_BadOtherD0 || truthIsBkg_BadSignalD0){
        deltambadRS->Fill(deltaMass,frac);
        mD0badRS->Fill(d0Mass,frac);
	mdmBADRS->Fill(d0Mass,deltaMass);
      }
      else if(truthIsBkg_FakePiSlow){
        deltammisRS->Fill(deltaMass,frac);
        mD0misRS->Fill(d0Mass,frac);
      }

      if(isccbar){ 
	deltamRSbkg1005->Fill(deltaMass);
	mD0RSbkg1005->Fill(d0Mass);
      }
      else if(isbpbm){
	deltamRSbkg1235->Fill(deltaMass);
	mD0RSbkg1235->Fill(d0Mass);
      }
      else if(isbzbzb){
	deltamRSbkg1237->Fill(deltaMass);
        mD0RSbkg1237->Fill(d0Mass);
      }
      else if(isuds){
	deltamRSbkg998->Fill(deltaMass);
	mD0RSbkg998->Fill(d0Mass);
      }
      else if(istautau){
	deltamRSbkg3429->Fill(deltaMass);
	mD0RSbkg3429->Fill(d0Mass);
      }
      else assert(0);

      if(deltaMass > 0.1449 && deltaMass < 0.1459)
	if(d0Mass > 1.8495 && d0Mass < 1.8795) lifeErrRSbkg->Fill(d0LifetimeErr,frac);
    }

    else if(isWS){

      if(!truthIsBkg_SwappedKpi && !truthIsBkg_FakePiSlow){
        deltamcombWS->Fill(deltaMass,frac);
        mD0combWS->Fill(d0Mass,frac);
      }
      else if(truthIsBkg_SwappedKpi){
        deltambadWS->Fill(deltaMass,frac);
        mD0badWS->Fill(d0Mass,frac);
	mdmBADWS->Fill(d0Mass,deltaMass);
      }
      else if(truthIsBkg_FakePiSlow){
       deltammisWS->Fill(deltaMass,frac);
        mD0misWS->Fill(d0Mass,frac);
      }

      if(isccbar){ 
	deltamWSbkg1005->Fill(deltaMass);
	mD0WSbkg1005->Fill(d0Mass);
      }
      else if(isbpbm){
	deltamWSbkg1235->Fill(deltaMass);
	mD0WSbkg1235->Fill(d0Mass);
      }
      else if(isbzbzb){
	deltamWSbkg1237->Fill(deltaMass);
        mD0WSbkg1237->Fill(d0Mass);
      }
      else if(isuds){
	deltamWSbkg998->Fill(deltaMass);
	mD0WSbkg998->Fill(d0Mass);
      }
      else if(istautau){
	deltamWSbkg3429->Fill(deltaMass);
	mD0WSbkg3429->Fill(d0Mass);
      }
      else assert(0);
      if(deltaMass > 0.1449 && deltaMass < 0.1459)
	if(d0Mass > 1.8495 && d0Mass < 1.8795) lifeErrWSbkg->Fill(d0LifetimeErr,frac);
    }
  }
  else assert(0);  //if it is not MC nor data, what else??

  if(deltaMass > 0.1449 && deltaMass < 0.1459 && d0LifetimeErr < 0.5){
    if(!isWS){
      if(d0Mass > 1.76 && d0Mass < 1.77){
	m2Kpi_leftRS->Fill(m2Kpi_d0mass,frac);
	m2Kpi0_leftRS->Fill(m2Kpi0_d0mass,frac);
	m2pipi0_leftRS->Fill(m2pipi0_d0mass,frac);
        t_leftRS->Fill(d0Lifetime,frac);
        lifeErr_leftRS->Fill(d0LifetimeErr,frac);
     }
      if(d0Mass > 1.96 && d0Mass < 1.97){
	m2Kpi_rightRS->Fill(m2Kpi_d0mass,frac);
	m2Kpi0_rightRS->Fill(m2Kpi0_d0mass,frac);
	m2pipi0_rightRS->Fill(m2pipi0_d0mass,frac);
        t_rightRS->Fill(d0Lifetime,frac);
        lifeErr_rightRS->Fill(d0LifetimeErr,frac);
     }
      if(d0Mass > 1.8495 && d0Mass < 1.8795 && !truthIsSignal && !truthIsBkg_FakePiSlow){
	m2Kpi_sigregRS->Fill(m2Kpi_d0mass,frac);
	m2Kpi0_sigregRS->Fill(m2Kpi0_d0mass,frac);
	m2pipi0_sigregRS->Fill(m2pipi0_d0mass,frac);
        t_sigregRS->Fill(d0Lifetime,frac);
        lifeErr_sigregRS->Fill(d0LifetimeErr,frac);
      }
      if(d0Mass > 1.8495 && d0Mass < 1.8795){
	m2Kpi_RS->Fill(m2Kpi_d0mass,frac);
	m2Kpi0_RS->Fill(m2Kpi0_d0mass,frac);
	m2pipi0_RS->Fill(m2pipi0_d0mass,frac);
	t_RS->Fill(d0Lifetime,frac);
      }
    }
    else{
	Int_t i = 0;
	if(d0Lifetime < 0.2 && d0Lifetime > 0.) i=1;
	if(d0Lifetime < 0.4 && d0Lifetime > 0.2) i=2;
	if(d0Lifetime < 0.8 && d0Lifetime > 0.4) i=3;
	if(d0Lifetime > 0.8) i=4;

      if(d0Mass > 1.76 && d0Mass < 1.77){
	part_m2Kpi_leftWS[i]->Fill(m2Kpi_d0mass,frac);
	part_m2Kpi0_leftWS[i]->Fill(m2Kpi0_d0mass,frac);
	part_m2pipi0_leftWS[i]->Fill(m2pipi0_d0mass,frac);
	m2Kpi_leftWS->Fill(m2Kpi_d0mass,frac);
	m2Kpi0_leftWS->Fill(m2Kpi0_d0mass,frac);
	m2pipi0_leftWS->Fill(m2pipi0_d0mass,frac);
	t_leftWS->Fill(d0Lifetime,frac);
 	lifeErr_leftWS->Fill(d0LifetimeErr,frac);
     }
      if(d0Mass > 1.96 && d0Mass < 1.97){
        part_m2Kpi_rightWS[i]->Fill(m2Kpi_d0mass,frac);
	part_m2Kpi0_rightWS[i]->Fill(m2Kpi0_d0mass,frac);
	part_m2pipi0_rightWS[i]->Fill(m2pipi0_d0mass,frac);
        m2Kpi_rightWS->Fill(m2Kpi_d0mass,frac);
	m2Kpi0_rightWS->Fill(m2Kpi0_d0mass,frac);
	m2pipi0_rightWS->Fill(m2pipi0_d0mass,frac);
	t_rightWS->Fill(d0Lifetime,frac);
 	lifeErr_rightWS->Fill(d0LifetimeErr,frac);
     }
      if(d0Mass > 1.8495 && d0Mass < 1.8795 && !truthIsSignal && !truthIsBkg_FakePiSlow){
	part_m2Kpi_sigregWS[i]->Fill(m2Kpi_d0mass,frac);
	part_m2Kpi0_sigregWS[i]->Fill(m2Kpi0_d0mass,frac);
	part_m2pipi0_sigregWS[i]->Fill(m2pipi0_d0mass,frac);
	m2Kpi_sigregWS->Fill(m2Kpi_d0mass,frac);
	m2Kpi0_sigregWS->Fill(m2Kpi0_d0mass,frac);
	m2pipi0_sigregWS->Fill(m2pipi0_d0mass,frac);
	t_sigregWS->Fill(d0Lifetime,frac);
	lifeErr_sigregWS->Fill(d0LifetimeErr,frac);
      }
     if(d0Mass > 1.8495 && d0Mass < 1.8795 && truthIsBkg_FakePiSlow){
        m2Kpi_misWS->Fill(m2Kpi_d0mass,frac);
      m2Kpi0_misWS->Fill(m2Kpi0_d0mass,frac);
       m2pipi0_misWS->Fill(m2pipi0_d0mass,frac);
       t_misWS->Fill(d0Lifetime,frac);
      }
    }
  }
}

myKpipi0::~myKpipi0() {
  if(!fChain) return;
  //  delete fChain->GetCurrentFile();
}

void myKpipi0::HistoWrite() 
{
  TFile *_file = new TFile("dstar_out.root","RECREATE");
  _file->cd();
  RecoTree->Write();

  deltamRS->Write();
  deltamWS->Write();
  mD0RS->Write();
  mD0WS->Write();
  lifeErrRS->Write();
  lifeErrWS->Write();
  swapRS->Write();
  swapWS->Write();

  m2Kpi_RS->Write();
  m2Kpi0_RS->Write();
  m2pipi0_RS->Write();
  t_RS->Write();

  p_K->Write();
  p_pi->Write();
  p_pis->Write();

  if(isMC){
  deltamRSbkg1005->Write();
  deltamRSbkg1235->Write();
  deltamRSbkg1237->Write();
  deltamRSbkg998->Write();
  deltamRSbkg3429->Write();
  deltamWSbkg1005->Write();
  deltamWSbkg1235->Write();
  deltamWSbkg1237->Write();
  deltamWSbkg998->Write();
  deltamWSbkg3429->Write();

  mD0RSbkg1005->Write();
  mD0RSbkg1235->Write();
  mD0RSbkg1237->Write();
  mD0RSbkg998->Write();
  mD0RSbkg3429->Write();
  mD0WSbkg1005->Write();
  mD0WSbkg1235->Write();
  mD0WSbkg1237->Write();
  mD0WSbkg998->Write();
  mD0WSbkg3429->Write();

  lifeErrRSbkg->Write();
  lifeErrWSbkg->Write();

  deltamcombRS->Write();
  mD0combRS->Write();
  deltambadRS->Write();
  mD0badRS->Write();
  deltammisRS->Write();
  mD0misRS->Write();

  deltamcombWS->Write();
  mD0combWS->Write();
  deltambadWS->Write();
  mD0badWS->Write();
  deltammisWS->Write();
  mD0misWS->Write();

  m2Kpi_sigregRS->Write();
  m2Kpi0_sigregRS->Write();
  m2pipi0_sigregRS->Write();
  t_sigregRS->Write();

  for(Int_t i=0;i<5;i++){
  part_m2Kpi_sigregWS[i]->Write();
  part_m2Kpi0_sigregWS[i]->Write();
  part_m2pipi0_sigregWS[i]->Write();
  }

  m2Kpi_sigregWS->Write();
  m2Kpi0_sigregWS->Write();
  m2pipi0_sigregWS->Write();
  t_sigregWS->Write();
  lifeErr_sigregRS->Write();
  lifeErr_sigregWS->Write();

  m2Kpi_misWS->Write();
  m2Kpi0_misWS->Write();
  m2pipi0_misWS->Write();
  t_misWS->Write();
  }

  m2Kpi_leftRS->Write();
  m2Kpi0_leftRS->Write();
  m2pipi0_leftRS->Write();
  m2Kpi_rightRS->Write();
  m2Kpi0_rightRS->Write();
  m2pipi0_rightRS->Write();

  for(Int_t i=0;i<5;i++){
  part_m2Kpi_leftWS[i]->Write();
  part_m2Kpi0_leftWS[i]->Write();
  part_m2pipi0_leftWS[i]->Write();
  part_m2Kpi_rightWS[i]->Write();
  part_m2Kpi0_rightWS[i]->Write();
  part_m2pipi0_rightWS[i]->Write();
}
  t_leftRS->Write();
  t_rightRS->Write();
  t_leftWS->Write();
  t_rightWS->Write();

  lifeErr_leftRS->Write();
  lifeErr_rightRS->Write();
  lifeErr_leftWS->Write();
  lifeErr_rightWS->Write();

  _file->Close();

  if(isMC){
  TFile f_fit("dstar_forfit.root","RECREATE");
  f_fit.cd();
  mdmBADRS->Write();
  mdmBADWS->Write();
  f_fit.Close();
  }

  return;
}

void myKpipi0::Loop()
{
  cout << "Starting the Loop() method" << endl;

  BaBarStyle p;
  //p.SetBaBarStyle();
  if (fChain == 0) return;
  HistoDef();

  Float_t signal[4][20][20][20];
  Float_t backcc[4][20][20][20];
  Float_t backbzbz[4][20][20][20];
  Float_t backbpbm[4][20][20][20];
  Float_t backtautau[4][20][20][20];
  Float_t backuds[4][20][20][20];
  Float_t cut1[20];
  Float_t cut2[20];
  Float_t cut3[20];
  Float_t cutgraph[20];
  Float_t sgraph[20];

  Float_t ssquared = 0.;
  Float_t cut1_max[4];
  Float_t cut2_max[4];
  Float_t cut3_max[4];
  Float_t signifi_max[4];

  for(Int_t i=0;i<4;i++){
    for(Int_t z=0;z<20;z++){
      for(Int_t g=0;g<20;g++){
	for(Int_t k=0;k<20;k++){
	  signal[i][z][g][k] = 0.;
	  backcc[i][z][g][k] = 0.;
	  backbzbz[i][z][g][k] = 0.;
	  backbpbm[i][z][g][k] = 0.;
	  backtautau[i][z][g][k] = 0.;
	  backuds[i][z][g][k] = 0.;
	}
      }
      cut1[z] = 0.;
      cut2[z] = 0.;
      cut3[z] = 0.;
      cutgraph[z] = 0.;
      sgraph[z] = 0.;
    }
    cut1_max[i] = 0.;
    cut2_max[i] = 0.;
    cut3_max[i] = 0.;
    signifi_max[i] = 0.;
  }

  Float_t Npass = 0.;
  Float_t Npass_sig = 0.;
  Float_t Npass_bkgcc = 0.;
  Float_t Npass_bkgbpbm = 0.;
  Float_t Npass_bkgbzbz = 0.;
  Float_t Npass_bkguds = 0.;
  Float_t Npass_bkgtautau = 0.;

  Float_t Nfake_pslow = 0.;
  Float_t Nbad_Dplus = 0.;
  Float_t Nswap_Kpi = 0.;
  Float_t Nbkg_generic = 0.;
  Float_t NbadD0sig = 0.;
  Float_t NbadD0other = 0.;
  Float_t Nfakepi = 0.;
  Float_t NfakeK = 0.;
  Float_t Nfakepi0 = 0.;

  for (Int_t jentry=0; jentry<nentries;jentry++){
    Int_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    GetEntry(jentry);

    checkMCbools();

    d0Lifetime *= pow(10.,12.);
    d0LifetimeErr *= pow(10.,12.);

    if(isMC && !isGoodEvent()) continue;
   //if(!tag_opp_side == 1) continue;

    HistoFill();
    if(deltaMass < 0.1449 || deltaMass > 0.1459) continue;
    if(d0Mass < 1.8495 || d0Mass > 1.8795) continue;
    if(d0LifetimeErr > 0.5) continue;

    Npass++;
    if(isMC && isWS){
      if(truthIsSignal) Npass_sig++;
      else{
	if(isccbar) Npass_bkgcc++;
	else if(isbpbm) Npass_bkgbpbm++;
	else if(isbzbzb) Npass_bkgbzbz++;
	else if(isuds) Npass_bkguds++;
	else if(istautau) Npass_bkgtautau++;
	else assert(0);

	if(truthIsBkg_FakePiSlow) Nfake_pslow += frac;
	else if(truthIsBkg_BadDplus) Nbad_Dplus += frac;
	else if(truthIsBkg_SwappedKpi) Nswap_Kpi += frac;
	else if(truthIsBkg_BadSignalD0) NbadD0sig += frac;
	else if(truthIsBkg_BadOtherD0) NbadD0other += frac;
	else if(truthHasMisIDKaon) NfakeK += frac;
	else if(truthHasMisIDPion) Nfakepi += frac;
	else Nbkg_generic += frac;

	if(isccbar && !truthHasMisIDKaon && !truthHasMisIDPion && !truthIsBkg_BadDplus && !truthIsBkg_FakePiSlow && !truthIsBkg_BadOtherD0 && truthIsBkg_BadSignalD0) Nfakepi0 += frac;
      }
    }

    /*
    //remember to comment isGoodEvent() when performing optimization!
    if(isMC && isWS){
      for(Int_t i=0;i<4;i++){
	for(Int_t k=0;k<20;k++){
	  cut1[k] = 0.30 + 0.025*k;
	  for(Int_t m=0;m<20;m++){
	    cut2[m] = 2.4 + 0.02*m;
	    for(Int_t g=0;g<20;g++){
	      cut3[g] = 0.35 + 0.005*g;
	      if(d0LifetimeErr < cut1[k] && d0pstar > cut2[m] && pi0Pmag > cut3[g]){
		if(i == 0 && !tag_k()) continue;
		if(i == 1 && !(tag_k() || tag_pi())) continue;
		if(i == 2 && !(tag_k() || tag_pi() || tag_e())) continue;
		if(i == 3 && !(tag_k() || tag_pi() || tag_e() || tag_mu())) continue;
		if(truthIsSignal) signal[i][k][m][g]++;
		else if(!truthIsSignal){
		  if(isccbar) backcc[i][k][m][g]++;
		  else if(isbpbm) backbpbm[i][k][m][g]++;
		  else if(isbzbzb) backbzbz[i][k][m][g]++;
		  else if(isuds) backuds[i][k][m][g]++;
		  else if(istautau) backtautau[i][k][m][g]++;
		  else assert(0);
		}
	      }
	    }
	  }
	}
      }      
    }//end of if(isMC && isWS)
    */

  }//end of loop over the events
  cout << "Finished looping over the events" << endl;

  HistoWrite();

  Int_t myk[4];
  Int_t mym[4];
  Int_t myg[4];

  /*
  if(isMC){
    cout << "Calculating statistical significance for the cuts" << endl;
    for(Int_t i=0;i<4;i++){
      for(Int_t k=0;k<20;k++){
	for(Int_t m=0;m<20;m++){
	  for(Int_t g=0;g<20;g++){
	    ssquared = signal[i][k][m][g]/sqrt(signal[i][k][m][g] + backcc[i][k][m][g] + backbzbz[i][k][m][g]*lumi1005/lumi1237 +  backbpbm[i][k][m][g]*lumi1005/lumi1235 + backuds[i][k][m][g]*lumi1005/lumi998 + backtautau[i][k][m][g]*lumi1005/lumi3429);
	    if(g==8 && m==10 && i==3)  sgraph[k] = ssquared;
	    cutgraph[k] = cut1[k];
	    if(ssquared > signifi_max[i]){
	      signifi_max[i] = ssquared;
	      cut1_max[i] = cut1[k];
	      cut2_max[i] = cut2[m];
	      cut3_max[i] = cut3[g];
	      myk[i] = k;
	      mym[i] = m;
	      myg[i] = g;
	    }
	  }
	}
      }
    }
  }

  TGraph *gr1 = new TGraph(20,cutgraph,sgraph);
  gr1->GetXaxis()->SetTitle("#sigma_t cut (GeV/c2)");
  gr1->GetYaxis()->SetTitle("stat. signif.");

  TCanvas tmp1;
  tmp1.cd();
  gr1->Draw("AC*");
  tmp1.Print("statsigcut.ps");
  */
  ssquared = Npass_sig/sqrt(Npass_sig + Npass_bkgcc + Npass_bkgbzbz*lumi1005/lumi1237 + Npass_bkgbpbm*lumi1005/lumi1235 + Npass_bkguds*lumi1005/lumi998 + Npass_bkgtautau*lumi1005/lumi3429);
 
  cout << "Number of total events " << Npass << endl;;
  cout << "Number of signal events " << Npass_sig << endl;;
  for(Int_t i=0;i<4;i++){
    cout << "################ Tag scenario number " << i << endl;
    cout << "sigma_t is " << cut1_max[i] << endl;
    cout << "pstar is " << cut2_max[i] << endl;
    cout << "pi0 p is " << cut3_max[i] << endl;
    //cout << "statistical significance  is " << signifi_max[i] << endl;
    cout << "statistical significance  is " << ssquared << endl;
    cout << "Signal efficiency " << signal[i][myk[i]][mym[i]][myg[i]]/Npass_sig;
    cout << "#################" << endl;
  }

  cout << "//////////////////////////" << endl;
  cout << "Events in background categories" << endl;
  cout << "//////////////////////////" << endl << endl;
  cout << "Number of fake slow pions = " << Nfake_pslow << endl;
  cout << "Number of Dplus candidates = " << Nbad_Dplus << endl;
  cout << "Number of swapped K-pi candidates = " << Nswap_Kpi << endl;
  cout << "Number of signal bad D0 = " << NbadD0sig << endl;
  cout << "Number of non-signal bad D0 = " << NbadD0other << endl;
  cout << "Number of fake pions = " << Nfakepi << endl;
  cout << "Number of fake kaons = " << NfakeK << endl;
  cout << "Number of fake pi0 = " << Nfakepi0 << endl;
  cout << "Number of generic background = " << Nbkg_generic << endl;

} //Loop method

inline Bool_t myKpipi0::tag_k() const
{
  if(tag_k_cms_p > 0.) return kTRUE;
  return kFALSE;
}

inline Bool_t myKpipi0::tag_pi() const
{
  if(tag_spi_pchi2 > 0.001 && tag_spi_dss_pt < 0.08 && tag_spi_dss_pl > -0.080 && tag_spi_dss_pl < 0.075 && tag_spi_dss_p < 0.09 && tag_spi_dss_p > 0.) return kTRUE;
  return kFALSE;
}

inline Bool_t myKpipi0::tag_e() const
{
  if(tag_e_m2 > 0.01 && tag_e_cms_p > 0.) return kTRUE;
  return kFALSE;
}

inline Bool_t myKpipi0::tag_mu() const
{
  if(tag_mu_cms_p > 0.) return kTRUE;
  return kFALSE;
}

inline Bool_t myKpipi0::isGoodEvent() const
{
  if(d0pstar > 2.4 && pi0Pmag > 0.35 && dstarChi2Prob > 0.01 && d0Chi2ProbPre > 0.005 && d0Lifetime > -2. && d0Lifetime < 4.) return kTRUE;
  return kFALSE;
}

void myKpipi0::checkMCbools()
{
  isccbar = kFALSE;
  isbpbm = kFALSE;
  isbzbzb = kFALSE;
  isuds = kFALSE;
  istautau = kFALSE;
  isMC = kTRUE;

  const char *filename = fChain->GetCurrentFile()->GetName();
  TString strfile(filename);
  if(strfile.Contains("1005")) isccbar = kTRUE;
  else if(strfile.Contains("1235")) isbpbm = kTRUE;
  else if(strfile.Contains("1237")) isbzbzb = kTRUE;
  else if(strfile.Contains("998")) isuds = kTRUE;
  else if(strfile.Contains("3429")) istautau = kTRUE;
  else if(!strfile.Contains("SP")) isMC = kFALSE;
  else assert(0); //all time of files checked, no reason to fail

  getFrac();
  return;
}

void myKpipi0::getFrac()
{
  frac = 1.;

  if(isbpbm) frac = lumi1005/lumi1235;
  else if(isbzbzb) frac = lumi1005/lumi1237;
  else if(isuds) frac = lumi1005/lumi998;
  else if(istautau) frac = lumi1005/lumi3429;
  return;
}

Float_t myKpipi0::mass_swap()
{
  Float_t newKE = sqrt(kE*kE - pow(0.493677,2.) + pow(0.13957018,2.));
  Float_t newPiE = sqrt(piE*piE + pow(0.493677,2.) - pow(0.13957018,2.));

  TLorentzVector newK(kPx,kPy,kPz,newKE);
  TLorentzVector newPi(piPx,piPy,piPz,newPiE);
  TLorentzVector pPi0(pi0Px,pi0Py,pi0Pz,pi0E);

  TLorentzVector newD0 = newK + newPi + pPi0;

  return newD0.M();
}
