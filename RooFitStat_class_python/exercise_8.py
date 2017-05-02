
import ROOT

#Open the rootfile and get the workspace from the exercise_6
fInput = ROOT.TFile("exercise_6.root")
fInput.cd()
w = fInput.Get("w")

#You can set constant parameters that are known
#If you leave them floating, the fit procedure will determine their uncertainty
w.var("mean").setConstant(1)
w.var("sigma").setConstant(1)
w.var("tau").setConstant(1)

#Configure the model, we need both the S+B and the B only models
sbModel = ROOT.RooStats.ModelConfig()
sbModel.SetWorkspace(w)
sbModel.SetPdf("PDFtot")
sbModel.SetName("S+B Model")

poi = w.var("Nsig")
poi.setRange(0.,30.) #this is mostly for plotting
sbModel.SetParametersOfInterest(ROOT.RooArgSet(poi))

bModel = sbModel.Clone()
bModel.SetPdf("PDFtot")
bModel.SetName(sbModel.GetName() + "_with_poi_0")
poi.setVal(0)
bModel.SetSnapshot(ROOT.RooArgSet(poi))

fc = ROOT.RooStats.FrequentistCalculator(w.data("PDFtotData"), bModel, sbModel)
fc.SetToys(2000,1000)

#Create hypotest inverter passing the desired calculator 
calc = ROOT.RooStats.HypoTestInverter(fc)

#Set confidence level (e.g. 95% upper limits)
calc.SetConfidenceLevel(0.95)

#use CLs
calc.UseCLs(1)

#Reduce the noise
calc.SetVerbose(0)

#Configure ToyMC Samler
toymcs = calc.GetHypoTestCalculator().GetTestStatSampler()

#Set Profile likelihood test statistics 
profll = ROOT.RooStats.ProfileLikelihoodTestStat(sbModel.GetPdf())
#For CLs (bounded intervals) use one-sided profile likelihood
profll.SetOneSided(1)

#Set the test statistic to use
toymcs.SetTestStatistic(profll)

npoints = 15 #Number of points to scan
#min and max (better to choose smaller intervals)
poimin = poi.getMin()
poimax = poi.getMax()

print "Doing a fixed scan  in interval : ", poimin, " , ",  poimax
calc.SetFixedScan(npoints,poimin,poimax)
  
result_freq = calc.GetInterval()
upperLimit = result_freq.UpperLimit()

#Example using the BayesianCalculator
#Now we also need to specify a prior in the ModelConfig
#To be quicker, we'll use the PDF factory facility of RooWorkspace
#NB!! For simplicity, we are using a flat prior, but this doesn't mean it's the best choice!
w.factory("Uniform::prior(Nsig)")
sbModel.SetPriorPdf(w.pdf("prior"))

#Construct the bayesian calculator
bc = ROOT.RooStats.BayesianCalculator(w.data("PDFtotData"), sbModel)
bc.SetConfidenceLevel(0.95)
bc.SetLeftSideTailFraction(0.) #for upper limit
bc_Int = bc.GetInterval()

#Now let's print the result of the two methods
#First the CLs
print "################"
print "The computed CLs upper limit is: ", upperLimit

#Compute expected limit
print "Expected upper limits, using the B (alternate) model : "
print " expected limit (median) ", result_freq.GetExpectedUpperLimit(0)
print " expected limit (-1 sig) ", result_freq.GetExpectedUpperLimit(-1)
print " expected limit (+1 sig) ", result_freq.GetExpectedUpperLimit(1)
print "################"

#Now let's see what the bayesian limit is
print "Bayesian upper limit on Nsig = ", bc_Int.UpperLimit()

#Plot now the result of the scan 
#First the CLs
plot = ROOT.RooStats.HypoTestInverterPlot("HTI_Result_Plot","HypoTest Scan Result",result_freq)
#Then the Bayesian posterior
bcPlot = bc.GetPosteriorPlot()

#Plot in a new canvas with style
canvas = ROOT.TCanvas()
canvas.Divide(2,1)
canvas.SetLogy(0)
canvas.cd(1)
plot.Draw("2CL")
canvas.cd(2)
bcPlot.Draw()
canvas.SaveAs("exercise_8.png")
