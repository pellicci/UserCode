
import ROOT

ROOT.RooRandom.randomGenerator().SetSeed(1234)

mass = ROOT.RooRealVar("mass","The invariant mass",100.,150.,"GeV/c^2")

#Create a gaussian signal PDF
#Signal is the convolution of a BW times a gaussian resolution function
mpole = ROOT.RooRealVar("mpole","Pole position",125.,110.,140.)
BWwidth = ROOT.RooRealVar("BWwidth","Width of the Breit-Wigner",1.,0.0001,5.)
BWsig = ROOT.RooBreitWigner("BWsig","Signal Breit-Wigner",mass,mpole,BWwidth)

meanGauss = ROOT.RooRealVar("meanGauss","The mean of the gaussian",0.5,0.0001,2.)
widthGauss = ROOT.RooRealVar("widthGauss","The width of the gaussian",1.,0.001,5.)
gaussPDF = ROOT.RooGaussian("gaussPDF","The gaussian function",mass,meanGauss,widthGauss)

widthGauss.setConstant(1)

totSigPDF = ROOT.RooNumConvPdf("totSigPDF","Total signal PDF",mass,gaussPDF,BWsig)

#Background PDF: exponential background
tau = ROOT.RooRealVar("tau","The tau parameter",-0.05,-5.,-0.0001)
expoPDF = ROOT.RooExponential("expoPDF","The exponential background",mass,tau)

#frac = ROOT.RooRealVar("frac","Fraction of signal",0.5,0.,1.)
#totPDF = ROOT.RooAddPdf("totPDF","The total PDF",ROOT.RooArgList(gaussPDF,expoPDF),ROOT.RooArgList(frac))

#Nsig = ROOT.RooRealVar("Nsig","Number of signal events",500.,0.001,1000.)
cross_sig = ROOT.RooRealVar("cross_sig","The signal cross section",1.,0.00001,5.)
lumi = ROOT.RooRealVar("lumi","The luminosity",500.)
Nsig_form = ROOT.RooFormulaVar("Nsig_form","@0*@1",ROOT.RooArgList(cross_sig,lumi))

Nbkg = ROOT.RooRealVar("Nbkg","Number of background events",500.,0.001,1000.)
totPDF = ROOT.RooAddPdf("totPDF","The total PDF",ROOT.RooArgList(totSigPDF,expoPDF),ROOT.RooArgList(Nsig_form,Nbkg))

data = totPDF.generate(ROOT.RooArgSet(mass),1000)

totPDF.fitTo(data,ROOT.RooFit.Extended(1))

massplot = mass.frame()
data.plotOn(massplot)
totPDF.plotOn(massplot)
totPDF.plotOn(massplot,ROOT.RooFit.Components("expoPDF"),ROOT.RooFit.LineStyle(ROOT.kDashed),ROOT.RooFit.LineColor(ROOT.kRed))

canvas = ROOT.TCanvas()
canvas.cd()
massplot.Draw()
canvas.SaveAs("exercise_2.png")

workspace = ROOT.RooWorkspace("myworkspace")
getattr(workspace,'import')(totPDF)
getattr(workspace,'import')(data)

fOut = ROOT.TFile("exercise_2.root","RECREATE")
fOut.cd()
workspace.Write()
fOut.Close()
