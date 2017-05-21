void ToyKs(char* filename,Int_t nexp,Int_t nev,Int_t SEED,Double_t c1val, Double_t c2val)
{
  //set the seed and the generator used by EvtGen
  RooRandom::randomGenerator()->SetSeed(SEED);
  cout << "  Toy seed ............. " << (RooRandom::randomGenerator()->GetSeed()) << endl;

  Bool_t doGen = kFALSE;
  Bool_t doFit = kTRUE;
  Bool_t extract = kTRUE;

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  RooRealVar tau("tau","tau",0.4101,0.4,0.5);
  RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
  RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
  RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",-2.,4.);
  RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",0.2,0.,0.5);
  RooCategory D0flav("D0flav","D0flav");
  D0flav.defineType("D0",-1);
  D0flav.defineType("antiD0",1);

  RooRealVar bias("bias","bias",0.01,-1.,1.);
  RooRealVar scalefact1("scalefact1","scalefact1",1.060,0.5,2.2);
  RooRealVar scalefact2("scalefact2","scalefact2",0.925,0.5,2.2);
  RooRealVar scalefact3("scalefact3","scalefact3",1.950,0.5,2.2);

  tau.setConstant(kTRUE);
  bias.setConstant(kTRUE);
  scalefact1.setConstant(kTRUE);
  scalefact2.setConstant(kTRUE);
  scalefact3.setConstant(kTRUE);

  RooRealVar c1("c1","c1",c1val,-10.,10.);
  RooRealVar c2("c2","c2",c2val,-10.,10.);

  //consider the resolution or the truth model
  RooGaussModel gm1("gm1","gauss model 1",d0Lifetime,bias,scalefact1,d0LifetimeErr) ;
  RooGaussModel gm2("gm2","gauss model 2",d0Lifetime,bias,scalefact2,d0LifetimeErr) ;
  RooGaussModel gm3("gm3","gauss model 3",d0Lifetime,bias,scalefact3,d0LifetimeErr) ;
  //RooTruthModel gm("gm","truth model",d0Lifetime);

  RooRealVar N1("N1","N1",0.45,0.001,0.99);
  RooRealVar N2("N2","N2",0.40,0.001,0.99);
  RooRealVar N3("N3","N3",0.15,0.001,0.99);
  RooRealVar N23("N23","N23",0.72,0.001,0.99);

  N1.setConstant(kTRUE);
  N2.setConstant(kTRUE);
  N3.setConstant(kTRUE);
  N23.setConstant(kTRUE);

  RooFormulaVar f2("f2","f2","(1-@0)*@1",RooArgList(N1,N23));
  RooFormulaVar f3("f3","f3","(1-@0)*(1-@1)",RooArgList(N1,N23));
  RooAddModel gm("gm","gm",RooArgList(gm2,gm3,gm1),RooArgList(f2,f3));

  RooTimepdfKs TOTTime("TOTTime","TOTTime",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,c1,c2,-1);
  RooTimepdfKs antiTOTTime("antiTOTTime","antiTOTTime",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,c1,c2,1);
  RooSimultaneous TOTsig("TOTsig","TOTsig",D0flav);
  TOTsig.addPdf(TOTTime,"D0");
  TOTsig.addPdf(antiTOTTime,"antiD0");

  //////////////////////////
  // BACKGROUND
  /////////////////////////

  //Mistag parametrization
  RooTimepdfKs TOTmistag("TOTmistag","TOTmistag",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,kFALSE,tau);

  //Combinatoric + bad-D0
  RooRealVar mean1("mean1","mean1",0.110372008,-0.5,0.5);
  RooRealVar mean2("mean2","mean2",0.343663025,-0.5,0.5);
  RooRealVar sigma1("sigma1","sigma1",0.291380654,0.,1.);
  RooRealVar sigma2("sigma2","sigma2",0.587107779,0.,1.);
  RooRealVar alpha("alpha","alpha",-1.4475246,-4.,4.);
  RooRealVar ncb("ncb","ncb",8.77316837,1.,40.);
  RooRealVar fcomb("fcomb","fcomb",0.518422142,0.,1.);

  ncb.setConstant(kTRUE);
  alpha.setConstant(kFALSE);
  fcomb.setConstant(kFALSE);
  mean1.setConstant(kFALSE);
  mean2.setConstant(kFALSE);
  sigma1.setConstant(kFALSE);
  sigma2.setConstant(kFALSE);

  RooGaussian gausscomb("gausscomb","gausscomb",d0Lifetime,mean1,sigma1);
  RooCBShape cbcomb("cbcomb","cbcomb",d0Lifetime,mean2,sigma2,alpha,ncb);
  RooAddPdf combtime("combtime","combtime",RooArgList(gausscomb,cbcomb),RooArgList(fcomb));

  RooBkg combdalitz("combdalitz","combdalitz",m2Kpi_d0mass,m2Kpi0_d0mass,&dalitzSpace);

  RooProdPdf Totcomb("Totcomb","Totcomb",combtime,combdalitz);

  Float_t totnonorm = 868. + 253. + 1057.;
  Float_t ratio = nev/totnonorm;
  Float_t fracBkgMis = 253./(253.+1057.);
  Float_t fracSig = 868./totnonorm;

  //RooRealVar Nsig("Nsig","Nsig",1288.81668);
  RooRealVar Nsig("Nsig","Nsig",868.*ratio,10.,10000.);
  //RooRealVar Nmis("Nmis","Nmis",2707.41282);
  RooRealVar Nmis("Nmis","Nmis",253.*ratio,10.,10000.);
  //RooRealVar Ncomb("Ncomb","Ncomb",29000.);
  RooRealVar Ncomb("Ncomb","Ncomb",1057.*ratio,10.,10000.);
  RooRealVar Nbkg("Nbkg","Nbkg",(253.+1057.)*ratio,50.,4000.);

  RooRealVar fracBkg("fracBkg","fracBkg",fracBkgMis,0.0001,0.5);
  RooRealVar fracNsig("fracNsig","fracNsig",fracSig,0.01,0.7);

  Nsig.setConstant(kFALSE);
  Nbkg.setConstant(kFALSE);
  fracBkg.setConstant(kFALSE);
  fracNsig.setConstant(kFALSE);

  RooRealVar g1("g1","g1",868./(868.+253.+1057.),0.1,0.8);
  RooRealVar g2("g2","g2",253./(868.+253.+1057.),0.,0.5);
  RooRealVar g3("g3","g3",1057./(868.+253.+1057.));

  //Signal + background
  //RooAddPdf TOTBkg("TOTBkg","TOTBkg",RooArgList(TOTmistag,Totcomb),RooArgList(fracBkg));
  //RooAddPdf TOTpdf("TOTpdf","TOTpdf",RooArgList(TOTTime,TOTBkg),RooArgList(Nsig,Nbkg));
  RooAddPdf TOTpdf("TOTpdf","TOTpdf",RooArgList(TOTsig,TOTmistag,Totcomb),RooArgList(Nsig,Nmis,Ncomb));

  //select the RS dataset to get the pseudo-generated per-event errors and D0 flavor
  RooArgSet observ(d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass);
  RooArgSet condition(d0LifetimeErr,D0flav);

  TFile RSfile("DataSet_RS_all.root");
  gROOT->cd();
  RooDataSet *RSdata = (RooDataSet*)RSfile.Get("fulldata");
  RooDataSet *RSdata_1 = (RooDataSet*)RSdata->reduce("d0Mass > 1.86 && d0Mass < 1.87");
  RooDataSet *RSdata_2 = (RooDataSet*)RSdata_1->reduce("deltaMass > 0.1453 && deltaMass < 0.1455");
  RooDataSet *RSdata_3 = (RooDataSet*)RSdata_2->reduce("d0LifetimeErr < 0.5");
  RooDataSet *Proto = (RooDataSet*)RSdata_3->reduce(condition);
  Int_t numProto = Proto->numEntries();
  Int_t start = TMath::Nint(numProto/2. - nev/2.);
  RooDataSet *ConditDataset = (RooDataSet*)Proto->reduce(EventRange(start,start+nev-1));

  RooMCStudy mgr(TOTpdf,observ,FitOptions(ConditionalObservables(condition),Save(1),Minos(0),Hesse(1),Extended(1)),Extended(1),ProtoData(*ConditDataset,1));

  TString dataname(filename);
  dataname.Append(".dat");
  TString toyname(filename);
  toyname.Append(".root");

  if(doGen && !doFit) mgr.generate(nexp,nev,kFALSE,dataname);
  if(doFit && !doGen) mgr.fit(nexp,dataname);
  if(doGen && doFit) mgr.generateAndFit(nexp,nev,kFALSE,dataname);

  RooDataSet mypar = mgr.fitParDataSet();
 
  const RooFitResult *theRes = mgr.fitResult(0);

  TFile *f = new TFile(toyname,"RECREATE");
  f->cd();
  mypar.Write();
  f->Close();

  if(extract){

    RooRealVar myc1("myc1","myc1",-10.,10.);
    RooRealVar myc2("myc2","myc2",-10.,10.);
    RooRealVar myratio("myratio","myratio",0.,0.,1.);
    RooRealVar myx("myx","myx",0.,-1.,1.);
    RooRealVar myy("myy","myy",0.,-1.,1.);

    RooDataSet *parFloat = new RooDataSet("parFloat","parFloat",RooArgList(myratio,myx,myy));

    for(Int_t j=0;j<200;j++){
      cout << "Performing step number " << j << endl;
      RooArgList floated = theRes->randomizePars();
      myc1.setVal(((RooAbsReal*)floated.at(9))->getVal());
      myc2.setVal(((RooAbsReal*)floated.at(10))->getVal());

      RooTimepdfKs mysigD0("mysigD0","mysigD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,myc1,myc2,-1);

      Double_t myDenom = mysigD0.createIntegral(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime))->getVal();
      Double_t myNum = RooRandom::randomGenerator()->Gaus(0.00234,0.00005);

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

  /*  
     RooPlot* time = d0Lifetime.frame();
     TOTpdf.plotOn(time,Project(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass)));
     //D0timefit1.plotOn(time,ProjWData(RooArgSet(D0flav,d0LifetimeErr),*RSdata_proto));


     RooPlot* xframe = m2Kpi_d0mass.frame();
     //TOTpdf.plotOn(xframe,Project(RooArgSet(d0Lifetime,m2Kpi0_d0mass)));
     //D0timefit1.plotOn(xframe,ProjWData(RooArgSet(D0flav,d0LifetimeErr),*RSdata_proto));

     RooPlot* yframe = m2Kpi0_d0mass.frame();
     //TOTpdf.plotOn(yframe,Project(RooArgSet(d0Lifetime,m2Kpi_d0mass)));
     //D0timefit1.plotOn(yframe,ProjWData(RooArgSet(D0flav,d0LifetimeErr),*RSdata_proto));

     //RooPlot* zframe = m2pipi0_d0mass.frame();
     //D0timefit1_23.plotOn(zframe,Project(RooArgSet(d0Lifetime,m2Kpi_d0mass)));
     //D0timefit1_23.plotOn(zframe,ProjWData(RooArgSet(D0flav,d0LifetimeErr),*RSdata_proto));

     //TH2 *pdf2d = m2Kpi_d0mass.createHistogram("pdf2d",m2Kpi0_d0mass);
     //TOTpdf.fillHistogram(pdf2d,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));
  
     TCanvas *can = new TCanvas();
     can->Divide(2,2);
     can->cd(1);
     //pdf2d->Draw("SURF");
     //can->cd(2);xframe->Draw();
     //can->cd(3);yframe->Draw();
     //can->cd(3);zframe->Draw();
     can->cd(4);time->Draw();
     can->SaveAs("TimeToy.eps");
  */

}
