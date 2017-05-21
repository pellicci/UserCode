{
gROOT->Reset();

Bool_t doFit=kFALSE;
Bool_t doBigPlots=kFALSE;
Bool_t doNorm=kFALSE;

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

Float_t total=md0*md0+mk*mk+mpi*mpi+mpi0*mpi0;
RooRealVar totalm("totalm","totalm",total);

RooRealVar d0Mass("d0Mass","d0Mass",d0lower,d0upper);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",m12lower,m12upper);
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",m13lower,m13upper);
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",m23lower,m23upper);

//read in the dataset
TFile hello("DataSet_RS_all.root");
gROOT->cd();
RooDataSet *fulldata = (RooDataSet*)hello.Get("fulldata");

RooFormulaVar mass13a("mass13a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2pipi0_d0mass));

cout << "*************************************************************" << endl;
cout << "The final data entry    " << fulldata->numEntries() << endl;
cout << "*************************************************************" << endl;

//Construct combinatoric background dataset and pdf
//pdf is assumed to be a cubic polynomial plus 3 resonances
RooDataSet *backgr_1 = fulldata->reduce("d0Mass<1.81||d0Mass>1.91");
//RooDataSet *combbkg = backgr_1->reduce("deltaMass < 0.146 || deltaMass > 0.143");
RooDataSet *combbkg = backgr_1->reduce("deltaMass > 0.154 || deltaMass < 0.141");

//here you can set the per-event weight. Work still in progess...
combbkg->setWeightVar(0);

//here we set the limits for the fit
Double_t low12,high12,low13,high13,low23,high23;

Bool_t m12bool = combbkg->getRange(m2Kpi_d0mass,low12,high12);
Bool_t m13bool = combbkg->getRange(m2Kpi0_d0mass,low13,high13);
Bool_t m23bool = combbkg->getRange(m2pipi0_d0mass,low23,high23);
m2Kpi_d0mass.setRange(low12,high12);
m2Kpi0_d0mass.setRange(low13,high13);
m2pipi0_d0mass.setRange(low23,high23);

RooBkg mypdf("mypdf","mypdf",m2Kpi_d0mass,m2Kpi0_d0mass);  //using Kspi+ , Kspi- as dalitz variable
RooBkg mypdf23("mypdf23","mypdf23",m2Kpi_d0mass,mass13a); //Using Kspi+, pi+pi- as dalitz variable

cout << "For M12 we are using bins " << m2Kpi_d0mass.getBins() << endl;
cout << "For M13 we are using bins " << m2Kpi0_d0mass.getBins() << endl;

cout << "*************************************************************" << endl;
cout << "The total sidebands entry    " << combbkg->numEntries() << endl;
cout << "*************************************************************" << endl;

//When we plot the 1D projection, need to calculate the 1D integral
//set the precision here
cout << "config integrator " << endl;
RooNumIntConfig* cfg = RooAbsReal::defaultIntegratorConfig();
cfg->setEpsAbs(1E-4);
cfg->setEpsRel(1E-4);
cfg->method1D().setLabel("RooSegmentedIntegrator1D");
cfg->getConfigSection("RooSegmentedIntegrator1D")->setRealValue("numSeg",40);
//cfg->method1D()->Print("v");
mypdf.setIntegratorConfig(*cfg);
mypdf23.setIntegratorConfig(*cfg);

cout << "about to init" << endl;

if(doNorm) mypdf.getManager()->calNorm();

Float_t norm = mypdf.getManager()->getNormalization();
cout << "***********************************" << endl;
cout << "The norm is   " << norm << endl;
cout << "***********************************" << endl;

//here is where we really fit
if(doFit) RooFitResult* fitRes = mypdf.fitTo(*combbkg,"HRMT");

//here is where we plot
//******************************************************
RooPlot* xframe = m2Kpi_d0mass.frame(low12,high12);
combbkg->plotOn(xframe,MarkerSize(0.1),DrawOption("z"));
mypdf.plotOn(xframe,Project(m2Kpi0_d0mass));
Double_t chi2Kpi = xframe->chiSquare();
xframe->getAttLine()->SetLineWidth(1);
xframe->getAttLine()->SetLineStyle(1);

RooPlot* yframe = m2Kpi0_d0mass.frame(low13,high13);
combbkg->plotOn(yframe,MarkerSize(0.1),DrawOption("z"));
mypdf.plotOn(yframe,Project(m2Kpi_d0mass));
Double_t chi2Kpi0 = yframe->chiSquare();
yframe->getAttLine()->SetLineWidth(1);
yframe->getAttLine()->SetLineStyle(1);

RooPlot* zframe = m2pipi0_d0mass.frame(low23,high23);
combbkg->plotOn(zframe,MarkerSize(0.1),DrawOption("z"));
mypdf23.plotOn(zframe,Project(m2Kpi_d0mass));
Double_t chi2pipi0 = zframe->chiSquare();
zframe->getAttLine()->SetLineWidth(1);
zframe->getAttLine()->SetLineStyle(1);

cout << "Chi2 for Kpi = " << chi2Kpi << endl;
cout << "Chi2 for Kpi0 = " << chi2Kpi0 << endl;
cout << "Chi2 for pipi0 = " << chi2pipi0 << endl;

TCanvas *c1 = new TCanvas("c1","Combinatoric background",1200,400);
c1->Divide(3,1);
c1->cd(1);xframe->Draw();
c1->cd(2);yframe->Draw();
c1->cd(3);zframe->Draw();
c1->SaveAs("combbkg.eps");

if(doBigPlots){
TH2F* comb_dalitz = m2Kpi_d0mass.createHistogram("Combinatoric background dalitz",m2Kpi0_d0mass);
combbkg.fillHistogram(comb_dalitz,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));

RooPlot* xbkg = m2Kpi_d0mass.frame(0,3);
combbkg->plotOn(xbkg,MarkerSize(0.1),DrawOption("z"));
RooPlot* ybkg = m2Kpi0_d0mass.frame(0,3);
combbkg->plotOn(ybkg,MarkerSize(0.1),DrawOption("z"));
RooPlot* zbkg = m2pipi0_d0mass.frame(0,2);
combbkg->plotOn(zbkg,MarkerSize(0.1),DrawOption("z"));

TFile *f = new TFile("bkg.root","RECREATE");
TCanvas *c3 = new TCanvas("c3","Combinatoric background",1200,400);
c3->Divide(2);
c3->cd(1);comb_dalitz->Draw("COLZ");
c3->cd(2);comb_dalitz->Draw("SURF2");
c3->SaveAs("RSbkgcomb.eps");
f->cd();
comb_dalitz->Write();
f->Close();

 TCanvas *c4 = new TCanvas("c4","Combinatoric background",1200,400);
 c4->Divide(3,1);
 c4->cd(1);xbkg->Draw();
 c4->cd(2);ybkg->Draw();
 c4->cd(3);zbkg->Draw();
 c4->SaveAs("RSbkgcomb2.eps");
}

}//end of the macro
