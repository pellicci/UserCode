{
gROOT->SetStyle("BABAR");
gStyle->SetOptStat(0);
//gStyle->SetOptTitle(0);
gStyle->SetPalette(1);

TFile fR18("dstar_out_dataR18.root");
TFile fSP1005("dstar_out_SP1005.root");
TFile fSP1235("dstar_out_SP1235.root");
TFile fSP1237("dstar_out_SP1237.root");
TFile fSP998("dstar_out_SP998.root");

//plots for the data
TH1F *d0lifeErrR18RS = (TH1F*)fR18.Get("lifeErrRS");
TH1F *d0lifeErrR18WS = (TH1F*)fR18.Get("lifeErrWS");
TH1F *RSdeltaMR18 = (TH1F*)fR18.Get("deltamRS");
TH1F *WSdeltaMR18 = (TH1F*)fR18.Get("deltamWS");
TH1F *RSmD0R18 = (TH1F*)fR18.Get("mD0RS");
TH1F *WSmD0R18 = (TH1F*)fR18.Get("mD0WS");

TH1F *p_K = (TH1F*)fR18.Get("p_K");
TH1F *p_pi = (TH1F*)fR18.Get("p_pi");
TH1F *p_pis = (TH1F*)fR18.Get("p_pis");

//plots for the montecarlo
TH1F *d0lifeErrSigRS = (TH1F*)fSP1005.Get("lifeErrRS");
TH1F *d0lifeErrbkg1005RS = (TH1F*)fSP1005.Get("lifeErrRSbkg");
TH1F *d0lifeErrbkg1235RS = (TH1F*)fSP1235.Get("lifeErrRSbkg");
TH1F *d0lifeErrbkg1237RS = (TH1F*)fSP1237.Get("lifeErrRSbkg");
TH1F *d0lifeErrbkg998RS = (TH1F*)fSP998.Get("lifeErrRSbkg");

TH1F *d0lifeErrSigWS = (TH1F*)fSP1005.Get("lifeErrWS");
TH1F *d0lifeErrbkg1005WS = (TH1F*)fSP1005.Get("lifeErrWSbkg");
TH1F *d0lifeErrbkg1235WS = (TH1F*)fSP1235.Get("lifeErrWSbkg");
TH1F *d0lifeErrbkg1237WS = (TH1F*)fSP1237.Get("lifeErrWSbkg");
TH1F *d0lifeErrbkg998WS = (TH1F*)fSP998.Get("lifeErrWSbkg");

TH1F *RSdeltaMSig = (TH1F*)fSP1005.Get("deltamRS");
TH1F *RSdeltaMbkg1005 = (TH1F*)fSP1005.Get("deltamRSbkg1005");
TH1F *RSdeltaMbkg1235 = (TH1F*)fSP1235.Get("deltamRSbkg1235");
TH1F *RSdeltaMbkg1237 = (TH1F*)fSP1237.Get("deltamRSbkg1237");
TH1F *RSdeltaMbkg998 = (TH1F*)fSP998.Get("deltamRSbkg998");

TH1F *WSdeltaMSig = (TH1F*)fSP1005.Get("deltamWS");
TH1F *WSdeltaMbkg1005 = (TH1F*)fSP1005.Get("deltamWSbkg1005");
TH1F *WSdeltaMbkg1235 = (TH1F*)fSP1235.Get("deltamWSbkg1235");
TH1F *WSdeltaMbkg1237 = (TH1F*)fSP1237.Get("deltamWSbkg1237");
TH1F *WSdeltaMbkg998 = (TH1F*)fSP998.Get("deltamWSbkg998");

TH1F *RSmD0Sig = (TH1F*)fSP1005.Get("mD0RS");
TH1F *RSmD0bkg1005 = (TH1F*)fSP1005.Get("mD0RSbkg1005");
TH1F *RSmD0bkg1235 = (TH1F*)fSP1235.Get("mD0RSbkg1235");
TH1F *RSmD0bkg1237 = (TH1F*)fSP1237.Get("mD0RSbkg1237");
TH1F *RSmD0bkg998 = (TH1F*)fSP998.Get("mD0RSbkg998");

TH1F *WSmD0Sig = (TH1F*)fSP1005.Get("mD0WS");
TH1F *WSmD0bkg1005 = (TH1F*)fSP1005.Get("mD0WSbkg1005");
TH1F *WSmD0bkg1235 = (TH1F*)fSP1235.Get("mD0WSbkg1235");
TH1F *WSmD0bkg1237 = (TH1F*)fSP1237.Get("mD0WSbkg1237");
TH1F *WSmD0bkg998 = (TH1F*)fSP998.Get("mD0WSbkg998");

d0lifeErrR18WS->Rebin(2);
d0lifeErrSigWS->Rebin(2);
d0lifeErrbkg1005WS->Rebin(2);
d0lifeErrbkg1235WS->Rebin(2);
d0lifeErrbkg1237WS->Rebin(2);
d0lifeErrbkg998WS->Rebin(2);

d0lifeErrR18RS->GetXaxis()->SetTitle("t_{K #pi #pi^{0}} (ps)");
d0lifeErrR18WS->GetXaxis()->SetTitle("t_{K #pi #pi^{0}} (ps)");
RSdeltaMR18->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");
WSdeltaMR18->GetXaxis()->SetTitle("#Delta m (GeV/c^{2})");
RSmD0R18->GetXaxis()->SetTitle("m_{K #pi #pi^{0}} (GeV/c^{2})");
WSmD0R18->GetXaxis()->SetTitle("m_{K #pi #pi^{0}} (GeV/c^{2})");

p_K->GetXaxis()->SetTitle("Momentum (GeV/c)");
p_pi->GetXaxis()->SetTitle("Momentum (GeV/c)");
p_pis->GetXaxis()->SetTitle("Momentum (GeV/c)");

d0lifeErrR18RS->SetTitle("D^0 Lifetime Error");
d0lifeErrR18WS->SetTitle("D^0 Lifetime Error");
RSdeltaMR18->SetTitle("m_{D^*} - m_{D^0} for RS sample");
WSdeltaMR18->SetTitle("m_{D^*} - m_{D^0} for WS sample");
RSmD0R18->SetTitle("D^0 mass for RS sample");
WSmD0R18->SetTitle("D^0 mass for WS sample");

p_K->SetTitle("Kaons momentum");
p_pi->SetTitle("Pions momentum");
p_pis->SetTitle("Slow pions momentum");

//normalize MC to data luminosity
Float_t lumiSig = (1305070000.*0.68*0.141*0.98)/(1.3*pow(10.,6.));
Float_t lumi1005 = 1305070000./(1.3*pow(10.,6.));
Float_t lumi1235 = 599906000./(1.05*0.5*pow(10.,6.));
Float_t lumi1237 = 588108000./(1.05*0.5*pow(10.,6.));
Float_t lumi998 = 789876000./((0.35 + 1.39 + 0.35)*pow(10.,6.));
Float_t lumidata = 383.8255;

Float_t lumibbbar = (599906000. + 588108000.)/(1.05*pow(10.,6.));
Float_t lumiccbar = 1305070000./(1.3*pow(10.,6.));
Float_t lumiuds = 789876000./(2.05*pow(10.,6.));

d0lifeErrSigRS->Scale(lumidata/lumiccbar);
d0lifeErrbkg1005RS->Scale(lumidata/lumiccbar);
d0lifeErrbkg1235RS->Add(d0lifeErrbkg1237RS,1.);
d0lifeErrbkg1235RS->Scale(lumidata/lumibbbar);
d0lifeErrbkg998RS->Scale(lumidata/lumiuds);

d0lifeErrSigWS->Scale(lumidata/lumiccbar);
d0lifeErrbkg1005WS->Scale(lumidata/lumiccbar);
d0lifeErrbkg1235WS->Add(d0lifeErrbkg1237WS,1.);
d0lifeErrbkg1235WS->Scale(lumidata/lumibbbar);
d0lifeErrbkg998WS->Scale(lumidata/lumiuds);

RSdeltaMSig->Scale(lumidata/lumiccbar);
RSdeltaMbkg1005->Scale(lumidata/lumiccbar);
RSdeltaMbkg1235->Add(RSdeltaMbkg1237,1.);
RSdeltaMbkg1235->Scale(lumidata/lumibbbar);
RSdeltaMbkg998->Scale(lumidata/lumiuds);

WSdeltaMSig->Scale(lumidata/lumiccbar);
WSdeltaMbkg1005->Scale(lumidata/lumiccbar);
WSdeltaMbkg1235->Add(WSdeltaMbkg1237,1.);
WSdeltaMbkg1235->Scale(lumidata/lumibbbar);
WSdeltaMbkg998->Scale(lumidata/lumiuds);

RSmD0Sig->Scale(lumidata/lumiccbar);
RSmD0bkg1005->Scale(lumidata/lumiccbar);
RSmD0bkg1235->Add(RSmD0bkg1237,1.);
RSmD0bkg1235->Scale(lumidata/lumibbbar);
RSmD0bkg998->Scale(lumidata/lumiuds);

WSmD0Sig->Scale(lumidata/lumiccbar);
WSmD0bkg1005->Scale(lumidata/lumiccbar);
WSmD0bkg1235->Add(WSmD0bkg1237,1.);
WSmD0bkg1235->Scale(lumidata/lumibbbar);
WSmD0bkg998->Scale(lumidata/lumiuds);

TLegend errorlegRS(0.6,0.6,0.8,0.8,"");
errorlegRS.AddEntry(d0lifeErrR18RS,"data R18","l");
errorlegRS.AddEntry(d0lifeErrSigRS,"signal MC","f");
errorlegRS.AddEntry(d0lifeErrbkg1005RS,"charm MC","f");
errorlegRS.AddEntry(d0lifeErrbkg1235RS,"b#bar{b} MC","f");
errorlegRS.AddEntry(d0lifeErrbkg998RS,"uds MC","f");

TLegend errorlegWS(0.6,0.6,0.8,0.8,"");
errorlegWS.AddEntry(d0lifeErrR18WS,"data R18","l");
errorlegWS.AddEntry(d0lifeErrSigWS,"signal MC","f");
errorlegWS.AddEntry(d0lifeErrbkg1005WS,"charm MC","f");
errorlegWS.AddEntry(d0lifeErrbkg1235WS,"b#bar{b} MC","f");
errorlegWS.AddEntry(d0lifeErrbkg998WS,"uds MC","f");

TLegend deltaMRSleg(0.7,0.7,0.9,0.9,"");
deltaMRSleg.AddEntry(RSdeltaMR18,"data R18","l");
deltaMRSleg.AddEntry(RSdeltaMSig,"signal MC","f");
deltaMRSleg.AddEntry(RSdeltaMbkg1005,"charm MC","f");
deltaMRSleg.AddEntry(RSdeltaMbkg1235,"b#bar{b} MC","f");
deltaMRSleg.AddEntry(RSdeltaMbkg998,"uds MC","f");

TLegend deltaMWSleg(0.7,0.7,0.9,0.9,"");
deltaMWSleg.AddEntry(WSdeltaMR18,"data R18","l");
deltaMWSleg.AddEntry(WSdeltaMSig,"signal MC","f");
deltaMWSleg.AddEntry(WSdeltaMbkg1005,"charm MC","f");
deltaMWSleg.AddEntry(WSdeltaMbkg1235,"b#bar{b} MC","f");
deltaMWSleg.AddEntry(WSdeltaMbkg998,"uds MC","f");

TLegend mD0RSleg(0.7,0.7,0.9,0.9,"");
mD0RSleg.AddEntry(RSmD0R18,"data R18","l");
mD0RSleg.AddEntry(RSmD0Sig,"signal MC","f");
mD0RSleg.AddEntry(RSmD0bkg1005,"charm MC","f");
mD0RSleg.AddEntry(RSmD0bkg1235,"b#bar{b} MC","f");
mD0RSleg.AddEntry(RSmD0bkg998,"uds MC","f");

TLegend mD0WSleg(0.7,0.7,0.9,0.9,"");
mD0WSleg.AddEntry(WSmD0R18,"data R18","l");
mD0WSleg.AddEntry(WSmD0Sig,"signal MC","f");
mD0WSleg.AddEntry(WSmD0bkg1005,"charm MC","f");
mD0WSleg.AddEntry(WSmD0bkg1235,"b#bar{b} MC","f");
mD0WSleg.AddEntry(WSmD0bkg998,"uds MC","f");

d0lifeErrbkg1005RS->Add(d0lifeErrSigRS,1.);
d0lifeErrbkg1235RS->Add(d0lifeErrbkg1005RS,1.);
d0lifeErrbkg998RS->Add(d0lifeErrbkg1235RS,1.);
d0lifeErrR18RS->Scale(d0lifeErrbkg998RS->Integral()/d0lifeErrR18RS->Integral());
d0lifeErrbkg998RS->SetMaximum(d0lifeErrR18RS->GetMaximum());

d0lifeErrbkg1005WS->Add(d0lifeErrSigWS,1.);
d0lifeErrbkg1235WS->Add(d0lifeErrbkg1005WS,1.);
d0lifeErrbkg998WS->Add(d0lifeErrbkg1235WS,1.);
d0lifeErrR18WS->Scale(d0lifeErrbkg998WS->Integral()/d0lifeErrR18WS->Integral());
d0lifeErrbkg998WS->SetMaximum(d0lifeErrR18WS->GetMaximum());

RSdeltaMbkg1005->Add(RSdeltaMSig,1.);
RSdeltaMbkg1235->Add(RSdeltaMbkg1005,1.);
RSdeltaMbkg998->Add(RSdeltaMbkg1235,1.);
RSdeltaMR18->Scale(RSdeltaMbkg998->Integral()/RSdeltaMR18->Integral());
RSdeltaMR18->SetMaximum(RSdeltaMbkg998->GetMaximum());

WSdeltaMbkg1005->Add(WSdeltaMSig,1.);
WSdeltaMbkg1235->Add(WSdeltaMbkg1005,1.);
WSdeltaMbkg998->Add(WSdeltaMbkg1235,1.);
WSdeltaMR18->Scale(WSdeltaMbkg998->Integral()/WSdeltaMR18->Integral());
WSdeltaMR18->SetMaximum(WSdeltaMbkg998->GetMaximum());

RSmD0bkg1005->Add(RSmD0Sig,1.);
RSmD0bkg1235->Add(RSmD0bkg1005,1.);
RSmD0bkg998->Add(RSmD0bkg1235,1.);
RSmD0R18->Scale(RSmD0bkg998->Integral()/RSmD0R18->Integral());
RSmD0R18->SetMaximum(RSmD0bkg998->GetMaximum());

WSmD0bkg1005->Add(WSmD0Sig,1.);
WSmD0bkg1235->Add(WSmD0bkg1005,1.);
WSmD0bkg998->Add(WSmD0bkg1235,1.);
WSmD0R18->Scale(WSmD0bkg998->Integral()/WSmD0R18->Integral());
WSmD0bkg998->SetMinimum(0);
WSmD0bkg998->SetMaximum(WSmD0R18->GetMaximum());

TCanvas c_p1;
c_p1.cd();
p_K->Draw();
c_p1.SaveAs("p_K.eps");

TCanvas c_p2;
c_p2.cd();
p_pi->Draw();
c_p2.SaveAs("p_pi.eps");

TCanvas c_p3;
c_p3.cd();
p_pis->Draw();
c_p3.SaveAs("p_pis.eps");

TCanvas c1;
c1.Divide(2,1);
c1.cd(1);
d0lifeErrR18RS->Draw();
d0lifeErrbkg998RS->SetFillColor(2);d0lifeErrbkg998RS->SetFillStyle(1001);d0lifeErrbkg998RS->Draw("SAME");
d0lifeErrbkg1235RS->SetFillColor(3);d0lifeErrbkg1235RS->SetFillStyle(1001);d0lifeErrbkg1235RS->Draw("SAME");
d0lifeErrbkg1005RS->SetFillColor(4);d0lifeErrbkg1005RS->SetFillStyle(1001);d0lifeErrbkg1005RS->Draw("SAME");
d0lifeErrSigRS->SetFillColor(5);d0lifeErrSigRS->SetFillStyle(1001);d0lifeErrSigRS->Draw("SAME");
d0lifeErrR18RS->Draw("SAME");
errorlegRS.Draw();
c1.cd(2);
d0lifeErrR18WS->Draw();
d0lifeErrbkg998WS->SetFillColor(2);d0lifeErrbkg998WS->SetFillStyle(1001);d0lifeErrbkg998WS->Draw("SAME");
d0lifeErrbkg1235WS->SetFillColor(3);d0lifeErrbkg1235WS->SetFillStyle(1001);d0lifeErrbkg1235WS->Draw("SAME");
d0lifeErrbkg1005WS->SetFillColor(4);d0lifeErrbkg1005WS->SetFillStyle(1001);d0lifeErrbkg1005WS->Draw("SAME");
d0lifeErrSigWS->SetFillColor(5);d0lifeErrSigWS->SetFillStyle(1001);d0lifeErrSigWS->Draw("SAME");
d0lifeErrR18WS->Draw("SAME");
errorlegWS.Draw();
c1.SaveAs("Decaytime.eps");

//now do the lifetime error ratio

d0lifeErrR18RS->Divide(d0lifeErrbkg998RS);
d0lifeErrR18RS->SetTitle("");
TCanvas c1_1;
c1_1.cd();
d0lifeErrR18RS->Draw();
c1_1.SaveAs("Liferr_ratio.eps");

TCanvas c2;
c2.Divide(2,2);
c2.cd(1);
RSdeltaMbkg998->SetFillColor(28);RSdeltaMbkg998->SetFillStyle(1001);RSdeltaMbkg998->Draw("SAME");
RSdeltaMbkg1235->SetFillColor(30);RSdeltaMbkg1235->SetFillStyle(1001);RSdeltaMbkg1235->Draw("SAME");
RSdeltaMbkg1005->SetFillColor(41);RSdeltaMbkg1005->SetFillStyle(1001);RSdeltaMbkg1005->Draw("SAME");
RSdeltaMSig->SetFillColor(9);RSdeltaMSig->SetFillStyle(1001);RSdeltaMSig->Draw("SAME");
RSdeltaMR18->Draw("SAME E");
deltaMRSleg.Draw();
c2.cd(2);
WSdeltaMbkg998->SetFillColor(28);WSdeltaMbkg998->SetFillStyle(1001);WSdeltaMbkg998->Draw("SAME");
WSdeltaMbkg1235->SetFillColor(30);WSdeltaMbkg1235->SetFillStyle(1001);WSdeltaMbkg1235->Draw("SAME");
WSdeltaMbkg1005->SetFillColor(41);WSdeltaMbkg1005->SetFillStyle(1001);WSdeltaMbkg1005->Draw("SAME");
WSdeltaMSig->SetFillColor(9);WSdeltaMSig->SetFillStyle(1001);WSdeltaMSig->Draw("SAME");
WSdeltaMR18->Draw("SAME E");
deltaMWSleg.Draw();
c2.cd(3);
RSmD0bkg998->SetFillColor(28);RSmD0bkg998->SetFillStyle(1001);RSmD0bkg998->Draw("SAME");
RSmD0bkg1235->SetFillColor(30);RSmD0bkg1235->SetFillStyle(1001);RSmD0bkg1235->Draw("SAME");
RSmD0bkg1005->SetFillColor(41);RSmD0bkg1005->SetFillStyle(1001);RSmD0bkg1005->Draw("SAME");
RSmD0Sig->SetFillColor(9);RSmD0Sig->SetFillStyle(1001);RSmD0Sig->Draw("SAME");
RSmD0R18->Draw("SAME E");
mD0RSleg.Draw();
c2.cd(4);
WSmD0bkg998->SetFillColor(28);WSmD0bkg998->SetFillStyle(1001);WSmD0bkg998->Draw("SAME");
WSmD0bkg1235->SetFillColor(30);WSmD0bkg1235->SetFillStyle(1001);WSmD0bkg1235->Draw("SAME");
WSmD0bkg1005->SetFillColor(41);WSmD0bkg1005->SetFillStyle(1001);WSmD0bkg1005->Draw("SAME");
WSmD0Sig->SetFillColor(9);WSmD0Sig->SetFillStyle(1001);WSmD0Sig->Draw("SAME");
WSmD0R18->Draw("SAME E");
mD0WSleg.Draw();
c2.SaveAs("Massesplots.eps");

TCanvas tmpc1;
tmpc1.cd();
WSdeltaMbkg998->SetFillColor(28);WSdeltaMbkg998->SetFillStyle(1001);WSdeltaMbkg998->Draw("SAME");
WSdeltaMbkg1235->SetFillColor(30);WSdeltaMbkg1235->SetFillStyle(1001);WSdeltaMbkg1235->Draw("SAME");
WSdeltaMbkg1005->SetFillColor(41);WSdeltaMbkg1005->SetFillStyle(1001);WSdeltaMbkg1005->Draw("SAME");
WSdeltaMSig->SetFillColor(9);WSdeltaMSig->SetFillStyle(1001);WSdeltaMSig->Draw("SAME");
WSdeltaMR18->Draw("SAME E");
deltaMWSleg.Draw();
tmpc1.SaveAs("deltaMWS.eps");

TCanvas tmpc2;
tmpc2.cd();
WSmD0bkg998->SetFillColor(28);WSmD0bkg998->SetFillStyle(1001);WSmD0bkg998->Draw("SAME");
WSmD0bkg1235->SetFillColor(30);WSmD0bkg1235->SetFillStyle(1001);WSmD0bkg1235->Draw("SAME");
WSmD0bkg1005->SetFillColor(41);WSmD0bkg1005->SetFillStyle(1001);WSmD0bkg1005->Draw("SAME");
WSmD0Sig->SetFillColor(9);WSmD0Sig->SetFillStyle(1001);WSmD0Sig->Draw("SAME");
WSmD0R18->Draw("SAME E");
mD0WSleg.Draw();
tmpc2.SaveAs("mD0WS.eps");

return 0;
}
