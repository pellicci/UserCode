
import ROOT

#Create a gaussian signal PDF
mass = ROOT.RooRealVar("mass","The invariant mass",100.,150.,"GeV/c^2")
mean = ROOT.RooRealVar("mean","The mean of the gaussian",125.,110.,140.)
width =  ROOT.RooRealVar("width","The width of the gaussian",2.,0.001,5.)

gaussPDF = ROOT.RooGaussian("gaussPDF","The gaussian function",mass,mean,width)

data = gaussPDF.generate(ROOT.RooArgSet(mass),1000)

gaussPDF.fitTo(data)

massplot = mass.frame()  #This is a RooPlot object
data.plotOn(massplot)
gaussPDF.plotOn(massplot)

canvas = ROOT.TCanvas()
canvas.cd()
massplot.Draw()
canvas.SaveAs("exercise_0.png")
