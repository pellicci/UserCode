
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
ws.var("meanpsi2S").setConstant(1)      #now this is again constant, not anymore our parameter of interest!
ws.var("Nbkg").setConstant(1)
ws.var("a1").setConstant(1)
ws.var("a2").setConstant(1)
ws.var("a3").setConstant(1)

#Now define the number of signal and background events
NJpsi = ws.var("NJpsi")
cross_psi = ws.var("cross_psi")
lumi_psi = ws.var("lumi_psi")
eff_psi = ws.var("eff_psi")
Nbkg = ws.var("Nbkg")


#Set the RooModelConfig and let it know what the content of the workspace is about
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(ws)
model.SetPdf("totPDF")
model.SetNuisanceParameters(ROOT.RooArgSet(ws.var("NJpsi")))

#Here we explicitly set the value of the parameters for the null.  
#We want no signal contribution, eg. cross_psi = 0
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
print "Without background uncertainty"
print "The p-value for the null is ", htr.NullPValue()
print "Corresponding to a signifcance of ", htr.Significance()
print "-------------------------------------------------"

#Now get the intervals to do some plots
plc.SetConfidenceLevel(0.68)
pl_Interval = plc.GetInterval()

#Let's make a plot
dataCanvas = ROOT.TCanvas("dataCanvas")
dataCanvas.cd()

plot_Interval = ROOT.RooStats.LikelihoodIntervalPlot(pl_Interval)
plot_Interval.SetTitle("Profile Likelihood Ratio for cross_psi")
plot_Interval.SetRange(4.,16.)
plot_Interval.SetMaximum(10.)
plot_Interval.Draw()

#We will partly redo exercise_0 to redefine the signal PDF to account for uncertainties on parameters
#J/psi PDF
cb_jpsi = ws.pdf("CBJpsi")

#Signal PDF
gauss2S = ws.pdf("gausspsi2S")

#Background PDF
backgroundPDF = ws.pdf("backgroundPDF")

#Assume an uncertainty on the luminosity
#Construct the uncertainty with a lognormal assumption
kappa_lumi = ROOT.RooRealVar("kappa_lumi","Dimension of systematic variation",1.1)    #10% systematic
beta_lumi  = ROOT.RooRealVar("beta_lumi","This is the real nuisance on lumi",0.,-5.,5.)
alpha_lumi = ROOT.RooFormulaVar("alpha_lumi","pow(@0,@1)",ROOT.RooArgList(kappa_lumi,beta_lumi))

lumi_psi_nuis  = ROOT.RooFormulaVar("lumi_psi_nuis","@0*@1",ROOT.RooArgList(lumi_psi,alpha_lumi))

#Now prepare a gaussian for the nuisance parameter, to be multiplied to the total PDF
one = ROOT.RooRealVar("one","one",1.)
lumi_syst = ROOT.RooRealVar("lumi_syst","The systematic uncertainty space on lumi",0.,-5.,5.)
constr_lumi = ROOT.RooGaussian("constr_lumi","Lumi uncertainty constraint",beta_lumi,lumi_syst,one)

#Now write the new Npsi = xsec * eff * lumi * alpha_lumi
Npsi_nuised = ROOT.RooFormulaVar("Npsi_nuised","@0*@1*@2", ROOT.RooArgList(eff_psi,lumi_psi_nuis,cross_psi))

#Now construct the "new" total PDF
PDFtot_nuis_unconstr = ROOT.RooAddPdf("PDFtot_nuis_unconstr","PDFtot_nuis_unconstr",ROOT.RooArgList(cb_jpsi,gauss2S,backgroundPDF),ROOT.RooArgList(NJpsi,Npsi_nuised,Nbkg))
 
#Now add the gaussian constraint to the total PDF
PDFtot_nuis = ROOT.RooProdPdf("PDFtot_nuis","PDFtot_nuis",ROOT.RooArgList(PDFtot_nuis_unconstr,constr_lumi))

#We now have two PDFs:
getattr(ws,'import')(PDFtot_nuis)

model_nuis = ROOT.RooStats.ModelConfig()
model_nuis.SetWorkspace(ws)
model_nuis.SetPdf("PDFtot_nuis")
model_nuis.SetGlobalObservables(ROOT.RooArgSet(ws.var("lumi_syst")))
model_nuis.SetNuisanceParameters(ROOT.RooArgSet(ws.var("beta_lumi"), ws.var("NJpsi"), ws.var("Nbkg")))

#Build the profile likelihood calculator with the Nbkg uncertainty
plc_nuis = ROOT.RooStats.ProfileLikelihoodCalculator()
plc_nuis.SetData(ws.data("data"))
plc_nuis.SetModel(model_nuis)
plc_nuis.SetParameters(poi)
plc_nuis.SetNullParameters(nullParams)

#We get a HypoTestResult out of the calculator, and we can query it.
htr_nuis = plc_nuis.GetHypoTest()

print "-------------------------------------------------"
print "With background uncertainty"
print "The p-value for the null is ", htr_nuis.NullPValue()
print "Corresponding to a signifcance of ", htr_nuis.Significance()
print "-------------------------------------------------"

#Now get the intervals to do some plots
plc_nuis.SetConfidenceLevel(0.68)
pl_Interval_nuis = plc_nuis.GetInterval()

#Let's make a plot
plot_Interval_nuis = ROOT.RooStats.LikelihoodIntervalPlot(pl_Interval_nuis)
plot_Interval_nuis.SetRange(4.,16.)
plot_Interval_nuis.SetContourColor(ROOT.kRed)
plot_Interval_nuis.Draw("SAME")

dataCanvas.SaveAs("exercise_6.png")

#PyROOT sometimes fails cleaning memory, this helps
del plc
del plc_nuis
