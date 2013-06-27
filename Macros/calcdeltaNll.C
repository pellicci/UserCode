{

gROOT->Reset();
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0);
gStyle->SetPalette(1);

gStyle->SetOptFit(0111);

RooArgSet params;               

TH1F *probchi2 = new TH1F("probchi2","probchi2",30,0.,1.);
TH1F *mychi2 = new TH1F("mychi2","mychi2",30,0.,20.);

for(Int_t i=1;i<=2000;i++){

  cout << "Now doing toy number " << i << endl;

  char filename1[200];
  sprintf(filename1,"Toy_results/central_value/toy_%d.root",i);
  TFile f1(filename1);

  RooFitResult *nll_1 = (RooFitResult*)f1.Get("nll");

  if(f1.GetSize() <=0) continue;

  char filename2[200];
  sprintf(filename2,"Toy_results/central_value/toy_%d_fixed.root",i);
  TFile f2(filename2);

  RooFitResult *nll_2 = (RooFitResult*)f2.Get("nll");

  Double_t deltalog = -2.*(nll_1->minNll() - nll_2->minNll());
  Double_t probchi = TMath::Prob(deltalog,2);

  probchi2->Fill(probchi);

  mychi2->Fill(deltalog);

  f1.Close();
  f2.Close();

}

probchi2->Fit("pol1","CF","SAME");

probchi2->SetTitle("");
probchi2->GetXaxis()->SetTitle("#chi^{2} probability");

TCanvas c1;
c1.cd();probchi2->Draw("E");
c1.SaveAs("probchi2.eps");

TCanvas c2;
c2.cd();mychi2->Draw("E");
c2.SaveAs("mychi2.eps");

}
