import ROOT

fInput = ROOT.TFile("DataSet_lowstat.root")
dataset = fInput.Get("data")

#The observable
mass = ROOT.RooRealVar("mass","#mu^{+}#mu^{-} invariant mass",2.,6.,"GeV")

#The Jpsi signal parametrization: we'll use a Crystal Ball
meanJpsi = ROOT.RooRealVar("meanJpsi","The mean of the Jpsi Gaussian",3.1,2.8,3.2)
sigmaJpsi = ROOT.RooRealVar("sigmaJpsi","The width of the Jpsi Gaussian",0.3,0.0001,1.)
alphaJpsi = ROOT.RooRealVar("alphaJpsi","The alpha of the Jpsi Gaussian",1.5,-5.,5.)
nJpsi = ROOT.RooRealVar("nJpsi","The alpha of the Jpsi Gaussian",1.5,0.5,5.)
CBJpsi = ROOT.RooCBShape("CBJpsi","The Jpsi Crystall Ball",mass,meanJpsi,sigmaJpsi,alphaJpsi,nJpsi)

#The psi(2S) signal parametrization: width will be similar to Jpsi core of the CB (almost Gaussian)
#Set the mean constant from the previous fit if allowing a negative value for the cross_section, or it will make the fit unstable
meanpsi2S = ROOT.RooRealVar("meanpsi2S","The mean of the psi(2S) Gaussian",3.7,3.65,3.75)
#meanpsi2S.setConstant(1)
gausspsi2S = ROOT.RooGaussian("gausspsi2S","The psi(2S) Gaussian",mass,meanpsi2S,sigmaJpsi)

#Background parametrization: just a polynomial
a1 = ROOT.RooRealVar("a1","The a1 of background",-0.7,-2.,2.)
a2 = ROOT.RooRealVar("a2","The a2 of background",0.3,-2.,2.)
a3 = ROOT.RooRealVar("a3","The a3 of background",-0.03,-2.,2.)
backgroundPDF = ROOT.RooChebychev("backgroundPDF","The background PDF",mass,ROOT.RooArgList(a1,a2,a3))

#Compose the total PDF
NJpsi = ROOT.RooRealVar("NJpsi","The Jpsi signal events",1500.,0.1,10000.)
Nbkg = ROOT.RooRealVar("Nbkg","The bkg events",5000.,0.1,50000.)

#Now define the number of psi(2S) events as a product of crss section*efficiency*luminosity (in pb)
#Let's assume we measured the trigger, reconstruction and identification efficiency for dimuons and found it to be 95%
#Lowstat sample has 0.64 pb-1
#Fullstat sample has 37 pb-1
eff_psi = ROOT.RooRealVar("eff_psi","The psi efficiency",0.75,0.00001,1.)
lumi_psi  = ROOT.RooRealVar("lumi_psi","The CMS luminosity",0.64,0.00001,50.,"pb-1")
cross_psi = ROOT.RooRealVar("cross_psi","The psi xsec",3.,-40.,40.)

#Now define the number of psi events
Npsi = ROOT.RooFormulaVar("Npsi","@0*@1*@2",ROOT.RooArgList(eff_psi,lumi_psi,cross_psi))

#Write the total PDF
totPDF = ROOT.RooAddPdf("totPDF","The total PDF",ROOT.RooArgList(CBJpsi,gausspsi2S,backgroundPDF),ROOT.RooArgList(NJpsi,Npsi,Nbkg))

#Important! We cannot fit simultaneously the efficiency, the luminosity and the cross section (our total PDF is only sensitive on the product of the three)
#We need to fix two of them, so we'll keep our POI floating
#One can also add an additional PDF to give predictive power on the other two parameters (later)
eff_psi.setConstant(1)
lumi_psi.setConstant(1)

#Do the actual fit
totPDF.fitTo(dataset,ROOT.RooFit.Extended(1))

#Print values of the parameters (that now reflect fitted values and errors)
print "##############"
Npsi.Print()
cross_psi.Print()
print "##############"

#Now plot the data and the fit result
xframe = mass.frame()
dataset.plotOn(xframe)
totPDF.plotOn(xframe)

#One can also plot the single components of the total PDF, like the background component
totPDF.plotOn(xframe, ROOT.RooFit.Components("backgroundPDF"), ROOT.RooFit.LineStyle(ROOT.kDashed), ROOT.RooFit.LineColor(ROOT.kRed))

#Draw the results
c1 = ROOT.TCanvas()
xframe.Draw()
c1.SaveAs("exercise_0_p1.png")

#Now plot the NLL scan for the parameter
nll = totPDF.createNLL(dataset)

#Minimize likelihood w.r.t all parameters before making plots
ROOT.RooMinimizer(nll).migrad()

#Plot likelihood scan frac 
frame_cross_psi = cross_psi.frame(ROOT.RooFit.Bins(10), ROOT.RooFit.Range(0.,19.), ROOT.RooFit.Title("LL and profileLL in cross_psi"))
nll.plotOn(frame_cross_psi,ROOT.RooFit.ShiftToZero())

#Adjust frame maximum for visual clarity
frame_cross_psi.SetMinimum(0)
frame_cross_psi.SetMaximum(3)

canvas_cross = ROOT.TCanvas()
canvas_cross.cd()
frame_cross_psi.Draw()
canvas_cross.SaveAs("exercise_0_p1_cross.png")

#Now save the data and the PDF into a Workspace, for later use for statistical analysis
ws = ROOT.RooWorkspace("ws")
getattr(ws,'import')(dataset)
getattr(ws,'import')(totPDF)

fOutput = ROOT.TFile("Workspace_mumufit.root","RECREATE")
ws.Write()
fOutput.Write()
fOutput.Close()
