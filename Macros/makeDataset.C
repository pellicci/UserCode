{
gROOT->Reset();

//calculate the dalitz boundary
Float_t md0 = 1.8645;
Float_t mk = 0.493677;
Float_t mpi0 = 0.1349766;
Float_t mpi = 0.13957018;

Float_t m12upper=pow(md0-mpi0,2);
Float_t m12lower=pow(mk+mpi,2);

Float_t m13upper=pow(md0-mpi,2);
Float_t m13lower=pow(mk+mpi0,2);

Float_t m23lower=pow(mpi+mpi0,2);
Float_t m23upper=pow(md0-mk,2);

Float_t d0lower = 1.;
Float_t d0upper = 2.99;

Float_t deltalower = 0.137;
Float_t deltaupper = 0.16;

Float_t efflower = -50;
Float_t effupper = 50;

Float_t sweightlower = -50.0;
Float_t sweightupper = 50.0;

Float_t timelow = -50.;
Float_t timehigh = 50.;

Float_t total=md0*md0+mk*mk+mpi*mpi+mpi0*mpi0;
RooRealVar totalm("totalm","totalm",total);

RooRealVar d0Mass("d0Mass","d0Mass",d0lower,d0upper);
RooRealVar deltaMass("deltaMass","deltaMass",deltalower,deltaupper);
RooRealVar m2Kpi_d0mass("m2Kpi_d0mass","m2Kpi_d0mass",m12lower,m12upper);
RooRealVar m2Kpi0_d0mass("m2Kpi0_d0mass","m2Kpi0_d0mass",m13lower,m13upper);
RooRealVar m2pipi0_d0mass("m2pipi0_d0mass","m2pipi0_d0mass",m23lower,m23upper);
RooRealVar pi0Pmag("pi0Pmag","pi0Pmag",0.,6.);
RooRealVar d0P_phi("d0P_phi","d0P_phi",-acos(-1.),acos(-1.));
RooRealVar d0P_theta("d0P_theta","d0P_theta",-10.,10.);
RooRealVar runnumber("runnumber","runnumber",0.,0.,100000000.);
RooCategory D0flav("D0flav","D0flav");
D0flav.defineType("D0",-1);
D0flav.defineType("antiD0",1);
RooRealVar d0Lifetime("d0Lifetime","d0Lifetime",timelow,timehigh);
RooRealVar d0LifetimeErr("d0LifetimeErr","d0LifetimeErr",timelow,timehigh);
RooCategory tag_opp_side("tag_opp_side","tag_opp_side");
tag_opp_side.defineType("notag",0);
tag_opp_side.defineType("tag",1);
RooCategory isWS("isWS","isWS");
isWS.defineType("RS",0);
isWS.defineType("WS",1);

RooCategory tag_K("tag_K","tag_K");
tag_K.defineType("TagK",1);
tag_K.defineType("UntaggedK",0);
RooCategory tag_pi("tag_pi","tag_pi");
tag_pi.defineType("Tagpi",1);
tag_pi.defineType("Untaggedpi",0);
RooCategory tag_e("tag_e","tag_e");
tag_e.defineType("Tage",1);
tag_e.defineType("Untaggede",0);
RooCategory tag_mu("tag_mu","tag_mu");
tag_mu.defineType("Tagmu",1);
tag_mu.defineType("Untaggedmu",0);

RooCategory truthIsSignal("truthIsSignal","truthIsSignal");
truthIsSignal.defineType("is_sig",1);
truthIsSignal.defineType("is__not_sig",0);
RooCategory truthIsBkg_FakePiSlow("truthIsBkg_FakePiSlow","truthIsBkg_FakePiSlow");
truthIsBkg_FakePiSlow.defineType("is_mistag",1);
truthIsBkg_FakePiSlow.defineType("is_not_mistag",0);

RooArgSet list;
list.add(d0Mass);
list.add(deltaMass);
list.add(m2Kpi_d0mass);
list.add(m2Kpi0_d0mass);
list.add(m2pipi0_d0mass);
//list.add(pi0Pmag);
list.add(D0flav);
list.add(isWS);
list.add(d0Lifetime);
list.add(d0LifetimeErr);
list.add(tag_opp_side);
list.add(d0P_phi);
list.add(d0P_theta);
//list.add(runnumber);
//list.add(tag_K);
//list.add(tag_pi);
//list.add(tag_e);
//list.add(tag_mu);
list.add(truthIsSignal);
list.add(truthIsBkg_FakePiSlow);

//read in the dataset
TChain *tree = new TChain("ntp3");
tree->Add("Data.root");
gROOT->cd();

RooDataSet *data = new RooDataSet("fulldata","fulldata",tree,list);
//RooDataSet *data = fulldata->reduce("tag_opp_side == 1");

//RooRealVar intercept("intercept","intercept",0.976776);
//RooRealVar slope("slope","slope",0.00591363);
//data->addColumn(intercept);
//data->addColumn(slope);
//RooFormulaVar eff_pi0("eff_pi0","@0 + @1*@2",RooArgSet(intercept,slope,pi0Pmag));
//data->addColumn(eff_pi0);

//save the DataSet, just in case
TFile file("DataSet_out_tmp_MC.root","RECREATE");
file.cd();
data->Write();
//data->write("dataR18/DataSet_out_signal.root");
file.Close();

}  //end the macro
