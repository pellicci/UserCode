
import ROOT

#Open the rootfile and get the workspace from the exercise_0
fInput = ROOT.TFile("Workspace_mumufit.root")
ws = fInput.Get("ws")
ws.Print()

#You can set constant parameters that are known
#If you leave them floating, the fit procedure will determine their uncertainty
ws.var("meanJpsi").setConstant(1)
ws.var("sigmaJpsi").setConstant(1)
ws.var("alphaJpsi").setConstant(1)
ws.var("nJpsi").setConstant(1)
ws.var("NJpsi").setConstant(1)
ws.var("meanpsi2S").setConstant(1)
ws.var("Nbkg").setConstant(1)
ws.var("a1").setConstant(1)
ws.var("a2").setConstant(1)
ws.var("a3").setConstant(1)

#Create a modifier to account for signal efficiency uncertainty
ws.factory("Gaussian::effConstrain(gSigEff[1.],ratioSigEff[1.,0.,3],0.1)")   #Gaussian with 10% uncertainty
ws.factory("SUM::totPDF_withscaling( prod(cross_psi,lumi_psi,eff_psi,ratioSigEff)*CBpsi2S , NJpsi*CBJpsi, Nbkg*backgroundPDF )") #Recreate the total PDF with the scaling
ws.factory("PROD::totPDF_withconstrain(totPDF_withscaling, effConstrain)")

print "##################################"
print "Now printing the workspace with the additional constraints"
print "##################################"
print ws.Print()

#Let the model know what is the parameter of interest
cross_psi = ws.var("cross_psi")
cross_psi.setRange(4., 16.)  #this is mostly for plotting reasons
poi = ROOT.RooArgSet(cross_psi)

ratioSigEff = ws.var("ratioSigEff")
constrainedParams = ROOT.RooArgSet(ratioSigEff)

#Configure the model
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(ws)
model.SetPdf("totPDF_withconstrain")
model.SetParametersOfInterest(poi)
model.SetNuisanceParameters(constrainedParams)
model.SetObservables( ROOT.RooArgSet(ws.var("mass")) )
model.SetGlobalObservables( ROOT.RooArgSet(ws.var("gSigEff")) )

#Set confidence level
confidenceLevel = 0.68

#Build the profile likelihood calculator
plc = ROOT.RooStats.ProfileLikelihoodCalculator(ws.data("data"), model)
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

dataCanvas.SaveAs("exercise_5.png")

#Now print the interval for mH for the two methods
print "PLC interval is [", pl_Interval.LowerLimit(cross_psi), ", ", pl_Interval.UpperLimit(cross_psi), "]"

print "Bayesian interval is [", MCMC_interval.LowerLimit(cross_psi), ", ", MCMC_interval.UpperLimit(cross_psi), "]"

#PyROOT sometimes fails cleaning memory, this helps
del plc
