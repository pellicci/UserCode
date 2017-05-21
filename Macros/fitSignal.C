{

  TFile fIn("SigNNLOShapes.root");
  fIn.cd();

  const float width_values[7] = {29.2,68.,123.,199.,304.,449.,647.};
  const string cstring_name[5] = {"C02","C04","C06","C08","C10"};

  RooRealVar m4l("m4l","m4l",600.,1400.);
  RooRealVar mass_H("mass_H","mass_H",100.,1200.);
  RooRealVar width_H("width_H","width_H",0.01,700.);

  //RooGenericPdf SignalTheor("SignalTheor","1./( pow(pow(@0,2)-pow(@1,2),2) + pow(@0,2)*pow(@2,2) )",RooArgSet(m4l,mass_H,width_H));
  //RooGenericPdf SignalTheor("SignalTheor","@0/( pow(pow(@0,2)-pow(@1,2),2) + pow(@0,4)*pow(@2,2)/pow(@1,2) )",RooArgSet(m4l,mass_H,width_H));

  RooGenericPdf SignalTheor("SignalTheor","1./( ( pow(pow(@0,2)-pow(@1,2),2) + pow(@1,4)*pow(@2,2)/pow(@0,2) ) * pow(@0,-3.1 + 7.2*(@1-400.)/1000.)  )",RooArgSet(m4l,mass_H,width_H));

  //RooGenericPdf SignalTheor("SignalTheor","@0/( pow(pow(@0,2)-pow(@1,2),2) + pow(@1,2)*pow(@2,2) )",RooArgSet(m4l,mass_H,width_H));

  //RooGenericPdf SignalTheor("SignalTheor","1./( ( pow(pow(@0,2)-pow(@1,2),2) + pow(@1,4)*pow(@2,2)/pow(@0,2) ) * pow(@0,0.3*@1/@0) )",RooArgSet(m4l,mass_H,width_H));

  TCanvas canv1;
  canv1.Divide(3,2);

  for(int i=0;i<7;i++){

    if(i>6)continue;

    const double mH = 400 + i*100;

    mass_H.setVal(mH);

    stringstream strs;
    strs << mH;
    string temp_mHstring = strs.str();

    for(int j=0;j<5;j++){

      const double c1 = 0.2 + j*0.2;

      width_H.setVal(width_values[i]*c1);

      mass_H.setVal(mH*sqrt(1-0.25*pow(width_values[i]*c1/mH,2)));
      width_H.setVal(width_values[i]*c1/sqrt(1-0.25*pow(width_values[i]*c1/mH,2)));

      mass_H.setConstant(kTRUE);
      //width_H.setConstant(kTRUE);

      cout << mass_H.getVal() << endl;
      cout << width_H.getVal() << endl;

      string histname = "mZZ_NNLO_H" + temp_mHstring + "_" + cstring_name[j];
      TH1F *hmass = (TH1F*)fIn.Get(histname.c_str());

      int rebin = 1;
      if(mH < 401.) rebin = 1;
      else if(mH < 601.) rebin = 5;
      else if(mH < 701.) rebin = 10;
      else rebin = 20;
      hmass->Rebin(rebin);

      RooDataHist hdata("hdata","hdata",RooArgList(m4l),hmass);

      SignalTheor.fitTo(hdata,RooFit::Minos(1),RooFit::Hesse(1));

      RooPlot *xframe = m4l.frame();
      hdata->plotOn(xframe);
      SignalTheor.plotOn(xframe);

      if(i == 6){
	canv1.cd(j+1);
	xframe->Draw();
      }

    }
  }

  canv1.SaveAs("prova.gif");


}
