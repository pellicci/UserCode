{

  gROOT->SetStyle("BABAR");

  RooRealVar d0Mass("d0Mass","d0Mass",1.74,1.98);

  TFile hello("DataSet_out_tmp.root");
  gROOT->cd();
  RooDataSet *data = (RooDataSet*)hello.Get("fulldata");
  RooDataSet *finaldata = (RooDataSet*)data->reduce("d0LifetimeErr < 0.5 && d0Lifetime > -2. && d0Lifetime < 4. && deltaMass > 0.1449 && deltaMass < 0.1599");
  finaldata->setWeightVar(0);

  cout << "Number of events : " << finaldata->numEntries() << endl;

  TH1F *d0plot = d0Mass.createHistogram("d0plot");
  finaldata->fillHistogram(d0plot,RooArgList(d0Mass));

  RooDataSet *final2 = (RooDataSet*)finaldata->reduce("d0Mass > 1.8495 && d0Mass < 1.8795");
  TH1F *d0plot2 = d0Mass.createHistogram("d0plot2");
  final2->fillHistogram(d0plot2,RooArgList(d0Mass));

  d0plot2->SetFillColor(15);
  d0plot2->SetFillStyle(1001);

  d0plot->GetXaxis()->SetTitle("m_{K#pi#pi^{0}} (GeV/c^{2})");
  d0plot2->GetXaxis()->SetTitle("m_{K#pi#pi^{0}} (GeV/c^{2})");

  d0plot->SetTitle("");
  d0plot2->SetTitle("");

  TCanvas c1;
  c1.cd();d0plot->Draw("HIST");d0plot2->Draw("HIST SAME");
  c1.SaveAs("d0massplot.eps");


}
