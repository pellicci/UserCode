
import ROOT

#Open the rootfile and get the workspace from the exercise_6
fInput = ROOT.TFile("exercise_6.root")
fInput.cd()
w = fInput.Get("w")

#You can set constant parameters that are known
#If you leave them floating, the fit procedure will determine their uncertainty
w.var("mean").setConstant(0)      #Don't fix the mean, it's what we want to know the interval for!
w.var("sigma").setConstant(1)
w.var("tau").setConstant(1)
w.var("Nsig").setConstant(1)
w.var("Nbkg").setConstant(1)

#Set the RooModelConfig and let it know what the content of the workspace is about
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(w)
model.SetPdf("PDFtot")

#Let the model know what is the parameter of interest
mean = w.var("mean")
mean.setRange(120., 130.) #This is mostly for plotting reasons
poi = ROOT.RooArgSet(mean)

#Set confidence level
confidenceLevel = 0.68

#Build the profile likelihood calculator
plc = ROOT.RooStats.ProfileLikelihoodCalculator()
plc.SetData(w.data("PDFtotData"))
plc.SetModel(model)
plc.SetParameters(poi)
plc.SetConfidenceLevel(confidenceLevel)

#Get the interval
plInt = plc.GetInterval()

#Now let's do the same for the Bayesian Calculator
#Now we also need to specify a prior in the ModelConfig
#To be quicker, we'll use the PDF factory facility of RooWorkspace
#NB!! For simplicity, we are using a flat prior, but this doesn't mean it's the best choice!
w.factory("Uniform::prior(mean)")
model.SetPriorPdf(w.pdf("prior"))

#Construct the bayesian calculator
bc = ROOT.RooStats.BayesianCalculator(w.data("PDFtotData"), model)
bc.SetConfidenceLevel(confidenceLevel)
bc.SetParameters(poi)
bcInt = bc.GetInterval()

#Let's make a plot
canvas = ROOT.TCanvas()
canvas.Divide(2,1)
canvas.cd(1)

plotInt = ROOT.RooStats.LikelihoodIntervalPlot(plInt)
plotInt.SetTitle("Profile Likelihood Ratio and Posterior for mH")
plotInt.SetMaximum(3.)
plotInt.Draw()

canvas.cd(2)
bcPlot = bc.GetPosteriorPlot()
bcPlot.Draw()

canvas.SaveAs("exercise_9.png")

#Now print the interval for mH for the two methods
print "PLC interval is [", plInt.LowerLimit(mean), ", ", plInt.UpperLimit(mean), "]"

print "Bayesian interval is [", bcInt.LowerLimit(), ", ", bcInt.UpperLimit(), "]"
