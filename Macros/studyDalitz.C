{
gROOT->SetStyle("BABAR");
gStyle->SetPalette(1);
gStyle->SetPadRightMargin(0.13);

//define DalitzSpace for generation
EvtPDL pdl;
pdl.readPDT("evt.pdl");
EvtDecayMode mode("D0 -> K- pi+ pi0");
EvtDalitzPlot dalitzSpace(mode);

RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",0.,-10.,10.);
RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",0.1,0.,0.5);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::BC),dalitzSpace.qAbsMax(EvtCyclic3::BC));
RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);

TFile hello("DataSet_out_tmp.root");
//TFile hello("dataR18/DataSet_out.root");
//TFile hello("dataR18/DataSet_out_signal.root");
gROOT->cd();

RooDataSet *data = (RooDataSet*)hello.Get("fulldata");
RooDataSet *data_1 = (RooDataSet*)data->reduce("isWS == 0 && d0Mass > 1.8495 && d0Mass < 1.8795 && d0Lifetime > -2. && d0Lifetime < 4.");
RooDataSet *finaldata = (RooDataSet*)data_1->reduce("deltaMass > 0.1449 && deltaMass < 0.1459 && d0LifetimeErr < 0.5");
//here we set the weights for the dataset
finaldata->setWeightVar(0);

cout << "*************************************************************" << endl;
cout << "The final data entry    " << finaldata->numEntries() << endl;
cout << "*************************************************************" << endl;

TProfile2D sigmat_dal("sigmat_dal","sigmat_dal",50,0.3,3.1,50,0.3,3.1,0.,2.);
TProfile2D tpull_dal("tpull_dal","tpull_dal",50,0.3,3.1,50,0.3,3.1,-10.,10.);
TProfile2D tdiff_dal("tdiff_dal","tdiff_dal",50,0.3,3.1,50,0.3,3.1,-10.,10.);

TProfile tpull_mkpi("tpull_mkpi","tpull_mkpi",50,0.3,3.1);

for(Int_t i=0;i<finaldata->numEntries();i++){
  RooArgSet *param = (RooArgSet*)finaldata->get(i);
  Double_t m12 = ((RooAbsReal*)param->find("m2Kpi_d0mass"))->getVal();
  Double_t m13 = ((RooAbsReal*)param->find("m2Kpi0_d0mass"))->getVal();

  Double_t sigmat = ((RooAbsReal*)param->find("d0LifetimeErr"))->getVal();
  Double_t t = ((RooAbsReal*)param->find("d0Lifetime"))->getVal();

  Double_t pull = (t - 0.4101)/sigmat;
  Double_t dt = t - 0.4101;

  sigmat_dal.Fill(m12,m13,sigmat,1);
  tpull_dal.Fill(m12,m13,pull,1);
  tdiff_dal.Fill(m12,m13,dt,1);
  tpull_mkpi.Fill(m12,pull,1);
}

sigmat_dal.SetTitle("");
sigmat_dal.GetXaxis()->SetTitle("m^{2}_{K#pi}");
sigmat_dal.GetYaxis()->SetTitle("m^{2}_{K#pi^{0}}");
sigmat_dal.SetBinContent(sigmat_dal.GetMaximumBin(),0.);

tpull_dal.SetTitle("");
tpull_dal.GetXaxis()->SetTitle("m^{2}_{K#pi}");
tpull_dal.GetYaxis()->SetTitle("m^{2}_{K#pi^{0}}");
tpull_dal.SetMaximum(1.5);
tpull_dal.SetMinimum(-1.5);

tdiff_dal.SetTitle("");
tdiff_dal.GetXaxis()->SetTitle("m^{2}_{K#pi}");
tdiff_dal.GetYaxis()->SetTitle("m^{2}_{K#pi^{0}}");
tdiff_dal.SetMaximum(0.5);
tdiff_dal.SetMinimum(-0.5);

tpull_mkpi.SetTitle("");
tpull_mkpi.GetXaxis()->SetTitle("m^{2}_{K#pi}");
tpull_mkpi.SetMaximum(0.4);
tpull_mkpi.SetMinimum(-0.4);

TCanvas prova("prova","prova",400,400);
prova.cd();sigmat_dal.Draw("COLZ");
prova.SaveAs("sigmat_dal_corr.eps");

Int_t palette[10] = {38, 3, 8, 30, 17, 10, 42, 45, 46, 2};
gStyle->SetPalette(10,palette);
                                                                                                                                                           
TCanvas prova2("prova2","prova2",400,400);;
prova2.cd();tpull_dal.Draw("COLZ");
prova2.SaveAs("tpull_dal_corr.eps");

TCanvas prova3("prova3","prova3",400,400);;
prova3.cd();tdiff_dal.Draw("COLZ");
prova3.SaveAs("tdiff_dal_corr.eps");

TCanvas prova4("prova4","prova4",400,400);;
prova4.cd();tpull_mkpi.Draw();
prova4.SaveAs("tpull_mkpi_corr.eps");

}
