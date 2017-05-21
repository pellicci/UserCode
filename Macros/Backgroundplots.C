{
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0);
gStyle->SetPalette(1);

TH1F *m2Kpi_leftRS[5], *m2Kpi0_leftRS[5], *m2pipi0_leftRS[5], *m2Kpi_rightRS[5], *m2Kpi0_rightRS[5], *m2pipi0_rightRS[5];
TH1F *m2Kpi_sigregRS[5], *m2Kpi0_sigregRS[5], *m2pipi0_sigregRS[5];

TFile f("dstar_out_SPall.root");

for(Int_t i=0;i<5;i++){
  char left12[100];
  sprintf(left12,"m2Kpi_leftWS_%d",i);
  char left13[100];
  sprintf(left13,"m2Kpi0_leftWS_%d",i);
  char left23[100];
  sprintf(left23,"m2pipi0_leftWS_%d",i);

  char right12[100];
  sprintf(right12,"m2Kpi_rightWS_%d",i);
  char right13[100];
  sprintf(right13,"m2Kpi0_rightWS_%d",i);
  char right23[100];
  sprintf(right23,"m2pipi0_rightWS_%d",i);

  char sigreg12[100];
  sprintf(sigreg12,"m2Kpi_sigregWS_%d",i);
  char sigreg13[100];
  sprintf(sigreg13,"m2Kpi0_sigregWS_%d",i);
  char sigreg23[100];
  sprintf(sigreg23,"m2pipi0_sigregWS_%d",i);

  m2Kpi_leftRS[i] = (TH1F*)f.Get(left12);
  m2Kpi_rightRS[i]= (TH1F*)f.Get(right12);
  m2Kpi0_leftRS[i]= (TH1F*)f.Get(left13);
  m2Kpi0_rightRS[i]= (TH1F*)f.Get(right13);
  m2pipi0_leftRS[i]= (TH1F*)f.Get(left23);
  m2pipi0_rightRS[i]= (TH1F*)f.Get(right23);

  m2Kpi_sigregRS[i]= (TH1F*)f.Get(sigreg12);
  m2Kpi0_sigregRS[i]= (TH1F*)f.Get(sigreg13);
  m2pipi0_sigregRS[i]= (TH1F*)f.Get(sigreg23);
}

for(Int_t i=1;i<5;i++){
  m2Kpi_sigregRS[i]->Scale(m2Kpi_sigregRS[0]->Integral()/m2Kpi_sigregRS[i]->Integral());
  m2Kpi0_sigregRS[i]->Scale(m2Kpi0_sigregRS[0]->Integral()/m2Kpi0_sigregRS[i]->Integral());
}

m2Kpi_sigregRS[1]->SetLineColor(kBlue);
m2Kpi_sigregRS[2]->SetLineColor(kRed);
m2Kpi_sigregRS[3]->SetLineColor(kGreen);
m2Kpi_sigregRS[4]->SetLineColor(134);

m2Kpi0_sigregRS[1]->SetLineColor(kBlue);
m2Kpi0_sigregRS[2]->SetLineColor(kRed);
m2Kpi0_sigregRS[3]->SetLineColor(kGreen);
m2Kpi0_sigregRS[4]->SetLineColor(134);

TLegend leg(0.7,0.7,0.9,0.9,"");
leg.AddEntry(m2Kpi_sigregRS[0],"-2 < t_{D^{0}} < 0 ps","l");
leg.AddEntry(m2Kpi_sigregRS[1],"0 < t_{D^{0}} < 0.2 ps","l");
leg.AddEntry(m2Kpi_sigregRS[2],"0.2 < t_{D^{0}} < 0.4 ps","l");
leg.AddEntry(m2Kpi_sigregRS[3],"0.4 < t_{D^{0}} < 0.8 ps","l");
leg.AddEntry(m2Kpi_sigregRS[4],"0.8 < t_{D^{0}} < 4 ps","l");

TH1F *dummy = new TH1F("dummy","dummy",50,0.3,3.1);
dummy->SetMaximum(60.);
dummy->SetTitle("");
dummy->GetXaxis()->SetTitle("m^{2}_{K^{+}#pi^{-}}");

for(Int_t i=0;i<5;i++) m2Kpi_sigregRS[i]->Rebin(6);
for(Int_t i=0;i<5;i++) m2Kpi0_sigregRS[i]->Rebin(6);
m2Kpi_sigregRS[4]->SetMaximum(40);
m2Kpi0_sigregRS[4]->SetMaximum(25);

TCanvas c2;
c2.cd();dummy->Draw();
for(Int_t i=0;i<5;i++) m2Kpi_sigregRS[i]->Draw("SAME");
leg.Draw("same");
c2.SaveAs("plot3.eps");

dummy->GetXaxis()->SetTitle("m^{2}_{K^{+}#pi^{0}}");

TCanvas c3;
c3.cd();dummy->Draw();
for(Int_t i=0;i<5;i++) m2Kpi0_sigregRS[i]->Draw("SAME");
leg.Draw("same");
c3.SaveAs("plot4.eps");

for(Int_t i=0;i<5;i++){
  m2Kpi_rightRS[i]->Scale(m2Kpi_leftRS[i]->Integral()/m2Kpi_rightRS[i]->Integral());
  m2Kpi0_rightRS[i]->Scale(m2Kpi0_leftRS[i]->Integral()/m2Kpi0_rightRS[i]->Integral());
  m2Kpi_leftRS[i]->Add(m2Kpi_rightRS[i],1.);
  m2Kpi0_leftRS[i]->Add(m2Kpi0_rightRS[i],1.);
  m2Kpi_leftRS[i]->Scale(m2Kpi_sigregRS[i]->Integral()/m2Kpi_leftRS[i]->Integral());
  m2Kpi0_leftRS[i]->Scale(m2Kpi0_sigregRS[i]->Integral()/m2Kpi0_leftRS[i]->Integral());
}

for(Int_t i=0;i<5;i++) m2Kpi_leftRS[i]->Rebin(6);
for(Int_t i=0;i<5;i++) m2Kpi0_leftRS[i]->Rebin(6);

/*m2Kpi_leftRS[1]->SetMaximum(40);
m2Kpi_leftRS[3]->SetMaximum(40);
m2Kpi_leftRS[4]->SetMaximum(40);
m2Kpi_sigregRS[4]->SetMaximum(30);
m2Kpi0_leftRS[2]->SetMaximum(50);
m2Kpi0_sigregRS[3]->SetMaximum(45);
m2Kpi0_sigregRS[4]->SetMaximum(40);

m2Kpi_sigregRS[2]->SetBinContent(m2Kpi_sigregRS[2]->GetMaximumBin(),31.);
m2Kpi_sigregRS[3]->SetBinContent(m2Kpi_sigregRS[3]->GetMaximumBin(),20.);
m2Kpi_sigregRS[3]->SetBinContent(m2Kpi_sigregRS[3]->GetMaximumBin(),10.);
m2Kpi_sigregRS[4]->SetBinContent(m2Kpi_sigregRS[4]->GetMaximumBin(),40.);
m2Kpi_sigregRS[4]->SetBinContent(m2Kpi_sigregRS[4]->GetMaximumBin(),35.);
m2Kpi_sigregRS[4]->SetBinContent(m2Kpi_sigregRS[4]->GetMaximumBin(),25.);
m2Kpi0_sigregRS[3]->SetBinContent(m2Kpi0_sigregRS[3]->GetMaximumBin(),30.);
m2Kpi0_sigregRS[3]->SetBinContent(m2Kpi0_sigregRS[3]->GetMaximumBin(),28.);
m2Kpi0_sigregRS[4]->SetBinContent(m2Kpi0_sigregRS[4]->GetMaximumBin(),10.);
m2Kpi0_sigregRS[4]->SetBinContent(m2Kpi0_sigregRS[4]->GetMaximumBin(),12.);
*/

TCanvas c4;
c4.Divide(3,2);
for(Int_t i=0;i<5;i++){ 
  c4.cd(i+1);
dummy->Draw();
  m2Kpi_sigregRS[i]->Draw("SAMEE");
  m2Kpi_leftRS[i]->Draw("SAME");
  }
 c4.SaveAs("sidecomb.eps");

TCanvas c5;
c5.Divide(3,2);
for(Int_t i=0;i<5;i++){ 
  c5.cd(i+1);
dummy->Draw();
  m2Kpi0_sigregRS[i]->Draw("SAMEE");
  m2Kpi0_leftRS[i]->Draw("SAME");
  }
 c5.SaveAs("sidecomb2.eps");



/*


TH1F *t_leftRS = (TH1F*)f.Get("t_leftRS");
TH1F *t_rightRS = (TH1F*)f.Get("t_rightRS");
TH1F *lifeErr_leftRS = (TH1F*)f.Get("lifeErr_leftRS");
TH1F *lifeErr_rightRS = (TH1F*)f.Get("lifeErr_rightRS");

TH1F *m2Kpi_sigregRS = (TH1F*)f.Get("m2Kpi_sigregRS");
TH1F *m2Kpi0_sigregRS = (TH1F*)f.Get("m2Kpi0_sigregRS");
TH1F *m2pipi0_sigregRS = (TH1F*)f.Get("m2pipi0_sigregRS");
TH1F *t_sigregRS = (TH1F*)f.Get("t_sigregRS");
TH1F *lifeErr_sigregRS = (TH1F*)f.Get("lifeErr_sigregRS");

TFile f1("dstar_out_dataR18.root");
TH1F *m2Kpi_leftRS_data = (TH1F*)f1.Get("m2Kpi_leftWS");
TH1F *m2Kpi_rightRS_data = (TH1F*)f1.Get("m2Kpi_rightWS");
TH1F *m2Kpi0_leftRS_data = (TH1F*)f1.Get("m2Kpi0_leftWS");
TH1F *m2Kpi0_rightRS_data = (TH1F*)f1.Get("m2Kpi0_rightWS");
TH1F *m2pipi0_leftRS_data = (TH1F*)f1.Get("m2pipi0_leftWS");
TH1F *m2pipi0_rightRS_data = (TH1F*)f1.Get("m2pipi0_rightWS");
TH1F *t_leftRS_data = (TH1F*)f1.Get("t_leftWS");
TH1F *t_rightRS_data = (TH1F*)f1.Get("t_rightWS");

m2Kpi_leftRS->Sumw2();
m2Kpi_rightRS->Sumw2();
m2Kpi0_leftRS->Sumw2();
m2Kpi0_rightRS->Sumw2();
m2pipi0_leftRS->Sumw2();
m2pipi0_rightRS->Sumw2();
t_leftRS->Sumw2();
t_rightRS->Sumw2();
lifeErr_leftRS->Sumw2();
lifeErr_rightRS->Sumw2();

m2Kpi_leftRS_data->Sumw2();
m2Kpi_rightRS_data->Sumw2();
m2Kpi0_leftRS_data->Sumw2();
m2Kpi0_rightRS_data->Sumw2();
m2pipi0_leftRS_data->Sumw2();
m2pipi0_rightRS_data->Sumw2();
t_leftRS_data->Sumw2();
t_rightRS_data->Sumw2();

m2Kpi_sigregRS->Sumw2();
m2Kpi0_sigregRS->Sumw2();
m2pipi0_sigregRS->Sumw2();
t_sigregRS->Sumw2();
lifeErr_sigregRS->Sumw2();

m2Kpi_rightRS->Scale(m2Kpi_leftRS->Integral()/m2Kpi_rightRS->Integral());
m2Kpi_rightRS->Sumw2();
m2Kpi0_rightRS->Scale(m2Kpi0_leftRS->Integral()/m2Kpi0_rightRS->Integral());
m2Kpi0_rightRS->Sumw2();
m2pipi0_rightRS->Scale(m2pipi0_leftRS->Integral()/m2pipi0_rightRS->Integral());
m2pipi0_rightRS->Sumw2();
t_rightRS->Scale(t_leftRS->Integral()/t_rightRS->Integral());
t_rightRS->Sumw2();
lifeErr_rightRS->Scale(lifeErr_leftRS->Integral()/lifeErr_rightRS->Integral());
lifeErr_rightRS->Sumw2();
///*
m2Kpi_leftRS->Rebin(2);
m2Kpi_rightRS->Rebin(2);
m2Kpi0_leftRS->Rebin(2);
m2Kpi0_rightRS->Rebin(2);
m2pipi0_leftRS->Rebin(2);
m2pipi0_rightRS->Rebin(2);
t_leftRS->Rebin(2);
t_rightRS->Rebin(2);
m2Kpi_leftRS_data->Rebin(2);
m2Kpi_rightRS_data->Rebin(2);
m2Kpi0_leftRS_data->Rebin(2);
m2Kpi0_rightRS_data->Rebin(2);
m2pipi0_leftRS_data->Rebin(2);
m2pipi0_rightRS_data->Rebin(2);
t_leftRS_data->Rebin(2);
t_rightRS_data->Rebin(2);

m2Kpi_sigregRS->Rebin(2);
m2Kpi0_sigregRS->Rebin(2);
m2pipi0_sigregRS->Rebin(2);
//*/
m2Kpi_leftRS_data->Scale(m2Kpi_leftRS->Integral()/m2Kpi_leftRS_data->Integral());
m2Kpi0_leftRS_data->Scale(m2Kpi0_leftRS->Integral()/m2Kpi0_leftRS_data->Integral());
m2pipi0_leftRS_data->Scale(m2pipi0_leftRS->Integral()/m2pipi0_leftRS_data->Integral());
m2Kpi_rightRS_data->Scale(m2Kpi_rightRS->Integral()/m2Kpi_rightRS_data->Integral());
m2Kpi0_rightRS_data->Scale(m2Kpi0_rightRS->Integral()/m2Kpi0_rightRS_data->Integral());
m2pipi0_rightRS_data->Scale(m2pipi0_rightRS->Integral()/m2pipi0_rightRS_data->Integral());
t_leftRS_data->Scale(t_leftRS->Integral()/t_leftRS_data->Integral());
t_rightRS_data->Scale(t_rightRS->Integral()/t_rightRS_data->Integral());

m2Kpi_leftRS->SetMaximum(m2Kpi_leftRS_data->GetMaximum()+sqrt(m2Kpi_leftRS_data->GetMaximum())+5);
m2Kpi_rightRS->SetMaximum(m2Kpi_rightRS_data->GetMaximum()+sqrt(m2Kpi_rightRS_data->GetMaximum())+5);
m2Kpi0_leftRS->SetMaximum(m2Kpi0_leftRS_data->GetMaximum()+sqrt(m2Kpi0_leftRS_data->GetMaximum())+5);
m2Kpi0_rightRS->SetMaximum(m2Kpi0_rightRS_data->GetMaximum()+sqrt(m2Kpi0_rightRS_data->GetMaximum())+5);
m2pipi0_leftRS->SetMaximum(m2pipi0_leftRS_data->GetMaximum()+sqrt(m2pipi0_leftRS_data->GetMaximum())+5);
m2pipi0_rightRS->SetMaximum(m2pipi0_rightRS_data->GetMaximum()+sqrt(m2pipi0_rightRS_data->GetMaximum())+5);
t_leftRS->SetMaximum(t_leftRS_data->GetMaximum()+sqrt(t_leftRS_data->GetMaximum())+30);
t_rightRS->SetMaximum(t_rightRS_data->GetMaximum()+sqrt(t_rightRS_data->GetMaximum())+10);

m2Kpi_leftRS->Add(m2Kpi_rightRS,(1-0.738)/0.738);
m2Kpi0_leftRS->Add(m2Kpi0_rightRS,(1-0.738)/0.738);
m2pipi0_leftRS->Add(m2pipi0_rightRS,(1.0.738)/0.738);

m2Kpi_leftRS->Scale(m2Kpi_sigregRS->Integral()/m2Kpi_leftRS->Integral());
m2Kpi0_leftRS->Scale(m2Kpi0_sigregRS->Integral()/m2Kpi0_leftRS->Integral());
m2pipi0_leftRS->Scale(m2pipi0_sigregRS->Integral()/m2pipi0_leftRS->Integral());

m2Kpi_sigregRS->SetLineColor(kBlue);
m2Kpi0_sigregRS->SetLineColor(kBlue);
m2pipi0_sigregRS->SetLineColor(kBlue);

Double_t kol1 = m2Kpi_sigregRS->Chi2Test(m2Kpi_leftRS,"P");
Double_t kol2 = m2Kpi0_sigregRS->Chi2Test(m2Kpi0_leftRS,"P");
Double_t kol3 = m2pipi0_sigregRS->Chi2Test(m2pipi0_leftRS,"P");

cout << "k1 = " << kol1 << endl;
cout << "k2 = " << kol2 << endl;
cout << "k3 = " << kol3 << endl;

m2Kpi_sigregRS->SetTitle("");
m2Kpi_sigregRS->GetXaxis()->SetTitle("m^{2}_{K#pi}");
m2Kpi0_sigregRS->SetTitle("");
m2Kpi0_sigregRS->GetXaxis()->SetTitle("m^{2}_{K#pi^{0}}");
m2pipi0_leftRS->SetTitle("");
m2pipi0_leftRS->GetXaxis()->SetTitle("m^{2}_{#pi#pi^{0}}");

TCanvas *ctmp = new TCanvas("ctmp","allevents",1200,400);
ctmp->Divide(3,1);
ctmp->cd(1);m2Kpi_sigregRS->Draw("E");m2Kpi_leftRS->Draw("eSAME");
ctmp->cd(2);m2Kpi0_sigregRS->Draw("E");m2Kpi0_leftRS->Draw("eSAME");
ctmp->cd(3);m2pipi0_leftRS->Draw("E");m2pipi0_sigregRS->Draw("eSAME");
ctmp->SaveAs("prova.eps");

///*
  m2Kpi_leftRS->SetTitle("m^{2}_{K#pi} distribution for the left sideband");
  m2Kpi_rightRS->SetTitle("m^{2}_{K#pi} distribution for the right sideband");
  m2Kpi0_leftRS->SetTitle("m^{2}_{K#pi^{0}} distribution for the left sideband");
  m2Kpi0_rightRS->SetTitle("m^{2}_{K#pi^{0}} distribution for the right sideband");
  m2pipi0_leftRS->SetTitle("m^{2}_{#pi#pi^{0}} distribution for the left sideband");
  m2pipi0_rightRS->SetTitle("m^{2}_{#pi#pi^{0}} distribution for the right sideband");
  t_leftRS->SetTitle("t_{K#pi#pi^{0}} distribution for the left sideband");
  t_rightRS->SetTitle("t_{K#pi#pi^{0}} distribution for the right sideband");

  m2Kpi_leftRS->GetXaxis()->SetTitle("m^{2}_{K#pi}");
  m2Kpi_rightRS->GetXaxis()->SetTitle("m^{2}_{K#pi}");
  m2Kpi0_leftRS->GetXaxis()->SetTitle("m^{2}_{K#pi^{0}}");
  m2Kpi0_rightRS->GetXaxis()->SetTitle("m^{2}_{K#pi^{0}}");
  m2pipi0_leftRS->GetXaxis()->SetTitle("m^{2}_{#pi#pi^{0}}");
  m2pipi0_rightRS->GetXaxis()->SetTitle("m^{2}_{#pi#pi^{0}}");
  t_leftRS->GetXaxis()->SetTitle("t_{K#pi#pi^{0}} (ps)");
  t_rightRS->GetXaxis()->SetTitle("t_{K#pi#pi^{0}} (ps)");
  lifeErr_leftRS->GetXaxis()->SetTitle("#sigma_{t_{K#pi#pi^{0}}} (ps)");
  lifeErr_rightRS->GetXaxis()->SetTitle("#sigma_{t_{K#pi#pi^{0}}} (ps)");

  TCanvas c1;
  c1.Divide(1,2);
  c1.cd(1); m2Kpi_leftRS->Draw("HIST");m2Kpi_leftRS_data->Draw("SAMEE");
  c1.cd(2);m2Kpi_rightRS->Draw("HIST");m2Kpi_rightRS_data->Draw("SAMEE");
  c1.SaveAs("bkgDalitz_RS_m2Kpi.eps");

  TCanvas c2;
  c2.Divide(1,2);
  c2.cd(1); m2Kpi0_leftRS->Draw("HIST");m2Kpi0_leftRS_data->Draw("SAMEE");
  c2.cd(2);m2Kpi0_rightRS->Draw("HIST");m2Kpi0_rightRS_data->Draw("SAMEE");
  c2.SaveAs("bkgDalitz_RS_m2Kpi0.eps");

  TCanvas c3;
  c3.Divide(1,2);
  c3.cd(1); m2pipi0_leftRS->Draw("HIST");m2pipi0_leftRS_data->Draw("SAMEE");
  c3.cd(2);m2pipi0_rightRS->Draw("HIST");m2pipi0_rightRS_data->Draw("SAMEE");
  c3.SaveAs("bkgDalitz_RS_m2pipi0.eps");

  TCanvas c4;
  c4.Divide(1,2);
  c4.cd(1);t_leftRS->Draw("HIST");t_leftRS_data->Draw("SAMEE");
  c4.cd(2);t_rightRS->Draw("HIST");t_rightRS_data->Draw("SAMEE");
  c4.SaveAs("bkgDalitz_RS_t.eps");
//*/
m2Kpi_leftRS->Add(m2Kpi_rightRS,1.);
m2Kpi_leftRS->Sumw2();
m2Kpi0_leftRS->Add(m2Kpi0_rightRS,1.);
m2Kpi0_leftRS->Sumw2();
m2pipi0_leftRS->Add(m2pipi0_rightRS,1.);
m2pipi0_leftRS->Sumw2();
t_leftRS->Add(t_rightRS,1.);
t_leftRS->Sumw2();
lifeErr_leftRS->Add(lifeErr_rightRS,1.);
lifeErr_leftRS->Sumw2();

m2Kpi_leftRS->Scale(m2Kpi_sigregRS->Integral()/m2Kpi_leftRS->Integral());
m2Kpi_leftRS->SetTitle("");
m2Kpi_sigregRS->SetTitle("");
m2Kpi0_leftRS->Scale(m2Kpi0_sigregRS->Integral()/m2Kpi0_leftRS->Integral());
m2Kpi0_leftRS->SetTitle("");
m2Kpi0_sigregRS->SetTitle("");
m2pipi0_leftRS->Scale(m2pipi0_sigregRS->Integral()/m2pipi0_leftRS->Integral());
m2pipi0_leftRS->SetTitle("");
m2pipi0_sigregRS->SetTitle("");
t_leftRS->Scale(t_sigregRS->Integral()/t_leftRS->Integral());
t_leftRS->SetTitle("");
t_sigregRS->SetTitle("");
lifeErr_leftRS->Scale(lifeErr_sigregRS->Integral()/lifeErr_leftRS->Integral());
lifeErr_leftRS->SetTitle("");
lifeErr_sigregRS->SetTitle("");

m2Kpi_leftRS->Rebin(1);
m2Kpi_sigregRS->Rebin(1);
m2Kpi0_leftRS->Rebin(1);
m2Kpi0_sigregRS->Rebin(1);
m2pipi0_leftRS->Rebin(1);
m2pipi0_sigregRS->Rebin(1);
//t_leftRS->Rebin();
//t_sigregRS->Rebin();
lifeErr_leftRS->Rebin(6);
lifeErr_sigregRS->Rebin(6);

Double_t chi2_Kpi = m2Kpi_leftRS->Chi2Test(m2Kpi_sigregRS,"UU");
Double_t chi2_Kpi0 = m2Kpi0_leftRS->Chi2Test(m2Kpi0_sigregRS,"UU");
Double_t chi2_pipi0 = m2pipi0_leftRS->Chi2Test(m2pipi0_sigregRS,"UU");
Double_t chi2_t = t_leftRS->Chi2Test(t_sigregRS,"PUW");
Double_t chi2_terr = lifeErr_leftRS->Chi2Test(lifeErr_sigregRS,"UU");

cout << "chi2 Kpi = " << chi2_Kpi << endl;
cout << "chi2 Kpi0 = " << chi2_Kpi0 << endl;
cout << "chi2 pipi0 = " << chi2_pipi0 << endl;
cout << "chi2 t = " << chi2_t << endl;
cout << "chi2 t err = " << chi2_terr << endl;

m2Kpi_leftRS->SetLineColor(kBlue);
m2Kpi0_leftRS->SetLineColor(kBlue);
m2pipi0_leftRS->SetLineColor(kBlue);
t_leftRS->SetLineColor(kBlue);
lifeErr_leftRS->SetLineColor(kBlue);
t_leftRS->SetMaximum(t_leftRS->GetMaximum()+50.);
lifeErr_leftRS->SetMaximum(lifeErr_leftRS->GetMaximum()+50.);

TCanvas c5;
c5.cd();m2Kpi_leftRS->Draw("HIST");
m2Kpi_sigregRS->Draw("SAMEE");
c5.SaveAs("bkgDalitz_WS_merged_Kpi.eps");

TCanvas c6;
c6.cd();m2Kpi0_leftRS->Draw("HIST");
m2Kpi0_sigregRS->Draw("SAMEE");
c6.SaveAs("bkgDalitz_WS_merged_Kpi0.eps");

TCanvas c7;
c7.cd();m2pipi0_leftRS->Draw("HIST");
m2pipi0_sigregRS->Draw("SAMEE");
c7.SaveAs("bkgDalitz_WS_merged_pipi0.eps");

TCanvas c8;
c8.cd();t_leftRS->Draw("HIST");
t_sigregRS->Draw("SAMEE");
c8.SaveAs("bkgDalitz_WS_merged_t.eps");

TCanvas c9;
c9.cd();lifeErr_leftRS->Draw("E");
lifeErr_sigregRS->Draw("SAMEE");
c9.SaveAs("bkgDalitz_WS_merged_terr.eps");

t_leftRS->Add(t_sigregRS,-1.);
t_leftRS->Draw();

gStyle->SetOptFit(0111);
t_leftRS->Fit("pol1");
TF1 *myf = t_leftRS->GetFunction("pol1");

Double_t chi2 = myf->GetChisquare();

cout << "chi2 " << chi2/13. << endl;
*/

}
