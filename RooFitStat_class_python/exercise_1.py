
import ROOT

ROOT.RooRandom.randomGenerator().SetSeed(1234)

mass = ROOT.RooRealVar("mass","The invariant mass",100.,150.,"GeV/c^2")

#Create a gaussian signal PDF
mean = ROOT.RooRealVar("mean","The mean of the gaussian",125.,110.,140.)
width = ROOT.RooRealVar("width","The width of the gaussian",2.,0.001,5.)
gaussPDF = ROOT.RooGaussian("gaussPDF","The gaussian function",mass,mean,width)

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
totPDF = ROOT.RooAddPdf("totPDF","The total PDF",ROOT.RooArgList(gaussPDF,expoPDF),ROOT.RooArgList(Nsig_form,Nbkg))

data = totPDF.generate(ROOT.RooArgSet(mass),1000);

totPDF.fitTo(data,ROOT.RooFit.Extended(1))

massplot = mass.frame()
data.plotOn(massplot)
totPDF.plotOn(massplot)
totPDF.plotOn(massplot,ROOT.RooFit.Components("expoPDF"),ROOT.RooFit.LineStyle(ROOT.kDashed),ROOT.RooFit.LineColor(ROOT.kRed))

canvas = ROOT.TCanvas()
canvas.cd()
massplot.Draw()
canvas.SaveAs("exercise_1.png")

workspace = ROOT.RooWorkspace("myworkspace")
getattr(workspace,'import')(totPDF)
getattr(workspace,'import')(data)

fOut = ROOT.TFile("exercise_1.root","RECREATE")
fOut.cd()
workspace.Write()
fOut.Close()
