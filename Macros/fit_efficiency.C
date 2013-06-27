{

gStyle->SetPalette(1);

Float_t md0 = 1.8645;
Float_t mk = 0.493677;
Float_t mpi0 = 0.1349766;
Float_t mpi = 0.13957018;
Float_t total=md0*md0+mk*mk+mpi*mpi+mpi0*mpi0;
RooRealVar totalm("totalm","totalm",total);

RooRealVar d0Mass("d0Mass","d0Mass",1.74,1.99);
RooRealVar deltaMass("deltaMass","deltaMass",0.139,0.16);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",0.,3.2);
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",0.,3.2);
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",0.,2.2);
RooRealVar eff_pi0("eff_pi0","eff_pi0",0.,2.);

//this is just to plot the m23 pdf
RooFormulaVar mass13a("mass13a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2pipi0_d0mass));

Int_t binx = 110;
Int_t biny = 110;
m2Kpi_d0mass.setBins(binx);
m2Kpi0_d0mass.setBins(biny);

//read in the dataset
TFile hello("DataSet_out.root");
gROOT->cd();
RooDataSet *fulldata = (RooDataSet*)hello.Get("fulldata");
//RooDataSet *fulldata = fulldata_1->reduce("isAntiD0 == 1");

fulldata->setWeightVar(eff_pi0);

RooRealVar zero("zero","zero",0.);
RooPoly  genmap("genmap","genmap",m2Kpi_d0mass,m2Kpi0_d0mass,zero,zero,zero,zero,zero,zero,zero,zero,zero);
//RooDataSet *generated = genmap.generate(RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass),7000000);

Int_t numgen = 6018000;
//Int_t numgen = 3031000;     //for D0
//Int_t numgen = 2987000;   //for D0bar
TFile f1("generated.root");
RooDataSet *generated_1 = (RooDataSet*)f1.Get("genmapData");
RooDataSet *generated = generated_1->reduce(EventRange(1,numgen));

//define boundaries of RooRealVars wrt the data
m2Kpi_d0mass.setRange(0.,3.2);
m2Kpi0_d0mass.setRange(0.,3.2);

RooRealVar a1("a1","a1",-1.37231,-50.,50.);
RooRealVar a2("a2","a2",1.49474e+01,-50.,50.);
RooRealVar a3("a3","a3",3.85027,-50.,50.);
RooRealVar a4("a4","a4",-7.16135,-50.,50.);
RooRealVar a5("a5","a5",-4.55876,-50.,50.);
RooRealVar a6("a6","a6",-1.09502,-50.,50.);
RooRealVar a7("a7","a7",1.10126,-50.,50.);
RooRealVar a8("a8","a8",1.09323,-50.,50.);
RooRealVar a9("a9","a9",1.30811e-01,-50.,50.);
a1.setConstant(kFALSE);
a2.setConstant(kFALSE);
a3.setConstant(kFALSE);
a4.setConstant(kFALSE);
a5.setConstant(kFALSE);
a6.setConstant(kFALSE);
a7.setConstant(kFALSE);
a8.setConstant(kFALSE);
a9.setConstant(kFALSE);

RooPoly effmap("effmap","effmap",m2Kpi_d0mass,m2Kpi0_d0mass,a1,a2,a3,a4,a5,a6,a7,a8,a9);
RooPoly effmap23("effmap23","effmap23",m2Kpi_d0mass,mass13a,a1,a2,a3,a4,a5,a6,a7,a8,a9);

RooNumIntConfig* cfg = RooAbsReal::defaultIntegratorConfig();
cfg->setEpsAbs(0.0001);
cfg->setEpsRel(0.01);
//cfg->method2D().setLabel("RooIntegrator2D");
//cfg->getConfigSection("RooIntegrator2D").setRealValue("maxSteps",100);
//cfg->getConfigSection("RooSegmentedIntegrator2D").setRealValue("numSeg",40);
//  cfg->method2D().Print("v");
effmap->setIntegratorConfig(*cfg);
effmap23->setIntegratorConfig(*cfg);

TH2F *dalitzeff = m2Kpi_d0mass.createHistogram("dalitzeff",m2Kpi0_d0mass);
fulldata->fillHistogram(dalitzeff,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));

TH2F *dalitzgen = m2Kpi_d0mass.createHistogram("dalitzgen",m2Kpi0_d0mass);
generated->fillHistogram(dalitzgen,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));

dalitzeff->Sumw2();
dalitzgen->Sumw2();

for(Int_t i=1;i<=binx*biny;i++){
  if(dalitzgen->GetBinContent(i)>1000) continue;
  dalitzgen->SetBinContent(i,0.);
  dalitzeff->SetBinContent(i,0.);
}

TH1D *projx = dalitzeff->ProjectionX("projx");
TH1D *projy = dalitzeff->ProjectionY("projy");

TH1D *projxgen = dalitzgen->ProjectionX("projxgen");
TH1D *projygen = dalitzgen->ProjectionY("projygen");

projx->Sumw2();
projy->Sumw2();
projxgen->Sumw2();
projygen->Sumw2();

projx->Divide(projxgen);
projy->Divide(projygen);

dalitzeff->Divide(dalitzgen);
dalitzeff->Sumw2();

dalitzeff->GetXaxis()->SetTitle("m^{2}_{K#pi}"); 
dalitzeff->GetYaxis()->SetTitle("m^{2}_{K#pi^{0}}"); 
projx->GetXaxis()->SetTitle("m^{2}_{K#pi}"); 
projy->GetXaxis()->SetTitle("m^{2}_{K#pi^{0}}"); 

RooDataHist* db = new RooDataHist("db","db",RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),dalitzeff);
//TFile fout("DataHistD0bar.root","RECREATE");
//fout.cd();
//db->Write();
//fout.Close();

RooHistPdf pdfh("pdfh","pdfh",RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),*db,4);

RooChi2Var chi2("chi2","chi2",pdfh,*db,DataError(RooAbsData::SumW2));

// Start Minuit session on Chi2
RooMinuit m2(chi2) ;
//m2.migrad();
//m2.hesse();
RooFitResult* fitRes = m2.save() ;
RooArgSet results(fitRes->floatParsFinal());
RooArgSet conresults(fitRes->constPars());
results.add(conresults);
results.writeToFile("effmap.txt");

//try to create average plots
RooDataSet *dataFit = pdfh.generate(RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass),fulldata->numEntries());
TH2F *effFit = dataFit->createHistogram(m2Kpi_d0mass,m2Kpi0_d0mass,"","effFit");
effFit->Sumw2();

for(Int_t i=1;i<=binx*biny;i++){
  if(dalitzgen->GetBinContent(i)>1000) continue;
  effFit->SetBinContent(i,0.);
}

TH1D *projFitx = effFit->ProjectionX("projFitx");
TH1D *projFity = effFit->ProjectionY("projFity");
projFitx->Sumw2();
projFity->Sumw2();
projFitx->Divide(projxgen);
projFity->Divide(projygen);
projFitx->GetXaxis()->SetTitle("m^{2}_{K#pi}"); 
projFity->GetXaxis()->SetTitle("m^{2}_{K#pi^{0}}"); 
effFit->Divide(dalitzgen);

TCanvas c0;
c0.Divide(2,1);
projx->GetYaxis()->SetRangeUser(0.,0.18);
projy->GetYaxis()->SetRangeUser(0.,0.18);
projFitx->SetLineStyle(2);
projFity->SetLineStyle(2);
c0.cd(1);projx->Draw("HIST");projFitx->Draw("HIST SAME C");
c0.cd(2);projy->Draw("HIST");projFity->Draw("HIST SAME C");
c0.SaveAs("effdata_fit.eps");

RooPlot *xframe = m2Kpi_d0mass.frame(0.,3.2);
db->plotOn(xframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
effmap->plotOn(xframe);
Double_t chi2Kpi = xframe->chiSquare();

RooPlot *yframe = m2Kpi0_d0mass.frame(0.,3.2);
db->plotOn(yframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
effmap->plotOn(yframe);
Double_t chi2Kpi0 = yframe->chiSquare();

RooPlot *zframe = m2pipi0_d0mass.frame(0.,2.2);
fulldata->plotOn(zframe,MarkerSize(0.1),DrawOption("z"),DataError(RooAbsData::SumW2));
effmap23->plotOn(zframe);
Double_t chi2pipi0 = zframe->chiSquare();

cout << "Chi2 for Kpi = " << chi2Kpi << endl;
cout << "Chi2 for Kpi0 = " << chi2Kpi0 << endl;
cout << "Chi2 for pipi0 = " << chi2pipi0 << endl;

TCanvas *c1 = new TCanvas("c1","allevents",1200,400);
c1->Divide(3,1);
c1->cd(1);xframe->Draw();
c1->cd(2);yframe->Draw();
c1->cd(3);zframe->Draw();
c1->SaveAs("efffit.eps");

//Add the old efficiency for comparison
TChain *tree = new TChain("ntp2");
tree->Add("DmixKpipi0UserTuple-AR-phsp.root");

RooDataSet *olddataset = new RooDataSet("olddataset","olddataset",tree,RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass));
RooDataSet *oldgen = generated->reduce(EventRange(1,2300000));

TH2F *oldeff = olddataset->createHistogram(m2Kpi_d0mass,m2Kpi0_d0mass,"","oldeff");
oldeff->Sumw2();

TH2F *oldTHgen = oldgen->createHistogram(m2Kpi_d0mass,m2Kpi0_d0mass,"","oldTHgen");
oldTHgen->Sumw2();

oldeff->Divide(oldTHgen);
oldeff->Sumw2();
oldeff->GetXaxis()->SetTitle("m^{2}_{K#pi}"); 
oldeff->GetYaxis()->SetTitle("m^{2}_{K#pi^{0}}"); 

//dalitzeff->SetBinContent(dalitzeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
oldeff->SetBinContent(oldeff->GetMaximumBin(),0.);
dalitzeff->SetMaximum(oldeff->GetMaximum());

dalitzeff->SetTitle("Run1-5 Efficiency for D0 with corrections");
oldeff->SetTitle("Run1-4 Efficiency without corrections");

TCanvas c2;
c2.Divide(2,1);
c2.cd(1);dalitzeff->Draw("COLZ");
c2.cd(3);oldeff->Draw("COLZ");
c2.SaveAs("eff_dalitz.eps");

effFit->Add(dalitzeff,-1);
TCanvas c3;
c3.cd();effFit->Draw("COLZ");
c3.SaveAs("fit_diff.eps");

}
