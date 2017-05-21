{

RooRealVar x("x","x",0.,200.);
x.setBins(25);

RooRealVar mean1("mean1","mean1",75.97,30.,80.);
RooRealVar sigma1("sigma1","sigma1",17.45.,0.,40.);
RooRealVar N1("N1","N1",30.,0.,50.);

RooRealVar mean2("mean2","mean2",91.73,30.,160.);
RooRealVar sigma2("sigma2","sigma2",3.77,1.,20.);
RooRealVar N2("N2","N2",10.,0.,50.);

RooGaussian g1("g1","g1",x,mean1,sigma1);
RooGaussian g2("g2","g2",x,mean2,sigma2);

RooAddPdf gtot("gtot","gtot",RooArgList(g1,g2),RooArgList(N1,N2));

mean1.setConstant(kTRUE);
sigma1.setConstant(kTRUE);
mean2.setConstant(kTRUE);
sigma2.setConstant(kTRUE);


TFile pippo("pippo.root");
pippo.cd();

TH1F *h = pippo.Get("massZ1");
h->Rebin(4);

RooDataHist histo("histo","histo",RooArgList(x),h);

gtot.fitTo(histo,RooFit::Extended(1));

RooPlot *xplot = x.frame(25);
histo.plotOn(xplot);
gtot.plotOn(xplot);

TCanvas c1;
c1.cd();
xplot->Draw();


}
