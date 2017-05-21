
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

#We will partly redo exercise_6 to redefine the signal PDF to account for uncertainties on parameters
#Signal PDF
gauss = w.pdf("gauss")

#Background PDF
exponential = w.pdf("exponential")

#Now define the number of signal and background events
Nsig = w.var("Nsig")
Nbkg = w.var("Nbkg")
Nsig.setRange(0.,30.)

#Assume an uncertainty on the number of background events
#Construct the uncertainty with a lognormal assumption
Nbkg_alpha = ROOT.RooRealVar("Nbkg_alpha","Dimension of systematic variation of Nbkg",1.,0.01,10.)
Nbkg_nuis = ROOT.RooFormulaVar("Nbkg_nuis","@0*@1", ROOT.RooArgList(Nbkg,Nbkg_alpha))

#Now prepare a gaussian for the nuisance parameter, to be multiplied to the total PDF
one = ROOT.RooRealVar("one","one",1.)
Nbkg_syst = ROOT.RooRealVar("Nbkg_syst","The systematic uncertainty on Nbkg",0.3)  #30% uncertainty
constr_Nbkg = ROOT.RooGaussian("constr_Nbkg","Background uncertainty constraint",one,Nbkg_alpha,Nbkg_syst)

#Now construct the total PDF
PDFtot_nuis_unconstr = ROOT.RooAddPdf("PDFtot_nuis_unconstr","PDFtot_nuis_unconstr", ROOT.RooArgList(gauss,exponential), ROOT.RooArgList(Nsig,Nbkg_nuis))
 
#Now add the gaussian constraint to the total PDF
PDFtot_nuis = ROOT.RooProdPdf("PDFtot_nuis","PDFtot_nuis", ROOT.RooArgList(PDFtot_nuis_unconstr,constr_Nbkg))

PDFtot_nuis.fitTo(w.data("PDFtotData"), ROOT.RooFit.Constrain( ROOT.RooArgSet(Nbkg_alpha)), ROOT.RooFit.Extended(1))

#We now have two PDFs
getattr(w,'import')(PDFtot_nuis)

#Set the RooModelConfig and let it know what the content of the workspace is about
model = ROOT.RooStats.ModelConfig()
model.SetWorkspace(w)
model.SetPdf("PDFtot")

model_nuis = ROOT.RooStats.ModelConfig()
model_nuis.SetWorkspace(w)
model_nuis.SetPdf("PDFtot_nuis")

#Here we explicitly set the value of the parameters for the null.  
#We want no signal contribution, eg. Nsig = 0
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
htr = plc.GetHypoTest()

#Build the profile likelihood calculator with the Nbkg uncertainty
plc_nuis = ROOT.RooStats.ProfileLikelihoodCalculator()
plc_nuis.SetData(w.data("PDFtotData"))
plc_nuis.SetModel(model_nuis)
plc_nuis.SetParameters(poi)
plc_nuis.SetNullParameters(nullParams)

#We get a HypoTestResult out of the calculator, and we can query it.
htr_nuis = plc_nuis.GetHypoTest()

print "-------------------------------------------------"
print "Without background uncertainty"
print "The p-value for the null is ", htr.NullPValue()
print "Corresponding to a signifcance of ", htr.Significance()
print "-------------------------------------------------"

print "-------------------------------------------------"
print "With background uncertainty"
print "The p-value for the null is ", htr_nuis.NullPValue()
print "Corresponding to a signifcance of ", htr_nuis.Significance()
print "-------------------------------------------------"

#Now get the intervals to do some plots
plc.SetConfidenceLevel(0.68)
plc_nuis.SetConfidenceLevel(0.68)

plInt = plc.GetInterval()
plInt_nuis = plc_nuis.GetInterval()

#Let's make a plot
canvas = ROOT.TCanvas()
canvas.cd()

plotInt = ROOT.RooStats.LikelihoodIntervalPlot(plInt)
plotInt.SetTitle("Profile Likelihood Ratio for Nsig")
plotInt.SetMaximum(10.)
plotInt.Draw()

plotInt_nuis = ROOT.RooStats.LikelihoodIntervalPlot(plInt_nuis)
plotInt_nuis.SetContourColor(ROOT.kRed)
plotInt_nuis.Draw("SAME")

canvas.SaveAs("exercise_10.png")
