import ROOT
import os
import numpy as np

dir_input = "Rates/"
dir_output = "extrap_plots/"
PU_extrap_points = [50.]

def find_rate(file, seed_name):

    file.seek(0)
    for line in file:
        if seed_name in line:
            list_line = line.split()
            return float(list_line[3])

def get_file_names():
    return os.listdir(dir_input)

def get_files(filenames):
    files = []
    for name_file in filenames:
        files.append(open(dir_input + name_file))
    return files

def get_PU_points(filenames):
    PU_points = []
    for filename in filenames:
        partial_PUname = filename.split("_")[1]
        PUname = partial_PUname.split("PU")[0]
        PU_points.append(float(PUname))
    return PU_points

##Here the program starts

list_of_seeds = ["L1_SingleMu16", "L1_SingleEG25", "L1_SingleIsoEG25er", "L1_SingleJet128", "L1_ETM60", "L1_HTT125"]

##The actual magic
filenames = get_file_names()
input_files = get_files(filenames)

PU_axis = get_PU_points(filenames)

if not os.path.exists(dir_output):
    os.makedirs(diroutput)

for seed_name in list_of_seeds:

    rate_values = []
    
    for inputfile in input_files:
        rate_values.append(find_rate(inputfile,seed_name))

    inter = ROOT.Math.Interpolator(len(PU_axis), ROOT.Math.Interpolation.kLINEAR)
    inter.SetData(len(PU_axis), np.asarray(PU_axis), np.asarray(rate_values) )

    rates_extrap = []
    for extrap_points in PU_extrap_points:
        rates_extrap.append(inter.Eval(extrap_points))

    PU_axis_forplots = PU_axis + PU_extrap_points
    rates_axis_forplots = rate_values + rates_extrap

    print seed_name
    print np.asarray(PU_axis_forplots)
    print np.asarray(rates_axis_forplots)

    canvas = ROOT.TCanvas()
    graph_seed = ROOT.TGraph(len(PU_axis_forplots), np.asarray(PU_axis_forplots), np.asarray(rates_axis_forplots) )
    graph_seed.GetXaxis().SetRangeUser(0.,60.)
    graph_seed.GetXaxis().SetTitle("nPU")
    graph_seed.GetYaxis().SetTitle("Rate (kHz)")
    graph_seed.SetTitle(seed_name)
    graph_seed.Draw("APL")
    canvas.SaveAs(dir_output + seed_name + ".gif")
