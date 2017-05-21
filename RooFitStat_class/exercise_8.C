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

  //Configure the model, we need both the S+B and the B only models
  ModelConfig sbModel;
  sbModel.SetWorkspace(*w);
  sbModel.SetPdf("PDFtot");
  sbModel.SetName("S+B Model");
  RooRealVar* poi = w->var("Nsig");
  poi->setRange(0.,30.);  //this is mostly for plotting
  sbModel.SetParametersOfInterest(*poi);

  ModelConfig *bModel = (ModelConfig*) sbModel.Clone();
  bModel->SetPdf("PDFtot");
  bModel->SetName(TString(sbModel.GetName())+TString("_with_poi_0"));      
  poi->setVal(0);
  bModel->SetSnapshot(*poi);

  FrequentistCalculator fc(*(w->data("PDFtotData")), *bModel, sbModel);
  fc.SetToys(2000,1000);

  //Create hypotest inverter passing the desired calculator 
  HypoTestInverter calc(fc);

  // set confidence level (e.g. 95% upper limits)
  calc.SetConfidenceLevel(0.95);

  //use CLs
  calc.UseCLs(true);

  //reduce the noise
  calc.SetVerbose(false);

  //configure ToyMC Samler
  ToyMCSampler *toymcs = (ToyMCSampler*)calc.GetHypoTestCalculator()->GetTestStatSampler();

  //profile likelihood test statistics 
  ProfileLikelihoodTestStat profll(*(sbModel.GetPdf()));
  //for CLs (bounded intervals) use one-sided profile likelihood
  profll.SetOneSided(true);

  //set the test statistic to use 
  toymcs->SetTestStatistic(&profll);

  int npoints = 15;  // number of points to scan
  // min and max (better to choose smaller intervals)
  double poimin = poi->getMin();
  double poimax = poi->getMax();

  cout << "Doing a fixed scan  in interval : " << poimin << " , " << poimax << endl;
  calc.SetFixedScan(npoints,poimin,poimax);
  
  HypoTestInverterResult * r = calc.GetInterval();
  double upperLimit = r->UpperLimit();

  //Example using the BayesianCalculator
  //Now we also need to specify a prior in the ModelConfig
  //To be quicker, we'll use the PDF factory facility of RooWorkspace
  //NB!! For simplicity, we are using a flat prior, but this doesn't mean it's the best choice!
  w->factory("Uniform::prior(Nsig)");
  sbModel.SetPriorPdf(*w->pdf("prior"));

  //Construct the bayesian calculator
  BayesianCalculator bc(*(w->data("PDFtotData")), sbModel);
  bc.SetConfidenceLevel(0.95);
  bc.SetLeftSideTailFraction(0.); // for upper limit
  SimpleInterval* bcInt = bc.GetInterval();

  //Now let's print the result of the two methods
  //First the CLs
  cout << "################" << endl;
  cout << "The computed CLs upper limit is: " << upperLimit << endl;

  //Compute expected limit
  cout << "Expected upper limits, using the B (alternate) model : " << endl;
  cout << " expected limit (median) " << r->GetExpectedUpperLimit(0) << endl;
  cout << " expected limit (-1 sig) " << r->GetExpectedUpperLimit(-1) << endl;
  cout << " expected limit (+1 sig) " << r->GetExpectedUpperLimit(1) << endl;

  cout << "################" << endl;

  //Now let's see what the bayesian limit is
  cout << "Bayesian upper limit on Nsig = " << bcInt->UpperLimit() << endl;

  // plot now the result of the scan 
  //First the CLs
  HypoTestInverterPlot *plot = new HypoTestInverterPlot("HTI_Result_Plot","HypoTest Scan Result",r);
  //Then the Bayesian posterior
  RooPlot *bcPlot = bc.GetPosteriorPlot();

  // plot in a new canvas with style
  TCanvas dataCanvas("dataCanvas");
  dataCanvas.Divide(2,1);
  dataCanvas.SetLogy(false);
  dataCanvas.cd(1);
  plot->Draw("2CL");
  dataCanvas.cd(2);
  bcPlot->Draw();

  dataCanvas.SaveAs("exercise_8.gif");
}
