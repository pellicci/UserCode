
import ROOT

#Open the rootfile and get the workspace from the exercise_0
fInput = ROOT.TFile("Workspace_mumufit.root")
ws = fInput.Get("ws")
ws.Print()

#You can set constant parameters that are known
#If you leave them floating, the fit procedure will determine their uncertainty
#Right now we will fix all the nuisance parameters just to speed up the computing time
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

#Configure the model, we need both the S+B and the B only models
sbModel = ROOT.RooStats.ModelConfig()
sbModel.SetWorkspace(ws)
sbModel.SetPdf("totPDF")
sbModel.SetName("S+B Model")
poi = ROOT.RooArgSet(ws.var("cross_psi"))
poi.find("cross_psi").setRange(0.,40.)  #this is mostly for plotting
sbModel.SetParametersOfInterest(poi)

bModel = sbModel.Clone()
bModel.SetPdf("totPDF")
bModel.SetName( sbModel.GetName() + "_with_poi_0")
poi.find("cross_psi").setVal(0)
bModel.SetSnapshot(poi)

#First example is with a frequentist approach
fc = ROOT.RooStats.FrequentistCalculator(ws.data("data"), bModel, sbModel)
fc.SetToys(1000,500)

#Create hypotest inverter passing the desired calculator 
calc = ROOT.RooStats.HypoTestInverter(fc)

#set confidence level (e.g. 95% upper limits)
calc.SetConfidenceLevel(0.95)

#use CLs
calc.UseCLs(1)

#reduce the noise
calc.SetVerbose(0)

#Configure ToyMC Samler
toymcs = calc.GetHypoTestCalculator().GetTestStatSampler()

#Use profile likelihood as test statistics 
profll = ROOT.RooStats.ProfileLikelihoodTestStat(sbModel.GetPdf())

#for CLs (bounded intervals) use one-sided profile likelihood
profll.SetOneSided(1)

#set the test statistic to use for toys
toymcs.SetTestStatistic(profll)

npoints = 8 #Number of points to scan
# min and max for the scan (better to choose smaller intervals)
poimin = poi.find("cross_psi").getMin()
poimax = poi.find("cross_psi").getMax()

print "Doing a fixed scan  in interval : ", poimin, " , ", poimax
calc.SetFixedScan(npoints,poimin,poimax);

result = calc.GetInterval() #This is a HypoTestInverter class object
upperLimit = result.UpperLimit()

#Example using the BayesianCalculator
#Now we also need to specify a prior in the ModelConfig
#To be quicker, we'll use the PDF factory facility of RooWorkspace
#Careful! For simplicity, we are using a flat prior, but this doesn't mean it's the best choice!
ws.factory("Uniform::prior(cross_psi)")
sbModel.SetPriorPdf(ws.pdf("prior"))

#Construct the bayesian calculator
bc = ROOT.RooStats.BayesianCalculator(ws.data("data"), sbModel)
bc.SetConfidenceLevel(0.95)
bc.SetLeftSideTailFraction(0.) # for upper limit

bcInterval = bc.GetInterval();

#Let's add FC!
fc = ROOT.RooStats.FeldmanCousins(ws.data("data"), sbModel)
fc.SetTestSize(.05) # set size of test
fc.UseAdaptiveSampling(1)
fc.SetNBins(10) #number of points to test per parameter
fcInterval = fc.GetInterval()

#Now let's print the result of the two methods
#First the CLs
print "################"
print "The observed CLs upper limit is: ", upperLimit

#Compute expected limit
print "Expected upper limits, using the B (alternate) model : "
print " expected limit (median) ", result.GetExpectedUpperLimit(0)
print " expected limit (-1 sig) ", result.GetExpectedUpperLimit(-1)
print " expected limit (+1 sig) ", result.GetExpectedUpperLimit(1)
print "################"

#Now let's see what the bayesian limit is
print "Bayesian upper limit on cross_psi = ", bcInterval.UpperLimit()
print "################"

#Now the Feldman-Cousins
print "Feldman-Cousins upper limit = ", fcInterval.UpperLimit(ws.var("cross_psi")) 

#Plot now the result of the scan 

#First the CLs
freq_plot = ROOT.RooStats.HypoTestInverterPlot("HTI_Result_Plot","Frequentist scan result for psi xsec",result)
#Then the Bayesian posterior
bc_plot = bc.GetPosteriorPlot()

#Plot in a new canvas with style
dataCanvas = ROOT.TCanvas("dataCanvas")
dataCanvas.Divide(2,1)
dataCanvas.SetLogy(0)
dataCanvas.cd(1)
freq_plot.Draw("2CL")
dataCanvas.cd(2)
bc_plot.Draw()
dataCanvas.SaveAs("exercise_3.png")
