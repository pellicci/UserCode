{

TRandom gener;

//define DalitzSpace for generation
EvtPDL pdl;
pdl.readPDT("evt.pdl");
EvtDecayMode mode("D0 -> K- pi+ pi0");
EvtDalitzPlot dalitzSpace(mode);

RooRealVar t("t","t",-2.,4.);
RooRealVar m12("m12","m12",dalitzSpace.qAbsMin(EvtCyclic3::AB),dalitzSpace.qAbsMax(EvtCyclic3::AB));
RooRealVar m13("m13","m13",dalitzSpace.qAbsMin(EvtCyclic3::AC),dalitzSpace.qAbsMax(EvtCyclic3::AC));
RooRealVar terr("terr","terr",0.,0.5);

RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);

RooDataSet *init = RooDataSet::read("prova.dat",RooArgList(t,m12,m13,terr,D0flav));

TTree *fChain = (TTree*)init->tree();
Double_t myt = 0. , mym12 = 0., mym13 = 0., myterr = 0.;
Int_t D0flav_idx(0);

fChain->SetBranchAddress("t",&myt);
fChain->SetBranchAddress("m12",&mym12);
fChain->SetBranchAddress("m13",&mym13);
fChain->SetBranchAddress("terr",&myterr);
fChain->SetBranchAddress("D0flav_idx",&D0flav_idx);

const Double_t sigmax = 0.01;
const Double_t sigmay = 0.01;
//const Double_t rho = -0.0021/sqrt(sigmax2*sigmay2);

ofstream f("prova2.dat");
if (f.fail()){
  cout << "Error opening file " << endl;
  assert(0);
}

Long64_t nbytes = 0, nb = 0;
Long64_t nentries = fChain->GetEntriesFast();
for (Long64_t jentry=0; jentry<nentries;jentry++) {
  nb = fChain->GetEntry(jentry);   nbytes += nb;

  Double_t newm12(0.), newm13(0.);

  while(1){
    newm12 = gener->Gaus(mym12,sigmax);
    newm13 = gener->Gaus(mym13,sigmay);

    const Double_t newm23 = pow(dalitzSpace.bigM(),2) + pow(dalitzSpace.mA(),2) + pow(dalitzSpace.mB(),2) + pow(dalitzSpace.mC(),2) - newm12 - newm13;
    EvtDalitzPoint dalitzPoint(dalitzSpace.mA(),dalitzSpace.mB(),dalitzSpace.mC(),newm12,newm23,newm13);
    if(!dalitzPoint.isValid()) continue;

    break;
  }

  f << myt << " " << newm12 << " " << newm13 << " " << myterr << " " << D0flav_idx << endl;

  if(fmod((Double_t)jentry,100.) == 0) cout << "So far smerdated " << jentry << " events" << endl;


}

}
