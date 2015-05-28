{
  
  TString nomeFile = "ZbbTT.root";
  TFile pippo(nomeFile);
  pippo.cd();
  
  //load dataset
  RooRealVar mass("mass","mass",60.,120.);
  mass.setBins(15);
  
  TTree *mytree = (TTree*)pippo.Get("ZbbTT.txt");
  RooDataSet dataset("dataset","dataset",mytree,RooArgSet(mass));

  RooArgSet parlist;
  
  // IF I WANT FOR THE SIGNAL CB + BW
  //Signal is CB shape (X) BW
  //RooRealVar sigCB_mean("sigCB_mean","sigCB_mean",91.,85.,100.);
  //  RooRealVar sigCB_mean("sigCB_mean","sigCB_mean",0.73630,-5.,5.);
  //  RooRealVar sigCB_sigma("sigCB_sigma","sigCB_sigma",1.8150,0.,5.);
  //  RooRealVar sigCB_alpha("sigCB_alpha","sigCB_alpha",1.6538,0.1,5.);
  //  RooRealVar sigCB_n("sigCB_n","sigCB_n",1.2610,0.,3.);
  //  RooCBShape signalCB("signalCB","signalCB",x,sigCB_mean,sigCB_sigma,sigCB_alpha,sigCB_n);
  //RooCBShape pdf_sig("signalCB","signalCB",x,sigCB_mean,sigCB_sigma,sigCB_alpha,sigCB_n);

  //RooRealVar sigBW_mean("sigBW_mean","sigBW_mean",91.04);  
  //RooRealVar sigBW_gamma("sigBW_gamma","sigBW_gamma",2.49); 
  //  RooRealVar sigBW_mean("sigBW_mean","sigBW_mean",91.04, 80.,100.);  
  //RooRealVar sigBW_gamma("sigBW_gamma","sigBW_gamma",2.49, 1., 3.); 

  //RooBreitWigner signalBW("signalBW", "signalBW",x,sigBW_mean,sigBW_gamma);
  //RooBreitWigner pdf_sig("signalBW", "signalBW",x,sigBW_mean,sigBW_gamma);
   
  //Construct BW (x) CB
  //Set #bins to be used for FFT sampling to 10000
  //x.setBins(10000,"fft") ;

  //RooFFTConvPdf pdf_sig("pdf_sig","BW (X) CB",x,signalBW,signalCB);
  //Buffer fraction for cyclical behavior
  //pdf_sig.setBufferFraction(0.5);

  RooRealVar sigBW_mean("sigBW_mean","sigBW_mean",91.04, 80.,100.);  
  RooRealVar sigBW_gamma("sigBW_gamma","sigBW_gamma",2.49); 
  RooRealVar sigBW_sigma("sigBW_sigma","sigBW_sigma",2.5, 0., 10.); 
  RooVoigtian pdf_sig("signalBW", "signalBW",mass,sigBW_mean, sigBW_gamma, sigBW_sigma);

  //IF I WANT FOR THE SIGNAL 2 GAUSS
  //gaussiana 1 massZ1
  //RooRealVar mean1Z1("mean1Z1","Z1 mass",65.,30.,100.,"GeV/c^{2}");
  //RooRealVar width1Z1("width1Z1","Z1 mass err",27.,0.,40.);
  //RooGaussian g1Z1("g1Z1","Z1 mass sig PDF",x,mean1Z1,width1Z1);
  
  //gaussiana 2 massZ1
  //RooRealVar mean2Z1("mean2Z1","Z1 mass",91.04,30.,160.,"GeV/c^{2}");
  //RooRealVar width2Z1("width2Z1","Z1 mass err",2.62,0.,5.);
  //RooGaussian g2Z1("g2Z1","Z1 mass sig PDF",x,mean2Z1,width2Z1);
  
  //polinomio bkg tt
  RooRealVar c0("c0", "", -0.93673,-10.,10.);
  //RooRealVar c1("c1", "", -0.22764,-10.,10.);
  //RooRealVar c2("c2", "", 0.23382,  -10., 10.);
  //RooRealVar c3("c3", "", -0.099348,-10., 10.);
  RooChebychev pdf_bkg("pdf_bkg", "", mass, RooArgList(c0));

  //RooGaussian constC0("constC0", "constC0",c0,RooConst(-0.66755),RooConst(0.257));
  //RooGaussian constC1("constC1", "constC1",c1,RooConst(-0.097858),RooConst(0.209)); //if errorlarger then value --> unuseless paramenter (retta) 
  //parlist.add(mean1Z1);
  //parlist.add(mean2Z1);
  //parlist.add(width1Z1);
  //parlist.add(width2Z1);
  parlist.add(c0);
  //parlist.add(c1);
  //parlist.add(c2);
  //parlist.add(c3);

  //   parlist.add(sigCB_mean);
  //   parlist.add(sigCB_sigma);
  //   parlist.add(sigCB_alpha);
  //   parlist.add(sigCB_n);
  parlist.add(sigBW_mean);
  parlist.add(sigBW_gamma);
  parlist.add(sigBW_sigma);

  //mean1Z1.setConstant(kTRUE); //si prende il valore iniziale che gli do
  //width1Z1.setConstant(kTRUE);
    
  //number of events of each pdf
  //RooRealVar frac_sig("frac_sig","",0.8.,0.,1.);
  RooRealVar Nsig("Nsig","Nsig",800.,0.,2000.);
  RooRealVar Nbkg("Nbkg","Nbkg",100.,0.,2000.);
  
  //parlist.add(frac_sig);
  parlist.add(Nsig);
  parlist.add(Nbkg);
  
  //segnale
  //RooAddPdf pdf_sig("pdf_sig","(1-f)*g1Z1+f*g2Z1",RooArgList(g2Z1,g1Z1),frac_sig);
  
  //totale
  RooAddPdf pdf("pdf","Nsig*sig+Nbkg*bkg",RooArgList(pdf_sig,pdf_bkg),RooArgList(Nsig,Nbkg));

  ///////////////////////////////////////////////////////////////
  /////////                      FIT                  ///////////
  ///////////////////////////////////////////////////////////////
  //RooFitResult *fitres = pdf.fitTo(histo,ExternalConstraints(RooArgSet(constC0,constC1)),RooFit::SumW2Error(kFALSE),RooFit::Save(1),RooFit::Extended(1));
  RooFitResult *fitres = pdf.fitTo(dataset,RooFit::Save(1),RooFit::Extended(1));
  //RooFitResult *fitres = pdf_sig.fitTo(histo,RooFit::SumW2Error(kFALSE),RooFit::Save(1));
  //RooFit::Minos(1)
  fitres->Print("v");
  RooArgSet results(fitres->floatParsFinal());
  RooArgSet constants(fitres->constPars());
  results.add(constants);
  
  nomeFile.ReplaceAll(".root",".txt");
  results.writeToFile(nomeFile.Data());
  
  //plot 
  RooPlot* xframe = mass.frame();
  dataset.plotOn(xframe,RooFit::DataError(RooAbsData::SumW2));
  pdf.plotOn(xframe);
  
  Double_t chi2 = xframe->chiSquare();
  
  //pdf.plotOn(xframe,Components(RooArgList(g1Z1,g2Z1,pdf_bkg)),DrawOption("F"),FillColor(kAzure+1));
  //pdf.plotOn(xframe,Components(RooArgList(g1Z1,pdf_bkg)),DrawOption("F"),FillColor(kAzure+1));
  //pdf.plotOn(xframe,Components(RooArgList(pdf_bkg)),DrawOption("F"),FillColor(kOrange+6));

  pdf.plotOn(xframe,RooFit::DrawOption("F"),RooFit::FillColor(kGreen-3));
  pdf.plotOn(xframe,RooFit::Components(RooArgList(pdf_bkg)),RooFit::DrawOption("F"),RooFit::FillColor(kCyan));  
  dataset.plotOn(xframe,RooFit::DataError(RooAbsData::SumW2));
    
  xframe->SetTitle("m_{Z1} fit: bkg control from data");
  xframe->GetXaxis()->SetTitle("m_{Z1} (GeV/c^{2})");

  TCanvas *canv1 = new TCanvas("Mass_Z1","Mass_Z1");
  canv1->cd();
  xframe->Draw();
  canv1->Show();
  
  nomeFile.ReplaceAll(".txt",".gif");
  canv1->SaveAs(nomeFile.Data());
  
  canv1->SetLogy();
  nomeFile.ReplaceAll(".gif","_log.gif");
  canv1->SaveAs(nomeFile.Data());
  
  nomeFile.ReplaceAll("_log.gif",".C");
  canv1->SaveAs(nomeFile.Data());
  
  cout << "chi2 " << chi2 << endl;
  
}
