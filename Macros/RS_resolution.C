#include <iostream>

#include <BaBarStyle.h>

#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TPaveText.h>
#include <TStyle.h>

#include <RooRealVar.h>
#include <RooCategory.h>
#include <RooDataSet.h>
#include <RooArgSet.h>
#include <RooFormulaVar.h>
#include <RooAddPdf.h>
#include <RooPlot.h>
#include <RooFitResult.h>
#include <RooGlobalFunc.h>
#include <RooDataHist.h>
#include <RooGaussModel.h>
#include <RooTruthModel.h>
#include <RooAddModel.h>
#include <RooNumIntConfig.h>
#include <RooChi2Var.h>
#include <RooMinuit.h>
#include <RooHist.h>
#include <RooGaussian.h>
#include <RooHistPdf.h>
#include <RooProdPdf.h>

#include <EvtGenBase/EvtDalitzPlot.hh>
#include <EvtGenBase/EvtDecayMode.hh>
#include <EvtGenBase/EvtPDL.hh>

#include <CharmDalitzFit/RooTimepdf.hh>

using namespace::RooFit;

int main(){

  BaBarStyle p;
  p.SetBaBarStyle();
  gROOT->GetStyle("BABAR")->SetPalette(1);
  gROOT->GetStyle("BABAR")->SetPadTopMargin(0.04);
  gROOT->GetStyle("BABAR")->SetPadLeftMargin(0.17);
  gROOT->GetStyle("BABAR")->SetPadBottomMargin(0.19);
  gROOT->GetStyle("BABAR")->SetTitleSize(0.08,"xyz"); // set the 3 axes title size 

  Bool_t doFit = kTRUE;

  RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",0.,-2.,4.);
  RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",0.,0.5);

  RooRealVar d0P_phi("d0P_phi","d0P_phi",0.,-acos(-1.),acos(1.));
  RooRealVar d0P_theta("d0P_theta","d0P_theta",0.1,0.,acos(1.));

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  //read in the dataset
  TFile hello("DataSet_out_tmp.root");
  gROOT->cd();
  RooDataSet *data = (RooDataSet*)hello.Get("fulldata");
  RooDataSet *data_1 = (RooDataSet*)data->reduce("isWS == 0 && deltaMass > 0.1449 && deltaMass < 0.1459 && d0LifetimeErr < 0.5 && d0Lifetime < 4. && d0Lifetime > -2.");

  RooDataSet *finaldata = (RooDataSet*)data_1->reduce("d0Mass > 1.8495 && d0Mass < 1.8795");
  RooDataSet *leftdata = (RooDataSet*)data_1->reduce("d0Mass > 1.75 && d0Mass < 1.77");
  RooDataSet *rightdata = (RooDataSet*)data_1->reduce("d0Mass > 1.95 && d0Mass < 1.97");

  //here we set the weights for the dataset
  finaldata->setWeightVar(0);
  leftdata->setWeightVar(0);
  rightdata->setWeightVar(0);

  cout << "*************************************************************" << endl;
  cout << "The final data entry    " << finaldata->numEntries() << endl;
  cout << "*************************************************************" << endl;

  //Construct signal pdf
  RooRealVar tau("tau","tau",4.1097e-01,0.39,0.43);
  RooRealVar bias("bias","bias",0.0053,-1.,1.) ;
  RooRealVar scalefact1("scalefact1","scalefact1",3.2048,0.,5.);
  RooRealVar scalefact2("scalefact2","scalefact2",1.4211,0.,5.);
  RooRealVar scalefact3("scalefact3","scalefact3",9.4218e-01,0.,5.);
  RooRealVar one("one","one",1.);

  bias.setConstant(kFALSE);
  scalefact1.setConstant(kTRUE);
  scalefact2.setConstant(kTRUE);
  scalefact3.setConstant(kTRUE);
  one.setConstant(kTRUE);

  //consider the resolution or the truth model
  RooGaussModel gm1("gm1","gauss model 1",d0Lifetime,bias,d0LifetimeErr,one,scalefact1);
  RooGaussModel gm2("gm2","gauss model 2",d0Lifetime,bias,d0LifetimeErr,one,scalefact2);
  RooGaussModel gm3("gm3","gauss model 3",d0Lifetime,bias,d0LifetimeErr,one,scalefact3);
  //RooTruthModel gm("gm","truth model",d0Lifetime);

  RooRealVar N1("N1","N1",0.0038,0.,1.);
  RooRealVar N2("N2","N2",0.180,0.,1.);

  RooFormulaVar f2("f2","f2","(1-@0)*@1",RooArgList(N1,N2));
  RooFormulaVar f3("f3","f3","(1-@0)*(1-@1)",RooArgList(N1,N2));
  RooAddModel gm("gm","gm",RooArgList(gm2,gm3,gm1),RooArgList(f2,f3));

  RooTimepdf *D0pdf = new RooTimepdf("D0pdf","D0pdf",d0Lifetime,gm,tau);

  cout << "about to init" << endl;

  d0Lifetime.setRange(-2.,4.);
  d0Lifetime.setBins(70);
  d0LifetimeErr.setBins(40);

  TH2F *lefth = (TH2F*)d0Lifetime.createHistogram("lefth",d0LifetimeErr);
  leftdata->fillHistogram(lefth,RooArgList(d0Lifetime,d0LifetimeErr));
  TH2F *righth = (TH2F*)d0Lifetime.createHistogram("righth",d0LifetimeErr);
  rightdata->fillHistogram(righth,RooArgList(d0Lifetime,d0LifetimeErr));
  righth->Scale(lefth->Integral()/righth->Integral());
  lefth->Sumw2();
  righth->Sumw2();
  lefth->Add(righth);
  lefth->Sumw2();
  RooDataHist *lefthist = new RooDataHist("lefthist","lefthist",RooArgList(d0Lifetime,d0LifetimeErr),lefth);
  RooHistPdf totbkg_norm("totbkg_norm","totbkg_norm",RooArgList(d0Lifetime,d0LifetimeErr),*lefthist,4);

  TH1F *err_sig_h = (TH1F*)d0LifetimeErr.createHistogram("err_sig_h");
  finaldata->fillHistogram(err_sig_h,RooArgSet(d0LifetimeErr));
  RooDataHist terr_sig("terr_sig","terr_sig",RooArgSet(d0LifetimeErr),err_sig_h);
  RooHistPdf terr_sig_pdf("terr_sig_pdf","terr_sig_pdf",RooArgSet(d0LifetimeErr),terr_sig,3);

  RooProdPdf totsig_norm("totsig_norm","totsig_norm",RooArgSet(terr_sig_pdf),Conditional(*D0pdf,RooArgSet(d0Lifetime)));

  RooDataHist* dbtime = new RooDataHist("dbtime","dbtime",RooArgSet(d0Lifetime,d0LifetimeErr),*finaldata);

  RooRealVar Nsig("Nsig","Nsig", 653962. + 2218.);
  RooRealVar Nbkg("Nbkg","Nbkg", 2255. + 551.);

  RooAddPdf totpdf("totpdf","totpdf",RooArgList(totsig_norm,totbkg_norm),RooArgList(Nsig,Nbkg));

  if(doFit){

    Int_t phi_div = 12;
    Int_t m2_div = 3;
    Float_t dm = (dalitzSpace.qAbsMax(EvtCyclic3::AB) - dalitzSpace.qAbsMin(EvtCyclic3::AB))/phi_div;

    Float_t dphi = 2*acos(-1.)/phi_div;
    Float_t phi_min = -acos(-1.);

    TCanvas can2,can3,can4;
    can2.Divide(2,3);
    can3.Divide(3,4);
    //can4.Divide(2,5);
    
    Int_t k = 0;
    //for(Int_t k=0;k<phi_div;k++){

    //for(Int_t l=0;l<m2_div;l++){
    Int_t l = 0;

    Float_t tmp_m_min = dalitzSpace.qAbsMin(EvtCyclic3::AB) + l*dm;
    Float_t tmp_m_max = tmp_m_min + dm;
    char cutm[100];
    sprintf(cutm,"m2Kpi_d0mass > %f && m2Kpi_d0mass < %f",tmp_m_min,tmp_m_max);

    Float_t tmp_phi_min = phi_min + k*dphi;
    Float_t tmp_phi_max = tmp_phi_min + dphi;
    Float_t tmp_phi_min_Plot = tmp_phi_min*180./acos(-1.);
    Float_t tmp_phi_max_Plot = tmp_phi_max*180./acos(-1.);
	
    Int_t theta_div = 4;
    Float_t dtheta = 2.3/theta_div;
	
    char cutphi[100];
    sprintf(cutphi,"d0P_phi > %f && d0P_phi < %f",tmp_phi_min,tmp_phi_max);
    char cutphi_Plot[100];
    sprintf(cutphi_Plot,"%f < #phi < %f",tmp_phi_min_Plot,tmp_phi_max_Plot);
    //RooDataSet *tmpdata_1 = (RooDataSet*)finaldata->reduce(cutm);

    /*
      RooDataSet *tmpdata = (RooDataSet*)finaldata->reduce(cutphi);
      RooDataHist mydbtime("mydbtime","mydbtime",RooArgSet(d0Lifetime,d0LifetimeErr),*tmpdata);

      cout << "////////////////////////////////////" << endl << endl;
      cout << "Fitting slice in phi: " << tmp_phi_min_Plot << " " << tmp_phi_max_Plot << endl << endl;
      cout << "////////////////////////////////////" << endl << endl;
    */

    //for(Int_t r=0;r<theta_div;r++){
    Int_t r = 0;
    Float_t tmp_theta_min;
    if(r==0) tmp_theta_min  = 0.3;
    if(r==1) tmp_theta_min  = 0.8;
    if(r==2) tmp_theta_min  = 1.3;
    if(r==3) tmp_theta_min  = 1.8;

    Float_t tmp_theta_max;
    if(r==0) tmp_theta_max  = 0.8;
    if(r==1) tmp_theta_max  = 1.3;
    if(r==2) tmp_theta_max  = 1.8;
    if(r==3) tmp_theta_max  = 2.5;

    tau.setVal(0.4101);
    scalefact1.setVal(2.84);
    scalefact2.setVal(1.36);
    scalefact3.setVal(0.93);
    N1.setVal(0.0038);
    N2.setVal(0.18);
    bias.setVal(0.0053);

    char cuttheta[100];
    sprintf(cuttheta,"d0P_theta > %f && d0P_theta < %f",tmp_theta_min,tmp_theta_max);
    //RooDataSet *tmpdata_1 = (RooDataSet*)finaldata->reduce(cuttheta);
    //RooDataHist mydbtime("mydbtime","mydbtime",RooArgSet(d0Lifetime,d0LifetimeErr),*tmpdata_1);

    cout << "////////////////////////////////////" << endl << endl;
    cout << "Fitting slice in theta: " << tmp_theta_min << " " << tmp_theta_max << endl << endl;
    cout << "////////////////////////////////////" << endl << endl;

    /*RooFitResult *fitRes = totpdf.fitTo(*finaldata,Save(1),Minos(0));    
    fitRes->Print("v");
    RooArgSet results(fitRes->floatParsFinal());
    RooArgSet conresults(fitRes->constPars());
    results.add(conresults);
    */
    //char filename[100];
    //sprintf(filename,"phiresults/fit_res_%d",k);
    //results.writeToFile(filename);

    d0LifetimeErr.setBins(60);
    RooDataHist errdb("errdb","errdb",RooArgSet(d0LifetimeErr),*dbtime);
    
    //Make the plots
    RooPlot* tframe = d0Lifetime.frame();
    dbtime->plotOn(tframe,MarkerSize(0.1),DrawOption("z"));
    totpdf.plotOn(tframe);
    tframe->getAttLine()->SetLineStyle(1);
    tframe->SetMaximum(2*tframe->GetMaximum());

    tframe->GetXaxis()->SetTitle("t_{K^{-}#pi^{+}#pi^{0}} [ps]");
    tframe->GetYaxis()->SetTitle("Events/0.08 ps");
    Double_t chi2time = tframe->chiSquare();
    
    cout << "Chi2 for time = " << chi2time << endl;

    RooPlot* pullFramet = d0Lifetime.frame() ;
    pullFramet->addPlotable(tframe->pullHist()) ;
    pullFramet->SetMaximum(5.);
    pullFramet->SetMinimum(-5.);
    pullFramet->GetXaxis()->SetTitle("");
    pullFramet->GetYaxis()->SetTitle("#pm #sqrt{#Chi^{2}}");

    totpdf.plotOn(tframe,Components(RooArgSet(totbkg_norm)),DrawOption("F"),FillColor(14));

    TPaveText *boxt = new TPaveText(2.5,2.5,2.7,2.7,"");
    boxt->AddText("(d)");
    boxt->SetFillColor(10);

    TCanvas c1("c1","c1",300,300);
    //c1.Divide(1,2);
    c1.cd();c1.cd()->SetLogy(1);tframe->Draw();boxt->Draw("SAME");
    //c1.cd(2);c1.cd(2)->SetLogy(0);pullFramet->Draw();
    c1.SaveAs("RStimefit.eps");

    /*  
	char plotname1[100];
	sprintf(plotname1,"RStimefit_%d_1.eps",k);
	char plotname2[100];
	sprintf(plotname2,"RStimefit_%d_2.eps",k);
	char plotname3[100];
	sprintf(plotname3,"RStimefit_%d_3.eps",k);
	char plotname4[x100];
	sprintf(plotname4,"RStimefit_%d_4.eps",k);

	if(r==0) c1.SaveAs(plotname1);
	if(r==1) c1.SaveAs(plotname2);
	if(r==2) c1.SaveAs(plotname3);
	if(r==3) c1.SaveAs(plotname4);
    */
    //}
	  
    //can2.cd(r+1);can2.cd(r+1)->SetLogy(1);tframe->Draw();
    //}*/
    //can2.cd(k+1);can2.cd(k+1)->SetLogy(1);tframe->Draw();
    
    //can3.cd(k+1);can3.cd(k+1)->SetLogy(1);tframe->Draw();
    //can4.cd(k+1);can4.cd(k+1)->SetLogy(1);tframe->Draw();
    //can2.cd(2);can2.cd(2)->SetLogy(0);pullFramet->Draw();
     
    //}
    //can2.cd();can2.cd()->SetLogy(1);tframe->Draw();
    //can3.SaveAs("RStimefit2.eps"); 
    //can4.SaveAs("RStimefit3.eps"); 
	
     
  }
  return 0;
}//end of the macro

