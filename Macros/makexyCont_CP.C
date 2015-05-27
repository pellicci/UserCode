#include<TH2F.h>
#include<TFile.h>
#include<RooDataSet.h>
#include<RooArgList.h>
#include<RooRealVar.h>
#include<RooTruthModel.h>
#include<CharmDalitzFit/RooTimepdf.hh>
#include <EvtGenBase/EvtDalitzPlot.hh>
#include <EvtGenBase/EvtDecayMode.hh>
#include <EvtGenBase/EvtPDL.hh>
#include <RooRandom.h>
#include<RooHistPdf.h>
#include<RooDataHist.h>
#include <RooGlobalFunc.h>

Float_t cov_matrix[14][14];
Float_t a_std[14];
Float_t err_std[14];

int main(int argc, char* argv[])
{
  Int_t SEED = 0, isD0 = -1;
  char *filename;

  for(Int_t i=1;i<argc;i++){
    char *pchar = argv[i];
 
    switch(pchar[0]){
 
    case '-':{
 
      switch(pchar[1]){

      case 's':
        SEED = atoi(argv[i+1]);
        break;

      case 'f':
        filename = argv[i+1];
        cout << "File name used in this toy " << filename << endl;
        break;

      case 'c':
        isD0 = atoi(argv[i+1]);
	assert(isD0 == 0 || isD0 == 1);
        break;
      }
    }
    }
  }

  //set the seed and the generator used for floating parameters
  RooRandom::randomGenerator()->SetSeed(SEED);
  cout << "  Toy seed ............. " << (RooRandom::randomGenerator()->GetSeed()) << endl;

  RooRealVar c1("c1","c1",-2.,2.);
  RooRealVar c2("c2","c2",-2.,2.);
  c1.setBins(31);
  c2.setBins(31);
  RooRealVar nll("nll","nll",0.,3000.);
  RooFormulaVar deltalp("deltal","exp(-(@0-802.97))",RooArgList(nll));
  RooFormulaVar deltalm("deltal","exp(-(@0-781.446))",RooArgList(nll));

  TFile *fnll, fnll_tmp;
  if(isD0) fnll = fnll_tmp.Open("c1c2nll_plus.root");
  else fnll = fnll_tmp.Open("c1c2nll_minus.root");

  //RooDataSet *init = (RooDataSet*)fnll->Get("finit");
  RooDataSet *init;
  if(isD0) init = RooDataSet::read("data_cont_plus.dat",RooArgList(c1,c2,nll));
  else init = RooDataSet::read("data_cont_minus.dat",RooArgList(c1,c2,nll));
  if(isD0) init->addColumn(deltalp);
  else init->addColumn(deltalp);

  TH2D *h;
  if(isD0) h = new TH2D("h","h",31,-1.,0.826,31,-0.428,1.118);
  else h = new TH2D("h","h",61,-0.71,1.2,61,-2.04,2.23);

  Double_t tc1 = 0. , tc2 = 0., tdeltal = 0.;
  Long64_t nentries = init->numEntries();
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    tc1 = ((RooAbsReal*)init->get(jentry)->find("c1"))->getVal();
    tc2 = ((RooAbsReal*)init->get(jentry)->find("c2"))->getVal();
    tdeltal = ((RooAbsReal*)init->get(jentry)->find("deltal"))->getVal();
    h->Fill(tc1,tc2,tdeltal);
  }

  RooDataHist init_h("init_h","init_h",RooArgList(c1,c2),h);
  RooHistPdf cont_c1c2("cont_c1c2","cont_c1c2",RooArgSet(c1,c2),init_h,5);

  RooDataSet *c1c2_gend = cont_c1c2.generate(RooArgSet(c1,c2),RooFit::NumEvents(30000));

  RooRealVar myc1("myc1","myc1",-10.,10.);
  RooRealVar myc2("myc2","myc2",-10.,10.);
  RooRealVar myratio("myratio","myratio",0.,1.);
  RooRealVar myx("myx","myx",-1.,1.);
  RooRealVar myy("myy","myy",-1.,1.);

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  RooRealVar tau("tau","tau",0.4099);
  RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",dalitzSpace.qAbsMin(EvtCyclic3::AB)+1e-6,dalitzSpace.qAbsMax(EvtCyclic3::AB)-1e-6);
  RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",dalitzSpace.qAbsMin(EvtCyclic3::AC)+1e-6,dalitzSpace.qAbsMax(EvtCyclic3::AC)-1e-6);
  RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",-2.,4.);
  RooTruthModel gm("gm","truth model",d0Lifetime);

  Double_t NrsNws = 2760./1198329.;
  Double_t ratioerr = sqrt(pow(96.,2.) + pow(NrsNws,2.)*pow(2575.,2.))/1120821.;
  RooDataSet *parFloat = new RooDataSet("parFloat","parFloat",RooArgList(myratio,myx,myy));

  string dirname = "configmaps/effmapping_CP2/"; 
  RooTimepdf *mysigD0;

  if(isD0) mysigD0 = new RooTimepdf("mysigD0","mysigD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,myc1,myc2,1,dirname);
  else mysigD0 = new RooTimepdf("mysigD0","mysigD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,myc1,myc2,-1,dirname);

  RooListProxy *params = mysigD0->getList();

  for(Int_t j=0;j<30000;j++){
    if(fmod((Double_t)j,1000.) == 0) cout << "Performing step number " << j << endl;

    RooArgSet *myfloat = (RooArgSet*)c1c2_gend->get(j);

    myc1.setVal(((RooAbsReal*)myfloat->find("c1"))->getVal());
    myc2.setVal(((RooAbsReal*)myfloat->find("c2"))->getVal());

    Double_t myDenom = mysigD0->createIntegral(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime))->getVal();
    Double_t myNum = RooRandom::randomGenerator()->Gaus(NrsNws,ratioerr);
 
    myratio.setVal(myNum/myDenom);
    myx.setVal(myc2.getVal()*sqrt((myNum/myDenom)));
    myy.setVal(myc1.getVal()*sqrt((myNum/myDenom)));
 
    parFloat->add(RooArgSet(myratio,myx,myy));
  }
 
  TString floatname(filename);
  floatname.Append(".root");
 
  TFile f1(floatname,"RECREATE");
  f1.cd();
  parFloat->tree().Write();
  f1.Close();

  return 0;
}
