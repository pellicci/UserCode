from ROOT import TTree, TRandom3, TCanvas
from array import array

mass_tree = TTree("mass_tree","Tree containing invariant mass points")

random_generator = TRandom3()

maxNevents = 1000

mass = array("f", [0.])
mass_tree.Branch('mass', mass, 'mass/F' )

for i in range(maxNevents):
    mass[0] = random_generator.BreitWigner(125.,0.004)
    mass_tree.Fill()
    print mass

c1 = TCanvas('c1','Tree Data Structure')
mass_tree.Draw("mass","mass < 140. && mass > 110.")
c1.SaveAs("smear_mass.gif")


