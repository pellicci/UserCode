{

  gStyle->SetOptStat(0);

  //First scenario: standard
  TFile f1("/data2/p/pellicci/DPG/FailureScenarios/results/std_80percent.root");
  f1.cd();

  TTree *tree_std = (TTree*)f1.Get("SelectedTree");

  TH1F hZMass_std("hZMass_std","hZMass_std",60,60.,120.);
  TH1F hZPt_std("hZPt_std","hZPt_std",120,0.,120.);
  TH1F hZEta_std("hZEta_std","hZEta_std",50,-4.5,4.5);
  TH1F hZPhi_std("hZPhi_std","hZPhi_std",50,-3.14,3.14);
  TH1F hMu1Pt_std("hMu1Pt_std","hMu1Pt_std",140,0.,180.);
  TH1F hMu2Pt_std("hMu2Pt_std","hMu2Pt_std",130,0.,140.);
  TH1F hMu1Eta_std("hMu1Eta_std","hMu1Eta_std",50,-1.25,1.25);
  TH1F hMu2Eta_std("hMu2Eta_std","hMu2Eta_std",50,-1.25,1.25);
  TH1F hMu1Phi_std("hMu1Phi_std","hMu1Phi_std",50,-3.14,3.14);
  TH1F hMu2Phi_std("hMu2Phi_std","hMu2Phi_std",50,-3.14,3.14);

  //Second scenario: alternative
  TFile f2("/data2/p/pellicci/DPG/FailureScenarios/results/80percent.root");
  f2.cd();

  TTree *tree_alt = (TTree*)f2.Get("SelectedTree");

  TH1F hZMass_alt("hZMass_alt","hZMass_alt",60,60.,120.);
  TH1F hZPt_alt("hZPt_alt","hZPt_alt",120,0.,120.);
  TH1F hZEta_alt("hZEta_alt","hZEta_alt",50,-4.5,4.5);
  TH1F hZPhi_alt("hZPhi_alt","hZPhi_alt",50,-3.14,3.14);
  TH1F hMu1Pt_alt("hMu1Pt_alt","hMu1Pt_alt",140,0.,180.);
  TH1F hMu2Pt_alt("hMu2Pt_alt","hMu2Pt_alt",130,0.,140.);
  TH1F hMu1Eta_alt("hMu1Eta_alt","hMu1Eta_alt",50,-1.25,1.25);
  TH1F hMu2Eta_alt("hMu2Eta_alt","hMu2Eta_alt",50,-1.25,1.25);
  TH1F hMu1Phi_alt("hMu1Phi_alt","hMu1Phi_alt",50,-3.14,3.14);
  TH1F hMu2Phi_alt("hMu2Phi_alt","hMu2Phi_alt",50,-3.14,3.14);

  //Ratio between the two scenarios
  TH1F hZMass_diff("hZMass_diff","hZMass_diff",60,60.,120.);
  TH1F hZPt_diff("hZPt_diff","hZPt_diff",120,0.,120.);
  TH1F hZEta_diff("hZEta_diff","hZEta_diff",50,-4.5,4.5);
  TH1F hZPhi_diff("hZPhi_diff","hZPhi_diff",50,-3.14,3.14);
  TH1F hMu1Pt_diff("hMu1Pt_diff","hMu1Pt_diff",140,0.,180.);
  TH1F hMu2Pt_diff("hMu2Pt_diff","hMu2Pt_diff",130,0.,140.);
  TH1F hMu1Eta_diff("hMu1Eta_diff","hMu1Eta_diff",50,-1.25,1.25);
  TH1F hMu2Eta_diff("hMu2Eta_diff","hMu2Eta_diff",50,-1.25,1.25);
  TH1F hMu1Phi_diff("hMu1Phi_diff","hMu1Phi_diff",50,-3.14,3.14);
  TH1F hMu2Phi_diff("hMu2Phi_diff","hMu2Phi_diff",50,-3.14,3.14);

  //Fill the histograms from the trees
  Float_t ZMass  = 0.;
  Float_t ZPt    = 0.;
  Float_t ZEta   = 0.;
  Float_t ZPhi   = 0.;
  Float_t Mu1Pt  = 0.;
  Float_t Mu1Eta = 0.;
  Float_t Mu1Phi = 0.;
  Float_t Mu2Pt  = 0.;
  Float_t Mu2Eta = 0.;
  Float_t Mu2Phi = 0.;

  tree_std->SetBranchAddress("ZMass",&ZMass);
  tree_std->SetBranchAddress("ZPt",&ZPt);
  tree_std->SetBranchAddress("ZEta",&ZEta);
  tree_std->SetBranchAddress("ZPhi",&ZPhi);
  tree_std->SetBranchAddress("Mu1Pt",&Mu1Pt);
  tree_std->SetBranchAddress("Mu1Eta",&Mu1Eta);
  tree_std->SetBranchAddress("Mu1Phi",&Mu1Phi);
  tree_std->SetBranchAddress("Mu2Pt",&Mu2Pt);
  tree_std->SetBranchAddress("Mu2Eta",&Mu2Eta);
  tree_std->SetBranchAddress("Mu2Phi",&Mu2Phi);

  Long64_t nentries_std = tree_std->GetEntriesFast();
  for(Long64_t jentry=0; jentry<nentries_std;jentry++) {
    tree_std->GetEntry(jentry);

    hZMass_std.Fill(ZMass);
    hZPt_std.Fill(ZPt);
    hZEta_std.Fill(ZEta);
    hZPhi_std.Fill(ZPhi);
    
    if(fabs(Mu1Eta) < 1.25) hMu1Pt_std.Fill(Mu1Pt);
    hMu1Eta_std.Fill(Mu1Eta);
    if(fabs(Mu1Eta) < 1.25) hMu1Phi_std.Fill(Mu1Phi);
    if(fabs(Mu2Eta) < 1.25) hMu2Pt_std.Fill(Mu2Pt);
    hMu2Eta_std.Fill(Mu2Eta);
    if(fabs(Mu2Eta) < 1.25) hMu2Phi_std.Fill(Mu2Phi);


  }

  tree_alt->SetBranchAddress("ZMass",&ZMass);
  tree_alt->SetBranchAddress("ZPt",&ZPt);
  tree_alt->SetBranchAddress("ZEta",&ZEta);
  tree_alt->SetBranchAddress("ZPhi",&ZPhi);
  tree_alt->SetBranchAddress("Mu1Pt",&Mu1Pt);
  tree_alt->SetBranchAddress("Mu1Eta",&Mu1Eta);
  tree_alt->SetBranchAddress("Mu1Phi",&Mu1Phi);
  tree_alt->SetBranchAddress("Mu2Pt",&Mu2Pt);
  tree_alt->SetBranchAddress("Mu2Eta",&Mu2Eta);
  tree_alt->SetBranchAddress("Mu2Phi",&Mu2Phi);

  Long64_t nentries_alt = tree_alt->GetEntriesFast();
  for(Long64_t jentry=0; jentry<nentries_alt;jentry++) {
    tree_alt->GetEntry(jentry);

    hZMass_alt.Fill(ZMass);
    hZPt_alt.Fill(ZPt);
    hZEta_alt.Fill(ZEta);
    hZPhi_alt.Fill(ZPhi);

    if(fabs(Mu1Eta) < 1.25) hMu1Pt_alt.Fill(Mu1Pt);
    hMu1Eta_alt.Fill(Mu1Eta);
    if(fabs(Mu1Eta) < 1.25) hMu1Phi_alt.Fill(Mu1Phi);
    if(fabs(Mu2Eta) < 1.25) hMu2Pt_alt.Fill(Mu2Pt);
    hMu2Eta_alt.Fill(Mu2Eta);
    if(fabs(Mu2Eta) < 1.25) hMu2Phi_alt.Fill(Mu2Phi);
  }

  //ZMass comparison
  for(int i=0;i<hZMass_std->GetNbinsX();i++){
    const Float_t ZMass_num = hZMass_alt->GetBinContent(i);
    const Float_t ZMass_den = hZMass_std->GetBinContent(i);

    if(ZMass_den > 0.0000001) hZMass_diff->SetBinContent(i,ZMass_num/ZMass_den);
    else hZMass_diff->SetBinContent(i,1.);
  }

  //Pt comparison : Z
  for(int i=0;i<hZPt_std->GetNbinsX();i++){
    const Float_t ZPt_num = hZPt_alt->GetBinContent(i);
    const Float_t ZPt_den = hZPt_std->GetBinContent(i);

    if(ZPt_den > 0.000001) hZPt_diff->SetBinContent(i,ZPt_num/ZPt_den);
    else hZPt_diff->SetBinContent(i,1.);
  }

  //Z Eta comparison
  for(int i=0;i<hZEta_std->GetNbinsX();i++){
    const Float_t ZEta_num = hZEta_alt->GetBinContent(i);
    const Float_t ZEta_den = hZEta_std->GetBinContent(i);

    if(ZEta_den > 0.0000001) hZEta_diff->SetBinContent(i,ZEta_num/ZEta_den);
    else hZEta_diff->SetBinContent(i,1.);
  }

  //Z Phi comparison
  for(int i=0;i<hZPhi_std->GetNbinsX();i++){
    const Float_t ZPhi_num = hZPhi_alt->GetBinContent(i);
    const Float_t ZPhi_den = hZPhi_std->GetBinContent(i);

    if(ZPhi_den > 0.0000001) hZPhi_diff->SetBinContent(i,ZPhi_num/ZPhi_den);
    else hZPhi_diff->SetBinContent(i,1.);
  }

  //Pt comparison for first (highest pt) muons
  for(int i=0;i<hMu1Pt_std->GetNbinsX();i++){
    const Float_t Mu1Pt_num = hMu1Pt_alt->GetBinContent(i);
    const Float_t Mu1Pt_den = hMu1Pt_std->GetBinContent(i);

    if(Mu1Pt_den > 0.0001) hMu1Pt_diff->SetBinContent(i,Mu1Pt_num/Mu1Pt_den);
    else hMu1Pt_diff->SetBinContent(i,1.);

    //cout << Mu2Pt_num << "  "  << Mu2Pt_den << endl;
  }

  //Pt comparison for second (lower pt) muons
  for(int i=0;i<hMu2Pt_std->GetNbinsX();i++){
    const Float_t Mu2Pt_num = hMu2Pt_alt->GetBinContent(i);
    const Float_t Mu2Pt_den = hMu2Pt_std->GetBinContent(i);

    if(Mu2Pt_den > 0.0001) hMu2Pt_diff->SetBinContent(i,Mu2Pt_num/Mu2Pt_den);
    else hMu2Pt_diff->SetBinContent(i,1.);

    //cout << Mu2Pt_num << "  "  << Mu2Pt_den << endl;
  }
  
  //Eta comparison for muons
  for(int i=0;i<hMu1Eta_std->GetNbinsX();i++){
    const Float_t Mu1Eta_num = hMu1Eta_alt->GetBinContent(i);
    const Float_t Mu1Eta_den = hMu1Eta_std->GetBinContent(i);

    const Float_t Mu2Eta_num = hMu2Eta_alt->GetBinContent(i);
    const Float_t Mu2Eta_den = hMu2Eta_std->GetBinContent(i);

    if(Mu1Eta_den > 0.0001) hMu1Eta_diff->SetBinContent(i,Mu1Eta_num/Mu1Eta_den);
    else  hMu1Eta_diff->SetBinContent(i,1.);

    if(Mu2Eta_den > 0.0001) hMu2Eta_diff->SetBinContent(i,Mu2Eta_num/Mu2Eta_den);
    else  hMu2Eta_diff->SetBinContent(i,1.);

  }

  //Phi Comparison for muons
  for(int i=0;i<hMu1Phi_std->GetNbinsX();i++){
    const Float_t Mu1Phi_num = hMu1Phi_alt->GetBinContent(i);
    const Float_t Mu1Phi_den = hMu1Phi_std->GetBinContent(i);

    const Float_t Mu2Phi_num = hMu2Phi_alt->GetBinContent(i);
    const Float_t Mu2Phi_den = hMu2Phi_std->GetBinContent(i);

    if(Mu1Phi_den > 0.0001) hMu1Phi_diff->SetBinContent(i,Mu1Phi_num/Mu1Phi_den);
    else  hMu1Phi_diff->SetBinContent(i,1.);

    if(Mu2Phi_den > 0.0001) hMu2Phi_diff->SetBinContent(i,Mu2Phi_num/Mu2Phi_den);
    else  hMu2Phi_diff->SetBinContent(i,1.);

  }


  hZMass_diff->GetXaxis()->SetTitle("Z Mass [GeV/c^{2}]");
  hZPt_diff->GetXaxis()->SetTitle("Z p_{t} [GeV/c]");
  hZEta_diff->GetXaxis()->SetTitle("Z #eta");
  hZPhi_diff->GetXaxis()->SetTitle("Z #phi [rad]");
  hMu1Pt_diff->GetXaxis()->SetTitle("First muon p_{t} [GeV/c]");
  hMu2Pt_diff->GetXaxis()->SetTitle("Second muon p_{t} [GeV/c]");
  hMu1Eta_diff->GetXaxis()->SetTitle("First muon #eta");
  hMu2Eta_diff->GetXaxis()->SetTitle("Second muon #eta");
  hMu1Phi_diff->GetXaxis()->SetTitle("First muon #phi [rad]");
  hMu2Phi_diff->GetXaxis()->SetTitle("Second muon #phi [rad]");

  hZMass_diff->SetTitle("");
  hZPt_diff->SetTitle("");
  hZEta_diff->SetTitle("");
  hZPhi_diff->SetTitle("");
  hMu1Pt_diff->SetTitle("");
  hMu2Pt_diff->SetTitle("");
  hMu1Eta_diff->SetTitle("");
  hMu2Eta_diff->SetTitle("");
  hMu1Phi_diff->SetTitle("");
  hMu2Phi_diff->SetTitle("");

  hZMass_diff->GetYaxis()->SetRangeUser(0.7,1.);
  hZPt_diff->GetYaxis()->SetRangeUser(0.7,1.);
  hZEta_diff->GetYaxis()->SetRangeUser(0.7,1.);
  hZPhi_diff->GetYaxis()->SetRangeUser(0.7,1.);
  hMu1Pt_diff->GetYaxis()->SetRangeUser(0.3,1.1);
  hMu1Eta_diff->GetYaxis()->SetRangeUser(0.6,1.1);
  hMu1Phi_diff->GetYaxis()->SetRangeUser(0.6,1.1);
  hMu2Pt_diff->GetYaxis()->SetRangeUser(0.3,1.1);
  hMu2Eta_diff->GetYaxis()->SetRangeUser(0.6,1.1);
  hMu2Phi_diff->GetYaxis()->SetRangeUser(0.6,1.1);

  TCanvas c1;
  c1.cd();hZMass_diff->Draw();
  c1.SaveAs("plots/ZMass_diff.gif");

  TCanvas c2;
  c2.cd();hZPt_diff->Draw();
  c2.SaveAs("plots/ZPt_diff.gif");

  TCanvas c21;
  c21.cd();hZEta_diff->Draw();
  c21.SaveAs("plots/ZEta_diff.gif");

  TCanvas c22;
  c22.cd();hZPhi_diff->Draw();
  c22.SaveAs("plots/ZPhi_diff.gif");

  TCanvas c3;
  c3.cd();hMu1Pt_diff->Draw();
  c3.SaveAs("plots/Mu1Pt_diff.gif");

  TCanvas c4;
  c4.cd();hMu2Pt_diff->Draw();
  c4.SaveAs("plots/Mu2Pt_diff.gif");

  TCanvas c5;
  c5.cd();hMu1Eta_diff->Draw();
  c5.SaveAs("plots/Mu1Eta_diff.gif");

  TCanvas c6;
  c6.cd();hMu2Eta_diff->Draw();
  c6.SaveAs("plots/Mu2Eta_diff.gif");

  TCanvas c7;
  c7.cd();hMu1Phi_diff->Draw();
  c7.SaveAs("plots/Mu1Phi_diff.gif");

  TCanvas c8;
  c8.cd();hMu2Phi_diff->Draw();
  c8.SaveAs("plots/Mu2Phi_diff.gif");





}
