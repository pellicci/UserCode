
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
w.var("meanpsi").setConstant(1)
w.var("a1").setConstant(1)
w.var("a2").setConstant(1)
w.var("a3").setConstant(1)
w.var("Nbkg").setConstant(1)
w.var("NJpsi").setConstant(1)

#Set the RooModelConfig and let it know what the content of the workspace is about
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(w)
model.SetPdf("totPDF")

#Here we explicitly set the value of the parameters for the null.  
#We want no signal contribution, so Npsi = 0
Npsi = w.var("Npsi")
poi = ROOT.RooArgSet(Npsi)
nullParams = poi.snapshot() 
nullParams.setRealValue("Npsi",0.)

#Build the profile likelihood calculator
plc = ROOT.RooStats.ProfileLikelihoodCalculator()

plc.SetData(w.data("data"))
plc.SetModel(model)
plc.SetParameters(poi)
plc.SetNullParameters(nullParams)

#We get a HypoTestResult out of the calculator, and we can query it.
htr = plc.GetHypoTest();

print "-------------------------------------------------"
print "The p-value for the null is ", htr.NullPValue()
print "Corresponding to a signifcance of ", htr.Significance()
print "-------------------------------------------------"
