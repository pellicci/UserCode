{
  gSystem->Load("libRooFit");
  gSystem->Load("libRooStats");

  using namespace RooFit;
  using namespace RooStats;

  //Open the rootfile and get the workspace
  TFile fIn("Workspace_final.root");
  fIn.cd();
  RooWorkspace *w = (RooWorkspace*)fIn.Get("w");

  //You can set constant parameters that are known
  //If you leave them floating, the fit procedure will determine their uncertainty
  w->var("meanJpsi")->setConstant(kTRUE);
  w->var("sigmaJpsi")->setConstant(kTRUE);
  w->var("alphaJpsi")->setConstant(kTRUE);
  w->var("meanpsi")->setConstant(kTRUE);
  w->var("a1")->setConstant(kTRUE);
  w->var("a2")->setConstant(kTRUE);
  w->var("a3")->setConstant(kTRUE);
  w->var("Nbkg")->setConstant(kTRUE);
  w->var("NJpsi")->setConstant(kTRUE);

  //Set the RooModelConfig and let it know what the content of the workspace is about
  ModelConfig model;
  model.SetWorkspace(*w);
  model.SetPdf("totPDF");

  // here we explicitly set the value of the parameters for the null.  
  // We want no signal contribution, so Npsi = 0
  RooRealVar* Npsi = w->var("Npsi");
  RooArgSet poi(*Npsi);
  RooArgSet *nullParams = (RooArgSet*) poi.snapshot(); 
  nullParams->setRealValue("Npsi",0.); 

  //Build the profile likelihood calculator
  ProfileLikelihoodCalculator plc; 

  plc.SetData(*(w->data("data"))); 
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
