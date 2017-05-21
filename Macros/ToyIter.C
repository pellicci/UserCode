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
#include <RooMCStudy.h>
#include <RooRandom.h>
#include <RooProdPdf.h>
#include <RooSimultaneous.h>
#include <RooHistPdf.h>

#include <EvtGenBase/EvtDalitzPlot.hh>
#include <EvtGenBase/EvtDecayMode.hh>
#include <EvtGenBase/EvtPDL.hh>
 
#include <CharmDalitzFit/RooTimepdf.hh>

using namespace::RooFit;

int main(int argc, char* argv[])
{
  char *filename;
  Int_t nexp = 0, nev = 0, SEED = 0;
  Double_t c1val = 0., c2val = 0.;
  Double_t c1pval = 0., c2pval = 0.;
  Double_t c1mval = 0., c2mval = 0.;

  for(Int_t i=1;i<argc;i++){
    char *pchar = argv[i];

    switch(pchar[0]){

    case '-':{

      switch(pchar[1]){
      case 'f':
	filename = argv[i+1];
	cout << "File name used in this toy " << filename << endl;
	break;

      case 'e':
	nexp = atoi(argv[i+1]);
	cout << "Number of experiments " << nexp << endl;
	break;

      case 'n':
	nev = atoi(argv[i+1]);
	cout << "Number of events per experiment " << nev << endl;
	break;

      case 's':
        SEED = atoi(argv[i+1]);
        break;

      case '1':
	c1pval = atof(argv[i+1]);
	cout << "The c1 value is " << c1pval << endl;
        break;

      case '2':
	c1mval = atof(argv[i+1]);
	cout << "The c1 value is " << c1mval << endl;
        break;

      case '3':
        c2pval = atof(argv[i+1]);
	cout << "The c2 values is " << c2pval << endl;
        break;

     case '4':
        c2mval = atof(argv[i+1]);
	cout << "The c2 values is " << c2mval << endl;
        break;

      case 'x':
        c1val = atof(argv[i+1]);
	cout << "The c1 value is " << c1pval << endl;
        break;

      case 'y':
        c2val = atof(argv[i+1]);
        cout << "The c2 values is " << c2pval << endl;
        break;
      }
    }
    }

  }

  //set the seed and the generator used by EvtGen
  RooRandom::randomGenerator()->SetSeed(SEED);
  cout << "  Toy seed ............. " << (RooRandom::randomGenerator()->GetSeed()) << endl;

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  Bool_t doGen = kFALSE;
  Bool_t doFit = kTRUE;
  Bool_t extract = kFALSE;

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

  RooRealVar c1("c1","c1",c1val,-3.,3.);
  RooRealVar c2("c2","c2",c2val,-3.,3.);
  RooRealVar c1p("c1p","c1p",c1pval,-3.,3.);
  RooRealVar c2p("c2p","c2p",c2pval,-3.,3.);
  RooRealVar c1m("c1m","c1m",c1mval,-3.,3.);
  RooRealVar c2m("c2m","c2m",c2mval,-3.,3.);

  c1p.setConstant(kTRUE);
  c2p.setConstant(kTRUE);

  m2Kpi_d0mass.setBins(10);
  m2Kpi0_d0mass.setBins(10);
  d0Lifetime.setBins(8);
  d0LifetimeErr.setBins(10);

  //Construct signal pdf
  RooRealVar bias("bias","bias",0.0047);
  RooRealVar one("one","one",1.);

  //consider the resolution or the truth model
  RooGaussModel gm1("gm1","gauss model 1",d0Lifetime,bias,d0LifetimeErr,one,scalefact1) ;
  RooGaussModel gm2("gm2","gauss model 2",d0Lifetime,bias,d0LifetimeErr,one,scalefact2) ;
  RooGaussModel gm3("gm3","gauss model 3",d0Lifetime,bias,d0LifetimeErr,one,scalefact3) ;
  //RooTruthModel gm("gm","truth model",d0Lifetime);

  RooRealVar N1("N1","N1",0.0052);
  RooRealVar N2("N2","N2",0.179);

  RooFormulaVar f2("f2","f2","(1-@0)*@1",RooArgList(N1,N2));
  RooFormulaVar f3("f3","f3","(1-@0)*(1-@1)",RooArgList(N1,N2));
  RooAddModel gm("gm","gm",RooArgList(gm2,gm3,gm1),RooArgList(f2,f3));

  string dirname = "configmaps/effmapping_std/";

  RooTimepdf TOTsigD0("TOTsigD0","TOTsigD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,c1p,c2p,-1,dirname);
  RooTimepdf TOTsigantiD0("TOTsigantiD0","TOTsigantiD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,c1p,c2p,-1,dirname);
 
  RooSimultaneous TOTTime("TOTTime","TOTTime",D0flav);
  TOTTime.addPdf(TOTsigD0,"D0");
  TOTTime.addPdf(TOTsigantiD0,"antiD0");

  //////////////////////////
  // BACKGROUND
  /////////////////////////

  TFile RSfile("DataSet_out_reduced_RS.root");
  gROOT->cd();
  RooDataSet *RSdata = (RooDataSet*)RSfile.Get("fulldata");

  m2Kpi_d0mass.setBins(150);
  m2Kpi0_d0mass.setBins(150);
  d0Lifetime.setBins(70);
  d0LifetimeErr.setBins(20);
  /*
  TH3F *mis_h = m2Kpi_d0mass.createHistogram("mis_h",m2Kpi0_d0mass,d0Lifetime,"");
  RSdata->fillHistogram(mis_h,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime));
  mis_h->Sumw2();
  RooDataHist *mis_hist = new RooDataHist("mis_hist","mis_hist",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),mis_h);
  RooHistPdf Tot_mis("Tot_mis","Tot_mis",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),*mis_hist);
  */
  TH3F *mis_hp = m2Kpi_d0mass.createHistogram("mis_hp",m2Kpi0_d0mass,d0Lifetime,"");
  RSdata->fillHistogram(mis_hp,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),"D0flav == 1");
  mis_hp->Sumw2();
  RooDataHist *mis_histp = new RooDataHist("mis_histp","mis_histp",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),mis_hp);
  RooHistPdf Tot_misp("Tot_misp","Tot_misp",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),*mis_histp);

  TH3F *mis_hm = m2Kpi_d0mass.createHistogram("mis_hm",m2Kpi0_d0mass,d0Lifetime,"");
  RSdata->fillHistogram(mis_hm,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),"D0flav == -1");
  mis_hm->Sumw2();
  RooDataHist *mis_histm = new RooDataHist("mis_histm","mis_histm",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),mis_hm);
  RooHistPdf Tot_mism("Tot_mism","Tot_mism",RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime),*mis_histm);

  RooSimultaneous Tot_mis("Tot_mis","Tot_mis",D0flav);
  Tot_mis.addPdf(Tot_misp,"D0");
  Tot_mis.addPdf(Tot_mism,"antiD0");

  cout << "///////////////" << endl;
  cout << "Sample of D0bar RS : " << mis_histp->numEntries(kTRUE) << endl;
  cout << "Sample of D0 RS : " << mis_histm->numEntries(kTRUE) << endl;
  cout << "///////////////" << endl;

  m2Kpi_d0mass.setBins(10);
  m2Kpi0_d0mass.setBins(10);
  d0Lifetime.setBins(8);
  d0LifetimeErr.setBins(10);

  RooArgSet observ(d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass);
  RooArgSet tot_var(d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,d0LifetimeErr,D0flav);

  TFile WSfile("DataSet_out_reduced_WS.root");
  gROOT->cd();
  RooDataSet *databkg = (RooDataSet*)WSfile.Get("fulldata");
  RooDataSet *leftdata = (RooDataSet*)databkg->reduce("d0Mass > 1.74 && d0Mass < 1.78");
  RooDataSet *rightdata = (RooDataSet*)databkg->reduce("d0Mass > 1.94 && d0Mass < 1.98");
  databkg->setWeightVar(0);
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

  Float_t totnonorm = 1508. + 791. + 663. + 47.;
  Float_t ratio = nev/totnonorm;

  RooRealVar Nsig("Nsig","Nsig",1508.*ratio);
  RooRealVar Nmis("Nmis","Nmis",791.*ratio);
  RooRealVar Ncomb("Ncomb","Ncomb",(663. + 47.)*ratio);

  d0LifetimeErr.setBins(100);
  RooDataSet *ProtoData_err = (RooDataSet*)RSdata->reduce(RooArgSet(d0LifetimeErr));
  TH1F *err_sig_h = (TH1F*)d0LifetimeErr.createHistogram("err_sig_h");
  ProtoData_err->fillHistogram(err_sig_h,RooArgSet(d0LifetimeErr));
  RooDataHist terr_sig("terr_sig","terr_sig",RooArgSet(d0LifetimeErr),err_sig_h);
  RooHistPdf terr_sig_pdf("terr_sig_pdf","terr_sig_pdf",RooArgSet(d0LifetimeErr),terr_sig,3);
  d0LifetimeErr.setBins(10);

  RooDataSet *ProtoData_bkg = (RooDataSet*)databkg->reduce(RooArgSet(d0LifetimeErr));
  TH1F *err_bkg_h = (TH1F*)d0LifetimeErr.createHistogram("err_bkg_h");
  ProtoData_bkg->fillHistogram(err_bkg_h,RooArgSet(d0LifetimeErr));
  err_bkg_h->Scale(err_sig_h->Integral()/err_bkg_h->Integral());
  RooDataHist terr_bkg("terr_bkg","terr_bkg",RooArgSet(d0LifetimeErr),err_bkg_h);
  RooHistPdf terr_bkg_pdf("terr_bkg_pdf","terr_bkg_pdf",RooArgSet(d0LifetimeErr),terr_bkg,3);

  RooDataSet *ProtoData_flav_1 = (RooDataSet*)RSdata->reduce(RooArgSet(D0flav));
  RooDataSet *ProtoData_flav = (RooDataSet*)ProtoData_flav_1->reduce(EventRange(1,(Int_t)((1508 + 791)*ratio)));
  //RooDataHist flav_sig("flav_sig","flav_sig",RooArgSet(D0flav),*ProtoData_flav);
  //RooHistPdf flav_sig_pdf("flav_sig_pdf","flav_sig_pdf",RooArgSet(D0flav),flav_sig);

  RooDataSet *ProtoData_flav_bkg_1 = (RooDataSet*)databkg->reduce(RooArgSet(D0flav));
  RooDataSet *ProtoData_flav_bkg = (RooDataSet*)ProtoData_flav_bkg_1->reduce(EventRange(1,(Int_t)((663 + 47)*ratio)));
  //RooDataHist flav_bkg("flav_bkg","flav_bkg",RooArgSet(D0flav),*ProtoData_flav_bkg);
  //RooHistPdf flav_bkg_pdf("flav_bkg_pdf","flav_bkg_pdf",RooArgSet(D0flav),flav_bkg);

  ProtoData_flav->append(*ProtoData_flav_bkg);

  RooProdPdf totsig_norm("totsig_norm","totsig_norm",RooArgSet(terr_sig_pdf),Conditional(TOTTime,observ));
  RooProdPdf totmis_norm("totmis_norm","totmis_norm",RooArgSet(terr_sig_pdf),Conditional(Tot_mis,observ));
  RooProdPdf totbkg_norm("totbkg_norm","totbkg_norm",RooArgSet(terr_bkg_pdf),Conditional(Tot_comb,observ));
  /*
  RooProdPdf totsig_norm("totsig_norm","totsig_norm",RooArgSet(terr_sig_pdf),Conditional(TOTsigD0,observ));
  RooProdPdf totmis_norm("totmis_norm","totmis_norm",RooArgSet(terr_sig_pdf),Conditional(Tot_mis,observ));
  RooProdPdf totbkg_norm("totbkg_norm","totbkg_norm",RooArgSet(terr_bkg_pdf),Conditional(Tot_comb,observ));
  */
  //Signal + background
  RooAddPdf TOTpdf("TOTpdf","TOTpdf",RooArgList(totsig_norm,totmis_norm,totbkg_norm),RooArgList(Nsig,Nmis,Ncomb));

  RooMCStudy mgr(totsig_norm,tot_var,FitOptions(Save(1),Extended(0),Minos(0)),Extended(0),ConditionalObservables(D0flav),RooFit::ProtoData(*ProtoData_flav,1));
  //RooMCStudy mgr(totsig_norm,tot_var,FitOptions(ConditionalObservables(RooArgSet(D0flav)),Save(1),Extended(0)),Extended(0),RooFit::ProtoData(*ConditDataset,1));

  TString dataname(filename);
  dataname.Append(".dat");
  TString toyname(filename);
  toyname.Append("_fixed.root");

  if(doGen && !doFit) mgr.generate(nexp,nev,kFALSE,dataname);
  if(doFit && !doGen) mgr.fit(nexp,dataname);
  if(doGen && doFit) mgr.generateAndFit(nexp,nev,kFALSE,dataname);

  if(doFit){
  TFile f(toyname,"RECREATE");
  f.cd();
  (RooFitResult*)mgr.fitResult(0)->Write();
  mgr.fitParDataSet().tree().Write();
  f.Close();
  }

  if(extract){

  RooFitResult *theRes = (RooFitResult*)mgr.fitResult(0);

    RooRealVar myc1("myc1","myc1",-10.,10.);
    RooRealVar myc2("myc2","myc2",-10.,10.);
    RooRealVar myratio("myratio","myratio",0.,0.,1.);
    RooRealVar myx("myx","myx",0.,-1.,1.);
    RooRealVar myy("myy","myy",0.,-1.,1.);

    Double_t NrsNws = 2760./1198329;
    Double_t ratioerr = sqrt(pow(96.,2.) + pow(NrsNws,2.)*pow(2760.,2.))/1198329.;
    RooDataSet *parFloat = new RooDataSet("parFloat","parFloat",RooArgList(myratio,myx,myy));

    RooTimepdf mysigD0("mysigD0","mysigD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,c1,c2,-1,dirname);
    Double_t myDenom = mysigD0.createIntegral(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime))->getVal();

    cout << "x' " << c2.getVal()*sqrt(NrsNws/myDenom) << endl;
    cout << "y' " << c1.getVal()*sqrt(NrsNws/myDenom) << endl;
    cout << "r0^2 " << NrsNws/myDenom << endl;

    for(Int_t j=0;j<1000;j++){
      cout << "Performing step number " << j << endl;
      RooArgList floated = theRes->randomizePars();
      myc1.setVal(((RooAbsReal*)floated.find("c1"))->getVal());
      myc2.setVal(((RooAbsReal*)floated.find("c2"))->getVal());

      Double_t myDenom = mysigD0.createIntegral(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime))->getVal();
      Double_t myNum = RooRandom::randomGenerator()->Gaus(NrsNws,ratioerr);

      myratio.setVal(myNum/myDenom);
      myx.setVal(myc2.getVal()*sqrt((myNum/myDenom)));
      myy.setVal(myc1.getVal()*sqrt((myNum/myDenom)));

      parFloat->add(RooArgSet(myratio,myx,myy));
    }

    TString floatname(filename);
    floatname.Append("_float.root");

    TFile *f1 = new TFile(floatname,"RECREATE");
    f1->cd();
    parFloat->Write();
    f1->Close();
  }

  return 0;
}
