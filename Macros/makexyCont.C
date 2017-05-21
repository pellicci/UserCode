#include<TH2F.h>
#include<RooFitResult.h>
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
#include<TMatrix.h>
#include<TVector.h>
#include<TIterator.h>
#include<RooHistPdf.h>
#include<RooDataHist.h>
#include <RooGlobalFunc.h>

Float_t cov_matrix[14][14];
Float_t a_std[14];
Float_t err_std[14];
TFile f_std("syst_root/fit_WS_std.root");
//TFile f_std("prova_theRes.root");
//TFile f_std("myprova_theRes.root");
//TFile f_std("toynomix_theRes.root");
RooArgList *_randomPars(0);
TMatrix *_Lt(0);

void getStdfit()
{
  gROOT->cd();
  RooFitResult *theRes = (RooFitResult*)f_std.Get("nll");

  RooArgList final_std_list = theRes->floatParsFinal();

  a_std[0] = ((RooAbsReal*)final_std_list.find("Kst2z1430_amp"))->getVal();
  a_std[1] = ((RooAbsReal*)final_std_list.find("Kst2z1430_phase"))->getVal();
  a_std[2] = ((RooAbsReal*)final_std_list.find("Kstm1430_amp"))->getVal();
  a_std[3] = ((RooAbsReal*)final_std_list.find("Kstm1430_phase"))->getVal();
  a_std[4] = ((RooAbsReal*)final_std_list.find("Kstminus_amp"))->getVal();
  a_std[5] = ((RooAbsReal*)final_std_list.find("Kstminus_phase"))->getVal();
  a_std[6] = ((RooAbsReal*)final_std_list.find("Kstz1430_amp"))->getVal();
  a_std[7] = ((RooAbsReal*)final_std_list.find("Kstz1430_phase"))->getVal();
  a_std[8] = ((RooAbsReal*)final_std_list.find("Kstzero_amp"))->getVal();
  a_std[9] = ((RooAbsReal*)final_std_list.find("Kstzero_phase"))->getVal();
  a_std[10] = ((RooAbsReal*)final_std_list.find("Rho1700_amp"))->getVal();
  a_std[11] = ((RooAbsReal*)final_std_list.find("Rho1700_phase"))->getVal();
  a_std[12] = ((RooAbsReal*)final_std_list.find("c1"))->getVal();
  a_std[13] = ((RooAbsReal*)final_std_list.find("c2"))->getVal();

  err_std[0] = ((RooRealVar*)final_std_list.find("Kst2z1430_amp"))->getError();
  err_std[1] = ((RooRealVar*)final_std_list.find("Kst2z1430_phase"))->getError();
  err_std[2] = ((RooRealVar*)final_std_list.find("Kstm1430_amp"))->getError();
  err_std[3] = ((RooRealVar*)final_std_list.find("Kstm1430_phase"))->getError();
  err_std[4] = ((RooRealVar*)final_std_list.find("Kstminus_amp"))->getError();
  err_std[5] = ((RooRealVar*)final_std_list.find("Kstminus_phase"))->getError();
  err_std[6] = ((RooRealVar*)final_std_list.find("Kstz1430_amp"))->getError();
  err_std[7] = ((RooRealVar*)final_std_list.find("Kstz1430_phase"))->getError();
  err_std[8] = ((RooRealVar*)final_std_list.find("Kstzero_amp"))->getError();
  err_std[9] = ((RooRealVar*)final_std_list.find("Kstzero_phase"))->getError();
  err_std[10] = ((RooRealVar*)final_std_list.find("Rho1700_amp"))->getError();
  err_std[11] = ((RooRealVar*)final_std_list.find("Rho1700_phase"))->getError();
  err_std[12] = ((RooRealVar*)final_std_list.find("c1"))->getError();
  err_std[13] = ((RooRealVar*)final_std_list.find("c2"))->getError();
}

void getCov(Bool_t isSyst){

  if(isSyst){
    char name[50];
    sprintf(name,"covmatrix.dat");

    ifstream f;
    f.open(name);
    if (!f){
      cout << "Error opening file " << endl;
      assert(0);
    }

    Float_t a = 0.;
    //Read in the cache file and store back to array
    for(Int_t j=0;j<14;j++) {
      for(Int_t k=0;k<14;k++){
	f >> a;       
	cov_matrix[j][k] = a;
      }
    }
  }
  else{
    RooFitResult *theRes = (RooFitResult*)f_std.Get("nll");
  RooArgList final_std_list = theRes->floatParsFinal();
    for(Int_t j=0;j<14;j++) {
      for(Int_t k=0;k<14;k++){
	cov_matrix[j][k] = theRes->correlation( *((RooAbsReal*)final_std_list.at(j)) , *((RooAbsReal*)final_std_list.at(k)) )*err_std[j]*err_std[k];
      }
    }
  }
  return;
}

RooArgList genpar(RooFitResult* theRes)
{
  Int_t nPar = 14;

  if(0 == _randomPars) { // first-time initialization

    _randomPars = (RooArgList*)(theRes->floatParsFinal().snapshot());
    RooArgList final_std_list = theRes->floatParsFinal();

    // calculate the elements of the upper-triangular matrix L that gives Lt*L = C
    // where Lt is the transpose of L (the "square-root method")
    TMatrix L(nPar,nPar);
    for(Int_t iPar= 0; iPar < nPar; iPar++) {
      // calculate the diagonal term first
      L(iPar,iPar)= cov_matrix[iPar][iPar];
      for(Int_t k= 0; k < iPar; k++) {
	Double_t tmp= L(k,iPar);
	L(iPar,iPar)-= tmp*tmp;
      }
      L(iPar,iPar)= sqrt(L(iPar,iPar));
      // then the off-diagonal terms
      for(Int_t jPar= iPar+1; jPar < nPar; jPar++) {
	L(iPar,jPar)= cov_matrix[iPar][jPar];
	for(Int_t k= 0; k < iPar; k++) {
	  L(iPar,jPar)-= L(k,iPar)*L(k,jPar);
	}
	L(iPar,jPar)/= L(iPar,iPar);
      }
    }
    // remember Lt
    _Lt= new TMatrix(TMatrix::kTransposed,L);
  }
  else {
    // reset to the final fit values
    *_randomPars= theRes->floatParsFinal();
  }

  // create a vector of unit Gaussian variables
  TVector g(nPar);
  for(Int_t k= 0; k < nPar; k++) g(k)= RooRandom::gaussian();
  // multiply this vector by Lt to introduce the appropriate correlations
  g*= (*_Lt);
  // add the mean value offsets and store the results
  TIterator *iter= _randomPars->createIterator();
  RooRealVar *par(0);
  Int_t index(0);
  while((0 != (par= (RooRealVar*)iter->Next()))) {
    par->setVal(par->getVal() + g(index++));
  }
  delete iter;

  return *_randomPars;
}

int main(int argc, char* argv[])
{
  Int_t SEED = 0;
  char *filename;
  char *infilename;

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

      case 'i':
        infilename = argv[i+1];
        cout << "File name used as input in this toy " << infilename << endl;
        break;

      }
    }
    }
  }

  getStdfit();
  getCov(kFALSE);

  //set the seed and the generator used for floating parameters
  RooRandom::randomGenerator()->SetSeed(SEED);
  cout << "  Toy seed ............. " << (RooRandom::randomGenerator()->GetSeed()) << endl;

  gROOT->cd();
  RooFitResult *theRes = (RooFitResult*)f_std.Get("nll");

  RooRealVar c1("c1","c1",-2.,2.);
  RooRealVar c2("c2","c2",-2.,2.);
  c1.setBins(31);
  c2.setBins(31);
  RooRealVar nll("nll","nll",0.,3000.);
  RooFormulaVar deltal("deltal","exp(-(@0-1591.4))",RooArgList(nll));

  TString floatname1(infilename);
  floatname1.Append(".root");

  TFile fnll(floatname1);
  RooDataSet *init = (RooDataSet*)fnll.Get("finit");
  //RooDataSet *init = RooDataSet::read("data_cont.dat",RooArgList(c1,c2,nll));
  //init->addColumn(deltal);
  TH2D *h = new TH2D("h","h",31,-0.638,0.725,31,-0.29,1.09);

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

  string dirname = "configmaps/effmapping_std/"; 
  RooTimepdf mysigD0("mysigD0","mysigD0",d0Lifetime,m2Kpi_d0mass,m2Kpi0_d0mass,gm,&dalitzSpace,tau,myc1,myc2,-1,dirname);
  RooListProxy *params = mysigD0.getList();

  for(Int_t j=0;j<30000;j++){
    if(fmod((Double_t)j,1000.) == 0) cout << "Performing step number " << j << endl;

    RooArgList floated = genpar(theRes);
    RooArgSet *myfloat = (RooArgSet*)c1c2_gend->get(j);
    myc1.setVal(((RooAbsReal*)myfloat->find("c1"))->getVal());
    myc2.setVal(((RooAbsReal*)myfloat->find("c2"))->getVal());

    Double_t myDenom = mysigD0.createIntegral(RooArgSet(m2Kpi_d0mass,m2Kpi0_d0mass,d0Lifetime))->getVal();
    Double_t myNum = RooRandom::randomGenerator()->Gaus(NrsNws,ratioerr);
 
    myratio.setVal(myNum/myDenom);
    myx.setVal(myc2.getVal()*sqrt((myNum/myDenom)));
    myy.setVal(myc1.getVal()*sqrt((myNum/myDenom)));
 
    parFloat->add(RooArgSet(myratio,myx,myy));
  }
 
  TString floatname2(filename);
  floatname2.Append(".root");
 
  TFile f1(floatname2,"RECREATE");
  f1.cd();
  parFloat->tree().Write();
  //init->Write();
  f1.Close();

  return 0;
}
