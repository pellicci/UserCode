
import ROOT

#Open the rootfile and get the workspace from the exercise_0
fInput = ROOT.TFile("Workspace_mumufit.root")
ws = fInput.Get("ws")

ws.Print()

#You can set constant parameters that are known
#If you leave them floating, the fit procedure will determine their uncertainty
ws.var("meanJpsi").setConstant(1)

#Set the RooModelConfig and let it know what the content of the workspace is about
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(ws)
model.SetPdf("totPDF")

#Here we explicitly set the value of the parameters for the null hypothesis
#We want no signal contribution, so cross_psi = 0
cross_psi = ws.var("cross_psi")
poi = ROOT.RooArgSet(cross_psi)
nullParams = poi.snapshot()
nullParams.setRealValue("cross_psi",0.)

#Build the profile likelihood calculator
plc = ROOT.RooStats.ProfileLikelihoodCalculator()

plc.SetData(ws.data("data"))
plc.SetModel(model)
plc.SetParameters(poi)
plc.SetNullParameters(nullParams)

#We get a HypoTestResult out of the calculator, and we can query it.
htr = plc.GetHypoTest()

print "-------------------------------------------------"
print "The p-value for the null is ", htr.NullPValue()
print "Corresponding to a signifcance of ", htr.Significance()
print "-------------------------------------------------"

#PyROOT sometimes fails cleaning memory, this helps
del plc
