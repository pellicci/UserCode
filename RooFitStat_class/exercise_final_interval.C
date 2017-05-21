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
  w->var("meanpsi")->setConstant(kFALSE); //Parameter of interest, don't fix
  w->var("a1")->setConstant(kTRUE);
  w->var("a2")->setConstant(kTRUE);
  w->var("a3")->setConstant(kTRUE);
  w->var("Nbkg")->setConstant(kTRUE);
  w->var("NJpsi")->setConstant(kTRUE);
  w->var("Npsi")->setConstant(kTRUE);

  //Set the RooModelConfig and let it know what the content of the workspace is about
  ModelConfig model;
  model.SetWorkspace(*w);
  model.SetPdf("totPDF");

  //Let the model know what is the parameter of interest
  RooRealVar* meanpsi = w->var("meanpsi");
  meanpsi->setRange(3.6, 3.75);   //this is mostly for plotting reasons
  meanpsi->setBins(20);
  RooArgSet poi(*meanpsi);

  // set confidence level
  double confidenceLevel = 0.68;

  //Build the profile likelihood calculator
  ProfileLikelihoodCalculator plc; 
  plc.SetData(*(w->data("data"))); 
  plc.SetModel(model);
  plc.SetParameters(poi);
  plc.SetConfidenceLevel(confidenceLevel);

  //Get the interval
  LikelihoodInterval* plInt = plc.GetInterval();

  // Let's make a plot
  TCanvas dataCanvas("dataCanvas");
  dataCanvas.cd();

  LikelihoodIntervalPlot plotInt((LikelihoodInterval*)plInt);
  plotInt.SetTitle("Profile Likelihood Ratio and Posterior for mH");
  plotInt.SetMaximum(3.);
  plotInt.Draw();

  dataCanvas.SaveAs("exercise_final_interval.gif");

  //Now print the interval for mH for the two methods
  cout << "PLC interval is [" << plInt->LowerLimit(*meanpsi) << ", " << 
    plInt->UpperLimit(*meanpsi) << "]" << endl;


}
