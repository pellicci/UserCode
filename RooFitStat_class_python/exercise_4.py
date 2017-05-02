
import ROOT

mass = ROOT.RooRealVar("mass","The invariant mass",100.,150.)

#Signal PDF
mean1 = ROOT.RooRealVar("mean1","Mean of first signal gaussian",125.,110.,140.)
sigma1 = ROOT.RooRealVar("sigma1","Sigma of first signal gaussian",1.,0.001,4.)
SigGauss1 = ROOT.RooGaussian("SigGauss1","First signal gaussian",mass,mean1,sigma1)

#Background PDF
a0 = ROOT.RooRealVar("a0","a0",-1.,-3.,3.)
a1 = ROOT.RooRealVar("a1","a1",0.5,-3.,3.)
BkgPDF = ROOT.RooChebychev("BkgPDF","BkgPDF",mass,ROOT.RooArgList(a0,a1))

#Total first PDF
frac1 = ROOT.RooRealVar("frac1","Fraction for first PDF",0.6,0.,1.)
totPDF1 = ROOT.RooAddPdf("totPDF1","Total PDF 1",ROOT.RooArgList(SigGauss1,BkgPDF),ROOT.RooArgList(frac1))

#Build the second signal PDF
sigma2 = ROOT.RooRealVar("sigma2","Sigma of second signal gaussian",2.,0.001,4.)
SigGauss2 = ROOT.RooGaussian("SigGauss2","Second signal gaussian",mass,mean1,sigma2)

#Total second PDF
frac2 = ROOT.RooRealVar("frac2","Fraction for second PDF",0.4,0.,1.)
totPDF2 = ROOT.RooAddPdf("totPDF2","Total PDF 2",ROOT.RooArgList(SigGauss2,BkgPDF),ROOT.RooArgList(frac2))

#Generate the two samples
data1 = totPDF1.generate(ROOT.RooArgSet(mass),1000)
data2 = totPDF2.generate(ROOT.RooArgSet(mass),2000)

SigCat = ROOT.RooCategory("SigCat","Signal categories")
SigCat.defineType("Signal1")
SigCat.defineType("Signal2")

combinedData = ROOT.RooDataSet("combinedData","The combined data", ROOT.RooArgSet(mass), ROOT.RooFit.Index(SigCat), ROOT.RooFit.Import("Signal1",data1), ROOT.RooFit.Import("Signal2",data2) )

#Construct the simultaneous PDF
simPdf = ROOT.RooSimultaneous("simPdf","The total simultaneous PDF",SigCat)
simPdf.addPdf(totPDF1,"Signal1")
simPdf.addPdf(totPDF2,"Signal2")

#Do the fitting
simPdf.fitTo(combinedData)

#Do the plotting

#Separately for the two categories
massframe1 = mass.frame()
combinedData.plotOn(massframe1, ROOT.RooFit.Cut("SigCat==SigCat::Signal1"))
simPdf.plotOn(massframe1, ROOT.RooFit.Slice(SigCat,"Signal1"), ROOT.RooFit.ProjWData(combinedData))
simPdf.plotOn(massframe1, ROOT.RooFit.Slice(SigCat,"Signal1"), ROOT.RooFit.ProjWData(combinedData), ROOT.RooFit.Components("BkgPDF"), ROOT.RooFit.LineStyle(ROOT.kDashed))

massframe2 = mass.frame()
combinedData.plotOn(massframe2, ROOT.RooFit.Cut("SigCat==SigCat::Signal2"))
simPdf.plotOn(massframe2, ROOT.RooFit.Slice(SigCat,"Signal2"), ROOT.RooFit.ProjWData(combinedData))
simPdf.plotOn(massframe2, ROOT.RooFit.Slice(SigCat,"Signal2"), ROOT.RooFit.ProjWData(combinedData), ROOT.RooFit.Components("BkgPDF"), ROOT.RooFit.LineStyle(ROOT.kDashed))

canvas = ROOT.TCanvas()
canvas.Divide(2,1)
canvas.cd(1)
massframe1.Draw()
canvas.cd(2)
massframe2.Draw()
canvas.SaveAs("exercise_4.png")
