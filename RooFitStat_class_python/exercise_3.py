
import ROOT

fInput = ROOT.TFile("exercise_1.root")
fInput.cd()

workspace = fInput.Get("myworkspace")

mass = workspace.var("mass")
totPDF = workspace.pdf("totPDF")

data = workspace.data("totPDFData")

massplot = mass.frame()
data.plotOn(massplot)
totPDF.plotOn(massplot)

canvas = ROOT.TCanvas()
canvas.cd()
massplot.Draw()
canvas.SaveAs("exercise_3.png")
