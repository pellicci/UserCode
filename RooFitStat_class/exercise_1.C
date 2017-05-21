{

  gSystem->Load("libRooFit");

  RooRandom::randomGenerator()->SetSeed(1234);

  RooRealVar mass("mass","The invariant mass",100.,150.,"GeV/c^2");

  //Create a gaussian signal PDF
  RooRealVar mean("mean","The mean of the gaussian",125.,110.,140.);
  RooRealVar width("width","The width of the gaussian",2.,0.001,5.);
  RooGaussian gaussPDF("gaussPDF","The gaussian function",mass,mean,width);

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
  RooAddPdf totPDF("totPDF","The total PDF",RooArgList(gaussPDF,expoPDF),RooArgList(Nsig_form,Nbkg));

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

  RooWorkspace workspace("myworkspace");
  workspace.import(totPDF);
  workspace.import(*data);

  TFile fOut("exercise_1.root","RECREATE");
  fOut.cd();
  workspace.Write();
  fOut.Close();

}
