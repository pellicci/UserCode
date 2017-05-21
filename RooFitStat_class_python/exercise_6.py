
import ROOT

#First, define the observable for the analysis
mass = ROOT.RooRealVar("mass","mass",100.,150.)

#Construct the signal P.D.F., a gaussian function
mean = ROOT.RooRealVar("mean","mean of gaussian",125.,110.,140.)
sigma = ROOT.RooRealVar("sigma","width of gaussian",2.,0.01,10.)
gauss = ROOT.RooGaussian("gauss","Signal PDF",mass,mean,sigma)

#Now define the background P.D.F, a simple exponential
tau = ROOT.RooRealVar("tau","exponential function parameter",-0.05,-10.,-0.001)
exponential = ROOT.RooExponential("exponential","Background PDF",mass,tau)

#Now construct the total PDF. We need to define the number of signal and background events in the model

#for UL calculation use Nsig = 5, Nbkg = 100
#for mH calculation use Nsig = 50, Nbkg = 450
#for systematics inclusion use Nsig = 20, Nbkg = 100, also, with the width set to 5 GeV!!
Nsig = ROOT.RooRealVar("Nsig","Number of signal events",5.,0.,200.)
Nbkg = ROOT.RooRealVar("Nbkg","Number of background events",100.,0.,1000.)

PDFtot = ROOT.RooAddPdf("PDFtot","PDFtot",ROOT.RooArgList(gauss,exponential),ROOT.RooArgList(Nsig,Nbkg))

#Now generate a sample with the total PDF
data = PDFtot.generate(ROOT.RooArgSet(mass),ROOT.RooFit.NumEvents(Nsig.getVal()+Nbkg.getVal()), ROOT.RooFit.Extended(1))

#Now fit the PDF to the data
#For low statistics, fix the mean and the width
mean.setConstant(1)
sigma.setConstant(1)

PDFtot.fitTo(data)

#Print values of mean and sigma (that now reflect fitted values and errors, unless you fixed them)
mean.Print()
sigma.Print()

#Now plot the data and the fitted PDF
massframe = mass.frame(50)
data.plotOn(massframe)
PDFtot.plotOn(massframe)

#One can also plot the single components of the total PDF, like the background component
PDFtot.plotOn(massframe, ROOT.RooFit.Components("exponential"), ROOT.RooFit.LineStyle(ROOT.kDashed), ROOT.RooFit.LineColor(ROOT.kRed))

#Actually plot the result
canvas = ROOT.TCanvas()
canvas.cd()
massframe.Draw()
canvas.SaveAs("exercise_6.png")

#Now save the data and the PDF into a Workspace, for later use for statistical analysis
#and save the workspace into a ROOT file
workspace = ROOT.RooWorkspace("w")
getattr(workspace,'import')(PDFtot)
getattr(workspace,'import')(data)

fOut = ROOT.TFile("exercise_6.root","RECREATE")
fOut.cd()
workspace.Write()
fOut.Close()
