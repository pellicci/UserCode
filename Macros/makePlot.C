{
//gROOT->SetStyle("BABAR");
  gStyle->SetOptStat(0);

  //define DalitzSpace for generation
  EvtPDL pdl;
  pdl.readPDT("evt.pdl");
  EvtDecayMode mode("D0 -> K- pi+ pi0");
  EvtDalitzPlot dalitzSpace(mode);

  RooIsobar *RSpdf = new RooIsobar(-1,0,&dalitzSpace);
  RooIsobar *WSpdf = new RooIsobar(-1,1,&dalitzSpace);
  Double_t I3valueRS = RSpdf->getNormalization(); 
  Double_t I3valueWS = WSpdf->getNormalization();

  Float_t time=0.,m12=0.,m13=0.,m23=0.;
  Float_t Ampre = 0.,Ampim = 0.;
  Float_t d0LifetimeErr = 0.;
  Int_t D0tag = 0.;
  Float_t basis=0.,linear=0.,quad=0.;
  EvtDalitzPoint *point = new EvtDalitzPoint();

Float_t c1 = 0.5;
  Float_t c2 = -0.5;
  Float_t c3 = 0.005;
  Float_t c4 = 0.001;

  TTree *mixTree = new TTree("myTree","The mix tree");
  mixTree->Branch("time",&time,"time/F");
  mixTree->Branch("m12",&m12,"m12/F");
  mixTree->Branch("m13",&m13,"m13/F");
  mixTree->Branch("m23",&m23,"m23/F");
  mixTree->Branch("basis",&basis,"basis/F");
  mixTree->Branch("linear",&linear,"linear/F");
  mixTree->Branch("quad",&quad,"quad/F");

  for(Int_t k=1;k<=1;k++) {

    char filename[200];
    //sprintf(filename,"Toy_results/toynow3/toy_%d.dat",k);
    sprintf(filename,"prova.dat",k);

    ifstream f;
    f.open(filename);

    cout << "Opening file: " << filename << endl;

    //Read in the cache file and store back to array
    for(Int_t j=1;j<1000;j++) {
      time =0.;
      m12 = 0.;
      m13 = 0.;
      f >> time >> m12 >> m13 >> d0LifetimeErr >> D0tag;

      m23 = pow(dalitzSpace->bigM(),2) + pow(dalitzSpace->mA(),2) + pow(dalitzSpace->mB(),2) + pow(dalitzSpace->mC(),2) - m12 - m13;
      *point = EvtDalitzPoint(dalitzSpace->mA(),dalitzSpace->mB(),dalitzSpace->mC(),m12,m23,m13);

      RooComplex RSp = RooComplex(RSpdf->getamp_Re(point),RSpdf->getamp_Im(point))/RooComplex(sqrt(I3valueRS),0.);
      RooComplex WSp = RooComplex(WSpdf->getamp_Re(point),WSpdf->getamp_Im(point))/RooComplex(sqrt(I3valueWS),0.);
      RooComplex ProdAmpl = RSp*WSp.conj();
      basis = WSp.abs2();
      linear = c1*ProdAmpl.re() - c2*ProdAmpl.im();
      quad = (c1*c1 + c2*c2)*RSp.abs2()/4;
      mixTree->Fill();
    }
    f.close();
  }

  cout << "RS integral = " << I3valueRS << endl;
  cout << "WS integral = " << I3valueWS << endl;

  TH2F *dalitz = new TH2F("dalitz","Dalitz",100,0.28,3.3,40,0.20,3.3);
  TH1F *timeplot = new TH1F("timeplot","time",20,-2.,3.5);
  TH1F *m12plot = new TH1F("m12plot","m12plot",30,0.4,3.);
  TH1F *m13plot = new TH1F("m13plot","m13plot",30,0.4,3.);
  TH1F *m23plot = new TH1F("m23plot","m23plot",30,0.2,3.);

  dalitz->GetXaxis()->SetTitle("m^2_{K#pi}");
  dalitz->GetYaxis()->SetTitle("m^2_{K#pi^0}");

  TH1F *basplot = new TH1F("basplot","basisexp",20,0.,5.);
  TH1F *linplot = new TH1F("linplot","linearexp",20,-0.01,0.008);
  TH1F *quadplot = new TH1F("quadplot","quadexp",20,0.,0.1);

  mixTree->Project("dalitz","m13:m12");
  mixTree->Project("timeplot","time");
  mixTree->Project("m12plot","m12");
  mixTree->Project("m13plot","m13");
mixTree->Project("m23plot","m23");

  mixTree->Project("basplot","basis");
  mixTree->Project("linplot","linear");
  mixTree->Project("quadplot","quad");

  TCanvas can2;
  can2.Divide(2,3);
  can2.cd(1);timeplot->Draw();
  can2.cd(2);dalitz->Draw();
  can2.cd(3);m12plot->Draw();
  can2.cd(4);m13plot->Draw();
  can2.cd(5);m23plot->Draw();
  can2.SaveAs("dalitzgen_1.eps");

  TCanvas can3;
  can3.Divide(3,1);
  can3.cd(1);basplot->Draw();
  can3.cd(2);linplot->Draw();
  can3.cd(3);quadplot->Draw();
  can3.SaveAs("dalitzgen_2.eps");

}
