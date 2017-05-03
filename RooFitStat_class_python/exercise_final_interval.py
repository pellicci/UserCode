
import ROOT

#Open the rootfile and get the workspace
fInput = ROOT.TFile("Workspace_final.root")
fInput.cd()

#Get the workspace
w = fInput.Get("w")

#You can set constant parameters that are known
#If you leave them floating, the fit procedure will determine their uncertainty
w.var("meanJpsi").setConstant(1)
w.var("sigmaJpsi").setConstant(1)
w.var("alphaJpsi").setConstant(1)
w.var("meanpsi").setConstant(0)      #Parameter of interest now, don't fix it
w.var("a1").setConstant(1)
w.var("a2").setConstant(1)
w.var("a3").setConstant(1)
w.var("Nbkg").setConstant(1)
w.var("NJpsi").setConstant(1)
w.var("Npsi").setConstant(1)

#Set the RooModelConfig and let it know what the content of the workspace is about
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(w)
model.SetPdf("totPDF")

#Let the model know what is the parameter of interest
meanpsi = w.var("meanpsi")
meanpsi.setRange(3.6, 3.75) #This is mostly for plotting reasons
meanpsi.setBins(20)
poi = ROOT.RooArgSet(meanpsi)

#Set confidence level
confidenceLevel = 0.68

#Build the profile likelihood calculator
plc = ROOT.RooStats.ProfileLikelihoodCalculator()
plc.SetData(w.data("data"))
plc.SetModel(model)
plc.SetParameters(poi)
plc.SetConfidenceLevel(confidenceLevel)

#Get the interval
plInt = plc.GetInterval();

#Let's make a plot
canvas = ROOT.TCanvas()
canvas.cd()

plotInt = ROOT.RooStats.LikelihoodIntervalPlot(plInt)
plotInt.SetTitle("Profile Likelihood Ratio and Posterior for mH")
plotInt.SetMaximum(3.)
plotInt.Draw()
canvas.SaveAs("exercise_final_interval.png")

#Now print the interval for mH for the two methods
print "PLC interval is [", plInt.LowerLimit(meanpsi), ", ", plInt.UpperLimit(meanpsi), "]"
