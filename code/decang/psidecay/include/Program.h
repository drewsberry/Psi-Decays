#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

// ROOT Things... you may need to add more
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
#include "TRandom3.h"
#include "TGenPhaseSpace.h"

// standard stuff
#include <exception>
#include <sstream>
#include <iostream>

#define PSIMASS 3.773
#define DMASS 1.86962

// define a class "Example"
class Program {

// define items that are only to be used by the class and only accessible by the class
private:
  // PROGRAM::FIT()
  Int_t pxNBins;
  Double_t pxXMin;
  Double_t pxXMax;
  
  Int_t pyNBins;
  Double_t pyXMin;
  Double_t pyXMax;
  
  Int_t pzNBins;
  Double_t pzXMin;
  Double_t pzXMax;

  // Custom functions
  TF1       *gaussFuncPx;
  TF1       *gaussFuncPy;
  TF1       *gaussFuncPz;
  TF1       *landauFunc;
  TF1       *totalPz;

  // Root file
  TFile     *file;
  TTree     *tree;

  // Histograms
  TH1F      *pxHist;
  TH1F      *pyHist;
  TH1F      *pzHist;
  TH1F      *pxRand;
  TH1F      *pyRand;
  TH1F      *pzRand;
  TH1F      pxHistScale;
  TH1F      pyHistScale;
  TH1F      pzHistScale;

  // Parameter arrays
  Double_t  ipar[8]; // Initial parameters
  Double_t  fpar[8]; // Final parameters

      //PROGRAM::BOOST()
  // Histograms
  TH1F      *histNonBoost;
  TH1F      *histBoost;

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
  Int_t Setup();
  Int_t Fit();
  Int_t Boost();
};
