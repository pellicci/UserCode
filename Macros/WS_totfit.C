{
gROOT->Reset();

Bool_t doNorm=kTRUE;
Bool_t do3DHistos=kFALSE;
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

Float_t weiglower = 0.5;
Float_t weigupper = 4.5;

Float_t sweiglower = -2.2;
Float_t sweigupper = 2.7;

Float_t total=md0*md0+mk*mk+mpi*mpi+mpi0*mpi0;
RooRealVar totalm("totalm","totalm",total);

RooRealVar d0Mass("d0Mass","d0Mass",d0lower,d0upper);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",m12lower,m12upper);
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",m13lower,m13upper);
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",m23lower,m23upper);
RooRealVar weight("weight","weight",weiglower,weigupper);
RooRealVar eff_weight("eff_weight","eff_weight",weiglower,weigupper);
RooRealVar nSigXR_sWeight("nSigXR_sWeight","nSigXR_sWeight",sweiglower,sweigupper);
RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);

//read in the dataset
TFile hello("DataSet_WS_all.root");
gROOT->cd();
RooDataSet *fulldata = (RooDataSet*)hello.Get("fulldata");

//here you can set the per-event weight. Work still in progess...
fulldata->setWeightVar(0);

cout << "*************************************************************" << endl;
cout << "The final data entry    " << fulldata->numEntries() << endl;
cout << "*************************************************************" << endl;

RooFormulaVar mass13a("mass13a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2pipi0_d0mass));

//Construct signal pdf
//careful: D0 is 1, antid0 is -1. this is because efficiency for WS is opposite to RS
RooKpipi0pdf D0pdf("D0pdf","D0pdf",m2Kpi_d0mass,m2Kpi0_d0mass,1,1);  //using Kspi+ , Kspi- as dalitz variable
RooKpipi0pdf D0pdf23("D0pdf23","D0pdf23",m2Kpi_d0mass,mass13a,1,1); //Using Kspi+, pi+pi- as dalitz variable

RooKpipi0pdf antiD0pdf("antiD0pdf","antiD0pdf",m2Kpi_d0mass,m2Kpi0_d0mass,-1,1);  //using Kspi+ , Kspi- as dalitz variable
RooKpipi0pdf antiD0pdf23("antiD0pdf23","antiD0pdf23",m2Kpi_d0mass,mass13a,-1,1); //Using Kspi+, pi+pi- as dalitz variable 

RooSimultaneous sigpdf("sigpdf","sigpdf",D0flav);
sigpdf.addPdf(D0pdf,"D0");
sigpdf.addPdf(antiD0pdf,"antiD0");

RooSimultaneous sigpdf23("sigpdf23","sigpdf23",D0flav);
sigpdf23.addPdf(D0pdf23,"D0");
sigpdf23.addPdf(antiD0pdf23,"antiD0");

RooRealVar N_sig("N_sig","N_sig",867.53);

//Construct signal dataset
RooDataSet *data_1 = fulldata->reduce("d0Mass>1.82 && d0Mass<1.90");
RooDataSet *data = data_1->reduce("deltaMass>0.1444 && deltaMass<0.1464");
data->setWeightVar(0);

cout << "For M12 we are using bins " << m2Kpi_d0mass.getBins() << endl;
cout << "For M13 we are using bins " << m2Kpi0_d0mass.getBins() << endl;

cout << "*************************************************************" << endl;
cout << "The total signal entry    " << data->numEntries() << endl;
cout << "*************************************************************" << endl;

//here we set the limits for the fit
Double_t low12,high12,low13,high13,low23,high23;
Bool_t m12bool = data->getRange(m2Kpi_d0mass,low12,high12);
Bool_t m13bool = data->getRange(m2Kpi0_d0mass,low13,high13);
Bool_t m23bool = data->getRange(m2pipi0_d0mass,low23,high23);
m2Kpi_d0mass.setRange(low12,high12);
m2Kpi0_d0mass.setRange(low13,high13);
m2pipi0_d0mass.setRange(low23,high23);

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
RooRealVar N_comb("N_comb","N_comb",1057.52);

//Bad D* background. This is mainly due to the RS sample, hence we use its function to fit
RooKpipi0pdf peakbkg("peakbkg","peakbkg",m2Kpi_d0mass,m2Kpi0_d0mass,-1,0);  //using Kspi+ , Kspi- as dalitz variable
RooKpipi0pdf peakbkg23("peakbkg23","peakbkg23",m2Kpi_d0mass,mass13a,-1,0); //Using Kspi+, pi+pi- as dalitz variable

RooKpipi0pdf antipeakbkg("antipeakbkg","antipeakbkg",m2Kpi_d0mass,m2Kpi0_d0mass,1,0);  //using Kspi+ , Kspi-
RooKpipi0pdf antipeakbkg23("antipeakbkg23","antipeakbkg23",m2Kpi_d0mass,mass13a,1,0); //Using Kspi+, pi+pi- 

RooSimultaneous peakpdf("peakpdf","peakpdf",D0flav);
peakpdf.addPdf(peakbkg,"D0");
peakpdf.addPdf(antipeakbkg,"antiD0");

RooSimultaneous peakpdf23("peakpdf23","peakpdf23",D0flav);
peakpdf23.addPdf(peakbkg23,"D0");
peakpdf23.addPdf(antipeakbkg23,"antiD0");

RooRealVar N_peak("N_peak","N_peak",252.92);

//When we plot the 1D projection, need to calculate the 1D integral
//set the precision here
cout << "config integrator " << endl;
RooNumIntConfig* cfg = RooAbsReal::defaultIntegratorConfig();
cfg->setEpsAbs(1E-4);
cfg->setEpsRel(1E-4);
cfg->method1D().setLabel("RooSegmentedIntegrator1D");
cfg->getConfigSection("RooSegmentedIntegrator1D")->setRealValue("numSeg",40);
//cfg->method1D()->Print("v");
D0pdf.setIntegratorConfig(*cfg);
D0pdf23.setIntegratorConfig(*cfg);
antiD0pdf.setIntegratorConfig(*cfg);
antiD0pdf23.setIntegratorConfig(*cfg);
peakbkg.setIntegratorConfig(*cfg);
peakbkg23.setIntegratorConfig(*cfg);
antipeakbkg.setIntegratorConfig(*cfg);
antipeakbkg23.setIntegratorConfig(*cfg);

cout << "about to init" << endl;

if(doNorm) D0pdf.getManager()->calNorm();
if(doNorm) antiD0pdf.getManager()->calNorm();
if(doNorm) peakbkg.getManager()->calNorm();
if(doNorm) antipeakbkg.getManager()->calNorm();

Float_t norm = D0pdf.getManager()->getNormalization();
cout << "***********************************" << endl;
cout << "The norm is   " << norm << endl;
cout << "***********************************" << endl;

//Compose pdf adding the non-interferring terms
RooAddPdf tot_pdf("tot_pdf","tot_pdf",RooArgList(sigpdf,peakpdf,combpdf),RooArgSet(N_sig,N_peak,N_comb));
RooAddPdf tot_pdf23("tot_pdf23","tot_pdf23",RooArgList(sigpdf23,peakpdf23,combpdf23),RooArgSet(N_sig,N_peak,N_comb));

//here is where we really fit
if(doFit) RooFitResult* fitRes = tot_pdf.fitTo(*data,"HRMT");

//Make the plots
//******************************************************

RooPlot* xframe = m2Kpi_d0mass.frame(low12,high12);
data->plotOn(xframe,MarkerSize(0.1),DrawOption("z"));
tot_pdf.plotOn(xframe,ProjWData(D0flav,*data));
//tot_pdf.plotOn(xframe,Project(m_Kpi0_d0mass),RooFit::Components(RooArgSet(comb_bkg)),RooFit::FillColor(kGreen));
xframe->getAttLine()->SetLineWidth(1);
xframe->getAttLine()->SetLineStyle(1);

RooPlot* yframe = m2Kpi0_d0mass.frame(low13,high13);
data->plotOn(yframe,MarkerSize(0.1),DrawOption("z"));
tot_pdf.plotOn(yframe,ProjWData(D0flav,*data)); 
//tot_pdf.plotOn(yframe,Project(m_Kpi_d0mass),RooFit::Components(RooArgSet(comb_bkg)));
yframe->getAttLine()->SetLineWidth(1);
yframe->getAttLine()->SetLineStyle(1);

RooPlot* zframe = m2pipi0_d0mass.frame(low23,high23);
data->plotOn(zframe,MarkerSize(0.1),DrawOption("z"));
tot_pdf23.plotOn(zframe,ProjWData(D0flav,*data)); 
//tot_pdf23.plotOn(zframe,Project(m_Kpi_d0mass),RooFit::Components(RooArgSet(comb_bkg23)));
zframe->getAttLine()->SetLineWidth(1);
zframe->getAttLine()->SetLineStyle(1);

TCanvas *c1 = new TCanvas("c1","allevents",1200,400);
c1->Divide(3,1);
c1->cd(1);xframe->Draw();
c1->cd(2);yframe->Draw();
c1->cd(3);zframe->Draw();
c1->SaveAs("WStotfit.eps");

//plots for weights studies
if(do3DHistos){
TH3F* eff_mKpi = m_Kpi_d0mass.createHistogram("mKpi vs efficiency",m_Kpi0_d0mass,eff_weight,"prova");
data.fillHistogram(eff_mKpi,RooArgList(m_Kpi_d0mass,m_Kpi0_d0mass,eff_weight));
TH3F* eff_mpipi0 = m_pipi0_d0mass.createHistogram("mpipi0 vs efficiency",m_Kpi_d0mass,eff_weight,"prova");
data.fillHistogram(eff_mpipi0,RooArgList(m_pipi0_d0mass,m_Kpi_d0mass,eff_weight));

TH3F* sw_mKpi = m_Kpi_d0mass.createHistogram("mKpi vs s_weight",m_Kpi0_d0mass,nSigXR_sWeight,"prova");
data.fillHistogram(sw_mKpi,RooArgList(m_Kpi_d0mass,m_Kpi0_d0mass,nSigXR_sWeight));
TH3F* sw_mpipi0 = m_pipi0_d0mass.createHistogram("mpipi0 vs s_weight",m_Kpi_d0mass,nSigXR_sWeight,"prova");
data.fillHistogram(sw_mpipi0,RooArgList(m_pipi0_d0mass,m_Kpi_d0mass,nSigXR_sWeight));

TCanvas *c2 = new TCanvas("c2","allevents");
c2->Divide(2,2);
c2->cd(1);eff_mKpi->Draw("ISO");
c2->cd(2);eff_mpipi0->Draw("ISO");
c2->cd(3);sw_mKpi->Draw("ISO");
c2->cd(4);sw_mpipi0->Draw("ISO");
c2->SaveAs("weights.eps");
}

}//end of the macro

