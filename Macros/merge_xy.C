#define merge_xy_cxx
#include "merge_xy.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void merge_xy::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   //TH2D *h = new TH2D("h","h",100,-0.06,0.06,100,-0.06,0.06);
TH2D *h = new TH2D("h","h",100,-0.02,0.06,100,-0.04,0.04);
TH1D *hx = new TH1D("hx","hx",100,-0.06,0.06);
TH1D *hy = new TH1D("hy","hy",100,-0.06,0.06);
TH1D *r0 = new TH1D("r0","r0",100,0.,0.02);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      h->Fill(myx,myy);
      hx->Fill(myx);
      hy->Fill(myy);
      r0->Fill(myratio);

      //      cout << "For event : " << jentry << " values are -> x = " << myx << "    y = " << myy <<  "   and  r0 = " << myratio << endl;

      // if (Cut(ientry) < 0) continue;
   }

h->Scale(1/h->Integral());
hx->Scale(1/hx->Integral());
hy->Scale(1/hy->Integral());
r0->Scale(1/r0->Integral());

TFile merda("provina.root","RECREATE");
merda.mkdir("dir");
merda.cd("dir");
h->Write();
hx->Write();
hy->Write();
r0->Write();
merda.Close();

}
