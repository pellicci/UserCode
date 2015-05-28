{

  double mH = 600.;
  double mlow = 400.;
  double mhigh = 800.;
  double cprimesq = 0.6;

  // 800 -> 304
  // 600 - > 123 

  TFile fIn("IntSMRatio.root");
  fIn.cd();

  TH1F *hRatio = (TH1F*)fIn.Get("IntSMRatio_mH600_C06");

  hRatio->SetAxisRange(mlow,mhigh);

  //Shape C'!=1
  //TF1 *f1 = new TF1("f1"," (1-[1]) * exp(- abs(pow(x-[0],3.))/pow(40.,3.) )  - x * pow(1.-[1],3.)/[0] + 1.2*[1] ",mlow,mhigh);
  TF1 *f1 = new TF1("f1"," - x * pow( (1.-[1])*(1.+[1]*[1]),3.)/[0] + [1] + (1.-[1])*(1-([0]-350.)/1000.) ",mlow,mhigh);

  f1->FixParameter(0,mH);
  f1->FixParameter(1,cprimesq);
  f1->SetParLimits(2,0.,1000.);

  TCanvas c1;
  //c1.SetLogy();
  hRatio->Fit("f1","RME");
  //hRatio->Draw("");
  //f1->Draw("SAME");

}
