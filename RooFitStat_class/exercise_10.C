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

  //We will partly redo exercise_0 to redefine the signal PDF to account for uncertainties on parameters
  //Signal PDF
  RooGaussian *gauss = (RooGaussian*)w->pdf("gauss");

  //Background PDF
  RooExponential *exponential = (RooExponential*)w->pdf("exponential");

  //Now define the number of signal and background events
  RooRealVar *Nsig = w->var("Nsig");
  RooRealVar *Nbkg = w->var("Nbkg");

  //Assume an uncertainty on the number of background events
  //Construct the uncertainty with a lognormal assumption
  RooRealVar Nbkg_alpha("Nbkg_alpha","Dimension of systematic variation of Nbkg",1.,0.01,10.);
  RooFormulaVar Nbkg_nuis("Nbkg_nuis","@0*@1",RooArgList(*Nbkg,Nbkg_alpha));

  //Now prepare a gaussian for the nuisance parameter, to be multiplied to the total PDF
  RooRealVar one("one","one",1.);
  RooRealVar Nbkg_syst("Nbkg_syst","The systematic uncertainty on Nbkg",0.3);    //30% uncertainty
  RooGaussian constr_Nbkg("constr_Nbkg","Background uncertainty constraint",one,Nbkg_alpha,Nbkg_syst);

  //Now construct the total PDF
  RooAddPdf PDFtot_nuis_unconstr("PDFtot_nuis_unconstr","PDFtot_nuis_unconstr",RooArgList(*gauss,*exponential),RooArgList(*Nsig,Nbkg_nuis));
 
  //Now add the gaussian constraint to the total PDF
  RooProdPdf PDFtot_nuis("PDFtot_nuis","PDFtot_nuis",RooArgList(PDFtot_nuis_unconstr,constr_Nbkg));

  PDFtot_nuis.fitTo(*w->data("PDFtotData"), RooFit::Constrain(RooArgSet(Nbkg_alpha)),Extended(1));

  //We now have two PDFs and two datasets:
  w->import(PDFtot_nuis);

  //Set the RooModelConfig and let it know what the content of the workspace is about
  ModelConfig model;
  model.SetWorkspace(*w);
  model.SetPdf("PDFtot");

  ModelConfig model_nuis;
  model_nuis.SetWorkspace(*w);
  model_nuis.SetPdf("PDFtot_nuis");

  // here we explicitly set the value of the parameters for the null.  
  // We want no signal contribution, eg. Nsig = 0
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

  //Build the profile likelihood calculator with the Nbkg uncertainty
  ProfileLikelihoodCalculator plc_nuis; 
  plc_nuis.SetData(*(w->data("PDFtotData"))); 
  plc_nuis.SetModel(model_nuis);
  plc_nuis.SetParameters(poi);
  plc_nuis.SetNullParameters(*nullParams);

  // We get a HypoTestResult out of the calculator, and we can query it.
  HypoTestResult* htr_nuis = plc_nuis.GetHypoTest();

  cout << "-------------------------------------------------" << endl;
  cout << "Without background uncertainty" << endl;
  cout << "The p-value for the null is " << htr->NullPValue() << endl;
  cout << "Corresponding to a signifcance of " << htr->Significance() << endl;
  cout << "-------------------------------------------------\n\n" << endl;

  cout << "-------------------------------------------------" << endl;
  cout << "With background uncertainty" << endl;
  cout << "The p-value for the null is " << htr_nuis->NullPValue() << endl;
  cout << "Corresponding to a signifcance of " << htr_nuis->Significance() << endl;
  cout << "-------------------------------------------------\n\n" << endl;

  //Now get the intervals to do some plots
  plc.SetConfidenceLevel(0.68);
  plc_nuis.SetConfidenceLevel(0.68);
  LikelihoodInterval* plInt = plc.GetInterval();
  LikelihoodInterval* plInt_nuis = plc_nuis.GetInterval();

  // Let's make a plot
  TCanvas dataCanvas("dataCanvas");
  dataCanvas.cd();

  LikelihoodIntervalPlot plotInt((LikelihoodInterval*)plInt);
  plotInt.SetTitle("Profile Likelihood Ratio for Nsig");
  plotInt.SetMaximum(10.);
  plotInt.Draw();

  LikelihoodIntervalPlot plotInt_nuis((LikelihoodInterval*)plInt_nuis);
  plotInt_nuis.SetContourColor(kRed);
  plotInt_nuis.Draw("SAME");

  dataCanvas.SaveAs("exercise_10.gif");

}
