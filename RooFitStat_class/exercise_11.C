{
  gSystem->Load("libRooFit");
  gSystem->Load("libRooStats");

  using namespace RooFit ;
  using namespace RooStats ;

  // make a simple model
  RooRealVar x("x","Number of observed events", 1,0.,20.);
  RooRealVar mu("mu","The mu parameter", 2.5,0., 15.); // with a limit on mu>=0
  RooConstVar b("b","", 3.);
  RooAddition mean("mean","",RooArgList(mu,b));
  RooPoisson pois("pois", "", x, mean);
  RooArgSet parameters(mu);

  // create a toy dataset
  RooDataSet* data = pois.generate(RooArgSet(x), 1);
  data->Print("v");
  
  TCanvas dataCanvas("dataCanvas");
  dataCanvas.cd();
  RooPlot* frame = x.frame();
  data->plotOn(frame);
  frame->Draw();
  dataCanvas.Update();

  RooWorkspace* w = new RooWorkspace();
  ModelConfig modelConfig("poissonProblem",w);
  modelConfig.SetPdf(pois);
  modelConfig.SetParametersOfInterest(parameters);
  modelConfig.SetObservables(RooArgSet(x));
  w->Print();

  //////// show use of Feldman-Cousins
  FeldmanCousins fc(*data,modelConfig);
  fc.SetTestSize(.05); // set size of test
  fc.UseAdaptiveSampling(true);
  fc.AdditionalNToysFactor(10.);
  fc.FluctuateNumDataEntries(false); // number counting analysis: dataset always has 1 entry with N events observed
  fc.SetNBins(200); // number of points to test per parameter

  // use the Feldman-Cousins tool
  PointSetInterval* interval = (PointSetInterval*)fc.GetInterval();

  std::cout << "The interval is ["<< interval->LowerLimit(mu)  << ", "  << interval->UpperLimit(mu) << "]" << endl;

  // No dedicated plotting class yet, so do it by hand:
  gStyle->SetOptStat(0);
  RooDataHist* parameterScan = (RooDataHist*) fc.GetPointsToScan();
  TH1F* hist = (TH1F*) parameterScan->createHistogram("mu",30);
  hist->GetXaxis()->SetTitle("#mu");
  hist->Draw();

  RooArgSet* tmpPoint;
  // loop over points to test
  for(Int_t i=0; i<parameterScan->numEntries(); ++i){
    //    cout << "on parameter point " << i << " out of " << parameterScan->numEntries() << endl;
    // get a parameter point from the list of points to test.
    tmpPoint = (RooArgSet*) parameterScan->get(i)->clone("temp");

    TMarker* mark = new TMarker(tmpPoint->getRealValue("mu"), 1, 25);
    if(interval->IsInInterval( *tmpPoint ) ) mark->SetMarkerColor(kBlue);
    else mark->SetMarkerColor(kRed);

    mark->Draw("s");
  }

}
