{

  gSystem->Load("libRooFit");

  RooRealVar mass("mass","The invariant mass",7.,14.);

  //Signal PDF
  //change sigma1 to 0.3 and sigma2 to 0.5 to see a 10% bias on sigma1
  RooRealVar mean1("mean1","Mean of first signal gaussian",9.4,8.,11.);
  RooRealVar sigma1("sigma1","Sigma of first signal gaussian",0.1,0.001,2.);
  RooGaussian SigGauss1("SigGauss1","First signal gaussian",mass,mean1,sigma1);

  RooRealVar mean2("mean2","Mean of second signal gaussian",10.5,9.,12.);
  RooRealVar sigma2("sigma2","Sigma of second signal gaussian",0.2,0.001,2.);
  RooGaussian SigGauss2("SigGauss2","Second signal gaussian",mass,mean2,sigma2);

  RooRealVar fracGauss("fracGauss","Fraction for signal PDFs",0.4,0.,1.);
  RooAddPdf totSigPDF("totSigPDF","Total Signal PDF",RooArgList(SigGauss1,SigGauss2),RooArgList(fracGauss));

  //Background PDF
  RooRealVar a0("a0","a0",-0.3,-0.8,0.8);
  RooRealVar a1("a1","a1",-0.1,-0.8,0.8);
  RooChebychev BkgPDF("BkgPDF","BkgPDF",mass,RooArgSet(a0,a1));

  //Total PDF
  RooRealVar Nsig("Nsig","Number of signal events",900.,0.1,3000.);
  RooRealVar Nbkg("Nbkg","Number of background events",100.,0.1,3000.);

  RooAddPdf totPDF("totPDF","Total PDF",RooArgList(totSigPDF,BkgPDF),RooArgList(Nsig,Nbkg));

  /*
  RooDataSet *data = totPDF->generate(RooArgSet(mass),1000);
  totPDF.fitTo(*data);

  RooPlot *xframe = mass.frame();
  data->plotOn(xframe);
  totPDF.plotOn(xframe);

  TCanvas c1;
  xframe->Draw();
  */

  //Construct the Toy-MC machinery
  //Binned(kTRUE)
  RooMCStudy mcstudy(totPDF,mass,RooFit::Silence(),RooFit::Extended(),RooFit::FitOptions(RooFit::Save(kTRUE),RooFit::PrintEvalErrors(0)));
  mcstudy.generateAndFit(1000);

  //Plot the distributions of the fitted parameter, the error and the pull
  RooPlot *sigma1val_frame = mcstudy->plotParam(sigma1,RooFit::Bins(40));
  RooPlot *sigma1err_frame = mcstudy->plotError(sigma1,RooFit::Bins(40));
  RooPlot *sigma1pull_frame = mcstudy->plotPull(sigma1,RooFit::Bins(40),RooFit::FitGauss(kTRUE));

  //Plot distribution of minimized likelihood
  RooPlot *NLLframe = mcstudy->plotNLL(RooFit::Bins(40));

  //Actually plot
  TCanvas c1;
  c1.Divide(2,2);
  c1.cd(1);
  sigma1val_frame->Draw();
  c1.cd(2);
  sigma1err_frame->Draw();
  c1.cd(3);
  sigma1pull_frame->Draw();
  c1.cd(4);
  NLLframe->Draw();

}
