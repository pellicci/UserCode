void fitA0(){
  using namespace RooFit;

  //gROOT->ProcessLine(".x Style.C");
  
  const int n_sample = 13 ;

  std::vector<TString> v_sample_names;

  Float_t v_mean[n_sample];

  v_sample_names.push_back("A05GeV_noW");
  v_sample_names.push_back("A06GeV_noW");
  v_sample_names.push_back("A07GeV_noW");
  v_sample_names.push_back("A08GeV_noW");
  v_sample_names.push_back("A09GeV_noW");
  v_sample_names.push_back("A09.4GeV_noW");
  v_sample_names.push_back("A09.8GeV_noW");
  v_sample_names.push_back("A010.2GeV_noW");
  v_sample_names.push_back("A010.35GeV_noW");
  v_sample_names.push_back("A010.5GeV_noW");
  v_sample_names.push_back("A011GeV_noW");
  v_sample_names.push_back("A012GeV_noW");
  v_sample_names.push_back("A013GeV_noW");
  
  v_mean[0] = 5.;
  v_mean[1] = 6.;
  v_mean[2] = 7.;
  v_mean[3] = 8.;
  v_mean[4] = 9.;
  v_mean[5] = 9.4;
  v_mean[6] = 9.8;
  v_mean[7] = 10.2;
  v_mean[8] = 10.35;
  v_mean[9] = 10.5;
  v_mean[10] = 11.;
  v_mean[11] = 12.;
  v_mean[12] = 13.;

  Float_t sigmaACB[n_sample];
  Float_t sigmaACB_err[n_sample];
  Float_t sigmaAGauss[n_sample];
  Float_t sigmaAGauss_err[n_sample];
  Float_t sigmaAFrac[n_sample];
  Float_t sigmaAFrac_err[n_sample];

  Float_t chi2[n_sample];

  Float_t errX[n_sample];

  TCanvas *can [n_sample] ;

  TFile *fFits = new TFile("a0fits_CBGauss.root", "RECREATE");
 
  RooDataHist *hdata1[n_sample];

  for ( int iSample = 0; iSample < n_sample; iSample++ )	
    {
      can[iSample] = new TCanvas(v_sample_names[iSample],v_sample_names[iSample]);

      errX[iSample] = 0.; 
      
      RooRealVar invMass("invMass","M_{#mu#mu} [GeV/c^{2}]",v_mean[iSample]-0.5,v_mean[iSample]+0.3);
      invMass.setBins(25);
      //      invMass.setRange("onlyA",v_mean[iSample]-(v_mean[iSample]/25),v_mean[iSample]+(v_mean[iSample]/35));

      TFile f( "./"+v_sample_names[iSample] + ".root", "READ" ) ;
      TTree *tInvMass = f.Get("tInvMass");
      RooDataSet dataset("dataset","dataset",tInvMass,RooArgSet(invMass));
  
      hdata1[iSample] = dataset.binnedClone();

      RooRealVar mean("mean","a mean",v_mean[iSample],4.,14.); 
   
      RooRealVar sigmaCB("sigmaCB","a width",0.06,0.002,0.2);
      RooRealVar sigmaGaus("sigmaGaus","a width",0.1, 0., 1.);
            
      RooRealVar alpha("alpha","alpha",1.8);//,-5.,10.);
      RooRealVar enne("enne","enne",1.);//,0.,200.);
      
      RooCBShape pdfaCB("pdfaCB","pdfaCB",invMass,mean,sigmaCB,alpha,enne);
      RooGaussian pdfaGaus("pdfaGauss","pdfaGauss",invMass,mean,sigmaGaus);

      RooRealVar sigmaFrac("sigmaFrac","sigmaFrac",0.04,0.,1.);
      //      RooRealVar sigmaFrac2("sigmaFrac2","sigmaFrac2",0.3,0.,1.);
      RooAddPdf pdfa("pdfa","pdfa",RooArgList(pdfaGaus,pdfaCB),RooArgList(sigmaFrac));//,sigmaFrac2));
 
      RooRealVar Na0("Na0","Na0",4200.,0.,100000000.);
       
      RooAddPdf TOTpdf("TOTpdf","TOTpdf",RooArgList(pdfa),RooArgList(Na0));

      fFits->cd();
  
 //      RooChi2Var chi2Var("chi2","chi2",TOTpdf,*hdata1[iSample],Extended(1));
//       RooMinuit m2(chi2Var);
//       m2.migrad();
//       m2.hesse();
//       RooFitResult* fitRes = m2.save();
      
      RooFitResult *fitRes = TOTpdf.fitTo(*hdata1[iSample],Extended(1),Save(1));//,Range("onlyA"));
      fitRes->Print("v");
      
      sigmaACB[iSample] = sigmaCB.getVal();
      sigmaACB_err[iSample] = sigmaCB.getError();

      sigmaAGauss[iSample] = sigmaGaus.getVal();
      sigmaAGauss_err[iSample] = sigmaGaus.getError();

      sigmaAFrac[iSample] = sigmaFrac.getVal();
      sigmaAFrac[iSample] = sigmaFrac.getError();

      RooPlot *xplot = invMass.frame();
      hdata1[iSample]->plotOn(xplot);//, RooFit::Cut("region==region::Background"));
      TOTpdf.plotOn(xplot);

      chi2[iSample] = xplot->chiSquare();

      can[iSample]->cd(0);    
      
      xplot->Draw();
      
      can[iSample]->Write();
      
    }
  
  TFile f_out("SigmaA0_vs_mass_CBGauss.root", "RECREATE");
  f_out.cd();
  
  TCanvas *c1 = new TCanvas("graph","graph");
  
  c1->Divide(2,2); 
  c1->cd(1);
    
  TGraphErrors* sigmaA0CB =  new TGraphErrors(n_sample, v_mean, sigmaACB, errX, sigmaACB_err);
  sigmaA0CB->SetTitle("pseudoscalar");
  sigmaA0CB->GetXaxis()->SetTitle("mass A0");
  sigmaA0CB->GetYaxis()->SetTitle("sigma A CB");
  sigmaA0CB->SetMarkerStyle(20);
  sigmaA0CB->SetMarkerColor(kRed);
  sigmaA0CB->SetFillColor(0);
  sigmaA0CB->SetFillStyle(0);
  gStyle->SetOptFit(1111);
  sigmaA0CB->Fit("pol1","FQ");
  sigmaA0CB->Draw("AP");

  c1->cd(2);
  TGraphErrors* sigmaA0Gauss =  new TGraphErrors(n_sample, v_mean, sigmaAGauss, errX, sigmaAGauss_err);
  sigmaA0Gauss->SetTitle(0);
  sigmaA0Gauss->GetXaxis()->SetTitle("mass A0");
  sigmaA0Gauss->GetYaxis()->SetTitle("sigma A gauss");
  sigmaA0Gauss->SetMarkerStyle(20);
  sigmaA0Gauss->SetMarkerColor(kRed);
  sigmaA0Gauss->SetFillColor(0);
  gStyle->SetOptFit(1111);
  sigmaA0Gauss->Fit("pol1","FQ");
  sigmaA0Gauss->Draw("AP");

  c1->cd(3);
  TGraphErrors* sigmaA0Frac =  new TGraphErrors(n_sample, v_mean, sigmaAFrac, errX, sigmaAFrac_err);
  sigmaA0Frac->SetTitle(0);
  sigmaA0Frac->GetXaxis()->SetTitle("mass A0");
  sigmaA0Frac->GetYaxis()->SetTitle("sigma Frac");
  sigmaA0Frac->SetMarkerStyle(20);
  sigmaA0Frac->SetMarkerColor(kRed);
  sigmaA0Frac->SetFillColor(0);
  sigmaA0Frac->Draw("AP");

  c1->cd(4);
  TGraph *chi2Fit = new TGraph(n_sample, v_mean, chi2);
  chi2Fit->GetXaxis()->SetTitle("mass A0");
  chi2Fit->GetYaxis()->SetTitle("Fit Chi2");
  chi2Fit->SetMarkerStyle(21);
  chi2Fit->SetMarkerColor(kBlue);
  chi2Fit->Draw("AP");
  
}
