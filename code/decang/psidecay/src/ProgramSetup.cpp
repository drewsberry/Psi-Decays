#include "../include/Program.h"
using namespace std;

Int_t Program::Setup()
{
    if (!gROOT->GetClass("TGenPhaseSpace"))
        gSystem->Load("libPhysics");
    
    gStyle->SetOptStat(0);
    
    file   = TFile::Open("../data/momentum.root");
    tree   = (TTree *)file->Get("mc_k3pi");

    gaussFuncPx = new TF1("gaussFuncPx", 
            "[0]*TMath::Gaus(x,[1],[2])",-37000,53000);
    gaussFuncPx->SetParameters(40000, 58, 3500);
    gaussFuncPx->SetNpx(1000);


    gaussFuncPy = new TF1("gaussFuncPy", 
            "[0]*TMath::Gaus(x,[1],[2])",-30000,30000);
    gaussFuncPy->SetParameters(40000, 58, 3500);
    gaussFuncPy->SetNpx(1000);

    landauFunc = new TF1("landauFunc", 
            "[2]*TMath::Landau(x*[3]+[4],[0],[1],0)",0,60000);
    landauFunc->SetParameters(200,200,40000,1,2000);
    landauFunc->SetNpx(1000); // Makes for smoother graph
    // Function for custom Landau fitting

    gaussFuncPz = new TF1("gaussFuncPz", 
            "[2]*TMath::Gaus(x,[0],[1])", 62000, 1000000);
    gaussFuncPz->SetParameters(58, 3500, 40000);
    gaussFuncPz->SetNpx(1000); // Makes for smoother graph

    totalPz = new TF1("totalPz",
            "[2]*TMath::Landau(x*[3]+[4],[0],[1],0) + [5]*TMath::Gaus(x,[6],[7])", 
            0, 1000000);
    totalPz->SetNpx(1000);
    // Define total function combining Landau and Gaussian
    
    histNonBoost = new TH1F("Non-Boosted D^{0} #bar{D^{0}} Angle",
            "Non-Boosted Angle Between D ^{0} and #bar{D}^{0}", 50, 179, 181);
    histBoost = new TH1F("Boosted D^{0} #bar{D^{0}} Angle",
            "Boosted Angle Between D ^{0} and #bar{D}^{0}", 200, 0, 5);

    return 0;
}
