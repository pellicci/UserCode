#include "BaBarStyle.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TPad.h"
#include <iostream>

using namespace std;

BaBarStyle::BaBarStyle()
{
}

void
BaBarStyle::SetBaBarStyle()
{
  // Create the 'BABAR' style for approved plots. Note that this style may need
  // some fine tuning in your macro depending on what you are plotting, e.g.
  //
  //  gStyle->SetMarkerSize(0.75);  // use smaller markers in a histogram with many bins
  //  gStyle->SetTitleOffset(0.65,"y");  // bring y axis label closer to narrow values
  TStyle *babarStyle= new TStyle("BABAR","BaBar approved plots style");
  
  // use plain black on white colors
  babarStyle->SetFrameBorderMode(0);
  babarStyle->SetCanvasBorderMode(0);
  babarStyle->SetPadBorderMode(0);
  babarStyle->SetPadColor(0);
  babarStyle->SetCanvasColor(0);
  babarStyle->SetTitleColor(0);
  babarStyle->SetStatColor(0);
  babarStyle->SetFillColor(0);
  
  // set the paper & margin sizes
  babarStyle->SetPaperSize(20,26);
  babarStyle->SetPadTopMargin(0.05);
  babarStyle->SetPadRightMargin(0.05);
  babarStyle->SetPadBottomMargin(0.16);
  babarStyle->SetPadLeftMargin(0.12);
  
  // use large Times-Roman fonts
  babarStyle->SetTextFont(132);
  babarStyle->SetTextSize(0.08);
  babarStyle->SetLabelFont(132,"x");
  babarStyle->SetLabelFont(132,"y");
  babarStyle->SetLabelFont(132,"z");
  babarStyle->SetLabelSize(0.05,"x");
  babarStyle->SetTitleSize(0.06,"x");
  babarStyle->SetLabelSize(0.05,"y");
  babarStyle->SetTitleSize(0.06,"y");
  babarStyle->SetLabelSize(0.05,"z");
  babarStyle->SetTitleSize(0.06,"z");
  
  // use bold lines and markers
  //babarStyle->SetMarkerStyle(8);
  //  babarStyle->SetHistLineWidth(1.85);
  // TStyle::SetHistLineWidth(short int ) ???
  short tmpLineWidth = short ( 1.85 );
  babarStyle->SetHistLineWidth( tmpLineWidth );
  
  babarStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  
  // do not display any of the standard histogram decorations
  babarStyle->SetOptTitle(0);
  babarStyle->SetOptStat(0);
  babarStyle->SetOptFit(0);
  
  // put tick marks on top and RHS of plots
  babarStyle->SetPadTickX(1);
  babarStyle->SetPadTickY(1);

  gROOT->SetStyle("BABAR");
  gROOT->SetBatch();
}

void
BaBarStyle::SetBaBarLabel(Double_t xpos, Double_t ypos, Double_t scale, TString str, Double_t scale2, TString align)
{
  // (AT) Since ROOT sets font size as a fraction of the smaller side of the pad, 
  // SetBaBarLabel() treats the cases of "vertical" and "horizontal" pads separately.
  // In addition, the label nicely positions itself in the upper-right corner of your plot.
  // The function takes three optional parameters: the x and the y coordinates of the
  // label's TOP-RIGHT corner and the label's relative size.
  //    Note, however, that the "BaBar" label will still get screwed up if you manually resize
  // the pad after drawing the label.
  //    Also note that what you see on the screen may not look perfect: I tried optimizing the 
  // way the label looks on paper. It goes without saying that your ROOT session should have 
  // TrueType font support turned on.  
  
  // Making -1 a placeholder for function's default value 
  if (xpos == -1) xpos = 0.9;
  if (ypos == -1) ypos = 0.9;
  if (scale == -1) scale = 1; 
  if (str == "-1") str = "null"; 
  if (scale2 == -1) scale2 = 0.5; 
  if (align == "-1") align = "R"; 
  // -2 as the first parameter triggers printing comamnd options
  if (xpos == -2) {
    cout 
      << endl
      << "  USAGE: SetBaBarLabel(xpos,ypos,scale,\"str\",scale2,\"align\");" << endl
      << "  Prints the official BaBar label on the active ROOT pad" << endl
      << "      xpos    X position of the \"BaBar\" label\'s top right corner, 0 < xpos < 1, defaults to 0.9" << endl 
      << "      ypos    Y position of the \"BaBar\" label\'s top right corner, 0 < ypos < 1, defaults to 0.9" << endl
      << "      scale   relative size of the label, defaults to 1" << endl 
      << "      str     LaTeX-style text that goes under the BaBar label. Use # instead of \\" << endl
      << "      scale2  relative size of the second line of text, defaults to 0.5" << endl
      << "      align   R or L: str is aligned to the right (default) or left edge of the \"BaBar\" label" << endl
      << "    By default, the second line of text is printed in Helvetica (a sans-serif font)." << endl
      << "  You can use the #font[] command to change the font. Refer to ROOT documentation for" << endl
      << "  more information on use of text in ROOT." << endl; 
    cout
      << "    \"Magic\" options: " << endl
      << "      xpos = -2 displays SetBaBarLabel() help" << endl
      << "      -1 can be used as a place holder to use the default value of any of the parameters" << endl
      << "      There are a few predefined values of str that start with a ~ (tilde):" << endl
      << "        \"~1\"       =          \"preliminary\"      " << endl
      << "        \"~2\"       =          \"very preliminary\" " << endl
      << "        \"~2000\"    =          \"year 2000 preliminary\" " << endl
      << "        \"~2001\"    =          \"year 2001 preliminary\" " << endl
      << "        \"~25\"      =          \"25 fb^{-1}\" " << endl     
      << "        \"~B->fcp\"  =           a big formula you should have seen before" << endl     
      << "    Examples: " << endl
      << "      SetBaBarLabel(); " << endl
      << "      SetBaBarLabel(-1,-1,-1,\"preliminary\"); " << endl
      << "      SetBaBarLabel(0.9,0.8,1.2,\"~25\"); " << endl
      << "      SetBaBarLabel(0.9,0.7,1.2,\"25 fb^{-1} preliminary\",0.6); " << endl
      << "      SetBaBarLabel(0.9,0.5,-1,\"~B->fcp\",0.25); " << endl 
      << endl;
    return;
  }
  // A few predefined labels to go to the second line of text
  if (str == "~1") str = "preliminary"; 
  if (str == "~2") str = "very preliminary"; 
  if (str == "~2000") str = "year 2000 preliminary"; 
  if (str == "~2001") str = "year 2000 preliminary"; 
  if (str == "~25") str = "25 fb^{-1}";
  if (str == "~B->fcp") str = "#font[12]{#Gamma#font[132]{(}B^{#font[12]{0}}_{#font[132]{phys}}#font[132]{(}t#font[132]{)} #rightarrow f_{CP}#font[132]{)} = #left|A_{f_{CP}}#right|^{#font[132]{2}} e^{-#Gamma t} #left[#frac{1+|#lambda_{f_{CP}}|^{#font[132]{2}}}{#font[132]{2}} + #frac{#font[132]{1}-|#lambda_{f_{CP}}|^{#font[132]{2}}}{#font[132]{2}} #font[132]{cos}#font[132]{(}#DeltaMt#font[132]{)} - #font[132]{Im }#lambda_{f_{CP}}#font[132]{sin}#font[132]{(}#DeltaMt#font[132]{)}#right]}";
  
  // Draw the label 
  TLatex *babar = new TLatex();
  Double_t cheburashkaFactorX=1, cheburashkaFactorY=1, padSizeX=500, padSizeY=500, xpos2, ypos2, xposL;
  babar->SetNDC(kTRUE);
  babar->SetTextFont(32); // Bold-Italic Times
  babar->SetTextAlign(31); // Right-Bottom
  padSizeX = gPad->GetWw()*gPad->GetWNDC(); // Get pad's dimensions
  padSizeY = gPad->GetWh()*gPad->GetHNDC();
  if (padSizeX>padSizeY) cheburashkaFactorX=padSizeY/padSizeX;
  if (padSizeX<padSizeY) cheburashkaFactorY=padSizeX/padSizeY;
  //xpos2=xpos-0.185*scale*cheburashkaFactorX;
  xpos2=xpos-0.188*scale*cheburashkaFactorX;
  ypos2=ypos-0.0620*scale*cheburashkaFactorY;
  xposL=xpos-0.253*scale*cheburashkaFactorX;
  babar->SetTextSize(0.10*scale); // Beginning to draw "BaBar"
  babar->DrawText(xpos2,ypos2,"B"); 
  babar->SetTextSize(0.075*scale);
  babar->DrawText(xpos2+0.039*scale*cheburashkaFactorX,ypos2,"A");
  babar->SetTextSize(0.10*scale);
  babar->DrawText(xpos2+0.1015*scale*cheburashkaFactorX,ypos2,"B");
  babar->SetTextSize(0.075*scale);
  babar->DrawText(xpos2+0.1875*scale*cheburashkaFactorX,ypos2,"AR");
  if (str == "null") return;    // Beginning to draw the second line of text
  babar->SetTextFont(42); // Helvetica (medium, upright) 
  babar->SetTextSize(0.1*scale2);
  if (align == "L") {
    babar->SetTextAlign(13); // Left-Top
    babar->DrawLatex(xposL,ypos2-0.02*scale2*cheburashkaFactorY,str);
  }
  else {
    babar->SetTextAlign(33); // Right-Top
    babar->DrawLatex(xpos,ypos2-0.02*scale2*cheburashkaFactorY,str);
  }
  delete babar;

}

void 
BaBarStyle::BABARLabel(Double_t xpos= 0.73, Double_t ypos= 0.85, Double_t scale= 1.0)
{
  // (DK) Generate the label "BABAR" for approved plots. The optional parameters specify
  // the lower-left corner of the label in normalized coordinates (0,1)x(0,1) and a
  // scale factor to apply to the label size. The defaults put the label in the
  // recommended location (top-right corner) with the recommended size.
  
  TText *babar = new TText();
  babar->SetNDC(kTRUE);
  babar->SetTextFont(32);
  babar->SetTextSize(0.10*scale);
  babar->DrawText(xpos,ypos,"B");
  babar->SetTextSize(0.075*scale);
  babar->DrawText(xpos+0.042*scale,ypos,"A");
  babar->SetTextSize(0.10*scale);
  babar->DrawText(xpos+0.078*scale,ypos,"B");
  babar->SetTextSize(0.075*scale);
  babar->DrawText(xpos+0.120*scale,ypos,"AR");
  delete babar;  
}
