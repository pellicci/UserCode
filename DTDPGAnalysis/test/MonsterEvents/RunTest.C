/*
 *=========================================================================
 *
 * DESCRIPTION: This macro provides an example on how to use the 
 *              MonsterEventsInspector class to read the monster events
 *              and correlate them with the CMS instantenous luminosity 
 *              to plot a few interesting plots for each wheel.
 *  DEVELOPERS: Isidro Gonzalez Caballero (U. Oviedo)
 *  
 *     UPDATES: [WHEN] - [WHO] - [WHAT]
 *=========================================================================
 */
{

  // Set general styles for plots
  gStyle->SetOptStat(11111111);
  gStyle->SetHistLineWidth(3);
  gStyle->SetHistFillColor(kBlue);


  // Load classes
  gROOT->LoadMacro("MonsterEventsInspector.C+");


  // Create a MonsterEventsInspector
  MonsterEventsInspector mei;


  // Read the luminosity file and store fills
  TFile* lfile = mei.ReadLumiFile();
  if (!lfile)
    return;


  // Create arrays of histograms (one per wheel)
  // + Number of monster events per luminosity bin
  TH1F* hInstLumi[5];
  // + Time between MEs with Beam
  TH1F* hDeltaTMEBeam[5];
  // + Time between MEs with no beam
  TH1F* hDeltaTMENoBeam[5];

  // + Initialize them
  for (unsigned int i = 0; i < 5; i++) {
    TString wheel = Form("YB%+i", i-2);
    hInstLumi[i] = new TH1F(Form("hInstLumi%i",i), 
			    Form("Number of Monster Events vs Lumi - %s", wheel.Data()),
			    150, 0, 150000);

    hDeltaTMEBeam[i]   = new TH1F(Form("hDeltaTMEBeam%i", i),
				  Form("Time between monster events in a fill - %s", wheel.Data()),
				  100, 0, 3600);  

    hDeltaTMENoBeam[i] = new TH1F(Form("hDeltaTMENoBeam%i", i),
				  Form("Time between monster events out of a fill - %s", wheel.Data()),
				  100, 0, 3600);
  }



  // Loop over wheels
  for (int w = 0; w < 5; w++) {

    // + Read MonsterEvents for this wheel
    int events = mei.ReadMonsterEvents(w-2);
    if (events == 0)
      return;
    
    
    bool isInBeam0 = false;
    TTimeStamp time0;
    // + Retrieve and fill histograms
    for (unsigned int i = 0; i < mei.GetNMonsterEvents(); i++) {
      MonsterEvent me = mei.GetMonsterEvent(i);
      
      //Calculate Delta between this event and the previous one
      time_t dt = mei.DeltaT(time0, me.EventTime);
      
      //Check if the monster event happened within a fill
      if (me.IsInBeam) {
	//cout << me << endl;
	hInstLumi[w]->Fill(me.InstLumi);
	
	//Fill only if both this and the previous event happend in a fill
	if (isInBeam0)
	  hDeltaTMEBeam[w]->Fill(dt);
      }
      else{
	if (!isInBeam0)
	  hDeltaTMENoBeam[w]->Fill(dt);
	
      }
      
      
      time0     = me.EventTime;
      isInBeam0 = me.IsInBeam;
    }
  }
  

  // Get 2012 luminosity distribution
  TH1F* hLumi2012 = mei.GetLumi2012();
  hLumi2012->SetMarkerColor(kRed);
  hLumi2012->SetMarkerStyle(20);



  // Plot everything
  TCanvas* cLumi = new TCanvas("Luminosity");
  cLumi->Divide(3,2);
  TH1F* hInstLumiAll = hInstLumi[0]->Clone("hInstLumiAll");
  hInstLumiAll->SetTitle("Number of Monster Events vs Lumi - All wheels");
  for (int w = 0; w < 5; w++) {
    if (w != 0)
      hInstLumiAll->Add(hInstLumi[w]);

    cLumi->cd(w+2);
    hInstLumi[w]->Draw();
    hInstLumi[w]->SetMaximum(150);
    hLumi2012->Draw("P, SAME");
  }
  cLumi->cd(1);
  hInstLumiAll->Draw();
  hLumi2012->Draw("P, SAME");


  TCanvas* deltaTB = new TCanvas("deltaTBeam");
  deltaTB->Divide(3,2);
  TH1F* hDeltaTMEBeamAll = hDeltaTMEBeam[0]->Clone("hDeltaTMEBeamAll");
  hDeltaTMEBeamAll->SetTitle("Time between monster events in a fill - All wheels");
  for (int w = 0; w < 5; w++) {
    if (w != 0)
      hDeltaTMEBeamAll->Add(hDeltaTMEBeam[w]);

    deltaTB->cd(w+2);
    gPad->SetLogy();
    hDeltaTMEBeam[w]->Draw();
  }
  deltaTB->cd(1);
  gPad->SetLogy();
  hDeltaTMEBeamAll->Draw();


  TCanvas* deltaTNB = new TCanvas("deltaTNoBeam");
  deltaTNB->Divide(3,2);
  TH1F* hDeltaTMENoBeamAll = hDeltaTMENoBeam[0]->Clone("hDeltaTMENoBeamAll");
  hDeltaTMENoBeamAll->SetTitle("Time between monster events out of a fill - All wheels");
  for (int w = 0; w < 5; w++) {
    if (w != 0)
      hDeltaTMENoBeamAll->Add(hDeltaTMENoBeam[w]);

    deltaTNB->cd(w+2);
    gPad->SetLogy();
    hDeltaTMENoBeam[w]->Draw();
  }
  deltaTNB->cd(1);
  gPad->SetLogy();
  hDeltaTMENoBeamAll->Draw();

}
