import ROOT

#Open the rootfile and get the workspace from the exercise_0
fInput = ROOT.TFile("Workspace_mumufit.root")
ws = fInput.Get("ws")
ws.Print()

#You can set constant parameters that are known
#If you leave them floating, the fit procedure will determine their uncertainty
# meanpsi2S is no more constant!
ws.var("meanJpsi").setConstant(1)
ws.var("sigmaJpsi").setConstant(1)
ws.var("alphaJpsi").setConstant(1)
ws.var("nJpsi").setConstant(1)
ws.var("NJpsi").setConstant(1)
ws.var("Npsi").setConstant(1)    #not anymore the parameter of interest!
ws.var("Nbkg").setConstant(1)
ws.var("a1").setConstant(1)
ws.var("a2").setConstant(1)
ws.var("a3").setConstant(1)

#Let the model know what is the parameter of interest
meanpsi2S = ws.var("meanpsi2S")
meanpsi2S.setRange(3.66, 3.7);  #this is mostly for plotting reasons
poi = ROOT.RooArgSet(meanpsi2S)

#Configure the model
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(ws)
model.SetPdf("totPDF")
model.SetParametersOfInterest(poi)

#Set confidence level
confidenceLevel = 0.68

#Build the profile likelihood calculator
plc = ROOT.RooStats.ProfileLikelihoodCalculator()
plc.SetData(ws.data("data"))
plc.SetModel(model)
plc.SetParameters(poi)
plc.SetConfidenceLevel(confidenceLevel)

#Get the interval
pl_Interval = plc.GetInterval()

#Now let's determine the Bayesian probability interval
#We could use the standard Bayesian Calculator, but this would be very slow for the integration
#So we profit of the Markov-Chain MC capabilities of RooStats to speed things up

mcmc = ROOT.RooStats.MCMCCalculator(ws.data("data") , model)
mcmc.SetConfidenceLevel(confidenceLevel)
mcmc.SetNumIters(20000)           #Metropolis-Hastings algorithm iterations
mcmc.SetNumBurnInSteps(100)       #first N steps to be ignored as burn-in
mcmc.SetLeftSideTailFraction(0.5) #for central interval

MCMC_interval = mcmc.GetInterval()

#Let's make a plot
dataCanvas = ROOT.TCanvas("dataCanvas")
dataCanvas.Divide(2,1)

dataCanvas.cd(1)
plot_Interval = ROOT.RooStats.LikelihoodIntervalPlot(pl_Interval)
plot_Interval.SetTitle("Profile Likelihood Ratio")
plot_Interval.SetMaximum(3.)
plot_Interval.Draw()

dataCanvas.cd(2)
plot_MCMC = ROOT.RooStats.MCMCIntervalPlot(MCMC_interval)
plot_MCMC.SetTitle("Bayesian probability interval (Markov Chain)")
plot_MCMC.Draw()

dataCanvas.SaveAs("exercise_3.png")

#Now print the interval for mH for the two methods
print "PLC interval is [", pl_Interval.LowerLimit(meanpsi2S), ", ", pl_Interval.UpperLimit(meanpsi2S), "]"

print "Bayesian interval is [", MCMC_interval.LowerLimit(meanpsi2S), ", ", MCMC_interval.UpperLimit(meanpsi2S), "]"

#PyROOT sometimes fails cleaning memory, this helps
del plc
