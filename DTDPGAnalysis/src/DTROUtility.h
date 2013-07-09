#ifndef DTROUtility_H
#define DTROUtility_H

/** \class DTROUtility
 *  Determines which sectors are actually read out.
 *  It uses the FEDIntegrity histos to determine the DDU in the RO 
 *  and the 00-DataIntegrity/FEDXXX/ROSYY/FEDXXX_ROSYY_Bunch_ID histo to determine
 *  which ROS was in the RO.
 *
 *  $Date: 2009/01/07 11:42:49 $
 *  $Revision: 1.2 $
 *  \author G. Cerminara - INFN Torino
 */

#include <string>
#include <vector>
#include <map>

class TFile;
class DQMStore;

class DTROUtility {
public:
  /// Constructor
  DTROUtility( TFile* file, const std::string mainFolder);

  DTROUtility(const DQMStore* file);


  /// Destructor
  virtual ~DTROUtility();

  // Operations
  std::map<int, std::vector<int> > getSectorMap() {
    return sectorsInROPerWheel;
  }

protected:

private:
  std::map<int, std::vector<int> > sectorsInROPerWheel;
  
};
#endif

