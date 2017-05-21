using namespace std;

#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TImage.h>
#include <TColor.h>
#include <TH2D.h>
#include <TDirectory.h>
#include <TLatex.h>
#include <TString.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLine.h>
#include <TApplication.h>
#include "analysis.h"
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TObjArray.h>
#include <TROOT.h>

double Pi = acos(-1.);
double xval=-999,xerr;
double yval=-999,yerr;

int main(int argc, char *argv[]){

  if ( argc<3) {
    cout << "####################################################"   << endl;
    cout << "%2Dplot:                                            "   << endl;
    cout << " - needed parameters                                "   << endl;
    cout << "  'filename' (w/o extension - .root assumed)        "   << endl;
    cout << "  'confname' (w/o extension - .conf assumed)        "   << endl;
    cout << "  'output file name'  (none -> same than conf file) "   << endl;
    cout << endl;
    cout << " e.g. " << endl;
    cout << "  > 2Dplot output analysis outplot               " << endl;
    cout << "    read from file output.root and make the plot " << endl;
    cout << "    as specified in analysis in plots/outplot.eps" << endl;
    cout << endl;
    cout << " you can also plot a single histo giving:        " << endl;
    cout << "  'filename' (w/o extension - .root assumed)     "   << endl;
    cout << "  'plotname' (e.g. sin2b   )                     "   << endl;
    cout << "  'fitname-directory'                            "   << endl;
    cout << "  'output file name'                             "   << endl;
    cout << " - optional parameters                           " << endl;
    cout << "   -xlab=namex  -> x label (default read from histogram)" << endl;
    cout << "   -ylab=namey  -> y label (default 'Probability density')" << endl;
    cout << "   -col1=index  -> color index for the 1 sigma interval" << endl;
    cout << "   -col2=index  -> color index for the 2 sigma interval" << endl;
    cout << "   -logo=position  -> 1=bottom-left(default), 2=top-left" << endl;
    cout << "                      3=top-right,            4=bottom-right" << endl;
    cout << "   --square     -> square shaped canvas" << endl;
    cout << "   --nologo     -> do not plot UTfit logo" << endl;
    cout << "   --drawlines  -> draw contour lines" << endl;
    cout << "   -plot2=nameplot2  -> plot to overimpose" << endl;
    cout << "   -dir2=namedir2  -> dir of the plot to overimpose" << endl;
    cout << "   -col3=index  -> color index for the 1 sigma interval" << endl;
    cout << "   -col4=index  -> color index for the 2 sigma interval" << endl;
    cout << "   -smooth=ntime -> smooth (ntime = number of iterative smoothing)" << endl;
    cout << endl;
    cout << "####################################################"   << endl;

    return 0;  
  }

  TString sfile((const char *)argv[1],strlen(argv[1]));
  TString input_dot_root = sfile + ".root";
  datafile= new TFile(input_dot_root);

  TString conffile((const char *)argv[2],strlen(argv[2]));  
  TString outfile = conffile;

  if(argc == 4 ) {
    const int n = argc -1;
    outfile = TString((const char *)argv[n],strlen(argv[n]));
  }

  if(argc >= 5) {
    const int n = 4;
    outfile = TString((const char *)argv[n],strlen(argv[n]));
  }

  char inputstr[100];
  logoposition=1;
  int other=0;
  if(argc >= 5) {
    plotname = TString((const char *)argv[2],strlen(argv[2]));
    dirname  = TString((const char *)argv[3],strlen(argv[3]));
    for (int i=1;i<argc;i++){
      if (strncmp(argv[i],"-",1)==0){
	if (strncmp(argv[i],"-xval",4)==0) sscanf(argv[i],"-xval=%lf",&xval);
	if (strncmp(argv[i],"-xerr",4)==0) sscanf(argv[i],"-xerr=%lf",&xerr);
	if (strncmp(argv[i],"-yval",4)==0) sscanf(argv[i],"-yval=%lf",&yval);
	if (strncmp(argv[i],"-yerr",4)==0) sscanf(argv[i],"-yerr=%lf",&yerr);
	if (strncmp(argv[i],"-smooth",7)==0) sscanf(argv[i],"-smooth=%d",&smooth);
      }
    }
    graphic = 1;
    makeps = 1;
    other=1;
    col1=2;
    col2=5;
    col3=3;
    col4=4;
    col5=5;
    for (int i=1;i<argc;i++){
      if (strncmp(argv[i],"-xlab",5)==0){
	sscanf(argv[i],"-xlab=%s",inputstr);
	TString sx(inputstr,strlen(inputstr));
	xlab  = sx;
	lxlab = true;
      }
      if (strncmp(argv[i],"-ylab",5)==0){ 
	sscanf(argv[i],"-ylab=%s",inputstr);
	TString sy(inputstr,strlen(inputstr));
	ylab  = sy;
	lylab = true;
      }      
      if (strncmp(argv[i],"-plot2",6)==0){
	sscanf(argv[i],"-plot2=%s",inputstr);
	TString p2(inputstr,strlen(inputstr));
	plotname2  = p2;
	lplot2 = true;
      }
      if (strncmp(argv[i],"-dir2",5)==0){
	sscanf(argv[i],"-dir2=%s",inputstr);
	TString d2(inputstr,strlen(inputstr));
	dirname2  = d2;
      }

      if (strncmp(argv[i],"-col1",5)==0) sscanf(argv[i],"-col1=%d",&col1);
      if (strncmp(argv[i],"-col2",5)==0) sscanf(argv[i],"-col2=%d",&col2);
      if (strncmp(argv[i],"-col3",5)==0) sscanf(argv[i],"-col3=%d",&col3);
      if (strncmp(argv[i],"-col4",5)==0) sscanf(argv[i],"-col4=%d",&col4);
      if (strncmp(argv[i],"-col5",5)==0) sscanf(argv[i],"-col5=%d",&col5);
      if (strncmp(argv[i],"-logo",5)==0) sscanf(argv[i],"-logo=%d",&logoposition);
      if (strncmp(argv[i],"--square",5)==0) lsquare = true;
      if (strncmp(argv[i],"--nologo",8)==0) llogo = false;
      if (strncmp(argv[i],"--drawlines",11)==0) llines = true;
    }
  } else {  
    const int namelenght = strlen(argv[2])+5;
    char filename[namelenght];  
    sprintf(filename,conffile + ".conf");
    Read_Parameters(filename);
    if(zoom!=0) {
      plotname = "zoometavsrho";
      xmax=0.6;
      xmin=0.0;
      ymax=0.6;
      ymin=0.0;
      etamin=0.0;
    }
  }
  
  //gStyle = new TStyle;
  DefineColors();
  SetDefaultPalette(other);
  gStyle->SetOptStat(0);
  gStyle->SetStatColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetFillColor(0);
  gStyle->SetLineWidth(2);
  gStyle->SetOptTitle(0);
  
  if (graphic){
    theapp = new TApplication("app",0,NULL);
  }

  if(zoom != 0 || (doNP ==1 && plotname == "etavsrho") || lsquare) {
    c1 =  new TCanvas("his2D","2D histograms",600,600);
    c1->SetLeftMargin(0.16);
  } else {
    c1 =  new TCanvas("his2D","2D histograms",600,352);
    c1->SetLeftMargin(0.12);
  }

  c1->SetFillColor(0);
  c1->SetBorderMode(0);

  char number[2];
  sprintf(number, "fit%d",fitnumber);
  string dir = number;

  if(plotname == "etavsrho" || (zoom !=0 && plotname == "zoometavsrho")) {
    makeCKMplot(dir);
  } else {
    c1->SetBottomMargin(0.15);
    /////////////////////////////////////////////////////////////////
    // calculate all the TGraphs, that go as argument of makeOtherPlot
    // to move to a subroutine later?????????
    /////////////////////////////////////////////////////////////////
    // get the levels
    get_data(plotname.c_str(),dirname.c_str(),2);
    TH2D* Constrain_1 = Constrain;
    double level68_1 = level[4];
    double level95_1 = level[3];
    double level99_1 = level[2];
    double level999_1 = level[1];
    double level9999_1 = level[0];

    TObjArray* histo_1 = GraphFromHisto(Constrain_1,level68_1,level95_1,level99_1,level999_1,level9999_1);
    TH2D* Constrain_2 = NULL;
    TObjArray* histo_2 = NULL;

    if (lplot2) {
      // get the levels of the second plot
      get_data(plotname2.c_str(),dirname2.c_str(),2);
      Constrain_2 = Constrain;      
      double level68_2 = level[4];
      double level95_2 = level[3];
      histo_2 = GraphFromHisto(Constrain_2,level68_2,level95_2);
    }
    //plot
    if (lplot2) {
      // passing 1, suverimposes lines. But we do it first
      // because we want filled area on top
      makeOtherPlot(Constrain_2,histo_2,1,col3,col4); 
      makeOtherPlot(Constrain_1,histo_1,0,col1,col2);
    } else {
      makeOtherPlot(Constrain_1,histo_1,0,col1,col2);
    }
  }

  if (graphic && !makeps) {
    cout <<"Select Quit ROOT from the menu File to continue " << endl;
    theapp->Run(true);
  }
  if (makeps){
    TString output_dot_eps = "plots/" + outfile + ".eps";
    c1->Print(output_dot_eps);
  }
  if (graphic) c1->Close();
  return 0;
}

void makeCKMplot(string dir) {  
  set_data(dir);
  prepare_epsk();
  prepare_Vub();
  prepare_b2taunu();
  prepare_dmd();
  prepare_dms();
  prepare_k2pnn();
  prepare_btovg();

  plot_rho_eta(dir);
  
  TLatex* tex = new TLatex;
  if(doNP == 1) {
    tex->SetTextSize(0.04);
    if (set_gamma[0]&&set_gamma[5]) tex->DrawLatex( 0.35,1.1, "#gamma");
    tex->SetTextSize(0.03);
    tex->SetTextAlign(22);
    //    if (set_s2b[0]&&set_s2b[5]) tex->DrawLatex(-0.64, 0.70, "sin2#beta");
    if (set_s2b[0]&&set_s2b[5]) tex->DrawLatex(-0.64, 0.70, "#beta");
    if (set_D0p0[0]&&set_D0p0[5]) tex->DrawLatex(-0.64, 1.1, "D^{0}#pi^{0}");
    if (set_c2b[0]&&set_c2b[5]) tex->DrawLatex(1.12, 0.2, "cos2#beta");
    if (set_s2a[0]&&set_s2a[5]) tex->DrawLatex(0.8, -0.5, "#alpha");
    if (set_s2bpg[0]&&set_s2bpg[5]) tex->DrawLatex( 1.1,0.35, "2#beta+#gamma");
    if (set_dms[0]&&set_dms[5]) tex->DrawLatex( 0.29, 0.62, "#frac{#Deltam_{d}}{#Deltam_{s}}");
    if (set_dmd[0]&&set_dmd[5]) tex->DrawLatex( 1.10, 0.73, "#Deltam_{d}");
    if (set_btovg[0]&&set_btovg[5]) {
      if(btovg_use_his == 2)
	tex->DrawLatex( 0.79, 0.72, "BR(B^{0}#rightarrow#rho^{0}#gamma)");
      else
	tex->DrawLatex( 0.79, 0.72, "BR(B#rightarrow#rho/#omega#gamma)");
      tex->DrawLatex( 0.79, 0.58, "BR(B#rightarrowK^{*}#gamma)");
      TLine* Axisratio = new TLine(0.58,0.65,1.00,0.65);
      Axisratio->SetLineWidth(1);
      Axisratio->Draw();
    }
    if (set_eps[0]&&set_eps[5]) tex->DrawLatex(-1., 0.18, "#varepsilon_{K}");
    tex->SetTextSize(0.032);
    if (set_vub[0]&&set_vub[5]) tex->DrawLatex(-0.38,0.14, "#left|#frac{V_{ub}}{V_{cb}}#right|");
    if (set_b2taunu[0]&&set_b2taunu[5]) tex->DrawLatex(-0.38,-0.14, "BR(B#rightarrow#tau#nu)");
  } else {
    tex->SetTextSize(0.055);
    tex->SetTextAlign(22);
    if (set_s2b[0]&&set_s2b[5]) tex->DrawLatex(-0.64, 0.70, "#beta");
    if (set_D0p0[0]&&set_D0p0[5]) tex->DrawLatex(-0.64, 1.1, "D^{0}#pi^{0}");
    if (set_c2b[0]&&set_c2b[5]) tex->DrawLatex(1.12, 0.2, "cos2#beta");
    if (set_s2a[0]&&set_s2a[5]) tex->DrawLatex(.75, 0.28, "#alpha");
    if (set_s2bpg[0]&&set_s2bpg[5]) tex->DrawLatex( 1.05,0.6, "2#beta+#gamma");
    tex->SetTextSize(0.065);
    if (set_gamma[0]&&set_gamma[5]) tex->DrawLatex( 0.05,1.1, "#gamma");
    tex->SetTextSize(0.055);
    if (set_dmd[0]&&set_dmd[5]) tex->DrawLatex( 0.23, 0.86, "#Deltam_{d}");
    if (set_dms[0]&&set_dms[5]) tex->DrawLatex( 1.15, 0.93, "#frac{#Deltam_{d}}{#Deltam_{s}}");
    tex->SetTextSize(0.065);
    if (set_eps[0]&&set_eps[5]) tex->DrawLatex(-0.60, 0.18, "#varepsilon_{K}");
    tex->SetTextSize(0.052);
    if (set_vub[0]&&set_vub[5]) tex->DrawLatex(-0.38,-0.12, "#left|#frac{V_{ub}}{V_{cb}}#right|");
    if (set_b2taunu[0]&&set_b2taunu[5]) tex->DrawLatex(-0.38,-0.14, "BR(B#rightarrow#tau#nu)");
    tex->SetTextSize(0.055);
    if (set_k2pnn[0]&&set_k2pnn[5]) tex->DrawLatex(0.5,1.1,"BR(K^{+}#rightarrow#pi^{+}#nu#bar{#nu})");
    if (set_kl2p0nn[0]&&set_kl2p0nn[5]) tex->DrawLatex(-0.8,0.5,"BR(K_{L}#rightarrow#pi^{0}#nu#bar{#nu})");
    if (set_btovg[0]&&set_btovg[5]) {
      tex->DrawLatex( 0.69, 0.72, "BR(B#rightarrow#rho/#omega#gamma)");
      tex->DrawLatex( 0.69, 0.58, "BR(B#rightarrowK^{*}#gamma)");
      TLine* Axisratio = new TLine(0.48,0.65,0.90,0.65);
      Axisratio->SetLineWidth(1);
      Axisratio->Draw();
    }
  }
  
  if(logoposition!=0) {
    TImage *img = TImage::Open("../common/logo.png");
    img->SetConstRatio(kFALSE);
    double x0 = (doNP == 1 || zoom!=0 ? 0.170 : 0.125);
    double y0 = 0.110;
    if (logoposition==3 || logoposition==4)
      x0 = (doNP == 1 || zoom!=0 ? 0.800 : 0.785); //right part of the plot
    if (logoposition==2 || logoposition==3)
      y0 = (doNP == 1 || zoom!=0 ? 0.820 : 0.770); //top part of the plot
    double x1 = x0+(doNP == 1 || zoom!=0 ? 0.095 : 0.11);
    double y1 = y0+(doNP == 1 || zoom!=0 ? 0.075 : 0.11);
    TPad *pad = new TPad("pad","pad",x0,y0,x1,y1);
    pad->Draw();
    pad->cd();
    img->Draw();
    gPad->Update();
  }
  c1->cd();
  c1->RedrawAxis("same");

  // drawing the triangle
  if(drawtriangle == 1) {
    string rhoplot="rho"+dir;
    string etaplot="eta"+dir;
    double drawrho = ((TH1D*)(((TDirectory*) 
 			       datafile->Get(dir.c_str()))->Get(rhoplot.c_str())))->GetMean();
    double draweta = ((TH1D*)(((TDirectory*) 
 			       datafile->Get(dir.c_str()))->Get(etaplot.c_str())))->GetMean();
    
    double xx[3],yy[3];
    xx[0] = 0.; yy[0] = 0.;
    xx[1] = drawrho; yy[1] = draweta;
    TGraph* Rb = new TGraph(2,xx,yy);
    Rb->SetLineWidth(2);
    Rb->Draw();
    xx[0] = 0.; yy[0] = 0.;
    xx[1] = 1.; yy[1] = 0.;
    TGraph* Rc = new TGraph(2,xx,yy);
    Rc->SetLineWidth(2);
    Rc->Draw();
    xx[0] = 1.; yy[0] = 0.;
    xx[1] = drawrho; yy[1] = draweta;
    TGraph* Rt = new TGraph(2,xx,yy);
    Rt->SetLineWidth(2);
    Rt->Draw();
  }
}

void  plot_rho_eta(string dir) {
  etamin = (doNP == 1 ? -1.25 : -0.25);
  if(zoom != 0) etamin = 0.;

  // calculate s2b contour levels
  if (set_s2b[0] == 1) {
    get_data("s2b","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      s2blevel[ind] = level[ind];
    }
    s2bConstrain = Constrain;
  }

  // calculate c2b contour levels
  if (set_c2b[0] == 1) {
    get_data("c2b","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      c2blevel[ind] = level[ind];
    }
    c2bConstrain = Constrain;
  }

  // calculate dmd contour levels
  if (set_dmd[0] == 1) {
    get_data("dmd","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      dmdlevel[ind] = level[ind];
    }
    dmdConstrain = Constrain;
  }

  // calculate dms contour levels
  if (set_dms[0] == 1) {
    get_data("dms","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      dmslevel[ind] = level[ind];
    }
    dmsConstrain = Constrain;
  }

  // calculate vub contour levels
  if (set_vub[0] == 1) {
    get_data("vub","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      vublevel[ind] = level[ind];
    }
    vubConstrain = Constrain;
  }

  // calculate eps contour levels
  if (set_eps[0] == 1) {
    get_data("epsk","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      epslevel[ind] = level[ind];
    }
    epsConstrain = Constrain;
  }

  // calculate s2bpg contour levels
  if (set_s2bpg[0] == 1) {
    TString s2bpg = "2bpg_all";
    if(s2bpg_use_his == 2) s2bpg = "2bpg_D";
    if(s2bpg_use_his == 3) s2bpg = "2bpg_Dstar";
    if(s2bpg_use_his == 4) s2bpg = "2bpg_Drho";
    get_data(s2bpg,"rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      s2bpglevel[ind] = level[ind];
    }
    s2bpgConstrain = Constrain;
  }

  // calculate s2a  contour levels
  if (set_s2a[0] == 1) {
    TString s2a = "s2a";
    if(s2a_use_his == 2) s2a = "pipi_sin2alpha";
    if(s2a_use_his == 3) s2a = "rhorho_sin2alpha";
    if(s2a_use_his == 4) s2a = "rhopi_sin2alpha";
    get_data(s2a,"rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      s2alevel[ind] = level[ind];
    }
    s2aConstrain = Constrain;
  }

  // calculate k2pnn  contour levels
  if (set_k2pnn[0] == 1) {
    get_data("k2pnn","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      k2pnnlevel[ind] = level[ind];
    }
    k2pnnConstrain = Constrain;
  }

  // calculate gamma contour levels
  if (set_gamma[0] == 1) {
    TString gamma = "gamma_all";
    if(gamma_use_his == 2) gamma = "gamma_GLW";
    if(gamma_use_his == 3) gamma = "gamma_ADS";
    if(gamma_use_his == 4) gamma = "gamma_DAL";
    get_data(gamma,"rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      gammalevel[ind] = level[ind];
    }
    gammaConstrain = Constrain;
  }

  // calculate b2taunu contour levels
  if (set_b2taunu[0] == 1) {
    get_data("b2taunu","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      b2taunulevel[ind] = level[ind];
    }
    b2taunuConstrain = Constrain;
  } 

  // calculate btovg contour levels
  if (set_btovg[0] == 1) {
    get_data("BtoVg","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      btovglevel[ind] = level[ind];
    }
    btovgConstrain = Constrain;
  }

  // calculate kl->p0nn contour levels
  if (set_kl2p0nn[0] == 1) {
    get_data("klp0nn","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      kl2p0nnlevel[ind] = level[ind];
    }
    kl2p0nnConstrain = Constrain;
  }

  // calculate BtoKpp contour levels
  if (set_BtoKpp[0] == 1) {
    get_data("BtoKpp","rhoetahisto",2);
    for(int ind=0; ind<5;ind++) {
      BtoKpplevel[ind] = level[ind];
    }
    BtoKppConstrain = Constrain;
  }

  for (int i = 1; i<6; i++) {
    vubsel[i]     = 0;
    dmdsel[i]     = 0;
    dmssel[i]     = 0;
    epssel[i]     = 0;
    s2bsel[i]     = 0;
    c2bsel[i]     = 0;
    s2bpgsel[i]   = 0;
    s2asel[i]     = 0;
    k2pnnsel[i]   = 0;
    gammasel[i]   = 0;
    b2taunusel[i] = 0;
    btovgsel[i]   = 0;
    D0p0sel[i]    = 0;
    kl2p0nnsel[i] = 0;
    BtoKppsel[i] = 0;
  }

  prepareopt(set_vub, vubsel);
  prepareopt(set_dmd, dmdsel);
  prepareopt(set_dms, dmssel);
  prepareopt(set_s2b, s2bsel);
  prepareopt(set_c2b, c2bsel);
  prepareopt(set_s2bpg, s2bpgsel);
  prepareopt(set_s2a, s2asel);
  prepareopt(set_k2pnn, k2pnnsel);
  prepareopt(set_eps, epssel);
  prepareopt(set_gamma, gammasel);
  prepareopt(set_b2taunu, b2taunusel);
  prepareopt(set_btovg, btovgsel);
  prepareopt(set_D0p0, D0p0sel);
  prepareopt(set_kl2p0nn, kl2p0nnsel);
  prepareopt(set_BtoKpp, BtoKppsel);

  // preliminary plots for 2alpha and 2bpg, if needed

  TH2D* null(0);
  null = new TH2D("null","",128,xmin,xmax,128,etamin,ymax);
  null->SetXTitle("#bar{#rho}");
  null->SetYTitle("#bar{#eta}");
  null->SetTitleSize(0.06,"X");
  null->SetTitleSize(0.06,"Y");
  null->SetTitleOffset(0.7,"X");
  if(zoom!=0) 
    null->SetTitleOffset(1.0,"Y");
  else
    null->SetTitleOffset(0.6,"Y");
    
  null->SetStats(0);
  null->Draw();

  // Draw constraints as areas
  string plot=plotname+dir;
  if(drawtotarea == 1) {
    get_data(plot.c_str(),dir.c_str(),2);
    int sel[6];
    sel[0] = 0;
    sel[1] = 0;
    sel[2] = 0;
    sel[3] = 1;
    sel[4] = 1;
    sel[5] = 1;
  }

  // Draw constraints as lines
  TLine* RefAxis = new TLine(xmin,0.,xmax,0.);
  RefAxis->Draw();
  RefAxis->DrawLine(0.,etamin,0.,ymax);

  if(drawtotarea == 0) {
    get_data(plot.c_str(),dir.c_str(),1);
  }
  null->Draw("same");
  TLine* Bound = new TLine(xmin,ymax,xmax,ymax);
  Bound->Draw();
  Bound->DrawLine(xmax,etamin,xmax,ymax);
}

void BtoKpp_lines(double bound1, double bound2,int color) {    
    
  double xx[3],yy[3];
  xx[0] = rho0CPS;   yy[0] = 0.;
  xx[1] = -2.0; yy[1] = bound1*(xx[1]-rho0CPS);
  TGraph* BtoKpp1 = new TGraph(2,xx,yy);
  BtoKpp1->SetLineColor(color);
  BtoKpp1->Draw();
  xx[1] = -2.0; yy[1] = bound2*(xx[1]-rho0CPS);
  BtoKpp1->DrawGraph(2,xx,yy);
  xx[1] =  4.; yy[1] = bound1*(xx[1]-rho0CPS);
  BtoKpp1->DrawGraph(2,xx,yy);
  xx[1] =  4.; yy[1] = bound2*(xx[1]-rho0CPS);
  BtoKpp1->DrawGraph(2,xx,yy);
}		       

void BtoKpp_areas(double bound1, double bound2,int color) {
     
  double xx[4],yy[4];
  xx[0] = rho0CPS;   yy[0] = 0.;
  yy[1] = -1.25; xx[1] = (yy[1]/bound1)+rho0CPS;
  yy[2] = -1.25; xx[2] = -1.25;
  yy[3] = -1.25; xx[3] = (yy[3]/bound2)+rho0CPS;

  TGraph* BtoKpp1 = new TGraph(4,xx,yy);
  BtoKpp1->SetFillColor(color);
  BtoKpp1->Draw("F");
     
  yy[1] =  1.25; xx[1] = (yy[1]/bound1)+rho0CPS;
  yy[2] =  1.25; xx[2] = 1.25;
  yy[3] =  1.25; xx[3] = (yy[3]/bound2)+rho0CPS;
  BtoKpp1->DrawGraph(4,xx,yy,"F");
 
}
void sin2b_lines(double bound1, double bound2,int color) {    
    
  double xx[3],yy[3];
  xx[0] = 1.;   yy[0] = 0.;
  xx[1] = -2.; yy[1] = 3.0/tan(bound1);
  TGraph* sen2b1 = new TGraph(2,xx,yy);
  sen2b1->SetLineColor(color);
  sen2b1->Draw();
  xx[1] = -2.0; yy[1] = 3.0/tan(bound2);
  sen2b1->DrawGraph(2,xx,yy);
  xx[1] =  4.; yy[1] = -3.0/tan(bound1);
  sen2b1->DrawGraph(2,xx,yy);
  xx[1] =  4.; yy[1] = -3.0/tan(bound2);
  sen2b1->DrawGraph(2,xx,yy);
}		       

void sin2b_areas(double bound1, double bound2,int color) {
     
  double xx[3],yy[3];
  xx[0] = 1.;   yy[0] = 0.;
  xx[1] = -2.0; yy[1] = 3.0/tan(bound1);
  xx[2] = -2.0; yy[2] = 3.0/tan(bound2);

  TGraph* sen2b1 = new TGraph(3,xx,yy);
  sen2b1->SetFillColor(color);
  sen2b1->Draw("F");
     
  xx[1] =  4.; yy[1] = -3.0/tan(bound1);
  xx[2] =  4.; yy[2] = -3.0/tan(bound2);
  sen2b1->DrawGraph(3,xx,yy,"F");
 
}

void gamma_lines(double bound1, double bound2,int color) {    
    
  double xx[3],yy[3];
  xx[0] = 0.;   yy[0] = 0.;
  xx[1] = -2.; yy[1] = -2.0*tan(bound1);
  TGraph* gamma1 = new TGraph(2,xx,yy);
  gamma1->SetLineColor(color);
  gamma1->Draw();
  xx[1] = -2.0; yy[1] = -2.0*tan(bound2);
  gamma1->DrawGraph(2,xx,yy);
  xx[1] =  4.; yy[1] = 4.0*tan(bound1);
  gamma1->DrawGraph(2,xx,yy);
  xx[1] =  4.; yy[1] = 4.0*tan(bound2);
  gamma1->DrawGraph(2,xx,yy);
}		       


void gamma_areas(double bound1, double bound2,int color) {
     
  double xx[3],yy[3];
  xx[0] = 0.;   yy[0] = 0.;
  xx[1] = -2.0/tan(bound1); yy[1] = -2.0;
  xx[2] = -2.0/tan(bound2); yy[2] = -2.0;

  TGraph* gamma1 = new TGraph(3,xx,yy);
  gamma1->SetFillColor(color);
  gamma1->Draw("F");
     
  yy[0] =  4.; xx[0] = 4.0/tan(bound2);
  yy[1] =  4.; xx[1] = 4.0/tan(bound1);
  yy[2] = 0.;  xx[2] = 0.;
    gamma1->DrawGraph(3,xx,yy,"F");
}

void cos2b_lines(double bound,int color) {    
    
  double xx[3],yy[3];
  double twob = acos(-1.)-acos(bound);
  xx[0] = -2.; yy[0] = 3.0/tan(twob/2);
  xx[1] =  1.; yy[1] = 0.;
  xx[2] =  2.; yy[2] = 1.0/tan(twob/2);
  TGraph* sen2b1 = new TGraph(3,xx,yy);
  sen2b1->SetLineColor(color);
  sen2b1->Draw();
  xx[0] = -2.; yy[0] = -3.0/tan(twob/2);
  xx[1] =  1.; yy[1] = 0.;
  xx[2] =  2.; yy[2] = -1.0/tan(twob/2);
  sen2b1->DrawGraph(3,xx,yy);  
}		       

void set_data(string dir) {  
//   Vub
  if(set_vub[0] == 2) {

    TH1D* tmp_vub = (TH1D*) datafile->Get("Input/input_vub");
    double vubOvcb = tmp_vub->GetMean();
    double err_vubOvcb = tmp_vub->GetRMS();

    vub1mn=vubOvcb-err_vubOvcb;
    vub1mx=vubOvcb+err_vubOvcb;
    vub2mn=vubOvcb-2*err_vubOvcb;
    vub2mx=vubOvcb+2*err_vubOvcb;

  }

//  delta_md  
  if(set_dmd[0] == 2) {
    TH1D* tmp_dmd = (TH1D*) datafile->Get("Input/input_dmd")->Clone();

    dmd=tmp_dmd->GetMean();
    err_dmd =tmp_dmd->GetRMS();
    delete tmp_dmd;
    
    dmd1mn=dmd-err_dmd;
    dmd1mx=dmd+err_dmd;
    dmd2mn=dmd-2*err_dmd;
    dmd2mx=dmd+2*err_dmd;
  }
}

// DrawOpt  = 1  ----> Overimpose
// DrawOpt  = 0  ----> Draw in a new Canvas
// DrawOpt !=0,1 ----> Do not Draw

void get_data(const char* HistoName, const char* DirName,int DrawOpt) {
  Constrain = (TH2D*)(((TDirectory*) datafile->Get(DirName))->Get(HistoName))->Clone();
  int nx = Constrain->GetNbinsX();
  int ny = Constrain->GetNbinsY();
  // delete all the underflow and overflow, otherwise fucked root 
  // take them into account in the normalization
  for(int ix = 0; ix <= nx+1; ix++) {
    Constrain->SetCellContent(ix,0,0.);
    Constrain->SetCellContent(ix,ny+1,0.);
  }
  for(int iy = 0; iy <= ny+1; iy++) {
    Constrain->SetCellContent(0,iy,0.);
    Constrain->SetCellContent(nx+1,iy,0.);
  }    
  Double_t Sum = Constrain->GetSum();
  Constrain->Scale(1./Sum);

  for (int ix=1; ix<=nx; ix++) {
    for (int iy=1; iy<=ny; iy++) {
      if ( Constrain->GetCellContent(ix,iy) < 0.00000001 ) {
	Constrain->SetCellContent(ix,iy,0.0000000);
      }
    }
  }

  Sum = Constrain->GetSum();
  Constrain->Scale(1./Sum);

  vector<Double_t> conf; 
  conf.push_back(0.9999);
  conf.push_back(0.999);
  conf.push_back(0.997);
  conf.push_back(0.955);
  conf.push_back(0.683);

  for (int j=0; j<5; j++) {
    level[j] = 0.;
    area[j] = 0.;
  }

  vector< Double_t > OrderedGArray;
  for (int ix=1; ix<=nx; ix++) {
    for (int iy=1; iy<=ny; iy++) {
      OrderedGArray.push_back(Constrain->GetCellContent(ix,iy));
    }
  }

  sort( OrderedGArray.begin(), OrderedGArray.end(),greater<double>() );

  vector< Double_t> SumArray;
  SumArray.push_back(OrderedGArray[0]);
  for (int i=1; i<= (int) OrderedGArray.size(); i++) {
    SumArray.push_back(SumArray[i-1] + OrderedGArray[i]);
    for (int j=0; j<5; j++) {
      if (SumArray[i] <= conf[j]) {
	level[j] = OrderedGArray[i];
	area[j] = SumArray[i];
      }
    }
  }

//  if(DrawOpt == 1 && positiveeta == 1) {
//    for (int ix=1; ix<=nx; ix++) {
//      for (int iy=1; iy<=32; iy++) {
//	Constrain->SetCellContent(ix,iy,Constrain->GetCellContent(ix,65-iy));	
//      }
//    }
//  }

  if(DrawOpt == 1 && positiveeta == 1) {
    for (int ix=1; ix<=nx; ix++) {
      for (int iy=1; iy<=ny; iy++) {
	if(2*iy<ny) 
	  Constrain->SetCellContent(ix,iy,Constrain->GetCellContent(ix,ny-iy));	
      }
    }
  }

  Constrain=smooth2D(Constrain,smooth,level,4);

  for (int j=0; j<5; j++) {
    cout << "level: " << level[j] << endl;
    cout << "area: " << area[j] << endl;
  }

  if (abs(DrawOpt) <= 1 ) {
    Constrain->SetContour(2);
    for (int k=3; k<5 ; k++) {
      int l=k-3;
      Constrain->SetContourLevel(l,level[k]);
    }
    if (DrawOpt == 1) {
      Constrain->SetLineColor(1);
      Constrain->SetLineWidth(2);
      Constrain->Draw("cont3same");
    }
    if (DrawOpt == 0) {
      Constrain->SetLineColor(1);
      Constrain->SetLineWidth(1);
      Constrain->Draw("cont3");
    }
  }
}

double Epsk(double rho, int coni) {
  double x1(-1.),x2,y1,y2(1.),A,B;
  if (coni == 1) {
    y1   = epsk1mx[0];
    x2   = epsk1mx[1];
  }
  if (coni == 2) {
    y1   = epsk2mx[0];
    x2   = epsk2mx[1];
  }
  if (coni == -1) {
    y1   = epsk1mn[0];
    x2   = epsk1mn[1];
  }
  if (coni == -2) {
    y1   = epsk2mn[0];
    x2   = epsk2mn[1];
  }
  
  B = -(1.-y1/y2)/((1.-x2)-y1/y2*(1.-x1));
  A = (y1-y2)/(1./(1+B*(1-x1))-1./(1+B*(1-x2)));

  return A*(1./(1+B*(1-rho)));
}

void prepare_epsk() {
  double lowx(-3.0),upx(1.1);
  double rho;
  for(int i=0; i<100; i++) {
    rho = ((double) i+0.5)/100.*(upx+fabs(lowx))+lowx;
    eta1_eps[i] = Epsk(rho,1);
    rho1_eps[i] = rho;
    eta1m_eps[i] = -Epsk(rho,1);
    rho1m_eps[i] = -rho+2;
  }
  for(int i=100; i<200; i++) {
    rho = upx-((double) i-99.5)/100.*(upx+fabs(lowx));
    eta1_eps[i] = Epsk(rho,-1);
    rho1_eps[i] = rho;
    eta1m_eps[i] = -Epsk(rho,-1);
    rho1m_eps[i] = -rho+2;
  }
  for(int i=0; i<100; i++) {
    rho = ((double) i+0.5)/100.*(upx+fabs(lowx))+lowx;
    eta2_eps[i] = Epsk(rho,2);
    rho2_eps[i] = rho;
    eta2m_eps[i] = -Epsk(rho,2);
    rho2m_eps[i] = -rho+2;
  }
  for(int i=100; i<200; i++) {
    rho = upx-((double) i-99.5)/100.*(upx+fabs(lowx));
    eta2_eps[i] = Epsk(rho,-2);
    rho2_eps[i] = rho;
    eta2m_eps[i] = -Epsk(rho,-2);
    rho2m_eps[i] = -rho+2;
  }  
}

double K2pnn(double eta, int coni, int sign) {
  double brfunc,sigmasq,rho0bar;
  
  if (coni == 1) {
    brfunc   = k2pnn1mx[0];
    sigmasq  = k2pnn1mx[1];
    rho0bar  = k2pnn1mx[2];
  }
  if (coni == 2) {
    brfunc    = k2pnn2mx[0];
    sigmasq   = k2pnn2mx[1];
    rho0bar   = k2pnn2mx[2];
  }
  if (coni == -1) {
    brfunc    = k2pnn1mn[0];
    sigmasq   = k2pnn1mn[1];
    rho0bar   = k2pnn1mn[2];
  }
  if (coni == -2) {
    brfunc    = k2pnn2mn[0];
    sigmasq   = k2pnn2mn[1];
    rho0bar   = k2pnn2mn[2];
  }


  if(brfunc >= sigmasq*pow(eta,2.)) {
    if(sign > 0) 
      return rho0bar + sqrt(brfunc - sigmasq*pow(eta,2.));
    else
      return rho0bar - sqrt(brfunc - sigmasq*pow(eta,2.));
  } else {
    return 1.25;
  }
}
  
void prepare_k2pnn() {
  double lowy,upy(1.25);
  if(doNP==1) 
    lowy=-1.25;
  else
    lowy=-0.25;
    
  double eta;
  for(int i=0; i<100; i++) {
    eta = ((double) i)/99.*(upy-lowy)+lowy;
    rho1_k2pnn[i] = K2pnn(eta,-1,-1);
    eta1_k2pnn[i] = eta;
    rho1_k2pnn[199-i] = K2pnn(eta,-1,1);
    eta1_k2pnn[199-i] = eta;
  }
  for(int i=0; i<100; i++) {
    eta = ((double) i)/99.*(upy-lowy)+lowy;
    rho1_k2pnn[200+i] = K2pnn(eta,1,1);
    eta1_k2pnn[200+i] = eta;
    rho1_k2pnn[399-i] = K2pnn(eta,1,-1);
    eta1_k2pnn[399-i] = eta;
  }

  for(int i=0; i<100; i++) {
    eta = ((double) i)/99.*(upy-lowy)+lowy;
    rho2_k2pnn[i] = K2pnn(eta,-2,-1);
    eta2_k2pnn[i] = eta;
    rho2_k2pnn[199-i] = K2pnn(eta,-2,1);
    eta2_k2pnn[199-i] = eta;
  }

  for(int i=0; i<100; i++) {
    eta = ((double) i)/99.*(upy-lowy)+lowy;
    rho2_k2pnn[200+i] = K2pnn(eta,2,1);
    eta2_k2pnn[200+i] = eta;
    rho2_k2pnn[399-i] = K2pnn(eta,2,-1);
    eta2_k2pnn[399-i] = eta;
  }  
}

////////////////////////////////////////////////////
//   Calculates circles for dmd, corresponding to //
//   dmd mean +/- 1sigma and 2sigma               //
////////////////////////////////////////////////////

void prepare_dmd() {
  double rho;
  // 1 sigma circles
  for(int i=0; i<100; i++) {
    // top quarter of circle, dmd + 1sigma
    rho = (1-dmd1mx)+i*(xmax-(1-dmd1mx))/99.;
    eta1_dmd[i]     =  sqrt(fabs(dmd1mx*dmd1mx-(rho-1)*(rho-1)));
    rho1_dmd[i]     =  rho;
    eta1_dmd[i+200] = -sqrt(fabs(dmd1mx*dmd1mx-(rho-1)*(rho-1)));
    rho1_dmd[i+200] =  rho;
    // top quarter of circle, dmd - 1sigma
    rho = xmax+i*(1-dmd1mn-xmax)/99.;
    eta1_dmd[i+100] =  sqrt(fabs(dmd1mn*dmd1mn-(rho-1)*(rho-1)));
    rho1_dmd[i+100] =  rho;
    eta1_dmd[i+300] = -sqrt(fabs(dmd1mn*dmd1mn-(rho-1)*(rho-1)));
    rho1_dmd[i+300] =  rho;
  }
  // 2 sigmas circles
  for(int i=0; i<100; i++) {
    // top quarter of circle, dmd + 2sigma
    rho = (1-dmd2mx)+i*(xmax-(1-dmd2mx))/99.;
    eta2_dmd[i]     =  sqrt(fabs(dmd2mx*dmd2mx-(rho-1)*(rho-1)));
    rho2_dmd[i]     =  rho;
    eta2_dmd[i+200] = -sqrt(fabs(dmd2mx*dmd2mx-(rho-1)*(rho-1)));
    rho2_dmd[i+200] =  rho;    
    // top quarter of circle, dmd - 2sigma
    rho = xmax+i*(1-dmd2mn-xmax)/99.;
    eta2_dmd[i+100] =  sqrt(fabs(dmd2mn*dmd2mn-(rho-1)*(rho-1)));
    rho2_dmd[i+100] =  rho;
    eta2_dmd[i+300] = -sqrt(fabs(dmd2mn*dmd2mn-(rho-1)*(rho-1)));
    rho2_dmd[i+300] =  rho;
  }
}

////////////////////////////////////////////////
//   Calculates circle for dms, corresponding //
//   to dms mean + 2sigma                     //
////////////////////////////////////////////////

void prepare_dms() {
  double rho;
  // 1 sigma circles
  for(int i=0; i<100; i++) {
    // top quarter of circle, dms + 1sigma
    rho = (1-dms1mx)+i*(xmax-(1-dms1mx))/99.;
    eta1_dms[i]     =  sqrt(fabs(dms1mx*dms1mx-(rho-1)*(rho-1)));
    rho1_dms[i]     =  rho;
    eta1_dms[i+200] = -sqrt(fabs(dms1mx*dms1mx-(rho-1)*(rho-1)));
    rho1_dms[i+200] =  rho;
    // top quarter of circle, dms - 1sigma
    rho = xmax+i*(1-dms1mn-xmax)/99.;
    eta1_dms[i+100] =  sqrt(fabs(dms1mn*dms1mn-(rho-1)*(rho-1)));
    rho1_dms[i+100] =  rho;
    eta1_dms[i+300] = -sqrt(fabs(dms1mn*dms1mn-(rho-1)*(rho-1)));
    rho1_dms[i+300] =  rho;
  }
  // 2 sigmas circles
  for(int i=0; i<100; i++) {
    // top quarter of circle, dms + 2sigma
    rho = (1-dms2mx)+i*(xmax-(1-dms2mx))/99.;
    eta2_dms[i]     =  sqrt(fabs(dms2mx*dms2mx-(rho-1)*(rho-1)));
    rho2_dms[i]     =  rho;
    eta2_dms[i+200] = -sqrt(fabs(dms2mx*dms2mx-(rho-1)*(rho-1)));
    rho2_dms[i+200] =  rho;    
    if(doMFV!=0) {
    // top quarter of circle, dms - 2sigma
      rho = xmax+i*(1-dms2mn-xmax)/99.;
      eta2_dms[i+100] =  sqrt(fabs(dms2mn*dms2mn-(rho-1)*(rho-1)));
      rho2_dms[i+100] =  rho;
      eta2_dms[i+300] = -sqrt(fabs(dms2mn*dms2mn-(rho-1)*(rho-1)));
      rho2_dms[i+300] =  rho;
    } else {
    // top quarter of circle, dmd - 2sigma
      rho = xmax+i*(1-dmd2mn-xmax)/99.;
      eta2_dms[i+100] =  sqrt(fabs(dmd2mn*dmd2mn-(rho-1)*(rho-1)));
      rho2_dms[i+100] =  rho;
      eta2_dms[i+300] = -sqrt(fabs(dmd2mn*dmd2mn-(rho-1)*(rho-1)));
      rho2_dms[i+300] =  rho;
    }
  }
}
//////////////////////////////////////////////////////
//   Calculates circles for btovg, corresponding to //
//   btovg mean +/- 1sigma and 2sigma               //
//////////////////////////////////////////////////////

void prepare_btovg() {
  double rho;
  // 1 sigma circles
  for(int i=0; i<100; i++) {
    // top quarter of circle, btovg + 1sigma
    rho = (1-btovg1mx)+i*(xmax-(1-btovg1mx))/99.;
    eta1_btovg[i]     =  sqrt(fabs(btovg1mx*btovg1mx-(rho-1)*(rho-1)));
    eta1_btovg[i+200] = -sqrt(fabs(btovg1mx*btovg1mx-(rho-1)*(rho-1)));
    if(rho > xmax) rho = xmax;
    if(rho < xmin) rho = xmin;
    rho1_btovg[i]     =  rho;
    rho1_btovg[i+200] =  rho;
    // top quarter of circle, btovg - 1sigma
    rho = xmax+i*(1-btovg1mn-xmax)/99.;
    eta1_btovg[i+100] =  sqrt(fabs(btovg1mn*btovg1mn-(rho-1)*(rho-1)));
    eta1_btovg[i+300] = -sqrt(fabs(btovg1mn*btovg1mn-(rho-1)*(rho-1)));
    if(rho > xmax) rho = xmax;
    if(rho < xmin) rho = xmin;
    rho1_btovg[i+100] =  rho;
    rho1_btovg[i+300] =  rho;
  }
  // 2 sigmas circles
  for(int i=0; i<100; i++) {
    // top quarter of circle, btovg + 2sigma
    rho = (1-btovg2mx)+i*(xmax-(1-btovg2mx))/99.;
    if(btovg2mx*btovg2mx-(rho-1)*(rho-1) >= 0.) {
      eta2_btovg[i]     =  sqrt(btovg2mx*btovg2mx-(rho-1)*(rho-1));
      eta2_btovg[i+200] = -sqrt(btovg2mx*btovg2mx-(rho-1)*(rho-1));
    } else {
      eta2_btovg[i]     =  0.;
      eta2_btovg[i+200] =  0.;
    }      
    if(rho > xmax) rho = xmax;
    if(rho < xmin) rho = xmin;
    rho2_btovg[i]     =  rho;
    rho2_btovg[i+200] =  rho;    
    // top quarter of circle, btovg - 2sigma
    rho = xmax+i*(1-btovg2mn-xmax)/99.;
    if(btovg2mn*btovg2mn-(rho-1)*(rho-1) >= 0.) {
      eta2_btovg[i+100] =  sqrt(btovg2mn*btovg2mn-(rho-1)*(rho-1));
      eta2_btovg[i+300] = -sqrt(btovg2mn*btovg2mn-(rho-1)*(rho-1));
    } else {
      eta2_btovg[i+100] = 0.;
      eta2_btovg[i+300] = 0.;
    }
    if(rho > xmax) rho = xmax;   
    if(rho < xmin) rho = xmin;
    rho2_btovg[i+100] =  rho;
    rho2_btovg[i+300] =  rho;

  }
}

////////////////////////////////////////////////////
//   Calculates circles for B2taunu, corresponding to //
//   B2taunu mean +/- 1sigma and 2sigma               //
////////////////////////////////////////////////////

void prepare_b2taunu() {
  double rho;
  // 1 sigma circles
  for(int i=0; i<100; i++) {
    // top half circle, B2taunu + 1sigma
    rho = -b2taunu1mx+i*2*b2taunu1mx/99.;
    eta1_b2taunu[i] = sqrt(fabs(b2taunu1mx*b2taunu1mx-rho*rho));
    rho1_b2taunu[i] = rho;
    // bottom half circle, B2taunu + 1sigma
    rho = b2taunu1mx-i*2*b2taunu1mx/99.;
    eta1_b2taunu[i+100] = -sqrt(fabs(b2taunu1mx*b2taunu1mx-rho*rho));
    rho1_b2taunu[i+100] = rho;
    // top half circle, B2taunu - 1sigma
    rho = -b2taunu1mn+i*2*b2taunu1mn/99.;
    eta1_b2taunu[i+200] = sqrt(fabs(b2taunu1mn*b2taunu1mn-rho*rho));
    rho1_b2taunu[i+200] = rho;
    // bottom half circle, B2taunu - 1sigma
    rho = b2taunu1mn-i*2*b2taunu1mn/99.;
    eta1_b2taunu[i+300] = -sqrt(fabs(b2taunu1mn*b2taunu1mn-rho*rho));
    rho1_b2taunu[i+300] = rho;
  }

  // 2 sigma circles
  for(int i=0; i<100; i++) {
    // top half circle, B2taunu + 2sigma
    rho = -b2taunu2mx+i*2*b2taunu2mx/99.;
    eta2_b2taunu[i] = sqrt(fabs(b2taunu2mx*b2taunu2mx-rho*rho));
    rho2_b2taunu[i] = rho;
    // bottom half circle, B2taunu + 2sigma
    rho = b2taunu2mx-i*2*b2taunu2mx/99.;
    eta2_b2taunu[i+100] = -sqrt(fabs(b2taunu2mx*b2taunu2mx-rho*rho));
    rho2_b2taunu[i+100] = rho;
    // top half circle, B2taunu - 2sigma
    rho = -b2taunu2mn+i*2*b2taunu2mn/99.;
    eta2_b2taunu[i+200] = sqrt(fabs(b2taunu2mn*b2taunu2mn-rho*rho));
    rho2_b2taunu[i+200] = rho;
    rho = b2taunu2mn-i*2*b2taunu2mn/99.;
    // bottom half circle, B2taunu - 2sigma
    eta2_b2taunu[i+300] = -sqrt(fabs(b2taunu2mn*b2taunu2mn-rho*rho));
    rho2_b2taunu[i+300] = rho;
  }
}

////////////////////////////////////////////////////
//   Calculates circles for Vub, corresponding to //
//   Vub mean +/- 1sigma and 2sigma               //
////////////////////////////////////////////////////

void prepare_Vub() {
  double rho;
  // 1 sigma circles
  for(int i=0; i<100; i++) {
    // top half circle, Vub + 1sigma
    rho = -vub1mx+i*2*vub1mx/99.;
    eta1_vub[i] = sqrt(fabs(vub1mx*vub1mx-rho*rho));
    rho1_vub[i] = rho;
    // bottom half circle, Vub + 1sigma
    rho = vub1mx-i*2*vub1mx/99.;
    eta1_vub[i+100] = -sqrt(fabs(vub1mx*vub1mx-rho*rho));
    rho1_vub[i+100] = rho;
    // top half circle, Vub - 1sigma
    rho = -vub1mn+i*2*vub1mn/99.;
    eta1_vub[i+200] = sqrt(fabs(vub1mn*vub1mn-rho*rho));
    rho1_vub[i+200] = rho;
    // bottom half circle, Vub - 1sigma
    rho = vub1mn-i*2*vub1mn/99.;
    eta1_vub[i+300] = -sqrt(fabs(vub1mn*vub1mn-rho*rho));
    rho1_vub[i+300] = rho;
  }

  // 2 sigma circles
  for(int i=0; i<100; i++) {
    // top half circle, Vub + 2sigma
    rho = -vub2mx+i*2*vub2mx/99.;
    eta2_vub[i] = sqrt(fabs(vub2mx*vub2mx-rho*rho));
    rho2_vub[i] = rho;
    // bottom half circle, Vub + 2sigma
    rho = vub2mx-i*2*vub2mx/99.;
    eta2_vub[i+100] = -sqrt(fabs(vub2mx*vub2mx-rho*rho));
    rho2_vub[i+100] = rho;
    // top half circle, Vub - 2sigma
    rho = -vub2mn+i*2*vub2mn/99.;
    eta2_vub[i+200] = sqrt(fabs(vub2mn*vub2mn-rho*rho));
    rho2_vub[i+200] = rho;
    rho = vub2mn-i*2*vub2mn/99.;
    // bottom half circle, Vub - 2sigma
    eta2_vub[i+300] = -sqrt(fabs(vub2mn*vub2mn-rho*rho));
    rho2_vub[i+300] = rho;
  }
}

void prepareopt(int optin[6], int optout[6]) {
  if (optin[1] && optin[1]< 10) {
    optout[optin[1]-1] = 300+optin[2];
  }
  if (optin[1] == 12) {
    optout[0] = 300+optin[2];//+1;
    optout[1] = 300+optin[2];
  }
  if (optin[1] == 23) {
    optout[1] = 300+optin[2]+1;
    optout[2] = 300+optin[2];
  }
  if (optin[1] == 123) {
    optout[0] = 300+optin[2]+1;
    optout[1] = 300+optin[2];
    optout[2] = 300+optin[2]+2;
  }

  int color = 300+optin[4];
  //if(optin[0] == 1) color = GetLevel(300+optin[4]);

  if (optin[3] && optin[3]< 10) {
    optout[optin[3]+2] = color;
  }
  if (optin[3] == 12) {
    optout[3] = color+1;
    optout[4] = color;
  }
  if (optin[3] == 23) {
    optout[4] = color+1;
    optout[5] = color;
  }
  if (optin[3] == 123) {
    optout[3] = color+1;
    optout[4] = color;
    optout[5] = color+2;
  }
}

//////////////////////////////////////////////////
//   given a rho vs eta histo and a level on z  //    
//     coordinate, returns the region having    //
//   z > level. It can be used to get 1sigma    //
//   or 2sigma region for not analitical bounds //
//////////////////////////////////////////////////

void SetDefaultPalette(int other) {

  for(int i=0;i<20;i++) {
    Palette[i] = 0;
  }
  if (other==0) {
    Palette[1] = 300+set_vub[4];
    Palette[2] = 300+set_dmd[4];
    Palette[3] = 300+set_eps[4];
    Palette[4] = 300+set_dms[4];
    Palette[5] = 300+set_s2b[4];
    Palette[6] = 300+set_s2bpg[4];
    Palette[7] = 300+set_s2a[4];
    Palette[8] = 300+set_k2pnn[4];
    Palette[9] = 300+set_gamma[4];
    Palette[10]= 300+set_c2b[4]; 

    Palette[11] = 300+set_vub[4]+1;
    Palette[12] = 300+set_dmd[4]+1;
    Palette[13] = 300+set_eps[4]+1;
    Palette[14] = 300+set_dms[4]+1;
    Palette[15] = 300+set_s2b[4]+1;
    Palette[16] = 300+set_s2bpg[4]+1;
    Palette[17] = 300+set_s2a[4]+1;
    Palette[18] = 300+set_k2pnn[4]+1;
    Palette[19] = 300+set_gamma[4]+1;
    
    // for 123 plots
    //Palette[17] = 8; // green  = 99%
    //Palette[18] = 5; // yellow = 95%
    //Palette[19] = 2; // red    = 68%
    //Palette[18] = 14; // grey   = 95%
    //Palette[19] = 4; // blue    = 68%
    //Palette[18] = 398; // customized   = 95%
    //Palette[19] = 399; // customized   = 68%
  } else {    
    Palette[1] = 1;
    Palette[2] = 2;
    Palette[3] = 3;
    Palette[4] = 4;
    Palette[5] = 5;
    Palette[6] = 6;
    Palette[7] = 7;
    Palette[8] = 8;
    Palette[9] = 9;
    Palette[10]= 390;
    Palette[11] = 391;
    Palette[12] = 392;
    Palette[13] = 393;
    Palette[14] = 394;
    Palette[15] = 395;
    Palette[16] = 396;
    Palette[17] = 397;
    Palette[18] = 398;
    Palette[19] = 399;
    
    // for 123 plots
    //Palette[17] = 8; // green  = 99%
    //Palette[18] = 5; // yellow = 95%
    //Palette[19] = 2; // red    = 68%
    //Palette[18] = 14; // grey   = 95%
    //Palette[19] = 4; // blue    = 68%
    //Palette[18] = 398; // customized   = 95%
    //Palette[19] = 399; // customized   = 68%
  }
  gStyle->SetPalette(20,Palette);
}

void SetOldPalette() {
   for(int i=0;i<20;i++) {
    Palette[i] = i;
  }
   gStyle->SetPalette(20,Palette);
}


int GetLevel(int indcol) {
  for(int i=0;i<20;i++) {
    if (Palette[i] == indcol)
      return i;
  }
  return 0;
}

void Read_Parameters(const char* filename) {
  char buffer[256];  
  ifstream reader (filename);
  map<string, int> data; 
  map<string, string> files; 
  string label, equal, svalue;
  char cvalue[40];
  int value;
  
  if ( ! reader.is_open())
    { cout << "Error opening file"; exit (1); }
  
  while ( reader.getline (buffer,256) ) {
    istringstream i(buffer);
    i >> label
      >> equal
      >> cvalue;
    if (equal == "=") {
      value = atoi(cvalue);
      data[label] = value;
    } else if (equal == "==") {
      svalue = (string) cvalue;
      files[label] = svalue;
    }
    equal = "";
  }
  map<string, int>::const_iterator iter;
  for (iter=data.begin(); iter != data.end(); iter++) {
    cout << iter->first << " " << iter->second << endl;
  }
  
  Assign_Parameters(data);
  //  Assign_Parameters(files);
  
  return;
}

void Assign_Parameters(map<string, string> files) {
  // not used yet... but it'here if we need it
  plotname   = files["plotname"];
  dirname   = files["dirname"];
}

void Assign_Parameters(map<string, int> data) {
  
  graphic       = data["interactive_root_window"];
  makeps        = data["create_output_file"];
  drawtotarea   = data["draw_total_area_color"];
  logoposition  = data["logo_position"];
  positiveeta   = data["positiveeta"];
  fitnumber     = data["fitnumber"];
  s2a_use_his   = data["s2a_use_his"];
  gamma_use_his = data["gamma_use_his"];
  s2bpg_use_his = data["s2bpg_use_his"];
  btovg_use_his = data["btovg_use_his"];
  drawtriangle  = data["drawtriangle"];
  doNP          = data["doNP"];
  doMFV         = data["doMFV"];
  zoom          = data["zoom"];
  smooth        = data["smooth"];

  set_dmd[0]  = data["dmd_draw_const"];
  set_dmd[1]  = data["dmd_sigma_line"];
  set_dmd[2]  = data["dmd_color_line"];
  set_dmd[3]  = data["dmd_sigma_area"];
  set_dmd[4]  = data["dmd_color_area"];
  set_dmd[5]  = data["dmd_draw_title"];
  set_eps[0]  = data["eps_draw_const"];
  set_eps[1]  = data["eps_sigma_line"];
  set_eps[2]  = data["eps_color_line"];
  set_eps[3]  = data["eps_sigma_area"];
  set_eps[4]  = data["eps_color_area"];
  set_eps[5]  = data["eps_draw_title"];
  set_dms[0]  = data["dms_draw_const"];
  set_dms[1]  = data["dms_sigma_line"];
  set_dms[2]  = data["dms_color_line"];
  set_dms[3]  = data["dms_sigma_area"];
  set_dms[4]  = data["dms_color_area"];
  set_dms[5]  = data["dms_draw_title"];
  set_vub[0]  = data["vub_draw_const"];
  set_vub[1]  = data["vub_sigma_line"];
  set_vub[2]  = data["vub_color_line"];
  set_vub[3]  = data["vub_sigma_area"];
  set_vub[4]  = data["vub_color_area"];
  set_vub[5]  = data["vub_draw_title"];
  set_s2b[0]  = data["s2b_draw_const"];
  set_s2b[1]  = data["s2b_sigma_line"];
  set_s2b[2]  = data["s2b_color_line"];
  set_s2b[3]  = data["s2b_sigma_area"];
  set_s2b[4]  = data["s2b_color_area"];
  set_s2b[5]  = data["s2b_draw_title"];
  set_c2b[0]  = data["c2b_draw_const"];
  set_c2b[1]  = data["c2b_sigma_line"];
  set_c2b[2]  = data["c2b_color_line"];
  set_c2b[3]  = data["c2b_sigma_area"];
  set_c2b[4]  = data["c2b_color_area"];
  set_c2b[5]  = data["c2b_draw_title"];
  set_s2bpg[0] = data["s2bpg_draw_const"];
  set_s2bpg[1] = data["s2bpg_sigma_line"];
  set_s2bpg[2] = data["s2bpg_color_line"];
  set_s2bpg[3] = data["s2bpg_sigma_area"];
  set_s2bpg[4] = data["s2bpg_color_area"];
  set_s2bpg[5] = data["s2bpg_draw_title"];
  set_s2a[0] = data["s2a_draw_const"];
  set_s2a[1] = data["s2a_sigma_line"];
  set_s2a[2] = data["s2a_color_line"];
  set_s2a[3] = data["s2a_sigma_area"];
  set_s2a[4] = data["s2a_color_area"];
  set_s2a[5] = data["s2a_draw_title"];
  set_k2pnn[0] = data["k2pnn_draw_const"];
  set_k2pnn[1] = data["k2pnn_sigma_line"];
  set_k2pnn[2] = data["k2pnn_color_line"];
  set_k2pnn[3] = data["k2pnn_sigma_area"];
  set_k2pnn[4] = data["k2pnn_color_area"];
  set_k2pnn[5] = data["k2pnn_draw_title"];
  set_gamma[0] = data["gamma_draw_const"];
  set_gamma[1] = data["gamma_sigma_line"];
  set_gamma[2] = data["gamma_color_line"];
  set_gamma[3] = data["gamma_sigma_area"];
  set_gamma[4] = data["gamma_color_area"];
  set_gamma[5] = data["gamma_draw_title"];
  set_b2taunu[0] = data["b2taunu_draw_const"];
  set_b2taunu[1] = data["b2taunu_sigma_line"];
  set_b2taunu[2] = data["b2taunu_color_line"];
  set_b2taunu[3] = data["b2taunu_sigma_area"];
  set_b2taunu[4] = data["b2taunu_color_area"];
  set_b2taunu[5] = data["b2taunu_draw_title"];
  set_btovg[0]  = data["btovg_draw_const"];
  set_btovg[1]  = data["btovg_sigma_line"];
  set_btovg[2]  = data["btovg_color_line"];
  set_btovg[3]  = data["btovg_sigma_area"];
  set_btovg[4]  = data["btovg_color_area"];
  set_btovg[5]  = data["btovg_draw_title"];
  set_D0p0[0]  = data["D0p0_draw_const"];
  set_D0p0[1]  = data["D0p0_sigma_line"];
  set_D0p0[2]  = data["D0p0_color_line"];
  set_D0p0[3]  = data["D0p0_sigma_area"];
  set_D0p0[4]  = data["D0p0_color_area"];
  set_D0p0[5]  = data["D0p0_draw_title"];
  set_kl2p0nn[0] = data["kl2p0nn_draw_const"];
  set_kl2p0nn[1] = data["kl2p0nn_sigma_line"];
  set_kl2p0nn[2] = data["kl2p0nn_color_line"];
  set_kl2p0nn[3] = data["kl2p0nn_sigma_area"];
  set_kl2p0nn[4] = data["kl2p0nn_color_area"];
  set_kl2p0nn[5] = data["kl2p0nn_draw_title"];
  set_BtoKpp[0] = data["BtoKpp_draw_const"];
  set_BtoKpp[1] = data["BtoKpp_sigma_line"];
  set_BtoKpp[2] = data["BtoKpp_color_line"];
  set_BtoKpp[3] = data["BtoKpp_sigma_area"];
  set_BtoKpp[4] = data["BtoKpp_color_area"];
  set_BtoKpp[5] = data["BtoKpp_draw_title"];
}

void DefineColors() {
  color[0]  = new TColor(300, 1.0, 1.0, 1.0, "");
  color[1]  = new TColor(301, 0.0, 0.0, 0.0, "");
  color[11] = new TColor(311, 0.6, 0.4, 1.0, "");
  color[12] = new TColor(312, 1.0, 0.5, 0.5, "");
  color[13] = new TColor(313, 0.5, 1.0, 0.4, "");
  color[14] = new TColor(314, 0.8, 0.6, 1.0, "");
  color[15] = new TColor(315, 1.0, 0.90, 0.82, ""); 
  color[16] = new TColor(316, 1.0, 0.75, 0.67, "");
  color[17] = new TColor(317, 0.5, 1.0, 0.5, "");
  //  color[18] = new TColor(318, 0.95, 1.0, 1.0, "");
  //  color[19] = new TColor(319, 0.7, 1.0, 0.8, "");

  color[18] = new TColor(318, 0.95, 1.0, 1.0, "");
  color[19] = new TColor(319, 0.7, 1.0, 0.8, "");

  //  color[18] = new TColor(318, 0.85, 1.0, 0.90, "");
  //  color[19] = new TColor(319, 0.57, 1.0, 0.62, "");
  color[20] = new TColor(320, 0.97, 0.87, 0.97, "");
  color[21] = new TColor(321, 0.85, 0.44, 0.84, "");
  color[22] = new TColor(322, 0.73, 0.33, 0.83, "");
  color[23] = new TColor(323, 0.60, 0.20, 0.80, "");
  color[24] = new TColor(324, 0.58, 0.00, 0.83, "");
  color[25] = new TColor(325, 0.54, 0.17, 0.89, "");
  color[26] = new TColor(326, 0.63, 0.13, 0.94, "");
  color[27] = new TColor(327, 0.58, 0.44, 0.86, "");
  color[28] = new TColor(328, 0.95, 0.85, 0.95, "");
  color[29] = new TColor(329, 0.93, 0.51, 0.93, "");
  color[30] = new TColor(330, 1.00, 0.98, 0.98, "");      
  color[31] = new TColor(331, 0.97, 0.97, 1.00, "");
  color[32] = new TColor(332, 1.00, 1.00, 1.00, ""); 
  color[33] = new TColor(333, 0.52, 0.44, 1.00, ""); 
  color[34] = new TColor(334, 0.12, 0.56, 1.00, "");
  color[35] = new TColor(335, 0.00, 0.75, 1.00, "");
  color[36] = new TColor(336, 0.88, 1.00, 1.00, "");
  color[37] = new TColor(337, 0.37, 0.62, 0.63, "");
  color[38] = new TColor(338, 0.40, 0.80, 0.67, "");
  color[39] = new TColor(339, 0.50, 1.00, 0.83, "");
  color[40] = new TColor(340, 0.00, 0.39, 0.00, "");
  color[41] = new TColor(341, 0.33, 0.42, 0.18, "");
  color[42] = new TColor(342, 0.56, 0.74, 0.56, "");
  color[43] = new TColor(343, 0.18, 0.55, 0.34, "");
  color[44] = new TColor(344, 0.24, 0.70, 0.44, "");
  color[45] = new TColor(345, 0.13, 0.70, 0.67, "");
  color[46] = new TColor(346, 0.60, 0.98, 0.60, "");
  color[47] = new TColor(347, 0.00, 1.00, 0.50, "");
  color[48] = new TColor(348, 0.49, 0.99, 0.00, "");
  color[49] = new TColor(349, 0.00, 1.00, 0.00, "");
  color[50] = new TColor(350, 0.50, 1.00, 0.00, "");
  color[51] = new TColor(351, 0.00, 0.98, 0.60, "");
  color[52] = new TColor(352, 0.68, 1.00, 0.18, "");
  color[53] = new TColor(353, 0.20, 0.80, 0.20, "");
  color[54] = new TColor(354, 0.60, 0.80, 0.20, "");
  color[55] = new TColor(355, 0.13, 0.55, 0.13, "");
  color[56] = new TColor(356, 0.42, 0.56, 0.14, "");
  color[57] = new TColor(357, 0.74, 0.72, 0.42, "");
  color[58] = new TColor(358, 0.94, 0.90, 0.55, "");
  color[59] = new TColor(359, 0.93, 0.91, 0.67, "");
  color[60] = new TColor(360, 0.99, 0.99, 0.75, "");
  color[61] = new TColor(361, 1.00, 0.70, 0.00, "");
  color[62] = new TColor(362, 1.00, 1.00, 0.00, "");
  color[63] = new TColor(363, 1.00, 0.84, 0.00, "");
  color[64] = new TColor(364, 1.00, 0.95, 0.60, "");
  color[65] = new TColor(365, 0.85, 0.65, 0.13, "");
  color[66] = new TColor(366, 0.72, 0.53, 0.04, "");
  color[67] = new TColor(367, 0.74, 0.56, 0.56, "");
  color[68] = new TColor(368, 0.80, 0.36, 0.36, "");
  color[69] = new TColor(369, 0.55, 0.27, 0.07, "");
  color[70] = new TColor(370, 0.63, 0.32, 0.18, "");
  color[71] = new TColor(371, 0.80, 0.52, 0.25, "");
  color[72] = new TColor(372, 0.99, 0.85, 0.70, "");
  color[73] = new TColor(373, 0.96, 0.96, 0.86, "");
  color[74] = new TColor(374, 0.99, 0.90, 0.75, "");
  color[75] = new TColor(375, 0.96, 0.64, 0.38, "");
  color[76] = new TColor(376, 0.82, 0.71, 0.55, "");
  color[77] = new TColor(377, 0.82, 0.41, 0.12, "");
  color[78] = new TColor(378, 0.70, 0.13, 0.13, "");
  color[79] = new TColor(379, 0.65, 0.16, 0.16, "");
  color[80] = new TColor(380, 0.91, 0.59, 0.48, "");
  color[81] = new TColor(381, 0.98, 0.50, 0.45, "");
  color[82] = new TColor(382, 1.00, 0.85, 0.80, "");
  color[83] = new TColor(383, 1.00, 0.65, 0.00, "");
  color[84] = new TColor(384, 1.00, 0.55, 0.00, "");
  color[85] = new TColor(385, 1.00, 0.50, 0.31, "");
  color[86] = new TColor(386, 0.94, 0.50, 0.50, "");
  color[87] = new TColor(387, 1.00, 0.39, 0.28, "");
  color[88] = new TColor(388, 1.00, 0.27, 0.00, "");
  color[89] = new TColor(389, 1.00, 0.00, 0.00, "");
  //color[90] = new TColor(390, 1.00, 0.41, 0.71, "");
  //color[91] = new TColor(391, 1.00, 0.08, 0.58, "");
  //color[92] = new TColor(392, 1.00, 0.75, 0.80, "");
  //color[93] = new TColor(393, 1.00, 0.71, 0.76, "");
  //color[94] = new TColor(394, 0.86, 0.44, 0.58, "");
  //color[95] = new TColor(395, 0.69, 0.19, 0.38, "");
  //color[96] = new TColor(396, 0.78, 0.08, 0.52, "");
  //color[97] = new TColor(397, 0.82, 0.13, 0.56, "");

  color[90] = new TColor(390, 0.90, 0.60, 0.60, ""); //red
  color[91] = new TColor(391, 0.70, 0.25, 0.25, "");
  color[92] = new TColor(392, 0.87, 0.87, 0.91, ""); //blue
  color[93] = new TColor(393, 0.59, 0.58, 0.91, ""); 
  color[94] = new TColor(394, 0.65, 0.55, 0.85, ""); //violet (gamma)
  color[95] = new TColor(395, 0.49, 0.26, 0.64, ""); 
  color[96] = new TColor(396, 0.95, 0.95, 0.60, ""); // yellow (alpha)
  color[97] = new TColor(397, 0.95, 0.95, 0.00, "");
  color[98] = new TColor(398, 0.75, 0.92, 0.68, ""); //green (2beta+gamma)
  color[99] = new TColor(399, 0.36, 0.57, 0.30, "");
  color[100] = new TColor(400, 0.97, 0.50, 0.09, ""); // orange
  color[101] = new TColor(401, 0.76, 0.34, 0.09, "");
  color[102] = new TColor(402, 0.97, 0.52, 0.75, ""); // pink
  color[103] = new TColor(403, 0.76, 0.32, 0.51, "");
  color[104] = new TColor(404, 0.49, 0.60, 0.82, ""); // dark blue (kpnn)
  color[105] = new TColor(405, 0.43, 0.48, 0.52, "");  
  color[106] = new TColor(406, 0.70, 0.70, 0.70, "");  // black
  color[107] = new TColor(407, 0.40, 0.40, 0.40, ""); 

}


double CalcThreshold(TH1D* InputPlot, double conf_level) {

  TH1D* PLot1D = (TH1D*) InputPlot->Clone();
  int nx = PLot1D->GetNbinsX();
  PLot1D->SetBinContent(0,0.);
  PLot1D->SetBinContent(1+nx,0.);
  conf_level *= PLot1D->GetSum();

  vector< Double_t > OrderedGArray1D;
  for (int ix=1; ix<=nx; ix++) {
    OrderedGArray1D.push_back(PLot1D->GetBinContent(ix));
  }
  
  double level1D = 0.;
  double area1D = 0.;
  sort( OrderedGArray1D.begin(), OrderedGArray1D.end(),greater<double>() );
  vector< Double_t> SumArray1D;
  SumArray1D.push_back(OrderedGArray1D[0]);
  for (int i=1; i< (int) OrderedGArray1D.size(); i++) {
    SumArray1D.push_back(SumArray1D[i-1] + (double) OrderedGArray1D[i]);
    if (SumArray1D[i] <= conf_level) {
      level1D = OrderedGArray1D[i];
      area1D = SumArray1D[i];
    }
  }
  delete PLot1D;
  return level1D;
}

void makeOtherPlot(TH2D* histo2D, TObjArray* histo, int superimpose, int col68, int col95) {

  TAxis* tmp = (TAxis*) histo2D->GetXaxis();
  xmin = tmp->GetXmin();
  xmax = tmp->GetXmax();
  binx =  tmp->GetNbins();
  
  tmp = (TAxis*) histo2D->GetYaxis();
  ymin = tmp->GetXmin();
  // to avoid problems with common code
  etamin=ymin;
  ymax = tmp->GetXmax();
  biny =  tmp->GetNbins();

  TH2D* null2 = new TH2D("null","",binx,xmin,xmax,biny,ymin,ymax);
  if(strncmp(plotname.c_str(),"gammavsRb",9)==0) {
    null2->SetXTitle("R_{b}");
    null2->SetYTitle("#gamma");
  }
  if(strncmp(plotname.c_str(),"FbvsBk",6)==0) {
    null2->SetXTitle("B_{k}");
    null2->SetYTitle("f_{B_{d}}#sqrt{B_{B_{d}}}[GeV]");
  }
  if(strncmp(plotname.c_str(),"FbsvsBk",7)==0) {
    null2->SetXTitle("B_{k}");
    null2->SetYTitle("f_{B_{s}}#sqrt{B_{B_{s}}}[GeV]");
  }
  if(strncmp(plotname.c_str(),"BkvsXi",6)==0) {
    null2->SetXTitle("#xi");
    null2->SetYTitle("B_{k}");
  }
  if(strncmp(plotname.c_str(),"FbvsXi",6)==0) {
    null2->SetXTitle("#xi");
    null2->SetYTitle("f_{B_{d}}#sqrt{B_{B_{d}}}[GeV]");
  }
  if(strncmp(plotname.c_str(),"FbsvsXi",7)==0) {
    null2->SetXTitle("#xi");
    null2->SetYTitle("f_{B_{s}}#sqrt{B_{B_{s}}}[GeV]");
  }
  
  if (lxlab) null2->SetXTitle(xlab);
  if (lylab) null2->SetYTitle(ylab+" ");
  
  null2->SetTitleSize(0.05,"X");
  null2->SetTitleSize(0.05,"Y");
  if (lsquare) {
    null2->SetTitleOffset(0.85,"X");
    null2->SetTitleOffset(1.5,"Y");
  } else {
    null2->SetTitleOffset(0.7,"X");
    null2->SetTitleOffset(0.7,"Y");
  }
  null2->SetStats(0);
  if (!superimpose)
    null2->Draw();

  if (!superimpose && drawtotarea == 1) {
    //drawFromGraph(histo, 0, "AREA", col4-2);
    drawFromGraph(histo, 0, "AREA", col5);
    drawFromGraph(histo, 1, "AREA", col4);
    drawFromGraph(histo, 2, "AREA", col3);
    drawFromGraph(histo, 3, "AREA", col95);
    drawFromGraph(histo, 4, "AREA", col68);
  }

  if(llines) {
    //drawFromGraph(histo, 0, "CONT", col3);
    drawFromGraph(histo, 0, "CONT", col3);
    drawFromGraph(histo, 1, "CONT", col3);
    drawFromGraph(histo, 2, "CONT", col3);
    drawFromGraph(histo, 3, "CONT", col3);
  }
  
  null2->Draw("same");

  // draw error bars
  if (xval!=-999 && yval!=-999){
    TLine *lx = new TLine();
    lx->SetLineWidth(2);
    double zero=0,err;
    err = xerr;
    TGraphErrors *g1 = new TGraphErrors(1,&xval,&yval,&err,&zero);
    g1->SetLineWidth(2);
    g1->SetLineStyle(1);
    g1->SetMarkerStyle(20);
    g1->Draw("P");
    
    err = xerr;
    double min_x = max(xval-err,xmin);
    double max_x = min(xval+err,xmax);
    lx->DrawLine(min_x,yval,max_x,yval);

    TLine *ly = new TLine();
    ly->SetLineWidth(2);
    err = yerr;
    TGraphErrors* g2 = new TGraphErrors(1,&xval,&yval,&zero,&err);
    g2->SetLineWidth(2);
    g2->SetLineStyle(1);
    g2->SetMarkerStyle(20);
    g2->Draw("P");
    
    double min_y = max(yval-err,ymin);
    double max_y = min(yval+err,ymax);
    ly->DrawLine(xval,min_y,xval,max_y);
  }

  if(llogo) {
    // draw logo
    TImage *img = TImage::Open("../common/logo.png");
    img->SetConstRatio(kFALSE);
    double x0 = 0.180;
    double y0 = 0.160;
    if (logoposition==3 || logoposition==4)
      x0 = 0.780; //right part of the plot
    if (logoposition==2 || logoposition==3)
      y0 = 0.820; //top part of the plot
    double x1 = x0+(lsquare == 1? 0.095 :0.11);
    double y1 = y0+(lsquare == 1? 0.075 :0.11);
    TPad *pad = new TPad("pad","pad",x0,y0,x1,y1);
    pad->Draw();
    pad->cd();
    img->Draw();  
    gPad->Update();
    c1->cd();
  }

  TLine* Bound = new TLine(xmin,ymax,xmax,ymax);
  Bound->Draw();
  Bound->DrawLine(xmax,ymin,xmax,ymax);

  //this is for x' and y'
  Float_t c1_c[1] = {0.0261};
  Float_t c2_c[1] = {-0.0006};
  //this is for x' and y' for D0
  //Float_t c1_c[1] = {0.025325};
  //Float_t c2_c[1] = {-0.005055};
  //this is for x' and y' for D0bar
  //Float_t c1_c[1] = {0.0355};
  //Float_t c2_c[1] = {-0.0054};

  //this is for c1 and c2
  //Float_t c1_c[1] = {-0.001996};
  //Float_t c2_c[1] = {0.3535};

  TGraph central(1,c1_c,c2_c);
  central.SetMarkerSize(4);

  Float_t c1_0[1] = {0.};
  Float_t c2_0[1] = {0.};
  TGraph zerop(1,c2_0,c1_0);
  zerop.SetMarkerSize(4);
  zerop.SetMarkerStyle(2);

  central.Draw("*SAME");
  zerop.Draw("PSAME");

  c1->RedrawAxis("same");

  //BaBarStyle p;
  //p.SetBaBarStyle();
  //p.SetBaBarLabel(-1,-1,-1,"preliminary");

 TLegend contleg(0.2,0.2,0.4,0.4,"");
  vector<string> conf; 
  conf.push_back("68.3 %");
  conf.push_back("95.5 %");
  conf.push_back("99.7 %");
  conf.push_back("99.9 %");

  vector<int> col;
  col.push_back(col1);
  col.push_back(col2);
  col.push_back(col3);
  col.push_back(col4);

  for (int i=0; i<4;i++) {
    TList* contour = (TList*)histo->At(i);
    TGraph* curv = (TGraph*)contour->First();
    TGraph* tmpTGraph = CloseTGraph(curv);
    tmpTGraph->SetFillColor(col[i]);
    contleg.AddEntry(tmpTGraph,conf[i].c_str(),"f");
  }
  //contleg.Draw();
  //c1->Update();

  c1->SaveAs("prova.eps");
}

double CalcLevel_Mediana(TH1D* InputPlot, double conf_level, char* side) {
  
  TH1D* Plot = (TH1D*) InputPlot->Clone();
  int nbin = Plot->GetNbinsX();
  double low = Plot->GetXaxis()->GetXmin();
  double up  = Plot->GetXaxis()->GetXmax();
  double width=(up-low)/nbin;

  Plot->SetBinContent(0,0.);
  Plot->SetBinContent(1+nbin,0.);

  double *NArray = new double[nbin];
  for (int i=0;i<nbin;i++) {
    NArray[i]=Plot->GetBinContent(i+1);
  }

  //compute coordinates
  double *coord = new double[nbin];
  for (int i=0;i<nbin;i++){
    coord[i] = low+width*i;
  }

  cout << coord[10] << endl;

  double sumold,sum=0;
  double chk; 
  double xcoo = -99.;

  // compute CLs and the corresponding coordinates
  //
  xcoo = low;
  if(side == "Low") {
    chk = (1.-conf_level)/2.*Plot->GetSum();
  } else {
    chk = (1.-(1.-conf_level)/2.)*Plot->GetSum();
    xcoo = up;
  }

  sum = NArray[0];
  for (int i=1;i<nbin;i++){
    sumold = sum;
    sum += NArray[i];
    if ( sum>=chk  && sumold<chk ){
      //	xcoo =coord[i] +tobeadded*width;
      xcoo =coord[i] +0.5*width;
    }
  }
    
  return xcoo;

}

TH2D* smooth2D(TH2D* ThisConstrain, int smooth, double level[5], int nlevel) {
  double nrho   = ThisConstrain->GetNbinsX();
  double neta   = ThisConstrain->GetNbinsY(); 
  TH2D* ThisConstrain2 = (TH2D*) ThisConstrain->Clone();

  for(int jj=0; jj<smooth; jj++) {
    for (int ix=2; ix<nrho; ix++) {
      for (int iy=2; iy<neta; iy++) {
	double new_weight = (ThisConstrain2->GetCellContent(ix+1,iy+1)+
			     ThisConstrain2->GetCellContent(ix+1,iy)+
			     ThisConstrain2->GetCellContent(ix+1,iy-1)+
			     ThisConstrain2->GetCellContent(ix,iy+1)+
			     ThisConstrain2->GetCellContent(ix,iy)+
			     ThisConstrain2->GetCellContent(ix,iy-1)+
			     ThisConstrain2->GetCellContent(ix-1,iy+1)+
			     ThisConstrain2->GetCellContent(ix-1,iy)+
			     ThisConstrain2->GetCellContent(ix-1,iy-1))/9.;
	ThisConstrain2->SetCellContent(ix,iy,new_weight);
      }
    }
    
    for (int ix=2; ix<nrho; ix++) {
      for (int iy=2; iy<neta; iy++) {
	if(ThisConstrain2->GetCellContent(ix,iy) <= level[4-nlevel]) {
	  int icont = 0;
	  if(ThisConstrain2->GetCellContent(ix+1,iy+1) > level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix+1,iy)   > level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix+1,iy-1) > level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix,iy+1)   > level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix,iy-1)   > level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix-1,iy+1) > level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix-1,iy)   > level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix-1,iy-1) > level[4-nlevel]) icont++;
	  if(icont >4)
	    ThisConstrain2->SetCellContent(ix,iy,level[4-nlevel]*1.01);  
	}
      }
    }
    
    for (int ix=2; ix<nrho; ix++) {
      for (int iy=2; iy<neta; iy++) {
	if(ThisConstrain2->GetCellContent(ix,iy)     > level[4-nlevel]) {
	  int icont = 0;
	  if(ThisConstrain2->GetCellContent(ix+1,iy+1) <= level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix+1,iy)   <= level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix+1,iy-1) <= level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix,iy+1)   <= level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix,iy-1)   <= level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix-1,iy+1) <= level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix-1,iy)   <= level[4-nlevel]) icont++;
	  if(ThisConstrain2->GetCellContent(ix-1,iy-1) <= level[4-nlevel]) icont++;
	  if(icont>6) 
	    ThisConstrain2->SetCellContent(ix,iy,level[4-nlevel]*0.99);
	}
      }
    }  
  }

  return ThisConstrain2;
}

/////////////////////////////////////////////////////////////////////////
// given rho, eta, a 1D histo and a constraint
// returns the value of the 1D histogram for 
// those values of rho and eta.
// only 2alpha and 2bpg are implemented (for the moment)
/////////////////////////////////////////////////////////////////////////

double findLevel(double rho, double eta, TH1D* Histo, TString name) {
  double var=0;
  if (strncmp(name,"2bpg",4)==0)
    var = acos(cos(2*atan2(eta,1-rho)+atan2(eta,rho)))*180./Pi;
  else if (strncmp(name,"alpha",5)==0) {
    var = (acos(-1.)- atan2(eta,1-rho) - atan2(eta,rho))*180./Pi;
    if(var < 0.) var += 180.;
    if(var > 180.) var -= 180.;
  }
  else if (strncmp(name,"s2a",3)==0)
    var = sin(2*(acos(-1.)- atan2(eta,1-rho) - atan2(eta,rho)));
  else if (strncmp(name,"dms",3)==0)
    var = sqrt(pow(1.-rho,2.) + pow(eta,2.));
  else
    cout << "you should implement the relation with rho and eta" << endl;
  double thislevel = 0.;

  if ((strncmp(name,"2bpg",4)==0) && (var == 180.))
    thislevel = Histo->GetBinContent(Histo->FindBin(var)-1);
  else
    thislevel = Histo->GetBinContent(Histo->FindBin(var));
    
  return thislevel;
}

/////////////////////////////////////////////////////////////////////////
// interface function that produces a 2d plot for rho and eta
// from a 1D plot on a given constraint and calls the general function
// GraphFromHisto to return the TObjArray containing the contours
/////////////////////////////////////////////////////////////////////////

TObjArray* CalcGraph(TH1D* Histo, double level1, double level2, TString name) {
  int rhobin= 1000;
  int imin = 0;
  int imax = 1000;
  int etabin= 600;
  int jmin = 0;
  int jmax = 600;

  double min = xmin;
  double max = xmax;
  double bottom = etamin;
  double top = ymax;

  if(name == "2bpg1") {
    min = xmin; max = 1.0;  imin = 0;   imax = 900; 
    bottom = etamin; top = 0.0;  jmin = 0;   jmax = 300; 
  }
  if(name == "2bpg2") {
    min = 1.0;  max = xmax; imin = 900; imax = 1000;
    bottom = etamin; top = 0.0;  jmin = 0;   jmax = 300; 
  }
  if(name == "2bpg3") {
    min = xmin; max = 1.0;  imin = 0;   imax = 900;
    bottom = 0; top = ymax;  jmin = 300;   jmax = 600; 
  }
  if(name == "2bpg4") {
    min = 1.0;  max = xmax; imin = 900; imax = 1000;
    bottom = 0; top = ymax;  jmin = 300;   jmax = 600; 
  }
  if(name == "alpha1") {
    min = xmin; max = 0.0;  imin = 0;   imax = 500; 
    bottom = etamin; top = 0.0;  jmin = 0;   jmax = 300; 
  }
  if(name == "alpha2") {
    min = 0.0;  max =1.0;   imin = 500; imax = 900;
  }
  if(name == "alpha3") {
    min = 1.0;  max = xmax; imin = 900; imax = 1000;
    bottom = etamin; top = 0.0;  jmin = 0;   jmax = 300; 
  }
  if(name == "alpha4") {
    min = xmin; max = 0.0;  imin = 0;   imax = 500;
    bottom = 0; top = ymax;  jmin = 300;   jmax = 600; 
  }
  if(name == "alpha5") {
    min = 1.0;  max = xmax; imin = 900; imax = 1000;
    bottom = 0; top = ymax;  jmin = 300;   jmax = 600; 
  }

  if(name == "alpha") {
    etabin= 1000;
    jmax=1000;
  }
  // we want the graph to be larger than the hist, to avoid 
  // problems at the boundaries
  TH2D* tmp2Dhisto = new TH2D(name, name, rhobin, xmin,xmax, etabin,etamin,ymax);

  for (int ix=imin+1; ix<=imax; ix++) {
    double irho = min + double(ix-imin-0.5)/(imax-imin)*(max-min);
    for (int iy=jmin+1; iy<=jmax; iy++) {
      double ieta = bottom + double(iy-jmin-0.5)/(jmax-jmin)*(top-bottom);
      tmp2Dhisto->SetCellContent(ix,iy,findLevel(irho,ieta,Histo,name));
    }
  }
  cout << "GETTING CONTOUR LIST FOR " << name << endl;
  TObjArray* array = (TObjArray*) GraphFromHisto(tmp2Dhisto,level1,level2);
  delete tmp2Dhisto;
  return  array;
}

/////////////////////////////////////////////////////////////////////////
// Return the contours of a 2D histogram tmp2Dhisto, given the two levels
// l1 and l2 (usually corresponding to 68% and 95%
/////////////////////////////////////////////////////////////////////////

TObjArray* GraphFromHisto(TH2D* tmp2Dhisto, double level1, double level2, double level3, double level4, double level5 ) {

  double levels[5];
  levels[0] = level5;
  levels[1] = level4;
  levels[2] = level3;
  levels[3] = level2;
  levels[4] = level1;

  tmp2Dhisto->SetContour(5,levels);
  tmp2Dhisto->Draw("contlist");
  c1->Update();

  TObjArray *contours = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");

  if (contours == NULL){
    printf("*** WARNING: No Contours Were Extracted!\n");
  }

  printf("TotalConts = %d\n", contours->GetSize());
  return contours;
}

void drawFromGraph(TObjArray* contours, int ind, char DrawOpt[], int col) {
  TList* contour = (TList*)contours->At(ind);
  printf("TotalGraphs = %d\n", contour->GetSize());

  TGraph* curv = (TGraph*)contour->First();
  for (int i=0; i<contour->GetSize();i++) {
    TGraph* tmpTGraph = CloseTGraph(curv);
    if(DrawOpt == "AREA") {
      tmpTGraph->SetLineWidth(2);
      tmpTGraph->SetLineColor(col);
      tmpTGraph->SetFillColor(col);
      tmpTGraph->Draw("F");
    }
    if( DrawOpt == "CONT") {
      curv->SetLineWidth(2);
      curv->SetLineColor(col);
      curv->SetFillColor(col);
      curv->Draw();
    }
    curv = (TGraph*)contour->After(curv); // Get Next graph
  }
  c1->Update();
  return;
}

TGraph* CloseTGraph(TGraph* inputgraph) {

  double x_i, x_j, y_i, y_j;
   inputgraph->GetPoint(0,x_i,y_i);
  inputgraph->GetPoint(inputgraph->GetN()-1,x_j,y_j);

  double xleft_i(0), xright_i(0);
  double ybottom_i(0), ytop_i(0);
  double xleft_j(0), xright_j(0);
  double ybottom_j(0), ytop_j(0);

  double deltax = (xmax-xmin)/binx;
  double deltay = (ymax-etamin)/biny;

  if(fabs(x_i-xmin)<deltax) xleft_i   = 1.;
  if(fabs(x_i-xmax)<deltax) xright_i  = 1.;
  if(fabs(y_i-etamin)<deltay) ybottom_i = 1.;
  if(fabs(y_i-ymax)<deltay) ytop_i    = 1.;

  if(fabs(x_j-xmin)<deltax) xleft_j   = 1.;
  if(fabs(x_j-xmax)<deltax) xright_j  = 1.;
  if(fabs(y_j-etamin)<deltay) ybottom_j = 1.;
  if(fabs(y_j-ymax)<deltay) ytop_j    = 1.;

  double xnew[inputgraph->GetN()+3];
  double ynew[inputgraph->GetN()+3];

  for(int i=0; i< inputgraph->GetN(); i++) {
    inputgraph->GetPoint(i,xnew[i],ynew[i]);
  }

  if(xleft_i ==1 && ybottom_j == 1) { 
    // we go from bottom to left
    // passing through the left-bottom corner
    xnew[inputgraph->GetN()]   = x_j;    ynew[inputgraph->GetN()]   = etamin;
    xnew[inputgraph->GetN()+1] = xmin;   ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = xmin;   ynew[inputgraph->GetN()+2] = y_i;
  } else if(xleft_j ==1 && ybottom_i == 1) { 
    // we go from left to bottom
    // passing through the left-bottom corner
    xnew[inputgraph->GetN()]   = xmin;   ynew[inputgraph->GetN()]   = y_j;
    xnew[inputgraph->GetN()+1] = xmin;   ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = x_i;    ynew[inputgraph->GetN()+2] = etamin;    
  } else if(xright_i == 1 && ytop_j ==1) {
    // we go from right to top
    // passing through the tight-top corner
    xnew[inputgraph->GetN()]   = x_j;    ynew[inputgraph->GetN()]   = ymax;
    xnew[inputgraph->GetN()+1] = xmax;   ynew[inputgraph->GetN()+1] = ymax;
    xnew[inputgraph->GetN()+2] = xmax;   ynew[inputgraph->GetN()+2] = y_i;
  } else if(xright_j == 1 && ytop_i == 1) {
    // we go from top to right
    // passing through the tight-top corner
    xnew[inputgraph->GetN()]   = xmax;   ynew[inputgraph->GetN()]   = y_j;
    xnew[inputgraph->GetN()+1] = xmax;   ynew[inputgraph->GetN()+1] = ymax;
    xnew[inputgraph->GetN()+2] = x_i;    ynew[inputgraph->GetN()+2] = ymax;
  } else if(xright_i == 1 && ybottom_j ==1) {
    // we go from right to bottom
    // passing through the right-bottom corner
    xnew[inputgraph->GetN()]   = x_j;    ynew[inputgraph->GetN()]   = etamin;
    xnew[inputgraph->GetN()+1] = xmax;   ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = xmax;   ynew[inputgraph->GetN()+2] = y_i;
  } else if(xright_j == 1 && ybottom_i ==1) {
    // we go from bottom to right
    // passing through the right-bottom corner
    xnew[inputgraph->GetN()]   = xmax;   ynew[inputgraph->GetN()]   = y_j;
    xnew[inputgraph->GetN()+1] = xmax;   ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = x_i;    ynew[inputgraph->GetN()+2] = etamin;
  } else if(xleft_i == 1 && ybottom_j ==1) {
    // we go from left to bottom
    // passing through the left-bottom corner
    xnew[inputgraph->GetN()]   = x_j;    ynew[inputgraph->GetN()]   = etamin;
    xnew[inputgraph->GetN()+1] = xmin;   ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = xmin;   ynew[inputgraph->GetN()+2] = y_i;
  } else if(xleft_j == 1 && ybottom_i ==1) {
    // we go from bottom to left
    // passing through the left-bottom corner
    xnew[inputgraph->GetN()]   = xmin;   ynew[inputgraph->GetN()]   = y_j;
    xnew[inputgraph->GetN()+1] = xmin;   ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = x_i;    ynew[inputgraph->GetN()+2] = etamin;
//    NP C_Bs vs phi_Bs
  } else if (ybottom_i ==1 && ytop_j ==1){ //from top to bottom
    xnew[inputgraph->GetN()]   = x_j;    ynew[inputgraph->GetN()]   = ymax;
    xnew[inputgraph->GetN()+1] = 0.002;    ynew[inputgraph->GetN()+1] = ymax;
    xnew[inputgraph->GetN()+2] = 0.002;    ynew[inputgraph->GetN()+2] = etamin;
  } else if (ybottom_j ==1 && ytop_i ==1){ //from bottom to top
    xnew[inputgraph->GetN()]   = x_j;    ynew[inputgraph->GetN()]   = etamin;
    xnew[inputgraph->GetN()+1] = 0.002;    ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = 0.002;    ynew[inputgraph->GetN()+2] = ymax;

// achilleplot Bd
  } else if (xleft_i ==1 && xright_j ==1){ //from left to right
    xnew[inputgraph->GetN()]   = xmax;    ynew[inputgraph->GetN()]   = y_j;
    xnew[inputgraph->GetN()+1] = xmax;    ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = xmin;    ynew[inputgraph->GetN()+2] = etamin;
  } else if (xleft_j ==1 && xright_i ==1){ //from right to left
    xnew[inputgraph->GetN()]   = xmin;    ynew[inputgraph->GetN()]   = y_j;
    xnew[inputgraph->GetN()+1] = xmin;    ynew[inputgraph->GetN()+1] = etamin;
    xnew[inputgraph->GetN()+2] = xmax;    ynew[inputgraph->GetN()+2] = etamin;	
  } else {
    // nominal
    xnew[inputgraph->GetN()]   = x_j; ynew[inputgraph->GetN()]   = y_j;
    xnew[inputgraph->GetN()+1] = x_j; ynew[inputgraph->GetN()+1] = y_j;
    xnew[inputgraph->GetN()+2] = x_j; ynew[inputgraph->GetN()+2] = y_j;
    
    // NP paper, achilleplot Bs
       /*
     if(x_j > 175.) {
       xnew[inputgraph->GetN()]   = xmax; ynew[inputgraph->GetN()]   = y_j;
       xnew[inputgraph->GetN()+1] = xmax; ynew[inputgraph->GetN()+1] = etamin;
       xnew[inputgraph->GetN()+2] = 0.; ynew[inputgraph->GetN()+2] = etamin;
     } else if(x_j < 10) {
       xnew[inputgraph->GetN()]   = xmin; ynew[inputgraph->GetN()]   = y_j;
       xnew[inputgraph->GetN()+1] = xmin; ynew[inputgraph->GetN()+1] = etamin;
       xnew[inputgraph->GetN()+2] = 0.; ynew[inputgraph->GetN()+2] = etamin;      
     } else {      
       xnew[inputgraph->GetN()]   = x_j; ynew[inputgraph->GetN()]   = y_j;
       xnew[inputgraph->GetN()+1] = x_j; ynew[inputgraph->GetN()+1] = y_j;
       xnew[inputgraph->GetN()+2] = x_j; ynew[inputgraph->GetN()+2] = y_j;
     }
       */
    // latticeQCD x SM paper
 
//     if(y_j > 0.) {
//       xnew[inputgraph->GetN()]   = x_j; ynew[inputgraph->GetN()]  = y_j;
//       xnew[inputgraph->GetN()+1] = 1.; ynew[inputgraph->GetN()+1] =  90.;
//       xnew[inputgraph->GetN()+2] = 1.; ynew[inputgraph->GetN()+2] = -90.;
//     } else {
//       xnew[inputgraph->GetN()]   = x_j; ynew[inputgraph->GetN()]  = y_j;
//       xnew[inputgraph->GetN()+1] = 1.; ynew[inputgraph->GetN()+1] = -90.;
//       xnew[inputgraph->GetN()+2] = 1.; ynew[inputgraph->GetN()+2] =  90.;
//     }
 
  }
  
  TGraph* newTGraph = new TGraph(inputgraph->GetN()+3,xnew,ynew);
  return newTGraph;
}
