{

  TFile f1("h_200_prova.root");
  f1.cd();

  TH1F *hmm = (TH1F*)f1.Get("hMassH12");
  hmm->Rebin(2);

  RooRealVar mm("mm","mm",386.,410.);

  RooDataHist hdata("hdata","hdata",RooArgList(mm),hmm);

  RooRealVar mean1("mean1","mean1",400.,390.,410.);
  RooRealVar mean2("mean2","mean2",400.,350.,410.);
  RooRealVar mean3("mean3","mean3",400.,350.,410.);
  RooRealVar mean4("mean4","mean4",400.,350.,410.);

  RooRealVar sigma1("sigma1","sigma1",20.,0.001,200.);
  RooRealVar sigma2("sigma2","sigma2",20.,0.001,200.);
  RooRealVar sigma3("sigma3","sigma3",20.,0.001,200.);
  RooRealVar sigma4("sigma4","sigma4",20.,0.001,200.);

  RooRealVar alpha("alpha","alpha",1.5,0.,10.);
  RooRealVar alpha2("alpha2","alpha2",1.5,0.,10.);
  RooRealVar n("n","n",1.4,0.1,10.);
  RooRealVar n2("n2","n2",1.4,0.1,10.);
  RooRealVar tail("tail","tail",0.99,0.,10.);

  RooRealVar frac1("frac1","frac1",0.5,0.,1.);
  RooRealVar frac2("frac2","frac2",0.5,0.,1.);
  RooRealVar frac3("frac3","frac3",0.5,0.,1.);

  RooCBShape g1("g1","g1",mm,mean1,sigma1,alpha,n);
  RooGaussian g2("g2","g2",mm,mean2,sigma2);
  RooCBShape g3("g3","g3",mm,mean1,sigma3,alpha2,n2);
  RooGaussian g4("g4","g4",mm,mean4,sigma4);

  RooAddPdf gp("gp","gp",RooArgList(g1,g2),RooArgList(frac1));
  RooAddPdf gs("gs","gs",RooArgList(g2,g4),RooArgList(frac2));

  RooAddPdf g("g","g",RooArgList(gp,gs),RooArgList(frac2));

  //n.setConstant(kTRUE);
  //alpha.setConstant(kTRUE);

  /*
  RooBifurGauss g1("g1","g1",mm,mean1,sigma1,sigma2);
  RooCBShape g1("g1","g1",mm,mean1,sigma1,alpha,n);
  RooGaussian g2("g2","g2",mm,mean2,sigma2);
  
  RooCBShape g3("g3","g3",mm,mean1,sigma1,alpha,n);
  RooGaussian g4("g4","g4",mm,mean2,sigma3);
  
  RooRealVar frac1("frac1","frac1",0.5,0.,1.);
  RooAddPdf g("g","g",RooArgList(g1,g2),RooArgList(frac1));

  RooRealVar frac2("frac2","frac2",0.5,0.,1.);
  RooAddPdf gp("gp","gp",RooArgList(g3,g4),RooArgList(frac2));

  RooRealVar frac3("frac3","frac3",0.5,0.,1.);
  RooAddPdf gt("gt","gt",RooArgList(g1,gp),RooArgList(frac3));
  */

  g.fitTo(hdata);

  RooPlot *xframe = mm.frame();
  hdata.plotOn(xframe);
  g.plotOn(xframe);

  TCanvas c1;
  c1.cd();xframe->Draw();
  c1.SaveAs("m12.gif");


}
