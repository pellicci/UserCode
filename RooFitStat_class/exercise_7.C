{
  gSystem->Load("libRooFit");
  gSystem->Load("libRooStats");

  using namespace RooFit;
  using namespace RooStats;

  //Open the rootfile and get the workspace from the exercise_0
  TFile fIn("exercise_6.root");
  fIn.cd();
  RooWorkspace *w = (RooWorkspace*)fIn.Get("w");

  //You can set constant parameters that are known
  //If you leave them floating, the fit procedure will determine their uncertainty
  w->var("mean")->setConstant(kTRUE);
  w->var("sigma")->setConstant(kTRUE);
  w->var("tau")->setConstant(kTRUE);
  w->var("Nbkg")->setConstant(kTRUE);

  //Set the RooModelConfig and let it know what the content of the workspace is about
  ModelConfig model;
  model.SetWorkspace(*w);
  model.SetPdf("PDFtot");

  // here we explicitly set the value of the parameters for the null.  
  // We want no signal contribution, so Nsig = 0
  RooRealVar* Nsig = w->var("Nsig");
  RooArgSet poi(*Nsig);
  RooArgSet *nullParams = (RooArgSet*) poi.snapshot(); 
  nullParams->setRealValue("Nsig",0.); 

  //Build the profile likelihood calculator
  ProfileLikelihoodCalculator plc; 

  plc.SetData(*(w->data("PDFtotData"))); 
  plc.SetModel(model);
  plc.SetParameters(poi);
  plc.SetNullParameters(*nullParams);

  // We get a HypoTestResult out of the calculator, and we can query it.
  HypoTestResult* htr = plc.GetHypoTest();
  cout << "-------------------------------------------------" << endl;
  cout << "The p-value for the null is " << htr->NullPValue() << endl;
  cout << "Corresponding to a signifcance of " << htr->Significance() << endl;
  cout << "-------------------------------------------------\n\n" << endl;

}
