\
#include<TFile.h>
#include<RooFitResult.h>
#include<RooArgList.h>
#include<RooAbsReal.h>
#include<RooRealVar.h>
#include <fstream>

const Int_t numsyst = 53;
const Int_t first_alone = 44;
const Int_t slot_rho = 48;
const Int_t slot_LASS = 49;

const Int_t TOT_syst = ((Int_t)(first_alone/2.) + numsyst - first_alone);

RooFitResult getRes(Int_t i = -1)
{
  TFile *f1(0);
  if(i == -1) f1 = new TFile("syst_root/fit_WS_std.root");
  else if(i == 0) f1 = new TFile("syst_root/fit_WS_Kstminus_m_down.root");
  else if(i == 1) f1 = new TFile("syst_root/fit_WS_Kstminus_m_up.root");
  else if(i == 2) f1 = new TFile("syst_root/fit_WS_Kstminus_w_down.root");
  else if(i == 3) f1 = new TFile("syst_root/fit_WS_Kstminus_w_up.root");
  else if(i == 4) f1 = new TFile("syst_root/fit_WS_rho_m_down.root");
  else if(i == 5) f1 = new TFile("syst_root/fit_WS_rho_m_up.root");
  else if(i == 6) f1 = new TFile("syst_root/fit_WS_rho_w_down.root");
  else if(i == 7) f1 = new TFile("syst_root/fit_WS_rho_w_up.root");
  else if(i == 8) f1 = new TFile("syst_root/fit_WS_Kstzero_m_down.root");
  else if(i == 9) f1 = new TFile("syst_root/fit_WS_Kstzero_m_up.root");
  else if(i == 10) f1 = new TFile("syst_root/fit_WS_Kstzero_w_down.root");
  else if(i == 11) f1 = new TFile("syst_root/fit_WS_Kstzero_w_up.root");
  else if(i == 12) f1 = new TFile("syst_root/fit_WS_Kstarm1430_m_down.root");
  else if(i == 13) f1 = new TFile("syst_root/fit_WS_Kstarm1430_m_up.root");
  else if(i == 14) f1 = new TFile("syst_root/fit_WS_Kstarm1430_w_down.root");
  else if(i == 15) f1 = new TFile("syst_root/fit_WS_Kstarm1430_w_up.root");
  else if(i == 16) f1 = new TFile("syst_root/fit_WS_Kstarz1430_m_down.root");
  else if(i == 17) f1 = new TFile("syst_root/fit_WS_Kstarz1430_m_up.root");
  else if(i == 18) f1 = new TFile("syst_root/fit_WS_Kstarz1430_w_down.root");
  else if(i == 19) f1 = new TFile("syst_root/fit_WS_Kstarz1430_w_up.root");
  else if(i == 20) f1 = new TFile("syst_root/fit_WS_Kst2z1430_m_down.root");
  else if(i == 21) f1 = new TFile("syst_root/fit_WS_Kst2z1430_m_up.root");
  else if(i == 22) f1 = new TFile("syst_root/fit_WS_Kst2z1430_w_down.root");
  else if(i == 23) f1 = new TFile("syst_root/fit_WS_Kst2z1430_w_up.root");
  else if(i == 24) f1 = new TFile("syst_root/fit_WS_scale1_down.root");
  else if(i == 25) f1 = new TFile("syst_root/fit_WS_scale1_up.root");
  else if(i == 26) f1 = new TFile("syst_root/fit_WS_scale2_down.root");
  else if(i == 27) f1 = new TFile("syst_root/fit_WS_scale2_up.root");
  else if(i == 28) f1 = new TFile("syst_root/fit_WS_scale3_down.root");
  else if(i == 29) f1 = new TFile("syst_root/fit_WS_scale3_up.root");
  else if(i == 30) f1 = new TFile("syst_root/fit_WS_N1_down.root");
  else if(i == 31) f1 = new TFile("syst_root/fit_WS_N1_up.root");
  else if(i == 32) f1 = new TFile("syst_root/fit_WS_N2_down.root");
  else if(i == 33) f1 = new TFile("syst_root/fit_WS_N2_up.root");
  else if(i == 34) f1 = new TFile("syst_root/fit_WS_Ns_down.root");
  else if(i == 35) f1 = new TFile("syst_root/fit_WS_Ns_up.root");
  else if(i == 36) f1 = new TFile("syst_root/fit_WS_Nmis_down.root");
  else if(i == 37) f1 = new TFile("syst_root/fit_WS_Nmis_up.root");
  else if(i == 38) f1 = new TFile("syst_root/fit_WS_Ncomb_down.root");
  else if(i == 39) f1 = new TFile("syst_root/fit_WS_Ncomb_up.root");
  else if(i == 40) f1 = new TFile("syst_root/fit_WS_err04.root");
  else if(i == 41) f1 = new TFile("syst_root/fit_WS_err06.root");
  else if(i == 42) f1 = new TFile("syst_root/fit_WS_t_small.root");
  else if(i == 43) f1 = new TFile("syst_root/fit_WS_t_wide.root");
  else if(i == 44) f1 = new TFile("syst_root/fit_WS_tau.root");        //is 22
  else if(i == 45) f1 = new TFile("syst_root/fit_WS_t0.root");
  else if(i == 46) f1 = new TFile("syst_root/fit_WS_eff.root");
  else if(i == 47) f1 = new TFile("syst_root/fit_WS_2sigma.root");
  else if(i == 48) f1 = new TFile("syst_root/fit_WS_rho1700.root");
  else if(i == 49) f1 = new TFile("syst_root/fit_WS_LASS.root");
  else if(i == 50) f1 = new TFile("syst_root/fit_WS_comb.root");
  else if(i == 51) f1 = new TFile("syst_root/fit_WS_mD0lim.root");
  else if(i == 52) f1 = new TFile("syst_root/fit_WS_deltaMlim.root");
  else if(i == 53) f1 = new TFile("syst_root/fit_WS_PID.root");
  else assert(0);

  RooFitResult *f = (RooFitResult*)f1->Get("nll");
  return *f;
}

char* getName(Int_t i = -1)
{
  char *name = new char[100];
  if(i == 0) sprintf(name,"$\\Kstarm$ mass");
  else if(i == 1) sprintf(name,"$\\Kstarm$ width");
  else if(i == 2) sprintf(name,"$\\rho$ mass");
  else if(i == 3) sprintf(name,"$\\rho$ width");
  else if(i == 4) sprintf(name,"$\\Kstarz$ mass");
  else if(i == 5) sprintf(name,"$\\Kstarz$ width");
  else if(i == 6) sprintf(name,"$\\Kstarm (1430)$ mass");
  else if(i == 7) sprintf(name,"$\\Kstarm (1430)$ width");
  else if(i == 8) sprintf(name,"$\\Kstarz (1430)$ mass");
  else if(i == 9) sprintf(name,"$\\Kstarz (1430)$ width");
  else if(i == 10) sprintf(name,"$\\Kstarz_{2} (1430)$ mass");
  else if(i == 11) sprintf(name,"$\\Kstarz_{2} (1430)$ width");
  else if(i == 12) sprintf(name,"Resol. scale factor $k_1$");
  else if(i == 13) sprintf(name,"Resol. scale factor $k_2$");
  else if(i == 14) sprintf(name,"Resol. scale factor $k_3$");
  else if(i == 15) sprintf(name,"Resol. fraction $f_1$");
  else if(i == 16) sprintf(name,"Resol. fraction $f_2$");
  else if(i == 17) sprintf(name,"$N_{sig}$");
  else if(i == 18) sprintf(name,"$N_{mis}$");
  else if(i == 19) sprintf(name,"$N_{comb} + N_{\\baddz}$");
  else if(i == 20) sprintf(name,"Lifetime error cut");
  else if(i == 21) sprintf(name,"Lifetime range");
  else if(i == 22) sprintf(name,"Mean \\Dz\\ lifetime");
  else if(i == 23) sprintf(name,"Resol. function offset");
  else if(i == 24) sprintf(name,"Dalitz Plot efficiency");
  else if(i == 25) sprintf(name,"Dalitz model");
  else if(i == 26) sprintf(name,"$\\rho (1700)$ parameters");
  else if(i == 27) sprintf(name,"$LASS WS$");
  else if(i == 28) sprintf(name,"Comb. background");
  else if(i == 29) sprintf(name,"$m_{\\Dz}$ signal region");
  else if(i == 30) sprintf(name,"$\\Delta m$ signal region");
  else if(i == 31) sprintf(name,"Particle Identification");
  else assert(0);

  return name;
}

void makeTable(Float_t syst_matrix[14][14][TOT_syst], Float_t err_std[14])
{
  //we want a Latex table, split for two groups of parameters
  //the first group
  cout << setprecision(3) << endl; 

  for(Int_t i=0;i<TOT_syst;i++){

    cout << "  " << getName(i) << "  ";
    for(Int_t j=0;j<7;j++){

      Float_t syst = sqrt(syst_matrix[j][j][i])/(err_std[j]);
      cout << " &  " << syst << " " ;
    }
    cout << " \\\\ " << endl;
  }
  cout << endl << endl;

  //now the second group
  for(Int_t i=0;i<TOT_syst;i++){

    cout << "  " << getName(i) << "  ";
    for(Int_t j=7;j<14;j++){
      Float_t syst = sqrt(syst_matrix[j][j][i])/(err_std[j]);
      cout << " &  " << syst << " " ;
    }
    cout << " \\\\ " << endl;
  }
  return;
}

void makeTable_TOT(Float_t syst_matrix[14][14], Float_t err_std[14])
{
  cout << setprecision(4) << endl;

  cout << endl << endl << "Total systematics on fit parameters" << endl;
  for(Int_t j=0;j<14;j++){
    Float_t syst = sqrt(syst_matrix[j][j])/err_std[j];
    cout << "   &  " << syst << " " ;
  }
  cout << " \\\\ " << endl;
  return;
}

void makeStatMatrix(Float_t cov_matrix[14][14])
{
  cout << setprecision(2) << endl;

  cout << endl << endl << "Statistical covariance matrix" << endl;
  for(Int_t i=0;i<14;i++){
    for(Int_t j=0;j<14;j++){
    cout << "  &  " << cov_matrix[i][j] << " " ;
  }
  cout << " \\\\ " << endl;
  }
  return;
}

void writeMatrix(Float_t fitmatrix[14][14], Float_t cov_matrix[14][14])
{

  char name[50];
  sprintf(name,"covmatrix.dat");
  ofstream ofs(name);
  if (ofs.fail()){
    cout << "error opening file " << endl;
    assert(0);
  }

  for(Int_t j=0;j<14;j++) {
    for(Int_t k=0;k<14;k++){
      Float_t totmatr = fitmatrix[j][k] + cov_matrix[j][k];
      ofs << totmatr << endl;;
    }
  }
  return;
}

void make_part(Float_t syst_matrix[14][14][TOT_syst], Float_t err_std[14])
{
  cout << setprecision(3) << endl;

  Float_t c1c2_sum[2][2][6];
  Float_t c1c2_corr[6];

  for(Int_t i=0;i<2;i++){
    for(Int_t j=0;j<2;j++){
      for(Int_t k=0;k<6;k++){
	c1c2_sum[i][j][k] = 0.;
	c1c2_corr[k] = 0.;
      }
    }
  }

  for(Int_t i=0;i<TOT_syst;i++){
    if(i<12 || (i>24 && i < 28)) c1c2_sum[0][0][0] += syst_matrix[12][12][i];    //Dalitz model
    if(i<12 || (i>24 && i < 28)) c1c2_sum[1][1][0] += syst_matrix[13][13][i];
    if(i<12 || (i>24 && i < 28)) c1c2_corr[0] += syst_matrix[13][12][i];

    if((i>11 && i < 17) || i == 22 || i == 23) c1c2_sum[0][0][1] += syst_matrix[12][12][i]; //resolution function
    if((i>11 && i < 17) || i == 22 || i == 23) c1c2_sum[1][1][1] += syst_matrix[13][13][i];
    if((i>11 && i < 17) || i == 22 || i == 23) c1c2_corr[1] += syst_matrix[13][12][i];

    if(i == 28) c1c2_sum[0][0][2] += syst_matrix[12][12][i];    //Background model
    if(i == 28) c1c2_sum[1][1][2] += syst_matrix[13][13][i];
    if(i == 28) c1c2_corr[2] += syst_matrix[13][12][i];

    if(i == 17 || i == 18 || i == 19) c1c2_sum[0][0][3] += syst_matrix[12][12][i];  //Signal and background yields
    if(i == 17 || i == 18 || i == 19) c1c2_sum[1][1][3] += syst_matrix[13][13][i];
    if(i == 17 || i == 18 || i == 19) c1c2_corr[3] += syst_matrix[13][12][i];

    if(i == 24) c1c2_sum[0][0][4] += syst_matrix[12][12][i];   //Dalitz plot efficiency
    if(i == 24) c1c2_sum[1][1][4] += syst_matrix[13][13][i];
    if(i == 24) c1c2_corr[4] += syst_matrix[13][12][i];

    if(i == 20 || i == 21 || i == 29 || i == 30) c1c2_sum[0][0][5] += syst_matrix[12][12][i];  //Selection criteria
    if(i == 20 || i == 21 || i == 29 || i == 30) c1c2_sum[1][1][5] += syst_matrix[13][13][i];
    if(i == 20 || i == 21 || i == 29 || i == 30) c1c2_corr[5] += syst_matrix[13][12][i];
  }

  cout << setprecision(3) << endl;

  for(Int_t i=0;i<6;i++){
    Float_t tmp_corr = c1c2_corr[i]/sqrt(c1c2_sum[0][0][i]*c1c2_sum[1][1][i]);
    cout << "   &  " << sqrt(c1c2_sum[0][0][i])/err_std[12] << "   &    "  << sqrt(c1c2_sum[1][1][i])/err_std[13] << "  &  " << tmp_corr << endl;
  }
  return;
}

int main(){

  RooFitResult f1 = getRes();

  RooArgList final_std_list = f1.floatParsFinal();

  Float_t a_std[14];
  a_std[0] = ((RooAbsReal*)final_std_list.find("Kst2z1430_amp"))->getVal();
  a_std[1] = ((RooAbsReal*)final_std_list.find("Kst2z1430_phase"))->getVal();
  a_std[2] = ((RooAbsReal*)final_std_list.find("Kstm1430_amp"))->getVal();
  a_std[3] = ((RooAbsReal*)final_std_list.find("Kstm1430_phase"))->getVal();
  a_std[4] = ((RooAbsReal*)final_std_list.find("Kstminus_amp"))->getVal();
  a_std[5] = ((RooAbsReal*)final_std_list.find("Kstminus_phase"))->getVal();
  a_std[6] = ((RooAbsReal*)final_std_list.find("Kstz1430_amp"))->getVal();
  a_std[7] = ((RooAbsReal*)final_std_list.find("Kstz1430_phase"))->getVal();
  a_std[8] = ((RooAbsReal*)final_std_list.find("Kstzero_amp"))->getVal();
  a_std[9] = ((RooAbsReal*)final_std_list.find("Kstzero_phase"))->getVal();
  a_std[10] = ((RooAbsReal*)final_std_list.find("Rho1700_amp"))->getVal();
  a_std[11] = ((RooAbsReal*)final_std_list.find("Rho1700_phase"))->getVal();
  a_std[12] = ((RooAbsReal*)final_std_list.find("c1"))->getVal();
  a_std[13] = ((RooAbsReal*)final_std_list.find("c2"))->getVal();

  Float_t err_std[14];
  err_std[0] = ((RooRealVar*)final_std_list.find("Kst2z1430_amp"))->getError();
  err_std[1] = ((RooRealVar*)final_std_list.find("Kst2z1430_phase"))->getError();
  err_std[2] = ((RooRealVar*)final_std_list.find("Kstm1430_amp"))->getError();
  err_std[3] = ((RooRealVar*)final_std_list.find("Kstm1430_phase"))->getError();
  err_std[4] = ((RooRealVar*)final_std_list.find("Kstminus_amp"))->getError();
  err_std[5] = ((RooRealVar*)final_std_list.find("Kstminus_phase"))->getError();
  err_std[6] = ((RooRealVar*)final_std_list.find("Kstz1430_amp"))->getError();
  err_std[7] = ((RooRealVar*)final_std_list.find("Kstz1430_phase"))->getError();
  err_std[8] = ((RooRealVar*)final_std_list.find("Kstzero_amp"))->getError();
  err_std[9] = ((RooRealVar*)final_std_list.find("Kstzero_phase"))->getError();
  err_std[10] = ((RooRealVar*)final_std_list.find("Rho1700_amp"))->getError();
  err_std[11] = ((RooRealVar*)final_std_list.find("Rho1700_phase"))->getError();
  err_std[12] = ((RooRealVar*)final_std_list.find("c1"))->getError();
  err_std[13] = ((RooRealVar*)final_std_list.find("c2"))->getError();

  Float_t stat_matrix[14][14];
  Float_t TOT_matrix[14][14];
  Float_t TOT_syst_matrix[14][14];

  for(Int_t j=0;j<14;j++){
    for(Int_t k=0;k<14;k++){
      stat_matrix[j][k] = f1.correlation( *((RooAbsReal*)final_std_list.at(j)) , *((RooAbsReal*)final_std_list.at(k)) )*err_std[j]*err_std[k];
      TOT_matrix[j][k] = stat_matrix[j][k];
      TOT_syst_matrix[j][k] = 0.;
    }
  }

  /*
  TFile f("toynomix_theRes.root");
  RooFitResult *toyres = (RooFitResult*)f.Get("nll");
  RooArgList toy_std_list = toyres->floatParsFinal();
  Float_t toy_std[14];
  toy_std[0] = ((RooAbsReal*)toy_std_list.find("Kst2z1430_amp"))->getVal();
  toy_std[1] = ((RooAbsReal*)toy_std_list.find("Kst2z1430_phase"))->getVal();
  toy_std[2] = ((RooAbsReal*)toy_std_list.find("Kstm1430_amp"))->getVal();
  toy_std[3] = ((RooAbsReal*)toy_std_list.find("Kstm1430_phase"))->getVal();
  toy_std[4] = ((RooAbsReal*)toy_std_list.find("Kstminus_amp"))->getVal();
  toy_std[5] = ((RooAbsReal*)toy_std_list.find("Kstminus_phase"))->getVal();
  toy_std[6] = ((RooAbsReal*)toy_std_list.find("Kstz1430_amp"))->getVal();
  toy_std[7] = ((RooAbsReal*)toy_std_list.find("Kstz1430_phase"))->getVal();
  toy_std[8] = ((RooAbsReal*)toy_std_list.find("Kstzero_amp"))->getVal();
  toy_std[9] = ((RooAbsReal*)toy_std_list.find("Kstzero_phase"))->getVal();
  toy_std[10] = ((RooAbsReal*)toy_std_list.find("Rho1700_amp"))->getVal();
  toy_std[11] = ((RooAbsReal*)toy_std_list.find("Rho1700_phase"))->getVal();
  toy_std[12] = ((RooAbsReal*)toy_std_list.find("c1"))->getVal();
  toy_std[13] = ((RooAbsReal*)toy_std_list.find("c2"))->getVal();

  Float_t err_toy_std[14];
  err_toy_std[0] = ((RooRealVar*)toy_std_list.find("Kst2z1430_amp"))->getError();
  err_toy_std[1] = ((RooRealVar*)toy_std_list.find("Kst2z1430_phase"))->getError();
  err_toy_std[2] = ((RooRealVar*)toy_std_list.find("Kstm1430_amp"))->getError();
  err_toy_std[3] = ((RooRealVar*)toy_std_list.find("Kstm1430_phase"))->getError();
  err_toy_std[4] = ((RooRealVar*)toy_std_list.find("Kstminus_amp"))->getError();
  err_toy_std[5] = ((RooRealVar*)toy_std_list.find("Kstminus_phase"))->getError();
  err_toy_std[6] = ((RooRealVar*)toy_std_list.find("Kstz1430_amp"))->getError();
  err_toy_std[7] = ((RooRealVar*)toy_std_list.find("Kstz1430_phase"))->getError();
  err_toy_std[8] = ((RooRealVar*)toy_std_list.find("Kstzero_amp"))->getError();
  err_toy_std[9] = ((RooRealVar*)toy_std_list.find("Kstzero_phase"))->getError();
  err_toy_std[10] = ((RooRealVar*)toy_std_list.find("Rho1700_amp"))->getError();
  err_toy_std[11] = ((RooRealVar*)toy_std_list.find("Rho1700_phase"))->getError();
  err_toy_std[12] = ((RooRealVar*)toy_std_list.find("c1"))->getError();
  err_toy_std[13] = ((RooRealVar*)toy_std_list.find("c2"))->getError();

  Float_t stat_toy_matrix[14][14];

  for(Int_t j=0;j<14;j++){
    for(Int_t k=0;k<14;k++){
      stat_toy_matrix[j][k] = toyres->correlation( *((RooAbsReal*)toy_std_list.at(j)) , *((RooAbsReal*)toy_std_list.at(k)) )*err_toy_std[j]*err_toy_std[k];
    }
  }
  */

  //create the systematics matrx, the last element is the number of systematics scenarios
  Float_t sys_matrix[14][14][TOT_syst];
  Int_t index = 0;

  //loop over all the systematics and fill the matrix
  for(Int_t i=0;i<numsyst;i++){

    if(i < first_alone && i % 2 != 0) continue;

    RooFitResult fsyst = getRes(i);
    RooArgList final_syst_list = fsyst.floatParsFinal();

    Float_t a_syst[14];
    Float_t a_syst_plus[14];

    a_syst[0] = ((RooAbsReal*)final_syst_list.find("Kst2z1430_amp"))->getVal();
    a_syst[1] = ((RooAbsReal*)final_syst_list.find("Kst2z1430_phase"))->getVal();
    if(i != slot_LASS){
      a_syst[2] = ((RooAbsReal*)final_syst_list.find("Kstm1430_amp"))->getVal();
      a_syst[3] = ((RooAbsReal*)final_syst_list.find("Kstm1430_phase"))->getVal();
      a_syst[6] = ((RooAbsReal*)final_syst_list.find("Kstz1430_amp"))->getVal();
      a_syst[7] = ((RooAbsReal*)final_syst_list.find("Kstz1430_phase"))->getVal();
    }
    else{
      a_syst[2] = a_std[2];
      a_syst[3] = a_std[3];
      a_syst[6] = a_std[6];
      a_syst[7] = a_std[7];
    }
    a_syst[4] = ((RooAbsReal*)final_syst_list.find("Kstminus_amp"))->getVal();
    a_syst[5] = ((RooAbsReal*)final_syst_list.find("Kstminus_phase"))->getVal();
    a_syst[8] = ((RooAbsReal*)final_syst_list.find("Kstzero_amp"))->getVal();
    a_syst[9] = ((RooAbsReal*)final_syst_list.find("Kstzero_phase"))->getVal();
    if(i != slot_rho){
      a_syst[10] = ((RooAbsReal*)final_syst_list.find("Rho1700_amp"))->getVal();
      a_syst[11] = ((RooAbsReal*)final_syst_list.find("Rho1700_phase"))->getVal();
    }
    else{
      a_syst[10] = a_std[10];
      a_syst[11] = a_std[11];
    }
    a_syst[12] = ((RooAbsReal*)final_syst_list.find("c1"))->getVal();
    a_syst[13] = ((RooAbsReal*)final_syst_list.find("c2"))->getVal();
    
    if(i<first_alone){
      RooFitResult fsyst_plus = getRes(i+1);
      RooArgList final_syst_plus_list = fsyst_plus.floatParsFinal();
      a_syst_plus[0] = ((RooAbsReal*)final_syst_plus_list.find("Kst2z1430_amp"))->getVal();
      a_syst_plus[1] = ((RooAbsReal*)final_syst_plus_list.find("Kst2z1430_phase"))->getVal();
      a_syst_plus[2] = ((RooAbsReal*)final_syst_plus_list.find("Kstm1430_amp"))->getVal();
      a_syst_plus[3] = ((RooAbsReal*)final_syst_plus_list.find("Kstm1430_phase"))->getVal();
      a_syst_plus[6] = ((RooAbsReal*)final_syst_plus_list.find("Kstz1430_amp"))->getVal();
      a_syst_plus[7] = ((RooAbsReal*)final_syst_plus_list.find("Kstz1430_phase"))->getVal();
      a_syst_plus[4] = ((RooAbsReal*)final_syst_plus_list.find("Kstminus_amp"))->getVal();
      a_syst_plus[5] = ((RooAbsReal*)final_syst_plus_list.find("Kstminus_phase"))->getVal();
      a_syst_plus[8] = ((RooAbsReal*)final_syst_plus_list.find("Kstzero_amp"))->getVal();
      a_syst_plus[9] = ((RooAbsReal*)final_syst_plus_list.find("Kstzero_phase"))->getVal();
      a_syst_plus[10] = ((RooAbsReal*)final_syst_plus_list.find("Rho1700_amp"))->getVal();
      a_syst_plus[11] = ((RooAbsReal*)final_syst_plus_list.find("Rho1700_phase"))->getVal();
      a_syst_plus[12] = ((RooAbsReal*)final_syst_plus_list.find("c1"))->getVal();
      a_syst_plus[13] = ((RooAbsReal*)final_syst_plus_list.find("c2"))->getVal();
    }
    
    for(Int_t l=0;l<14;l++){
      for(Int_t m=0;m<14;m++){
	if(i<first_alone){
	  sys_matrix[l][m][index] = (a_syst[l] - a_std[l])*(a_syst[m] - a_std[m])/2. + (a_syst_plus[l] - a_std[l])*( a_syst_plus[m] - a_std[m])/2.;
	  TOT_matrix[l][m] += sys_matrix[l][m][index];
	  TOT_syst_matrix[l][m] += sys_matrix[l][m][index];
	}
	else{
	  sys_matrix[l][m][index] = (a_syst[l]-a_std[l])*(a_syst[m]-a_std[m]);
	  TOT_matrix[l][m] += sys_matrix[l][m][index];
	  TOT_syst_matrix[l][m] += sys_matrix[l][m][index];
	}
      }
    }

    index++;
  } //end of loop over the systematics

  //for(Int_t l=0;l<14;l++){
  //  cov_matrix[l][l] += 0.03*0.03*err_std[l]*err_std[l];
  //}

  //statistical covariance matrix
  makeStatMatrix(stat_matrix);
  //systematics covariance matrix
  makeStatMatrix(TOT_syst_matrix);
  //total covariance matrix
  makeStatMatrix(TOT_matrix);

  //summary table of all systematics contributions
  makeTable(sys_matrix,err_std);
  //summary of the sum of all systematics
  makeTable_TOT(TOT_syst_matrix,err_std);

  //write for toy generation
  writeMatrix(stat_matrix,TOT_matrix);
  make_part(sys_matrix,err_std);

  return 0;
}

//  LocalWords:  sprintf
