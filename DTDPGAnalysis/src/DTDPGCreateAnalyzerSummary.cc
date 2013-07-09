/*
 *  See header file for a description of this class.
 *
 *  $Date: 2013/07/04 17:16:09 $
 *  $Revision: 1.12 $
 *  \author G. Mila - INFN Torino
 * revised U.G. 2007/07/24
 * Modified M.C Fouz. 2008/04/22 
 *          Updated for version 200 
 *          include the run & sector number on gif files
 */


#include <UserCode/DTDPGAnalysis/src/DTDPGCreateAnalyzerSummary.h>
#include "UserCode/DTDPGAnalysis/src/DTROUtility.h"

// Framework
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/EventSetup.h>

// Geometry
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/DTGeometry/interface/DTLayer.h"
#include "Geometry/DTGeometry/interface/DTTopology.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>

#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGraph.h"
#include "TPostScript.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TFolder.h"
#include "TColor.h"
#include "TPaletteAxis.h"
#include "boost/filesystem.hpp"

using namespace edm;
using namespace std;
using namespace boost::filesystem;

DTDPGCreateAnalyzerSummary::DTDPGCreateAnalyzerSummary(const edm::ParameterSet& ps) : myFile(0){

  LogVerbatim("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Constructor";

  myParameters = ps;
  myRunNumber = ps.getUntrackedParameter<int>("runNumber",0);
  
}

DTDPGCreateAnalyzerSummary::~DTDPGCreateAnalyzerSummary(){

  edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Destructor ";

}


void DTDPGCreateAnalyzerSummary::beginJob(){

  edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: BeginJob";

}

void DTDPGCreateAnalyzerSummary::analyze(const edm::Event& e, const edm::EventSetup& context){
}


void DTDPGCreateAnalyzerSummary::endJob(){

  edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: endJob";

  myFile = new TFile(myParameters.getUntrackedParameter<string>("rootFileName", "DTEfficiencyTest.root").c_str(), "READ");

  char cMainFolder[30];sprintf(cMainFolder,"DQMData/Run %d", myRunNumber);
  TFolder * mfolder=(TFolder*)myFile->Get(cMainFolder);
  if(!mfolder) {
    throw cms::Exception("DTDPGCreateAnalyzerSummaryError") << "[DTDPGCreateAnalyzerSummary]: Folder = " << cMainFolder << " does not exist!!! Check the run number" << endl;     
  }
  
  myMainFolder.append(cMainFolder);
  myMainFolder.append("/DT/Run summary/DTOfflineAnalyzer/");

  string mainFold;
  mainFold.append(cMainFolder);
  mainFold.append("/DT/Run summary/");
  edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Creating summaries!";

  DTROUtility roUtil(myFile,mainFold);
  mySectors = roUtil.getSectorMap();

  if (myParameters.getUntrackedParameter<bool>("SummaryHistos", false))    { createSummaryPlots(); }
  if (myParameters.getUntrackedParameter<bool>("SummaryWheelHistos", false)) { createSummaryWheelPlots(); }
  if (myParameters.getUntrackedParameter<bool>("SummaryAllHistos", false))   { createSummaryAllPlots(); }

  if(myFile) {
    myFile->Close();
    delete myFile;
  }

}

void DTDPGCreateAnalyzerSummary::createGifFile(string fileName, int wh, int sec, string tag, TCanvas *canvas, bool isExtraFile) {

  stringstream gifBase;
  gifBase << "Run" << myRunNumber << "/Wheel" << showpos << wh << "/Sect" << noshowpos << setfill('0')<< setw(2) << sec;
  if (isExtraFile) { gifBase << "/ExtraPlots"; }

  try {
    create_directories(gifBase.str());
  } catch(const std::exception & ex) {
    throw cms::Exception("DTDPGCreateAnalyzerSummaryError")<< "[DTDPGCreateAnalyzerSummary]: Excepiton " << ex.what() << " thrown creating " << gifBase.str() << " directory" << endl;
  }
  
  stringstream gifTag; gifTag << "_r" << myRunNumber << "_W" << wh <<"_S" << sec;
  string gifFile = gifBase.str() + "/" + fileName + gifTag.str() + tag + ".gif";
  canvas->Update();
  canvas->Print(gifFile.c_str());

}

void DTDPGCreateAnalyzerSummary::createGifFile(string fileName, int wh, string tag, TCanvas *canvas, bool isExtraFile) {

  stringstream gifBase;
  gifBase << "Run" << myRunNumber << "/Wheel" << showpos << wh << noshowpos;
  if (isExtraFile) { gifBase << "/ExtraPlots"; }
  try {
    create_directories(gifBase.str());
  } catch(const std::exception & ex) {
    throw cms::Exception("DTDPGCreateAnalyzerSummaryError")<< "[DTDPGCreateAnalyzerSummary]: Excepiton " << ex.what() << " thrown creating " << gifBase.str() << " directory" << endl;
  }
  
  stringstream gifTag; gifTag << "_r" << myRunNumber << "_W" << wh;
  string gifFile = gifBase.str() + "/" + fileName +  gifTag.str() + tag + ".gif";
  canvas->Update();
  canvas->Print(gifFile.c_str());

}

void DTDPGCreateAnalyzerSummary::createGifFile(string fileName, string tag, TCanvas *canvas, bool isExtraFile) {

  stringstream gifBase;
  gifBase << "Run" << myRunNumber;
  if (isExtraFile) { gifBase << "/ExtraPlots"; }
  try {
    create_directories(gifBase.str());
  } catch(const std::exception & ex) {
    throw cms::Exception("DTDPGCreateAnalyzerSummaryError")<< "[DTDPGCreateAnalyzerSummary]: Excepiton " << ex.what() << " thrown creating " << gifBase.str() << " directory" << endl;
  }
  
  stringstream runTag; runTag << "_r" << myRunNumber;
  
  string gifFile = gifBase.str() + "/" + fileName + runTag.str() + tag + ".gif";
  canvas->Update();
  canvas->Print(gifFile.c_str());

}
  
void DTDPGCreateAnalyzerSummary::createSummaryPlots() {

  string Whname[5]={"Wm2","Wm1","W0","W1","W2"};

  gStyle->SetTitleW(0.55);
  gStyle->SetTitleH(0.13);
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.51);
  gStyle->SetTitleY(1.00);
  
  gStyle->SetOptStat(10);
  //gStyle->SetStatY(0.97);
  gStyle->SetStatY(0.89);
  gStyle->SetStatX(0.98);
  gStyle->SetStatW(0.35);
  //gStyle->SetStatH(0.45);
  gStyle->SetStatH(0.20);

  
  // Get histos to be plotted
  TH1F * first_to_paint;
  //TH1F * first_to_paint_MB[4];
  string SLname[3]={"Phi1","Theta","Phi2"};

  //int nbin;
  //float max, max1;

  TH2F *DigiXYS[5][14];
  TH1F *DigiXSecMBSlLayer[5][14][4][3][4];
  TH1F *TBoxSecMBSlLayer[5][14][4][3][4];
  TH1F *TBoxSegSecMBSlLayer[5][14][4][3][4];
  //TH1F *OccupMB[5][4];
  //TH1F *Correlated_trig_Bx[5][14][4][3];  // Not being used and in 62X gives erors for being set but not used
  //TH1F *hTrg_effnum_SecMB[5][14][4];  // Not being used and in 62X gives erors for being set but not used
  //TH1F *hTrg_effdenum_SecMB[5][14][4];  // Not being used and in 62X gives erors for being set but not used
  //TH1F *hPhiHL_SecMB[5][14][4];  // Not being used and in 62X gives erors for being set but not used
  //TH1F *TriggerMatrix[5][15];  // Not being used and in 62X gives erors for being set but not used
  TH1F * TriggerInclusive[5];

  std::map<int,std::vector<int> >::const_iterator whIt  = mySectors.begin();
  std::map<int,std::vector<int> >::const_iterator whEnd = mySectors.end();
  for(;whIt!=whEnd;++whIt) {
    int iw = (*whIt).first + 2;
    std::vector<int>::const_iterator secIt  = (*whIt).second.begin();
    std::vector<int>::const_iterator secEnd = (*whIt).second.end();
    for(;secIt!=secEnd;++secIt) {
      int isec = (*secIt);
 
     // Occupancies
      stringstream histoNameOcc; histoNameOcc << "hDigiXY_" << Whname[iw] << "_S" << isec;
      DigiXYS[iw][isec-1]=getHisto<TH2F>(histoNameOcc.str());
      for(int ich=1;ich<5;++ich){
	for(int isl=1;isl<4;++isl){
	  for(int il=1;il<5;++il){
	    // Create and fill individual layer occupancy plots from hDigiXY_S
	    stringstream histoNameOccup;  histoNameOccup  << "Occup_" << Whname[iw] << "_S" << isec << "_MB" << ich << "_SL" << isl << "_L" <<il;
	    stringstream histoTitleOccup; histoTitleOccup << "Occupancy  " << Whname[iw] << " S" << isec << " MB" << ich << " SL" << SLname[isl-1] << "L" << il;
	    DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]= new TH1F(histoNameOccup.str().c_str(),histoTitleOccup.str().c_str(),100, 0.,100.);
	    // TBoxes
	    stringstream histoNameTBox; histoNameTBox << "htime_" << Whname[iw] << "_S" << isec << "_MB" << ich << "_SL" << isl << "_L" << il;
	    TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]=getHisto<TH1F>(histoNameTBox.str());
	    stringstream histoNameTBoxSeg; histoNameTBoxSeg << "SegTimeBox_" << Whname[iw] << "_S" << isec << "_MB" << ich << "_SL" << isl << "_L" << il;
	    TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]=getHisto<TH1F>(histoNameTBoxSeg.str());
	  }
	}
	// Correlated Triggers
	for(int iq=4;iq<7;iq++){
	  stringstream histoNameTrQual; histoNameTrQual << "hTrigBX_" << Whname[iw] << "_S" << isec << "_MB" << ich << "_qual" << iq;
	  // Correlated_trig_Bx[iw][isec-1][ich-1][iq-4]=getHisto<TH1F>(histoNameTrQual.str()); //  Not being used and in 62X gives erors for being set but not used
	}
	// Trig Eff
	stringstream htag; htag << "_" << Whname[iw] << "_S" << isec << "_MB" << ich;
	stringstream heffden; heffden << "hTrg_effdenum" << htag.str();
	//hTrg_effdenum_SecMB[iw][isec-1][ich-1]=getHisto<TH1F>(heffden.str());  // Not being used and in 62X gives erors for being set but not used
	stringstream heffnum; heffnum  << "hTrg_effnum" << htag.str();
	// hTrg_effnum_SecMB[iw][isec-1][ich-1]=getHisto<TH1F>(heffnum.str()); //  Not being used and in 62X gives erors for being set but not used
	stringstream phihl; phihl << "hPhiHL" << htag.str();
	//hPhiHL_SecMB[iw][isec-1][ich-1]=getHisto<TH1F>(phihl.str());  // Not being used and in 62X gives erors for being set but not used

      }

      int nbx= DigiXYS[iw][isec-1]->GetNbinsX() ;

      for(int ich=1;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	  for(int il=1;il<5;il++){
	    int iby=(ich-1)*20+(isl-1)*4+il+1;
	    float totentr=0;
	    for(int ibx=1;ibx<nbx;ibx++){
	      float yval=DigiXYS[iw][isec-1]->GetBinContent(ibx,iby);
	      DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetBinContent(ibx,yval);
	      totentr+=yval; 
	    }
	    DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetEntries(totentr);
	  }
	}
      }

      // Trigger matrix
      stringstream histoNameTrMatrix; histoNameTrMatrix << "TriggerMatrix" << Whname[iw] << "_S" << isec;
      //TriggerMatrix[iw][isec-1]=getHisto<TH1F>(histoNameTrMatrix.str());  // Not being used and in 62X gives erors for being set but not used

    }
    // Trigger Inclusive
    stringstream histoNameTrInclusive; histoNameTrInclusive << "TriggerInclusive" << Whname[iw];
    TriggerInclusive[iw]=getHisto<TH1F>(histoNameTrInclusive.str());
    for (int isec=1;isec<13;++isec) {
      for (int ibin=1; ibin<5; ibin++) {
	stringstream hlabel; hlabel << "S" << isec << "MB" << ibin;
	TriggerInclusive[iw]->GetXaxis()->SetBinLabel((isec-1)*5+ibin,hlabel.str().c_str());
      } 
      TriggerInclusive[iw]->GetXaxis()->SetBinLabel(isec*5," ");
    }	
  }

   
  gStyle->SetTitleW(0.55);
  //gStyle->SetTitleH(0.13);
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleH(0.10);
  gStyle->SetTitleX(0.51);
  gStyle->SetTitleY(1.00);

  whIt  = mySectors.begin();
  whEnd = mySectors.end();
  for(;whIt!=whEnd;++whIt) {
    int iw = (*whIt).first + 2;
    std::vector<int>::const_iterator secIt  = (*whIt).second.begin();
    std::vector<int>::const_iterator secEnd = (*whIt).second.end();
    for(;secIt!=secEnd;++secIt) {
      int isec = (*secIt);

      //===================================================================================
      //    DIGI's occupancies
      //===================================================================================
      edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Drawing DIGI's occupancies per layer in 1 single page per Sector wh " 
					<< (iw-2) << " sec " << isec << endl;

      TCanvas *Digi = new TCanvas("Digi", "",201,81,999,699);  
      Digi->Divide(3,4) ;

      for(int ich=1;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	  bool dodraw=1;
	  if(ich==4 && isl==2)dodraw=0; // avoid ThetaMB4
	  if(dodraw){
	    // look first for the maximum bin entries
	    first_to_paint=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][0];
	    float nbmax=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][0]->GetMaximum();
	    for(int il=2;il<5;il++){
	      float nbmax0=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetMaximum();
	      if(nbmax0>nbmax){
		first_to_paint=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1];
		nbmax=nbmax0;
	      }
	      DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetLineColor(il);
	    }
	    stringstream htitle; htitle << "Occupancy W" << (iw-2) << " S" << isec << " MB" << ich << " SL" << SLname[isl-1];
	    first_to_paint->SetTitle(htitle.str().c_str());
	    int icpos=(ich-1)*3+isl;
	    Digi->cd(icpos) ;
	    Digi->cd(icpos)->SetLogy();
	    first_to_paint->GetYaxis()->SetLabelSize(0.07);
	    first_to_paint->GetXaxis()->SetLabelSize(0.07);
	    first_to_paint->Draw();
	    for(int il=1;il<5;il++){
	      DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->Draw("same");
	    }
	  }
	}
      }
      createGifFile("Occupancies_LogScale",iw-2,isec,"",Digi);
      delete Digi;

      //===================================================================================
      //    DIGI's occupancies
      //    now print 1 page per SL
      //===================================================================================
      edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Drawing DIGI's occupancies  per layer in 1 single page per SL wh " 
					<< (iw-2) << " sec " << isec << endl;
      int ichmin=1; if (isec==13|| isec==14)ichmin=4;
      for(int ich=ichmin;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	  bool dodraw=1;
	  if(ich==4 && isl==2)dodraw=0; // avoid ThetaMB4
	  if(dodraw){
	    TCanvas *DigiSL = new TCanvas("DigiSL", "",201,81,999,699);  
	    // look first for the maximum bin entries
	    first_to_paint=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][0];
	    float nbmax=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][0]->GetMaximum();
	    for(int il=2;il<5;il++){
	      float nbmax0=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetMaximum();
	      if(nbmax0>nbmax){
		first_to_paint=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1];
		nbmax=nbmax0;
	      }
	      DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetLineColor(il);
	    }
	    stringstream htitle;  htitle << "Occupancy W" << (iw-2) << " S" << isec << " MB" << ich << " SL" << SLname[isl-1];
	    first_to_paint->SetTitle(htitle.str().c_str());
	    first_to_paint->GetYaxis()->SetLabelSize(0.05);
	    first_to_paint->GetXaxis()->SetLabelSize(0.05);
	    first_to_paint->Draw();
	    for(int il=1;il<5;il++){
	      DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->Draw("same");
	    }
	     
	    stringstream fileTag; fileTag << "_MB" << ich << "_SL" << SLname[isl-1];
	    createGifFile("Occupancies",(iw-2),isec,fileTag.str(),DigiSL);
	    delete DigiSL;
	  }
	   
	}//end Loop Superlayers
      }//end Loop chambers

      //====================================================================================
      //    Time boxes: all in 1 single page (Layer granularity)
      //===================================================================================
      edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Drawing Time boxes per layer in 1 single page per Sector wh "
					<< (iw-2) << " sec " << isec << endl;
      TCanvas *Tboxes = new TCanvas("Tboxes", "",201,81,999,699);
      Tboxes->Divide(3,4) ;

      for(int ich=1;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	  bool dodraw=1;
	  if(ich==4 && isl==2)dodraw=0; // avoid ThetaMB4
	  if(dodraw){
	    // look first for the maximum bin entries
	    first_to_paint=TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][0];
	    float nbmax=TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][0]->GetMaximum();
	    for(int il=2;il<5;il++){
	      float nbmax0=TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetMaximum();
	      if(nbmax0>nbmax){
		first_to_paint=TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1];
		nbmax=nbmax0;
	      }
	      TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetLineColor(il);
	    }
	    stringstream htitle; htitle << "TimeBox W" << (iw-2) << " S" << isec << " MB" << ich << " SL" << SLname[isl-1];
	    first_to_paint->SetTitle(htitle.str().c_str());
	    int icpos=(ich-1)*3+isl;
	    Tboxes->cd(icpos) ;
	    first_to_paint->GetYaxis()->SetLabelSize(0.07);
	    first_to_paint->GetXaxis()->SetLabelSize(0.07);
	    first_to_paint->Draw();
	    for(int il=1;il<5;il++){
	      TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->Draw("same");
	    }
	  }
	}
      }
  
      createGifFile("Tboxes",(iw-2),isec,"",Tboxes);
      delete Tboxes;


      //====================================================================================
      //    Time boxes - From Segment hits: all in 1 single page (Layer granularity)
      //===================================================================================
      edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Drawing Time boxes (from Segments) per layer in 1 single page per Sector wh "
					<< (iw-2) << " sec " << isec << endl;
      TCanvas *TboxesSeg = new TCanvas("TboxesSeg", "",201,81,999,699);
      TboxesSeg->Divide(3,4) ;

      for(int ich=1;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	  bool dodraw=1;
	  if(ich==4 && isl==2)dodraw=0; // avoid ThetaMB4
	  if(dodraw){
	    // look first for the maximum bin entries
	    first_to_paint=TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][0];
	    float nbmax=TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][0]->GetMaximum();
	    for(int il=2;il<5;il++){
	      float nbmax0=TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetMaximum();
	      if(nbmax0>nbmax){
		first_to_paint=TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1];
		nbmax=nbmax0;
	      }
	      TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetLineColor(il);
	    }
	    stringstream htitle; htitle << "TimeBox W" << (iw-2) << " S" << isec << " MB" << ich << " SL" << SLname[isl-1];
	    first_to_paint->SetTitle(htitle.str().c_str());
	    int icpos=(ich-1)*3+isl;
	    TboxesSeg->cd(icpos) ;
	    first_to_paint->GetYaxis()->SetLabelSize(0.07);
	    first_to_paint->GetXaxis()->SetLabelSize(0.07);
	    first_to_paint->Draw();
	    for(int il=1;il<5;il++){
	      TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->Draw("same");
	    }
	  }
	}
      }
  
      createGifFile("TboxesSeg",(iw-2),isec,"",TboxesSeg);
      delete TboxesSeg;

      //===================================================================================
      //    Time boxes: 1 page per SL 
      //===================================================================================
      edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Drawing Time boxes per layer in 1 single page per SL wh " 
					<< (iw-2) << " sec " << isec << endl;
      ichmin=1; if (isec==13|| isec==14)ichmin=4;
      for(int ich=ichmin;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	   
	  bool dodraw=1;
	  if(ich==4 && isl==2)dodraw=0; // avoid ThetaMB4
	  if(dodraw){
	     TCanvas *TboxSL = new TCanvas("TboxSL", "",201,81,999,699);
	    // look first for the maximum bin entries
	    first_to_paint=TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][0];
	    float nbmax=TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][0]->GetMaximum();
	    for(int il=2;il<5;il++){
	      float nbmax0=TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetMaximum();
	      if(nbmax0>nbmax){
		first_to_paint=TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1];
		nbmax=nbmax0;
	      }
	      TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetLineColor(il);
	    }
	    stringstream htitle; htitle << "TimeBox W" << (iw-2) << " S" << isec << " MB" << ich << " SL" << SLname[isl-1];
	    first_to_paint->SetTitle(htitle.str().c_str());
	    first_to_paint->GetYaxis()->SetLabelSize(0.04);
	    first_to_paint->GetXaxis()->SetLabelSize(0.04);
	    first_to_paint->Draw();
	    for(int il=1;il<5;il++){
	      TBoxSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->Draw("same");
	    }
	     
	    stringstream fileTag; fileTag << "_MB" << ich << "_SL" << SLname[isl-1]; 
	    createGifFile("Tboxes",(iw-2),isec,fileTag.str(),TboxSL);
	    delete TboxSL;

	  }
	}//end loop SL      
      }//end loop chambers

      //===================================================================================
      //    Time boxes - From Segment Hits: 1 page per SL 
      //===================================================================================
      edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Drawing Time boxes (from Segments) per layer in 1 single page per SL wh " 
					<< (iw-2) << " sec " << isec << endl;
      ichmin=1; if (isec==13|| isec==14)ichmin=4;
      for(int ich=ichmin;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	   
	  bool dodraw=1;
	  if(ich==4 && isl==2)dodraw=0; // avoid ThetaMB4
	  if(dodraw){
	     TCanvas *TboxSegSL = new TCanvas("TboxSegSL", "",201,81,999,699);
	    // look first for the maximum bin entries
	    first_to_paint=TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][0];
	    float nbmax=TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][0]->GetMaximum();
	    for(int il=2;il<5;il++){
	      float nbmax0=TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetMaximum();
	      if(nbmax0>nbmax){
		first_to_paint=TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1];
		nbmax=nbmax0;
	      }
	      TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetLineColor(il);
	    }
	    stringstream htitle; htitle << "TimeBox W" << (iw-2) << " S" << isec << " MB" << ich << " SL" << SLname[isl-1];
	    first_to_paint->SetTitle(htitle.str().c_str());
	    first_to_paint->GetYaxis()->SetLabelSize(0.04);
	    first_to_paint->GetXaxis()->SetLabelSize(0.04);
	    first_to_paint->Draw();
	    for(int il=1;il<5;il++){
	      TBoxSegSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->Draw("same");
	    }
	     
	    stringstream fileTag; fileTag << "_MB" << ich << "_SL" << SLname[isl-1]; 
	    createGifFile("TboxesSeg",(iw-2),isec,fileTag.str(),TboxSegSL);
	    delete TboxSegSL;
	  }
	}//end loop SL      
      }//end loop chambers

    }
  }//end Loop on sectors/wheels

}

void DTDPGCreateAnalyzerSummary::createSummaryWheelPlots() {

  string Whname[5]={"Wm2","Wm1","W0","W1","W2"};
  string SLname[3]={"Phi1","Theta","Phi2"};
  
  TH1F *historun   = getHisto<TH1F>("RunInfo_RunNumbers");
  float TotEntries = 999999999.; // It was happen sometime that this histo was not created.
                                 // to protect from this problem
  if(historun != NULL) TotEntries = historun->GetEntries();
  else {
   for(int i=1;i<10;i++)cout << "WARNING!!!! histo RunInfo_RunNumbers was NOT FOUND " << endl;
  }
  
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.51);
  gStyle->SetTitleY(1.00);
  
  gStyle->SetPalette(1);   // set palette for 2D histos
  gStyle->SetTitleW(0.97);
  gStyle->SetTitleH(0.1);

  gStyle->SetOptFit(1);
  gStyle->SetOptStat(10);
  //gStyle->SetStatY(0.95); //92
  gStyle->SetStatY(0.89); //92
  gStyle->SetStatX(0.98);
  gStyle->SetStatW(0.35); //45
  //gStyle->SetStatH(0.45); //85
  gStyle->SetStatH(0.20); //85

  gStyle->SetTitleBorderSize(2);

  TH1F * first_to_paint;

  TH1F *BXSummary[5][4];
  for(int iw=0;iw<5;iw++){ // Loop in wheels
    for(int ic=1;ic<5;ic++){
      stringstream hname;  hname << "BX_mean_MB" << ic << "_W" << (iw-2); 
      stringstream htitle; htitle << "BX MeanValue (HH,HL) MB" << ic << " W" << (iw-2);
      BXSummary[iw][ic-1]= new TH1F(hname.str().c_str(),htitle.str().c_str(),12,1.,13.);
      for(int is=1;is<13;is++){
	stringstream xlab; xlab << "S" << is;
	BXSummary[iw][ic-1]->GetXaxis()->SetBinLabel(is,xlab.str().c_str()); 
      }
    }
  }

  

 for(int iw=0;iw<5;iw++){ // Loop in wheels   

   edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Processing Wheel " << iw-2 << endl; 
   //    Digi scatter plots
   TCanvas *DQM1 = new TCanvas("DQM1", "",201,81,999,699);
   DQM1->Divide(2,3) ;
   TCanvas *DQM1b = new TCanvas("DQM1b", "",201,81,999,699);
   DQM1b->Divide(2,3) ;
   TCanvas *DQM2 = new TCanvas("DQM2", "",201,81,999,699);
   DQM2->Divide(2,3) ;
   TCanvas *DQM2b = new TCanvas("DQM2b", "",201,81,999,699);
   DQM2b->Divide(2,3) ;

   TCanvas *ExtraS13S14 = new TCanvas("ExtraS13S14", "",201,81,1150,950);  
   ExtraS13S14->Divide(2,4);
   int iExtraPad=1; 
   
    TH2F *hDigiXYList[14];
   
    for(int isec=1;isec<15;isec++){
      stringstream histoname; histoname << "hDigiXY_" << Whname[iw] << "_S" << isec;
      for(int iih=1;iih<25;++iih)
      hDigiXYList[isec-1]= getHisto<TH2F>(histoname.str());
    }
   
    float Max=3000;
    float Max0[12];
    //float MaxMean=0;
    float MaxMean0=0;
    float MaxRMS0=0;
    //float MaxRMS=0;
    int Ns=0;
    for(int is=0;is<12; is++){
     if(hDigiXYList[is] != NULL)
     {
      Max0[is]=0;
      Max0[is]=hDigiXYList[is]->GetMaximum();
      if(Max0[is]>Max)Max=Max0[is];
      if(Max0[is]>0){ MaxMean0+=Max0[is]; MaxRMS0+=Max0[is]*Max0[is];Ns++;}
     }
    }


    for(int is=0;is<12; is++){
      if(is<6){DQM1->cd(is+1); DQM1->cd(is+1)->SetLogz();}
      else  {DQM2->cd(is-5); DQM2->cd(is-5)->SetLogz();}
     if(hDigiXYList[is] != NULL)
     {
      hDigiXYList[is]->SetStats(0);
      hDigiXYList[is]->SetMaximum(Max);
      hDigiXYList[is]->Draw("colz");
     }
    }

    createGifFile("Digi",(iw-2),"_S1-S6",DQM1);
    createGifFile("Digi",(iw-2),"_S7_S12",DQM2);
   
    // MB4 S13 & S14  
    for(int is=13;is<15; is++){
      ExtraS13S14->cd(iExtraPad);iExtraPad++;
      if(hDigiXYList[is-1] != NULL)
      {
       hDigiXYList[is-1]->SetStats(0);
       hDigiXYList[is-1]->SetMaximum(Max);
       hDigiXYList[is-1]->Draw("colz");
      }
    }

    if(Max>TotEntries){ // To cut noise cells and see better the
                        // occupancies on other cells 
      for(int is=0;is<12; is++){
  	  if(is<6){DQM1b->cd(is+1); DQM1b->cd(is+1)->SetLogz();}
	  else  {DQM2b->cd(is-5); DQM2b->cd(is-5)->SetLogz();}
        if(hDigiXYList[is] != NULL)
        {
	     hDigiXYList[is]->SetStats(0);
	     hDigiXYList[is]->SetMaximum(TotEntries);
	     hDigiXYList[is]->Draw("colz");
        }
      }
       
      createGifFile("Digi",(iw-2),"_S1-S6_b",DQM1b);
      createGifFile("Digi",(iw-2),"_S7-S12_b",DQM2b);
    }

    //    Ocupancies per SL    
    // Get histos to be plotted
    //int nbin;
    //float max, max1;
    //char sid1[50]; 
    
     // Occupancies
    TH2F *DigiXYS[5][14];
    for(int isec=1;isec<15;isec++){
      stringstream histoname; histoname << "hDigiXY_" << Whname[iw] << "_S" << isec;
      DigiXYS[iw][isec-1]=getHisto<TH2F>(histoname.str());
    }
    
    // Crea and fill individual layer occupancy plots from hDigiXY_S
    TH1F *DigiXSecMBSl[5][14][4][3];
    TH1F *DigiXSecMBSlLayer[5][14][4][3][4];
    for(int isec=1;isec<15;isec++){
      for(int ich=1;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	  stringstream hnamesl; hnamesl  << "Occup_" << Whname[iw] << "_S" << isec << "_MB" << ich <<" _SL" << isl;
	  stringstream htitlesl; htitlesl << "Occupancy  " << Whname[iw] << " S" << isec << " MB" << ich << " SL" << SLname[isl-1];
	  DigiXSecMBSl[iw][isec-1][ich-1][isl-1]= new TH1F(hnamesl.str().c_str(),htitlesl.str().c_str(),100, 0.,100.);
	  for(int il=1;il<5;il++){
	    stringstream hnamel;  hnamel  << hnamesl.str() << "_L" << il;
	    stringstream htitlel; htitlel << htitlesl.str()<< " L" << il;
	    DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]= new TH1F(hnamel.str().c_str(),htitlel.str().c_str(),100, 0.,100.);
	  }
	}
      }
    }
    
    for(int isec=1;isec<15;isec++){
     if(DigiXYS[iw][isec-1] != NULL)
     {
      int nbx= DigiXYS[iw][isec-1]->GetNbinsX() ;
      //int nby= DigiXYS[iw][isec-1]->GetNbinsY() ;
    
      for(int ich=1;ich<5;ich++){
	for(int isl=1;isl<4;isl++){
	  // Fill layer histos
	  for(int il=1;il<5;il++){
	    int iby=(ich-1)*20+(isl-1)*4+il+1;
	    float totentr=0;
	    for(int ibx=1;ibx<nbx;ibx++){
              float yval=DigiXYS[iw][isec-1]->GetBinContent(ibx,iby);
              DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetBinContent(ibx,yval);
              totentr+=yval; 
	    }
	    DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetEntries(totentr);
	  }
	  // Fill SL histos adding individual layer contents
	  for(int ibx=1;ibx<nbx;ibx++){
            float yval=0;
            for(int il=1;il<5;il++)
              yval+=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetBinContent(ibx);
	    
            DigiXSecMBSl[iw][isec-1][ich-1][isl-1]->SetBinContent(ibx,yval);
	  }
	}
      }
     }
    }// end loop sector

    TCanvas *Digi1 = new TCanvas("Digi1", "",201,81,1150,950);  
    TCanvas *Digi2 = new TCanvas("Digi2", "",201,81,1150,950);  
    TCanvas *Digi3 = new TCanvas("Digi3", "",201,81,1150,950);  
    Digi1->Divide(4,12,0.00001,0.00001); Digi2->Divide(4,12,0.00001,0.00001); Digi3->Divide(4,12,0.00001,0.00001);
    for(int isec=1;isec<13;isec++){ // Loop on sectors
      gStyle->SetTitleW(0.25);
      gStyle->SetTitleH(0.22);
      //gStyle->SetTitleX(0.72);
      //gStyle->SetTitleY(0.99);
      gStyle->SetTitleX(0.79);
      gStyle->SetTitleY(0.89);


    for(int ich=1;ich<5;ich++){
    for(int isl=1;isl<4;isl++){
     if(!(ich==4 && isl==2)){ // avoid ThetaMB4
	// look first for the maximum bin entries
	first_to_paint=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][0];
	float nbmax=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][0]->GetMaximum();
	for(int il=1;il<5;il++){
	    float nbmax0=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetMaximum();
	    if(nbmax0>nbmax){
	      first_to_paint=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1];
	      nbmax=nbmax0;
	    }
	    DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetLineColor(il);
	}
	stringstream htitle; htitle << "W" << (iw-2) << " S" << isec << " MB" << ich << " SL " << isl;
	first_to_paint->SetTitle(htitle.str().c_str());
	if(isec<5)           {int icpos=(ich-1)*3*4+(isl-1)*4+isec;     Digi1->cd(icpos) ; Digi1->cd(icpos)->SetBottomMargin(0.15) ; Digi1->cd(icpos)->SetLeftMargin(0.15) ; Digi1->cd(icpos)->SetLogy();}
	if(isec>4 && isec<9) {int icpos=(ich-1)*3*4+(isl-1)*4+(isec-4); Digi2->cd(icpos) ; Digi2->cd(icpos)->SetBottomMargin(0.15) ; Digi2->cd(icpos)->SetLeftMargin(0.15) ; Digi2->cd(icpos)->SetLogy();}
	if(isec>8 && isec<13){int icpos=(ich-1)*3*4+(isl-1)*4+(isec-8); Digi3->cd(icpos) ; Digi3->cd(icpos)->SetBottomMargin(0.15) ; Digi3->cd(icpos)->SetLeftMargin(0.15) ; Digi3->cd(icpos)->SetLogy();}
	first_to_paint->GetYaxis()->SetLabelSize(0.14);
	first_to_paint->GetXaxis()->SetLabelSize(0.14);
	first_to_paint->SetStats(0);
	first_to_paint->Draw();
	for(int il=1;il<5;il++)
	    DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->Draw("same");
     }
      
     if(ich==4 && isl !=2)
     {
       if(isec ==4 || isec ==10)
       {
        int isec_extra=13;
        if (isec ==10)isec_extra=14;
        ExtraS13S14->cd(iExtraPad); iExtraPad++;
	  DigiXSecMBSlLayer[iw][isec_extra-1][ich-1][isl-1][0]->Draw();
	  for(int il=2;il<5;il++)
        {
          DigiXSecMBSlLayer[iw][isec_extra-1][ich-1][isl-1][il-1]->SetLineColor(il);
          DigiXSecMBSlLayer[iw][isec_extra-1][ich-1][isl-1][il-1]->Draw("same");
        }
       }
     }

    }// End Loop in  SLs
    }// End Loop in Chambers 
    }// End Loop on sectors
    createGifFile("Occupancies_LogScale",(iw-2),"_S1-S4",Digi1);
    createGifFile("Occupancies_LogScale",(iw-2),"_S5-S8",Digi2);
    createGifFile("Occupancies_LogScale",(iw-2),"_S9-S12",Digi3);

  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.51);
  gStyle->SetTitleY(1.00);
  gStyle->SetTitleW(0.97);
  gStyle->SetTitleH(0.1);

  gStyle->SetStatH(0.20); 


    //    TimeBoxes        

    TCanvas *TB1 = new TCanvas("TB1", "",201,81,999,999);
    TCanvas *TB2 = new TCanvas("TB2", "",201,81,999,999);
    TB1->Divide(4,6,0.00001,0.00001) ;
    TB2->Divide(4,6,0.00001,0.00001) ;
    for (int ins=1; ins<13;ins++)
    for(int ic=1;ic<5;ic++){
      TH1F *hHisto[3];
      int nbmax=0;
      int nbmax0=0;


      for(int isl=1;isl<4;isl++){
	stringstream hname; hname << "htime_" << Whname[iw] << "_S" << ins << "_MB" << ic << "_SL" << isl;
        hHisto[isl-1]=getHisto<TH1F>(hname.str());
        if(hHisto[isl-1] !=NULL) hHisto[isl-1]->SetLineColor(isl);
      }

      first_to_paint = hHisto[0];
      if(first_to_paint !=NULL)nbmax=hHisto[0]->GetMaximum();

      for(int isl=2;isl<4;isl++){
       if(hHisto[isl-1] !=NULL) 
       {
        nbmax0=hHisto[isl-1]->GetMaximum();
        if(nbmax0>nbmax){
          nbmax=nbmax0;
          first_to_paint=hHisto[isl-1];
        }
       }
      }

      if(ins<7) 
      {
         int icpos=(ins-1)*4+ic;
         TB1->cd(icpos);
         TB1->cd(icpos)->SetLeftMargin(0.20);
      }
      else   
      {
         int icpos=(ins-7)*4+ic;
         TB2->cd(icpos);
         TB2->cd(icpos)->SetLeftMargin(0.20);
      }

      if(first_to_paint != NULL)
      {
        first_to_paint->GetYaxis()->SetLabelSize(0.08);
        first_to_paint->GetXaxis()->SetLabelSize(0.08);
        first_to_paint->GetXaxis()->SetLabelOffset(-0.025);
        first_to_paint->GetXaxis()->SetTitle("ns");
        first_to_paint->GetXaxis()->SetTitleSize(0.09);
        first_to_paint->GetXaxis()->SetTitleOffset(0.5);
        first_to_paint->GetXaxis()->SetNdivisions(308);
        //char htit[240];
        stringstream htitle; htitle << "TimeBox W" << iw-2 << " S" << ins << " MB"<< ic;
        first_to_paint->SetTitle(htitle.str().c_str());
        first_to_paint->Draw();
        for(int isl=1;isl<4;isl++) hHisto[isl-1]->Draw("same");
      }

      if(ic==4)
      {
       if(ins==4 || ins==10)
       {
        int isec_extra=13;
        if (ins ==10)isec_extra=14;
        TH1F *hHisto_extra[3];
        for(int isl=1;isl<4;isl++){
          stringstream hname; hname << "htime_" << Whname[iw] << "_S" << isec_extra << "_MB" << ic << "_SL" << isl;
          hHisto_extra[isl-1]=getHisto<TH1F>(hname.str());
          if(hHisto_extra[isl-1] != NULL) hHisto_extra[isl-1]->SetLineColor(isl);
        }
        ExtraS13S14->cd(iExtraPad); iExtraPad++;
        int nbmax=0; 
        first_to_paint=hHisto_extra[0];
        if(first_to_paint !=NULL)nbmax=hHisto[0]->GetMaximum();
        for(int isl=2;isl<4;isl++){
         if(hHisto[isl-1] !=NULL) 
         {
          int nbmax0=hHisto[isl-1]->GetMaximum();
          if(nbmax0>nbmax)
           { nbmax=nbmax0; first_to_paint=hHisto[isl-1];}
         }
        }

        if(first_to_paint!=NULL)
        {
          stringstream nhtitle; nhtitle << "TimeBox W" << iw-2 << " S" << isec_extra << " MB"<< ic;
          first_to_paint->SetTitle(nhtitle.str().c_str());
          first_to_paint->Draw();
          for(int isl=1;isl<4;isl++) hHisto_extra[isl-1]->Draw("same");
        }
       }
      }
        
    }// end loop on sectors & Chambers
    createGifFile("TBox_S1_S6",(iw-2),"",TB1);
    createGifFile("TBox_S7_S12",(iw-2),"",TB2);

    createGifFile("MB4S13S14Plots",(iw-2),"",ExtraS13S14);


    //    TimeBoxes - Segment hits

    TCanvas *TB1Seg = new TCanvas("TB1Seg", "",201,81,999,999);
    TCanvas *TB2Seg = new TCanvas("TB2Seg", "",201,81,999,999);
    TB1Seg->Divide(4,6,0.00001,0.00001) ;
    TB2Seg->Divide(4,6,0.00001,0.00001) ;
    for (int ins=1; ins<13;ins++)
    for(int ic=1;ic<5;ic++){
      TH1F *hHisto[3];
      int nbmax=0;
      int nbmax0=0;


      for(int isl=1;isl<4;isl++){
	stringstream hname; hname << "SegTimeBox_" << Whname[iw] << "_S" << ins << "_MB" << ic << "_SL" << isl;
        hHisto[isl-1]=getHisto<TH1F>(hname.str());
        if(hHisto[isl-1] !=NULL) hHisto[isl-1]->SetLineColor(isl);
      }

      first_to_paint = hHisto[0];
      if(first_to_paint !=NULL)nbmax=hHisto[0]->GetMaximum();

      for(int isl=2;isl<4;isl++){
       if(hHisto[isl-1] !=NULL) 
       {
        nbmax0=hHisto[isl-1]->GetMaximum();
        if(nbmax0>nbmax){
          nbmax=nbmax0;
          first_to_paint=hHisto[isl-1];
        }
       }
      }

      if(ins<7) 
      {
         int icpos=(ins-1)*4+ic;
         TB1Seg->cd(icpos);
         TB1Seg->cd(icpos)->SetLeftMargin(0.20);
      }
      else   
      {
         int icpos=(ins-7)*4+ic;
         TB2Seg->cd(icpos);
         TB2Seg->cd(icpos)->SetLeftMargin(0.20);
      }

      if(first_to_paint != NULL)
      {
        first_to_paint->GetYaxis()->SetLabelSize(0.08);
        first_to_paint->GetXaxis()->SetLabelSize(0.08);
        first_to_paint->GetXaxis()->SetLabelOffset(-0.025);
        first_to_paint->GetXaxis()->SetTitle("ns");
        first_to_paint->GetXaxis()->SetTitleSize(0.09);
        first_to_paint->GetXaxis()->SetTitleOffset(0.5);
        first_to_paint->GetXaxis()->SetNdivisions(308);
        //char htit[240];
        stringstream htitle; htitle << "TimeBox W" << iw-2 << " S" << ins << " MB"<< ic;
        first_to_paint->SetTitle(htitle.str().c_str());
        first_to_paint->Draw();
        for(int isl=1;isl<4;isl++) hHisto[isl-1]->Draw("same");
      }
        
    }// end loop on sectors & Chambers
    createGifFile("TBoxSeg_S1_S6",(iw-2),"",TB1Seg);
    createGifFile("TBoxSeg_S7_S12",(iw-2),"",TB2Seg);

    //    Hit Residuals        
    DQM1->Clear();
    DQM1->Divide(6,2) ;

    for(int ins=1;ins<13; ins++){
      TH1F *hHisto[4];
      DQM1->cd(ins);
      DQM1->cd(ins)->SetLeftMargin(0.20);

      int nbmax=0;
      int nbmax0=0;
          
      for(int ic=1;ic<5;ic++){
	stringstream hname; hname << "hResX_" << Whname[iw] << "_S" << ins << "_MB" << ic;
        hHisto[ic-1]= getHisto<TH1F>(hname.str());
        hHisto[ic-1]->SetLineColor(ic);
      }
      
      first_to_paint = hHisto[0];
      nbmax=hHisto[0]->GetMaximum();
     
      for(int ic=2;ic<5;ic++){
        nbmax0=hHisto[ic-1]->GetMaximum();
        if(nbmax0>nbmax){
          nbmax=nbmax0;
          first_to_paint=hHisto[ic-1];
        }
      }
      
      first_to_paint->GetYaxis()->SetLabelSize(0.08);
      first_to_paint->GetXaxis()->SetLabelSize(0.08);
      first_to_paint->GetXaxis()->SetLabelOffset(-0.025);
      first_to_paint->GetXaxis()->SetTitle("cm");
      first_to_paint->GetXaxis()->SetTitleSize(0.09);
      first_to_paint->GetXaxis()->SetTitleOffset(0.5);
      first_to_paint->GetXaxis()->SetNdivisions(308);
      stringstream htitle; htitle << "Hit residuals W" << (iw-2) << " S" << ins;
      first_to_paint->SetTitle(htitle.str().c_str());
      
      first_to_paint->Draw();
      for(int ic=1;ic<5;ic++)
	hHisto[ic-1]->Draw("same");

    }// end loop on sectors

    createGifFile("HitResiduals",(iw-2),"",DQM1);
    
    //    Angle Phi LOCAL
    DQM1->Clear();
    DQM1->Divide(6,2) ;

    for (int ins=1; ins<13;ins++){
      TH1F *hPhi[4];
      DQM1->cd(ins);
      DQM1->cd(ins)->SetLeftMargin(0.20);
      int nbmax=0;
      int nbmax0=0;
      
      for(int ic=1;ic<5;ic++){
	stringstream hname; hname << "hPhi_" << Whname[iw] << "_S" << ins << "_MB" << ic;
        hPhi[ic-1]=getHisto<TH1F>(hname.str());
        hPhi[ic-1]->SetLineColor(ic);
      }

      first_to_paint = hPhi[0];
      nbmax=hPhi[0]->GetMaximum();

      for(int ic=2;ic<5;ic++){
        nbmax0=hPhi[ic-1]->GetMaximum();
        if(nbmax0>nbmax){
          nbmax=nbmax0;
          first_to_paint=hPhi[ic-1];
        }
      }

      first_to_paint->GetYaxis()->SetLabelSize(0.08);
      first_to_paint->GetXaxis()->SetLabelSize(0.08);
      first_to_paint->GetXaxis()->SetLabelOffset(-0.025);
      first_to_paint->GetXaxis()->SetTitle("deg");
      first_to_paint->GetXaxis()->SetTitleSize(0.09);
      first_to_paint->GetXaxis()->SetTitleOffset(0.5);
      first_to_paint->GetXaxis()->SetNdivisions(308);
      stringstream htitle; htitle << "Phi local W" << (iw-2) << " S" << ins;
      first_to_paint->SetTitle(htitle.str().c_str());
 
      first_to_paint->Draw();
      for(int ic=1;ic<5;ic++) hPhi[ic-1]->Draw( "same");

    }// end loop on sectors


    createGifFile("PhiLocal",(iw-2),"",DQM1);

    //    STA Digis              
    DQM1->Clear();
    
    stringstream hnameSTADigi; hnameSTADigi << "hHitsPosXYSA_" << Whname[iw];

    // STA Plots created only on demand they could not exist 
    TH1F *hXYHisto=force_getHisto<TH1F>(hnameSTADigi.str());;
    if(hXYHisto)
    {
      hXYHisto->SetStats(0);
      hXYHisto->Draw("colz");

      createGifFile("STADigi",(iw-2),"",DQM1);
    }
    else 
       edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: STA histo " 
            << hnameSTADigi.str() << " not present, skiping STADigi gif file" << endl;


    //    STA Phi Hits     
    TCanvas *DQM6 = new TCanvas("DQM6", "",301,81,999,699); // open a large canvas
    TH1F *hnHitDT= getHisto<TH1F>("hnHitDT");
    //int hh=0;
    if(hnHitDT != NULL)
    {
       Float_t Nevents = hnHitDT->GetEntries();
       edm::LogVerbatim ("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]: Total nr. of triggers:" << Nevents << endl;
       
       TH1F *hPhiHisto[4];
       TH1F *heff[4];
       
       bool doSTAPhiHits=false;
       //float ymax = 0.1;
       float ymax = 0.0;
       for(int ic=1;ic<5;ic++){
         stringstream hname1, hname2, htitle;
       
         hname1 << "hPhiHit_" << Whname[iw] << "_MB" << ic;
         // STA Plots created only on demand they could not exist 
         hPhiHisto[ic-1]=force_getHisto<TH1F>(hname1.str());
         
         if(hPhiHisto[ic-1])
         {
           doSTAPhiHits=true;
           hname2 << "heff" << ic;
           heff[ic-1] =(TH1F*) hPhiHisto[ic-1]->Clone(hname2.str().c_str());
           heff[ic-1]->Add(heff[ic-1],heff[ic-1],0.5/Nevents,0.5/Nevents);
           
           float nbmax=heff[ic-1]->GetMaximum();
           if(nbmax>ymax)ymax=nbmax;
           heff[ic-1]->SetStats(0);
           heff[ic-1]->SetLineColor(ic);
           htitle << "Phi of ass. hit, W" << (iw-2);
           heff[0]->SetTitle(htitle.str().c_str());
         }
         
       }
       ymax=ymax*1.1;
       for(int ic=1;ic<5;ic++){
         if(hPhiHisto[ic-1])
         {
           heff[ic-1]->SetMaximum(ymax);
           if(ic==1)heff[ic-1]->Draw();
           else   heff[ic-1]->Draw("same");
         }
       }

       TLine *l[16];
       l[0] = new TLine(-165, 0, -165, ymax); l[0]->Draw();
       l[1] = new TLine(-135, 0, -135, ymax); l[1]->Draw();
       l[2] = new TLine(-105, 0, -105, ymax); l[2]->Draw();
       l[3] = new TLine( -75, 0,  -75, ymax); l[3]->Draw();
       l[4] = new TLine( -45, 0,  -45, ymax); l[4]->Draw();
       l[5] = new TLine( -15, 0,  -15, ymax); l[5]->Draw();
       l[6] = new TLine(  15, 0,   15, ymax); l[6]->Draw();
       l[7] = new TLine(  45, 0,   45, ymax); l[7]->Draw();
       l[8] = new TLine(  75, 0,   75, ymax); l[8]->Draw();
       l[9] = new TLine( 105, 0,  105, ymax); l[9]->Draw();
       l[10] = new TLine( 135, 0,  135, ymax); l[10]->Draw();
       l[11] = new TLine( 165, 0,  165, ymax); l[11]->Draw();
       
       l[12] = new TLine( -40, 0.8*ymax,  -20, 0.8*ymax); //l->Draw();
       l[12]->SetLineColor(1);
       l[12]->Draw();
       TPaveLabel * box [4];
       box[0] = new TPaveLabel(-10,0.8*ymax,5,0.85*ymax,"MB1");
       box[0]->Draw();
       
       l[13] = new TLine( -40, 0.7*ymax,  -20, 0.7*ymax); //l->Draw();
       l[13]->SetLineColor(2);
       l[13]->Draw();
       box[1] = new TPaveLabel(-10,0.7*ymax,5,0.75*ymax,"MB2");
       box[1]->Draw();
       
       l[14] = new TLine( -40, 0.6*ymax,  -20, 0.6*ymax); //l->Draw();
       l[14]->SetLineColor(3);
       l[14]->Draw();
       box[2] = new TPaveLabel(-10,0.6*ymax,5,0.65*ymax,"MB3");
       box[2]->Draw();
       
       l[15] = new TLine( -40, 0.5*ymax,  -20, 0.5*ymax); //l->Draw();
       l[15]->SetLineColor(4);
       l[15]->Draw();
       box[3] = new TPaveLabel(-10,0.5*ymax,5,0.55*ymax,"MB4");
       box[3]->Draw();
       
       if(doSTAPhiHits) createGifFile("STAPhiHits",(iw-2),"",DQM6);
       
       for (int i=0;i<16;++i) delete l[i];
       for (int i=0;i<4;++i) delete box[i];
    }

    //    STA Hits     
    DQM1->Clear();
    DQM1->Divide(6,2) ;

    TH1F *hNassList[12];

    for(int isec=1;isec<13;isec++){
      stringstream histoname; histoname << "hNhass_" << Whname[iw] << "_S" << isec;
      hNassList[isec-1]=force_getHisto<TH1F>(histoname.str());
    }


    bool doSTAHits=false;
    for(int is=0;is<12;is++){
     if(hNassList[is])
     {
      doSTAHits=true;
      hNassList[is]->GetYaxis()->SetLabelSize(0.08);
      hNassList[is]->GetXaxis()->SetNdivisions(308);
      hNassList[is]->GetXaxis()->SetLabelSize(0.08);
      hNassList[is]->GetXaxis()->SetLabelOffset(-0.025);
      hNassList[is]->GetXaxis()->SetTitle("# hits");
      hNassList[is]->GetXaxis()->SetTitleSize(0.01);
      hNassList[is]->GetXaxis()->SetTitleOffset(0.5);
      
      DQM1->cd(is+1);
      DQM1->cd(is+1)->SetLeftMargin(0.20);
      hNassList[is]->SetStats(1);
      hNassList[is]->Draw();
     }
    }

    if(doSTAHits) createGifFile("STAHits",(iw-2),"",DQM1);


    //    Segment Hits     
    DQM2->Clear();
    DQM2->Divide(6,2);
    gStyle->SetStatX(0.6);
    gStyle->SetStatY(0.88);
    gStyle->SetStatW(0.40);
    gStyle->SetStatH(0.20);


    TH1F *hNhits[12][4];
    for (int ins=1; ins<13;ins++){
      DQM2->cd(ins);
      DQM2->cd(ins)->SetLeftMargin(0.20);
      int nbmax=0;
      int nbmax0=0;
      
      for(int ic=1;ic<5;ic++){
	stringstream hname; hname << "hNhits_" << Whname[iw] << "_S" << ins << "_MB" << ic;
	hNhits[ins-1][ic-1]= getHisto<TH1F>(hname.str());
	hNhits[ins-1][ic-1]->SetLineColor(ic);
      }

      first_to_paint= hNhits[ins-1][0];
      nbmax=hNhits[ins-1][0]->GetMaximum();

      for(int ic=2;ic<5;ic++){
	nbmax0=hNhits[ins-1][ic-1]->GetMaximum();
	if(nbmax0>nbmax){
	  nbmax=nbmax0;
	  first_to_paint=hNhits[ins-1][ic-1];
	}
      }

      first_to_paint->GetYaxis()->SetLabelSize(0.08);
      first_to_paint->GetXaxis()->SetLabelSize(0.08);
      first_to_paint->GetXaxis()->SetLabelOffset(-0.025);
      first_to_paint->GetXaxis()->SetTitle("#hits");
      first_to_paint->GetXaxis()->SetTitleSize(0.09);
      first_to_paint->GetXaxis()->SetTitleOffset(0.5);
      first_to_paint->GetXaxis()->SetNdivisions(308);
      stringstream htitle; htitle << "# hits in seg W" << (iw-2) << " S" << ins;
      first_to_paint->SetTitle(htitle.str().c_str());

      first_to_paint->Draw();
      for(int ic=1;ic<5;ic++) hNhits[ins-1][ic-1]->Draw( "same");

    }// end loop on sectors


    createGifFile("SegHits",(iw-2),"",DQM2);



  gStyle->SetStatY(0.89);
  gStyle->SetStatX(0.98);
  gStyle->SetStatW(0.40);
  gStyle->SetStatH(0.20); 


    //    Segment Hits     
    DQM1->Clear();
    DQM1->Divide(6,2);
    TH1F * hNsegsList[12];
    for(int is=0;is<12;is++){
      stringstream hname; hname << "hNsegs_" << Whname[iw] << "_S" <<is+1;
      hNsegsList[is]= getHisto<TH1F>(hname.str());
      hNsegsList[is]->GetXaxis()->SetTitle("# Segments");
    }
     
    for(int is=0;is<12;is++){
      DQM1->cd(is+1);
      DQM1->cd(is+1)->SetLeftMargin(0.20);
      hNsegsList[is]->GetYaxis()->SetLabelSize(0.08);
      hNsegsList[is]->GetXaxis()->SetNdivisions(308);
      hNsegsList[is]->GetXaxis()->SetLabelSize(0.08);
      hNsegsList[is]->GetXaxis()->SetLabelOffset(-0.025);
      hNsegsList[is]->GetXaxis()->SetTitleSize(0.09);
      hNsegsList[is]->GetXaxis()->SetTitleOffset(0.5);
      hNsegsList[is]->SetStats(1);
      hNsegsList[is]->GetXaxis()->SetRangeUser(1.,10.);
      hNsegsList[is]->Draw();
    }
    
    createGifFile("Segments",(iw-2),"",DQM1);

    //    TMAX
    

    gStyle->SetOptStat(10);
    //gStyle->SetStatY(0.95);
    gStyle->SetStatY(0.89);
    gStyle->SetStatX(0.98);
    gStyle->SetStatW(0.35);
    gStyle->SetStatH(0.45);

    TCanvas *DQM11 = new TCanvas("DQM11", "1",101,81,999,699); 
    TCanvas *DQM12 = new TCanvas("DQM12", "2",101,81,999,699); 
    TCanvas *DQM13 = new TCanvas("DQM13", "3",101,81,999,699); 
    TCanvas *DQM14 = new TCanvas("DQM14", "4",101,81,999,699); 
    DQM11->Divide(4,3) ;
    DQM12->Divide(4,3) ;
    DQM13->Divide(4,3) ;
    DQM14->Divide(4,3) ;


    for (int ins=1; ins<13;ins++){
      TH1F *hHisto[2];
      for(int ic=1;ic<5;ic++){


	stringstream hname; hname << "htmax_" << Whname[iw] << "_S" << ins << "_MB" << ic;
	hHisto[0]= getHisto<TH1F>(hname.str()+"_SL1");
	hHisto[1]= getHisto<TH1F>(hname.str()+"_SL3");

	if(ins<4){
	  int ipos=(ins-1)*4+ic;
	  DQM11->cd(ipos);
	}
	if(ins>3 && ins<7){
	  int ipos=(ins-4)*4+ic;
	  DQM12->cd(ipos);
	}
	if(ins>6 && ins<10){
	  int ipos=(ins-7)*4+ic;
	  DQM13->cd(ipos);
	}
	if(ins>9){
         int ipos=(ins-10)*4+ic;
         DQM14->cd(ipos);
	}

	hHisto[0]->SetStats(1);
	gStyle->SetOptFit(1);
	hHisto[0]->Draw();
	if(hHisto[0]->GetEntries()>50) // Problems on version 31X when no entries or few entries
	try {
	  hHisto[0]->Fit("gaus","Q");
	  hHisto[0]->Draw("same");
	} catch(const cms::Exception&) {
	  edm::LogError("DTDPGSummary") << "[DTDPGCreateAnalyzerSummary]:  Error fitting " << hname.str() << "_SL1";
	}
	hHisto[1]->SetLineColor(2);
	hHisto[1]->Draw("same");
      }// end loop on chambers
    }// end loop on sectors

    createGifFile("TMax",(iw-2),"S1-S3",DQM11,true);
    createGifFile("TMax",(iw-2),"S4-S6",DQM12,true);
    createGifFile("TMax",(iw-2),"S7-S9",DQM13,true);
    createGifFile("TMax",(iw-2),"S10-S12",DQM14,true);

     gStyle->SetOptStat(10);
     //gStyle->SetStatY(0.95); //92
     gStyle->SetStatY(0.89); //92
     gStyle->SetStatX(0.98);
     gStyle->SetStatW(0.35); //45
     gStyle->SetStatH(0.45); //85

    //    Phi-Trig Efficiency
    TCanvas *Eff = new TCanvas("Eff", "",201,81,999,699);
    TH1F *hHisto[4];
    TH1F *hHistoTr[4];
    TH1F *heffx[4];
    for(int ic=1;ic<5;ic++)
    {
      stringstream hname1; hname1 << "hPhiGlob_" << Whname[iw] << "_MB" << ic;
      hHisto[ic-1]= getHisto<TH1F>(hname1.str());

      stringstream hname2; hname2 << "heff" << ic <<"x";
      heffx[ic-1] =(TH1F*) hHisto[ic-1]->Clone(hname2.str().c_str());
      heffx[ic-1]->SetLineColor(ic);
      
      stringstream hname3; hname3 << "hPhiTrigg_" << Whname[iw] << "_MB" << ic;
      hHistoTr[ic-1]= getHisto<TH1F>(hname3.str());
      heffx[ic-1]->Divide(hHistoTr[ic-1],hHisto[ic-1],1.0,1.0);
      
      for (int i = 0; i <= heffx[ic-1]->GetNbinsX()+1; i++ ) {
        Float_t tot   = hHisto[ic-1]->GetBinContent(i) ;
        Float_t tot_e = hHisto[ic-1]->GetBinError(i);
        Float_t eff = heffx[ic-1]->GetBinContent(i) ;
        Float_t Err = 0.;
        if (tot > 0) Err = tot_e / tot * sqrt( eff* (1-eff) );
	//    if (eff == 1. || isnan(Err) || !isfinite(Err) ) Err=1.e-3;
        heffx[ic-1]->SetBinError(i, Err);
      }
      heffx[ic-1]->SetStats(0);
      heffx[ic-1]->SetMaximum(1);
      stringstream htitle; htitle << "Phi-Trigger Eff W" << iw-2;
      heffx[0]->SetTitle(htitle.str().c_str());
      heffx[0]->SetMaximum(1.02);
      
      if(ic==1)heffx[ic-1]->Draw();
      else heffx[ic-1]->Draw("same");
    }

    float ymax = 1.;
    TLine *l[16];
    l[0] = new TLine(-165, 0, -165, ymax); l[0]->Draw();
    l[1] = new TLine(-135, 0, -135, ymax); l[1]->Draw();
    l[2] = new TLine(-105, 0, -105, ymax); l[2]->Draw();
    l[3] = new TLine( -75, 0,  -75, ymax); l[3]->Draw();
    l[4] = new TLine( -45, 0,  -45, ymax); l[4]->Draw();
    l[5] = new TLine( -15, 0,  -15, ymax); l[5]->Draw();
    l[6] = new TLine(  15, 0,   15, ymax); l[6]->Draw();
    l[7] = new TLine(  45, 0,   45, ymax); l[7]->Draw();
    l[8] = new TLine(  75, 0,   75, ymax); l[8]->Draw();
    l[9] = new TLine( 105, 0,  105, ymax); l[9]->Draw();
    l[10] = new TLine( 135, 0,  135, ymax); l[10]->Draw();
    l[11] = new TLine( 165, 0,  165, ymax); l[11]->Draw();
    
    createGifFile("TrigEff",(iw-2),"",Eff,true);

//     for (int i=0;i<12;++i) delete l[i];

    delete TB1; 
    delete TB2; 
    delete TB1Seg; 
    delete TB2Seg; 
    delete DQM1;
    delete DQM2;
    delete DQM1b;
    delete DQM2b;
    delete Digi1;
    delete Digi2;
    delete Digi3;
    delete DQM6;
    
    delete DQM11;
    delete DQM12;
    delete DQM13;
    delete DQM14;

    delete Eff;
    delete ExtraS13S14;

 }// END loop in wheels

    
}
  

void DTDPGCreateAnalyzerSummary::createSummaryAllPlots() {
  string Whname[5]={"Wm2","Wm1","W0","W1","W2"};

  gStyle->SetTitleW(0.55);
  gStyle->SetTitleH(0.13);
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.51);
  gStyle->SetTitleY(1.00);
  
  gStyle->SetOptStat(10);
  //gStyle->SetStatY(0.97);
  gStyle->SetStatY(0.82);
  gStyle->SetStatX(0.98);
  gStyle->SetStatW(0.35);
  //gStyle->SetStatH(0.45);
  gStyle->SetStatH(0.20); 

  //Change standard palette colors
  const Int_t NRGBs = 5;
  //const Int_t NCont = 255;
  const Int_t NCont = 155;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.99, 0.40, 0.00, 0.80, 0.95 };
  Double_t green[NRGBs] = { 0.99, 0.40, 0.40, 0.10, 0.00 };
  Double_t blue[NRGBs]  = { 0.20, 0.00, 0.90, 0.10, 0.00 };
  // It needs to be initialize if not root gives a warning and cmssw an error and
  // the program stops
  TColor::InitializeColors();
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  //gStyle->SetNumberContours(NCont);

  // Get histos to be plotted
  TH1F * first_to_paint;
  TH1F * first_to_paint_MB[4];
  string SLname[3]={"Phi1","Theta","Phi2"};

  TH1F *DigiXSecMBSlLayer[5][14][4][3][4];

  for(int iw=0;iw<5;++iw)
  for(int isec=1;isec<15;++isec)
  for(int ich=1;ich<5;++ich)
  for(int isl=1;isl<4;++isl)
  for(int il=1;il<5;++il){
      // Create individual layer occupancy plots from hDigiXY_S
      stringstream histoNameOccup;  histoNameOccup  << "Occup_" << Whname[iw] << "_S" << isec << "_MB" << ich << "_SL" << isl << "_L" <<il;
      stringstream histoTitleOccup; histoTitleOccup << "Occupancy  " << Whname[iw] << " S" << isec << " MB" << ich << " SL" << SLname[isl-1] << "L" << il;
      DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]= new TH1F(histoNameOccup.str().c_str(),histoTitleOccup.str().c_str(),100, 0.,100.);
  }

  TH2F *DigiXYS[5][14];
  TH1F *OccupMB[5][4];
  TH1F *OccupWh[5];

  std::map<int,std::vector<int> >::const_iterator whIt  = mySectors.begin();
  std::map<int,std::vector<int> >::const_iterator whEnd = mySectors.end();
  for(;whIt!=whEnd;++whIt) {
    int iw = (*whIt).first + 2;
    std::vector<int>::const_iterator secIt  = (*whIt).second.begin();
    std::vector<int>::const_iterator secEnd = (*whIt).second.end();
    for(;secIt!=secEnd;++secIt) {
      int isec = (*secIt);
 
     // Occupancies
      stringstream histoNameOcc; histoNameOcc << "hDigiXY_" << Whname[iw] << "_S" << isec;
      DigiXYS[iw][isec-1]=getHisto<TH2F>(histoNameOcc.str());
      int nbx= DigiXYS[iw][isec-1]->GetNbinsX() ;

      for(int ich=1;ich<5;ich++){
	 for(int isl=1;isl<4;isl++){
	  for(int il=1;il<5;il++){
	    int iby=(ich-1)*20+(isl-1)*4+il+1;
	    float totentr=0;
	    for(int ibx=1;ibx<nbx;ibx++){
	      float yval=DigiXYS[iw][isec-1]->GetBinContent(ibx,iby);
	      DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetBinContent(ibx,yval);
	      totentr+=yval; 
	    }
	    DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->SetEntries(totentr);
	  }
	 }
      }
    }// End loop Sectors
  }//End loop Wheels

  for(int iw=0;iw<5;++iw)
  for(int ich=1;ich<5;++ich)
  {
     stringstream histoNameOccMB; histoNameOccMB << "Digi_" << Whname[iw] << "_MB" << ich;
     OccupMB[iw][ich-1]= new TH1F(histoNameOccMB.str().c_str(),histoNameOccMB.str().c_str(),14, 0.,14.);
  }
  whIt  = mySectors.begin();
  whEnd = mySectors.end();
  for(;whIt!=whEnd;++whIt) {
   int iw = (*whIt).first + 2;
   for(int ich=1;ich<5;++ich){
     for(int isec=1;isec<13;isec++){
      float totentr=0;
      for(int isl=1;isl<4;isl++){
        for(int il=1;il<5;il++){
          totentr+=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetEntries();
        }
      }
      OccupMB[iw][ich-1]->Fill(isec,totentr);
     }
   }
  }
   

/*
 for(int ic=0;ic<4;ic++)
 {
   first_to_paint_MB[ic]=OccupMB[0][ic];
   float nbmax=0;
   nbmax=OccupMB[0][ic]->GetMaximum();
   for(int iw=0;iw<5;iw++)
   {
      float nbmax0=0;
      nbmax0=OccupMB[iw][ic]->GetMaximum();

      if(nbmax0>nbmax)
      {
         nbmax=nbmax0; first_to_paint_MB[ic]=OccupMB[iw][ic];
      }
   }
 }

*/

 float Ocmax[4]={0.,0.,0.,0};
 for(int ic=0;ic<4;ic++)
 {
   first_to_paint_MB[ic]=OccupMB[0][ic];
   float nbmin=9999999;
   //float nbmin00=OccupMB[0][ic]->GetMinimum();
   //if(nbmin00 > 0) nbmin=nbmin00; 
   for(int iw=0;iw<5;iw++)
   {
      float nbmax0=0;
      //float nbmin0=99999999.;  // Not being used and in 62X gives erors for being set but not used
      nbmax0=OccupMB[iw][ic]->GetMaximum();
      //nbmin0=OccupMB[iw][ic]->GetMinimum();

      if(nbmax0>Ocmax[ic]) Ocmax[ic]=nbmax0; 
      if(nbmax0>0 && nbmax0<nbmin)
      {
         nbmin=nbmax0; first_to_paint_MB[ic]=OccupMB[iw][ic];
      }
      //if(nbmin0>0 && nbmin0<nbmin)
     // {
      //  nbmin=nbmin0; first_to_paint_MB[ic]=OccupMB[iw][ic];
     // }
   }
 }


 for(int ic=1;ic<5;ic++)
 {
   stringstream hname21; hname21 << "Total Occupancy  MB" << ic ;
   first_to_paint_MB[ic-1]->SetTitle(hname21.str().c_str());

   first_to_paint_MB[ic-1]->GetXaxis()->SetLabelSize(0.09);
   first_to_paint_MB[ic-1]->GetXaxis()->SetTitleSize(0.09);
   first_to_paint_MB[ic-1]->GetXaxis()->SetTitleOffset(0.5);
   first_to_paint_MB[ic-1]->GetXaxis()->SetTitle("Sector   ");
   first_to_paint_MB[ic-1]->GetYaxis()->SetLabelSize(0.09);
   first_to_paint_MB[ic-1]->GetYaxis()->SetTitleSize(0.09);
   first_to_paint_MB[ic-1]->GetYaxis()->SetTitleOffset(0.5);
   first_to_paint_MB[ic-1]->GetYaxis()->SetTitle("Entries");
   first_to_paint_MB[ic-1]->SetStats(0);
   first_to_paint_MB[ic-1]->SetMaximum(Ocmax[ic-1]*1.25);
//   int nbb=first_to_paint_MB[ic-1]->GetNbinsX();
//   float ymin=9999999999999.; 
//   for(int ib=1;ib<nbb;ib++)
//   {
//      float ymin0= first_to_paint_MB[ic-1]->GetBinContent(ib);
//      if(ymin0>0 && ymin0<ymin)ymin=ymin0;
//   }
//   first_to_paint_MB[ic-1]->SetMinimum(ymin*.20);
 }

  gStyle->SetTitleW(0.25);
  gStyle->SetTitleH(0.22);
  //gStyle->SetTitleX(0.74);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.90);
  gStyle->SetTitleY(1.01);
 

 TCanvas *OccupanALL = new TCanvas("OccupanALL", "",201,81,999,950);
 OccupanALL->Divide(1,4) ;
 for(int ic=1;ic<5;ic++)
 {
    OccupanALL->cd(ic)->SetLogy(1);
    OccupanALL->cd(ic)->SetFillColor(0);
    OccupanALL->cd(ic)->SetFrameFillColor(0);
    OccupanALL->cd(ic);
    first_to_paint_MB[ic-1]->Draw();

    for(int iw=0;iw<5;iw++)
    {
      OccupMB[iw][ic-1]->SetLineColor(iw+1);
      if(iw==4)
         OccupMB[iw][ic-1]->SetLineColor(6);
      OccupanALL->cd(ic);  OccupMB[iw][ic-1]->Draw("same");
    }
 }
 createGifFile("OccupancyAll","",OccupanALL,false);

 delete OccupanALL;

 // Occupancies/Sector
  for(int iw=0;iw<5;iw++){
    stringstream histoNameOccMB; histoNameOccMB << "Digi_" << Whname[iw];
    OccupWh[iw]= new TH1F(histoNameOccMB.str().c_str(),histoNameOccMB.str().c_str(),14, 0.,14.);
    for(int isec=1;isec<13;isec++){
     float totentr=0;
     for(int ich=1;ich<5;++ich){
      for(int isl=1;isl<4;isl++){
        for(int il=1;il<5;il++){
          if(DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1])
            totentr+=DigiXSecMBSlLayer[iw][isec-1][ich-1][isl-1][il-1]->GetEntries();
        }
      }
     OccupWh[iw]->Fill(isec,totentr);
     }
   }
  }

 first_to_paint=OccupWh[0];

/*
 float nbmax=0;
 nbmax=OccupWh[0]->GetMaximum();
 for(int iw=1;iw<5;iw++)
 {
   float nbmax0=0;
   nbmax0=OccupWh[iw]->GetMaximum();
   if(nbmax0>nbmax)
   {
      nbmax=nbmax0; first_to_paint=OccupWh[iw];
   }
 }
*/

 float OcmaxS=0;
 float nbminS=9999999;
 float nbminS00=OccupWh[0]->GetMinimum();
 if(nbminS00 > 0) nbminS=nbminS00;
 for(int iw=1;iw<5;iw++)
 {
    float nbmax0=0;
    float nbmin0=99999999.;
    nbmax0=OccupWh[iw]->GetMaximum();

    if(nbmax0>OcmaxS) OcmaxS=nbmax0;
    if(nbmin0>0 && nbmin0<nbminS)
    {
        nbminS=nbmin0; first_to_paint_MB[iw]=OccupWh[iw];
    }
 }



 stringstream hname21; hname21 << "Total Occupancy ";
 first_to_paint->SetTitle(hname21.str().c_str());

 first_to_paint->GetXaxis()->SetLabelSize(0.04);
 first_to_paint->GetXaxis()->SetTitleSize(0.04);
// first_to_paint->GetXaxis()->SetTitleOffset(0.5);
 first_to_paint->GetXaxis()->SetTitle("Sector   ");
 first_to_paint->GetYaxis()->SetLabelSize(0.04);
 first_to_paint->GetYaxis()->SetTitleSize(0.04);
// first_to_paint->GetYaxis()->SetTitleOffset(0.5);
 first_to_paint->GetYaxis()->SetTitle("Entries");
 first_to_paint->SetStats(0);


  gStyle->SetTitleX(0.31);
  gStyle->SetTitleY(1.01);
  gStyle->SetTitleW(0.87);
  gStyle->SetTitleH(0.12);


 TCanvas *OccupanSec = new TCanvas("OccupanSec", "",201,81,650,550);
 OccupanSec->SetLogy(1) ;
 first_to_paint->SetMaximum(OcmaxS*1.25);
 float yminS=9999999999999.; 
 int nbbS=first_to_paint->GetNbinsX();
 for(int ib=1;ib<nbbS;ib++)
 {
   float ymin0= first_to_paint->GetBinContent(ib);
   if(ymin0>0 && ymin0<yminS)yminS=ymin0;
  }
 first_to_paint->SetMinimum(yminS*.20);
 first_to_paint->Draw();
 for(int iw=0;iw<5;iw++)
 {
   OccupWh[iw]->SetLineColor(iw+1);
   if(iw==4)OccupWh[iw]->SetLineColor(6);
   OccupWh[iw]->Draw("same");
 }

 createGifFile("OccupancySec","",OccupanSec,false);
 delete OccupanSec;

  gStyle->SetTitleW(0.55);
  gStyle->SetTitleH(0.13);
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.31);
  gStyle->SetTitleY(1.03);
  
  gStyle->SetOptStat(10);
  gStyle->SetStatX(0.98);
  //gStyle->SetStatY(0.97);
  gStyle->SetStatY(0.89);
  gStyle->SetStatW(0.35);
  //gStyle->SetStatH(0.38);
  gStyle->SetStatH(0.20);


 TH1F *TBoxSec[5][12];
 TH1F *TBoxMB[5][4];
 TH1F *TBoxMBTop[5][4];
 TH1F *TBoxMBBottom[5][4];
 TH1F *TBoxMBVertical[5][4];

 TH1F *TBoxSegSec[5][12];
 TH1F *TBoxSegMB[5][4];
 TH1F *TBoxSegMBTop[5][4];
 TH1F *TBoxSegMBBottom[5][4];
 TH1F *TBoxSegMBVertical[5][4];


 for(int iw=0; iw<5; iw++)
 {
   for(int is=0;is<12; is++)
   {
     TBoxSec[iw][is]=NULL;
     TBoxSegSec[iw][is]=NULL;
   }
   for(int ic=0;ic<4; ic++)
   {
     TBoxMB[iw][ic]=NULL;
     TBoxMBTop[iw][ic]=NULL;
     TBoxMBBottom[iw][ic]=NULL;
     TBoxMBVertical[iw][ic]=NULL;
     
     TBoxSegMB[iw][ic]=NULL;
     TBoxSegMBTop[iw][ic]=NULL;
     TBoxSegMBBottom[iw][ic]=NULL;
     TBoxSegMBVertical[iw][ic]=NULL;
   }
 }


 whIt  = mySectors.begin();
 whEnd = mySectors.end();
 for(;whIt!=whEnd;++whIt) {
   int iw = (*whIt).first + 2;
  
   std::vector<int>::const_iterator secIt  = (*whIt).second.begin();
   std::vector<int>::const_iterator secEnd = (*whIt).second.end();
   for(;secIt!=secEnd;++secIt) {
      int isec = (*secIt);
    if(isec<13)  
    for(int ic=1;ic<5;ic++){
        stringstream hname; hname << "htime_" << Whname[iw] << "_S" << isec << "_MB" << ic;
        TH1F * theHisto=getHisto<TH1F>(hname.str());

        stringstream hnames; hnames << "SegTimeBox_" << Whname[iw] << "_S" << isec << "_MB" << ic;
        TH1F * theHistos=getHisto<TH1F>(hnames.str());

        if(isec==1)
        {
           stringstream hname2; hname2 << "htime_" << Whname[iw] << "_MB" << ic ;
           TBoxMB[iw][ic-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           TBoxMB[iw][ic-1]->SetTitle(hname2.str().c_str());

           stringstream hname3; hname3 << "htime_" << Whname[iw] << "_MB" << ic << "_Vertical" ;
           TBoxMBVertical[iw][ic-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           TBoxMBVertical[iw][ic-1]->SetTitle(hname3.str().c_str());

           stringstream hname2s; hname2s << "SegTimeBox_" << Whname[iw] << "_MB" << ic ;
           TBoxSegMB[iw][ic-1]=(TH1F*)theHistos->Clone(hnames.str().c_str());
           TBoxSegMB[iw][ic-1]->SetTitle(hname2s.str().c_str());

           stringstream hname3s; hname3s << "SegTimeBox_" << Whname[iw] << "_MB" << ic << "_Vertical" ;
           TBoxSegMBVertical[iw][ic-1]=(TH1F*)theHistos->Clone(hnames.str().c_str());
           TBoxSegMBVertical[iw][ic-1]->SetTitle(hname3s.str().c_str());
        }
        if(isec==2)
        {
           stringstream hname2; hname2 << "htime_" << Whname[iw] << "_MB" << ic << "_Top"  ;
           TBoxMBTop[iw][ic-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           TBoxMBTop[iw][ic-1]->SetTitle(hname2.str().c_str());

           stringstream hname2s; hname2s << "SegTimeBox_" << Whname[iw] << "_MB" << ic << "_Top"  ;
           TBoxSegMBTop[iw][ic-1]=(TH1F*)theHistos->Clone(hnames.str().c_str());
           TBoxSegMBTop[iw][ic-1]->SetTitle(hname2s.str().c_str());
        }
        if(isec==8)
        {
           stringstream hname2; hname2 << "htime_" << Whname[iw] << "_MB" << ic << "_Bottom"  ;
           TBoxMBBottom[iw][ic-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           TBoxMBBottom[iw][ic-1]->SetTitle(hname2.str().c_str());

           stringstream hname2s; hname2s << "SegTimeBox_" << Whname[iw] << "_MB" << ic << "_Bottom"  ;
           TBoxSegMBBottom[iw][ic-1]=(TH1F*)theHistos->Clone(hnames.str().c_str());
           TBoxSegMBBottom[iw][ic-1]->SetTitle(hname2s.str().c_str());
        } 
 
        if(isec>2)TBoxMB[iw][ic-1]->Add(theHisto);   // 
        if(isec>2 && isec<7)TBoxMBTop[iw][ic-1]->Add(theHisto);  
        if(isec>8)TBoxMBBottom[iw][ic-1]->Add(theHisto);  
        if(isec==7)TBoxMBVertical[iw][ic-1]->Add(theHisto);   // 

        if(isec>2)TBoxSegMB[iw][ic-1]->Add(theHistos);   // 
        if(isec>2 && isec<7)TBoxSegMBTop[iw][ic-1]->Add(theHistos);  
        if(isec>8)TBoxSegMBBottom[iw][ic-1]->Add(theHistos);  
        if(isec==7)TBoxSegMBVertical[iw][ic-1]->Add(theHistos);   // 

        if(ic==1) 
        {
           stringstream hname2; hname2 << "timebox_" << Whname[iw] << "_S" << isec ;
           TBoxSec[iw][isec-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           TBoxSec[iw][isec-1]->SetTitle(hname2.str().c_str());

           stringstream hname2s; hname2s << "SegTimeBox_" << Whname[iw] << "_S" << isec ;
           TBoxSegSec[iw][isec-1]=(TH1F*)theHistos->Clone(hnames.str().c_str());
           TBoxSegSec[iw][isec-1]->SetTitle(hname2s.str().c_str());

        }
        if(ic>1)TBoxSec[iw][isec-1]->Add(theHisto);   // 
        if(ic>1)TBoxSegSec[iw][isec-1]->Add(theHistos);   // 

    }// end loop MB
   }// end loop Sector
 }// end loop Wheel

 TH1F * first_to_paint_MB_typ[4][4];
 for(int ic=0;ic<4;ic++)
 {
   first_to_paint_MB_typ[ic][0]=TBoxMB[0][ic];
   first_to_paint_MB_typ[ic][1]=TBoxMBTop[0][ic];
   first_to_paint_MB_typ[ic][2]=TBoxMBBottom[0][ic];
   first_to_paint_MB_typ[ic][3]=TBoxMBVertical[0][ic];
   float nbmax[4]={0,0,0,0};
   if(TBoxMB[0][ic] != NULL) nbmax[0]=TBoxMB[0][ic]->GetMaximum();
   if(TBoxMBTop[0][ic] != NULL) nbmax[1]=TBoxMBTop[0][ic]->GetMaximum();
   if(TBoxMBBottom[0][ic] != NULL) nbmax[2]=TBoxMBBottom[0][ic]->GetMaximum();
   if(TBoxMBVertical[0][ic] != NULL) nbmax[3]=TBoxMBVertical[0][ic]->GetMaximum();
   for(int iw=1;iw<5;iw++)
   {
      float nbmax0[4]={0,0,0,0};
      if(TBoxMB[iw][ic] != NULL)        nbmax0[0]=TBoxMB[iw][ic]->GetMaximum();
      if(TBoxMBTop[iw][ic] != NULL)     nbmax0[1]=TBoxMBTop[iw][ic]->GetMaximum();
      if(TBoxMBBottom[iw][ic] != NULL)  nbmax0[2]=TBoxMBBottom[iw][ic]->GetMaximum();
      if(TBoxMBVertical[iw][ic] != NULL)nbmax0[3]=TBoxMBVertical[iw][ic]->GetMaximum();

      if(nbmax0[0]>nbmax[0])
      {
         nbmax[0]=nbmax0[0]; first_to_paint_MB_typ[ic][0]=TBoxMB[iw][ic];
      }
      if(nbmax0[1]>nbmax[1])
      {
         nbmax[1]=nbmax0[1]; first_to_paint_MB_typ[ic][1]=TBoxMBTop[iw][ic];
      }
      if(nbmax0[2]>nbmax[2])
      {
         nbmax[2]=nbmax0[2]; first_to_paint_MB_typ[ic][2]=TBoxMBBottom[iw][ic];
      }
      if(nbmax0[3]>nbmax[3])
      {
         nbmax[3]=nbmax0[3]; first_to_paint_MB_typ[ic][3]=TBoxMBVertical[iw][ic];
      }

   }
 }
 for(int ic=1;ic<5;ic++)
 {
   stringstream hname21; hname21 << "htime_MB" << ic ;
   stringstream hname22; hname22 << "htime_MB" << ic << "_Top"  ;
   stringstream hname23; hname23 << "htime_MB" << ic << "_Bottom"  ;
   stringstream hname24; hname24 << "htime_MB" << ic << "_Vertical"  ;
   if(first_to_paint_MB_typ[ic-1][0] != NULL) first_to_paint_MB_typ[ic-1][0]->SetTitle(hname21.str().c_str());
   if(first_to_paint_MB_typ[ic-1][1] != NULL) first_to_paint_MB_typ[ic-1][1]->SetTitle(hname22.str().c_str());
   if(first_to_paint_MB_typ[ic-1][2] != NULL) first_to_paint_MB_typ[ic-1][2]->SetTitle(hname23.str().c_str());
   if(first_to_paint_MB_typ[ic-1][3] != NULL) first_to_paint_MB_typ[ic-1][3]->SetTitle(hname24.str().c_str());

   for(int ityp=0;ityp<4;ityp++)
   {
     if(first_to_paint_MB_typ[ic-1][ityp] != NULL)
     {
       first_to_paint_MB_typ[ic-1][ityp]->GetXaxis()->SetLabelSize(0.07);
       first_to_paint_MB_typ[ic-1][ityp]->GetYaxis()->SetLabelSize(0.05);
       first_to_paint_MB_typ[ic-1][ityp]->SetNdivisions(505);
     }
   }
 }


 TCanvas *TBoxAll = new TCanvas("TBoxAll", "",201,81,999,950);
 int TBoxAllCheck=0;
 TBoxAll->Divide(4,4) ;
 for(int ic=1;ic<5;ic++)
 {
    for(int it=0;it<4;it++) 
    {
      TBoxAll->cd((ic-1)*4+it+1); 
      if(first_to_paint_MB_typ[ic-1][it]!= NULL) 
      {
         TBoxAllCheck++;
         first_to_paint_MB_typ[ic-1][it]->SetMinimum(0);
         first_to_paint_MB_typ[ic-1][it]->Draw();
      }
    }

    for(int iw=0;iw<5;iw++)
    {
      if(TBoxMB[iw][ic-1]!=NULL) TBoxMB[iw][ic-1]->SetLineColor(iw+1);
      if(TBoxMBTop[iw][ic-1]!=NULL) TBoxMBTop[iw][ic-1]->SetLineColor(iw+1);
      if(TBoxMBBottom[iw][ic-1]!=NULL) TBoxMBBottom[iw][ic-1]->SetLineColor(iw+1);
      if(TBoxMBVertical[iw][ic-1]!=NULL) TBoxMBVertical[iw][ic-1]->SetLineColor(iw+1);
      if(iw==4)
       {
         if(TBoxMB[iw][ic-1]!=NULL) TBoxMB[iw][ic-1]->SetLineColor(6);
         if(TBoxMBTop[iw][ic-1]!=NULL) TBoxMBTop[iw][ic-1]->SetLineColor(6);
         if(TBoxMBBottom[iw][ic-1]!=NULL) TBoxMBBottom[iw][ic-1]->SetLineColor(6);
         if(TBoxMBVertical[iw][ic-1]!=NULL) TBoxMBVertical[iw][ic-1]->SetLineColor(6);
       }
      TBoxAll->cd((ic-1)*4+1);  if(TBoxMB[iw][ic-1]!=NULL)  TBoxMB[iw][ic-1]->Draw("same");
      TBoxAll->cd((ic-1)*4+2);  if(TBoxMBTop[iw][ic-1]!=NULL)  TBoxMBTop[iw][ic-1]->Draw("same");
      TBoxAll->cd((ic-1)*4+3);  if(TBoxMBBottom[iw][ic-1]!=NULL)  TBoxMBBottom[iw][ic-1]->Draw("same");
      TBoxAll->cd((ic-1)*4+4);  if(TBoxMBVertical[iw][ic-1]!=NULL)  TBoxMBVertical[iw][ic-1]->Draw("same");
    }
 }

 if(TBoxAllCheck > 0)createGifFile("TimeBoxAll","",TBoxAll,false);
 delete TBoxAll;

  gStyle->SetTitleW(0.55);
  gStyle->SetTitleH(0.13);
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.31);
  gStyle->SetTitleY(1.03);


 TCanvas *TBoxWh[5];
 TBoxWh[0] = new TCanvas("TBoxWh-2", "",201,81,999,950);
 TBoxWh[1] = new TCanvas("TBoxWh-1", "",201,81,999,950);
 TBoxWh[2] = new TCanvas("TBoxWh0", "",201,81,999,950);
 TBoxWh[3] = new TCanvas("TBoxWh+1", "",201,81,999,950);
 TBoxWh[4] = new TCanvas("TBoxWh+2", "",201,81,999,950);
 int TBoxWhCheck[5]={0,0,0,0,0};
 for(int iw=0;iw<5;iw++)
 {
   TBoxWh[iw]->Divide(3,4) ;
   for(int isec=1;isec<13;isec++)
   {
     TBoxWh[iw]->cd(isec);
     TBoxWh[iw]->cd(isec)->SetFillColor(0);
     TBoxWh[iw]->cd(isec)->SetFrameFillColor(0);
     if(TBoxSec[iw][isec-1] != NULL)
     {
       TBoxWhCheck[iw]++;
      TBoxSec[iw][isec-1]->GetXaxis()->SetLabelSize(0.07);
      TBoxSec[iw][isec-1]->GetYaxis()->SetLabelSize(0.05);
      TBoxSec[iw][isec-1]->SetNdivisions(505);
      TBoxSec[iw][isec-1]->Draw();   // 
     }
   }
 }

 for(int iw=0;iw<5;iw++)
 {
   if(TBoxWhCheck[iw]>0)
    createGifFile("TimeBoxAll",(iw-2),"",TBoxWh[iw]);
   delete TBoxWh[iw];
 }

 TH1F * first_to_paint_MB_typSeg[4][4];
 for(int i=0;i<4;i++)
   for(int j=0;j<4;j++)
        first_to_paint_MB_typSeg[i][j]=NULL;

 for(int ic=0;ic<4;ic++)
 {
   if(TBoxSegMB[0][ic]!=NULL)         first_to_paint_MB_typSeg[ic][0]=TBoxSegMB[0][ic];
   if(TBoxSegMBTop[0][ic]!=NULL)      first_to_paint_MB_typSeg[ic][1]=TBoxSegMBTop[0][ic];
   if(TBoxSegMBBottom[0][ic]!=NULL)   first_to_paint_MB_typSeg[ic][2]=TBoxSegMBBottom[0][ic];
   if(TBoxSegMBVertical[0][ic]!=NULL) first_to_paint_MB_typSeg[ic][3]=TBoxSegMBVertical[0][ic];
   float nbmax[4]={0,0,0,0};
   if(TBoxSegMB[0][ic]!=NULL)         nbmax[0]=TBoxSegMB[0][ic]->GetMaximum();
   if(TBoxSegMBTop[0][ic]!=NULL)      nbmax[1]=TBoxSegMBTop[0][ic]->GetMaximum();
   if(TBoxSegMBBottom[0][ic]!=NULL)   nbmax[2]=TBoxSegMBBottom[0][ic]->GetMaximum();
   if(TBoxSegMBVertical[0][ic]!=NULL) nbmax[3]=TBoxSegMBVertical[0][ic]->GetMaximum();
   for(int iw=1;iw<5;iw++)
   {
      float nbmax0[4]={0,0,0,0};
      if(TBoxSegMB[0][ic]!=NULL)         nbmax0[0]=TBoxSegMB[iw][ic]->GetMaximum();
      if(TBoxSegMBTop[0][ic]!=NULL)      nbmax0[1]=TBoxSegMBTop[iw][ic]->GetMaximum();
      if(TBoxSegMBBottom[0][ic]!=NULL)   nbmax0[2]=TBoxSegMBBottom[iw][ic]->GetMaximum();
      if(TBoxSegMBVertical[0][ic]!=NULL) nbmax0[3]=TBoxSegMBVertical[iw][ic]->GetMaximum();

      if(nbmax0[0]>nbmax[0])
      {
         nbmax[0]=nbmax0[0]; first_to_paint_MB_typSeg[ic][0]=TBoxSegMB[iw][ic];
      }
      if(nbmax0[1]>nbmax[1])
      {
         nbmax[1]=nbmax0[1]; first_to_paint_MB_typSeg[ic][1]=TBoxSegMBTop[iw][ic];
      }
      if(nbmax0[2]>nbmax[2])
      {
         nbmax[2]=nbmax0[2]; first_to_paint_MB_typSeg[ic][2]=TBoxSegMBBottom[iw][ic];
      }
      if(nbmax0[3]>nbmax[3])
      {
         nbmax[3]=nbmax0[3]; first_to_paint_MB_typSeg[ic][3]=TBoxSegMBVertical[iw][ic];
      }

   }
 }
 for(int ic=1;ic<5;ic++)
 {
   stringstream hname21; hname21 << "htime_MB" << ic ;
   stringstream hname22; hname22 << "htime_MB" << ic << "_Top"  ;
   stringstream hname23; hname23 << "htime_MB" << ic << "_Bottom"  ;
   stringstream hname24; hname24 << "htime_MB" << ic << "_Vertical"  ;
   if(first_to_paint_MB_typSeg[ic-1][0] != NULL) first_to_paint_MB_typSeg[ic-1][0]->SetTitle(hname21.str().c_str());
   if(first_to_paint_MB_typSeg[ic-1][1] != NULL) first_to_paint_MB_typSeg[ic-1][1]->SetTitle(hname22.str().c_str());
   if(first_to_paint_MB_typSeg[ic-1][2] != NULL) first_to_paint_MB_typSeg[ic-1][2]->SetTitle(hname23.str().c_str());
   if(first_to_paint_MB_typSeg[ic-1][3] != NULL) first_to_paint_MB_typSeg[ic-1][3]->SetTitle(hname24.str().c_str());

   for(int ityp=0;ityp<4;ityp++)
   {
    if(first_to_paint_MB_typSeg[ic-1][ityp]!= NULL)
    {
     first_to_paint_MB_typSeg[ic-1][ityp]->GetXaxis()->SetLabelSize(0.07);
     first_to_paint_MB_typSeg[ic-1][ityp]->GetYaxis()->SetLabelSize(0.05);
     first_to_paint_MB_typSeg[ic-1][ityp]->SetNdivisions(505);
    } 
   }
 }


 TCanvas *TBoxAllSeg = new TCanvas("TBoxAllSeg", "",201,81,999,950);
 TBoxAllSeg->Divide(4,4) ;
 int TBoxAllSegCheck=0;
 for(int ic=1;ic<5;ic++)
 {
    for (int it=0;it<4;it++)
    {
      if(first_to_paint_MB_typSeg[ic-1][it] != NULL )
      {
        TBoxAllSegCheck++;
        first_to_paint_MB_typSeg[ic-1][it]->SetMinimum(0);
        TBoxAllSeg->cd((ic-1)*4+it+1); 
        first_to_paint_MB_typSeg[ic-1][it]->Draw();
      }
    }

    for(int iw=0;iw<5;iw++)
    {
      if(TBoxSegMB[iw][ic-1] != NULL)        TBoxSegMB[iw][ic-1]->SetLineColor(iw+1);
      if(TBoxSegMBTop[iw][ic-1] != NULL)     TBoxSegMBTop[iw][ic-1]->SetLineColor(iw+1);
      if(TBoxSegMBBottom[iw][ic-1] != NULL)  TBoxSegMBBottom[iw][ic-1]->SetLineColor(iw+1);
      if(TBoxSegMBVertical[iw][ic-1] != NULL)TBoxSegMBVertical[iw][ic-1]->SetLineColor(iw+1);
      if(iw==4)
       {
         if(TBoxSegMB[iw][ic-1] != NULL)        TBoxSegMB[iw][ic-1]->SetLineColor(6);
         if(TBoxSegMBTop[iw][ic-1] != NULL)     TBoxSegMBTop[iw][ic-1]->SetLineColor(6);
         if(TBoxSegMBBottom[iw][ic-1] != NULL)  TBoxSegMBBottom[iw][ic-1]->SetLineColor(6);
         if(TBoxSegMBVertical[iw][ic-1] != NULL)TBoxSegMBVertical[iw][ic-1]->SetLineColor(6);
       }
      TBoxAllSeg->cd((ic-1)*4+1); if(TBoxSegMB[iw][ic-1] != NULL)         TBoxSegMB[iw][ic-1]->Draw("same");
      TBoxAllSeg->cd((ic-1)*4+2); if(TBoxSegMBTop[iw][ic-1] != NULL)      TBoxSegMBTop[iw][ic-1]->Draw("same");
      TBoxAllSeg->cd((ic-1)*4+3); if(TBoxSegMBBottom[iw][ic-1] != NULL)   TBoxSegMBBottom[iw][ic-1]->Draw("same");
      TBoxAllSeg->cd((ic-1)*4+4); if(TBoxSegMBVertical[iw][ic-1] != NULL) TBoxSegMBVertical[iw][ic-1]->Draw("same");
    }
 }

 if(TBoxAllSegCheck>0)createGifFile("TimeBoxAllSeg","",TBoxAllSeg,false);
 delete TBoxAllSeg;

  gStyle->SetTitleW(0.55);
  gStyle->SetTitleH(0.13);
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.31);
  gStyle->SetTitleY(1.03);


 TCanvas *TBoxWhSeg[5];
 int TBoxWhSegCheck[5]={0,0,0,0,0};
 TBoxWhSeg[0] = new TCanvas("TBoxSegWh-2", "",201,81,999,950);
 TBoxWhSeg[1] = new TCanvas("TBoxSegWh-1", "",201,81,999,950);
 TBoxWhSeg[2] = new TCanvas("TBoxSegWh0", "",201,81,999,950);
 TBoxWhSeg[3] = new TCanvas("TBoxSegWh+1", "",201,81,999,950);
 TBoxWhSeg[4] = new TCanvas("TBoxSegWh+2", "",201,81,999,950);
 for(int iw=0;iw<5;iw++)
 {
   TBoxWhSeg[iw]->Divide(3,4) ;
   for(int isec=1;isec<13;isec++)
   {
     TBoxWhSeg[iw]->cd(isec);
     TBoxWhSeg[iw]->cd(isec)->SetFillColor(0);
     TBoxWhSeg[iw]->cd(isec)->SetFrameFillColor(0);

     if(TBoxSegSec[iw][isec-1] != NULL)
     {
      TBoxWhSegCheck[iw]++;
      TBoxSegSec[iw][isec-1]->GetXaxis()->SetLabelSize(0.07);
      TBoxSegSec[iw][isec-1]->GetYaxis()->SetLabelSize(0.05);
      TBoxSegSec[iw][isec-1]->SetNdivisions(505);
      TBoxSegSec[iw][isec-1]->Draw();   // 
     }
   }
 }

 for(int iw=0;iw<5;iw++)
 {
    if(TBoxWhSegCheck[iw]>0)
      createGifFile("TimeBoxAllSeg",(iw-2),"",TBoxWhSeg[iw]);
    delete TBoxWhSeg[iw];
 }

 


 
  gStyle->SetOptStat(10);
  gStyle->SetStatX(0.4);
  gStyle->SetStatY(0.88);
  gStyle->SetStatW(0.29);
  gStyle->SetStatH(0.38);
  gStyle->SetTitleY(1.03);


 TH1F *NHitsSec[5][12];
 TH1F *NHitsMB[5][4];
 TH1F *NHitsMBTop[5][4];
 TH1F *NHitsMBBottom[5][4];
 TH1F *NHitsMBVertical[5][4];
 for(int iw=0;iw<5;iw++)
 {
   for(int isec=0;isec<12;isec++)NHitsSec[iw][isec]=NULL;
   for(int ic=0;ic<5;ic++)
   {
    NHitsMB[iw][ic]=NULL;
    NHitsMBTop[iw][ic]=NULL;
    NHitsMBBottom[iw][ic]=NULL;
    NHitsMBVertical[iw][ic]=NULL;
   }
 }

 whIt  = mySectors.begin();
 whEnd = mySectors.end();
 for(;whIt!=whEnd;++whIt) {
  int iw = (*whIt).first + 2;
  std::vector<int>::const_iterator secIt  = (*whIt).second.begin();
  std::vector<int>::const_iterator secEnd = (*whIt).second.end();
  for(;secIt!=secEnd;++secIt) {
    int isec = (*secIt);
    if(isec<13)
    for(int ic=1;ic<5;ic++){
      //for(int isl=1;isl<4;isl++){
        //stringstream hname; hname << "hNhits_" << Whname[iw] << "_S" << isec << "_MB" << ic << "_SL" << isl;
      {
        stringstream hname; hname << "hNhits_" << Whname[iw] << "_S" << isec << "_MB" << ic;
        TH1F * theHisto=getHisto<TH1F>(hname.str());

        if(isec==1)
        {
           stringstream hname2; hname2 << "nHits_" << Whname[iw] << "_MB" << ic ;
           NHitsMB[iw][ic-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           NHitsMB[iw][ic-1]->SetTitle(hname2.str().c_str());

           stringstream hname3; hname3 << "nHits_" << Whname[iw] << "_MB" << ic << "_Vertical";
           NHitsMBVertical[iw][ic-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           NHitsMBVertical[iw][ic-1]->SetTitle(hname3.str().c_str());
        }
        if(isec==2)
        {
           stringstream hname2; hname2 << "nHits_" << Whname[iw] << "_MB" << ic << "_Top"  ;
           NHitsMBTop[iw][ic-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           NHitsMBTop[iw][ic-1]->SetTitle(hname2.str().c_str());
        }
        if(isec==8)
        {
           stringstream hname2; hname2 << "nHits_" << Whname[iw] << "_MB" << ic << "_Bottom"  ;
           NHitsMBBottom[iw][ic-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           NHitsMBBottom[iw][ic-1]->SetTitle(hname2.str().c_str());
        }


        if(isec>2)NHitsMB[iw][ic-1]->Add(theHisto);   // 
        if(isec>2 && isec<7)NHitsMBTop[iw][ic-1]->Add(theHisto);
        if(isec>8)NHitsMBBottom[iw][ic-1]->Add(theHisto);
        if(isec==7)NHitsMBVertical[iw][ic-1]->Add(theHisto);

        if(ic==1)
        {
           stringstream hname2; hname2 << "nHits_" << Whname[iw] << "_S"  << isec ;
           NHitsSec[iw][isec-1]=(TH1F*)theHisto->Clone(hname.str().c_str());
           NHitsSec[iw][isec-1]->SetTitle(hname2.str().c_str());

        }
        if(ic>1 && ic<4)NHitsSec[iw][isec-1]->Add(theHisto);  // To avoid mix with MB4
                                                              // that has not Theta SLs 
      }
    }
  }
 }

 for(int ic=0;ic<4;ic++)
 {
   first_to_paint_MB_typ[ic][0]=NHitsMB[0][ic];
   first_to_paint_MB_typ[ic][1]=NHitsMBTop[0][ic];
   first_to_paint_MB_typ[ic][2]=NHitsMBBottom[0][ic];
   first_to_paint_MB_typ[ic][3]=NHitsMBVertical[0][ic];
   float nbmax[4]={0,0,0,0};
   if(NHitsMB[0][ic])nbmax[0]=NHitsMB[0][ic]->GetMaximum();
   if(NHitsMBTop[0][ic])nbmax[1]=NHitsMBTop[0][ic]->GetMaximum();
   if(NHitsMBBottom[0][ic])nbmax[2]=NHitsMBBottom[0][ic]->GetMaximum();
   if(NHitsMBVertical[0][ic])nbmax[3]=NHitsMBVertical[0][ic]->GetMaximum();
   for(int iw=1;iw<5;iw++)
   {
      float nbmax0[4]={0,0,0,0};
      if(NHitsMB[iw][ic] !=NULL)nbmax0[0]=NHitsMB[iw][ic]->GetMaximum();
      if(NHitsMBTop[iw][ic] !=NULL)nbmax0[1]=NHitsMBTop[iw][ic]->GetMaximum();
      if(NHitsMBBottom[iw][ic] !=NULL)nbmax0[2]=NHitsMBBottom[iw][ic]->GetMaximum();
      if(NHitsMBVertical[iw][ic] !=NULL)nbmax0[3]=NHitsMBVertical[iw][ic]->GetMaximum();

      if(nbmax0[0]>nbmax[0])
      {
         nbmax[0]=nbmax0[0]; first_to_paint_MB_typ[ic][0]=NHitsMB[iw][ic];
      }
      if(nbmax0[1]>nbmax[1])
      {
         nbmax[1]=nbmax0[1]; first_to_paint_MB_typ[ic][1]=NHitsMBTop[iw][ic];
      }
      if(nbmax0[2]>nbmax[2])
      {
         nbmax[2]=nbmax0[2]; first_to_paint_MB_typ[ic][2]=NHitsMBBottom[iw][ic];
      }
      if(nbmax0[3]>nbmax[3])
      {
         nbmax[3]=nbmax0[3]; first_to_paint_MB_typ[ic][3]=NHitsMBVertical[iw][ic];
      }
   }
 }


 for(int ic=1;ic<5;ic++)
 {
   stringstream hname21; hname21 << "nHits_MB" << ic ;
   stringstream hname22; hname22 << "nHits_MB" << ic << "_Top"  ;
   stringstream hname23; hname23 << "nHits_MB" << ic << "_Bottom"  ;
   stringstream hname24; hname24 << "nHits_MB" << ic << "_Vertical"  ;
   if(first_to_paint_MB_typ[ic-1][0] != NULL) first_to_paint_MB_typ[ic-1][0]->SetTitle(hname21.str().c_str());
   if(first_to_paint_MB_typ[ic-1][1] != NULL) first_to_paint_MB_typ[ic-1][1]->SetTitle(hname22.str().c_str());
   if(first_to_paint_MB_typ[ic-1][2] != NULL) first_to_paint_MB_typ[ic-1][2]->SetTitle(hname23.str().c_str());
   if(first_to_paint_MB_typ[ic-1][3] != NULL) first_to_paint_MB_typ[ic-1][3]->SetTitle(hname24.str().c_str());

   for(int ityp=0;ityp<4;ityp++)
   {
     if(first_to_paint_MB_typ[ic-1][ityp] != NULL)
     {
       first_to_paint_MB_typ[ic-1][ityp]->GetXaxis()->SetLabelSize(0.07);
       first_to_paint_MB_typ[ic-1][ityp]->GetYaxis()->SetLabelSize(0.05);
       first_to_paint_MB_typ[ic-1][ityp]->SetNdivisions(505);
     }
   }
 }

 TCanvas *NHitsAll = new TCanvas("NHitsAll", "",201,81,999,950);
 int NHitsAllCheck=0;
 NHitsAll->Divide(4,4) ;
 for(int ip=1;ip<17;ip++)
 {
    NHitsAll->cd(ip)->SetFillColor(0) ;
    NHitsAll->cd(ip)->SetFrameFillColor(0) ;
 }
 for(int ic=1;ic<5;ic++)
 {
    for(int it=0;it<4; it++)
    {
       NHitsAll->cd((ic-1)*4+it+1); 
       if(first_to_paint_MB_typ[ic-1][it] != NULL)
       {
         NHitsAllCheck++;
         first_to_paint_MB_typ[ic-1][it]->Draw();
       }
    }

    for(int iw=0;iw<5;iw++)
    {
      if(NHitsMB[iw][ic-1] != NULL)NHitsMB[iw][ic-1]->SetLineColor(iw+1);
      if(NHitsMBTop[iw][ic-1] != NULL)NHitsMBTop[iw][ic-1]->SetLineColor(iw+1);
      if(NHitsMBBottom[iw][ic-1] != NULL)NHitsMBBottom[iw][ic-1]->SetLineColor(iw+1);
      if(NHitsMBVertical[iw][ic-1]!= NULL)NHitsMBVertical[iw][ic-1]->SetLineColor(iw+1);
      if(iw==4)
       {
         if(NHitsMB[iw][ic-1] != NULL)NHitsMB[iw][ic-1]->SetLineColor(6);
         if(NHitsMBTop[iw][ic-1] != NULL)NHitsMBTop[iw][ic-1]->SetLineColor(6);
         if(NHitsMBBottom[iw][ic-1] != NULL)NHitsMBBottom[iw][ic-1]->SetLineColor(6);
         if(NHitsMBVertical[iw][ic-1]!= NULL)NHitsMBVertical[iw][ic-1]->SetLineColor(6);
       }
      NHitsAll->cd((ic-1)*4+1);   if(NHitsMB[iw][ic-1] != NULL)NHitsMB[iw][ic-1]->Draw("same");
      NHitsAll->cd((ic-1)*4+2);   if(NHitsMBTop[iw][ic-1] != NULL)NHitsMBTop[iw][ic-1]->Draw("same");
      NHitsAll->cd((ic-1)*4+3);   if(NHitsMBBottom[iw][ic-1] != NULL)NHitsMBBottom[iw][ic-1]->Draw("same");
      NHitsAll->cd((ic-1)*4+4);   if(NHitsMBVertical[iw][ic-1]!= NULL)NHitsMBVertical[iw][ic-1]->Draw("same");
    }
 }


 if(NHitsAllCheck>0)createGifFile("NHitsAll","",NHitsAll,false);
 delete NHitsAll;
 

  gStyle->SetTitleW(0.55);
  gStyle->SetTitleH(0.13);
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.31);
  gStyle->SetTitleY(1.03);
 
 TCanvas *NHitsWh[5];
 int NHitsWhCheck[5]={0,0,0,0,0};
 NHitsWh[0] = new TCanvas("NHitsWh-2", "",201,81,999,950);
 NHitsWh[1] = new TCanvas("NHitsWh-1", "",201,81,999,950);
 NHitsWh[2] = new TCanvas("NHitsWh0", "",201,81,999,950);
 NHitsWh[3] = new TCanvas("NHitsWh+1", "",201,81,999,950);
 NHitsWh[4] = new TCanvas("NHitsWh+2", "",201,81,999,950);
 for(int iw=0;iw<5;iw++)
 {
   NHitsWh[iw]->Divide(3,4) ;
   for(int isec=1;isec<13;isec++)
   {
      NHitsWh[iw]->cd(isec);
      NHitsWh[iw]->cd(isec)->SetFillColor(0);
      NHitsWh[iw]->cd(isec)->SetFrameFillColor(0);
      if(NHitsSec[iw][isec-1] != NULL)
      {
        NHitsWhCheck[iw]++;
        NHitsSec[iw][isec-1]->GetXaxis()->SetLabelSize(0.07);
        NHitsSec[iw][isec-1]->GetYaxis()->SetLabelSize(0.05);
        NHitsSec[iw][isec-1]->SetNdivisions(505);
        NHitsSec[iw][isec-1]->Draw();   // 
      }
   }
 }

 for(int iw=0;iw<5;iw++)
 {
   if(NHitsWhCheck[iw]>0)createGifFile("NHitsSec",(iw-2),"",NHitsWh[iw]);
   delete NHitsWh[iw];
 }


  gStyle->SetTitleW(0.55);
  //gStyle->SetTitleH(0.13);
  gStyle->SetTitleH(0.11);
  //gStyle->SetTitleX(0.01);
  //gStyle->SetTitleY(0.99);
  gStyle->SetTitleX(0.31);
  gStyle->SetTitleY(1.03);

 TCanvas *NHitsWhAll;
 NHitsWhAll = new TCanvas("NHitsWhAll", "",201,81,999,950);
 NHitsWhAll->Divide(3,4) ;
 int NHitsWhAllCheck=0;
 for(int ins=1;ins<13;ins++)
 {
   first_to_paint=NHitsSec[0][ins-1];
   float nbmax1=0;
   if(NHitsSec[0][ins-1]!=NULL)NHitsSec[0][ins-1]->GetMaximum();
   for(int iw=1;iw<5;iw++)
   {
      float nbmax2=0;
      if(NHitsSec[iw][ins-1] != NULL)nbmax2=NHitsSec[iw][ins-1]->GetMaximum();
      if(nbmax2>nbmax1)
      {
         nbmax1=nbmax2; first_to_paint=NHitsSec[iw][ins-1];
      }
    }

    NHitsWhAll->cd(ins) ;
    NHitsWhAll->cd(ins)->SetFillColor(0) ;
    NHitsWhAll->cd(ins)->SetFrameFillColor(0) ;
    stringstream hname; hname << "nHits_S"  << ins ;
    if(first_to_paint != NULL)
    {
      NHitsWhAllCheck++;
      first_to_paint->SetTitle(hname.str().c_str());
      first_to_paint->Draw();
      for(int iw=0;iw<5;iw++)
      {
        if(NHitsSec[iw][ins-1] != NULL)
        {
         NHitsSec[iw][ins-1]->SetLineColor(iw+1);
         if(iw==4) NHitsSec[iw][ins-1]->SetLineColor(6);
         NHitsSec[iw][ins-1]->Draw("same");
        }
      }
    }
 }

 if(NHitsWhAllCheck>0)createGifFile("NHitsSec","",NHitsWhAll,false);

 delete NHitsWhAll;

 gStyle->SetStatY(1.01);
 //gStyle->SetStatX(0.98);
 gStyle->SetStatX(1.01);
 //gStyle->SetStatW(0.40);
 gStyle->SetStatW(0.35);
 //gStyle->SetStatH(0.25);
 gStyle->SetStatH(0.10);


 stringstream hnameSTA1; hnameSTA1 << "hrIPSA" ;
 stringstream hnameSTA2; hnameSTA2 << "hzIPSA" ;
 stringstream hnameSTA3; hnameSTA3 << "hrVszIPSA" ;

 TH1F * theHistoSTA1=NULL;
 TH1F * theHistoSTA2=NULL;
 TH2F * theHistoSTA3=NULL;

 theHistoSTA1=getHisto<TH1F>(hnameSTA1.str());
 theHistoSTA2=getHisto<TH1F>(hnameSTA2.str());
 theHistoSTA3=getHisto<TH2F>(hnameSTA3.str());

 TCanvas *STAatIP;
 STAatIP = new TCanvas("STAatIP", "",201,81,999,400);
 STAatIP->Divide(3,1) ;
 int CheckSTAatIP=0;
 for(int i=1;i<5;i++)
 { STAatIP->cd(i)->SetFillColor(0);STAatIP->cd(i)->SetFrameFillColor(0); }
 if(theHistoSTA1 != NULL){STAatIP->cd(1);theHistoSTA1->Draw(); CheckSTAatIP++; }
 else cout << " hrIPSA histo not found " << endl;
 if(theHistoSTA2 != NULL){STAatIP->cd(2);theHistoSTA2->Draw(); CheckSTAatIP++; }
 else cout << " hzIPSA histo not found " << endl;
 if(theHistoSTA3 != NULL){STAatIP->cd(3);theHistoSTA3->Draw("colz"); CheckSTAatIP++; }
 else cout << " hrvszIPSA histo not found " << endl;

 if(CheckSTAatIP>0)
   createGifFile("STATrack_at_IP","",STAatIP,false);
 delete STAatIP;


 //gStyle->SetStatY(0.97);
 gStyle->SetStatY(0.89);
 gStyle->SetStatX(0.98);
 gStyle->SetStatW(0.25);
 gStyle->SetStatH(0.15);


 TH1F * segphi=getHisto<TH1F>("segphi");
 TH1F * segphivsz=getHisto<TH1F>("segphivsz");

 TH1F * segphiMB[4];
 TH1F * segzMB[4];
 for(int ic=1;ic<5;ic++)
 {
   stringstream hname1; hname1 << "segphiMB" << ic ;
   stringstream hname2; hname2 << "segzMB" << ic ;
   segphiMB[ic-1]=getHisto<TH1F>(hname1.str());
   segzMB[ic-1]=getHisto<TH1F>(hname2.str());
 }

 TCanvas *SegPhiZ;
 SegPhiZ = new TCanvas("SegPhiZ", "",201,81,999,850);
 SegPhiZ->Divide(2,2) ;
 for(int i=1;i<5;i++)
 { SegPhiZ->cd(i)->SetFillColor(0);SegPhiZ->cd(i)->SetFrameFillColor(0); }

 SegPhiZ->cd(1);segphi->Draw();
 SegPhiZ->cd(2);segphivsz->Draw("colz");
 first_to_paint=segphiMB[0];
 int nbmaxPSeg=segphiMB[0]->GetMaximum();
 for(int i=1;i<4;i++)
 {
   int nbmax0=segphiMB[i]->GetMaximum();
   if(nbmax0>nbmaxPSeg){
      nbmaxPSeg=nbmax0;
      first_to_paint=segphiMB[i];
   }
 }
 first_to_paint->SetTitle("phi of segment position");
 first_to_paint->SetMinimum(0);
 SegPhiZ->cd(3);first_to_paint->Draw();
 for(int i=0;i<4;i++)
 {
  segphiMB[i]->SetLineColor(i+1); 
  segphiMB[i]->Draw("same"); 
 }
 first_to_paint=segzMB[0];
 first_to_paint->SetMinimum(0);
 int nbmaxZSeg=segzMB[0]->GetMaximum();
 for(int i=1;i<3;i++) // Not consider the MB4, not Theta Segment 
 {
   int nbmax0=segzMB[i]->GetMaximum();
   if(nbmax0>nbmaxZSeg){
      nbmaxZSeg=nbmax0;
      first_to_paint=segzMB[i];
   }
 }
 first_to_paint->SetTitle("z of segment position");
 SegPhiZ->cd(4);first_to_paint->Draw();
 for(int i=0;i<3;i++)  // Not consider the MB4, not Theta Segment 
 {
  segzMB[i]->SetLineColor(i+1); 
  segzMB[i]->Draw("same"); 
 }


 createGifFile("SegmentPosition","",SegPhiZ,false);
 delete SegPhiZ;

 TH1F * difPhi4_all=getHisto<TH1F>("DifPhi4_1");
 TH1F * difPhi4_top=getHisto<TH1F>("DifPhi4_1_top");
 TH1F * difPhi4_bot=getHisto<TH1F>("DifPhi4_1_bot");

 TCanvas *DifPhi4;
 DifPhi4 = new TCanvas("DifPhi4", "",201,81,699,400);
 DifPhi4->Divide(2,1) ;
 for(int i=1;i<3;i++)
 { DifPhi4->cd(i)->SetFillColor(0);DifPhi4->cd(i)->SetFrameFillColor(0); }
 TPad *DifPhi4_2 = (TPad*) DifPhi4->GetListOfPrimitives()->FindObject("DifPhi4_2");

 DifPhi4->cd(1);difPhi4_all->Draw();
 TPaveLabel * titleDifPhi41 = new TPaveLabel(0.05,0.92,0.7,0.99,"phi pos. in MB4-MB1","NDC");
 titleDifPhi41->Draw();                                                                       

 difPhi4_top->SetTitle("Top Sectors"); difPhi4_bot->SetTitle("Bottom Sectors");
 DifPhi4->cd(2)->SetFillColor(0);DifPhi4->cd(2)->SetFrameFillColor(0);
 DifPhi4->cd(2);
 gStyle->SetOptTitle(0);
 double nphi4top=difPhi4_top->GetMaximum();
 double nphi4bot=difPhi4_bot->GetMaximum();
 if(nphi4bot>nphi4top)
 { difPhi4_bot->Draw();difPhi4_top->Draw("same"); }
 else
  {difPhi4_top->Draw();difPhi4_bot->Draw("same"); }
  
 DifPhi4_2->BuildLegend();
 titleDifPhi41->Draw();


 createGifFile("DifPhi14","",DifPhi4,false);
 
 delete DifPhi4;

 gStyle->SetOptTitle(1);

 
 TCanvas *hSeg;
 hSeg = new TCanvas("hSeg", "",201,81,999,850);
 hSeg->Divide(2,2);
 for(int i=1;i<4;i++)
 { hSeg->cd(i)->SetFillColor(0);hSeg->cd(i)->SetFrameFillColor(0); }

 TH1F * hnSegDT=getHisto<TH1F>("hnSegDT");
 TH1F * hnHSegDT=getHisto<TH1F>("hnHSegDT");
 TH1F * hnSegMB1=getHisto<TH1F>("hnSegMB1");
 TH1F * hnHSegMB1=getHisto<TH1F>("hnHSegMB1");

 hSeg->cd(1);hnSegDT->Draw();
 hSeg->cd(2);hnHSegDT->Draw();
 hSeg->cd(3);hnSegMB1->Draw();
 hSeg->cd(4);hnHSegMB1->Draw();
 
 createGifFile("SegmentsAll","",hSeg,false);
 delete hSeg;

}

  
