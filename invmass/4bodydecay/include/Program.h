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
#include "TGenPhaseSpace.h"
#include "TLorentzVector.h"

// standard stuff
#include <exception>
#include <sstream>
#include <iostream>
#include <fstream>

class Program {

// define items that are only to be used by the class and only accessible by the class
private:
  // Declare any variables/functions used privately by Program here

  TH1F *K_plusK_minus1Hist1; //1*
  TH1F *K_plusK_minus2Hist; //2
  TH1F *K_minus1K_minus2Hist; //3

  TH1F *K_plusPi_plusHist1; //4*
  TH1F *K_minus1Pi_plusHist; //5
  TH1F *K_minus2Pi_plusHist; //6

  TH1F *K_plusK_minus1K_minus2Hist1; //7*

  TH1F *K_plusK_minus1Pi_plusHist1; //8*
  TH1F *K_plusK_minus2Pi_plusHist; //9
  TH1F *K_minus1K_minus2Pi_plusHist; //10

  TH1F *K_plusK_minus1Hist2; //11*
  TH1F *K_plusPi_plusHist2; //12*
  TH1F *K_plusK_minus1K_minus2Hist2; //13*
  TH1F *K_plusK_minus1Pi_plusHist2; //14*

  TH1F *getHist()
  {
      TH1F      *currentHist;
      if((currentHist = (TH1F *)gPad->GetPrimitive("htemp"))) {
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
  Int_t Code(); // Define function for processing actual code
};

// vim: set tabstop=2:
