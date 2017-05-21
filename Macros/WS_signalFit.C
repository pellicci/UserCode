{
//macro to perform the time-independent dalitz fit of the WS sample
// decay is D0 -> K+ pi- pi0
//          antiD0 -> K- pi+ pi0

// REMEMBER:  m12 -> m^2(K+,pi-)
//            m13 -> m^2(K+,pi0)

gStyle->SetOptStat(0);

Bool_t doNorm=kTRUE;
Bool_t do3DHistos=kFALSE;
Bool_t doFit=kFALSE;
Bool_t doComparison=kFALSE;
Bool_t d0Hel=kFALSE;
Bool_t doFitFract=kFALSE;

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

Float_t sweiglower = -100;
Float_t sweigupper = 100;

Float_t total=md0*md0+mk*mk+mpi*mpi+mpi0*mpi0;
RooRealVar totalm("totalm","totalm",total);

RooRealVar d0Mass("d0Mass","d0Mass",d0lower,d0upper);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",m12lower,m12upper);
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",m13lower,m13upper);
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",m23lower,m23upper);
RooRealVar eff_weight("eff_weight","eff_weight",weiglower,weigupper);
RooRealVar nSigXW_sWeight("nSigXW_sWeight","nSigXW_sWeight",sweiglower,sweigupper);
RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);

//read in the dataset
TFile hello("DataSet_WS_all.root");
gROOT->cd();
RooDataSet *fulldata = (RooDataSet*)hello.Get("fulldata");

//use this if you want to combine efficiency weight and s-weight
RooFormulaVar weight("weight","@0*@1",RooArgSet(eff_weight,nSigXW_sWeight));
fulldata->addColumn(weight);

//here you can set the per-event weight. Work still in progess...
fulldata->setWeightVar(0);

//define DalitzSpace for generation
EvtPDL pdl;
pdl.readPDT("evt.pdl");
EvtDecayMode mode("D0 -> K+ pi- pi0");
EvtDalitzPlot dalitzSpace(mode);

//define boundaries of RooRealVars wrt the data
Double_t low12,hig12,low13,hig13,low23,hig23;

Bool_t m12bool = fulldata->getRange(m2Kpi_d0mass,low12,hig12);
Bool_t m13bool = fulldata->getRange(m2Kpi0_d0mass,low13,hig13);
Bool_t m23bool = fulldata->getRange(m2pipi0_d0mass,low23,hig23);
m2Kpi_d0mass.setRange(low12,hig12);
m2Kpi0_d0mass.setRange(low13,hig13);
m2pipi0_d0mass.setRange(low23,hig23);

//if you want to have a little dataset to test, uncomment next line and rename fulldata above
//RooDataSet *fulldata = fulldata_1->reduce(EventRange(1,10000));
RooDataSet *D0data = fulldata->reduce("D0flav==-1");
RooDataSet *antiD0data = fulldata->reduce("D0flav==1");

cout << "*************************************************************" << endl;
cout << "The full data entry    " << fulldata->numEntries() << endl;
cout << "*************************************************************" << endl;
cout << "*************************************************************" << endl;
cout << "The D0 data entry    " << D0data->numEntries() << endl;
cout << "*************************************************************" << endl;
cout << "*************************************************************" << endl;
cout << "The anti D0 data entry    " << antiD0data->numEntries() << endl;
cout << "*************************************************************" << endl;

//this is just to plot the m23 pdf
RooFormulaVar mass13a("mass13a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2pipi0_d0mass));

//Construct signal pdf
//Construct signal pdf
//careful: D0 is -1, antiD0 is 1
RooKpipi0pdf D0pdf("D0pdf","D0pdf",m2Kpi_d0mass,m2Kpi0_d0mass,-1,1,&dalitzSpace);
RooKpipi0pdf D0pdf23("D0pdf23","D0pdf23",m2Kpi_d0mass,mass13a,-1,1,&dalitzSpace);

RooKpipi0pdf antiD0pdf("antiD0pdf","antiD0pdf",m2Kpi_d0mass,m2Kpi0_d0mass,1,1,&dalitzSpace);
RooKpipi0pdf antiD0pdf23("antiD0pdf23","antiD0pdf23",m2Kpi_d0mass,mass13a,1,1,&dalitzSpace);

RooSimultaneous sigpdf("sigpdf","sigpdf",D0flav);
sigpdf.addPdf(D0pdf,"D0");
sigpdf.addPdf(antiD0pdf,"antiD0");

RooSimultaneous sigpdf23("sigpdf23","sigpdf23",D0flav);
sigpdf23.addPdf(D0pdf23,"D0");
sigpdf23.addPdf(antiD0pdf23,"antiD0");

cout << "For M12 we are using bins " << m2Kpi_d0mass.getBins() << endl;
cout << "For M13 we are using bins " << m2Kpi0_d0mass.getBins() << endl;

//When we plot the 1D projection, need to calculate the 1D integral
//set the precision here
cout << "config integrator " << endl;

  RooNumIntConfig* cfg = RooAbsReal::defaultIntegratorConfig();
  cfg->setEpsAbs(1E-4);
  cfg->setEpsRel(1E-4);
  cfg->method1D().setLabel("RooSegmentedIntegrator1D");
//cfg->getConfigSection("RooSegmentedIntegrator1D")->setRealValue("numSeg",40);
  //cfg->method1D()->Print("v");
  D0pdf.setIntegratorConfig(*cfg);
  D0pdf23.setIntegratorConfig(*cfg);
  antiD0pdf.setIntegratorConfig(*cfg);
  antiD0pdf23.setIntegratorConfig(*cfg);

cout << "about to init" << endl;

if(doNorm) D0pdf.getManager()->calNorm();
if(doNorm) antiD0pdf.getManager()->calNorm();

Float_t norm = D0pdf.getManager()->getNormalization();
Float_t norm_antiD0 = antiD0pdf.getManager()->getNormalization();
cout << "***********************************" << endl;
cout << "The norm is   " << norm << endl;
cout << "(for D0bar is " << norm_antiD0 << ")" << endl;
cout << "***********************************" << endl;

//here is where we really fit  RIGHT NOW JUST DOING D0 FIT (NO ANTID0)
if(doFit) {
  RooFitResult* fitRes = D0pdf.fitTo(*fulldata,"SHRMT");

  //save the result of the fit
  fitRes.Print("v");
  RooArgSet results(fitRes->floatParsFinal());
  RooArgSet conresults(fitRes->constPars());
  results.add(conresults);
  results->writeToFile("fit_isobar_WS.txt");

  //save the stupid result
  TFile f("fit_WS_result.root","RECREATE");
  fitRes.Write();
  f.Close();

  if(doFitFract){
    Int_t nRes = D0pdf.getManager()->nRes;
    TH1F fitty[nRes];
    RooRealVar normarray[nRes+1][nRes+1];
    RooRealVar normD0Var("normD0Var","normD0Var",norm);

    //read the integral value from the cache file.
    char int_name[50];
    D0pdf.getManager()->getFileName(int_name);
    ifstream fs;
    fs.open(int_name);
    if (!fs){
      cout << "Error opening file " << endl;
      assert(0);
    }
  
    Double_t re=0.,im=0.;
    //Read in the cache file and store back to array
    for(Int_t j=1;j<=nRes;j++) {
      char thname[100];
      sprintf(thname,"thname_%d",j);
      fitty[j] = TH1F(thname,thname,30,0.,1.);
      for(Int_t k=1;k<=nRes;k++){
	fs >> re >> im;       
	normarray[j][k]= RooRealVar("re","re",re);
      }
    }   

    for(Int_t l=0;l<500;l++){
      RooArgList listpar = fitRes->randomizePars();

      //now calculate the fit fractions
      for(Int_t i=0;i<2*nRes;i+2){
	fitfrac[i/2] = RooFormulaVar("","abs2(@0*@1)/@2",RooArgSet(listpar[i]));
	fitty[i/2].Fill(fitfrac[i/2]);
      }
    }// nexperiments

    for(Int_t i=0;i<nRes;i++){
      fitty[i].Fit("gaus","","",0.,1.);
    }
  }
}


//Make the plots
// REMEBER: if you want roofit to consider the reweighted errors, you must put DataError(RooAbsData::SumW2))
//******************************************************
RooPlot* xframe = m2Kpi_d0mass.frame(); //30
fulldata->plotOn(xframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
//sigpdf.plotOn(xframe,ProjWData(D0flav,*fulldata));
D0pdf.plotOn(xframe);
xframe->getAttLine()->SetLineWidth(1);
xframe->getAttLine()->SetLineStyle(1);
Double_t chi2Kpi = xframe->chiSquare();

RooPlot* yframe = m2Kpi0_d0mass.frame(110); //17
fulldata->plotOn(yframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
//sigpdf.plotOn(yframe,ProjWData(D0flav,*fulldata));
D0pdf.plotOn(yframe);
yframe->getAttLine()->SetLineWidth(1);
yframe->getAttLine()->SetLineStyle(1);
Double_t chi2Kpi0 = yframe->chiSquare();

RooPlot* zframe = m2pipi0_d0mass.frame()   //0.15,1.9); //35
fulldata->plotOn(zframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
//sigpdf23.plotOn(zframe,ProjWData(D0flav,*fulldata));
D0pdf23.plotOn(zframe);
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
c1->SaveAs("WSsigfit.eps");

//plots for weights studies
if(do3DHistos){
  TH3F* eff_mKpi = m2Kpi_d0mass.createHistogram("mKpi_sq vs efficiency",m2Kpi0_d0mass,eff_weight,"prova");
  dataplots.fillHistogram(eff_mKpi,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,eff_weight));
  TH3F* eff_mpipi0 = m2pipi0_d0mass.createHistogram("mpipi0_sq vs efficiency",m2Kpi_d0mass,eff_weight,"prova");
  dataplots.fillHistogram(eff_mpipi0,RooArgList(m2pipi0_d0mass,m2Kpi_d0mass,eff_weight));

  TH3F* sw_mKpi = m2Kpi_d0mass.createHistogram("mKpi_sq vs s_weight",m2Kpi0_d0mass,nSigXR_sWeight,"prova");
  dataplots.fillHistogram(sw_mKpi,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass,nSigXR_sWeight));
  TH3F* sw_mpipi0 = m2pipi0_d0mass.createHistogram("mpipi0_sq vs s_weight",m2Kpi_d0mass,nSigXR_sWeight,"prova");
  dataplots.fillHistogram(sw_mpipi0,RooArgList(m2pipi0_d0mass,m2Kpi_d0mass,nSigXR_sWeight));

  TCanvas *c2 = new TCanvas("c2","allevents");
  c2->Divide(2,2);
  c2->cd(1);eff_mKpi->Draw("ISO");
  c2->cd(2);eff_mpipi0->Draw("ISO");
  c2->cd(3);sw_mKpi->Draw("ISO");
  c2->cd(4);sw_mpipi0->Draw("ISO");
  c2->SaveAs("weights.eps");
}

}//end of the macro

