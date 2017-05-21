{
  TFile fIn("DataSet_final.root");
  fIn.cd();
  RooDataSet *data = (RooDataSet*)fIn.Get("data");

  RooRealVar mass("mass","The invariant mass",2.,6.,"GeV");

  //The Jpsi signal parametrization
  RooRealVar meanJpsi("meanJpsi","The mean of the Jpsi Gaussian",3.1,2.8,3.2);
  RooRealVar sigmaJpsi("sigmaJpsi","The width of the Jpsi Gaussian",0.3,0.001,1.);
  RooRealVar alphaJpsi("alphaJpsi","The alpha of the Jpsi Gaussian",1.5,-5.,5.);
  RooRealVar nJpsi("nJpsi","The alpha of the Jpsi Gaussian",1.5);
  RooCBShape CBJpsi("CBJpsi","The Jpsi Crystall Ball",mass,meanJpsi,sigmaJpsi,alphaJpsi,nJpsi);

  //The psi(2S) signal parametrization
  RooRealVar meanpsi("meanpsi","The mean of the psi Gaussian",3.7,3.5,4.);
  RooGaussian gausspsi("gausspsi","The psi Gaussian",mass,meanpsi,sigmaJpsi);

  //Background parametrization
  RooRealVar a1("a1","The a1 of background",-0.7,-2.,2.);
  RooRealVar a2("a2","The a2 of background",0.3,-2.,2.);
  RooRealVar a3("a3","The a3 of background",-0.03,-2.,2.);
  RooChebychev backPDF("backPDF","The background",mass,RooArgList(a1,a2,a3));

  //Compose the total signal

  //Either with fractions:
  //RooRealVar fracJpsi("fracJpsi","The Jpsi signal fraction",0.6,0.,1.);
  //RooAddPdf totSigPDF("totSigPDF","The total Signal PDF",RooArgList(gaussJpsi,gausspsi),RooArgList(fracJpsi));

  //RooRealVar fracSig("fracSig","The signal fraction",0.2,0.,1.);
  //RooAddPdf totPDF("totPDF","The total PDF",RooArgList(totSigPDF,backPDF),RooArgList(fracSig));

  //Or extended
  RooRealVar NJpsi("NJpsi","The Jpsi signal events",9000.,0.1,20000.);
  RooRealVar Npsi("Npsi","The psi signal events",300.,0.1,600.);
  RooRealVar Nbkg("Nbkg","The bkg events",20000.,0.1,50000.);
  RooAddPdf totPDF("totPDF","The total PDF",RooArgList(CBJpsi,gausspsi,backPDF),RooArgList(NJpsi,Npsi,Nbkg));

  totPDF.fitTo(*data,RooFit::Extended(1));

  RooPlot *xframe = mass.frame();
  data->plotOn(xframe);
  //totPDF.plotOn(xframe);

  TCanvas c1;
  c1.cd();
  xframe->Draw();
  c1.SaveAs("exercise_final.gif");

  RooWorkspace w("w");
  w.import(*data);
  w.import(totPDF);

  TFile fOut("Workspace_final.root","RECREATE");
  fOut.cd();
  w.Write();
  fOut.Write();
  fOut.Close();


}
