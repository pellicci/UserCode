{

//macro to perform the time-independent dalitz fit of the RS sample
// decay is D0 -> K- pi+ pi0
//          antiD0 -> K+ pi- pi0

// REMEMBER:  m12 -> m^2(K-,pi+)
//            m13 -> m^2(K-,pi0)

gStyle->SetOptStat(0);
RooRandom::randomGenerator()->SetSeed(3);
RooEvtRandom eng;
EvtRandom::setRandomEngine(&eng);

Bool_t doNorm=kFALSE;
Bool_t do3DHistos=kFALSE;
Bool_t doFit=kTRUE;
Bool_t doComparison=kFALSE;
Bool_t doHel=kFALSE;
Bool_t doFract=kFALSE;
Bool_t doPlots=kTRUE;

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

RooRealVar d0Mass("d0Mass","d0Mass",d0lower,d0upper);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",m12lower,m12upper);
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",m13lower,m13upper);
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",m23lower,m23upper);
RooRealVar eff_weight("eff_weight","eff_weight",weiglower,weigupper);
RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);

//read in the dataset
TFile hello("DataSet_RS_all.root");
gROOT->cd();
RooDataSet *finaldata = (RooDataSet*)hello.Get("fulldata");
//RooDataSet *finaldata = data->reduce("d0Mass > 1.875 && d0Mass < 1.88");

//here we set the weights for the dataset
finaldata->setWeightVar(eff_weight);

//define DalitzSpace for generation
EvtPDL pdl;
pdl.readPDT("evt.pdl");
EvtDecayMode mode("D0 -> K- pi+ pi0");
EvtDalitzPlot dalitzSpace(mode);

//define boundaries of RooRealVars wrt the data
Double_t low12,hig12,low13,hig13,low23,hig23;

Bool_t m12bool = finaldata->getRange(m2Kpi_d0mass,low12,hig12);
Bool_t m13bool = finaldata->getRange(m2Kpi0_d0mass,low13,hig13);
Bool_t m23bool = finaldata->getRange(m2pipi0_d0mass,low23,hig23);
m2Kpi_d0mass.setRange(low12,hig12);
m2Kpi0_d0mass.setRange(low13,hig13);
m2pipi0_d0mass.setRange(low23,hig23);

//if you want to have a little dataset to test, uncomment next line and rename finaldata above
//RooDataSet *finaldata = finaldata_1->reduce(EventRange(1,10000));
RooDataSet *D0data = finaldata->reduce("D0flav==-1");
RooDataSet *antiD0data = finaldata->reduce("D0flav==1");

cout << "*************************************************************" << endl;
cout << "The final data entry    " << finaldata->numEntries() << endl;
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
//careful: D0 is -1, antiD0 is 1
RooKpipi0pdf D0pdf("D0pdf","D0pdf",m2Kpi_d0mass,m2Kpi0_d0mass,-1,0,&dalitzSpace);
RooKpipi0pdf D0pdf23("D0pdf23","D0pdf23",m2Kpi_d0mass,mass13a,-1,0,&dalitzSpace);

RooKpipi0pdf antiD0pdf("antiD0pdf","antiD0pdf",m2Kpi_d0mass,m2Kpi0_d0mass,1,0,&dalitzSpace);
RooKpipi0pdf antiD0pdf23("antiD0pdf23","antiD0pdf23",m2Kpi_d0mass,mass13a,1,0,&dalitzSpace);

RooSimultaneous sigpdf("sigpdf","sigpdf",D0flav);
sigpdf.addPdf(D0pdf,"D0");
sigpdf.addPdf(antiD0pdf,"antiD0");

RooSimultaneous sigpdf23("sigpdf23","sigpdf23",D0flav);
sigpdf23.addPdf(D0pdf23,"D0");
sigpdf23.addPdf(antiD0pdf23,"antiD0");

RooRealVar N_sig("N_sig","N_sig",252969.55);

//*********************************
//   BACKGROUND
//*********************************
//here we deal with background

//Combinatoric
//for combinatoric background we use a PDF which is flat in Dalitz Plot
RooBkg comb_bkg("comb_bkg","comb_bkg",m2Kpi_d0mass,m2Kpi0_d0mass);
RooBkg comb_bkg23("comb_bkg23","comb_bkg23",m2Kpi_d0mass,mass13a);
RooBkg anticomb_bkg("anticomb_bkg","anticomb_bkg",m2Kpi_d0mass,m2Kpi0_d0mass);
RooBkg anticomb_bkg23("anticomb_bkg23","anticomb_bkg23",m2Kpi_d0mass,mass13a);

RooSimultaneous combpdf("combpdf","combpdf",D0flav);
combpdf.addPdf(comb_bkg,"D0");
combpdf.addPdf(anticomb_bkg,"antiD0");

RooSimultaneous combpdf23("combpdf23","combpdf23",D0flav);
combpdf23.addPdf(comb_bkg23,"D0");
combpdf23.addPdf(anticomb_bkg23,"antiD0");

//here we set the quantity of combinatoric background in signal region
//this was extracted before from the deltaM and mD0 fit
RooRealVar N_comb("N_comb","N_comb",2308.45);

//Compose pdf adding the non-interferring terms
//RooAddPdf tot_pdf("tot_pdf","tot_pdf",RooArgList(sigpdf,combpdf),RooArgSet(N_sig,N_comb));
//RooAddPdf tot_pdf23("tot_pdf23","tot_pdf23",RooArgList(sigpdf23,combpdf23),RooArgSet(N_sig,N_comb));
RooAddPdf tot_pdf("tot_pdf","tot_pdf",RooArgList(D0pdf,comb_bkg),RooArgSet(N_sig,N_comb));
RooAddPdf tot_pdf23("tot_pdf23","tot_pdf23",RooArgList(D0pdf23,comb_bkg23),RooArgSet(N_sig,N_comb));

cout << "For M12 we are using bins " << m2Kpi_d0mass.getBins() << endl;
cout << "For M13 we are using bins " << m2Kpi0_d0mass.getBins() << endl;

cout << "about to init" << endl;

if(doNorm) D0pdf.getManager()->calNorm();
if(doNorm) antiD0pdf.getManager()->calNorm();

Float_t norm_D0 = D0pdf.getManager()->getNormalization();
Float_t norm_antiD0 = antiD0pdf.getManager()->getNormalization();
cout << "***********************************" << endl;
cout << "The norm is   " << norm_D0 << endl;
cout << "(for D0bar is " << norm_antiD0 << ")" << endl;
cout << "***********************************" << endl;

//here is where we really fit  RIGHT NOW JUST DOING D0 FIT (NO ANTID0)
if(doFit) {
  RooFitResult* fitRes = tot_pdf.fitTo(*finaldata,,Minos(0),Save(1));

  //save the result of the fit
  fitRes.Print("v");
  RooArgSet results(fitRes->floatParsFinal());
  RooArgSet conresults(fitRes->constPars());
  results.add(conresults);
  results->writeToFile("fit_isobar_RS.txt");

  //save the stupid result
  TFile f("fit_RS_result.root","RECREATE");
  fitRes.Write();
  f.Close();

  if(doFract) {
    //now calculate the fit fractions
    Int_t nRes = D0pdf.getManager()->nRes;
    RooRealVar normarray[nRes+1][nRes+1];
    RooRealVar normD0Var("normD0Var","normD0Var",norm);
    TH1F fitty[nRes];

    //read the integral value from the cache file.
    //In this way we don't need to compute the normalization everytime during MIGRAD
    char int_name[50];
    D0pdf.getManager()->getFileName(int_name);

    ifstream f1;
    f1.open(int_name);
    if (!f1){
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
	f1 >> re >> im;       
        normarray[j][k]= RooRealVar("re","re",re);
      }
    }   

    for(Int_t l=0;l<500;l++){
      RooArgList listpar = fitRes->randomizePars();

      //now calculate the fit fractions
      for(Int_t i=0;i<2*nRes;i+2){
        fitfrac[i/2] = RooFormulaVar("","abs2(@0*@1)/@2",RooArgSet(listpar[i],normarray[i/2][i/2],normD0Var));
        fitty[i/2].Fill(fitfrac[i/2]);
      }
    }// nexperiments

    for(Int_t i=0;i<nRes;i++){
      fitty[i].Fit("gaus","","",0.,1.);
    }

    cout << "///////////////////////////" << endl;
  }

}

if(doPlots){
//Make the plots
// REMEBER: if you want roofit to consider the reweighted errors, you must put DataError(RooAbsData::SumW2))
//******************************************************
RooPlot* xframe = m2Kpi_d0mass.frame(150);
finaldata->plotOn(xframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
//sigpdf.plotOn(xframe,ProjWData(D0flav,*finaldata));
tot_pdf.plotOn(xframe);
xframe->getAttLine()->SetLineWidth(1);
xframe->getAttLine()->SetLineStyle(1);
Double_t chi2Kpi = xframe->chiSquare();

RooPlot* yframe = m2Kpi0_d0mass.frame(150);
finaldata->plotOn(yframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
//sigpdf.plotOn(yframe,ProjWData(D0flav,*finaldata));
tot_pdf.plotOn(yframe);
yframe->getAttLine()->SetLineWidth(1);
yframe->getAttLine()->SetLineStyle(1);
Double_t chi2Kpi0 = yframe->chiSquare();

RooPlot* zframe = m2pipi0_d0mass.frame(150);
finaldata->plotOn(zframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
//sigpdf23.plotOn(zframe,ProjWData(D0flav,*finaldata));
tot_pdf23.plotOn(zframe); 
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
c1->SaveAs("RSsigfit.eps");

}

//here we do the partial wave analysis stuff
if(doHel){
  RooDataSet *small = finaldata->reduce("d0Mass < 1.88 && d0Mass > 1.79");
  D0pdf.getManager()->helicityangle(small);

  RooDataSet* toyset = D0pdf.generate(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),small->numEntries());
  D0pdf.getManager()->helicityangle(toyset);

  TFile *fil = new TFile("prova.root","RECREATE");
  fil->cd(); toyset->Write(); 
  fil->Close();

  TCanvas *hel = new TCanvas("hel","allevents");
  hel->Divide(2,3);
  hel->cd(1);
  toyset->tree()->Draw("m2Kpi_d0mass","cos12");
  small->tree()->Draw("m2Kpi_d0mass","cos12","esame");    //plot Y_10
  hel->cd(2);
  toyset->tree()->Draw("m2Kpi0_d0mass","cos13");
  small->tree()->Draw("m2Kpi0_d0mass","cos13","esame");

  hel->cd(3);
  toyset->tree()->Draw("m2Kpi_d0mass","0.5*(3*cos12*cos12-1)");
  small->tree()->Draw("m2Kpi_d0mass","0.5*(3*pow(cos12,2)-1)","esame");  //plot Y_20
  hel->cd(4);
  toyset->tree()->Draw("m2Kpi0_d0mass","0.5*(3*cos13*cos13-1)");
  small->tree()->Draw("m2Kpi0_d0mass","0.5*(3*pow(cos13,2)-1)","esame");

  hel->cd(5);
  toyset->tree()->Draw("m2Kpi_d0mass","5*pow(cos12,3)-3*cos12");
  small->tree()->Draw("m2Kpi_d0mass","5*pow(cos12,3)-3*cos12","esame");  //plot Y_30
  hel->cd(6);
  toyset->tree()->Draw("m2Kpi0_d0mass","5*pow(cos13,3)-3*cos13");
  small->tree()->Draw("m2Kpi0_d0mass","5*pow(cos13,3)-3*cos13","esame");

 hel->SaveAs("partialRS.eps");

 TCanvas *hel2 = new TCanvas("hel2","allevents");
  hel2->Divide(2,3);

  hel2->cd(1);
  toyset->tree()->Draw("m2Kpi_d0mass","35*pow(cos12,4)-27*pow(cos12,2)+3");
  small->tree()->Draw("m2Kpi_d0mass","35*pow(cos12,4)-27*pow(cos12,2)+3","esame");  //plot Y_40
  hel2->cd(2);
  toyset->tree()->Draw("m2Kpi0_d0mass","35*pow(cos13,4)-27*pow(cos13,2)+3");
  small->tree()->Draw("m2Kpi0_d0mass","35*pow(cos13,4)-27*pow(cos13,2)+3","esame");

  hel2->cd(3);
  toyset->tree()->Draw("m2Kpi_d0mass","63*pow(cos12,5)-70*pow(cos12,3)+15*cos12");
  small->tree()->Draw("m2Kpi_d0mass","63*pow(cos12,5)-70*pow(cos12,3)+15*cos12","esame");  //plot Y_50
  hel2->cd(4);
  toyset->tree()->Draw("m2Kpi0_d0mass","63*pow(cos13,5)-70*pow(cos13,3)+15*cos13");
  small->tree()->Draw("m2Kpi0_d0mass","63*pow(cos13,5)-70*pow(cos13,3)+15*cos13","esame");

  hel2->cd(5);
  toyset->tree()->Draw("m2Kpi_d0mass","231*pow(cos12,6)-315*pow(cos12,4)+105*pow(cos12,2)-5");
  small->tree()->Draw("m2Kpi_d0mass","231*pow(cos12,6)-315*pow(cos12,4)+105*pow(cos12,2)-5","esame");    //plot Y_60
  hel2->cd(6);
  toyset->tree()->Draw("m2Kpi0_d0mass","231*pow(cos13,6)-315*pow(cos13,4)+105*pow(cos13,2)-5");
  small->tree()->Draw("m2Kpi0_d0mass","231*pow(cos13,6)-315*pow(cos13,4)+105*pow(cos13,2)-5","esame");    //plot Y_60

 hel2->SaveAs("partialRS2.eps");

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
  c2->SaveAs("RSweights.eps");
}

}//end of the macro

