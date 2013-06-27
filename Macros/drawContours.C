#include <iostream>
#include <ctype.h>
 
#include <BaBarStyle.h>
 
#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TH3F.h>
 
#include <RooRealVar.h>
#include <RooCategory.h>
#include <RooDataSet.h>
#include <RooArgSet.h>
#include <RooFormulaVar.h>
#include <RooAddPdf.h>
#include <RooPlot.h>
#include <RooFitResult.h>
#include <RooGlobalFunc.h>
#include <RooGaussModel.h>
#include <RooTruthModel.h>
#include <RooAddModel.h>
#include <RooNumIntConfig.h>
#include <RooRandom.h>
#include <RooCBShape.h>
#include <RooProdPdf.h>
#include <RooSimultaneous.h>
#include <RooHistPdf.h>
#include <RooUnblindOffset.h>

#include <EvtGenBase/EvtDalitzPlot.hh>
#include <EvtGenBase/EvtDecayMode.hh>
#include <EvtGenBase/EvtPDL.hh>
 
#include <CharmDalitzFit/RooTimepdf.hh>

using namespace::RooFit;

int main(int argc, char* argv[])
{
  string name;
  char *filename;
  Double_t c1val = 0., c2val = 0.;

  for(Int_t i=1;i<argc;i++){
    char *pchar = argv[i];

    switch(pchar[0]){

    case '-':{

      switch(pchar[1]){
      case 'n':
        name = argv[i+1];
        cout << "Name of the configuration key " << name << endl;
        break;

      case 'f':
        filename = argv[i+1];
        cout << "File name used in this toy " << filename << endl;
        break;

      case 'y':
        c1val = atof(argv[i+1]);
        cout << "The c1 value is " << c1val << endl;
        break;

      case 'x':
        c2val = atof(argv[i+1]);
        cout << "The c2 values is " << c2val << endl;
        break;

      }
    }
    }
  }

  BaBarStyle p;
  p.SetBaBarStyle();

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  RooRealVar tau("tau","tau",0.4099);
  RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
  RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
  RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",-2.,4.);
  RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",0.0000001,0.5);
  RooCategory D0flav("D0flav","D0flav");
  D0flav.defineType("D0",-1);
  D0flav.defineType("antiD0",1);


  RooRealVar scalefact1("scalefact1","scalefact1",3.20);
  RooRealVar scalefact2("scalefact2","scalefact2",1.42);
  RooRealVar scalefact3("scalefact3","scalefact3",0.94);

  RooRealVar c1("c1","c1",c1val);
  RooRealVar c2("c2","c2",c2val);

  TFile fWS("dataR18/DataSet_out_tmp.root");
  gROOT->cd();
  RooDataSet *data = (RooDataSet*)fWS.Get("fulldata");
  RooDataSet *data_clean = (RooDataSet*)data->reduce("d0LifetimeErr < 0.5 && d0Lifetime > -2. && d0Lifetime < 4. && deltaMass > 0.1449 && deltaMass < 0.1459");
  RooDataSet *dataWS_2 = (RooDataSet*)data_clean->reduce("isWS == 1");
  RooDataSet *dataWS = (RooDataSet*)dataWS_2->reduce("d0Mass > 1.8495 && d0Mass < 1.8795");
  RooDataSet *RSdata = (RooDataSet*)data_clean->reduce("isWS == 0 && d0Mass > 1.8495 && d0Mass < 1.8795");

  Double_t low12,hig12,low13,hig13,low23,hig23;
  Bool_t m12bool = dataWS->getRange(m2Kpi_d0mass,low12,hig12);
  Bool_t m13bool = dataWS->getRange(m2Kpi0_d0mass,low13,hig13);
  m2Kpi_d0mass.setRange(low12,hig12);
  m2Kpi0_d0mass.setRange(low13,hig13);

  m2Kpi_d0mass.setBins(10);
  m2Kpi0_d0mass.setBins(10);
  d0Lifetime.setBins(8);
  d0LifetimeErr.setBins(10);

  //Construct signal pdf
  RooRealVar bias("bias","bias",0.0047) ;
  RooRealVar one("one","one",1.);

  //consider the resolution or the truth model
  RooGaussModel gm1("gm1","gauss model 1",d0Lifetime,bias,d0LifetimeErr,one,scalefact1) ;
  RooGaussModel gm2("gm2","gauss model 2",d0Lifetime,bias,d0LifetimeErr,one,scalefact2) ;
  RooGaussModel gm3("gm3","gauss model 3",d0Lifetime,bias,d0LifetimeErr,one,scalefact3) ;

  RooRealVar N1("N1","N1",0.0052);
  RooRealVar N2("N2","N2",0.179);

  RooFormulaVar f2("f2","f2","(1-@0)*@1",RooArgList(N1,N2));
  RooFormulaVar f3("f3","f3","(1-@0)*(1-@1)",RooArgList(N1,N2));
  RooAddModel gm("gm","gm",RooArgList(gm2,gm3,gm1),RooArgList(f2,f3));

  string dirname = "configmaps/effmapping_" + name + "/";

  RooTimepdf TOTsigD0("TOTsigD0","TOTsigD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,c1,c2,-1,dirname);
  //RooTimepdf TOTsigantiD0("TOTsigantiD0","TOTsigantiD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,c1_unblind,c2_unblind,1);
 
  //RooSimultaneous TOTTime("TOTTime","TOTTime",D0flav);
  //TOTTime.addPdf(TOTsigD0,"D0");
  //TOTTime.addPdf(TOTsigantiD0,"antiD0");

  //////////////////////////
  // BACKGROUND
  /////////////////////////

  //Mistag parametrization
  m2Kpi_d0mass.setBins(150);
  m2Kpi0_d0mass.setBins(150);
  d0Lifetime.setBins(70);

  TH3F *mis_h = m2Kpi_d0mass.createHistogram("mis_h",m2Kpi0_d0mass,d0Lifetime,"");
  RSdata->fillHistogram(mis_h,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime));
  mis_h->Sumw2();
  RooDataHist *mis_hist = new RooDataHist("mis_hist","mis_hist",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),mis_h);
  RooHistPdf Tot_mis("Tot_mis","Tot_mis",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),*mis_hist);

  m2Kpi_d0mass.setBins(10);
  m2Kpi0_d0mass.setBins(10);
  d0Lifetime.setBins(8);
  d0LifetimeErr.setBins(10);

  RooArgSet observ(d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass);
  RooArgSet tot_var(d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,d0LifetimeErr);

  //combinatoric
  RooDataSet *leftdata = (RooDataSet*)dataWS_2->reduce("d0Mass > 1.75 && d0Mass < 1.77");
  RooDataSet *rightdata = (RooDataSet*)dataWS_2->reduce("d0Mass > 1.95 && d0Mass < 1.97");
  RooDataSet *bkgdata = (RooDataSet*)dataWS_2->reduce("d0Mass > 1.95 || d0Mass < 1.77");
  rightdata->setWeightVar(0);
  leftdata->setWeightVar(0);

  TH3F *lefth = m2Kpi_d0mass.createHistogram("lefth",m2Kpi0_d0mass,d0Lifetime,"");
  leftdata->fillHistogram(lefth,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime));
  TH3F *righth = m2Kpi_d0mass.createHistogram("righth",m2Kpi0_d0mass,d0Lifetime,"");
  rightdata->fillHistogram(righth,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime));
  righth->Scale(lefth->Integral()/righth->Integral());
  lefth->Sumw2();
  righth->Sumw2();
  lefth->Add(righth);
  lefth->Sumw2();

  RooDataHist *lefthist = new RooDataHist("lefthist","lefthist",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),lefth);
  RooHistPdf Tot_comb("Tot_comb","Tot_comb",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),*lefthist);

  RooRealVar Nsig("Nsig","Nsig",1508.);
  RooRealVar Nmis("Nmis","Nmis",791.);
  RooRealVar Ncomb("Ncomb","Ncomb",(663. + 47.));

  d0LifetimeErr.setBins(100);
  RooDataSet *ProtoData_err = (RooDataSet*)RSdata->reduce(RooArgSet(d0LifetimeErr));
  TH1F *err_sig_h = (TH1F*)d0LifetimeErr.createHistogram("err_sig_h");
  ProtoData_err->fillHistogram(err_sig_h,RooArgSet(d0LifetimeErr));
  RooDataHist terr_sig("terr_sig","terr_sig",RooArgSet(d0LifetimeErr),err_sig_h);
  RooHistPdf terr_sig_pdf("terr_sig_pdf","terr_sig_pdf",RooArgSet(d0LifetimeErr),terr_sig,3);
  d0LifetimeErr.setBins(10);

  RooDataSet *ProtoData_bkg = (RooDataSet*)bkgdata->reduce(RooArgSet(d0LifetimeErr));
  TH1F *err_bkg_h = (TH1F*)d0LifetimeErr.createHistogram("err_bkg_h");
  ProtoData_bkg->fillHistogram(err_bkg_h,RooArgSet(d0LifetimeErr));
  err_bkg_h->Scale(err_sig_h->Integral()/err_bkg_h->Integral());
  RooDataHist terr_bkg("terr_bkg","terr_bkg",RooArgSet(d0LifetimeErr),err_bkg_h);
  RooHistPdf terr_bkg_pdf("terr_bkg_pdf","terr_bkg_pdf",RooArgSet(d0LifetimeErr),terr_bkg,3);

  RooProdPdf totsig_norm("totsig_norm","totsig_norm",RooArgSet(terr_sig_pdf),Conditional(TOTsigD0,observ));
  RooProdPdf totmis_norm("totmis_norm","totmis_norm",RooArgSet(terr_sig_pdf),Conditional(Tot_mis,observ));
  RooProdPdf totbkg_norm("totbkg_norm","totbkg_norm",RooArgSet(terr_bkg_pdf),Conditional(Tot_comb,observ));

  //Signal + background
  RooAddPdf TOTpdf("TOTpdf","TOTpdf",RooArgList(totsig_norm,totmis_norm,totbkg_norm),RooArgList(Nsig,Nmis,Ncomb));

  RooFitResult *theRes = TOTpdf.fitTo(*dataWS,Save(1),Minos(0),Extended(0));

  ofstream ofs(filename);
  if (ofs.fail()){
    cout << "Error opening file " << endl;
    assert(0);
  }
  ofs << c1.getVal() << " " << c2.getVal() << " " << theRes->minNll() << endl;

  return 0;
}
