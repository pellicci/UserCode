//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 21 20:36:31 2008 by ROOT version 5.14/00e
// from TChain parFloat/
//////////////////////////////////////////////////////////

#ifndef merge_xy_h
#define merge_xy_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class merge_xy {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Double_t        myratio;
   Double_t        myx;
   Double_t        myy;

   // List of branches
   TBranch        *b_myratio;   //!
   TBranch        *b_myx;   //!
   TBranch        *b_myy;   //!

   merge_xy(TTree *tree=0);
   virtual ~merge_xy();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef merge_xy_cxx
merge_xy::merge_xy(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f) {
         f = new TFile("Memory Directory");
         f->cd("Rint:/");
      }
      tree = (TTree*)gDirectory->Get("parFloat");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("parFloat","");
      chain->Add("generate_xy/syst/toyxy_1.root/parFloat");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

merge_xy::~merge_xy()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t merge_xy::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t merge_xy::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void merge_xy::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normaly not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("myratio", &myratio, &b_myratio);
   fChain->SetBranchAddress("myx", &myx, &b_myx);
   fChain->SetBranchAddress("myy", &myy, &b_myy);
   Notify();
}

Bool_t merge_xy::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void merge_xy::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t merge_xy::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef merge_xy_cxx
