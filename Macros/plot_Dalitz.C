{

gROOT->SetStyle("BABAR");
gStyle->SetPalette(1);
gStyle->SetPadTopMargin(0.04);
gStyle->SetPadLeftMargin(0.17);
gStyle->SetPadRightMargin(0.13);
gStyle->SetPadBottomMargin(0.19);
babarStyle->SetTitleSize(0.08,"xyz"); // set the 3 axes title size 

EvtPDL pdl;
pdl.readPDT("evt.pdl");
EvtDecayMode mode("D0 -> K- pi+ pi0");
EvtDalitzPlot dalitzSpace(mode);

RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",-2.,4.);
RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",0.,0.5);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::BC),dalitzSpace.qAbsMax(EvtCyclic3::BC));
RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);

TFile hello("DataSet_out_tmp.root");
gROOT->cd();
RooDataSet *data = (RooDataSet*)hello.Get("fulldata");
RooDataSet *data_1 = (RooDataSet*)data->reduce("d0Mass > 1.8495 && d0Mass < 1.8795 && d0Lifetime > -2. && d0Lifetime < 4. && deltaMass > 0.1449 && deltaMass < 0.1459 && d0LifetimeErr < 0.5");
RooDataSet *dataRS = (RooDataSet*)data_1->reduce("isWS == 0");
RooDataSet *dataWS = (RooDataSet*)data_1->reduce("isWS == 1");

TH2F *hRS = new TH2F("hRS","hRS",200,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB),200,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
TH2F *hWS = new TH2F("hWS","hWS",50,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB),50,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));

dataRS->fillHistogram(hRS,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));
dataWS->fillHistogram(hWS,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));

hRS->GetXaxis()->SetTitle("m^{2}_{K^{-}#pi^{+}} [GeV^{2}/c^{4}]");
hRS->GetYaxis()->SetTitle("m^{2}_{K^{-}#pi^{0}} [GeV^{2}/c^{4}]");
hWS->GetXaxis()->SetTitle("m^{2}_{K^{+}#pi^{-}} [GeV^{2}/c^{4}]");
hWS->GetYaxis()->SetTitle("m^{2}_{K^{+}#pi^{0}} [GeV^{2}/c^{4}]");

hRS->SetTitle("RS Dalitz plot");
hWS->SetTitle("");

TPaveText *boxRS = new TPaveText(2.5,2.5,2.7,2.7,"");
boxRS->AddText("(a)");
TPaveText *boxWS = new TPaveText(2.5,2.5,2.7,2.7,"");
boxWS->AddText("(b)");

boxRS->SetFillColor(10);
boxWS->SetFillColor(10);

Int_t normPalette[15];
Float_t rgbval = 0.7f;
for( Int_t i = 0; i < 15; ++i ) {
  normPalette[i] = TColor::GetColor(rgbval,rgbval,rgbval);
  rgbval -= 0.05;
}
//gStyle->SetPalette(15,normPalette);
gStyle->SetPalette(1);

TCanvas c1("RS","RS",300,300);
 c1.cd();hRS->Draw("COLZ");//boxRS->Draw("SAME");
c1.SaveAs("plotRS_dal.eps");

TCanvas c2("WS","WS",300,300);
c2.cd();hWS->Draw("COLZ");boxWS->Draw("SAME");
c2.SaveAs("plotWS_dal.eps");

}
