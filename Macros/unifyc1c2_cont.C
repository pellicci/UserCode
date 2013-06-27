#include<RooRealVar.h>
#include<RooDataSet.h>
#include<TTree.h>
#include<TH2D.h>
#include<TFile.h>

int main(int argc, char* argv[])
{

  Double_t sigmax2 = 0.0036469;
  Double_t sigmay2 = 0.003645524;
  char *filename;
  Double_t rho = -0.0021/sqrt(sigmax2*sigmay2);

  for(Int_t i=1;i<argc;i++){
    char *pchar = argv[i];
 
    switch(pchar[0]){
 
    case '-':{
 
      switch(pchar[1]){

      case 'x':
        sigmax2 = pow(atof(argv[i+1])*0.0908079,2.);
        cout << "Element sigma_11 is " << sigmax2 << endl;
        break;

      case 'y':
        sigmay2 = pow(atof(argv[i+1])*0.091869,2.);
        cout << "Element sigma_22 is " << sigmay2 << endl;
        break;

      case 'r':
        rho = atof(argv[i+1]);
        cout << "Element sigma_12 is " << rho << endl;
        break;

      case 'f':
        filename = argv[i+1];
        cout << "File name used for this smearing is " << filename << endl;
        break;
      }
    }
    }
  }

  //const Double_t rho = sigmaxy2/sqrt(sigmax2*sigmay2);

  RooRealVar c1("c1","c1",-1.1,1.1);
  RooRealVar c2("c2","c2",-1.1,1.1);
  RooRealVar nll("nll","nll",0.,3000.);
  RooRealVar deltal("deltal","deltal",-100,100);

  RooDataSet *init = RooDataSet::read("data_cont.dat",RooArgList(c1,c2,nll));
  RooDataSet *finit = new RooDataSet("finit","finit",RooArgSet(c1,c2,deltal));

  //TH2D *h = new TH2D("h","h",31,-0.29,1.09,31,-0.638,0.725);
  TH2D *h = new TH2D("h","h",31,-0.638,0.725,31,-0.29,1.09);

  TTree *fChain = (TTree*)&(init->tree());
  Double_t myc1 = 0. , myc2 = 0., mynll = 0., mydeltal = 0.;
  fChain->SetBranchAddress("c1",&myc1);
  fChain->SetBranchAddress("c2",&myc2);
  fChain->SetBranchAddress("nll",&mynll);

  Long64_t nbytes = 0, nb = 0;
  Long64_t nentries = fChain->GetEntriesFast();
  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    nb = fChain->GetEntry(jentry);   nbytes += nb;
    mydeltal = exp(-(mynll-1591.4));

    h->Fill(myc1,myc2,mydeltal);
  }

  //TH2D *hsyst = new TH2D("hsyst","hsyst",31,-0.29,1.09,31,-0.638,0.725);
  TH2D *hsyst = new TH2D("hsyst","hsyst",31,-0.638,0.725,31,-0.29,1.09);

  Double_t THElike = 0.;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    nb = fChain->GetEntry(jentry);
    Double_t tmpc1 = myc1;
    Double_t tmpc2 = myc2;
    Double_t tmpdelta = exp(-(mynll-1591.4));
    Double_t newlike = 0.;

    for (Long64_t kentry=0; kentry<nentries;kentry++) {
      fChain->GetEntry(kentry);
      Double_t myexp = exp(-(pow(myc1-tmpc1,2.)/sigmax2 + pow(myc2-tmpc2,2.)/sigmay2 - 2*rho*(myc1-tmpc1)*(myc2-tmpc2)/sqrt(sigmax2*sigmay2)));
      newlike += exp(-(mynll-1591.4))*myexp;
    }
    if(tmpdelta==1.) THElike = newlike;
  }
  Double_t deltamin = -2*(-log(THElike)); 

  cout << "New likelihood for minimum " << deltamin << endl;

  for (Long64_t jentry=0; jentry<nentries;jentry++){

    if(jentry<nentries) fChain->GetEntry(jentry);   nbytes += nb;

    Double_t tmpc1 = myc1;
    Double_t tmpc2 = myc2;
    Double_t newlike = 0.;

    for (Long64_t kentry=0; kentry<=nentries;kentry++) {
      if(kentry<nentries) fChain->GetEntry(kentry);

      Double_t myexp = exp(-(pow(myc1-tmpc1,2.)/sigmax2 + pow(myc2-tmpc2,2.)/sigmay2 - 2*rho*(myc1-tmpc1)*(myc2-tmpc2)/sqrt(sigmax2*sigmay2)));
      newlike += exp(-(mynll-1591.4))*myexp;
    }

    if(tmpc1 == 0 && tmpc2 == 0){
      Double_t deltanomix = -2*(-log(newlike)); 
      cout << "delta likelihood for no mixing" << deltanomix << endl;
    }

    hsyst->Fill(tmpc1,tmpc2,newlike);
    c1.setVal(tmpc1);
    c2.setVal(tmpc2);
    deltal.setVal(newlike);
    finit->add(RooArgSet(c1,c2,deltal));
  }

  h->Scale(1/h->Integral());
  hsyst->Scale(1/hsyst->Integral());

  TString floatname(filename);
  floatname.Append(".root");

  TFile f(floatname,"RECREATE");
  f.cd();
  finit->Write();
  fChain->Write();
  f.mkdir("dir");
  f.cd("dir");
  h->Write();
  hsyst->Write();
  f.Close();

  return 0;
}
