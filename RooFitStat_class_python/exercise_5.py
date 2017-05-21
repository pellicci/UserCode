
import ROOT

mass = ROOT.RooRealVar("mass","The invariant mass",7.,14.)

#Signal PDF
#change sigma1 to 0.3 and sigma2 to 0.5 to see a 10% bias on sigma1
mean1 = ROOT.RooRealVar("mean1","Mean of first signal gaussian",9.4,8.,11.)
sigma1 = ROOT.RooRealVar("sigma1","Sigma of first signal gaussian",0.1,0.001,2.)
SigGauss1 = ROOT.RooGaussian("SigGauss1","First signal gaussian",mass,mean1,sigma1)

mean2 = ROOT.RooRealVar("mean2","Mean of second signal gaussian",10.5,9.,12.)
sigma2 = ROOT.RooRealVar("sigma2","Sigma of second signal gaussian",0.2,0.001,2.)
SigGauss2 = ROOT.RooGaussian("SigGauss2","Second signal gaussian",mass,mean2,sigma2)

fracGauss = ROOT.RooRealVar("fracGauss","Fraction for signal PDFs",0.4,0.,1.)
totSigPDF = ROOT.RooAddPdf("totSigPDF","Total Signal PDF", ROOT.RooArgList(SigGauss1,SigGauss2), ROOT.RooArgList(fracGauss))

#Background PDF
a0 = ROOT.RooRealVar("a0","a0",-0.3,-0.8,0.8)
a1 = ROOT.RooRealVar("a1","a1",-0.1,-0.8,0.8)
BkgPDF = ROOT.RooChebychev("BkgPDF","BkgPDF",mass,ROOT.RooArgList(a0,a1))

#Total PDF
Nsig = ROOT.RooRealVar("Nsig","Number of signal events",900.,0.1,3000.)
Nbkg = ROOT.RooRealVar("Nbkg","Number of background events",100.,0.1,3000.)

totPDF = ROOT.RooAddPdf("totPDF","Total PDF", ROOT.RooArgList(totSigPDF,BkgPDF), ROOT.RooArgList(Nsig,Nbkg))

"""
data = totPDF.generate(ROOT.RooArgSet(mass),1000)
totPDF.fitTo(data)

xframe = mass.frame()
data.plotOn(xframe)
totPDF.plotOn(xframe)

c1 = ROOT.TCanvas()
xframe.Draw()
"""

#Construct the Toy-MC machinery
#Binned(kTRUE)
mcstudy = ROOT.RooMCStudy(totPDF, ROOT.RooArgSet(mass), ROOT.RooFit.Silence(), ROOT.RooFit.Extended(), ROOT.RooFit.FitOptions(ROOT.RooFit.Save(1), ROOT.RooFit.PrintEvalErrors(0)))
mcstudy.generateAndFit(1000)

#Plot the distributions of the fitted parameter, the error and the pull
sigma1val_frame = mcstudy.plotParam(sigma1, ROOT.RooFit.Bins(40))
sigma1err_frame = mcstudy.plotError(sigma1, ROOT.RooFit.Bins(40))
sigma1pull_frame = mcstudy.plotPull(sigma1, ROOT.RooFit.Bins(40), ROOT.RooFit.FitGauss(1))

#Plot distribution of minimized likelihood
NLLframe = mcstudy.plotNLL(ROOT.RooFit.Bins(40))

#Actually plot
canvas = ROOT.TCanvas()
canvas.Divide(2,2)
canvas.cd(1)
sigma1val_frame.Draw()
canvas.cd(2)
sigma1err_frame.Draw()
canvas.cd(3)
sigma1pull_frame.Draw()
canvas.cd(4)
NLLframe.Draw()
canvas.SaveAs("exercise_5.png")
