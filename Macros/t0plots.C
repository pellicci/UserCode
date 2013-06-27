{

TFile f("t0/t0TestMonitoring_112341_Vs_111873.root");
f.cd();

int ncount = 0;
float mean = 0.;

TH1F *htot = new TH1F("htot","htot",49,0.,49.5);

for(int wheel=-2; wheel<3; wheel++){

for(int icham=1; icham<5; icham++) {
 
  for(Int_t Sect=1; Sect<13; Sect++){

    for(int SL=1; SL<4; SL++){

      for(int layer=1; layer<5; layer++){

	if(icham == 4 && SL == 2) continue;
	if(wheel == 1 && Sect == 7 && icham == 3 && SL == 2) continue;
        if(wheel == -1 && Sect == 3) continue;
        if(wheel == 0 && Sect == 9) continue;
        if(wheel == 2 && Sect == 1 && icham == 2) continue;
        if(wheel == -2 && Sect == 8 && icham == 1 && SL == 2) continue;
        if(wheel == -2 && Sect == 8 && icham == 3 && SL == 2) continue;
        if(wheel == -1 && Sect == 8 && icham == 1 && SL == 2) continue;

string stringName;
stringstream theStream;
 theStream <<  "hDifference_W" << wheel << "_St" << icham << "_Sec" << Sect << "_SL" << SL << "_L" << layer;
theStream >> stringName;
TString Stringout = stringName.c_str();

 string stringDirFin;
 stringstream theStreamDirFin;
 theStreamDirFin <<  "/DQMData/DT/t0Validation/Wheel" << wheel << "/Station" << icham << "/Sector" << Sect << "/SuperLayer" << SL ;
 theStreamDirFin >> stringDirFin;

 //cout << stringDirFin.c_str() << endl;
 //cout << stringName.c_str() << endl;

 // gDirectory->cd(StringoutDirFin);
 f.cd(stringDirFin.c_str()); 
 gDirectory->pwd();

 //TH1F *hist = (TH1F*)f.Get(stringName.c_str());

 TH1F* hist =((TH1F*)gDirectory->Get(stringName.c_str()));

 //htot->Add(hist,1.);

 mean += hist->Integral();
 ncount++;

      }
    }
  }
}
}

cout << mean/ncount << endl;

htot->Draw();

}
