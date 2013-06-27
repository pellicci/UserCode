#ifndef analysis_H
#define analysis_H

Double_t level[5];
Double_t dmdlevel[5];
Double_t dmslevel[5];
Double_t s2blevel[5];
Double_t c2blevel[5];
Double_t epslevel[5];
Double_t vublevel[5];
Double_t s2bpglevel[5];
Double_t s2alevel[5];
Double_t k2pnnlevel[5];
Double_t gammalevel[5];
Double_t b2taunulevel[5];
Double_t btovglevel[5];
Double_t kl2p0nnlevel[5];
Double_t BtoKpplevel[5];
Double_t area[5];

TH2D * Constrain;
TH2D * dmdConstrain;
TH2D * dmsConstrain;
TH2D * vubConstrain;
TH2D * epsConstrain;
TH2D * s2bConstrain;
TH2D * c2bConstrain;
TH2D * s2bpgConstrain;
TH2D * s2aConstrain;
TH2D * k2pnnConstrain;
TH2D * b2taunuConstrain;
TH2D * gammaConstrain;
TH2D * btovgConstrain;
TH2D * kl2p0nnConstrain;
TH2D * BtoKppConstrain;

TObjArray* s2ahisto1;
TObjArray* s2ahisto2;
TObjArray* s2ahisto3;
TObjArray* s2ahisto4;
TObjArray* s2ahisto5;
TObjArray* s2ahisto6;
TObjArray* s2ahisto;

TObjArray* s2bpghisto1;
TObjArray* s2bpghisto2;
TObjArray* s2bpghisto3;
TObjArray* s2bpghisto4;
TObjArray* s2bpghisto;

//   Vub
double vub2mn;
double vub1mn;
double vub1mx;
double vub2mx;
//   B2taunu
double b2taunu;
double err_b2taunu;
double b2taunu2mn;
double b2taunu1mn;
double b2taunu1mx;
double b2taunu2mx;
//  delta_md  
double dmd;
double err_dmd;
double dmd2mn;
double dmd1mn;
double dmd1mx;
double dmd2mx;
//  Btovg
double btovg2mn;
double btovg1mn;
double btovg1mx;
double btovg2mx;
//  epsilon  
double epsk2mn[3];
double epsk1mn[3]; 
double epsk1mx[3]; 
double epsk2mx[3]; 
//  k2pnn
double k2pnn2mn[3];
double k2pnn1mn[3]; 
double k2pnn1mx[3]; 
double k2pnn2mx[3]; 
//  k2pnn
double kl2p0nns2mn;
double kl2p0nns1mn; 
double kl2p0nns1mx; 
double kl2p0nns2mx; 
//  sen2beta
double sin2b;
double err_sin2b;
double b1s1mn;
double b1s1mx;
double b1s2mn;
double b1s2mx;
double b2s1mn;
double b2s1mx;
double b2s2mn;
double b2s2mx;
//  cos2beta
double cos2b;
double err_cos2b;
double b1s1_c;
double b1s2_c;
//BtoKpp
double rho0CPS;
double BtoKpps2mn;
double BtoKpps2mx;
double BtoKpps1mn;
double BtoKpps1mx;
// D0p0
double b1s1mn_d0p0;
double b1s2mn_d0p0;
double b1s1mx_d0p0;
double b1s2mx_d0p0;
//  gamma
double g1s1mn;
double g1s1mx;
double g1s2mn;
double g1s2mx;

double g1s1mn1;
double g1s1mx1;
double g2s1mn1;
double g2s1mx1;
double g1s1mn2;
double g1s1mx2;
double g2s1mn2;
double g2s1mx2;

double g2s1mn;
double g2s1mx;
double g2s2mn;
double g2s2mx;

// 2alpha
double s2as2;
double s2as1;
TH1D * s2a1D;

// 2bpg
double s2bpgs2;
double s2bpgs1;
TH1D * s2bpg1D;

//  delta_ms  
double dms;
double err_dms;
double dms2mn;
double dms1mn;
double dms1mx;
double dms2mx;

// set
int set_dmd[6];
int set_eps[6];
int set_dms[6];
int set_vub[6];
int set_s2b[6];
int set_c2b[6];
int set_s2bpg[6];
int set_s2a[6];
int set_k2pnn[6];
int set_gamma[6];
int set_b2taunu[6];
int set_btovg[6];
int set_D0p0[6];
int set_kl2p0nn[6];
int set_BtoKpp[6];

int vubsel[6];
int dmdsel[6]; 
int dmssel[6]; 
int epssel[6]; 
int s2bsel[6]; 
int c2bsel[6]; 
int s2bpgsel[6]; 
int s2asel[6];
int k2pnnsel[6];
int gammasel[6];
int b2taunusel[6];
int btovgsel[6];
int D0p0sel[6];
int kl2p0nnsel[6];
int BtoKppsel[6];

int fitnumber;

// arrays for TGraphs
double eta2_eps[200], rho2_eps[200];
double eta1_eps[200], rho1_eps[200];
double eta2m_eps[200], rho2m_eps[200];
double eta1m_eps[200], rho1m_eps[200];

double eta2_k2pnn[400], rho2_k2pnn[400];
double eta1_k2pnn[400], rho1_k2pnn[400];

double eta2_vub[400], rho2_vub[400];
double eta1_vub[400], rho1_vub[400];

double eta2_b2taunu[400], rho2_b2taunu[400];
double eta1_b2taunu[400], rho1_b2taunu[400];

double eta2_dmd[400], rho2_dmd[400];
double eta1_dmd[400], rho1_dmd[400];
double eta2_dms[400], rho2_dms[400];
double eta1_dms[400], rho1_dms[400];

double eta1_s2bpg[200], rho1_s2bpg[200];
double eta2_s2bpg[200], rho2_s2bpg[200];

double eta1_s2a[200], rho1_s2a[200];
double eta2_s2a[200], rho2_s2a[200];

double eta2_btovg[400], rho2_btovg[400];
double eta1_btovg[400], rho1_btovg[400];

TStyle* gStyle;
TCanvas* c1;
TFile* datafile=NULL;
TColor *color[120];
int Palette[20];

TApplication   *theapp=NULL;
int graphic(1),makeps(1),drawtotarea(1), doNP(0), doMFV(0);
int drawtriangle(0), positiveeta(0), zoom(0);
int  s2a_use_his(1), gamma_use_his(1), s2bpg_use_his(1);
int btovg_use_his(1);

string plotname = "etavsrho";
string dirname;
string plotname2;
string dirname2;

TString xlab,ylab;
int col1,col2,logoposition;
int col3,col4,col5;
int smooth(0);
bool lxlab=false,lylab=false;
bool lsquare = false;
bool llogo = true;
bool llines = false;
bool lplot2 = false;

// Bounds for rho vs eta histos
double xmax(1.25),xmin(-1.25),ymax(1.25),ymin(-0.25);
double etamin(-0.25);
int binx(128), biny(128);

void makeCKMplot(string dir);
void makeOtherPlot(TH2D*, TObjArray*, int, int, int);
void plot_rho_eta(string dir);
void tria_tit(int vubt, int dmdt, int epst, int dmst, int s2bt, 
	      int c2bt, int s2bpgt, int s2at, int k2pnnt, int gammat, 
	      int b2taunut, int btovgt, int D0p0t, int kl2p0nnt, int BtoKppt);
void tria(int vubd, int dmdd, int epsd, int dmsd, int s2bd, int c2bd, 
	  int s2bpgd, int s2ad, int k2pnnd, int gammad, int b2taunud, 
	  int btovgd, int D0p0d, int kl2p0nnd, int BtoKppd, char[]);
void sin2b_lines(double bound1, double bound2,int color);
void sin2b_areas(double bound1, double bound2,int color);
////// quando avremo una misura a modo useremo quella sopra pure per il coseno
void cos2b_lines(double bound,int color);
void cos2b_areas(double,double,int, char[]);
void draw_cos2b(double bound, int color);
// porcata?
void D0p0_areas(double beta_min, double beta_max, int color, char side[]);
void D0p0_lines(double beta_min, double beta_max ,int color);
//////
void gamma_lines(double bound1, double bound2,int color);
void gamma_areas(double bound1, double bound2,int color);
////////////////////////
void kl2p0nn_lines(double kl2p0nnsmn, double kl2p0nnsmx, int color);
void kl2p0nn_areas(double kl2p0nnsmn, double kl2p0nnsmx, int color);

void BtoKpp_lines(double bound1, double bound2,int color);
void BtoKpp_areas(double bound1, double bound2,int color);

void makelegend(TObjArray* contour);
void drawgamma(double, double, int);
void drawBtoKpp(double, double, int);
//void drawFromHisto(TH1D*, double, int, char[], int, TString);
TObjArray* CalcGraph(TH1D* Histo, double level1, double level2, TString name);
TObjArray* GraphFromHisto(TH2D*, double, double, double lev3 = 0., double lev4 = 0., double lev5 = 0.);
void drawFromGraph(TObjArray* contour, int ind, char DrawOpt[], int col);
double findLevel(double rho, double eta, TH1D* Histo, TString name);
TGraph* CloseTGraph(TGraph*);

void set_data(string);
void get_data(const char* HistoName, const char* DirName,int DrawOpt);
double Epsk(double rho, int coni);
double K2pnn(double rho, int coni, int sign);
void prepare_epsk();
void prepare_k2pnn();
void prepare_dmd();
void prepare_btovg();
void prepare_dms();
void prepare_Vub();
void prepare_b2taunu();
void prepareopt(int optin[6], int optout[6]);
void drawfunc(double rho[400], double eta[400], int nsind, char[]);
void drawfunc200(double rho[200], double eta[200], int nsind, char[]);
void setdrawlevel(TH2D* Constrain, double level[5], int sel[6], char[]);
void drawcont(TH2D* ThisConstrain, double level[5],int nlevel, int color, char[]);
// void SetPalette(int color);
void SetDefaultPalette(int);
void SetOldPalette();
void DefineColors();
int GetLevel(int);
void DefineColors();
void Read_Parameters(const char* filename);
void Assign_Parameters(map<string, int> data);
void Assign_Parameters(map<string, string> files);
double CalcThreshold(TH1D* Constraint, double level);
double CalcLevel(TH1D* Constraint, double level, char* side);
double CalcLevel_Mediana(TH1D* Constraint, double level, char* side);
TH2D* smooth2D(TH2D*, int, double level[5], int nlevel);

#endif
