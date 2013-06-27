#include <iostream>

#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TProfile2D.h>
#include <TPaveText.h>

#include <RooRealVar.h>
#include <RooCategory.h>
#include <RooDataSet.h>
#include <RooArgSet.h>
#include <RooFormulaVar.h>
#include <RooAddPdf.h>
#include <RooPlot.h>
#include <RooFitResult.h>
#include <RooGlobalFunc.h>
#include <RooDataHist.h>
#include <RooGaussModel.h>
#include <RooTruthModel.h>
#include <RooAddModel.h>
#include <RooNumIntConfig.h>
#include <RooChi2Var.h>
#include <RooMinuit.h>
#include <RooHist.h>
#include <RooHistPdf.h>

#include <EvtGenBase/EvtDalitzPlot.hh>
#include <EvtGenBase/EvtDecayMode.hh>
#include <EvtGenBase/EvtPDL.hh>

#include <CharmDalitzFit/RooKpipi0pdf.hh>

using namespace::RooFit;

int main(){

  gROOT->SetStyle("Plain");

  Bool_t doNorm = kFALSE;

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
  RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
  RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::BC),dalitzSpace.qAbsMax(EvtCyclic3::BC));

  //this is just to plot the m23 pdf
  Float_t total = pow(dalitzSpace.bigM(),2) + pow(dalitzSpace.mA(),2) + pow(dalitzSpace.mB(),2) + pow(dalitzSpace.mC(),2);
  RooRealVar totalm("totalm","totalm",total);
  RooFormulaVar mass13a("mass13a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2pipi0_d0mass));
  RooFormulaVar mass23a("mass23a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2Kpi0_d0mass));

  //Construct signal pdf
  string dirname = "configmaps/effmapping_RS_gene_part/";

  RooKpipi0pdf *D0pdf = new RooKpipi0pdf("D0pdf","D0pdf",m2Kpi_d0mass,m2Kpi0_d0mass,&dalitzSpace,dirname,1);
  RooKpipi0pdf *D0pdf23 = new RooKpipi0pdf("D0pdf23","D0pdf23",m2Kpi_d0mass,mass13a,&dalitzSpace,dirname,1);

  if(doNorm) D0pdf->getManager()->calNorm();

  //When we plot the 1D projection, need to calculate the 1D integral
  //set the precision here
  //cout << "config integrator " << endl;
  RooNumIntConfig *cfg = RooAbsReal::defaultIntegratorConfig();
  cfg->setEpsAbs(1E-3);
  cfg->setEpsRel(1E-3);
  cfg->method1D().setLabel("RooSegmentedIntegrator1D");
  //cfg.getConfigSection("RooSegmentedIntegrator1D").setRealValue("numSeg",3);
  //cfg->method1D()->Print("v");
  D0pdf->setIntegratorConfig(*cfg);
  D0pdf23->setIntegratorConfig(*cfg);

  cout << "about to init" << endl;

  m2Kpi_d0mass.setBins(150);
  m2Kpi0_d0mass.setBins(150);
  m2pipi0_d0mass.setBins(150);

  RooDataSet *gendata = D0pdf->generate(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),50000);
  gendata->addColumn(mass23a);

  RooDataSet *gendata23 = D0pdf23->generate(RooArgSet(m2Kpi_d0mass,m2pipi0_d0mass),50000);

    RooPlot* xframe = m2Kpi_d0mass.frame();
    gendata->plotOn(xframe,MarkerSize(0.1),DrawOption("z"));
    xframe->SetTitle("");
    xframe->GetXaxis()->SetTitle("s_{12} [GeV^{2}/c^{4}]");
    xframe->GetYaxis()->SetTitle("Events/4 MeV^{2}/c^{4}");

    RooPlot* yframe = m2Kpi0_d0mass.frame();
    gendata->plotOn(yframe,MarkerSize(0.1),DrawOption("z"));
    yframe->SetTitle("");
    yframe->GetXaxis()->SetTitle("s_{13} [GeV^{2}/c^{4}]");
    yframe->GetYaxis()->SetTitle("Events/5 MeV^{2}/c^{4}");

   RooPlot* zframe = m2pipi0_d0mass.frame();
   gendata23->plotOn(zframe,MarkerSize(0.1),DrawOption("z"));
   zframe->SetTitle("");
   zframe->GetXaxis()->SetTitle("s_{23} [GeV^{2}/c^{4}]");
   zframe->GetYaxis()->SetTitle("Events/5 MeV^{2}/c^{4}");

    TCanvas *c1 = new TCanvas("c1","residuals",1200,400);
    c1->Divide(3,1);
    c1->cd(1);xframe->Draw();
    c1->cd(2);yframe->Draw();
    c1->cd(3);zframe->Draw();
    c1->SaveAs("RSgeneration.gif");

    TFile *f = new TFile("RSgeneration.root","RECREATE");
    f->cd();
    gendata->tree().Write();
    f->Close();

  return 0;
}//end of the macro
