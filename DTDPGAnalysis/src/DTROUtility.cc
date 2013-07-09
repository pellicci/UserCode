/*
 *  See header file for a description of this class.
 *
 *  $Date: 2011/07/13 08:47:00 $
 *  $Revision: 1.4 $
 *  \author G. Cerminara - INFN Torino
 */

#include "UserCode/DTDPGAnalysis/src/DTROUtility.h"

#include "TFile.h"
#include "TH1F.h"

#include <sstream>
#include <iostream>

using namespace std;

DTROUtility::DTROUtility( TFile* file, const std::string mainFolder) {
  
  // Use FEDIntegrity Monitor to determine if a given FED is in the RO

  //const TH1F *fedIntegrityHisto = (const TH1F *) file->Get(string(mainFolder + "FEDIntegrity_DT/FEDEntries").c_str());
  //const TH1F *fedIntegrityHistoNF = (const TH1F *) file->Get(string(mainFolder + "FEDIntegrity_DT/FEDNonFatal").c_str());
  //const TH1F *fedIntegrityHistoF = (const TH1F *) file->Get(string(mainFolder + "FEDIntegrity_DT/FEDFatal").c_str());
  const TH1F *fedIntegrityHisto = (const TH1F *) file->Get(string(mainFolder + "FEDIntegrity/FEDEntries").c_str());
  const TH1F *fedIntegrityHistoNF = (const TH1F *) file->Get(string(mainFolder + "FEDIntegrity/FEDNonFatal").c_str());
  const TH1F *fedIntegrityHistoF = (const TH1F *) file->Get(string(mainFolder + "FEDIntegrity/FEDFatal").c_str());

  if(fedIntegrityHisto != 0 && fedIntegrityHistoNF != 0 && fedIntegrityHistoF != 0) {
    for(int fed0 = 770; fed0 != 775; ++fed0) { // loop over FEDs
     int bin = fed0 - 769;
     int bin2 = bin+5;  
     bool fedfound[2]={false,false};
     if(fedIntegrityHisto->GetBinContent(bin) != 0 || 
      fedIntegrityHistoNF->GetBinContent(bin) != 0 || 
      fedIntegrityHistoF->GetBinContent(bin) != 0) fedfound[0]=true;

     if(fedIntegrityHisto->GetBinContent(bin2) != 0 || 
      fedIntegrityHistoNF->GetBinContent(bin2) != 0 || 
      fedIntegrityHistoF->GetBinContent(bin2) != 0) fedfound[1]=true;

     if(fedfound[0]!=false || fedfound[1]!=false)
     {
	vector<int> rosInTheFED;
      for(int ifed=0;ifed<2;ifed++)
      {
       if(fedfound[ifed]!=false)
       {
        int fed=fed0+ifed*5;
        cout << "FED: " << fed << " in the RO" << endl;
        for(int ros = 1; ros != 13; ++ros) { // loop over ROS
         stringstream rosHistoName; rosHistoName << mainFolder << "00-DataIntegrity/FED" << fed << "/ROS" << ros
           					  << "/FED" << fed << "_ROS" << ros << "_ROSEventLenght";
         const TH1F *hBunchId = (const TH1F*) file->Get(rosHistoName.str().c_str());
         if(hBunchId != 0) {
           if(hBunchId->GetEntries() != 0) {
             cout << "   ROS: " << ros << " in the RO" << endl;
             rosInTheFED.push_back(ros);
             if(ros==4 )rosInTheFED.push_back(13); // Add extra MB4 at S4  == S13 
             if(ros==10)rosInTheFED.push_back(14); // Add extra MB4 at S10 == S14 
           }
         } else {
           cout << "[DTROUtility] Error: histo " << rosHistoName.str() << " not found!" << endl;
         }
        }// End loop ROS
       }
       else { cout << "FED: " << fed0+ifed*5 << " NOT in the RO" << endl; }
      }

	int wheel = fed0 - 772;
	sectorsInROPerWheel[wheel] = rosInTheFED;
     } 
     else { cout << "FED: " << fed0 << " and FED: " << fed0+5 << "  NOT in the RO" << endl; }
    }// End loop FEDs
  } else {
    cout << "[DTROUtility] Error: histo " << string(mainFolder + "FEDIntegrity/FEDEntries") << " not found!" << endl;
  }
}

DTROUtility::DTROUtility(const DQMStore* file){} //FIXME: dummy implementation at the moment

DTROUtility::~DTROUtility() {}

