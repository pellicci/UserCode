#! /usr/bin/env python

import ROOT
import sys
import os

ROOT.gStyle.SetOptStat(0)

dir_out = "plots/"
if not os.path.exists(dir_out):
    os.makedirs(dir_out)

list_files = sys.argv[1:]

mycanvas = dict()
fInput = []
first_histos = []
pad_plot = []
pad_ratio = []

for idx_file,file_name in enumerate(list_files):
    fInput.append(ROOT.TFile(file_name))

    names_list = fInput[idx_file].GetListOfKeys()
    names_iter = names_list.MakeIterator()

    plot_counter = 0

    while(names_iter.Next()) :

        histoname = names_iter.GetName()

        if idx_file == 0:
            mycanvas[histoname] = ROOT.TCanvas(histoname)
            mycanvas[histoname].cd()

            pad_plot.append(ROOT.TPad("pad_plot","",0.05,0.26,0.99,0.99))
            pad_plot[plot_counter].Draw()
            pad_plot[plot_counter].SetGrid()
            pad_plot[plot_counter].SetLogy()

            pad_ratio.append(ROOT.TPad("pad_ratio","",0.05,0.01,0.99,0.25))
            pad_ratio[plot_counter].Draw()
            pad_ratio[plot_counter].SetGrid()

            first_histos.append(fInput[idx_file].Get(histoname).Clone())

        histo = fInput[idx_file].Get(histoname)
        histo.SetLineColor(idx_file + 1)
        histo.SetMarkerColor(idx_file + 1)
        histo.SetMarkerStyle(21 + idx_file)

        mycanvas[histoname].cd()
        if idx_file == 0:
            pad_plot[plot_counter].cd()
            histo.Draw("E")
        else:
            pad_ratio[plot_counter].cd()
            eff_plot = histo.Clone()
            eff_plot.Divide(first_histos[plot_counter])
            eff_plot.SetTitle(";;Ratio")
            eff_plot.SetLineColor(idx_file + 1)
            eff_plot.SetMarkerColor(idx_file + 1)
            eff_plot.SetMarkerStyle(21 + idx_file)
            eff_plot.GetYaxis().SetTitleSize(0.14)
            eff_plot.GetYaxis().SetTitleOffset(0.4)
            eff_plot.GetYaxis().SetRangeUser(0.1,5.)
            eff_plot.GetYaxis().SetLabelSize(0.11)

            if idx_file == 1 :
                eff_plot.Draw("PE1")
            else :
                eff_plot.Draw("SAMEPE1")
                
            pad_plot[plot_counter].cd()
            histo.Draw("ESAME")

        mycanvas[histoname].Update()
        plot_counter += 1

for canva in mycanvas:
    mycanvas[canva].SaveAs(dir_out + canva + ".gif")
