#include "../include/Program.h"
using namespace std;

void Program::Setup()
{
    gStyle->SetOptStat(0);
    TGaxis::SetMaxDigits(3);
    TVirtualFitter::SetMaxIterations(50000);

    const Int_t NRGBs = 5;
    const Int_t NCont = 35;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle -> SetNumberContours(NCont);

    if (!gROOT->GetClass("TGenPhaseSpace")) {
        gSystem->Load("libPhysics");
    }

    randm3.SetSeed(17);

    D0_PT       = "TMath::Sqrt(TMath::Power(D0_PX,2) + TMath::Power(D0_PY,2))";
    Bach_PT     = "TMath::Sqrt(TMath::Power(Bach_PX,2) + TMath::Power(Bach_PY,2))";
    B_PT        = "TMath::Sqrt(TMath::Power(D0_PX + Bach_PX,2) + TMath::Power(D0_PY + Bach_PY,2))";

    mcfile1     = TFile::Open("../data/MC11_b2dk_kkpipi.root");
    mcfile2     = TFile::Open("../data/MC11_BDPI_b2dk_d2kkpipi_magup_BDT.root");
                                                                                
    mctree1     = (TTree *)mcfile1->Get("Bu2D0X");
    mctree2     = (TTree *)mcfile2->Get("Bu2D0X");

    correlationFactors.open("../data/CorrelationFactors.dat", ios::out | ios::trunc);

    backCut     = "Bu_BKGCAT == 0";
    D0PXCut     = "D0_PX > 2000 || D0_PX < -2000";
    D0PYCut     = "D0_PY > 2000 || D0_PY < -2000";
    BachPXCut   = "Bach_PX > 500 || Bach_PX < -500";
    BachPYCut   = "Bach_PY > 500 || Bach_PY < -500";
    D0PXYCut    = D0PXCut && D0PYCut;
    BachPXYCut  = BachPXCut && BachPYCut;
    D0PTCut     = "D0_PT > 3000";
    BachPTCut   = "Bach_PT > 1500";
    BPXCut      = "D0_PX + Bach_PX > 4500 || D0_PX + Bach_PX < -4500";
    BPYCut      = "D0_PY + Bach_PY > 500 || D0_PY + Bach_PY < -500";

    D0_PxFit    = new TF1("D0_PxFit", 
        "[0]*TMath::Gaus(x,0,[1])", 2000, 50000);
    D0_PxFunc   = new TF1("D0_PxFunc", 
        "[0]*TMath::Gaus(x,0,[1])", -50000, 50000);
    D0_PxFunc->SetNpx(1000);
    D0_PxFit->SetParameters(500,5000);

    D0_PyFit    = new TF1("D0_PyFit",
         "[0]*TMath::Gaus(x,0,[1])", 2000, 50000);
    D0_PyFunc   = new TF1("D0_PyFunc",
        "[0]*TMath::Gaus(x,0,[1])", -50000, 50000);
    D0_PyFunc->SetNpx(1000);
    D0_PyFit->SetParameters(500,5000);

    Bach_PxFit  = new TF1("Bach_PxFit",
     "[0]*TMath::Gaus(x,0,[1])", 500, 50000);
    Bach_PxFunc = new TF1("Bach_PxFunc",
        "[0]*TMath::Gaus(x,0,[1])", -50000, 50000);
    Bach_PxFunc->SetNpx(1000);
    Bach_PxFit->SetParameters(500,5000);

    Bach_PyFit  = new TF1("Bach_PyFit",
        "[0]*TMath::Gaus(x,0,[1])", 500, 50000);
    Bach_PyFunc = new TF1("Bach_PyFunc", 
        "[0]*TMath::Gaus(x,0,[1])", -50000, 50000);
    Bach_PyFunc->SetNpx(1000);
    Bach_PyFit->SetParameters(500,5000);

    B_PxFit     = new TF1("B_PxFit", 
        "[0]*TMath::Gaus(x,0,[1])", 4500, 50000);
    B_PxFunc    = new TF1("B_PxFunc",
        "[0]*TMath::Gaus(x,0,[1])", -50000, 50000);
    B_PxFunc->SetNpx(1000);
    B_PxFit->SetParameters(500, 10000);

    B_PyFit     = new TF1("B_PyFit", 
        "[0]*TMath::Gaus(x,0,[1])", 1000, 50000);
    B_PyFunc    = new TF1("B_PyFunc", 
        "[0]*TMath::Gaus(x,0,[1])", -50000, 50000);
    B_PyFunc->SetNpx(1000);
    B_PyFit->SetParameters(500, 10000);

    B_PzFitLand = new TF1("B_PzFitLand", 
        "[2]*TMath::Landau(x*[3]+[4],[0],[1],0)", 0, 130000);
    B_PzFitLand->SetParameters(44000, 15000, 5000, 1.2, -6500);
    B_PzFitLand->SetNpx(1000);

    B_PzFitGaus = new TF1("B_PzFitGaus",
        "[2]*TMath::Gaus(x,[0],[1])", 130000, 1100000);
    B_PzFitGaus->SetParameters(-3000000, -500000, 100000000000);
    B_PzFitGaus->SetNpx(1000);

    B_PzRandHist = new TH1F("B_PzRandHist", "B_PzRandHist", 100, 0, 1100000);
}
