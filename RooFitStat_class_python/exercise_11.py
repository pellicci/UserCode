
import ROOT

#Make a simple model
x = ROOT.RooRealVar("x","Number of observed events", 1.,0.,20.)
mu = ROOT.RooRealVar("mu","The mu parameter", 2.5,0., 15.) #With a limit on mu>=0
b = ROOT.RooConstVar("b","", 3.)
mean = ROOT.RooAddition("mean","", ROOT.RooArgList(mu,b))
pois = ROOT.RooPoisson("pois", "", x, mean)
parameters = ROOT.RooArgSet(mu)

#Create a toy dataset
data = pois.generate(ROOT.RooArgSet(x), 1)
data.Print("v")

canvas = ROOT.TCanvas("dataCanvas")
canvas.cd()
frame = x.frame()
data.plotOn(frame)
frame.Draw()
canvas.Update()

w = ROOT.RooWorkspace()
modelConfig = ROOT.RooStats.ModelConfig("poissonProblem",w)
modelConfig.SetPdf(pois)
modelConfig.SetParametersOfInterest(parameters)
modelConfig.SetObservables(ROOT.RooArgSet(x))
w.Print()

#Show use of Feldman-Cousins
fc = ROOT.RooStats.FeldmanCousins(data,modelConfig)
fc.SetTestSize(.05) #Set size of test
fc.UseAdaptiveSampling(1)
fc.AdditionalNToysFactor(10.)
fc.FluctuateNumDataEntries(0) #Number counting analysis: dataset always has 1 entry with N events observed
fc.SetNBins(200) #Number of points to test per parameter

#Nse the Feldman-Cousins tool
interval = fc.GetInterval()

print "The interval is [", interval.LowerLimit(mu), ", ", interval.UpperLimit(mu), "]"

#No dedicated plotting class yet, so do it by hand:
ROOT.gStyle.SetOptStat(0)

parameterScan = fc.GetPointsToScan()    #this is a RooDataHist
hist = parameterScan.createHistogram("mu",30)
hist.GetXaxis().SetTitle("#mu")

canvas = ROOT.TCanvas()
canvas.cd()
hist.Draw()

mark = []
#Loop over points to test
for i in range(parameterScan.numEntries()) :
    print "on parameter point ", i, " out of ", parameterScan.numEntries()
    #Get a parameter point from the list of points to test.
    tmpPoint = parameterScan.get(i).clone("temp")

    mark.append(ROOT.TMarker(tmpPoint.getRealValue("mu"), 1, 25))
    if (interval.IsInInterval(tmpPoint)):
        mark[i].SetMarkerColor(ROOT.kBlue)
    else:
        mark[i].SetMarkerColor(ROOT.kRed)

    mark[i].Draw("s")

canvas.SaveAs("exercise_11.png")
