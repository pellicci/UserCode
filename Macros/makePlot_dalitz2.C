#include <iostream>

#include <BaBarStyle.h>

#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TPaveLabel.h>

#include <RooRealVar.h>
#include <RooGlobalFunc.h>
#include <RooTruthModel.h>

#include <EvtGenBase/EvtDalitzPlot.hh>
#include <EvtGenBase/EvtDecayMode.hh>
#include <EvtGenBase/EvtPDL.hh>

#include <CharmDalitzFit/RooTimepdf.hh>

using namespace::RooFit;

int main(int argc, char* argv[])
{

  double thex(0.), they(0.);

  for(Int_t i=1;i<argc;i++){
    char *pchar = argv[i];

    switch(pchar[0]){

    case '-':{

      switch(pchar[1]){
      case 'x':
        thex = atof(argv[i+1]);
	cout << "x is set to " << thex << endl;
        break;

      case 'y':
        they = atof(argv[i+1]);
        cout <<"y is set to " << they<< endl;
        break;
      }
    }
    }
  }

  BaBarStyle p;
  p.SetBaBarStyle();
  gROOT->GetStyle("BABAR")->SetPalette(1);

  /*->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(10);
  gStyle->SetFrameFillColor(10);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetTitleColor(1);
  gStyle->SetStatColor(0);
  gStyle->SetOptStat(0);   // No stats by default
  gStyle->SetFillColor(0);
  gStyle->SetFuncWidth(1);
  gStyle->SetLineWidth(1);
  //gStyle->SetHistLineWidth(2);
  gStyle->SetLineColor(1);
  gStyle->SetPalette(1, 0);
  */

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  RooRealVar x("x", "x",0.,-0.5,0.5);
  RooRealVar y("y", "y",0.,-0.5,0.5);
  RooRealVar t("time", "t",0.,20.);
  RooRealVar tau("tau", "tau", 0.4101);

  RooTruthModel resolution("resolution", "Truth", t);
  x.setVal(thex);
  y.setVal(they);

  const Double_t m12_min = dalitzSpace.qAbsMin(EvtCyclic3::AB);
  const Double_t m12_max = dalitzSpace.qAbsMax(EvtCyclic3::AB);
  const Double_t m13_min = dalitzSpace.qAbsMin(EvtCyclic3::AC);
  const Double_t m13_max = dalitzSpace.qAbsMax(EvtCyclic3::AC);

  RooRealVar fit_S12("fit_S12","fit_S12",1.,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
  RooRealVar fit_S13("fit_S13","fit_S13",1.,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
  RooRealVar fit_S23("fit_S23","fit_S23",1.,dalitzSpace.qAbsMin(EvtCyclic3::BC),dalitzSpace.qAbsMax(EvtCyclic3::BC));
  fit_S23.setBins(360);
  fit_S13.setBins(360);
  fit_S12.setBins(360);

  RooRealVar qp("qp","qp",1.);
  RooRealVar phi("phi","phi",0.);

  string dirname = "configmaps/effmapping_plot/";

  RooTimepdf myDmix("myDmix","myDmix",t,fit_S12,fit_S13,resolution,&dalitzSpace,tau,x,y,-1,dirname);

  const Int_t numbins = 30;

  TH1D aver1D("aver1D","",60,0.3,0.5);

  TH2D entriesDalitz("entriesDalitz","",numbins,m12_min,m12_max,numbins,m13_min,m13_max);
  TH2D averageDalitz("averageDalitz", "",numbins,m12_min,m12_max,numbins,m13_min,m13_max);
  TH2D xdifflnDalitz("xdifflnDalitz", "",numbins,m12_min,m12_max,numbins,m13_min,m13_max);
  TH2D ydifflnDalitz("ydifflnDalitz", "",numbins,m12_min,m12_max,numbins,m13_min,m13_max);
  averageDalitz.SetStats(false);
  entriesDalitz.SetStats(false);
  xdifflnDalitz.SetStats(false);
  ydifflnDalitz.SetStats(false);

  double maxEnt = 0.;
  double minAvg = 100000.;
  double maxAvg = 0.;
  double coeffs[4];

  std::cout << "Filling histograms" << std::endl;
  TAxis* xaxis = averageDalitz.GetXaxis();
  TAxis* yaxis = averageDalitz.GetYaxis();
  for (int i = 1; i <= averageDalitz.GetNbinsX(); ++i) {
    for (int j = 1; j <= averageDalitz.GetNbinsY(); ++j) {

      const Double_t mym23 = pow(dalitzSpace.bigM(),2)+pow(dalitzSpace.mA(),2)+pow(dalitzSpace.mB(),2) + pow(dalitzSpace.mC(),2) - xaxis->GetBinCenter(i) - yaxis->GetBinCenter(j);
      EvtDalitzPoint dalitzPoint(dalitzSpace.mA(),dalitzSpace.mB(),dalitzSpace.mC(),xaxis->GetBinCenter(i),mym23,yaxis->GetBinCenter(i));
      if(!dalitzPoint.isValid()) continue;

      fit_S12.setVal(xaxis->GetBinCenter(j));
      fit_S13.setVal(yaxis->GetBinCenter(i));

      double ent = 0.;
      double avg = 0.;

      for (double time = 0.; time < 20.; time += 0.00005) {
	t.setVal(time);
	const double curr = myDmix.myevaluate();

	if (curr < 0.0000005) break; 

	ent += curr;
	avg += time*curr;
      }

      if (ent < 0.0000001) continue;
      if (ent > maxEnt) maxEnt = ent;
      avg /= ent;
      entriesDalitz.SetBinContent(i, j, ent);
      averageDalitz.SetBinContent(i, j, avg);
      aver1D.Fill(avg);
      //xdifflnDalitz.SetBinContent(i, j, xdiff/ent);
      //ydifflnDalitz.SetBinContent(i, j, ydiff/ent);
      minAvg = std::min(avg, minAvg);
      maxAvg = std::max(avg, maxAvg);
      std::cout << "(Average, integral) = (" << avg << ", " << ent << ")" << std::endl;
    }
  }

  std::cout << "Max weight: " << maxEnt << " " << minAvg << " " << maxAvg << std::endl;

  const int numHists = 7;
  double* bounds = new double[numHists];
  int* colours = new int[numHists];
  
  bounds[0] = 0.405;
  bounds[1] = 0.407;
  bounds[2] = 0.409;
  bounds[3] = 0.411;
  bounds[4] = 0.413;
  bounds[5] = 0.415;
  bounds[6] = 10000.;
  colours[0] = kRed + 100;
  colours[1] = kRed;
  colours[2] = kRed +150;
  colours[3] = kMagenta;
  colours[4] = kBlue +150;
  colours[5] = kBlue;
  colours[6] = kBlue + 100;

  maxEnt = entriesDalitz.GetMaximum();

  TH2D** hists = new TH2D*[numHists];
  char name[200];
  for (int i = 0; i < numHists; ++i) {
    sprintf(name, "blah%i", i);
    hists[i] = new TH2D(name, "", numbins, 0., 3., numbins, 0., 3.);
    hists[i]->GetZaxis()->SetRangeUser(0, maxEnt);
    if (0 == i) {
      sprintf(name, "Less than %.3f ps", bounds[i]);
    }
    else if (i == numHists-1) {
      sprintf(name, "Greater than %.3f ps", bounds[i-1]);
    }
    else {
      sprintf(name, "(%.3f - %.3f) ps", bounds[i-1], bounds[i]);
    }
    hists[i]->SetTitle(name); 
    hists[i]->SetStats(false);
    hists[i]->SetLineColor(colours[i]);
    hists[i]->SetFillColor(colours[i]);
    hists[i]->SetFillStyle(1001);
  }

  for (int i = 1; i <= averageDalitz.GetNbinsX(); ++i) {
    for (int j = 1; j <= averageDalitz.GetNbinsY(); ++j) {
      double ent = entriesDalitz.GetBinContent(i, j);
      if (ent < 0.0000000001) continue; 
      double avg = averageDalitz.GetBinContent(i, j);

      int index = 0;
      for (; index < numHists; index++) {
	if (avg < bounds[index]) break;
      }
      hists[index]->SetBinContent(i, j, ent);
    }
  }

  TLegend* leg = new TLegend(0.65, 0.7, 0.95, 0.95);
  hists[0]->SetTitle("");
  hists[0]->GetXaxis()->SetTitle("m^{2}_{K^{+}#pi^{-}} [GeV^{2}]");
  hists[0]->GetYaxis()->SetTitle("m^{2}_{K^{+}#pi^{0}} [GeV^{2}]");
  hists[0]->GetYaxis()->SetTitleOffset(1.3);

  TCanvas c1("c1","c1",500,500);
  //c1.Divide(2,1);
  c1.cd();
  hists[0]->Draw("box");
  hists[0]->SetLineWidth(4);
  leg->AddEntry(hists[0], "Less than 0.405 ps", "l");
  for (int i = 1; i < numHists; ++i) {
    hists[i]->Draw("boxsame");
    hists[i]->SetLineWidth(4);
    leg->AddEntry(hists[i], hists[i]->GetTitle(), "l");
  }
  leg->Draw();

  TPaveLabel p1(2.,1.6,2.7,2.,"c_{1} = 0 , c_{2} = 0");
  p1.Draw();
  /*
  c1.cd(2);c1.cd(2)->SetLogz(1);
  hists[0]->Draw("box");
  hists[0]->SetLineWidth(4);
  for (int i = 1; i < numHists; ++i) {
    hists[i]->Draw("boxsame");
    hists[i]->SetLineWidth(4);
  }
  leg->Draw();
  p1.Draw();
  */
  c1.SaveAs("colourDalitz.eps");

  aver1D.SetTitle("");
  aver1D.GetXaxis()->SetTitle("Average lifetime (ps)");

  TCanvas c2;
  c2.cd();aver1D.Draw();
  c2.SaveAs("averlife_1D.eps");

  TFile f("1dplot.root","RECREATE");
  f.cd();aver1D.Write();
  f.Close();

  return 0;

}
