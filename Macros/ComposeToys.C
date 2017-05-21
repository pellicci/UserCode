{

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  RooArgSet params;               

  RooRealVar c1("c1","c1",-0.5,0.5);
  RooRealVar c2("c2","c2",-0.5,0.5);
  params.add(c1);
  params.add(c2);

  RooRealVar c1err("c1err","c1err",0.,0.2);
  RooRealVar c2err("c2err","c2err",0.,0.2);
  params.add(c1err);
  params.add(c2err);

  RooRealVar c1pull("c1pull","c1pull",-3.2,3.2);
  RooRealVar c2pull("c2pull","c2pull",-3.2,3.2);
  params.add(c1pull);
  params.add(c2pull);

  RooRealVar Kstminus_amp("Kstminus_amp","Kstplus_amp",0.,5.4);
  RooRealVar Kstminus_phase("Kstminus_phase","Kstplus_phase",-200.,200.);
  RooRealVar Kstzero_amp("Kstzero_amp","Kstzero_amp",0.,0.7);
  RooRealVar Kstzero_phase("Kstzero_phase","Kstzero_phase",-50.,100.);
  params.add(Kstminus_amp);
  params.add(Kstminus_phase);
  params.add(Kstzero_amp);
  params.add(Kstzero_phase);

  RooRealVar Kstzero_amperr("Kstzero_amperr","Kstplus_amperr",0.,0.2);
  RooRealVar Kstzero_phaseerr("Kstzero_phaseerr","Kstplus_phaseerr",0.,10.);
  RooRealVar Kstminus_amperr("Kstminus_amperr","Kstplus_amperr",0.,3.);
  RooRealVar Kstminus_phaseerr("Kstminus_phaseerr","Kstplus_phaseerr",0.,100.);
  params.add(Kstzero_amperr);
  params.add(Kstzero_phaseerr);
  params.add(Kstminus_amperr);
  params.add(Kstminus_phaseerr);

  RooRealVar Kstzero_amppull("Kstzero_amppull","Kstplus_amppull",-3.2,3.2);
  RooRealVar Kstzero_phasepull("Kstzero_phasepull","Kstplus_phasepull",-3.2,3.2);
  RooRealVar Kstminus_amppull("Kstminus_amppull","Kstplus_amppull",-3.2,3.2);
  RooRealVar Kstminus_phasepull("Kstminus_phasepull","Kstplus_phasepull",-3.2,3.2);
  params.add(Kstzero_amppull);
  params.add(Kstzero_phasepull);
  params.add(Kstminus_amppull);
  params.add(Kstminus_phasepull);

  RooRealVar myratio("myratio","myratio",0.,0.,0.01);
  RooRealVar myx("myx","myx",0.,-0.04,0.04);
  RooRealVar myy("myy","myy",0.,-0.1,0.25);

  RooRealVar finalr0("finalr0","finalr0",0.003,0.008);
  RooRealVar finalr0err("finalr0err","finalr0err",0.,0.,0.002);
  RooRealVar finalx("finalx","finalx",0.,-0.04,0.05);
  RooRealVar finalxerr("finalxerr","finalxerr",0.,0.,0.013);
  RooRealVar finaly("finaly","finaly",0.,-0.04,0.04);
  RooRealVar finalyerr("finalyerr","finalyerr",0.,0.,0.013);

  RooRealVar residualx("residualx","residualx",-1.,1.);
  RooRealVar residualy("residualy","residualy",-1.,1.);

  RooDataSet *finalPars = new RooDataSet("finalPars","finalPars",RooArgSet(finalr0,finalr0err,finalx,finalxerr,finaly,finalyerr,residualx,residualy));

  TFile f("toy_tmp.root");
  f.cd();
  TTree *tree = (TTree*)f.Get("fitParData");
  RooDataSet *mypars = new RooDataSet("fitParData","fitParData",tree,RooArgSet(params));
  /*
    for(Int_t i=1;i<=2000;i++){

    char filename1[200];
    sprintf(filename1,"Toy_results/UNBLIND/toy_%d_float.root",i);
    TFile f1(filename1);

    if(f1.GetSize() <=0) continue;

    RooDataSet *tmpy1 = (RooDataSet*)f1.Get("parFloat");

    RooPlot* r0frame = myratio.frame(50);
    tmpy1->plotOn(r0frame);
    finalr0.setVal(tmpy1->fillHistogram(r0frame,RooArgList(myratio))->GetMean());
    finalr0err.setVal(tmpy1->fillHistogram(r0frame,RooArgList(myratio))->GetRMS());

    RooPlot* xframe = myx.frame(50);
    tmpy1->plotOn(xframe);
    finalx.setVal(tmpy1->fillHistogram(xframe,RooArgList(myx))->GetMean());
    finalxerr.setVal(tmpy1->fillHistogram(xframe,RooArgList(myx))->GetRMS());

    RooPlot* yframe = myy.frame(50);
    tmpy1->plotOn(yframe);
    finaly.setVal(tmpy1->fillHistogram(yframe,RooArgList(myy))->GetMean());
    finalyerr.setVal(tmpy1->fillHistogram(yframe,RooArgList(myy))->GetRMS());

    f1.Close();

    finalPars->add(RooArgSet(finalr0,finalr0err,finalx,finalxerr,finaly,finalyerr));

    tmpy1 = NULL;
    }
    TFile fp("myfinalpars.root","RECREATE");
    fp.cd();
    mypars->Write();
    finalPars->Write();
    fp.Close();

    RooFormulaVar x_pull("x_pull","(@0-0.0236927)/@1",RooArgList(finalx,finalxerr));
    RooFormulaVar y_pull("y_pull","(@0+0.00214914)/@1",RooArgList(finaly,finalyerr));
    RooFormulaVar r0_pull("r0_pull","(@0-0.00543482)/@1",RooArgList(finalr0,finalr0err));

    finalPars->addColumn(x_pull);
    finalPars->addColumn(y_pull);
    finalPars->addColumn(r0_pull);

    RooRealVar xpull("x_pull","x_pull",-3.,3.);
    RooRealVar ypull("y_pull","y_pull",-3.,3.);
    RooRealVar r0pull("r0_pull","r0_pull",-3.,3.);
  */
  Double_t c1low,c1high,c1elow,c1ehigh,c1plow,c1phigh;
  Double_t c2low,c2high,c2elow,c2ehigh,c2plow,c2phigh;

  Bool_t c1bool = mypars->getRange(c1,c1low,c1high);
  Bool_t c1ebool = mypars->getRange(c1err,c1elow,c1ehigh);
  Bool_t c1pbool = mypars->getRange(c1pull,c1plow,c1phigh);

  Bool_t c2bool = mypars->getRange(c2,c2low,c2high);
  Bool_t c2ebool = mypars->getRange(c2err,c2elow,c2ehigh);
  Bool_t c2pbool = mypars->getRange(c2pull,c2plow,c2phigh);

  RooRealVar c1pull_mean("c1pull_mean","c1pull_mean",0.,-3.,3.);
  RooRealVar c1pull_sigma("c1pull_sigma","c1pull_sigma",0.1,0.,2.);
  RooGaussian gauss_pullc1("gauss_pullc1","gauss_pullc1",c1pull,c1pull_mean,c1pull_sigma);

  RooRealVar c2pull_mean("c2pull_mean","c2pull_mean",0.,-3.,3.);
  RooRealVar c2pull_sigma("c2pull_sigma","c2pull_sigma",2.,0.,2.);
  RooGaussian gauss_pullc2("gauss_pullc2","gauss_pullc2",c2pull,c2pull_mean,c2pull_sigma);

  RooRealVar Kstzero_amppull_mean("Kstzero_amppull_mean","Kstzero_amppull_mean",0.,-3.,3.);
  RooRealVar Kstzero_amppull_sigma("Kstzero_amppull_sigma","Kstzero_amppull_sigma",0.1,0.,2.);
  RooGaussian gauss_pullKstzero_amp("gauss_pullKstzero_amp","gauss_pullKstzero_amp",Kstzero_amppull,Kstzero_amppull_mean,Kstzero_amppull_sigma);

  RooRealVar Kstzero_phasepull_mean("Kstzero_phasepull_mean","Kstzero_phasepull_mean",0.,-3.,3.);
  RooRealVar Kstzero_phasepull_sigma("Kstzero_phasepull_sigma","Kstzero_phasepull_sigma",0.1,0.,2.);
  RooGaussian gauss_pullKstzero_phase("gauss_pullKstzero_phase","gauss_pullKstzero_phase",Kstzero_phasepull,Kstzero_phasepull_mean,Kstzero_phasepull_sigma);
  /*
    RooRealVar xpull_mean("xpull_mean","xpull_mean",0.,-3.,3.);
    RooRealVar xpull_sigma("xpull_sigma","xpull_sigma",0.1,0.,2.);
    RooGaussian gauss_pullx("gauss_pullx","gauss_pullx",xpull,xpull_mean,xpull_sigma);

    RooRealVar ypull_mean("ypull_mean","ypull_mean",0.,-3.,3.);
    RooRealVar ypull_sigma("ypull_sigma","ypull_sigma",0.1,0.,2.);
    RooGaussian gauss_pully("gauss_pully","gauss_pully",ypull,ypull_mean,ypull_sigma);

    RooRealVar r0pull_mean("r0pull_mean","r0pull_mean",0.,-3.,3.);
    RooRealVar r0pull_sigma("r0pull_sigma","r0pull_sigma",0.1,0.,2.);
    RooGaussian gauss_pullr0("gauss_pullr0","gauss_pullr0",r0pull,r0pull_mean,r0pull_sigma);
  */
  gauss_pullc1.fitTo(*mypars);
  gauss_pullc2.fitTo(*mypars);
  gauss_pullKstzero_amp.fitTo(*mypars);
  gauss_pullKstzero_phase.fitTo(*mypars);
  //gauss_pullx.fitTo(*finalPars);
  //gauss_pully.fitTo(*finalPars);
  //gauss_pullr0.fitTo(*finalPars);

  Int_t nBins = 15;

  RooPlot *c1plot = c1.frame(50);
  mypars->plotOn(c1plot,RooFit::MarkerSize(0.1));
  c1plot->SetTitle("c_{1} fit value");
  c1plot->GetXaxis()->SetTitle("");

  RooPlot *c2plot = c2.frame(50);
  mypars->plotOn(c2plot,RooFit::MarkerSize(0.1));
  c2plot->SetTitle("c_{2} fit value");
  c2plot->GetXaxis()->SetTitle("");

  RooPlot *c1eplot = c1err.frame(nBins);
  mypars->plotOn(c1eplot,RooFit::MarkerSize(0.1));
  c1eplot->SetTitle("c_{1} fit error");
  c1eplot->GetXaxis()->SetTitle("");

  RooPlot *c2eplot = c2err.frame(nBins);
  mypars->plotOn(c2eplot,RooFit::MarkerSize(0.1));
  c2eplot->SetTitle("c_{2} fit error");
  c2eplot->GetXaxis()->SetTitle("");

  RooPlot *c1pplot = c1pull.frame(30);
  mypars->plotOn(c1pplot,RooFit::MarkerSize(0.1));
  gauss_pullc1.plotOn(c1pplot);
  c1pplot->getAttLine()->SetLineWidth(1);
  c1pplot->getAttLine()->SetLineStyle(1);
  c1pplot->SetTitle("c_{1} pull");
  c1pplot->GetXaxis()->SetTitle("");

  RooPlot *c2pplot = c2pull.frame(30);
  mypars->plotOn(c2pplot,RooFit::MarkerSize(0.1));
  gauss_pullc2.plotOn(c2pplot);
  c2pplot->getAttLine()->SetLineWidth(1);
  c2pplot->getAttLine()->SetLineStyle(1);
  c2pplot->SetTitle("c_{2} pull");
  c2pplot->GetXaxis()->SetTitle("");

  TCanvas *canv = new TCanvas();
  canv->Divide(3,2);
  canv->cd(1);c1plot->Draw();
  canv->cd(2);c1eplot->Draw();
  canv->cd(3);c1pplot->Draw();
  canv->cd(4);c2plot->Draw();
  canv->cd(5);c2eplot->Draw();
  canv->cd(6);c2pplot->Draw();
  canv->SaveAs("Toy.eps");

  /*
    RooPlot* r0frame = finalr0.frame(20);
    finalPars->plotOn(r0frame,RooFit::MarkerSize(0.1));
    r0frame->SetTitle("Distribution of r_{0}^{2}");
    r0frame->GetXaxis()->SetTitle("r^{0}");

    RooPlot* r0errframe = finalr0err.frame(20);
    finalPars->plotOn(r0errframe,RooFit::MarkerSize(0.1));
    r0errframe->SetTitle("Distribution of #sigma_{r_{0}^{2}}");
    r0errframe->GetXaxis()->SetTitle("#sigma_{r^{0}}");

    RooPlot* r0pframe = r0pull.frame(20);
    finalPars->plotOn(r0pframe,RooFit::MarkerSize(0.1));
    gauss_pullr0.plotOn(r0pframe);
    r0pframe->getAttLine()->SetLineWidth(1);
    r0pframe->getAttLine()->SetLineStyle(1);
    r0pframe->SetTitle("Distribution of r_{0} pull");
    r0pframe->GetXaxis()->SetTitle("r_{0} pull");

    RooPlot* xframe = finalx.frame(20);
    finalPars->plotOn(xframe,RooFit::MarkerSize(0.1));
    xframe->SetTitle("Distribution of x^{'}");
    xframe->GetXaxis()->SetTitle("x^{'}");

    RooPlot* xerrframe = finalxerr.frame(20);
    finalPars->plotOn(xerrframe,RooFit::MarkerSize(0.1));
    xerrframe->SetTitle("Distribution of #sigma_{x^{'}}");
    xerrframe->GetXaxis()->SetTitle("#sigma_{x^{'}}");

    RooPlot* xpframe = xpull.frame(20);
    finalPars->plotOn(xpframe,RooFit::MarkerSize(0.1));
    gauss_pullx.plotOn(xpframe);
    xpframe->getAttLine()->SetLineWidth(1);
    xpframe->getAttLine()->SetLineStyle(1);
    xpframe->SetTitle("Distribution of x^{'} pull");
    xpframe->GetXaxis()->SetTitle("x^{'} pull");

    RooPlot* yframe = finaly.frame(20);
    finalPars->plotOn(yframe,RooFit::MarkerSize(0.1));
    yframe->SetTitle("Distribution of y^{'}");
    yframe->GetXaxis()->SetTitle("y^{'}");

    RooPlot* yerrframe = finalyerr.frame(20);
    finalPars->plotOn(yerrframe,RooFit::MarkerSize(0.1));
    yerrframe->SetTitle("Distribution of #sigma_{y^{'}}");
    yerrframe->GetXaxis()->SetTitle("#sigma_{y^{'}}");

    RooPlot* ypframe = ypull.frame(20);
    finalPars->plotOn(ypframe,RooFit::MarkerSize(0.1));
    gauss_pully.plotOn(ypframe);
    ypframe->getAttLine()->SetLineWidth(1);
    ypframe->getAttLine()->SetLineStyle(1);
    ypframe->SetTitle("Distribution of y^{'} pull");
    ypframe->GetXaxis()->SetTitle("y^{'} pull");

    TCanvas *c = new TCanvas();
    c->Divide(3,3);
    c->cd(1);r0frame->Draw();
    c->cd(2);r0errframe->Draw();
    c->cd(3);r0pframe->Draw();
    c->cd(4);xframe->Draw();
    c->cd(5);xerrframe->Draw();
    c->cd(6);xpframe->Draw();
    c->cd(7);yframe->Draw();
    c->cd(8);yerrframe->Draw();
    c->cd(9);ypframe->Draw();
    c->SaveAs("Toy_xyr0.eps");

    TH2F *h1 = new TH2F("h1","h1",30,-0.01,0.02,30,0.,0.02);
    h1 = finalPars.createHistogram(finalx,finaly);
    h1->SetTitle("");
    h1->GetXaxis()->SetTitle("x^{'}");
    h1->GetYaxis()->SetTitle("y^{'}");
    TCanvas tmpo;
    tmpo.cd();
    h1->Draw("colz");
    tmpo.SaveAs("boh.eps");
  */
  RooPlot *Kstzero_aplot = Kstzero_amp.frame(40);
  mypars->plotOn(Kstzero_aplot,RooFit::MarkerSize(0.1));
  Kstzero_aplot->SetTitle("K^{*0} amplitude fit value");
  Kstzero_aplot->GetXaxis()->SetTitle("");

  RooPlot *Kstzero_pplot = Kstzero_phase.frame(40);
  mypars->plotOn(Kstzero_pplot,RooFit::MarkerSize(0.1));
  Kstzero_pplot->SetTitle("K^{*0} phase fit value");
  Kstzero_pplot->GetXaxis()->SetTitle("");

  RooPlot *Kstzero_aeplot = Kstzero_amperr.frame(40);
  mypars->plotOn(Kstzero_aeplot,RooFit::MarkerSize(0.1));
  Kstzero_aeplot->SetTitle("K^{*0} amplitude error");
  Kstzero_aeplot->GetXaxis()->SetTitle("");

  RooPlot *Kstzero_peplot = Kstzero_phaseerr.frame(40);
  mypars->plotOn(Kstzero_peplot,RooFit::MarkerSize(0.1));
  Kstzero_peplot->SetTitle("K^{*0} phase error");
  Kstzero_peplot->GetXaxis()->SetTitle("");

  RooPlot *Kstzero_ampplot = Kstzero_amppull.frame(40);
  mypars->plotOn(Kstzero_ampplot,RooFit::MarkerSize(0.1));
  gauss_pullKstzero_amp.plotOn(Kstzero_ampplot);
  Kstzero_ampplot->getAttLine()->SetLineWidth(1);
  Kstzero_ampplot->getAttLine()->SetLineStyle(1);
  Kstzero_ampplot->SetTitle("K^{*0} amplitude pull");
  Kstzero_ampplot->GetXaxis()->SetTitle("");

  RooPlot *Kstzero_phaseplot = Kstzero_phasepull.frame(40);
  mypars->plotOn(Kstzero_phaseplot,RooFit::MarkerSize(0.1));
  gauss_pullKstzero_phase.plotOn(Kstzero_phaseplot);
  Kstzero_phaseplot->getAttLine()->SetLineWidth(1);
  Kstzero_phaseplot->getAttLine()->SetLineStyle(1);
  Kstzero_phaseplot->SetTitle("K^{*0} phase pull");
  Kstzero_phaseplot->GetXaxis()->SetTitle("");

  TCanvas *canva2 = new TCanvas();
  canva2->Divide(3,2);
  canva2->cd(1);Kstzero_aplot->Draw();
  canva2->cd(2);Kstzero_aeplot->Draw();
  canva2->cd(3);Kstzero_ampplot->Draw();
  canva2->cd(4);Kstzero_pplot->Draw();
  canva2->cd(5);Kstzero_peplot->Draw();
  canva2->cd(6);Kstzero_phaseplot->Draw();
  canva2->SaveAs("Toydalitz.eps");

}
