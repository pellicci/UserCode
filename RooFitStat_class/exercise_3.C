{

  TFile fIn("exercise_1.root");
  fIn.cd();

  RooWorkspace *workspace = fIn.Get("myworkspace");

  RooRealVar *mass = workspace->var("mass");
  RooAbsPdf *totPDF = workspace->pdf("totPDF");

  RooDataSet *data = workspace->data("totPDFData");

  RooPlot *massplot = mass->frame();
  data->plotOn(massplot);
  totPDF->plotOn(massplot);

  TCanvas c1;
  c1.cd();
  massplot->Draw();



}
