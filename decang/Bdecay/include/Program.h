#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TText.h"
#include "TPaveText.h"
#include "TSystem.h"
#include "TString.h"
#include "TCut.h"
#include "TApplication.h" 
#include "TFrame.h" 
#include "TTree.h"
#include "TH2F.h"
#include "TCut.h"
#include "TGaxis.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TGenPhaseSpace.h"
#include "TVirtualFitter.h"
#include "TRandom3.h"

#include <exception>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

#define BMASS   5.27915
#define PSIMASS 3.7781
#define DMASS   1.86484
#define KMASS   0.493677

class Program {

// define items that are only to be used by the class and only accessible by the class
private:
  // Program::Setup()
  TString   D0_PT;
  TString   Bach_PT;
  TString   B_PT;

  TFile     *mcfile1;
  TFile     *mcfile2;

  TTree     *mctree1;
  TTree     *mctree2;

  ofstream  correlationFactors;

  Double_t  ipar[8];
  Double_t  fpar[8];

  TRandom3  randm3;
  Double_t  randm;

  Double_t  landaufrac;

  TF1       *D0_PxFit;
  TF1       *D0_PyFit;
  TF1       *D0_PxFunc;
  TF1       *D0_PyFunc;

  TF1       *Bach_PxFit;
  TF1       *Bach_PyFit;
  TF1       *Bach_PxFunc;
  TF1       *Bach_PyFunc;

  TF1       *B_PxFit;
  TF1       *B_PyFit;
  TF1       *B_PxFunc;
  TF1       *B_PyFunc;
  TF1       *B_PzFitLand;
  TF1       *B_PzFuncLand;
  TF1       *B_PzFitGaus;
  TF1       *B_PzFunc;
  TF1       *B_PzFuncAdd;

  TCut      backCut;
  TCut      D0PTCut;
  TCut      BachPTCut;
  TCut      D0PXCut;
  TCut      D0PYCut;
  TCut      D0PXYCut;
  TCut      BachPXCut;
  TCut      BachPYCut;
  TCut      BachPXYCut;
  TCut      BPXCut;
  TCut      BPYCut;

  // Program::Correlation()
  TH2F      *BPxPyLego;
  TH2F      *BPxPyCont;
  TH2F      *BPxPyScat;

  TH2F      *BPxPzLego;
  TH2F      *BPxPzCont;
  TH2F      *BPxPzScat;

  TH2F      *BPyPzLego;
  TH2F      *BPyPzCont;
  TH2F      *BPyPzScat;

  // Program::Fit()
  TH1F      *D0_PxHist;
  TH1F      *D0_PyHist;
  TH1F      *D0_PzHist;
  TH1F      *D0_EHist;

  TH1F      *D0_PxXCutHist;
  TH1F      *D0_PxYCutHist;
  TH1F      *D0_PyXCutHist;
  TH1F      *D0_PyYCutHist;

  TH1F      *Bach_PxHist;
  TH1F      *Bach_PyHist;
  TH1F      *Bach_PzHist;
  TH1F      *Bach_EHist;

  TH1F      *B_PxHist;
  TH1F      *B_PyHist;
  TH1F      *B_PzHist;
  TH1F      *B_EHist;

  TH1F      *B_PzRandHist;

  TH1F      *D0_PTHist;
  TH1F      *Bach_PTHist;
  TH1F      *B_PTHist;

  // Program::Boost()
  TH1F      *psikNonBoostAngleHist;
  TH1F      *d0d0barNonBoostAngleHist;
  TH1F      *psikBoostAngleHist;
  TH1F      *d0d0barBoostAngleHist;

  TH1F      *get1DHist()
  {
    TH1F      *currentHist;
    if((currentHist = (TH1F *)gPad->GetPrimitive("htemp"))) {
      return currentHist;
    } else {
      fprintf(stderr, "\n[ERROR] Cannot retrieve last drawn histogram\n\n");
      return NULL;
    }
  }

  TH2F      *get2DHist()
  {
    TH2F      *currentHist;
    if((currentHist = (TH2F *)gPad->GetPrimitive("htemp"))) {
      return currentHist;
    } else {
      fprintf(stderr, "\n[ERROR] Cannot retrieve last drawn histogram\n\n");
      return NULL;
    }
  }

// define items that someone could access from another program
public:
  Program() // CONSTRUCTOR ... this sets up the class member variable defaults
  { 
    // DEFAULTS
  }

  ~Program() // DESTRUCTOR
  {
    // delete any variables you created with "new" here

  }

  // Function declarations and/or definitions
  void Setup(); // Setup the variables, load th data file etc.
  void Correlation(); // Find the correlation coefficients and print graphs
  void Fit(); // Fit the data to function
  void Boost(); // Run the MC decay with the boosted B Meson
  void Clean(); // Delete any variables created with "new"
};
