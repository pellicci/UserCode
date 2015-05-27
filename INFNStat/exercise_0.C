//////////////////////////////////////////////////////////////////////////
//
// First exercise for the CMS DAS
// 
// Creating a dataset, fitting saving into a Workspace
//
// pdf = gauss(x,m,s) + exp(x,tau)
//
//
// 2014 - Mario Pelliccioni, Luca Lista
// 
/////////////////////////////////////////////////////////////////////////

gSystem->Load("libRooFit");

using namespace RooFit;

void exercise_0()
{

  //First, define the observable for the analysis
  RooRealVar mass("mass","mass",100.,150.);

  //Construct the signal P.D.F., a gaussian function
  RooRealVar mean("mean","mean of gaussian",125.,110.,140.);
  RooRealVar sigma("sigma","width of gaussian",6.,0.01,10.);
  RooGaussian gauss("gauss","Signal PDF",mass,mean,sigma);  

  //Now define the background P.D.F, a simple exponential
  RooRealVar tau("tau","exponential function parameter",-0.05,-10.,-0.001);
  RooExponential exponential("exponential","Background PDF",mass,tau);

  //Now construct the total PDF. We need to define the number of signal and background events in the model
  //
  //for UL calculation use Nsig = 5, Nbkg = 100
  //for mH calculation use Nsig = 50, Nbkg = 450
  //for systematics inclusion use Nsig = 20, Nbkg = 100, also, with the width set to 5 GeV!!
  RooRealVar Nsig("Nsig","Number of signal events",20.,0.,200.);
  RooRealVar Nbkg("Nbkg","Number of background events",100.,0.,1000.);

  RooAddPdf PDFtot("PDFtot","PDFtot",RooArgList(gauss,exponential),RooArgList(Nsig,Nbkg));

  //Now generate a sample with the total PDF
  RooDataSet *data = PDFtot.generate(RooArgSet(mass),NumEvents(Nsig.getVal()+Nbkg.getVal()),Extended(1));

  //Now fit the PDF to the data
  //For low statistics, fix the mean and the width
  mean.setConstant(kTRUE);
  sigma.setConstant(kTRUE);
  PDFtot.fitTo(*data);

  // Print values of mean and sigma (that now reflect fitted values and errors, unless you fixed them)
  mean.Print();
  sigma.Print();

  //Now plot the data and the fitted PDF
  RooPlot *massframe = mass.frame(50);
  data->plotOn(massframe);
  PDFtot.plotOn(massframe);

  //One can also plot the single components of the total PDF, like the background component
  PDFtot.plotOn(massframe,Components(exponential),LineStyle(kDashed),LineColor(kRed));

  //Actually plot the result
  TCanvas c1;
  c1.cd();
  massframe->Draw();
  c1.SaveAs("exercise_0.gif");

  //Now save the data and the PDF into a Workspace, for later use for statistical analysis
  //and save the workspace into a ROOT file
  RooWorkspace* w = new RooWorkspace("w") ;
  w->import(*data);
  w->import(PDFtot);

  TFile fOut("exercise_0.root","RECREATE");
  fOut.cd();
  w->Write();
  fOut.Close();

}
