
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
Npsi = ws.var("Npsi")
Nbkg = ws.var("Nbkg")

#Set the RooModelConfig and let it know what the content of the workspace is about
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(ws)
model.SetPdf("totPDF")
model.SetNuisanceParameters(ROOT.RooArgSet(ws.var("NJpsi")))

#Here we explicitly set the value of the parameters for the null.  
#We want no signal contribution, eg. Nsig = 0
Npsi = ws.var("Npsi")
poi = ROOT.RooArgSet(Npsi)
nullParams = poi.snapshot()
nullParams.setRealValue("Npsi",0.)

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
plot_Interval.SetTitle("Profile Likelihood Ratio for Npsi")
plot_Interval.SetRange(200.,350.)
plot_Interval.SetMaximum(10.)
plot_Interval.Draw()

#We will partly redo exercise_0 to redefine the signal PDF to account for uncertainties on parameters
#J/psi PDF
cb_jpsi = ws.pdf("CBJpsi")

#Signal PDF
gauss2S = ws.pdf("gausspsi2S")

#Background PDF
backgroundPDF = ws.pdf("backgroundPDF")

#Assume an uncertainty on the number of psi events
#Construct the uncertainty with a lognormal assumption
N_kappa = ROOT.RooRealVar("N_kappa","Dimension of systematic variation of Nbkg",1.3)    #30% systematic
N_beta  = ROOT.RooRealVar("N_beta","This is the real nuisance on N",0.,-5.,5.)
N_alpha = ROOT.RooFormulaVar("N_alpha","pow(@0,@1)",ROOT.RooArgList(N_kappa,N_beta))

NJpsi_nuis = ROOT.RooFormulaVar("NJpsi_nuis","@0*@1",ROOT.RooArgList(NJpsi,N_alpha))
Npsi_nuis  = ROOT.RooFormulaVar("Npsi_nuis","@0*@1",ROOT.RooArgList(Npsi,N_alpha))

#Now prepare a gaussian for the nuisance parameter, to be multiplied to the total PDF
one = ROOT.RooRealVar("one","one",1.)
N_syst = ROOT.RooRealVar("N_syst","The systematic uncertainty space on N",0.,-5.,5.)
constr_N = ROOT.RooGaussian("constr_N","N uncertainty constraint",N_beta,N_syst,one)

#Now construct the "new" total PDF
PDFtot_nuis_unconstr = ROOT.RooAddPdf("PDFtot_nuis_unconstr","PDFtot_nuis_unconstr",ROOT.RooArgList(cb_jpsi,gauss2S,backgroundPDF),ROOT.RooArgList(NJpsi_nuis,Npsi_nuis,Nbkg))
 
#Now add the gaussian constraint to the total PDF
PDFtot_nuis = ROOT.RooProdPdf("PDFtot_nuis","PDFtot_nuis",ROOT.RooArgList(PDFtot_nuis_unconstr,constr_N))


#We now have two PDFs:
getattr(ws,'import')(PDFtot_nuis)

model_nuis = ROOT.RooStats.ModelConfig()
model_nuis.SetWorkspace(ws)
model_nuis.SetPdf("PDFtot_nuis")
model_nuis.SetGlobalObservables(ROOT.RooArgSet(ws.var("N_syst")))
model_nuis.SetNuisanceParameters(ROOT.RooArgSet(ws.var("N_beta"), ws.var("NJpsi"), ws.var("Nbkg")))

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
plot_Interval_nuis.SetRange(200.,350.)
plot_Interval_nuis.SetContourColor(ROOT.kRed)
plot_Interval_nuis.Draw("SAME")

dataCanvas.SaveAs("exercise_4.png")

#PyROOT sometimes fails cleaning memory, this helps
del plc
del plc_nuis
