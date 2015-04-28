{

  gSystem->Load("libRooFit");

  //Create a gaussian signal PDF
  RooRealVar mass("mass","The invariant mass",100.,150.,"GeV/c^2");
  RooRealVar mean("mean","The mean of the gaussian",125.,110.,140.);
  RooRealVar width("width","The width of the gaussian",2.,0.001,5.);

  RooGaussian gaussPDF("gaussPDF","The gaussian function",mass,mean,width);

  RooDataSet *data = gaussPDF.generate(RooArgSet(mass),1000);

  gaussPDF.fitTo(*data);

  RooPlot *massplot = mass.frame();
  data->plotOn(massplot);
  gaussPDF.plotOn(massplot);

  TCanvas c1;
  c1.cd();
  massplot->Draw();
  c1.SaveAs("exercise_0.pdf");


}
