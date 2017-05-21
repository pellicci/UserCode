{

gROOT->SetStyle("Plain");

Float_t runnumber[8] = {109468,109721,110219,110409,110835,111873,112227,112341};

Float_t noise_u[8] = {226,476,153,406,357,135,156,179};

Float_t noise_m[8] = {24,19,20,26,20,23,22,19};

Float_t t0off[8] = {0.62,0.51,-0.48,2.18,-0.18,0.,-0.05,0.01};

Float_t runnumber_short[4] = {109146.,110440.,111047.,112237};
Float_t noise[4] = {38.,20.,21.,21.};

TGraph gr_u(8,runnumber,noise_u);
TGraph gr_m(8,runnumber,noise_m);
TGraph gr_off(8,runnumber,t0off);
TGraph gr_noise(4,runnumber_short,noise);

gr_u.GetXaxis()->SetTitle("Run number");
gr_u.GetYaxis()->SetTitle("Dead channels");

gr_m.GetXaxis()->SetTitle("Run number");
gr_m.GetYaxis()->SetTitle("Dead channels");

gr_off.GetXaxis()->SetTitle("Run number");
gr_off.GetYaxis()->SetTitle("t_{0} mean offset (ns)");

gr_noise.GetXaxis()->SetTitle("Run number");
gr_noise.GetYaxis()->SetTitle("Number of noisy channels");

gr_u.GetXaxis()->SetNoExponent(kTRUE);
gr_m.GetXaxis()->SetNoExponent(kTRUE);
gr_off.GetXaxis()->SetNoExponent(kTRUE);
gr_noise.GetXaxis()->SetNoExponent(kTRUE);

gr_off.GetYaxis()->SetRangeUser(-3.,3.);

gr_u.SetTitle("Dead channels (unmasked)");
gr_m.SetTitle("Dead channels (masked)");
gr_off.SetTitle("t_{0} mean offset");
gr_noise.SetTitle("Noisy channels");

gr_u.SetMarkerStyle(kCircle);
gr_m.SetMarkerStyle(kCircle);
gr_off.SetMarkerStyle(kCircle);
gr_noise.SetMarkerStyle(kCircle);

TCanvas c1;
c1.cd();
gr_u->Draw("ALP");
c1.SaveAs("noise_unmasked.gif");

TCanvas c2;
c2.cd();
gr_m->Draw("ALP");
c2.SaveAs("noise_masked.gif");

TCanvas c3;
c3.cd();
gr_off->Draw("ALP");
c3.SaveAs("offsett0.gif");

TCanvas c4;
c4.cd();
gr_noise->Draw("ALP");
c4.SaveAs("noise.gif");         

}
