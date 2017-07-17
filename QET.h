//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 12 23:18:06 2017 by ROOT version 5.34/36
// from TTree Tangle2/Energy
// found on file: 30M.root
//////////////////////////////////////////////////////////

#ifndef QET_h
#define QET_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class QET {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        crystal0;
   Double_t        crystal1;
   Double_t        crystal2;
   Double_t        crystal3;
   Double_t        crystal4;
   Double_t        crystal5;
   Double_t        crystal6;
   Double_t        crystal7;
   Double_t        crystal8;
   Double_t        crystal9;
   Double_t        crystal10;
   Double_t        crystal11;
   Double_t        crystal12;
   Double_t        crystal13;
   Double_t        crystal14;
   Double_t        crystal15;
   Double_t        crystal16;
   Double_t        crystal17;
   Int_t           TrueEvent;
   Double_t        cosA;
   Double_t        cosB;

   // List of branches
   TBranch        *b_crystal0;   //!
   TBranch        *b_crystal1;   //!
   TBranch        *b_crystal2;   //!
   TBranch        *b_crystal3;   //!
   TBranch        *b_crystal4;   //!
   TBranch        *b_crystal5;   //!
   TBranch        *b_crystal6;   //!
   TBranch        *b_crystal7;   //!
   TBranch        *b_crystal8;   //!
   TBranch        *b_crystal9;   //!
   TBranch        *b_crystal10;   //!
   TBranch        *b_crystal11;   //!
   TBranch        *b_crystal12;   //!
   TBranch        *b_crystal13;   //!
   TBranch        *b_crystal14;   //!
   TBranch        *b_crystal15;   //!
   TBranch        *b_crystal16;   //!
   TBranch        *b_crystal17;   //!
   TBranch        *b_TrueEvent;   //!
   TBranch        *b_cosA;   //!
   TBranch        *b_cosB;   //!

   QET(TTree *tree=0);
   virtual ~QET();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef QET_cxx
QET::QET(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("SimData.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("SimData.root");
      }
      f->GetObject("Tangle2",tree);

   }
   Init(tree);
}

QET::~QET()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t QET::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t QET::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void QET::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("crystal0", &crystal0, &b_crystal0);
   fChain->SetBranchAddress("crystal1", &crystal1, &b_crystal1);
   fChain->SetBranchAddress("crystal2", &crystal2, &b_crystal2);
   fChain->SetBranchAddress("crystal3", &crystal3, &b_crystal3);
   fChain->SetBranchAddress("crystal4", &crystal4, &b_crystal4);
   fChain->SetBranchAddress("crystal5", &crystal5, &b_crystal5);
   fChain->SetBranchAddress("crystal6", &crystal6, &b_crystal6);
   fChain->SetBranchAddress("crystal7", &crystal7, &b_crystal7);
   fChain->SetBranchAddress("crystal8", &crystal8, &b_crystal8);
   fChain->SetBranchAddress("crystal9", &crystal9, &b_crystal9);
   fChain->SetBranchAddress("crystal10", &crystal10, &b_crystal10);
   fChain->SetBranchAddress("crystal11", &crystal11, &b_crystal11);
   fChain->SetBranchAddress("crystal12", &crystal12, &b_crystal12);
   fChain->SetBranchAddress("crystal13", &crystal13, &b_crystal13);
   fChain->SetBranchAddress("crystal14", &crystal14, &b_crystal14);
   fChain->SetBranchAddress("crystal15", &crystal15, &b_crystal15);
   fChain->SetBranchAddress("crystal16", &crystal16, &b_crystal16);
   fChain->SetBranchAddress("crystal17", &crystal17, &b_crystal17);
   fChain->SetBranchAddress("TrueEvent", &TrueEvent, &b_TrueEvent);
   fChain->SetBranchAddress("cosA", &cosA, &b_cosA);
   fChain->SetBranchAddress("cosB", &cosB, &b_cosB);
   Notify();
}

Bool_t QET::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void QET::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t QET::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef QET_cxx
