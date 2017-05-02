
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
w.var("Nbkg").setConstant(1)

#Set the RooModelConfig and let it know what the content of the workspace is about
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(w)
model.SetPdf("PDFtot")

#Here we explicitly set the value of the parameters for the null.  
#We want no signal contribution, so Nsig = 0
Nsig = w.var("Nsig")
poi = ROOT.RooArgSet(Nsig)
nullParams = poi.snapshot()
nullParams.setRealValue("Nsig",0.)

#Build the profile likelihood calculator
plc = ROOT.RooStats.ProfileLikelihoodCalculator()

plc.SetData(w.data("PDFtotData"))
plc.SetModel(model)
plc.SetParameters(poi)
plc.SetNullParameters(nullParams)

#We get a HypoTestResult out of the calculator, and we can query it.
hypo_test_result = plc.GetHypoTest()
print "-------------------------------------------------"
print "The p-value for the null is ", hypo_test_result.NullPValue()
print "Corresponding to a signifcance of ", hypo_test_result.Significance()
print "-------------------------------------------------"
