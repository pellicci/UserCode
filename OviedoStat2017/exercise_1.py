
import ROOT

#Open the rootfile and get the workspace from the exercise_0
fInput = ROOT.TFile("Workspace_mumufit.root")
ws = fInput.Get("ws")
ws.Print()

#Get the observable and PDF out of the Workspace
mass = ws.var("mass")
totPDF = ws.pdf("totPDF")

#Initialize RooMCStudy
mc_study = ROOT.RooMCStudy(totPDF, ROOT.RooArgSet(mass), ROOT.RooFit.Extended(1), ROOT.RooFit.FitOptions(ROOT.RooFit.Save(1)) )

#Generate 1000 experiments and fit each one, each fluctuating in Nevents = NJpsi + Npsi + Nbkg
mc_study.generateAndFit(1000)

#Now let's see the results. For example, the study of the cross section variable
cross_psi = ws.var("cross_psi")
frame_cross_par = mc_study.plotParam(cross_psi, ROOT.RooFit.Bins(40))
frame_cross_err = mc_study.plotError(cross_psi, ROOT.RooFit.Bins(40), ROOT.RooFit.FrameRange(0.,30.) )
frame_cross_pul = mc_study.plotPull(cross_psi, ROOT.RooFit.Bins(40), ROOT.RooFit.FitGauss(1) )

#Also, let's see the distribution of the NLL for all the fits
frame_nll = mc_study.plotNLL(ROOT.RooFit.Bins(40))

#Now plot the whole thing
ROOT.gStyle.SetOptStat(0)

mcstudy_Canvas = ROOT.TCanvas("mcstudy_Canvas")
mcstudy_Canvas.Divide(2,2)

mcstudy_Canvas.cd(1)
frame_cross_par.Draw()

mcstudy_Canvas.cd(2)
frame_cross_err.Draw()

mcstudy_Canvas.cd(3)
frame_cross_pul.Draw()

mcstudy_Canvas.cd(4)
frame_nll.Draw()

mcstudy_Canvas.SaveAs("exercise_1.png")

#Now plot some less constroversial variable
meanJpsi = ws.var("meanJpsi")
frame_mjpsi_par = mc_study.plotParam(meanJpsi, ROOT.RooFit.Bins(40))
frame_mjpsi_pul = mc_study.plotPull(meanJpsi, ROOT.RooFit.Bins(40), ROOT.RooFit.FitGauss(1) )

mcstudy_Canvas_jpsi = ROOT.TCanvas("mcstudy_Canvas_jpsi")
mcstudy_Canvas_jpsi.Divide(2,1)

mcstudy_Canvas_jpsi.cd(1)
frame_mjpsi_par.Draw()

mcstudy_Canvas_jpsi.cd(2)
frame_mjpsi_pul.Draw()

mcstudy_Canvas_jpsi.SaveAs("exercise_1_mjpsi.png")
