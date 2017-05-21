#include <iostream>
#include <ctype.h>
 
#include <BaBarStyle.h>
 
#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TH3F.h>
#include <TPaveText.h>
#include <TStyle.h>

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

  for(Int_t i=1;i<argc;i++){
    char *pchar = argv[i];

    switch(pchar[0]){

    case '-':{

      switch(pchar[1]){
      case 'n':
        name = argv[i+1];
        cout << "Name of the configuration key " << name << endl;
        break;
      }
    }
    }
  }

  Bool_t doFit = kFALSE;
  Bool_t extract = kFALSE;
  Bool_t doFrac = kFALSE;
  Bool_t doPlots = kTRUE;
  Bool_t doChi2 = kFALSE;

  BaBarStyle p;
  p.SetBaBarStyle();
  gROOT->GetStyle("BABAR")->SetPalette(1);
  gROOT->GetStyle("BABAR")->SetPadTopMargin(0.04);
  gROOT->GetStyle("BABAR")->SetPadLeftMargin(0.17);
  gROOT->GetStyle("BABAR")->SetPadBottomMargin(0.19);
  gROOT->GetStyle("BABAR")->SetTitleSize(0.08,"xyz"); // set the 3 axes title size 

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  RooRealVar tau("tau","tau",0.4099);
  RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
  RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
  RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::BC),dalitzSpace.qAbsMax(EvtCyclic3::BC));
  RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",-2.,4.);
  RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",0.0000001,0.5);
  RooCategory D0flav("D0flav","D0flav");
  D0flav.defineType("D0",-1);
  D0flav.defineType("antiD0",1);

  RooRealVar scalefact1("scalefact1","scalefact1",3.20);
  RooRealVar scalefact2("scalefact2","scalefact2",1.42);
  RooRealVar scalefact3("scalefact3","scalefact3",0.94);

  RooRealVar c1("c1","c1",-2.,2.);
  RooRealVar c2("c2","c2",-2.,2.);
  RooUnblindOffset c1_unblind("c1_unblind","c1 (unblind)","VaffanculoS",1.,c1) ;
  RooUnblindOffset c2_unblind("c2_unblind","c2 (unblind)","VaffanculoS",1.,c2) ;

  TFile fWS("DataSet_out_tmp.root");
  gROOT->cd();
  RooDataSet *data = (RooDataSet*)fWS.Get("fulldata");
  RooDataSet *data_clean = (RooDataSet*)data->reduce("d0LifetimeErr < 0.5 && d0Lifetime > -2. && d0Lifetime < 4. && deltaMass > 0.1449 && deltaMass < 0.1459");
  RooDataSet *dataWS_2 = (RooDataSet*)data_clean->reduce("isWS == 1");
  RooDataSet *dataWS = (RooDataSet*)dataWS_2->reduce("d0Mass > 1.8495 && d0Mass < 1.8795");
  RooDataSet *RSdata = (RooDataSet*)data_clean->reduce("isWS == 0 && d0Mass > 1.8495 && d0Mass < 1.8795");

  Double_t low12,hig12,low13,hig13,low23,hig23;
  Bool_t m12bool = dataWS->getRange(m2Kpi_d0mass,low12,hig12);
  Bool_t m13bool = dataWS->getRange(m2Kpi0_d0mass,low13,hig13);
  Bool_t m23bool = dataWS->getRange(m2pipi0_d0mass,low23,hig23);
  m2Kpi_d0mass.setRange(low12,hig12);
  m2Kpi0_d0mass.setRange(low13,hig13);
  m2pipi0_d0mass.setRange(low23,hig23);

  m2Kpi_d0mass.setBins(10);
  m2Kpi0_d0mass.setBins(10);
  d0Lifetime.setBins(8);
  d0LifetimeErr.setBins(10);
  m2pipi0_d0mass.setBins(10);

  Float_t total = pow(dalitzSpace.bigM(),2) + pow(dalitzSpace.mA(),2) + pow(dalitzSpace.mB(),2) + pow(dalitzSpace.mC(),2);
  RooRealVar totalm("totalm","totalm",total);
  RooFormulaVar mass13a("mass13a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2pipi0_d0mass));

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

  RooTimepdf TOTsigD023("TOTsigD023","TOTsigD023",d0Lifetime,m2Kpi_d0mass,mass13a,gm,&dalitzSpace,tau,c1,c2,-1,dirname);

  //////////////////////////
  // BACKGROUND
  /////////////////////////

  //Mistag parametrization
  m2Kpi_d0mass.setBins(150);
  m2Kpi0_d0mass.setBins(150);
  m2pipi0_d0mass.setBins(150);
  d0Lifetime.setBins(70);

  TH3F *mis_h = m2Kpi_d0mass.createHistogram("mis_h",m2Kpi0_d0mass,d0Lifetime,"");
  RSdata->fillHistogram(mis_h,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime));
  mis_h->Sumw2();
  RooDataHist *mis_hist = new RooDataHist("mis_hist","mis_hist",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),mis_h);
  RooHistPdf Tot_mis("Tot_mis","Tot_mis",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),*mis_hist);

  TH3F *mis_h23 = m2Kpi_d0mass.createHistogram("mis_h",m2pipi0_d0mass,d0Lifetime,"");
  RSdata->fillHistogram(mis_h23,RooArgList(m2Kpi_d0mass,m2pipi0_d0mass,d0Lifetime));
  mis_h23->Sumw2();
  RooDataHist *mis_hist23 = new RooDataHist("mis_hist23","mis_hist23",RooArgList(m2Kpi_d0mass,m2pipi0_d0mass,d0Lifetime),mis_h23);
  RooHistPdf Tot_mis23("Tot_mis23","Tot_mis23",RooArgList(m2Kpi_d0mass,m2pipi0_d0mass,d0Lifetime),*mis_hist23);

  m2Kpi_d0mass.setBins(10);
  m2Kpi0_d0mass.setBins(10);
  m2pipi0_d0mass.setBins(10);
  d0Lifetime.setBins(8);
  d0LifetimeErr.setBins(10);

  RooArgSet observ(d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass);
  RooArgSet observ23(d0Lifetime,m2Kpi_d0mass,m2pipi0_d0mass);
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

  TH3F *lefth23 = m2Kpi_d0mass.createHistogram("lefth23",m2pipi0_d0mass,d0Lifetime,"");
  leftdata->fillHistogram(lefth23,RooArgList(m2Kpi_d0mass,m2pipi0_d0mass,d0Lifetime));
  TH3F *righth23 = m2Kpi_d0mass.createHistogram("righth23",m2pipi0_d0mass,d0Lifetime,"");
  rightdata->fillHistogram(righth23,RooArgList(m2Kpi_d0mass,m2pipi0_d0mass,d0Lifetime));
  righth23->Scale(lefth23->Integral()/righth23->Integral());
  lefth23->Sumw2();
  righth23->Sumw2();
  lefth23->Add(righth23);
  lefth23->Sumw2();
  RooDataHist *lefthist23 = new RooDataHist("lefthist23","lefthist23",RooArgList(m2Kpi_d0mass,m2pipi0_d0mass,d0Lifetime),lefth23);
  RooHistPdf Tot_comb23("Tot_comb23","Tot_comb23",RooArgList(m2Kpi_d0mass,m2pipi0_d0mass,d0Lifetime),*lefthist23);

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

  RooProdPdf totsig_norm23("totsig_norm23","totsig_norm23",RooArgSet(terr_sig_pdf),Conditional(TOTsigD023,observ23));
  RooProdPdf totmis_norm23("totmis_norm23","totmis_norm23",RooArgSet(terr_sig_pdf),Conditional(Tot_mis23,observ23));
  RooProdPdf totbkg_norm23("totbkg_norm23","totbkg_norm23",RooArgSet(terr_bkg_pdf),Conditional(Tot_comb23,observ23));

  //Signal + background
  RooAddPdf TOTpdf("TOTpdf","TOTpdf",RooArgList(totsig_norm,totmis_norm,totbkg_norm),RooArgList(Nsig,Nmis,Ncomb));
  RooAddPdf TOTpdf23("TOTpdf23","TOTpdf23",RooArgList(totsig_norm23,totmis_norm23,totbkg_norm23),RooArgList(Nsig,Nmis,Ncomb));

  if(doFit){

    RooFitResult *theRes = TOTpdf.fitTo(*dataWS,Save(1),Minos(0),Extended(0));

    string filename = "syst_root/fit_WS_" + name + ".root";
    TFile fout(filename.c_str(),"RECREATE");
    fout.cd();
    theRes->Write();
    fout.Close();
  }

  if(extract){
    TFile f("fitWS.root");
    RooFitResult* theRes = (RooFitResult*)f.Get("nll");
 
    RooRealVar myc1("myc1","myc1",-10.,10.);
    RooRealVar myc2("myc2","myc2",-10.,10.);
    RooRealVar myratio("myratio","myratio",0.,0.,1.);
    RooRealVar myx("myx","myx",0.,-1.,1.);
    RooRealVar myy("myy","myy",0.,-1.,1.);
 
    Double_t NrsNws = 2562./1132332.;
    Double_t ratioerr = sqrt(pow(89.,2.) + pow(NrsNws,2.)*pow(2862.,2.))/1132332.;
    RooDataSet *parFloat = new RooDataSet("parFloat","parFloat",RooArgList(myratio,myx,myy));
 
    for(Int_t j=0;j<400;j++){
      cout << "Performing step number " << j << endl;
      RooArgList floated = theRes->randomizePars();
      myc1.setVal(((RooAbsReal*)floated.find("c1"))->getVal());
      myc2.setVal(((RooAbsReal*)floated.find("c2"))->getVal());
 
      RooTimepdf mysigD0("mysigD0","mysigD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,myc1,myc2,-1,dirname);
      Double_t myDenom = mysigD0.createIntegral(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime))->getVal();
      Double_t myNum = RooRandom::randomGenerator()->Gaus(NrsNws,ratioerr);
 
      myratio.setVal(myNum/myDenom);
      myx.setVal(myc2.getVal()*sqrt((myNum/myDenom)));
      myy.setVal(myc1.getVal()*sqrt((myNum/myDenom)));
 
      parFloat->add(RooArgSet(myratio,myx,myy));
    }
 
    TFile *f1 = new TFile("fitWS_float.root","RECREATE");
    f1->cd();
    parFloat->Write();
    f1->Close();
  }

  if(doChi2){
 
    m2Kpi_d0mass.setBins(40);
    m2Kpi0_d0mass.setBins(40);
 
    RooDataSet *dterr_ds = (RooDataSet*)dataWS->reduce(RooArgSet(d0LifetimeErr));
 
    TH2F *dphist_data = (TH2F*)m2Kpi_d0mass.createHistogram("dphist_data",m2Kpi0_d0mass);
    dataWS->fillHistogram(dphist_data,RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass));
 
    RooDataSet *pdf_ds = (RooDataSet*)TOTpdf.generate(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),dataWS->numEntries(),RooFit::ProtoData(*dterr_ds,1));
    TH2F *dphist = (TH2F*)m2Kpi_d0mass.createHistogram("dphist",m2Kpi0_d0mass);
    pdf_ds->fillHistogram(dphist,RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass));
 
    Int_t binx = m2Kpi_d0mass.getBinning().numBins();
    Int_t biny = m2Kpi0_d0mass.getBinning().numBins();
    Double_t chi2 = 0.;
    Int_t myBins = 0;
    Int_t nBin = 1;
 
    TH2F *pull_dal = (TH2F*)m2Kpi_d0mass.createHistogram("pull_dal",m2Kpi0_d0mass);
 
    dphist->Sumw2();
    dphist->Scale(dphist_data->Integral()/dphist->Integral());
    dphist->Sumw2();
 
    for(Int_t i=0;i<binx*biny;i++){
 
      Double_t chi_tmp = (dphist->GetBinContent(i)-dphist_data->GetBinContent(i))/dphist->GetBinError(i);
      Double_t nEv = dphist_data->GetBinContent(i);
      if(nEv == 0.) chi_tmp = 0.;
      pull_dal->SetBinContent(i,chi_tmp);
 
      if(nBin > 1){
	nBin--;
	//Double_t chi_tmp = (dphist->GetBinContent(i)-dphist_data->GetBinContent(i))/dphist->GetBinError(i);
	//pull_dal->SetBinContent(i,chi_tmp);
	continue;
      }
 
      if(nEv == 0.) continue;
      Double_t ndata = dphist_data->GetBinContent(i);
      Double_t npdf = dphist->GetBinContent(i);
      Double_t err = dphist->GetBinError(i);
      myBins++;
 
      while(nEv < 9.){
	if(dphist_data->GetBinContent(i+nBin) == 0. || dphist->GetBinError(i+nBin) == 0.){
	  nBin++;
	  continue;
	}
	ndata += dphist_data->GetBinContent(i+nBin);
	npdf += dphist->GetBinContent(i+nBin);
	err += sqrt(pow(err,2.) + pow(dphist->GetBinError(i+nBin),2.));
	nEv += dphist_data->GetBinContent(i+nBin);
	nBin++;
      }
 
      chi2 += pow((ndata-npdf)/err,2.);
    }
 
    Double_t chi2_root = dphist_data->Chi2Test(dphist,"UW");
 
    cout << "chi2 = " << chi2 << endl;
    cout << "chi2/ndof = " << chi2/(myBins -1.) << endl;
    cout << "mybins = " << myBins << endl;
    cout << "chi2 for root = " << chi2_root << endl;
 
    dphist_data->Sumw2();
    dphist->Sumw2();
    dphist_data->Add(dphist,-1.);
    dphist_data->SetMaximum(15.);

    dphist_data->SetMinimum(-15.);

    TCanvas c;
    c.Divide(1,2);
    c.cd(1);dphist_data->Draw("COLZ");
    c.cd(2);pull_dal->Draw("COLZ");
    c.SaveAs("WScomparison.eps");
    TFile fp("prova.root","RECREATE");
    dphist_data->Write();
    pull_dal->Write();
    fp.Close();
  }

  if(doPlots){
 
    m2Kpi_d0mass.setBins(20);
    m2Kpi0_d0mass.setBins(20);
    m2pipi0_d0mass.setBins(20);
    d0Lifetime.setBins(70);
 
    RooDataHist *dshist = new RooDataHist("dshist","dshist",RooArgSet(d0LifetimeErr),*dataWS);

    TH2F *lefth_t = m2Kpi_d0mass.createHistogram("lefth_t",m2Kpi0_d0mass);
    leftdata->fillHistogram(lefth_t,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));
    TH2F *righth_t = m2Kpi_d0mass.createHistogram("righth_t",m2Kpi0_d0mass);
    rightdata->fillHistogram(righth_t,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));
    righth_t->Scale(lefth_t->Integral()/righth_t->Integral());
    lefth_t->Sumw2();
    righth_t->Sumw2();
    lefth_t->Add(righth);
    lefth_t->Sumw2();
    TH1F *left_t = (TH1F*)d0Lifetime.createHistogram("left_t");
    leftdata->fillHistogram(left_t,RooArgList(d0Lifetime));
    TH1F *right_t = (TH1F*)d0Lifetime.createHistogram("right_t");
    rightdata->fillHistogram(right_t,RooArgList(d0Lifetime));
    right_t->Scale(left_t->Integral()/right_t->Integral());
    left_t->Sumw2();
    right_t->Sumw2();
    left_t->Add(right_t);
    left_t->Sumw2();
 
    RooDataHist *lefthist_d = new RooDataHist("lefthist_d","lefthist_d",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass),lefth_t);
    RooDataHist *lefthist_t = new RooDataHist("lefthist_t","lefthist_t",RooArgList(d0Lifetime),left_t);
    RooHistPdf left_plot("left_plot","left_plot",RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),*lefthist_d,6);
    RooHistPdf left_t_plot("left_t_plot","left_t_plot",RooArgSet(d0Lifetime),*lefthist_t,6);
 
    RooProdPdf tot_plot("tot_plot","tot_plot",left_plot,left_t_plot);
 
    RooProdPdf totbkg_norm_plot("totbkg_norm_plot","totbkg_norm_plot",RooArgSet(terr_bkg_pdf),Conditional(tot_plot,observ));
    RooAddPdf TOTpdf_plot("TOTpdf_plot","TOTpdf_plot",RooArgList(totsig_norm,totmis_norm,totbkg_norm_plot),RooArgList(Nsig,Nmis,Ncomb));

    RooPlot* tframe = d0Lifetime.frame();
    dataWS->plotOn(tframe,MarkerSize(0.1),DrawOption("z"));
    //TOTpdf.plotOn(tframe,Project(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass,d0LifetimeErr)),ProjWData(*dshist));
    TOTpdf_plot.plotOn(tframe);
    Double_t chi2t = tframe->chiSquare();
    TOTpdf_plot.plotOn(tframe,Components(RooArgSet(totmis_norm,totbkg_norm_plot)),DrawOption("F"),FillColor(kBlue));       //FillColor(17));
    TOTpdf_plot.plotOn(tframe,Components(RooArgSet(totbkg_norm_plot)),DrawOption("F"),FillColor(kRed));                       //FillColor(14));
    tframe->getAttLine()->SetLineWidth(1);
    tframe->getAttLine()->SetLineStyle(1);
    tframe->SetTitle("");
    tframe->GetXaxis()->SetTitle("t_{K^{+}#pi^{-}#pi^{0}} [ps]");
    tframe->GetYaxis()->SetTitle("Events/0.08 ps");

    TPaveText *boxt = new TPaveText(2.5,2.5,2.7,2.7,"");
    boxt->AddText("(d)");
    boxt->SetFillColor(10);

    cout << "Chi2 for t = " << chi2t << endl;
    TCanvas ct("t","t",300,300);
    ct.cd();tframe->Draw();boxt->Draw("SAME");
    ct.SaveAs("WSfit_t.eps");

    //When we plot the 1D projection, need to calculate the 1D integral
    //set the precision here
    //cout << "config integrator " << endl;
    RooNumIntConfig *cfg = RooAbsReal::defaultIntegratorConfig();
    cfg->setEpsAbs(1E-5);
    cfg->setEpsRel(1E-5);
    cfg->method1D().setLabel("RooSegmentedIntegrator1D");
    //cfg.getConfigSection("RooSegmentedIntegrator1D").setRealValue("numSeg",3);
    //cfg->method1D()->Print("v");
    TOTsigD0.setIntegratorConfig(*cfg);
    //TOTsigantiD0.setIntegratorConfig(*cfg);
    TOTsigD023.setIntegratorConfig(*cfg);
    //TOTsigantiD023.setIntegratorConfig(*cfg);

    RooPlot* xframe = m2Kpi_d0mass.frame(53);  //was 19
    dataWS->plotOn(xframe,MarkerSize(0.1),DrawOption("z"));
    TOTpdf.plotOn(xframe,Project(RooArgSet(m2Kpi0_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist));
    xframe->getAttLine()->SetLineWidth(1);
    xframe->getAttLine()->SetLineStyle(1);
    xframe->SetTitle("");
    xframe->GetXaxis()->SetTitle("m^{2}_{K^{+}#pi^{-}}  [GeV^{2}/c^{4}]");
    xframe->GetYaxis()->SetTitle("Events/0.05 GeV^{2}/c^{4}");
    Double_t chi2Kpi = xframe->chiSquare();
    TOTpdf.plotOn(xframe,Project(RooArgSet(m2Kpi0_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist),Components(RooArgSet(totmis_norm,totbkg_norm)),DrawOption("F"),FillColor(kBlue)); //FillColor(17));
    TOTpdf.plotOn(xframe,Project(RooArgSet(m2Kpi0_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist),Components(RooArgSet(totbkg_norm)),DrawOption("F"),FillColor(kRed)); //FillColor(14));
    dataWS->plotOn(xframe,MarkerSize(0.1),DrawOption("z"));

    xframe->GetYaxis()->SetTitleOffset(1.3);

    TPaveText *box_m12 = new TPaveText(2.5,2.5,2.7,2.7,"");
    box_m12->AddText("(b)");
    box_m12->SetFillColor(10);

    TCanvas c1("c1","c1",300,300);
    c1.cd();xframe->Draw();box_m12->Draw("SAME");
    c1.SaveAs("WSfit_m2Kpi.eps");

    m2Kpi0_d0mass.setBins(50);

    RooPlot* yframe = m2Kpi0_d0mass.frame(49);
    dataWS->plotOn(yframe,MarkerSize(0.1),DrawOption("z"));
    TOTpdf.plotOn(yframe,Project(RooArgSet(m2Kpi_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist));
    yframe->getAttLine()->SetLineWidth(1);
    yframe->getAttLine()->SetLineStyle(1);
    yframe->SetTitle("");
    yframe->GetYaxis()->SetTitle("Events/0.05 GeV^{2}/c^{4}");
    yframe->GetXaxis()->SetTitle("m^{2}_{K^{+}#pi^{0}}  [GeV^{2}/c^{4}]");
    Double_t chi2Kpi0 = yframe->chiSquare();
    TOTpdf.plotOn(yframe,Project(RooArgSet(m2Kpi_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist),Components(RooArgSet(totmis_norm,totbkg_norm)),DrawOption("F"),FillColor(kBlue)); //FillColor(17));
    TOTpdf.plotOn(yframe,Project(RooArgSet(m2Kpi_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist),Components(RooArgSet(totbkg_norm)),DrawOption("F"),FillColor(kRed));  //FillColor(14));

    yframe->GetYaxis()->SetTitleOffset(1.3);

    TPaveText *box_m13 = new TPaveText(2.5,2.5,2.7,2.7,"");
    box_m13->AddText("(c)");
    box_m13->SetFillColor(10);

    TCanvas c2("c2","c2",300,300);
    c2.cd();yframe->Draw();box_m13->Draw("SAME");
    c2.SaveAs("WSfit_m2Kpi0.eps");

    m2Kpi0_d0mass.setBins(20);

    RooPlot* zframe = m2pipi0_d0mass.frame(50);
    dataWS->plotOn(zframe,MarkerSize(0.1),DrawOption("z"));
    TOTpdf23.plotOn(zframe,Project(RooArgSet(m2Kpi_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist));
    zframe->getAttLine()->SetLineWidth(1);
    zframe->getAttLine()->SetLineStyle(1);
    zframe->SetTitle("");
    zframe->GetYaxis()->SetTitle("Events/0.08 GeV^{2}/c^{4}");
    zframe->GetXaxis()->SetTitle("m^{2}_{#pi^{-}#pi^{0}} [GeV/c^{2}]");
    Double_t chi2pipi0 = zframe->chiSquare();
    TOTpdf23.plotOn(zframe,Project(RooArgSet(m2Kpi_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist),Components(RooArgSet(totmis_norm23,totbkg_norm23)),DrawOption("F"),FillColor(kBlue));
    TOTpdf23.plotOn(zframe,Project(RooArgSet(m2Kpi_d0mass,d0Lifetime,d0LifetimeErr)),ProjWData(*dshist),Components(RooArgSet(totbkg_norm23)),DrawOption("F"),FillColor(kRed));

    cout << "Chi2 for Kpi = " << chi2Kpi << endl;
    cout << "Chi2 for Kpi0 = " << chi2Kpi0 << endl;
    cout << "Chi2 for pipi0 = " << chi2pipi0 << endl;

    TCanvas *c = new TCanvas("c","allevents",1200,400);
    c->Divide(3,1);
    c->cd(1);xframe->Draw();
    c->cd(2);yframe->Draw();
    c->cd(3);zframe->Draw();
    c->SaveAs("WSfit.eps");

  }

  if(doFrac){
    cout << "Calculating fit fractions" << endl;
    TFile f("fitWS.root");
    RooFitResult* fitRes = (RooFitResult*)f.Get("nll");
 
    //now calculate the fit fractions
    const Int_t nRes = TOTsigD0.getManager()->getnRes();
 
    //recalculate the normalization if necessary
    //TOTsigD0.getManager()->calNorm();
 
    EvtComplex normarray[nRes][nRes];
 
    const Int_t myRes = 7;
    TH1F fitty[myRes];
 
    //read the integral value from the cache file.
    //In this way we don't need to compute the normalization everytime during MIGRAD
    char int_name[50];
    TOTsigD0.getManager()->getFileName(int_name);
 
    ifstream f1;
    f1.open(int_name);
    if (!f1){
      cout << "Error opening file " << endl;
      assert(0);
    }
   
    Double_t re=0.,im=0.;
    //Read in the cache file and store back to array
    for(Int_t j=0;j<nRes;j++) {
      char thname[100];
      sprintf(thname,"thname_%d",j);
      if(j < myRes) fitty[j] = TH1F(thname,thname,30,0.,1.);
      for(Int_t k=0;k<nRes;k++){
	f1 >> re >> im;       
	normarray[j][k] = EvtComplex(re,im);
      }
    }   
    EvtComplex mynorm[myRes][myRes];
    Int_t m = 0, l = 0;
    for(Int_t i=0;i<myRes;i++){
      for(Int_t j=0;j<myRes;j++){
	if(i==0) l = 11;
	else if(i==1) l = 5;
	else if(i==2) l = 3;
	else if(i==3) l = 10;
	else if(i==4) l = 8;
	else if(i==5) l = 2;
	else if(i==6) l = 0;
 
	if(j==0) m = 11;
	else if(j==1) m = 5;
	else if(j==2) m = 3;
	else if(j==3) m = 10;
	else if(j==4) m = 8;
	else if(j==5) m = 2;
	else if(j==6) m = 0;
 
	mynorm[i][j] = normarray[l][m];
      }
    }
 
    //do 100 experiments and extract parameters using covariance matrix
    for(Int_t l=0;l<200;l++){
      RooArgList listpar = fitRes->randomizePars();
      if(l==0) listpar.Print();

      Double_t mynormD0 = 0.;
      EvtComplex coeff_i(0.,0.), coeff_j(0.,0.);
      for(Int_t i=0;i<2*myRes;i++){
        for(Int_t j=0;j<2*myRes;j++){
          if(i==(2*myRes - 2)) coeff_i = EvtComplex(1.,0.);
          else coeff_i = EvtComplex(((RooAbsReal*)listpar.at(i))->getVal()*cos(((RooAbsReal*)listpar.at(i+1))->getVal()),
                                    ((RooAbsReal*)listpar.at(i))->getVal()*sin(((RooAbsReal*)listpar.at(i+1))->getVal()));

          if(j==(2*myRes - 2)) coeff_j = EvtComplex(1.,0.);
          else coeff_j = EvtComplex(((RooAbsReal*)listpar.at(j))->getVal()*cos(((RooAbsReal*)listpar.at(j+1))->getVal()),
                                    ((RooAbsReal*)listpar.at(j))->getVal()*sin(((RooAbsReal*)listpar.at(j+1))->getVal()));
          mynormD0 += real(coeff_i*conj(coeff_j)*(mynorm[i/2][j/2]));
          j++;
        }
        i++;
      }

      //now calculate the fit fractions
      for(Int_t i=0;i<2*myRes;i++){
        Double_t fitfrac = 0.;
        if(i==(2*myRes - 2)) fitfrac = abs(mynorm[i/2][i/2])/mynormD0;
        else fitfrac = abs2( ((RooAbsReal*)listpar.at(i))->getVal())*abs(mynorm[i/2][i/2])/mynormD0;
        fitty[i/2].Fill(fitfrac);
        i++;
      }
    }// nexperiments

    Double_t tot_frac = 0.;
    for(Int_t i=0;i<myRes;i++){
      tot_frac += fitty[i].GetMean();
      cout << "Resonance " << i << ": fit fraction = " << fitty[i].GetMean() << " +/- " << fitty[i].GetRMS() << endl;
    }
    cout << "Total fit fraction = " << tot_frac << endl;
    cout << "///////////////////////////" << endl;
  }

  return 0;
}
