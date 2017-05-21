
import ROOT

#Open the rootfile and get the workspace from the exercise_0_p1
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
ws.var("cross_psi").setConstant(1)    #not anymore the parameter of interest!
ws.var("Nbkg").setConstant(1)
ws.var("a1").setConstant(1)
ws.var("a2").setConstant(1)
ws.var("a3").setConstant(1)

#Let the model know what is the parameter of interest
meanpsi2S = ws.var("meanpsi2S")
meanpsi2S.setConstant(0)
meanpsi2S.setRange(3.6858, 3.6864)  #this is mostly for plotting reasons
poi = ROOT.RooArgSet(meanpsi2S)

#Configure the model
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(ws)
model.SetPdf("totPDF")
model.SetParametersOfInterest(poi)

#Set confidence level
confidenceLevel = 0.68

#Now let's determine the Bayesian probability interval
#We could use the standard Bayesian Calculator, but this would be very slow for the integration
#So we profit of the Markov-Chain MC capabilities of RooStats to speed things up

mcmc = ROOT.RooStats.MCMCCalculator(ws.data("data") , model)
mcmc.SetConfidenceLevel(confidenceLevel)
mcmc.SetNumIters(10000)           #Metropolis-Hastings algorithm iterations
mcmc.SetNumBurnInSteps(5)       #first N steps to be ignored as burn-in
mcmc.SetLeftSideTailFraction(0.5) #for central interval

#Now we add a prior using known measurements
ws.factory("Gaussian::prior(meanpsi2S,m[3.686097],s[0.000025])")
mcmc.SetPriorPdf(ws.pdf("prior"))

MCMC_interval = mcmc.GetInterval()

#Let's make a plot
dataCanvas = ROOT.TCanvas("dataCanvas")
plot_MCMC = ROOT.RooStats.MCMCIntervalPlot(MCMC_interval)
plot_MCMC.SetTitle("Bayesian probability interval (Markov Chain)")
plot_MCMC.Draw()

dataCanvas.SaveAs("exercise_5_p1.png")

print "Bayesian interval is [", MCMC_interval.LowerLimit(meanpsi2S), ", ", MCMC_interval.UpperLimit(meanpsi2S), "]"
