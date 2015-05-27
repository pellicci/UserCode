{

RooRealVar c1("c1","c1",-3.,3.);
RooRealVar c2("c2","c2",-3.,3.);
RooRealVar nll("nll","nll",0.,3000.);
RooRealVar deltal("deltal","deltal",-100,100);

//for the minus case
const Double_t like_centr = 781.446;
const Double_t sigmax2 = 0.00398253;
const Double_t sigmay2 = 0.014802876;
//for the plus case
//const Double_t like_centr = 802.97;
//const Double_t sigmax2 = 0.003630613;
//const Double_t sigmay2 = 0.001937536;

const Double_t rho = -0.0021/sqrt(sigmax2*sigmay2);

RooDataSet *init = RooDataSet::read("data_cont_minus.dat",RooArgList(c1,c2,nll));
RooDataSet *finit = new RooDataSet("finit","finit",RooArgSet(c1,c2,deltal));

//this is for the minus case
TH2D *h = new TH2D("h","h",61,-0.71,1.2,61,-2.04,2.23);
//this is for the plus case
//TH2D *h = new TH2D("h","h",31,-1.,0.826,31,-0.428,1.118);

TTree *fChain = (TTree*)init->tree();
Double_t myc1 = 0. , myc2 = 0., mynll = 0., mydeltal = 0.;
fChain->SetBranchAddress("c1",&myc1);
fChain->SetBranchAddress("c2",&myc2);
fChain->SetBranchAddress("nll",&mynll);

Long64_t nbytes = 0, nb = 0;
Long64_t nentries = fChain->GetEntriesFast();
for (Long64_t jentry=0; jentry<nentries;jentry++) {

  nb = fChain->GetEntry(jentry);   nbytes += nb;
  mydeltal = exp(-(mynll-like_centr));

  h->Fill(myc1,myc2,mydeltal);
}

//this is for the minus case
TH2D *hsyst = new TH2D("hsyst","hsyst",61,-0.706,1.191,61,-2.033,2.223);
//this is for the plus case
//TH2D *hsyst = new TH2D("hsyst","hsyst",31,-1.,0.826,31,-0.428,1.118);

Double_t THElike = 0.;

for (Long64_t jentry=0; jentry<nentries;jentry++) {
  nb = fChain->GetEntry(jentry);
  Double_t tmpc1 = myc1;
  Double_t tmpc2 = myc2;
  Double_t tmpdelta = exp(-(mynll-like_centr));
  Double_t newlike = 0.;

  for (Long64_t kentry=0; kentry<nentries;kentry++) {
    fChain->GetEntry(kentry);
    Double_t myexp = exp(-(pow(myc1-tmpc1,2.)/sigmax2 + pow(myc2-tmpc2,2.)/sigmay2 - 2*rho*(myc1-tmpc1)*(myc2-tmpc2)/sqrt(sigmax2*sigmay2)));
    newlike += exp(-(mynll-like_centr))*myexp;
  }

  //cout << "newnll " << newlike << endl;
  //cout << "oldnll " << tmpdelta << endl;

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
    newlike += exp(-(mynll-like_centr))*myexp;
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

 TFile f("c1c2nll_tmp.root","RECREATE");
f.cd();
finit->Write();
fChain->Write();
f.mkdir("dir");
f.cd("dir");
h->Write();
hsyst->Write();
f.Close();

}
