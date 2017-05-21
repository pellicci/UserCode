import ROOT

def fluctuate_poisson():
    entry_sm_200 = 38000
    entry_bsm_200 = 38000

    Niteration = 100000

    histodiff = ROOT.TH1F("histodiff","Diff of Nevents",200,-2000.,10000.)

    generator = ROOT.TRandom3()
    for k in range(0, Niteration) :

        N_sm  = generator.Poisson(entry_sm_200)
        #N_bsm = generator.Poisson(entry_bsm_200)

        diff = N_sm - entry_bsm_200
        histodiff.Fill(diff)

    c1 = ROOT.TCanvas()
    c1.cd()

    histodiff.Draw()
    c1.SaveAs("histodiff.png")


fluctuate_poisson()
