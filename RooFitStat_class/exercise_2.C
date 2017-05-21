{

  gSystem->Load("libRooFit");

  RooRandom::randomGenerator()->SetSeed(1234);

  RooRealVar mass("mass","The invariant mass",100.,150.,"GeV/c^2");

  //Create a gaussian signal PDF
  //Signal is the convolution of a BW times a gaussian resolution function
  RooRealVar mpole("mpole","Pole position",125.,110.,140.);
  RooRealVar BWwidth("BWwidth","Width of the Breit-Wigner",1.,0.0001,5.);
  RooBreitWigner BWsig("BWsig","Signal Breit-Wigner",mass,mpole,BWwidth);

  RooRealVar meanGauss("meanGauss","The mean of the gaussian",0.5,0.0001,2.);
  RooRealVar widthGauss("widthGauss","The width of the gaussian",1.,0.001,5.);
  RooGaussian gaussPDF("gaussPDF","The gaussian function",mass,meanGauss,widthGauss);

  widthGauss.setConstant(kTRUE);

  RooNumConvPdf totSigPDF("totSigPDF","Total signal PDF",mass,gaussPDF,BWsig);

  //Background PDF: exponential background
  RooRealVar tau("tau","The tau parameter",-0.05,-5.,-0.0001);
  RooExponential expoPDF("expoPDF","The exponential background",mass,tau);

  //RooRealVar frac("frac","Fraction of signal",0.5,0.,1.);
  //RooAddPdf totPDF("totPDF","The total PDF",RooArgList(gaussPDF,expoPDF),RooArgList(frac));

  //RooRealVar Nsig("Nsig","Number of signal events",500.,0.001,1000.);
  RooRealVar cross_sig("cross_sig","The signal cross section",1.,0.00001,5.);
  RooRealVar lumi("lumi","The luminosity",500.);
  RooFormulaVar Nsig_form("Nsig_form","@0*@1",RooArgList(cross_sig,lumi));

  RooRealVar Nbkg("Nbkg","Number of background events",500.,0.001,1000.);
  RooAddPdf totPDF("totPDF","The total PDF",RooArgList(totSigPDF,expoPDF),RooArgList(Nsig_form,Nbkg));

  RooDataSet *data = totPDF.generate(RooArgSet(mass),1000);

  totPDF.fitTo(*data,RooFit::Extended(true));

  RooPlot *massplot = mass.frame();
  data->plotOn(massplot);
  totPDF.plotOn(massplot);
  totPDF.plotOn(massplot,RooFit::Components(RooArgSet(expoPDF)),RooFit::LineStyle(kDashed),RooFit::LineColor(kRed));

  TCanvas c1;
  c1.cd();
  massplot->Draw();
  c1.SaveAs("exercise_0.pdf");

  RooWorkspace workspace;
  workspace.import(totPDF);
  workspace.import(*data);

  TFile fOut("exercise_2.root","RECREATE");
  fOut.cd();
  workspace.Write();
  fOut.Close();

}
