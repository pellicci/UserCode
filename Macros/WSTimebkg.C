{

//macro to perform the time-independent dalitz fit of the RS sample
// decay is D0 -> K- pi+ pi0
//          antiD0 -> K+ pi- pi0

// REMEMBER:  m12 -> m^2(K-,pi+)
//            m13 -> m^2(K-,pi0)

gStyle->SetOptStat(0);
//RooRandom::randomGenerator()->SetSeed(3);
//RooEvtRandom eng;
//EvtRandom::setRandomEngine(&eng);

Bool_t doTFit = kTRUE;
Bool_t dorightFit = kFALSE;
Bool_t doleftFit = kFALSE;
Bool_t doMergedFit = kFALSE;

Bool_t doComparison = kFALSE;
Bool_t checkTdep = kFALSE;

//calculate the dalitz boundary
Float_t md0 = 1.8645;
Float_t mk = 0.493677;
Float_t mpi0 = 0.1349766;
Float_t mpi = 0.13957018;

Float_t m12upper=pow(md0-mpi0,2);
Float_t m12lower=pow(mk+mpi,2);

Float_t m13upper=pow(md0-mpi,2);
Float_t m13lower=pow(mk+mpi0,2);

Float_t m23lower=pow(mpi+mpi0,2);
Float_t m23upper=pow(md0-mk,2);

Float_t d0lower = 1.74;
Float_t d0upper = 1.99;

Float_t weiglower = -100;
Float_t weigupper = 100;

Float_t total=md0*md0+mk*mk+mpi*mpi+mpi0*mpi0;
RooRealVar totalm("totalm","totalm",total);

RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",-3.,4.5);
RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",0.,0.5);
RooRealVar d0Mass("d0Mass","d0Mass",d0lower,d0upper);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",m12lower,m12upper);
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",m13lower,m13upper);
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",m23lower,m23upper);

RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);

//read in the dataset
TFile hello("DataSet_WS_all.root");
gROOT->cd();
RooDataSet *data = (RooDataSet*)hello.Get("fulldata");
RooDataSet *data_1 = data->reduce("d0LifetimeErr < 0.5");

RooDataSet *tdata = data_1->reduce("d0Mass < 1.79 || d0Mass > 1.92");
RooDataSet *leftdata = data_1->reduce("d0Mass > 1.76 && d0Mass < 1.79");
RooDataSet *rightdata = data_1->reduce("d0Mass > 1.92 && d0Mass < 1.95");

//if you want to have a little dataset to test, uncomment next line and rename finaldata above
//RooDataSet *finaldata = finaldata_1->reduce(EventRange(1,100));

//here we set the weights for the dataset
tdata->setWeightVar(0);
rightdata->setWeightVar(0);
leftdata->setWeightVar(0);

//define DalitzSpace for generation
EvtPDL pdl;
pdl.readPDT("evt.pdl");
EvtDecayMode mode("D0 -> K- pi+ pi0");
EvtDalitzPlot dalitzSpace(mode);

//define boundaries of RooRealVars wrt the data
Double_t low12,hig12,low13,hig13,low23,hig23,lowt,higt;

Bool_t m12bool = tdata->getRange(m2Kpi_d0mass,low12,hig12);
Bool_t m13bool = tdata->getRange(m2Kpi0_d0mass,low13,hig13);
Bool_t m23bool = tdata->getRange(m2pipi0_d0mass,low23,hig23);
Bool_t tbool = tdata->getRange(d0Lifetime,lowt,higt);
m2Kpi_d0mass.setRange(low12,hig12);
m2Kpi0_d0mass.setRange(low13,hig13);
m2pipi0_d0mass.setRange(low23,hig23);
d0Lifetime.setRange(lowt,higt);

cout << "*************************************************************" << endl;
cout << "The time fit  data events " << tdata->numEntries() << endl;
cout << "*************************************************************" << endl;
cout << "*************************************************************" << endl;
cout << "The right data events " << rightdata->numEntries() << endl;
cout << "*************************************************************" << endl;
cout << "*************************************************************" << endl;
cout << "The left data entry " << leftdata->numEntries() << endl;
cout << "*************************************************************" << endl;

//this is just to plot the m23 pdf
RooFormulaVar mass13a("mass13a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2pipi0_d0mass));

cout << "For M12 we are using bins " << m2Kpi_d0mass.getBins() << endl;
cout << "For M13 we are using bins " << m2Kpi0_d0mass.getBins() << endl;

if(doTFit){
  ///////////////////////////////////
  // LIFETIME DISTRIBUTION BACKGROUND
  ///////////////////////////////////

  //FIRST THE COMBINATORIC
  RooRealVar mean1("mean1","mean1",0.110372008,-1.,1.);
  RooRealVar mean2("mean2","mean2",0.343663025,-1.,1.);
  RooRealVar sigma1("sigma1","sigma1",0.291380654,0.,4.);
  RooRealVar sigma2("sigma2","sigma2",0.587107779,0.,4.);
  RooRealVar alpha("alpha","alpha",-1.4475246,-4.,4.);
  RooRealVar ncb("ncb","ncb",8.77316837,6.,10.);
  RooRealVar fcomb("fcomb","fcomb",0.518422142,0.,1.);

  ncb.setConstant(kFALSE);

  RooGaussian gausscomb("gausscomb","gausscomb",d0Lifetime,mean1,sigma1);
  RooCBShape cbcomb("cbcomb","cbcomb",d0Lifetime,mean2,sigma2,alpha,ncb);
  RooAddPdf combtime("combtime","combtime",RooArgList(gausscomb,cbcomb),RooArgList(fcomb));

  //THEN THE "BAD"-D0 BACKGROUND
  
    RooRealVar taub("taub","taub",0.357104096,0.1,0.5);
    RooRealVar scalefact1("scalefact1","scalefact1",1.060,0.5,2.2);
    RooRealVar scalefact2("scalefact2","scalefact2",0.925,0.5,2.2);
    RooRealVar scalefact3("scalefact3","scalefact3",1.950,0.5,2.2);
    RooRealVar bias("bias","bias",0.) ;

    scalefact1.setConstant(kTRUE);
    scalefact2.setConstant(kTRUE);
    scalefact3.setConstant(kTRUE);

    //first the resolution model
    RooGaussModel gm1("gm1","gauss model 1",d0Lifetime,bias,scalefact1,d0LifetimeErr) ;
    RooGaussModel gm2("gm2","gauss model 2",d0Lifetime,bias,scalefact2,d0LifetimeErr) ;
    RooGaussModel gm3("gm3","gauss model 3",d0Lifetime,bias,scalefact3,d0LifetimeErr) ;

    RooRealVar N1("N1","N1",0.536182748,0.,1.);
    RooRealVar N2("N2","N2",0.429210085,0.,1.);
    N1.setConstant(kTRUE);
    N2.setConstant(kTRUE);

    RooFormulaVar f2("f2","f2","(1-@0)*@1",RooArgList(N1,N2));
    RooFormulaVar f3("f3","f3","(1-@0)*(1-@1)",RooArgList(N1,N2));

    RooAddModel gm("gm","gm",RooArgList(gm1,gm2,gm3),RooArgList(N1,N2));
    RooTimeMistag TOTTMistag("TOTTMistag","TOTTMistag",d0Lifetime,taub,gm);

    //now mix all the backgrounds
    RooRealVar N_comb("N_comb","N_comb",2.49598548e+04);
    RooRealVar N_brok("N_brok","N_brok",4.12582765e+03);
    RooFormulaVar brokfrac("brokfrac","@0/(@0+@1)",RooArgList(N_comb,N_brok));

    RooAddPdf TotTime("TotTime","TotTime",RooArgList(combtime,TOTTMistag),RooArgList(brokfrac));
  

  RooFitResult* fitRes = combtime.fitTo(*tdata,Minos(0),Save(1));
  //save the result of the fit
  fitRes.Print("v");
  RooArgSet results(fitRes->floatParsFinal());
  RooArgSet conresults(fitRes->constPars());
  results.add(conresults);
  results->writeToFile("fit_timebkg.txt");
  //save the stupid result
  TFile f("fit_timebkg.root","RECREATE");
  fitRes.Write();
  f.Close();

  RooPlot* tframe = d0Lifetime.frame(80);
  tdata->plotOn(tframe,MarkerSize(0.1),DrawOption("z"));
  combtime.plotOn(tframe);
  tframe->getAttLine()->SetLineWidth(1);
  tframe->getAttLine()->SetLineStyle(1);
  Double_t chi2time = tframe->chiSquare();
  cout << "Chi2 for D0 lifetime = " << chi2time << endl;

  TCanvas *c2 = new TCanvas();
  c2->cd();tframe->Draw();
  c2->SaveAs("WStimefit_bkg2.eps");
}

if(dorightFit){
  RooBkg combdalitz("combdalitz","combdalitz",m2Kpi_d0mass,m2Kpi0_d0mass,&dalitzSpace);
  RooBkg combdalitz23("combdalitz23","combdalitz23",m2Kpi_d0mass,mass13a,&dalitzSpace);

  Float_t norm_D0 = combdalitz.getManager()->getNormalization();
  cout << "***********************************" << endl;
  cout << "The norm is   " << norm_D0 << endl;
  cout << "***********************************" << endl;
  /*
  //here is where we really fit
  RooFitResult* rightfitRes = combdalitz.fitTo(*rightdata,Minos(0),Save(1));

  //save the result of the fit
  rightfitRes.Print("v");
  RooArgSet results(rightfitRes->floatParsFinal());
  RooArgSet conresults(rightfitRes->constPars());
  results.add(conresults);
  results->writeToFile("fit_rightbkg.txt");

  //save the stupid result
  TFile f("fit_rightbkg.root","RECREATE");
  rightfitRes.Write();
  f.Close();
  */
  //When we plot the 1D projection, need to calculate the 1D integral
  //set the precision here
  RooNumIntConfig *cfg = RooAbsReal::defaultIntegratorConfig();
  cfg->setEpsAbs(1E-4);
  cfg->setEpsRel(1E-4);
  cfg->method1D().setLabel("RooSegmentedIntegrator1D");
  //cfg->getConfigSection("RooIntegrator1D").setRealValue("maxSteps",100);
  combdalitz.setIntegratorConfig(*cfg);

  RooPlot* xframe = m2Kpi_d0mass.frame(50);
  rightdata->plotOn(xframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz.plotOn(xframe);
  xframe->getAttLine()->SetLineWidth(1);
  xframe->getAttLine()->SetLineStyle(1);
  Double_t chi2Kpi = xframe->chiSquare();

  RooPlot* yframe = m2Kpi0_d0mass.frame(50);
  rightdata->plotOn(yframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz.plotOn(yframe);
  yframe->getAttLine()->SetLineWidth(1);
  yframe->getAttLine()->SetLineStyle(1);
  Double_t chi2Kpi0 = yframe->chiSquare();

  RooPlot* zframe = m2pipi0_d0mass.frame(50);
  rightdata->plotOn(zframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz23.plotOn(zframe); 
  zframe->getAttLine()->SetLineWidth(1);
  zframe->getAttLine()->SetLineStyle(1);
  Double_t chi2pipi0 = zframe->chiSquare();

  cout << "Chi2 for Kpi = " << chi2Kpi << endl;
  cout << "Chi2 for Kpi0 = " << chi2Kpi0 << endl;
  cout << "Chi2 for pipi0 = " << chi2pipi0 << endl;

  TCanvas *c1 = new TCanvas("c1","allevents",1200,400);
  c1->Divide(3,1);
  c1->cd(1);xframe->Draw();
  c1->cd(2);yframe->Draw();
  c1->cd(3);zframe->Draw();
  c1->SaveAs("WStimefit_bkg_right.eps");

  RooDataSet *rightgen = combdalitz.generate(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),100000);
  RooDataSet *rightgen23 = combdalitz23.generate(RooArgSet(m2Kpi_d0mass,m2pipi0_d0mass),100000);
  RooDataSet *reduced23 = rightgen23->reduce(RooArgSet(m2pipi0_d0mass));
  rightgen->merge(reduced23);

  TFile f("rightbkggen.root","RECREATE");
  f.cd();rightgen->Write();
  f.Close();
}

if(doleftFit){
  RooBkg combdalitz("combdalitz","combdalitz",m2Kpi_d0mass,m2Kpi0_d0mass,&dalitzSpace);
  RooBkg combdalitz23("combdalitz23","combdalitz23",m2Kpi_d0mass,mass13a,&dalitzSpace);

  Float_t norm_D0 = combdalitz.getManager()->getNormalization();
  cout << "***********************************" << endl;
  cout << "The norm is   " << norm_D0 << endl;
  cout << "***********************************" << endl;
  /*
  //here is where we really fit
  RooFitResult* leftfitRes = combdalitz.fitTo(*leftdata,Minos(0),Save(1));

  //save the result of the fit
  leftfitRes.Print("v");
  RooArgSet results(leftfitRes->floatParsFinal());
  RooArgSet conresults(leftfitRes->constPars());
  results.add(conresults);
  results->writeToFile("fit_leftbkg.txt");

  //save the stupid result
  TFile f("fit_leftbkg.root","RECREATE");
  leftfitRes.Write();
  f.Close();
  */
  //When we plot the 1D projection, need to calculate the 1D integral
  //set the precision here
  //cout << "config integrator " << endl;
  RooNumIntConfig *cfg = RooAbsReal::defaultIntegratorConfig();
  cfg->setEpsAbs(1E-4);
  cfg->setEpsRel(1E-4);
  cfg->method1D().setLabel("RooSegmentedIntegrator1D");
  //cfg->getConfigSection("RooIntegrator1D").setRealValue("maxSteps",100);
  //cfg->method1D()->Print("v");
  combdalitz.setIntegratorConfig(*cfg);

  RooPlot* xframe = m2Kpi_d0mass.frame(50);
  leftdata->plotOn(xframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz.plotOn(xframe);
  xframe->getAttLine()->SetLineWidth(1);
  xframe->getAttLine()->SetLineStyle(1);
  Double_t chi2Kpi = xframe->chiSquare();

  RooPlot* yframe = m2Kpi0_d0mass.frame(50);
  leftdata->plotOn(yframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz.plotOn(yframe);
  yframe->getAttLine()->SetLineWidth(1);
  yframe->getAttLine()->SetLineStyle(1);
  Double_t chi2Kpi0 = yframe->chiSquare();

  RooPlot* zframe = m2pipi0_d0mass.frame(50);
  leftdata->plotOn(zframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz23.plotOn(zframe); 
  zframe->getAttLine()->SetLineWidth(1);
  zframe->getAttLine()->SetLineStyle(1);
  Double_t chi2pipi0 = zframe->chiSquare();

  cout << "Chi2 for Kpi = " << chi2Kpi << endl;
  cout << "Chi2 for Kpi0 = " << chi2Kpi0 << endl;
  cout << "Chi2 for pipi0 = " << chi2pipi0 << endl;

  TCanvas *c1 = new TCanvas("c1","allevents",1200,400);
  c1->Divide(3,1);
  c1->cd(1);xframe->Draw();
  c1->cd(2);yframe->Draw();
  c1->cd(3);zframe->Draw();
  c1->SaveAs("WStimefit_bkg_left.eps)");

  RooDataSet *leftgen = combdalitz.generate(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),100000);
  RooDataSet *leftgen = combdalitz.generate(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),100000);
  RooDataSet *leftgen23 = combdalitz23.generate(RooArgSet(m2Kpi_d0mass,m2pipi0_d0mass),100000);
  RooDataSet *reduced23 = leftgen23->reduce(RooArgSet(m2pipi0_d0mass));
  leftgen->merge(reduced23);

  TFile f("leftbkggen.root","RECREATE");
  f.cd();leftgen->Write();
  f.Close();
}

if(doMergedFit){
  TFile *f1 = new TFile("leftbkggen.root");
  TFile *f2 = new TFile("rightbkggen.root");
  gROOT->cd();
  RooDataSet left = (RooDataSet)f1->Get("combdalitzData");
  RooDataSet right = (RooDataSet)f2->Get("combdalitzData");

  left.append(right);

  RooBkg combdalitz("combdalitz","combdalitz",m2Kpi_d0mass,m2Kpi0_d0mass,&dalitzSpace);
  RooBkg combdalitz23("combdalitz23","combdalitz23",m2Kpi_d0mass,mass13a,&dalitzSpace);

  Float_t norm_D0 = combdalitz.getManager()->getNormalization();
  cout << "***********************************" << endl;
  cout << "The norm is   " << norm_D0 << endl;
  cout << "***********************************" << endl;
  /*
  //here is where we really fit
  RooFitResult* fitRes = combdalitz.fitTo(left,Minos(0),Save(1));

  //save the result of the fit
  fitRes.Print("v");
  RooArgSet results(fitRes->floatParsFinal());
  RooArgSet conresults(fitRes->constPars());
  results.add(conresults);
  results->writeToFile("fit_mergedbkg.txt");

  //save the stupid result
  TFile f("fit_mergedbkg.root","RECREATE");
  fitRes.Write();
  f.Close();
  */
  //When we plot the 1D projection, need to calculate the 1D integral
  //set the precision here
  //cout << "config integrator " << endl;

  RooNumIntConfig *cfg = RooAbsReal::defaultIntegratorConfig();
  cfg->setEpsAbs(1E-4);
  cfg->setEpsRel(1E-4);
  cfg->method1D().setLabel("RooSegmentedIntegrator1D");
  //cfg->getConfigSection("RooIntegrator1D").setRealValue("maxSteps",100);
  //cfg->method1D()->Print("v");
  combdalitz.setIntegratorConfig(*cfg);

  RooPlot* xframe = m2Kpi_d0mass.frame(50);
  left.plotOn(xframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz.plotOn(xframe);
  xframe->getAttLine()->SetLineWidth(1);
  xframe->getAttLine()->SetLineStyle(1);
  Double_t chi2Kpi = xframe->chiSquare();

  RooPlot* yframe = m2Kpi0_d0mass.frame(50);
  left.plotOn(yframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz.plotOn(yframe);
  yframe->getAttLine()->SetLineWidth(1);
  yframe->getAttLine()->SetLineStyle(1);
  Double_t chi2Kpi0 = yframe->chiSquare();

  RooPlot* zframe = m2pipi0_d0mass.frame(50);
  left.plotOn(zframe,MarkerSize(0.1),DrawOption("z"));
  combdalitz23.plotOn(zframe); 
  zframe->getAttLine()->SetLineWidth(1);
  zframe->getAttLine()->SetLineStyle(1);
  Double_t chi2pipi0 = zframe->chiSquare();

  cout << "Chi2 for Kpi = " << chi2Kpi << endl;
  cout << "Chi2 for Kpi0 = " << chi2Kpi0 << endl;
  cout << "Chi2 for pipi0 = " << chi2pipi0 << endl;

  TCanvas *c1 = new TCanvas("c1","allevents",1200,400);
  c1->Divide(3,1);
  c1->cd(1);xframe->Draw();
  c1->cd(2);yframe->Draw();
  c1->cd(3);zframe->Draw();
  c1->SaveAs("WStimefit_bkg_merged.eps");
}

if(checkTdep){
  rightdata->append(*leftdata);
  RooDataSet *dataset_1 = rightdata->reduce("m2Kpi_d0mass < 1.");
  RooDataSet *dataset_2 = rightdata->reduce("m2Kpi0_d0mass < 1.");
  RooDataSet *dataset_3 = rightdata->reduce("m2Kpi0_d0mass > 1.&& m2Kpi_d0mass > 1.");

  TH1F *frame1 = new TH1F("frame1","frame1",20,-3.5,4.);
  TH1F *frame2 = new TH1F("frame2","frame2",20,-3.5,4.);
  TH1F *frame3 = new TH1F("frame3","frame3",20,-3.5,4.);

  dataset_1->fillHistogram(frame1,d0Lifetime);
  dataset_2->fillHistogram(frame2,d0Lifetime);
  dataset_3->fillHistogram(frame3,d0Lifetime);

  TH1F *frame3_1 = new TH1F("frame3_1","frame3_1",20,-3.5,4.);
  TH1F *frame3_2 = new TH1F("frame3_2","frame3_2",20,-3.5,4.);

  dataset_3->fillHistogram(frame3_1,d0Lifetime);
  dataset_3->fillHistogram(frame3_2,d0Lifetime);

  frame3_1->Scale(frame1->Integral()/frame3_1->Integral());
  frame3_2->Scale(frame2->Integral()/frame3_2->Integral());

  frame3_1->Add(frame1,-1);
  frame3_2->Add(frame2,-1);

  TCanvas c1,c2;

  c1.Divide(3,1);
  c1.cd(1);
  frame1->Draw();
  c1.cd(2);
  frame2->Draw();
  c1.cd(3);
  frame3->Draw();

  c2.Divide(2,1);
  c2.cd(1);
  frame3_1->Draw();
  c2.cd(2);
  frame3_2->Draw();

  c1.SaveAs("Timefit_Tdep.eps(");
  c2.SaveAs("Timefit_Tdep.eps)");
}

if(doComparison){
  gStyle->SetPalette(1);
  RooDataSet *littledata = fulldata->reduce("d0Mass > 1.855 && d0Mass < 1.875");
  RooArgSet VarList1(m2Kpi_d0mass,m2Kpi0_d0mass);
  Int_t num_entries = finaldata->numEntries();
  RooDataSet* genpdf = D0pdf.generate(VarList1,num_entries);

  TH2F* pdfhist = new TH2F("pdfhist","pdfhist",30,0.39,3.,30,0.39,3.);
  TH2F* datahist = new TH2F("datahist","datahist",30,0.39,3.,30,0.39,3.);
  pdfhist = genpdf->createHistogram(m2Kpi_d0mass,m2Kpi0_d0mass);
  datahist = finaldata->createHistogram(m2Kpi_d0mass,m2Kpi0_d0mass);
  pdfhist->GetXaxis()->SetTitle("m_{K#pi}^{2}");
  pdfhist->GetYaxis()->SetTitle("m_{K#pi^{0}}^{2}");

  pdfhist->Add(datahist,-1);

  TCanvas *c2 = new TCanvas("c2","difference between fit and data");
  c2->cd();pdfhist->Draw("SURF2Z");
  c2->SaveAs("RSsigdiff.eps");
}

}//end of the macro
