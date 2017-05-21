
import ROOT

fInput = ROOT.TFile("DataSet_final.root")
fInput.cd()
data = fInput.Get("data")

mass = ROOT.RooRealVar("mass","The invariant mass",2.,6.,"GeV")

#The Jpsi signal parametrization
meanJpsi = ROOT.RooRealVar("meanJpsi","The mean of the Jpsi Gaussian",3.1,2.8,3.2)
sigmaJpsi = ROOT.RooRealVar("sigmaJpsi","The width of the Jpsi Gaussian",0.3,0.001,1.)
alphaJpsi = ROOT.RooRealVar("alphaJpsi","The alpha of the Jpsi Gaussian",1.5,-5.,5.)
nJpsi = ROOT.RooRealVar("nJpsi","The alpha of the Jpsi Gaussian",1.5)
CBJpsi = ROOT.RooCBShape("CBJpsi","The Jpsi Crystall Ball",mass,meanJpsi,sigmaJpsi,alphaJpsi,nJpsi)

#The psi(2S) signal parametrization
meanpsi = ROOT.RooRealVar("meanpsi","The mean of the psi Gaussian",3.7,3.5,4.)
gausspsi = ROOT.RooGaussian("gausspsi","The psi Gaussian",mass,meanpsi,sigmaJpsi)

#Background parametrization
a1 = ROOT.RooRealVar("a1","The a1 of background",-0.7,-2.,2.)
a2 = ROOT.RooRealVar("a2","The a2 of background",0.3,-2.,2.)
a3 = ROOT.RooRealVar("a3","The a3 of background",-0.03,-2.,2.)
backPDF = ROOT.RooChebychev("backPDF","The background",mass,ROOT.RooArgList(a1,a2,a3))

#Compose the total signal

#Either with fractions:
#fracJpsi = ROOT.RooRealVar("fracJpsi","The Jpsi signal fraction",0.6,0.,1.)
#totSigPDF = ROOT.RooAddPdf("totSigPDF","The total Signal PDF",ROOT.RooArgList(gaussJpsi,gausspsi),ROOT.RooArgList(fracJpsi))

#fracSig = ROOT.RooRealVar("fracSig","The signal fraction",0.2,0.,1.)
#totPDF = ROOT.RooAddPdf("totPDF","The total PDF",ROOT.RooArgList(totSigPDF,backPDF),ROOT.RooArgList(fracSig))

#Or extended
NJpsi = ROOT.RooRealVar("NJpsi","The Jpsi signal events",9000.,0.1,20000.)
Npsi = ROOT.RooRealVar("Npsi","The psi signal events",300.,0.1,600.)
Nbkg = ROOT.RooRealVar("Nbkg","The bkg events",20000.,0.1,50000.)
totPDF = ROOT.RooAddPdf("totPDF","The total PDF",ROOT.RooArgList(CBJpsi,gausspsi,backPDF),ROOT.RooArgList(NJpsi,Npsi,Nbkg))

totPDF.fitTo(data,ROOT.RooFit.Extended(1))

xframe = mass.frame()
data.plotOn(xframe)
totPDF.plotOn(xframe)

canvas = ROOT.TCanvas()
canvas.cd()
xframe.Draw()
canvas.SaveAs("exercise_final.png")

w = ROOT.RooWorkspace("w")
getattr(w,'import')(totPDF)
getattr(w,'import')(data)

fOutput = ROOT.TFile("Workspace_final.root","RECREATE")
fOutput.cd()
w.Write()
fOutput.Write()
fOutput.Close()
