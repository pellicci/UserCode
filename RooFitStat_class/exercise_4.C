{

  gSystem->Load("libRooFit");

  RooRealVar mass("mass","The invariant mass",100.,150.);

  //Signal PDF
  RooRealVar mean1("mean1","Mean of first signal gaussian",125.,110.,140.);
  RooRealVar sigma1("sigma1","Sigma of first signal gaussian",1.,0.001,4.);
  RooGaussian SigGauss1("SigGauss1","First signal gaussian",mass,mean1,sigma1);

  //Background PDF
  RooRealVar a0("a0","a0",-1.,-3.,3.);
  RooRealVar a1("a1","a1",0.5,-3.,3.);
  RooChebychev BkgPDF("BkgPDF","BkgPDF",mass,RooArgSet(a0,a1));

  //Total first PDF
  RooRealVar frac1("frac1","Fraction for first PDF",0.6,0.,1.);
  RooAddPdf totPDF1("totPDF1","Total PDF 1",RooArgList(SigGauss1,BkgPDF),RooArgList(frac1));

  //Build the second signal PDF
  RooRealVar sigma2("sigma2","Sigma of second signal gaussian",2.,0.001,4.);
  RooGaussian SigGauss2("SigGauss2","Second signal gaussian",mass,mean1,sigma2);

  //Total second PDF
  RooRealVar frac2("frac2","Fraction for second PDF",0.4,0.,1.);
  RooAddPdf totPDF2("totPDF2","Total PDF 2",RooArgList(SigGauss2,BkgPDF),RooArgList(frac2));

  //Generate the two samples
  RooDataSet *data1 = totPDF1.generate(RooArgSet(mass),1000);
  RooDataSet *data2 = totPDF2.generate(RooArgSet(mass),2000);

  RooCategory SigCat("SigCat","Signal categories");
  SigCat.defineType("Signal1");
  SigCat.defineType("Signal2");

  RooDataSet combinedData("combinedData","The combined data",mass,RooFit::Index(SigCat),RooFit::Import("Signal1",*data1),RooFit::Import("Signal2",*data2));

  //Construct the simultaneous PDF
  RooSimultaneous simPdf("simPdf","The total simultaneous PDF",SigCat);
  simPdf.addPdf(totPDF1,"Signal1");
  simPdf.addPdf(totPDF2,"Signal2");

  //Do the fitting
  simPdf.fitTo(combinedData);

  //Do the plotting

  //Separately for the two categories
  RooPlot *massframe1 = mass.frame();
  combinedData.plotOn(massframe1,RooFit::Cut("SigCat==SigCat::Signal1"));
  simPdf.plotOn(massframe1,RooFit::Slice(SigCat,"Signal1"),RooFit::ProjWData(SigCat,combinedData));
  simPdf.plotOn(massframe1,RooFit::Slice(SigCat,"Signal1"),RooFit::ProjWData(SigCat,combinedData),RooFit::Components("BkgPDF"),RooFit::LineStyle(kDashed));

  RooPlot *massframe2 = mass.frame();
  combinedData.plotOn(massframe2,RooFit::Cut("SigCat==SigCat::Signal2"));
  simPdf.plotOn(massframe2,RooFit::Slice(SigCat,"Signal2"),RooFit::ProjWData(SigCat,combinedData));
  simPdf.plotOn(massframe2,RooFit::Slice(SigCat,"Signal2"),RooFit::ProjWData(SigCat,combinedData),RooFit::Components("BkgPDF"),RooFit::LineStyle(kDashed));

  TCanvas c1;
  c1.Divide(2,1);
  c1.cd(1);
  massframe1->Draw();
  c1.cd(2);
  massframe2->Draw();



}
