{
gROOT->Reset();

Bool_t doFit=kTRUE;

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

Float_t weiglower = -50;
Float_t weigupper = 50;

Float_t sweiglower = -100;
Float_t sweigupper = 100;

Float_t timelow = -50.;
Float_t timehigh = 50.;

Float_t total=md0*md0+mk*mk+mpi*mpi+mpi0*mpi0;
RooRealVar totalm("totalm","totalm",total);

RooRealVar d0Mass("d0Mass","d0Mass",d0lower,d0upper);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",m12lower,m12upper);
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",m13lower,m13upper);
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",m23lower,m23upper);
RooRealVar weight("weight","weight",weiglower,weigupper);
RooRealVar eff_weight("eff_weight","eff_weight",weiglower,weigupper);
RooRealVar nSigXW_sWeight("nSigXW_sWeight","nSigXW_sWeight",sweiglower,sweigupper);
RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);
RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",timelow,timehigh);
RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",timelow,timehigh);

RooRealVar scalefact1("scalefact1","scalefact1",1.060,0.5,2.2);
RooRealVar scalefact2("scalefact2","scalefact2",0.925,0.5,2.2);
RooRealVar scalefact3("scalefact3","scalefact3",1.950,0.5,2.2);

RooRealVar x("x","x",0.0,-0.5,0.5);
RooRealVar y("y","y",0.0,-0.5,0.5);

scalefact1.setConstant(kTRUE);
scalefact2.setConstant(kTRUE);
scalefact3.setConstant(kTRUE);

//read in the dataset
TFile hello("DataSet_WS_all.root");
gROOT->cd();
RooDataSet *data = (RooDataSet*)hello.Get("fulldata");
RooDataSet *data2 = data->reduce("d0LifetimeErr < 0.5");
RooDataSet *fulldata = data2->reduce("d0Lifetime < 3.5 && d0Lifetime > -1.5");

//here you can set the per-event weight. Work still in progess...
fulldata->setWeightVar(nSigXW_sWeight);

cout << "*************************************************************" << endl;
cout << "The final data entry    " << fulldata->numEntries() << endl;
cout << "*************************************************************" << endl;

//Construct signal pdf
RooFormulaVar coeff1("coeff1","@0*@1",RooArgSet(scalefact1,d0LifetimeErr));
RooFormulaVar coeff2("coeff2","@0*@1",RooArgSet(scalefact2,d0LifetimeErr));
RooFormulaVar coeff3("coeff3","@0*@1",RooArgSet(scalefact3,d0LifetimeErr));

RooTimepdf D0timefit1("D0timefit1","D0timefit1",d0Lifetime,coeff1,m2Kpi_d0mass,m2Kpi0_d0mass,1);
RooTimepdf antiD0timefit1("antiD0timefit1","antiD0timefit1",d0Lifetime,coeff1,m2Kpi_d0mass,m2Kpi0_d0mass,-1);
RooSimultaneous sigpdf1("sigpdf1","sigpdf1",D0flav);
sigpdf1.addPdf(D0timefit1,"D0");
sigpdf1.addPdf(antiD0timefit1,"antiD0");

RooRealVar N_sig1("N_sig1","N_sig1",0.33,0.,1.);

RooTimepdf D0timefit2("D0timefit2","D0timefit2",d0Lifetime,coeff2,m2Kpi_d0mass,m2Kpi0_d0mass,1);
RooTimepdf antiD0timefit2("antiD0timefit2","antiD0timefit2",d0Lifetime,coeff2,m2Kpi_d0mass,m2Kpi0_d0mass,-1);
RooSimultaneous sigpdf2("sigpdf2","sigpdf2",D0flav);
sigpdf2.addPdf(D0timefit2,"D0");
sigpdf2.addPdf(antiD0timefit2,"antiD0");

RooRealVar N_sig2("N_sig2","N_sig2",0.33,0.,1.);

RooTimepdf D0timefit3("D0timefit3","D0timefit3",d0Lifetime,coeff3,m2Kpi_d0mass,m2Kpi0_d0mass,1);
RooTimepdf antiD0timefit3("antiD0timefit3","antiD0timefit3",d0Lifetime,coeff3,m2Kpi_d0mass,m2Kpi0_d0mass,-1);
RooSimultaneous sigpdf3("sigpdf3","sigpdf3",D0flav);
sigpdf3.addPdf(D0timefit3,"D0");
sigpdf3.addPdf(antiD0timefit3,"antiD0");

RooFormulaVar N_sig3("N_sig3","1-@0-@1",RooArgSet(N_sig1,N_sig2));

//here we set the limits for the fit
Double_t lowt,hight,lowterr,highterr;
Bool_t tbool = fulldata->getRange(d0Lifetime,lowt,hight);
Bool_t terrbool = fulldata->getRange(d0LifetimeErr,lowterr,highterr);
d0Lifetime.setRange(lowt,hight);
d0LifetimeErr.setRange(lowterr,highterr);

RooAddPdf tot_pdf("tot_pdf","tot_pdf",RooArgList(D0timefit1,D0timefit2,D0timefit3),RooArgSet(N_sig1,N_sig2,N_sig3));

//When we plot the 1D projection, need to calculate the 1D integral
//set the precision here
cout << "config integrator " << endl;
RooNumIntConfig* cfg = RooAbsReal::defaultIntegratorConfig();
cfg->setEpsAbs(1E-4);
cfg->setEpsRel(1E-4);
cfg->method1D().setLabel("RooSegmentedIntegrator1D");
cfg->getConfigSection("RooSegmentedIntegrator1D")->setRealValue("numSeg",40);
//cfg->method1D()->Print("v");
D0timefit1.setIntegratorConfig(*cfg);
antiD0timefit1.setIntegratorConfig(*cfg);
D0timefit2.setIntegratorConfig(*cfg);
antiD0timefit2.setIntegratorConfig(*cfg);
D0timefit3.setIntegratorConfig(*cfg);
antiD0timefit3.setIntegratorConfig(*cfg);

//here is where we really fit
//if(doFit) RooFitResult* fitRes = tot_pdf.fitTo(*fulldata,"HRM");

RooPlot* tframe = d0Lifetime.frame(lowt,hight);
fulldata->plotOn(tframe,MarkerSize(0.1),DrawOption("z"));
tot_pdf.plotOn(tframe);
//tot_pdf.plotOn(tframe);
//tot_pdf.plotOn(tframe,ProjWData(RooArgSet(D0flav),*fulldata));
tframe->getAttLine()->SetLineWidth(1);
tframe->getAttLine()->SetLineStyle(1);

TCanvas *c1 = new TCanvas();
c1->cd();tframe->Draw();
c1->SaveAs("WStimefit.eps");

}
