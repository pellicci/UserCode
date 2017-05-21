#include <iostream>

#include <BaBarStyle.h>

#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TProfile2D.h>
#include <TPaveText.h>

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
#include <RooHistPdf.h>

#include <EvtGenBase/EvtDalitzPlot.hh>
#include <EvtGenBase/EvtDecayMode.hh>
#include <EvtGenBase/EvtPDL.hh>

#include <CharmDalitzFit/RooKpipi0pdf.hh>

using namespace::RooFit;

int main(){

  BaBarStyle p;
  p.SetBaBarStyle();
  //gROOT->SetStyle("Plain");

  Bool_t doNorm = kTRUE;
  Bool_t doComparison = kFALSE;
  Bool_t doFract = kFALSE;
  Bool_t doFit = kFALSE;
  Bool_t doPlots = kFALSE;

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
  RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
  RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",1.,dalitzSpace.qAbsMin(EvtCyclic3::BC),dalitzSpace.qAbsMax(EvtCyclic3::BC));
  RooCategory D0flav("D0flav","D0flav");
  D0flav.defineType("D0",-1);
  D0flav.defineType("antiD0",1);

  //this is just to plot the m23 pdf
  Float_t total = pow(dalitzSpace.bigM(),2) + pow(dalitzSpace.mA(),2) + pow(dalitzSpace.mB(),2) + pow(dalitzSpace.mC(),2);
  RooRealVar totalm("totalm","totalm",total);
  RooFormulaVar mass13a("mass13a","@0-@1-@2",RooArgSet(totalm,m2Kpi_d0mass,m2pipi0_d0mass));

  cout << "read the dataset" << endl;

  TFile hello("DataSet_out_tmp.root");
  gROOT->cd();
  RooDataSet *data = (RooDataSet*)hello.Get("fulldata");
  RooDataSet *data_1 = (RooDataSet*)data->reduce("D0flav ==  1 && isWS == 0 && d0LifetimeErr < 0.5 && d0Lifetime > -2. && d0Lifetime < 4.");
  RooDataSet *finaldata = (RooDataSet*)data_1->reduce("deltaMass > 0.1449 && deltaMass < 0.1459 && d0Mass > 1.8495 && d0Mass < 1.8795");
  RooDataSet *leftdata = (RooDataSet*)(RooDataSet*)data_1->reduce("d0Mass > 1.74 && d0Mass < 1.79");
  RooDataSet *rightdata = (RooDataSet*)data_1->reduce("d0Mass > 1.94 && d0Mass < 1.99");

  //here we set the weights for the dataset
  finaldata->setWeightVar(0);
  leftdata->setWeightVar(0);
  rightdata->setWeightVar(0);

  //if you want to have a little dataset to test, uncomment next line and rename finaldata above
  //RooDataSet *finaldata = finaldata_1->reduce(EventRange(1,1000));
  cout << "*************************************************************" << endl;
  cout << "The final data entry    " << finaldata->numEntries() << endl;
  cout << "*************************************************************" << endl;

  //Construct signal pdf
  string dirname = "configmaps/effmapping_RS_CP/";

  RooKpipi0pdf *D0pdf = new RooKpipi0pdf("D0pdf","D0pdf",m2Kpi_d0mass,m2Kpi0_d0mass,&dalitzSpace,dirname,1);
  RooKpipi0pdf *D0pdf23 = new RooKpipi0pdf("D0pdf23","D0pdf23",m2Kpi_d0mass,mass13a,&dalitzSpace,dirname,1);

  if(doNorm) D0pdf->getManager()->calNorm();

  //When we plot the 1D projection, need to calculate the 1D integral
  //set the precision here
  //cout << "config integrator " << endl;
  RooNumIntConfig *cfg = RooAbsReal::defaultIntegratorConfig();
  cfg->setEpsAbs(1E-3);
  cfg->setEpsRel(1E-3);
  cfg->method1D().setLabel("RooSegmentedIntegrator1D");
  //cfg.getConfigSection("RooSegmentedIntegrator1D").setRealValue("numSeg",3);
  //cfg->method1D()->Print("v");
  D0pdf->setIntegratorConfig(*cfg);
  D0pdf23->setIntegratorConfig(*cfg);

  cout << "about to init" << endl;

  m2Kpi_d0mass.setBins(150);
  m2Kpi0_d0mass.setBins(150);
  m2pipi0_d0mass.setBins(150);

  //background description
  //RooBkg combdalitz("combdalitz","combdalitz",m2Kpi_d0mass,m2Kpi0_d0mass,&dalitzSpace);
  //RooBkg combdalitz23("combdalitz23","combdalitz23",m2Kpi_d0mass,mass13a,&dalitzSpace);

  RooRealVar Nsig("Nsig","Nsig", 653962. + 2218.);
  RooRealVar Nbkg("Nbkg","Nbkg", 2255. + 551.);

  RooDataHist* dbdalitz = new RooDataHist("dbdalitz","dbdalitz",RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),*finaldata);
  RooDataHist* dbdalitz23 = new RooDataHist("dbdalitz23","dbdalitz23",RooArgSet(m2Kpi_d0mass,m2pipi0_d0mass),*finaldata);

  ////////////////////////////////////////
  //background parametrization using sidebands histograms
  ////////////////////////////////////////
  TH2F *lefth = m2Kpi_d0mass.createHistogram("lefth",m2Kpi0_d0mass);
  leftdata->fillHistogram(lefth,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));
  TH2F *righth = m2Kpi_d0mass.createHistogram("righth",m2Kpi0_d0mass);
  rightdata->fillHistogram(righth,RooArgList(m2Kpi_d0mass,m2Kpi0_d0mass));

  TH2F *lefth23 = m2Kpi_d0mass.createHistogram("lefth23",m2pipi0_d0mass);
  leftdata->fillHistogram(lefth23,RooArgList(m2Kpi_d0mass,m2pipi0_d0mass));
  TH2F *righth23 = m2Kpi_d0mass.createHistogram("righth23",m2pipi0_d0mass);
  rightdata->fillHistogram(righth23,RooArgList(m2Kpi_d0mass,m2pipi0_d0mass));

  righth->Scale(lefth->Integral()/righth->Integral());
  lefth->Sumw2();
  righth->Sumw2();
  righth23->Scale(lefth23->Integral()/righth23->Integral());
  lefth23->Sumw2();
  righth23->Sumw2();

  RooDataHist *lefthist = new RooDataHist("lefthist","lefthist",RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),lefth);
  RooDataHist *righthist = new RooDataHist("righthist","righthist",RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),righth);
  RooDataHist *lefthist23 = new RooDataHist("lefthist23","lefthist23",RooArgSet(m2Kpi_d0mass,m2pipi0_d0mass),lefth23);
  RooDataHist *righthist23 = new RooDataHist("righthist23","righthist23",RooArgSet(m2Kpi_d0mass,m2pipi0_d0mass),righth23);

  RooHistPdf leftpdf("leftpdf","leftpdf",RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),*lefthist,4);
  RooHistPdf rightpdf("rightpdf","rightpdf",RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass),*righthist,4);
  RooHistPdf leftpdf23("leftpdf23","leftpdf23",RooArgSet(m2Kpi_d0mass,m2pipi0_d0mass),*lefthist23,4);
  RooHistPdf rightpdf23("rightpdf23","rightpdf23",RooArgSet(m2Kpi_d0mass,m2pipi0_d0mass),*righthist23,4);

  RooRealVar fcomb("fcomb","fcomb",0.738);
  RooAddPdf combdalitz("combdalitz","combdalitz",RooArgList(leftpdf,rightpdf),RooArgList(fcomb));
  RooAddPdf combdalitz23("combdalitz23","combdalitz23",RooArgList(leftpdf23,rightpdf23),RooArgList(fcomb));
  ///////////////////////////////////////

  RooAddPdf totpdf("totpdf","totpdf",RooArgList(*D0pdf,combdalitz),RooArgList(Nsig,Nbkg));
  RooAddPdf totpdf23("totpdf23","totpdf23",RooArgList(*D0pdf23,combdalitz23),RooArgList(Nsig,Nbkg));

  if(doFit){
    // Start Minuit session on Chi2
    RooChi2Var chi2("chi2","chi2",totpdf,*dbdalitz);
    RooMinuit m2(chi2);
    m2.migrad();
    m2.hesse();
    RooFitResult* fitRes = m2.save();
    fitRes->Print("v");
    RooArgSet results(fitRes->floatParsFinal());
    RooArgSet conresults(fitRes->constPars());
    results.add(conresults);
    results.writeToFile("fit_isobar_RS.txt");

    //save the stupid result
    TFile f("fit_RSDalitz_result.root","RECREATE");
    fitRes->Write();
    f.Close();
  }

  if(doFract) {

    cout << "Calculating fit fractions" << endl;
    TFile f("fit_RSDalitz_result.root");
    RooFitResult* fitRes = (RooFitResult*)f.Get("chi2");

    //now calculate the fit fractions
    const Int_t nRes = D0pdf->getManager()->getnRes();

    //recalculate the normalization if necessary
    D0pdf->getManager()->calNorm();

    EvtComplex normarray[nRes][nRes];

    const Int_t myRes = 12;
    TH1F fitty[myRes];

    //read the integral value from the cache file.
    //In this way we don't need to compute the normalization everytime during MIGRAD
    char int_name[50];
    D0pdf->getManager()->getFileName(int_name);

    ifstream f1;
    f1.open(int_name);
    if (!f1){
      cout << "Error opening file " << endl;
      assert(0);
    }
  
    Double_t re=0.,im=0.;
    //Read in the cache file and store back to array
    for(Int_t j=0;j<nRes;j++) {
      char thname[100];
      sprintf(thname,"thname_%d",j);
      if(j < myRes) fitty[j] = TH1F(thname,thname,30,0.,1.);
      for(Int_t k=0;k<nRes;k++){
	f1 >> re >> im;       
	normarray[j][k] = EvtComplex(re,im);
      }
    }   

    EvtComplex mynorm[myRes][myRes];
    Int_t m = 0, l = 0;
    for(Int_t i=0;i<myRes;i++){
      for(Int_t j=0;j<myRes;j++){
	if(i==0) l = 7;
	else if(i==1) l = 6;
	else if(i==2) l = 11;
	else if(i==3) l = 4;
	else if(i==4) l = 5;
	else if(i==5) l = 3;
	else if(i==6) l = 9;
	else if(i==7) l = 10;
	else if(i==8) l = 12;
	else if(i==9) l = 8;
	else if(i==10) l = 2;
	else if(i==11) l = 0;

	if(j==0) m = 7;
	else if(j==1) m = 6;
	else if(j==2) m = 11;
	else if(j==3) m = 4;
	else if(j==4) m = 5;
	else if(j==5) m = 3;
	else if(j==6) m = 9;
	else if(j==7) m = 10;
	else if(j==8) m = 12;
	else if(j==9) m = 8;
	else if(j==10) m = 2;
	else if(j==11) m = 0;

	mynorm[i][j] = normarray[l][m];
      }
    }

    //do 100 experiments and extract parameters using covariance matrix
    for(Int_t l=0;l<300;l++){
      RooArgList listpar = fitRes->randomizePars();
      if(l==0) listpar.Print();

      Double_t mynormD0 = 0.;
      EvtComplex coeff_i(0.,0.), coeff_j(0.,0.);
      for(Int_t i=0;i<2*myRes;i++){
	for(Int_t j=0;j<2*myRes;j++){
	  if(i==(2*myRes - 2)) coeff_i = EvtComplex(1.,0.);
	  else coeff_i = EvtComplex(((RooAbsReal*)listpar.at(i))->getVal()*cos(((RooAbsReal*)listpar.at(i+1))->getVal()),
				    ((RooAbsReal*)listpar.at(i))->getVal()*sin(((RooAbsReal*)listpar.at(i+1))->getVal()));

	  if(j==(2*myRes - 2)) coeff_j = EvtComplex(1.,0.);
	  else coeff_j = EvtComplex(((RooAbsReal*)listpar.at(j))->getVal()*cos(((RooAbsReal*)listpar.at(j+1))->getVal()),
				    ((RooAbsReal*)listpar.at(j))->getVal()*sin(((RooAbsReal*)listpar.at(j+1))->getVal()));

	  mynormD0 += real(coeff_i*conj(coeff_j)*(mynorm[i/2][j/2]));
	  j++;
	}
	i++;
      }

      //now calculate the fit fractions
      for(Int_t i=0;i<2*myRes;i++){
	Double_t fitfrac = 0.;
	if(i==(2*myRes - 2)) fitfrac = abs(mynorm[i/2][i/2])/mynormD0;
	else fitfrac = abs2( ((RooAbsReal*)listpar.at(i))->getVal())*abs(mynorm[i/2][i/2])/mynormD0;
	fitty[i/2].Fill(fitfrac);
	i++;
      }
    }// nexperiments

    Double_t tot_frac = 0.;
    for(Int_t i=0;i<myRes;i++){
      tot_frac += fitty[i].GetMean();
      cout << "Resonance " << i << ": fit fraction = " << fitty[i].GetMean() << " +/- " << fitty[i].GetRMS() << endl;
    }

    cout << "Total fit fraction = " << tot_frac << endl;
    cout << "///////////////////////////" << endl;
  }

  if(doPlots){
    //Make the plots
    // REMEBER: if you want roofit to consider the reweighted errors, you must put DataError(RooAbsData::SumW2))
    //******************************************************
    RooPlot* xframe = m2Kpi_d0mass.frame();
    dbdalitz->plotOn(xframe,MarkerSize(0.1),DrawOption("z"));
    totpdf.plotOn(xframe);
    xframe->getAttLine()->SetLineWidth(1);
    xframe->getAttLine()->SetLineStyle(1);
    xframe->SetTitle("");
    xframe->GetXaxis()->SetTitle("s_{12} [GeV^{2}/c^{4}]");
    xframe->GetYaxis()->SetTitle("Events/4 MeV^{2}/c^{4}");
    Double_t chi2Kpi = xframe->chiSquare();

    RooPlot* yframe = m2Kpi0_d0mass.frame();
    dbdalitz->plotOn(yframe,MarkerSize(0.1),DrawOption("z"));
    totpdf.plotOn(yframe);
    yframe->getAttLine()->SetLineWidth(1);
    yframe->getAttLine()->SetLineStyle(1);
    yframe->SetTitle("");
    yframe->GetXaxis()->SetTitle("s_{13} [GeV^{2}/c^{4}]");
    yframe->GetYaxis()->SetTitle("Events/5 MeV^{2}/c^{4}");
    Double_t chi2Kpi0 = yframe->chiSquare();
    /*
    RooPlot* zframe = m2pipi0_d0mass.frame(0.,2.3);
    dbdalitz23->plotOn(zframe,MarkerSize(0.1),DrawOption("z"));
    totpdf23.plotOn(zframe);
    zframe->getAttLine()->SetLineWidth(1);
    zframe->getAttLine()->SetLineStyle(1);
    zframe->SetTitle("");
    zframe->GetXaxis()->SetTitle("m^{2}_{#pi^{+}#pi^{0}}");
    Double_t chi2pipi0 = zframe->chiSquare();

    cout << "Chi2 for Kpi = " << chi2Kpi << endl;
    cout << "Chi2 for Kpi0 = " << chi2Kpi0 << endl;
    cout << "Chi2 for pipi0 = " << chi2pipi0 << endl;

    RooPlot* pullFramem12 = m2Kpi_d0mass.frame() ;
    pullFramem12->SetTitle("");
    pullFramem12->GetXaxis()->SetTitle("");
    pullFramem12->addPlotable(xframe->pullHist()) ;
    pullFramem12->SetMaximum(5.);
    pullFramem12->SetMinimum(-5.);

    RooPlot* pullFramem13 = m2Kpi0_d0mass.frame() ;
    pullFramem13->SetTitle("");
    pullFramem13->GetXaxis()->SetTitle("");
    pullFramem13->addPlotable(yframe->pullHist()) ;
    pullFramem13->SetMaximum(5.);
    pullFramem13->SetMinimum(-5.);

    RooPlot* pullFramem23 = m2pipi0_d0mass.frame() ;
    pullFramem23->SetTitle("");        
    pullFramem23->GetXaxis()->SetTitle("");
    pullFramem23->addPlotable(zframe->pullHist()) ;
    pullFramem23->SetMaximum(5.);
    pullFramem23->SetMinimum(-5.);

    TCanvas *c2 = new TCanvas("c2","residuals",1200,200);
    c2->Divide(3,1);
    c2->cd(1);pullFramem12->Draw();
    c2->cd(2);pullFramem13->Draw();
    c2->cd(3);pullFramem23->Draw();
    c2->SaveAs("RSresiduals.eps");
    */
    totpdf.plotOn(xframe,Project(m2Kpi0_d0mass),Components(RooArgSet(combdalitz)),DrawOption("F"),FillColor(kRed));
    totpdf.plotOn(yframe,Project(m2Kpi_d0mass),Components(RooArgSet(combdalitz)),DrawOption("F"),FillColor(kRed));
    //totpdf23.plotOn(zframe,Project(m2Kpi_d0mass),Components(RooArgSet(combdalitz23)),DrawOption("F"),FillColor(kRed));

    TPaveText *box_m12 = new TPaveText(2.5,2.5,2.7,2.7,"");
    box_m12->AddText("(b)");
    box_m12->SetFillColor(10);

    TPaveText *box_m13 = new TPaveText(2.5,2.5,2.7,2.7,"");
    box_m13->AddText("(c)");
    box_m13->SetFillColor(10);

    TCanvas c1("c1","c1",600,600);
    c1.cd();
    xframe->Draw();box_m12->Draw("SAME");
    c1.SaveAs("RSfit_m2Kpi.eps");

    TCanvas c2("c2","c2",600,600);
    c2.cd();
    yframe->Draw();box_m13->Draw("SAME");
    c2.SaveAs("RSfit_m2Kpi0.eps");
    /*
    TCanvas *c1 = new TCanvas("c1","allevents",1200,400);
    c1->Divide(3,1);
    c1->cd(1);xframe->Draw();
    //p.SetBaBarLabel(-1,-1,-1,"preliminary");
    c1->cd(2);yframe->Draw();
    //p.SetBaBarLabel(-1,-1,-1,"preliminary");
    c1->cd(3);zframe->Draw();
    //p.SetBaBarLabel(-1,-1,-1,"preliminary");
    c1->SaveAs("RSsigfit.eps");
    */
  }

  if(doComparison){
    RooDataSet *littledata = (RooDataSet*)finaldata->reduce(EventRange(1,70000));
    RooArgSet VarList1(m2Kpi_d0mass,m2Kpi0_d0mass);
    Int_t num_entries = littledata->numEntries();
    RooDataSet* genpdf = D0pdf->generate(VarList1,num_entries);

    Int_t nbinx = 20;
    Int_t nbiny = 20;
    m2Kpi_d0mass.setBins(nbinx);
    m2Kpi0_d0mass.setBins(nbiny);

    TH2F* pdfhist = new TH2F("pdfhist","pdfhist",nbinx,0.39,3.,nbiny,0.39,3.);
    TH2F* datahist = new TH2F("datahist","datahist",nbinx,0.39,3.,nbiny,0.39,3.);
    pdfhist = genpdf->createHistogram(m2Kpi_d0mass,m2Kpi0_d0mass);
    datahist = finaldata->createHistogram(m2Kpi_d0mass,m2Kpi0_d0mass);
    pdfhist->GetXaxis()->SetTitle("m_{K#pi}^{2}");
    pdfhist->GetYaxis()->SetTitle("m_{K#pi^{0}}^{2}");

    pdfhist->Scale(datahist->Integral()/pdfhist->Integral());

    pdfhist->Add(datahist,-1.);

    TCanvas c2;
    c2.cd();pdfhist->Draw("LEGO2Z");
    c2.SaveAs("RSsigdiff.eps");

    TFile ftmp("prova.root","RECREATE");
    ftmp.cd();pdfhist->Write();
    ftmp.Close();

  }

  return 0;
}//end of the macro
