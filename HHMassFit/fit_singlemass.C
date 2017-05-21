{
  gROOT->SetStyle("Plain");

  TFile f1("h_200_prova.root");
  f1.cd();

  TH1F *hmm = (TH1F*)f1.Get("hMassH1");
  hmm->Rebin(5);

  RooRealVar mm("mm","Single Higgs mass",160.,240.,"GeV/c^{2}");

  RooDataHist hdata("hdata","hdata",RooArgList(mm),hmm);

  RooRealVar mean1("mean1","mean1",200.,195.,205.);
  RooRealVar mean2("mean2","mean2",200.,195.,205.);

  RooRealVar sigma1("sigma1","sigma1",10.,0.001,50.);
  RooRealVar sigma2("sigma2","sigma2",10.,0.001,50.);
  RooRealVar sigma3("sigma3","sigma3",10.,0.001,50.);
  RooRealVar sigma4("sigma4","sigma4",50.,0.01,100.);

  RooRealVar alpha("alpha","alpha",1.5,0.,100.);
  RooRealVar n("n","n",0.75,0.1,100.);
  RooRealVar tail("tail","tail",1.,0.00001,10.);

  RooCBShape g1("g1","g1",mm,mean1,sigma1,alpha,n);
  RooGaussian g2("g2","g2",mm,mean2,sigma2);

  RooRealVar frac1("frac1","frac1",0.5,0.,1.);
  RooAddPdf g("g","g",RooArgList(g1,g2),RooArgList(frac1));

  g.fitTo(hdata);

  RooPlot *xframe = mm.frame();
  hdata.plotOn(xframe);
  g.plotOn(xframe);

  TCanvas c1;
  c1.cd();xframe->Draw();
  c1.SaveAs("m1.gif");


}
