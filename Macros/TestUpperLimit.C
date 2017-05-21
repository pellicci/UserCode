{
using namespace RooFit;

//gROOT->ProcessLine(".x Style.C");
  
  const Int_t n_fits = 30;

  Float_t errX[n_fits];
  Float_t chi2[n_fits];

  TCanvas *c1[n_fits];

  TFile fits("outputFitA0Search6GeV.root", "RECREATE");

  TString histoName("hInvMass");

  Float_t mass[n_fits];
  Float_t sigmaA0[n_fits];

  Float_t bkgCont[n_fits];
  Float_t errBkgCont[n_fits];

  Float_t A0Cont[n_fits];
  Float_t errA0Cont[n_fits];

  Float_t A0xSec[n_fits];
  Float_t errA0xSec[n_fits];

  TFile f("MuMuDataNew_pt2.root");
  f.cd();
  TTree *tInvMass = f.Get("tInvMass");

  RooRealVar invMass("invMass","M_{#mu#mu} [GeV/c^{2}]",4.,8.5);
  invMass.setBins(4.5/.15);
  RooDataSet dataset("dataset","dataset",tInvMass,RooArgSet(invMass));
  RooDataHist hdata("hdata","hdata",RooArgSet(invMass),dataset);

  for(int i=0; i<n_fits; i++){
    stringstream stream; stream << i;
    TString counter = stream.str();
   
    TString hName = "FitMass_bin"+counter;
    c1[i] = new TCanvas(hName, hName);

    mass[i] = 4.075+i*.15;
    
    sigmaA0[i] = 0.00789+0.009874*mass[i];
    
    RooRealVar a("a","a of bkg", -3.8342, -10., 10.);
    RooRealVar b("b","b of bkg", 2.3173, -10., 10);
    RooRealVar c("c","c of bkg", -0.3742, -10., 10.);
    RooRealVar d("d","d of bkg", 0.018696, -10., 10.);
  
    RooPolynomial bkgpdf("pol","polynomial background",invMass,RooArgList(a,b,c,d));
  
    RooRealVar mean1("mean1","a mean",mass[i]);
    RooRealVar sigma1("sigma1","a width",sigmaA0[i]);
 
    //a.setConstant(kTRUE);
    //b.setConstant(kTRUE);
    //c.setConstant(kTRUE);
    //d.setConstant(kTRUE);

    sigma1.setConstant(kTRUE);
    mean1.setConstant(kTRUE);  

    RooGaussian pdfa1("pdfa1","pdfa1",invMass,mean1,sigma1);
    RooRealVar Na0("Na0","Na0",0.,-1000.,1000.);

    RooRealVar Ncont("Ncont","Ncont",83000.,0.,1000000000.);
    RooAddPdf TOTpdf("TOTpdf","TOTpdf",RooArgList(pdfa1,bkgpdf),RooArgList(Na0,Ncont));
    //RooAddPdf TOTpdf("TOTpdf","TOTpdf",RooArgList(bkgpdf),RooArgList(Ncont));

    //RooFitResult *fitRes = TOTpdf.fitTo((hdata),Extended(1),Save(1));

    RooChi2Var chi2Var("chi2","chi2",TOTpdf,hdata,Extended(1));
    RooMinuit m2(chi2Var);
    m2.migrad();
    m2.hesse();
    RooFitResult* fitRes = m2.save();

    fitRes->Print("v");

    fits.cd();
  
    bkgCont[i] = Ncont.getVal();
    errBkgCont[i] = Ncont.getError();

    A0Cont[i] = Na0.getVal();
    errA0Cont[i] = Na0.getError();

    A0xSec[i] = A0Cont[i]/35.9;//pb
    errA0xSec[i] = errA0Cont[i]/35.9;
  
    RooPlot *xplot = invMass.frame();
    hdata.plotOn(xplot);

    TOTpdf.plotOn(xplot);      
    TOTpdf.paramOn(xplot,Format("NELU",FixedPrecision(2)),Layout(0.5309045,0.8785714,0.518956)); //to show parameters fit value on the plot

    chi2[i] = xplot->chiSquare();

    c1[i]->cd();
    c1[i]->SetFillColor(kWhite);
    
    xplot->SetTitle("");
    errX[i] = 0.;
   
    xplot->Draw();

    c1[i]->Write();
 
  }

  TCanvas c2;
  c2->Divide(2,2);
  c2->SetFillColor(kWhite);
  
  c2->cd(1);
  TGraphErrors *BkgCounts = new TGraphErrors(n_fits, mass, bkgCont, errX, errBkgCont);
  BkgCounts->SetTitle(0);
  BkgCounts->GetXaxis()->SetTitle("#mu#mu Mass");
  BkgCounts->GetYaxis()->SetTitle("Background counts");
  BkgCounts->SetMarkerStyle(20);
  BkgCounts->SetMarkerColor(kRed);
  BkgCounts->Draw("AP");
  

  c2->cd(2);
  TGraphErrors *FitChi2 = new TGraphErrors(n_fits, mass, chi2, errX, errX);
  FitChi2->SetTitle(0);
  FitChi2->GetXaxis()->SetTitle("#mu#mu Mass");
  FitChi2->GetYaxis()->SetTitle("Fit #chi^{2}");
  FitChi2->SetMarkerStyle(20);
  FitChi2->SetMarkerColor(kRed);
  FitChi2->Draw("AP");

  c2->cd(3);
  TGraphErrors *A0Counts = new TGraphErrors(n_fits, mass, A0Cont, errX, errA0Cont);
  A0Counts->SetTitle(0);
  A0Counts->GetXaxis()->SetTitle("#mu#mu Mass");
  A0Counts->GetYaxis()->SetTitle("Signal counts");
  A0Counts->SetMarkerStyle(20);
  A0Counts->SetMarkerColor(kRed);
  A0Counts->Draw("AP");
    
  c2->cd(4);
  TGraphErrors *A0Xsec = new TGraphErrors(n_fits, mass, A0xSec, errX, errA0xSec);
  A0Xsec->SetTitle(0);
  A0Xsec->GetXaxis()->SetTitle("#mu#mu Mass");
  A0Xsec->GetYaxis()->SetTitle("Signal XSec [pb]");
  A0Xsec->SetMarkerStyle(20);
  A0Xsec->SetMarkerColor(kRed);
  A0Xsec->Draw("AP");
 
}
