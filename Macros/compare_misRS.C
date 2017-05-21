{

  gROOT->SetStyle("BABAR");
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  TFile f("dstar_out_SPall.root");

  TH1F *m2Kpi_RS = (TH1F*)f.Get("m2Kpi_RS");
  TH1F *m2Kpi0_RS = (TH1F*)f.Get("m2Kpi0_RS");
  TH1F *m2pipi0_RS = (TH1F*)f.Get("m2pipi0_RS");
  TH1F *t_RS = (TH1F*)f.Get("t_RS");

  TH1F *m2Kpi_misWS = (TH1F*)f.Get("m2Kpi_misWS");
  TH1F *m2Kpi0_misWS = (TH1F*)f.Get("m2Kpi0_misWS");
  TH1F *m2pipi0_misWS = (TH1F*)f.Get("m2pipi0_misWS");
  TH1F *t_misWS = (TH1F*)f.Get("t_misWS");

  m2Kpi_RS->SetTitle("");
  m2Kpi0_RS->SetTitle("");
  m2pipi0_RS->SetTitle("");
  t_RS->SetTitle("");

  m2Kpi_misWS->SetTitle("");
  m2Kpi0_misWS->SetTitle("");
  m2pipi0_misWS->SetTitle("");
  t_misWS->SetTitle("");

  m2Kpi_RS->Scale(m2Kpi_misWS->Integral()/m2Kpi_RS->Integral());
  m2Kpi0_RS->Scale(m2Kpi0_misWS->Integral()/m2Kpi0_RS->Integral());
  m2pipi0_RS->Scale(m2pipi0_misWS->Integral()/m2pipi0_RS->Integral());
  t_RS->Scale(t_misWS->Integral()/t_RS->Integral());

  m2Kpi_misWS->GetXaxis()->SetTitle("m^{2}_{K#pi}");
  m2Kpi0_misWS->GetXaxis()->SetTitle("m^{2}_{K#pi^{0}}");
  m2pipi0_misWS->GetXaxis()->SetTitle("m^{2}_{#pi#pi^{0}}");
  t_misWS->GetXaxis()->SetTitle("t_{K#pi#pi^{0}}");

  Double_t chi2_kpi = m2Kpi_RS->Chi2Test(m2Kpi_misWS);
  Double_t chi2_kpi0 = m2Kpi0_RS->Chi2Test(m2Kpi0_misWS);
  Double_t chi2_pipi0 = m2pipi0_RS->Chi2Test(m2pipi0_misWS);
  Double_t chi2_t = t_RS->Chi2Test(t_misWS);

  cout << "chi2/ndof value for Kpi " << chi2_kpi << endl;
  cout << "chi2/ndof value for Kpio " << chi2_kpi0 << endl;
  cout << "chi2/ndof value for pipi0 " << chi2_pipi0 << endl;
  cout << "chi2/ndof value for t " << chi2_t << endl;

  TCanvas c1;
  c1.cd();m2Kpi_misWS->Draw("E");m2Kpi_RS->Draw("SAME");
  c1.SaveAs("comb_WSmis_RSsig_kpi.eps");

  TCanvas c2;
  c2.cd();m2Kpi0_misWS->Draw("E");m2Kpi0_RS->Draw("SAME");
  c2.SaveAs("comb_WSmis_RSsig_kpi0.eps");

  TCanvas c3;
  c3.cd();m2pipi0_misWS->Draw("E");m2pipi0_RS->Draw("SAME");
  c3.SaveAs("comb_WSmis_RSsig_pipi0.eps");

  TCanvas c4;
  c4.cd();t_misWS->Draw("E");t_RS->Draw("SAME");
  c4.SaveAs("comb_WSmis_RSsig_t.eps");

}
