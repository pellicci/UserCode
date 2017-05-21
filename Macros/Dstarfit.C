#include <iostream>

#include <BaBarStyle.h>

#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TPaveText.h>
#include <TArrow.h>
#include <TStyle.h>

#include <RooRealVar.h>
#include <RooCategory.h>
#include <RooDataSet.h>
#include <RooArgSet.h>
#include <RooFormulaVar.h>
#include <RooGaussian.h>
#include <RooCBShape.h>
#include <RooProdPdf.h>
#include <RooAddPdf.h>
#include <RooGenericPdf.h>
#include <RooPolynomial.h>
#include <RooSimultaneous.h>
#include <RooSimPdfBuilder.h>
#include <RooPlot.h>
#include <RooFitResult.h>
#include <RooGlobalFunc.h>
#include <RooChi2Var.h>
#include <RooMinuit.h>
#include <RooHist.h>
#include <RooDataHist.h>
#include <RooHistPdf.h>

using namespace::RooFit;

int main(){

  Bool_t doPlots = kTRUE;
  Bool_t doMC = kFALSE;
                                                                                                                                                             
  BaBarStyle p;
  p.SetBaBarStyle();
  gROOT->GetStyle("BABAR")->SetPalette(1);
  gROOT->GetStyle("BABAR")->SetPadTopMargin(0.04);
  gROOT->GetStyle("BABAR")->SetPadLeftMargin(0.19);
  gROOT->GetStyle("BABAR")->SetPadRightMargin(0.08);
  gROOT->GetStyle("BABAR")->SetPadBottomMargin(0.19);
  gROOT->GetStyle("BABAR")->SetTitleSize(0.08,"xyz"); // set the 3 axes title size 

  RooRealVar d0Mass("d0Mass","d0Mass",1.74,1.98);
  RooRealVar deltaMass("deltaMass","deltaMass",0.13923,0.155);
  RooCategory isWS("isWS","isWS");
  isWS.defineType("RS",0);
  isWS.defineType("WS",1);
  RooCategory tag_opp_side("tag_opp_side","tag_opp_side");
  tag_opp_side.defineType("tag",1);
  tag_opp_side.defineType("notag",0);
  RooCategory truthIsSignal("truthIsSignal","truthIsSignal");
  truthIsSignal.defineType("sig",1);
  truthIsSignal.defineType("nosig",0);
  RooCategory truthIsBkg_FakePiSlow("truthIsBkg_FakePiSlow","truthIsBkg_FakePiSlow");
  truthIsBkg_FakePiSlow.defineType("mis",1);
  truthIsBkg_FakePiSlow.defineType("nomis",0);
  RooCategory truthIsBkg_SwappedKpi("truthIsBkg_SwappedKpi","truthIsBkg_SwappedKpi");
  truthIsBkg_SwappedKpi.defineType("swap",1);
  truthIsBkg_SwappedKpi.defineType("noswap",0);
  RooCategory truthIsBkg_BadOtherD0("truthIsBkg_BadOtherD0","truthIsBkg_BadOtherD0");
  truthIsBkg_BadOtherD0.defineType("badd0",1);
  truthIsBkg_BadOtherD0.defineType("nobadd0",0);
  RooCategory truthIsBkg_BadDplus("truthIsBkg_BadDplus","truthIsBkg_BadDplus");
  truthIsBkg_BadDplus.defineType("baddp",1);
  truthIsBkg_BadDplus.defineType("nobaddp",0);
  RooCategory truthIsBkg_Comb("truthIsBkg_Comb","truthIsBkg_Comb");
  truthIsBkg_Comb.defineType("comb",1);
  truthIsBkg_Comb.defineType("nocomb",0);
  RooRealVar frac("frac","frac",0.,100000.);

  //read in the dataset
  TFile hello("DataSet_out_tmp.root");
  gROOT->cd();
  RooDataSet *data = (RooDataSet*)hello.Get("fulldata");
  RooDataSet *finaldata = (RooDataSet*)data->reduce("d0LifetimeErr < 0.5 && d0Lifetime > -2. && d0Lifetime < 4.");
  //RooDataSet *finaldata = (RooDataSet*)finaldata_1->reduce(EventRange(1,70000));
  //here we set the weights for the dataset
  finaldata->setWeightVar(0);

  cout << "Number of events : " << finaldata->numEntries() << endl;

  Double_t lowm,higm,lowdm,higdm;
  finaldata->getRange(d0Mass,lowm,higm);
  finaldata->getRange(deltaMass,lowdm,higdm);
  cout << "D0 mass " << lowm << " " << higm << endl;
  cout << "delta mass " << lowdm << " " << higdm << endl;
  d0Mass.setRange(lowm,higm);
  deltaMass.setRange(lowdm,higdm);

  RooArgSet paramslist;

  RooRealVar mmean1("mmean1","mmean1",1.86529849,1.83,1.88);
  RooRealVar mmean2("mmean2","mmean2",1.86611085,1.83,1.88);
  RooRealVar mmean3("mmean3","mmean3",1.85607239,1.83,1.88);
  RooRealVar mmean4("mmean4","mmean4",1.86613406,1.83,1.88);
  paramslist.add(mmean1);
  paramslist.add(mmean2);
  paramslist.add(mmean3);
  paramslist.add(mmean4);

  RooRealVar msigma1("msigma1","msigma1",1.35353345e-02,0.,1.);
  RooRealVar msigma2("msigma2","msigma2",7.99704142e-03,0.,1.);
  RooRealVar msigma3("msigma3","msigma3",2.82501065e-02,0.,1.);
  RooRealVar msigma4("msigma4","msigma4",1.30870575e-02,0.,1.);
  paramslist.add(msigma1);
  paramslist.add(msigma2);
  paramslist.add(msigma3);
  paramslist.add(msigma4);

  RooRealVar dmmean1("dmmean1","dmmean1",1.45407903e-01,0.144,0.147);
  RooRealVar dmmean2("dmmean2","dmmean2",1.45414622e-01,0.144,0.147);
  RooRealVar dmmean3("dmmean3","dmmean3",1.45463869e-01,0.144,0.147);
  RooRealVar dmmean4("dmmean4","dmmean4",1.45611208e-01,0.144,0.147);
  paramslist.add(dmmean1);
  paramslist.add(dmmean2);
  paramslist.add(dmmean3);
  paramslist.add(dmmean4);

  RooRealVar dmsigma1("dmsigma1","dmsigma1",1.81584381e-04,0.,1.);
  RooRealVar dmsigma2("dmsigma2","dmsigma2",2.90761479e-04,0.,1.);
  RooRealVar dmsigma3("dmsigma3","dmsigma3",4.84649013e-04,0.,1.);
  RooRealVar dmsigma4("dmsigma4","dmsigma4",1.11906966e-03,0.,1.);
  paramslist.add(dmsigma1);
  paramslist.add(dmsigma2);
  paramslist.add(dmsigma3);
  paramslist.add(dmsigma4);

  RooRealVar dmcorr1("dmcorr1","dmcorr1",5.03372726e-05,-0.1,0.1);
  RooRealVar dmcorr2("dmcorr2","dmcorr2",2.26300787e-05,-0.1,0.1);
  RooRealVar dmcorr3("dmcorr3","dmcorr3",8.77842836e-05,-0.1,0.1);
  RooRealVar alpha4("alpha4","alpha4",-1.34031232,-5.,5.);
  paramslist.add(dmcorr1);
  paramslist.add(dmcorr2);
  paramslist.add(dmcorr3);
  paramslist.add(alpha4);

  RooRealVar two("two","two",2.);
  RooRealVar f1("f1","f1",2.12010936e-01,0.,1.);
  RooRealVar f2("f2","f2",2.03988520e-01,0.,1.);
  RooRealVar f3("f3","f3",2.47816789e-01,0.,1.);
  paramslist.add(f1);
  paramslist.add(f2);
  paramslist.add(f3);

  //now define pdfs, first signal
  RooGaussian mD1("mD1","mD1",d0Mass,mmean1,msigma1);
  RooGaussian mD2("mD2","mD2",d0Mass,mmean2,msigma2);
  RooGaussian mD3("mD3","mD3",d0Mass,mmean3,msigma3);
  RooGaussian mD4("mD4","mD4",d0Mass,mmean4,msigma4);

  RooFormulaVar denom1("denom1","@0 + @1*pow((@2-@3)/@4,2)",RooArgList(dmsigma1,dmcorr1,d0Mass,mmean1,msigma1));
  RooFormulaVar denom2("denom2","@0 + @1*pow((@2-@3)/@4,2)",RooArgList(dmsigma2,dmcorr2,d0Mass,mmean2,msigma2));
  RooFormulaVar denom3("denom3","@0 + @1*pow((@2-@3)/@4,2)",RooArgList(dmsigma3,dmcorr3,d0Mass,mmean3,msigma3));

  RooGaussian dM1("dM1","dM1",deltaMass,dmmean1,denom1);
  RooGaussian dM2("dM2","dM2",deltaMass,dmmean2,denom2);
  RooGaussian dM3("dM3","dM3",deltaMass,dmmean3,denom3);
  RooCBShape cbs("cbs","cbs",deltaMass,dmmean4,dmsigma4,alpha4,two);

  RooProdPdf s1("s1","s1",mD1,dM1);
  RooProdPdf s2("s2","s2",mD2,dM2);
  RooProdPdf s3("s3","s3",mD3,dM3);
  RooProdPdf s4("s4","s4",mD4,cbs);

  RooAddPdf sig1("sig1","sig1",RooArgList(s3,s4),RooArgList(f3));
  RooAddPdf sig2("sig2","sig2",RooArgList(s2,sig1),RooArgList(f2));
  RooAddPdf totsig("totsig","totsig",RooArgList(s1,sig2),RooArgList(f1));

  //COMBINATORIC
  RooRealVar x0("x0","x0",0.13957);
  RooFormulaVar d0Massshift("d0Massshift","@0-1.865",RooArgList(d0Mass));
  RooRealVar cws("cws","cws",2.31080532,1.,10.);
  RooRealVar crs("crs","crs",4.56495807,1.,10.);
  RooRealVar b1RS("b1RS","b1RS",-4.34601295e-01,-4.,4.);
  RooRealVar b1WS("b1WS","b1WS",-3.28806817e-01,-4.,4.);
  paramslist.add(cws);
  paramslist.add(crs);
  paramslist.add(b1RS);
  paramslist.add(b1WS);

  //same as RS and WS!!!
  RooGenericPdf aWS("aWS","aWS","@0*sqrt(pow(@0/@1,2)-1.)*exp(-@2*(pow(@0/@1,2)-1.))",RooArgList(deltaMass,x0,cws));
  RooGenericPdf aRS("aRS","aRS","@0*sqrt(pow(@0/@1,2)-1.)*exp(-@2*(pow(@0/@1,2)-1.))",RooArgList(deltaMass,x0,crs));
  RooPolynomial polyRS("polyRS","polyRS",d0Massshift,RooArgList(b1RS));
  RooPolynomial polyWS("polyWS","polyWS",d0Massshift,RooArgList(b1WS));

  RooProdPdf nonpeakRS("nonpeakRS","nonpeakRS",aRS,polyRS);
  RooProdPdf nonpeakWS("nonpeakWS","nonpeakWS",aWS,polyWS);

  //MISTAG
  RooAddPdf mmis1("mmis1","mmis1",RooArgList(mD3,mD4),RooArgList(f3));
  RooAddPdf mmis2("mmis2","mmis2",RooArgList(mD2,mmis1),RooArgList(f2));
  RooAddPdf mmistot("mmistot","mmistot",RooArgList(mD1,mmis2),RooArgList(f1));
  RooProdPdf totmisRS("totmisRS","totmisRS",mmistot,aRS);
  RooProdPdf totmisWS("totmisWS","totmisWS",mmistot,aWS);

  //BAD D0
  TFile fbad("dstar_forfit.root");
  fbad.cd();

  TH1F *bad_mD0RS = (TH1F*)fbad.Get("mD0badRS");
  RooDataHist *badmD0_datahistRS = new RooDataHist("badmD0_datahistRS","badmD0_datahistRS",RooArgList(d0Mass),bad_mD0RS);
  RooHistPdf totbadmD0RS("totbadmD0RS","totbadmD0RS",RooArgSet(d0Mass),*badmD0_datahistRS,3);
  TH1F *bad_deltamRS = (TH1F*)fbad.Get("deltambadRS");
  RooDataHist *baddeltam_datahistRS = new RooDataHist("baddeltam_datahistRS","baddeltam_datahistRS",RooArgList(deltaMass),bad_deltamRS);
  RooHistPdf totbaddeltamRS("totbaddeltamRS","totbaddeltamRS",RooArgSet(deltaMass),*baddeltam_datahistRS,3);
  RooProdPdf totbadD0RS("totbadD0RS","totbadD0RS",totbadmD0RS,totbaddeltamRS);

  TH1F *bad_mD0WS = (TH1F*)fbad.Get("mD0badWS");
  RooDataHist *badmD0_datahistWS = new RooDataHist("badmD0_datahistWS","badmD0_datahistWS",RooArgList(d0Mass),bad_mD0WS);
  RooHistPdf totbadmD0WS("totbadmD0WS","totbadmD0WS",RooArgSet(d0Mass),*badmD0_datahistWS,3);
  TH1F *bad_deltamWS = (TH1F*)fbad.Get("deltambadWS");
  RooDataHist *baddeltam_datahistWS = new RooDataHist("baddeltam_datahistWS","baddeltam_datahistWS",RooArgList(deltaMass),bad_deltamWS);
  RooHistPdf totbaddeltamWS("totbaddeltamWS","totbaddeltamWS",RooArgSet(deltaMass),*baddeltam_datahistWS,3);
  RooProdPdf totbadD0WS("totbadD0WS","totbadD0WS",totbadmD0WS,totbaddeltamWS);

  //PUT ALL REALLY TOGETHER
  RooRealVar NsigRS("NsigRS","NsigRS",4.50711081e+05,0.,1.e+07);
  RooRealVar NcombRS("NcombRS","NsigRS",1.09760040e+05,0.,1.e+07);
  RooRealVar NmistagRS("NmistagRS","NmistagRS",1.57130302e+04,0.,1.e+07);
  RooRealVar NbrokRS("NbrokRS","NbrokRS",7.24961432e+04,0.,1.e+07);
  paramslist.add(NsigRS);
  paramslist.add(NcombRS);
  paramslist.add(NmistagRS);
  paramslist.add(NbrokRS);

  RooRealVar NsigWS("NsigWS","NsigWS",9.60250721e+02,0.,1.e+06);
  RooRealVar NcombWS("NcombWS","NsigWS",1.94793713e+04,0.,50000.);
  RooRealVar NmistagWS("NmistagWS","NmistagWS",2.05824765e+03,0.,10000.);
  RooRealVar NbrokWS("NbrokWS","NbrokWS",2.35940834e+03,0.,10000.);
  paramslist.add(NsigWS);
  paramslist.add(NcombWS);
  paramslist.add(NmistagWS);
  paramslist.add(NbrokWS);

  RooAddPdf TOTpdfRS("TOTpdfRS","TOTpdfRS",RooArgList(totsig,nonpeakRS,totmisRS,totbadD0RS),RooArgList(NsigRS,NcombRS,NmistagRS,NbrokRS));
  RooAddPdf TOTpdfWS("TOTpdfWS","TOTpdfWS",RooArgList(totsig,nonpeakWS,totmisWS,totbadD0WS),RooArgList(NsigWS,NcombWS,NmistagWS,NbrokWS));

  RooSimultaneous TOTpdf("TOTpdf","TOTpdf",isWS);
  TOTpdf.addPdf(TOTpdfRS,"RS");
  TOTpdf.addPdf(TOTpdfWS,"WS");

  paramslist.readFromFile("mD0deltaMpars_chi2.txt");
  paramslist.printLatex(OutputFile("params_latex.txt"),Format("NE"));

  deltaMass.setBins(65);
  d0Mass.setBins(65);

  RooDataHist* db = new RooDataHist("db","db",RooArgSet(deltaMass,d0Mass,isWS),*finaldata);
  /*
    RooChi2Var chi2("chi2","chi2",TOTpdf,*db,ConditionalObservables(RooArgSet(isWS)),Extended(1),DataError(RooAbsData::SumW2));
    RooMinuit m2(chi2) ;
    m2.migrad() ;
    m2.hesse() ;
    //m2.minos();
    RooFitResult* fitRes = m2.save() ;
    fitRes->Print("v");
    RooArgSet results(fitRes->floatParsFinal());
    RooArgSet conresults(fitRes->constPars());
    results.add(conresults);
    results.writeToFile("fit_mD0deltam_chi2.txt");
    TFile saveres("fit_result.root","RECREATE");
    fitRes->Write();
    saveres.Close(); 
  */
  /*
  //determine fraction of events in signal region using toy-mc
  RooDataSet *toysig = (RooDataSet*)totsig.generate(RooArgSet(d0Mass,deltaMass),1000000);
  RooDataSet *toysig_red = (RooDataSet*)toysig->reduce("d0Mass > 1.91 && d0Mass < 1.98 && deltaMass > 0.1441 && deltaMass < 0.1462");
  Double_t frac_sig = ((Double_t)toysig_red->numEntries())/((Double_t)toysig->numEntries());
  
  RooDataSet *toycomb = (RooDataSet*)nonpeakWS.generate(RooArgSet(d0Mass,deltaMass),1000000);
  RooDataSet *toycomb_red = (RooDataSet*)toycomb->reduce("d0Mass > 1.91 && d0Mass < 1.98 && deltaMass > 0.1441 && deltaMass < 0.1462");
  Double_t frac_comb = ((Double_t)toycomb_red->numEntries())/((Double_t)toycomb->numEntries());

  RooDataSet *toymis = (RooDataSet*)totmisWS.generate(RooArgSet(d0Mass,deltaMass),1000000);
  RooDataSet *toymis_red = (RooDataSet*)toymis->reduce("d0Mass > 1.91 && d0Mass < 1.98 && deltaMass > 0.1441 && deltaMass < 0.1462");
  Double_t frac_mis = ((Double_t)toymis_red->numEntries())/((Double_t)toymis->numEntries());
  
  RooDataSet *toybadD0 = (RooDataSet*)totbadD0WS.generate(RooArgSet(d0Mass,deltaMass),1000000);
  RooDataSet *toybadD0_red = (RooDataSet*)toybadD0->reduce("d0Mass > 1.91 && d0Mass < 1.98 && deltaMass > 0.1441 && deltaMass < 0.1462");
  Double_t frac_badD0 = ((Double_t)toybadD0_red->numEntries())/((Double_t)toybadD0->numEntries());
  
  cout << "###################################################" << endl;
  cout << "Signal fractions:" << endl;
  cout << "signal fraction = " << frac_sig << endl;
  cout << "combinatoric fraction = " << frac_comb << endl;
  cout << "mistag fraction = " << frac_mis << endl;
  cout << "badD0 fraction = " << frac_badD0 << endl;
  cout << "###################################################" << endl;
  cout << "Events in signal region:" << endl;
  cout << "Signal = " << frac_sig*NsigWS.getVal() << endl;
  cout << "Combinatoric = " << frac_comb*NcombWS.getVal() << endl;
  cout << "Mistag = " << frac_mis*NmistagWS.getVal() << endl;
  cout << "Bad D0 = " << frac_badD0*NbrokWS.getVal() << endl;
  cout << "###################################################" << endl;
  cout << "Errors" << endl;
  cout << "Signal = " << sqrt(frac_sig*(1.-frac_sig)*NsigWS.getVal()) << endl;
  cout << "Combinatoric = " << sqrt(frac_comb*(1.-frac_comb)*NcombWS.getVal()) << endl;
  cout << "Mistag = " << sqrt(frac_mis*(1.-frac_mis)*NmistagWS.getVal()) << endl;
  cout << "Bad D0 = " << sqrt(frac_badD0*(1-frac_badD0)*NbrokWS.getVal()) << endl;
  cout << "###################################################" << endl;
  */
  RooDataSet *db_dummy = (RooDataSet*)finaldata->reduce(RooArgSet(isWS));
  /*
  //  RooDataSet *toysig = (RooDataSet*)totsig.generate(RooArgSet(d0Mass,deltaMass),1000000);
  TFile ftmp("prova.root","RECREATE");
  ftmp.cd();
  toysig->Write();
  ftmp.Close();
  */
  /*
    RooDataSet *db_dummy_dm_1 = TOTpdf.generate(RooArgSet(d0Mass,deltaMass,isWS),finaldata->numEntries(),RooFit::ProtoData(*db_dummy,1));
    RooDataSet *db_dummy_dm_2 = (RooDataSet*)db_dummy_dm_1->reduce("deltaMass > 0.145 && deltaMass < 0.146");
    RooDataHist *db_dummy_dm = new RooDataHist("db_dummy_dm","db_dummy_dm",RooArgSet(deltaMass,isWS),*db_dummy_dm_2);

    RooDataSet *db_dummy_1 = TOTpdf.generate(RooArgSet(d0Mass,deltaMass,isWS),finaldata->numEntries(),RooFit::ProtoData(*db_dummy,1));
    RooDataSet *db_dummy_2 = (RooDataSet*)db_dummy_m_1->reduce("d0Mass > 1.85 && d0Mass < 1.88");
    RooDataHist *db_dummy_m = new RooDataHist("db_dummy_m","db_dummy_m",RooArgSet(d0Mass,isWS),*db_dummy_m_2);
 
    deltaMass.setRange(lowdm,higdm);
    d0Mass.setRange(lowm,higm);
  */
  deltaMass.setRange("signal_region",0.1449,0.1459);
  d0Mass.setRange("signal_region",1.8495,1.8795);
  deltaMass.setRange("left_dm",lowdm,0.143);
  deltaMass.setRange("right_dm",0.149,higdm);
  d0Mass.setRange("left_m",lowm,1.81);
  d0Mass.setRange("right_m",1.91,higm);

  deltaMass.setRange("normal",lowdm,higdm);
  d0Mass.setRange("normal",lowm,higm);

  if(doPlots){

    //PLOT DATA AND FIT

    //tagged RS

    d0Mass.setBins(160);
    deltaMass.setBins(160);

    isWS.setIndex(0,kTRUE);
   
    RooPlot* mframeRS = d0Mass.frame();
    finaldata->plotOn(mframeRS,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::RS && deltaMass > 0.1449 && deltaMass < 0.1459"));
    TOTpdf.plotOn(mframeRS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)));

    RooPlot* pullRSmD0 = d0Mass.frame() ;
    pullRSmD0->addPlotable(mframeRS->pullHist()) ;
    pullRSmD0->SetMaximum(5.);
    pullRSmD0->SetMinimum(-5.);
  
    TOTpdf.plotOn(mframeRS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakRS,totbadD0RS,totmisRS)),DrawOption("F"),FillColor(kBlue));
    TOTpdf.plotOn(mframeRS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakRS,totbadD0RS)),DrawOption("F"),FillColor(kRed));
    TOTpdf.plotOn(mframeRS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakRS)),DrawOption("F"),FillColor(kGreen));
    finaldata->plotOn(mframeRS,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::RS && deltaMass > 0.1449 && deltaMass < 0.1459"));
    mframeRS->getAttLine()->SetLineWidth(1);
    mframeRS->getAttLine()->SetLineStyle(1);
  
    RooPlot* dmframeRS = deltaMass.frame();
    finaldata->plotOn(dmframeRS,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::RS && d0Mass > 1.8495 && d0Mass < 1.8795"));
    TOTpdf.plotOn(dmframeRS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)));

    RooPlot* pullRSdm = deltaMass.frame() ;
    pullRSdm->addPlotable(dmframeRS->pullHist()) ;
    pullRSdm->SetMaximum(5.);
    pullRSdm->SetMinimum(-5.);
  
    TOTpdf.plotOn(dmframeRS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakRS,totbadD0RS,totmisRS)),DrawOption("F"),FillColor(kRed));
    TOTpdf.plotOn(dmframeRS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakRS,totmisRS)),DrawOption("F"),FillColor(kBlue));
    TOTpdf.plotOn(dmframeRS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakRS)),DrawOption("F"),FillColor(kGreen));
    finaldata->plotOn(dmframeRS,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::RS && d0Mass > 1.8495 && d0Mass < 1.8795"));
    dmframeRS->getAttLine()->SetLineWidth(1);
    dmframeRS->getAttLine()->SetLineStyle(1);

    //tagged WS
    isWS.setIndex(1,kTRUE);
    deltaMass.setBins(70);
    d0Mass.setBins(70);

    RooPlot* mframeWS = d0Mass.frame();
    finaldata->plotOn(mframeWS,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::WS && deltaMass > 0.1449 && deltaMass < 0.1459"));
    TOTpdf.plotOn(mframeWS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)));

    RooPlot* pullWSmD0 = d0Mass.frame() ;
    pullWSmD0->addPlotable(mframeWS->pullHist()) ;
    pullWSmD0->SetMaximum(5.);
    pullWSmD0->SetMinimum(-5.);
  
    TOTpdf.plotOn(mframeWS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS,totbadD0WS,totmisWS)),DrawOption("F"),/*FillColor(kBlue));*/   FillColor(17)); //for PRL
    TOTpdf.plotOn(mframeWS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS,totbadD0WS)),DrawOption("F"),/*FillColor(kRed));*/   FillColor(14)); // for PRL
    //TOTpdf.plotOn(mframeWS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS)),DrawOption("F"),FillColor(kGreen));
    finaldata->plotOn(mframeWS,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::WS && deltaMass > 0.1449 && deltaMass < 0.1459"));
    mframeWS->getAttLine()->SetLineWidth(1);
    mframeWS->getAttLine()->SetLineStyle(1);
  
    RooPlot* dmframeWS = deltaMass.frame(lowdm,0.15,100);
    finaldata->plotOn(dmframeWS,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::WS && d0Mass > 1.8495 && d0Mass < 1.8795"));
    TOTpdf.plotOn(dmframeWS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)));

    RooPlot* pullWSdm = deltaMass.frame() ;
    pullWSdm->addPlotable(dmframeWS->pullHist()) ;
    pullWSdm->SetMaximum(5.);
    pullWSdm->SetMinimum(-5.);
  
    TOTpdf.plotOn(dmframeWS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS,totbadD0WS,totmisWS)),DrawOption("F"),/*FillColor(kRed));*/   FillColor(17)); // for PRL
    TOTpdf.plotOn(dmframeWS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS,totbadD0WS)),DrawOption("F"),/*FillColor(kBlue));*/   FillColor(14)); // for PRL
    //TOTpdf.plotOn(dmframeWS,ProjWData(*db_dummy),ProjectionRange("signal_region"),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS)),DrawOption("F"),FillColor(kGreen));
    finaldata->plotOn(dmframeWS,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::WS && d0Mass > 1.8495 && d0Mass < 1.8795"));
    dmframeWS->getAttLine()->SetLineWidth(1);
    dmframeWS->getAttLine()->SetLineStyle(1);
  
    mframeRS->SetTitle("");
    dmframeRS->SetTitle("");
    mframeWS->SetTitle("");
    dmframeWS->SetTitle("");
    pullRSmD0->SetTitle("");
    pullRSdm->SetTitle("");
    pullWSmD0->SetTitle("");
    pullWSdm->SetTitle("");

    mframeRS->GetXaxis()->SetTitle("m_{K^{-}#pi^{+}#pi^{0}} [GeV/c^{2}]");
    dmframeRS->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");
    mframeWS->GetXaxis()->SetTitle("m_{K^{+}#pi^{-}#pi^{0}} [GeV/c^{2}]");
    dmframeWS->GetXaxis()->SetTitle("#Delta m [GeV/c^{2}]");

    mframeWS->GetYaxis()->SetTitle("Events/3.4 MeV/c^{2}");
    dmframeWS->GetYaxis()->SetTitle("Events/0.12 MeV/c^{2}");

    pullRSmD0->GetXaxis()->SetTitle("");
    pullRSdm->GetXaxis()->SetTitle("");
    pullWSmD0->GetXaxis()->SetTitle("");
    pullWSdm->GetXaxis()->SetTitle("");

    pullRSmD0->GetYaxis()->SetTitle("#pm{#sqrt{#Chi^{2}}}");
    pullRSdm->GetYaxis()->SetTitle("#pm{#sqrt{#Chi^{2}}}");
    pullWSmD0->GetYaxis()->SetTitle("#pm{#sqrt{#Chi^{2}}}");
    pullWSdm->GetYaxis()->SetTitle("#pm{#sqrt{#Chi^{2}}}");

    TPaveText *boxmd0 = new TPaveText(1.5,1.5,1.7,1.7,"");
    boxmd0->AddText("b)");
    TPaveText *boxdm = new TPaveText(1.5,1.5,1.7,1.7,"");
    boxdm->AddText("c)");

    boxdm->SetFillColor(10);
    boxmd0->SetFillColor(10);

    TArrow* arr_dm1 = new TArrow(0.1449,400.,0.1449,260.);
    TArrow* arr_dm2 = new TArrow(0.1459,400.,0.1459,260.);

    TArrow* arr_m1 = new TArrow(1.8495,420.,1.8495,275.);
    TArrow* arr_m2 = new TArrow(1.8795,420.,1.8795,275.);

    dmframeWS->addObject(arr_dm1);
    dmframeWS->addObject(arr_dm2);
    mframeWS->addObject(arr_m1);
    mframeWS->addObject(arr_m2);

    TCanvas c1;
    //c1.Divide(2,1);
    c1.cd();c1.cd()->SetLogy(0);mframeRS->Draw();
    c1.SaveAs("RSmassFit_md0.eps");

    TCanvas c2;
    //p.SetBaBarLabel(-1,-1,-1,"preliminary");
    c2.cd();c2.cd()->SetLogy(0);dmframeRS->Draw();
    //p.SetBaBarLabel(-1,-1,-1,"preliminary");
    c2.SaveAs("RSmassFit_dm.eps");

    mframeWS->GetYaxis()->SetTitleOffset(1.3);
    dmframeWS->GetYaxis()->SetTitleOffset(1.3);

    TCanvas c3("c3","c3",300,300);
    //c2.Divide(2,1);
    c3.cd();mframeWS->Draw();                     boxmd0->Draw("SAME");
    //p.SetBaBarLabel(-1,-1,-1,"preliminary");
    c3.SaveAs("WSmassFit_md0.eps");

    TCanvas c4("c4","c4",300,300);
    //TCanvas c2_1("WSmass","WSmass",800,800);
    c4.cd();dmframeWS->Draw();                   boxdm->Draw("SAME");
    c4.SaveAs("WSmassFit_dm.eps");

    /*
      c2.cd(2);dmframeWS->Draw();
      //p.SetBaBarLabel(-1,-1,-1,"preliminary");
      c2.SaveAs("WSmassFit.eps");

      mframeRS->GetXaxis()->SetRangeUser(1.,100000.);
      dmframeRS->GetXaxis()->SetRangeUser(1.,500000.);
   
      TCanvas c3;
      c3.Divide(2,1);
      c3.cd(1);c3.cd(1)->SetLogy(1);mframeRS->Draw();
      c3.cd(2);c3.cd(2)->SetLogy(1);dmframeRS->Draw();
      c3.SaveAs("RSmassFit_log.eps");
    */
    TCanvas c5;
    //c5.Divide(2,1);
    c5.cd();pullRSmD0->Draw();
    c5.SaveAs("RSmasspull_md0.eps");

    TCanvas c6;
    c6.cd();pullRSdm->Draw();
    c6.SaveAs("RSmasspull_dm.eps");

    TCanvas c7;
    //c6.Divide(2,1);
    c7.cd();pullWSmD0->Draw();
    c7.SaveAs("WSmasspull_md0.eps");

    TCanvas c8;
    c8.cd();pullWSdm->Draw();
    c8.SaveAs("WSmasspull_dm.eps");
   
  }

  if(doMC){
    isWS.setIndex(0,kTRUE);
    truthIsBkg_BadOtherD0.setIndex(1,kTRUE);
    truthIsBkg_SwappedKpi.setIndex(1,kTRUE);
    truthIsBkg_BadDplus.setIndex(1,kTRUE);
    truthIsSignal.setIndex(0,kTRUE);

    RooPlot* mframeRSbad = d0Mass.frame();
    finaldata->plotOn(mframeRSbad,MarkerSize(0.1),DrawOption("z"),Cut("deltaMass > 0.1449 && deltaMass < 0.1459 && isWS==isWS::RS && truthIsSignal==truthIsSignal::nosig && truthIsBkg_FakePiSlow==truthIsBkg_FakePiSlow::nomis"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(mframeRSbad,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totbadD0RS,nonpeakRS)),ProjectionRange("signal_region"));
    mframeRSbad->getAttLine()->SetLineWidth(1);
    mframeRSbad->getAttLine()->SetLineStyle(1);
    mframeRSbad->SetTitle("bad D^{0} m_{D^{0}} distribution for RS MC");
    mframeRSbad->GetXaxis()->SetTitle("m_{D^{0}} (GeV/c^{2})");

    RooPlot* dmframeRSbad = deltaMass.frame();
    finaldata->plotOn(dmframeRSbad,MarkerSize(0.1),DrawOption("z"),Cut("d0Mass < 1.8795 && d0Mass > 1.8495 && isWS==isWS::RS && truthIsSignal==truthIsSignal::nosig && truthIsBkg_FakePiSlow==truthIsBkg_FakePiSlow::nomis"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(dmframeRSbad,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totbadD0RS,nonpeakRS)),ProjectionRange("signal_region"));
    dmframeRSbad->getAttLine()->SetLineWidth(1);
    dmframeRSbad->getAttLine()->SetLineStyle(1);
    dmframeRSbad->SetTitle("bad D^{0} #Delta m distribution for RS MC");
    dmframeRSbad->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");

    isWS.setIndex(1,kTRUE);

    RooPlot* mframeWSbad = d0Mass.frame();
    finaldata->plotOn(mframeWSbad,MarkerSize(0.1),DrawOption("z"),Cut("deltaMass > 0.1449 && deltaMass < 0.1459 && isWS==isWS::WS && truthIsSignal==truthIsSignal::nosig && truthIsBkg_FakePiSlow==truthIsBkg_FakePiSlow::nomis"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(mframeWSbad,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totbadD0WS,nonpeakWS)),ProjectionRange("signal_region"));
    mframeWSbad->getAttLine()->SetLineWidth(1);
    mframeWSbad->getAttLine()->SetLineStyle(1);
    mframeWSbad->SetTitle("bad D^{0} m_{D^{0}} distribution for WS MC");
    mframeWSbad->GetXaxis()->SetTitle("m_{D^{0}} (GeV/c^{2})");

    RooPlot* dmframeWSbad = deltaMass.frame();
    finaldata->plotOn(dmframeWSbad,MarkerSize(0.1),DrawOption("z"),Cut("d0Mass < 1.8795 && d0Mass > 1.8495 && isWS==isWS::WS && truthIsSignal==truthIsSignal::nosig && truthIsBkg_FakePiSlow==truthIsBkg_FakePiSlow::nomis"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(dmframeWSbad,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totbadD0WS,nonpeakWS)),ProjectionRange("signal_region"));
    dmframeWSbad->getAttLine()->SetLineWidth(1);
    dmframeWSbad->getAttLine()->SetLineStyle(1);
    dmframeWSbad->SetTitle("bad D^{0} #Delta m distribution for WS MC");
    dmframeWSbad->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");

    isWS.setIndex(0,kTRUE);
    truthIsBkg_FakePiSlow.setIndex(1,kTRUE);

    RooPlot* mframeRSmis = d0Mass.frame();
    finaldata->plotOn(mframeRSmis,MarkerSize(0.1),DrawOption("z"),Cut("deltaMass > 0.1449 && deltaMass < 0.1459 && isWS==isWS::RS && truthIsBkg_FakePiSlow==truthIsBkg_FakePiSlow::mis && truthIsBkg_Comb==truthIsBkg_Comb::nocomb"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(mframeRSmis,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totmisRS)),ProjectionRange("signal_region"));
    mframeRSmis->getAttLine()->SetLineWidth(1);
    mframeRSmis->getAttLine()->SetLineStyle(1);
    mframeRSmis->SetTitle("mistag m_{D^{0}} distribution for RS MC");
    mframeRSmis->GetXaxis()->SetTitle("m_{D^{0}} (GeV/c^{2})");
    mframeRSmis->SetMaximum(700.);

    RooPlot* dmframeRSmis = deltaMass.frame();
    finaldata->plotOn(dmframeRSmis,MarkerSize(0.1),DrawOption("z"),Cut("d0Mass < 1.8795 && d0Mass > 1.8495 && isWS==isWS::RS && truthIsBkg_FakePiSlow==truthIsBkg_FakePiSlow::mis && truthIsBkg_Comb==truthIsBkg_Comb::nocomb"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(dmframeRSmis,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totmisRS)),ProjectionRange("signal_region"));
    dmframeRSmis->getAttLine()->SetLineWidth(1);
    dmframeRSmis->getAttLine()->SetLineStyle(1);
    dmframeRSmis->SetTitle("mistag #Delta m distribution for RS MC");
    dmframeRSmis->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");
    dmframeRSmis->SetMaximum(1200.);

    isWS.setIndex(1,kTRUE);

    RooPlot* mframeWSmis = d0Mass.frame();
    finaldata->plotOn(mframeWSmis,MarkerSize(0.1),DrawOption("z"),Cut("deltaMass > 0.1449 && deltaMass < 0.1459 && isWS==isWS::WS && truthIsBkg_FakePiSlow==truthIsBkg_FakePiSlow::mis"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(mframeWSmis,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totmisWS)),ProjectionRange("signal_region"));
    mframeWSmis->getAttLine()->SetLineWidth(1);
    mframeWSmis->getAttLine()->SetLineStyle(1);
    mframeWSmis->SetTitle("mistag m_{D^{0}} distribution for WS MC");
    mframeWSmis->GetXaxis()->SetTitle("m_{D^{0}} (GeV/c^{2})");

    RooPlot* dmframeWSmis = deltaMass.frame();
    finaldata->plotOn(dmframeWSmis,MarkerSize(0.1),DrawOption("z"),Cut("d0Mass < 1.8795 && d0Mass > 1.8495 && isWS==isWS::WS && truthIsBkg_FakePiSlow==truthIsBkg_FakePiSlow::mis"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(dmframeWSmis,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totmisWS)),ProjectionRange("signal_region"));
    dmframeWSmis->getAttLine()->SetLineWidth(1);
    dmframeWSmis->getAttLine()->SetLineStyle(1);
    dmframeWSmis->SetTitle("mistag #Delta m distribution for WS MC");
    dmframeWSmis->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");

    isWS.setIndex(0,kTRUE);
    truthIsSignal.setIndex(1,kTRUE);

    RooPlot* mframeRSsig = d0Mass.frame();
    finaldata->plotOn(mframeRSsig,MarkerSize(0.1),DrawOption("z"),Cut("deltaMass > 0.1449 && deltaMass < 0.1459 && isWS==isWS::RS && truthIsSignal==truthIsSignal::sig"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(mframeRSsig,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totsig)),ProjectionRange("signal_region"));
    mframeRSsig->getAttLine()->SetLineWidth(1);
    mframeRSsig->getAttLine()->SetLineStyle(1);
    mframeRSsig->SetTitle("Signal m_{D^{0}} distribution for RS MC");
    mframeRSsig->GetXaxis()->SetTitle("m_{D^{0}} (GeV/c^{2})");

    RooPlot* dmframeRSsig = deltaMass.frame();
    finaldata->plotOn(dmframeRSsig,MarkerSize(0.1),DrawOption("z"),Cut("d0Mass < 1.8795 && d0Mass > 1.8495 && isWS==isWS::RS && truthIsSignal==truthIsSignal::sig"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(dmframeRSsig,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totsig)),ProjectionRange("signal_region"));
    dmframeRSsig->getAttLine()->SetLineWidth(1);
    dmframeRSsig->getAttLine()->SetLineStyle(1);
    dmframeRSsig->SetTitle("Signal #Delta m distribution for RS MC");
    dmframeRSsig->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");

    isWS.setIndex(1,kTRUE);

    RooPlot* mframeWSsig = d0Mass.frame();
    finaldata->plotOn(mframeWSsig,MarkerSize(0.1),DrawOption("z"),Cut("deltaMass > 0.1449 && deltaMass < 0.1459 && isWS==isWS::WS && truthIsSignal==truthIsSignal::sig"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(mframeWSsig,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totsig)),ProjectionRange("signal_region"));
    mframeWSsig->getAttLine()->SetLineWidth(1);
    mframeWSsig->getAttLine()->SetLineStyle(1);
    mframeWSsig->SetTitle("Signal m_{D^{0}} distribution for WS MC");
    mframeWSsig->GetXaxis()->SetTitle("m_{D^{0}} (GeV/c^{2})");

    RooPlot* dmframeWSsig = deltaMass.frame();
    finaldata->plotOn(dmframeWSsig,MarkerSize(0.1),DrawOption("z"),Cut("d0Mass < 1.8795 && d0Mass > 1.8495 && isWS==isWS::WS && truthIsSignal==truthIsSignal::sig"),DataError(RooAbsData::SumW2));
    TOTpdf.plotOn(dmframeWSsig,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(totsig)),ProjectionRange("signal_region"));
    dmframeWSsig->getAttLine()->SetLineWidth(1);
    dmframeWSsig->getAttLine()->SetLineStyle(1);
    dmframeWSsig->SetTitle("Signal #Delta m distribution for WS MC");
    dmframeWSsig->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");

    /*
      isWS.setIndex(0,kTRUE);
      truthIsBkg_Comb.setIndex(1,kTRUE);

      RooPlot* mframeRScomb = d0Mass.frame(50);
      finaldata->plotOn(mframeRScomb,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::RS && truthIsBkg_Comb==truthIsBkg_Comb::comb"));
      TOTpdf.plotOn(mframeRScomb,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS)));
      mframeRScomb->getAttLine()->SetLineWidth(1);
      mframeRScomb->getAttLine()->SetLineStyle(1);

      RooPlot* dmframeRScomb = deltaMass.frame(50);
      finaldata->plotOn(dmframeRScomb,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::RS && truthIsBkg_Comb==truthIsBkg_Comb::comb"));
      TOTpdf.plotOn(dmframeRScomb,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS)));
      dmframeRScomb->getAttLine()->SetLineWidth(1);
      dmframeRScomb->getAttLine()->SetLineStyle(1);

      isWS.setIndex(1,kTRUE);

      RooPlot* mframeWScomb = d0Mass.frame(50);
      finaldata->plotOn(mframeWScomb,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::WS && truthIsBkg_Comb==truthIsBkg_Comb::comb"));
      TOTpdf.plotOn(mframeWScomb,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS)));
      mframeWScomb->getAttLine()->SetLineWidth(1);
      mframeWScomb->getAttLine()->SetLineStyle(1);

      RooPlot* dmframeWScomb = deltaMass.frame(50);
      finaldata->plotOn(dmframeWScomb,MarkerSize(0.1),DrawOption("z"),Cut("isWS==isWS::WS && truthIsBkg_Comb==truthIsBkg_Comb::comb"));
      TOTpdf.plotOn(dmframeWScomb,ProjWData(*db_dummy),Slice(RooArgSet(isWS)),Components(RooArgSet(nonpeakWS)));
      dmframeWScomb->getAttLine()->SetLineWidth(1);
      dmframeWScomb->getAttLine()->SetLineStyle(1);
    */
    TCanvas cbad;
    cbad.Divide(2,2);
    cbad.cd(1);mframeRSbad->Draw();
    cbad.cd(2);mframeWSbad->Draw();
    cbad.cd(3);dmframeRSbad->Draw();
    cbad.cd(4);dmframeWSbad->Draw();
    cbad.SaveAs("mdm_bkg_bad.eps");
    /*
      TCanvas ccomb;
      ccomb.Divide(2,2);
      ccomb.cd(1);mframeRScomb->Draw();
      ccomb.cd(2);mframeWScomb->Draw();
      ccomb.cd(3);dmframeRScomb->Draw();
      ccomb.cd(4);dmframeWScomb->Draw();
      ccomb.SaveAs("mdm_bkg_comb.eps");
    */
    TCanvas cmis;
    cmis.Divide(2,2);
    cmis.cd(1);mframeRSmis->Draw();
    cmis.cd(2);mframeWSmis->Draw();
    cmis.cd(3);dmframeRSmis->Draw();
    cmis.cd(4);dmframeWSmis->Draw();
    cmis.SaveAs("mdm_bkg_mis.eps");

    TCanvas csig;
    csig.Divide(2,2);
    csig.cd(1);csig.cd(1)->SetLogy(1);mframeRSsig->Draw();
    csig.cd(2);csig.cd(2)->SetLogy(0);mframeWSsig->Draw();
    csig.cd(3);csig.cd(3)->SetLogy(1);dmframeRSsig->Draw();
    csig.cd(4);csig.cd(4)->SetLogy(0);dmframeWSsig->Draw();
    csig.SaveAs("mdm_bkg_sig.eps");
  }
  return 0;
}
