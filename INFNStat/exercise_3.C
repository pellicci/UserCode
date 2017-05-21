//////////////////////////////////////////////////////////////////////////
//
// First exercise for the CMS DAS
// 
// Hypothesis testing with the Profile Likelihood method
//
// pdf = gauss(x,m,s) + exp(x,tau)
//
//
// 2014 - Mario Pelliccioni, Luca Lista
// 
/////////////////////////////////////////////////////////////////////////

gSystem->Load("libRooFit");
gSystem->Load("libRooStats");

using namespace RooFit;
using namespace RooStats;

void exercise_3() {
  //Open the rootfile and get the workspace from the exercise_0
  TFile fIn("exercise_0.root");
  fIn.cd();
  RooWorkspace *w = (RooWorkspace*)fIn.Get("w");

  //You can set constant parameters that are known
  //If you leave them floating, the fit procedure will determine their uncertainty
  w->var("mean")->setConstant(kFALSE); //don't fix the mean, it's what we want to know the interval for!
  w->var("sigma")->setConstant(kTRUE);
  w->var("tau")->setConstant(kTRUE);
  w->var("Nsig")->setConstant(kTRUE);
  w->var("Nbkg")->setConstant(kTRUE);

  //Set the RooModelConfig and let it know what the content of the workspace is about
  ModelConfig model;
  model.SetWorkspace(*w);
  model.SetPdf("PDFtot");

  //Let the model know what is the parameter of interest
  RooRealVar* mean = w->var("mean");
  mean->setRange(120., 130.);   //this is mostly for plotting reasons
  RooArgSet poi(*mean);

  // set confidence level
  double confidenceLevel = 0.68;

  //Build the profile likelihood calculator
  ProfileLikelihoodCalculator plc; 
  plc.SetData(*(w->data("PDFtotData"))); 
  plc.SetModel(model);
  plc.SetParameters(poi);
  plc.SetConfidenceLevel(confidenceLevel);

  //Get the interval
  LikelihoodInterval* plInt = plc.GetInterval();

  //Now let's do the same for the Bayesian Calculator
  //Now we also need to specify a prior in the ModelConfig
  //To be quicker, we'll use the PDF factory facility of RooWorkspace
  //NB!! For simplicity, we are using a flat prior, but this doesn't mean it's the best choice!
  w->factory("Uniform::prior(mean)");
  model.SetPriorPdf(*w->pdf("prior"));

  //Construct the bayesian calculator
  BayesianCalculator bc(*(w->data("PDFtotData")), model);
  bc.SetConfidenceLevel(confidenceLevel);
  bc.SetParameters(poi);
  SimpleInterval* bcInt = bc.GetInterval();

  // Let's make a plot
  TCanvas dataCanvas("dataCanvas");
  dataCanvas.Divide(2,1);
  dataCanvas.cd(1);

  LikelihoodIntervalPlot plotInt((LikelihoodInterval*)plInt);
  plotInt.SetTitle("Profile Likelihood Ratio and Posterior for mH");
  plotInt.SetMaximum(3.);
  plotInt.Draw();

  dataCanvas.cd(2);
  RooPlot *bcPlot = bc.GetPosteriorPlot();
  bcPlot->Draw();

  dataCanvas.SaveAs("exercise_3.gif");

  //Now print the interval for mH for the two methods
  cout << "PLC interval is [" << plInt->LowerLimit(*mean) << ", " << 
    plInt->UpperLimit(*mean) << "]" << endl;

  cout << "Bayesian interval is [" << bcInt->LowerLimit() << ", " << 
    bcInt->UpperLimit() << "]" << endl;

}
