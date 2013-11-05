#include "../include/Program.h"
using namespace std;

Int_t Program::Code()
{
    /* Note that TFGenPhaseSpace, as per LHCb standard, is in GeV. Hence all the
     * calculations and graphs hereonin are in GeV. */

    if (!gROOT -> GetClass("TGenPhaseSpace"))
        gSystem->Load("libPhysics"); // Get and load TGenPhaseSoace class

    gStyle->SetOptStat(0);

    K_plusK_minus1Hist1 = new TH1F("KplusKminus1Hist1", 
            "K^{+} K^{-}_{1};m^{2}(K^{+} K^{-}_{1}) [(GeV/c^{2})^{2}]", 
            50, 0.95, 1.55);
    K_plusK_minus2Hist = new TH1F("K_plusK_minus2Hist", 
            "K^{+} K^{-}_{2};m^{2}(K^{+} K^{-}_{2}) [(GeV/c^{2})^{2}]",
            50, 0.95, 1.55);
    K_minus1K_minus2Hist = new TH1F("K_minus1K_minus2Hist", 
            "K^{-}_{1} K^{-}_{2};m^{2}(K^{-}_{1} K^{-}_{2}) [(GeV/c^{2})^{2}]",
            50, 0.95, 1.55);
    
    K_plusPi_plusHist1 = new TH1F("K_plusPi_plusHist1", 
            "K^{+} #pi^{+};m^{2}(K^{+} #pi^{+}) [(GeV/c^{2})^{2}]",
            50, 0.35, 0.8);
    K_minus1Pi_plusHist = new TH1F("K_minus1Pi_plusHist",
            "K^{-}_{1} #pi^{+};m^{2}(K^{-}_{1} #pi^{+}) [(GeV/c^{2})^{2}]",
            50, 0.35, 0.8);
    K_minus2Pi_plusHist = new TH1F("K_minus2Pi_plusHist", 
            "K^{-}_{2} #pi^{+};m^{2}(K^{-}_{2} #pi^{+}) [(GeV/c^{2})^{2}]",
            50, 0.35, 0.8);
    
    K_plusK_minus1K_minus2Hist1 = new TH1F("K_plusK_minus1K_minus2Hist1",
            "K^{+} K^{-}_{1} K^{-}_{2};m^{2}(K^{+} K^{-}_{1} K^{-}_{2}) [(GeV/c^{2})^{2}]", 
            50, 2.1, 3);

    K_plusK_minus1Pi_plusHist1 = new TH1F("K_plusK_minus1Pi_plusHist1",
            "K^{+} K^{-}_{1} #pi^{+};m^{2}(K^{+} K^{-}_{1} #pi^{+}) [(GeV/c^{2})^{2}]",
            50, 1.2, 1.9);
    K_plusK_minus2Pi_plusHist = new TH1F("K_plusK_minus2Pi_plusHist",
            "K^{+} K^{-}_{2} #pi^{+};m^{2}(K^{+} K^{-}_{2} #pi^{+}) [(GeV/c^{2})^{2}]",
            50, 1.2, 1.9);
    K_minus1K_minus2Pi_plusHist = new TH1F("K_minus1K_minus2Pi_plusHist", 
            "K^{-}_{1} K^{-}_{2} #pi^{+};m^{2}(K^{-}_{1} K^{-}_{2} #pi^{+}) [(GeV/c^{2})^{2}]",
            50, 1.2, 1.9);

    K_plusK_minus1Hist2 = new TH1F("K_plusK_minus1Hist2",
            "K K; m(K K) [GeV/c^{2}]",
            50, 0.98, 1.25);
    K_plusPi_plusHist2 = new TH1F("K_plusPi_plusHist2",
            "K #pi; m(K #pi) [GeV/c^{2}]", 
            50, 0.62, 0.9);
    K_plusK_minus1K_minus2Hist2 = new TH1F("K_plusK_minus1K_minus2Hist2",
            "K K K; m(K K K) [GeV/c^{2}]", 
            50, 1.48, 1.74);
    K_plusK_minus1Pi_plusHist2 = new TH1F("K_plusK_minus1Pi_plusHist2",
            "K K #pi; m(K K #pi) [GeV/c^{2}]",
            50, 1.12, 1.38);
    // Initiliase all the histograms used for plotting later on

    TLorentzVector D0(0.0, 0.0, 0.0, 1.86484);
    // 4-vector for parent D0 in rest frame

    Double_t masses[4] = { 0.493677, 0.493677, 0.493677, 0.13957018 };
    // Product particles mass array

    TGenPhaseSpace event; // Declare event of type class TGenPhaseSpace
    event.SetDecay(D0, 4, masses); // Setup decay

    for (Int_t n = 0; n < 100000; n++) // Loop 100,000 times
    {
        Double_t        weight                  = event.Generate();
        // generate weightings for each event

        TLorentzVector  *K_plus                 = event.GetDecay(0);
        TLorentzVector  *K_minus1               = event.GetDecay(1);
        TLorentzVector  *K_minus2               = event.GetDecay(2);
        TLorentzVector  *Pi_plus                = event.GetDecay(3);    
        // Get 4-vectors for products from GetDecay(), in order of mass arrah

        TLorentzVector  K_plusK_minus1          = *K_plus + *K_minus1;
        TLorentzVector  K_plusK_minus2          = *K_plus + *K_minus2;
        TLorentzVector  K_plusPi_plus           = *K_plus + *Pi_plus;
        TLorentzVector  K_minus1K_minus2        = *K_minus1 + *K_minus2;
        TLorentzVector  K_minus1Pi_plus         = *K_minus1 + *Pi_plus;
        TLorentzVector  K_minus2Pi_plus         = *K_minus2 + *Pi_plus;
        // Add the different two-combinations of products

        TLorentzVector  K_plusK_minus1K_minus2  = *K_plus + *K_minus1 + *K_minus2;
        TLorentzVector  K_plusK_minus1Pi_plus   = *K_plus + *K_minus1 + *Pi_plus;
        TLorentzVector  K_plusK_minus2Pi_plus   = *K_plus + *K_minus2 + *Pi_plus;
        TLorentzVector  K_minus1K_minus2Pi_plus = *K_minus1 + *K_minus2 + *Pi_plus;
        // All the different three-combinations of products

        K_plusK_minus1Hist1->Fill(K_plusK_minus1.M2(), weight);
        K_plusK_minus2Hist->Fill(K_plusK_minus2.M2(), weight);
        K_minus1K_minus2Hist->Fill(K_minus1K_minus2.M2(), weight);

        K_plusPi_plusHist1->Fill(K_plusPi_plus.M2(), weight);
        K_minus1Pi_plusHist->Fill(K_minus1Pi_plus.M2(), weight);
        K_minus2Pi_plusHist->Fill(K_minus2Pi_plus.M2(), weight);

        K_plusK_minus1K_minus2Hist1->Fill(K_plusK_minus1K_minus2.M2(), weight);

        K_plusK_minus1Pi_plusHist1->Fill(K_plusK_minus1Pi_plus.M2(), weight);
        K_plusK_minus2Pi_plusHist->Fill(K_plusK_minus2Pi_plus.M2(), weight);
        K_minus1K_minus2Pi_plusHist->Fill(K_minus1K_minus2Pi_plus.M2(), weight);

        K_plusK_minus1Hist2->Fill(K_plusK_minus1.M(), weight);
        K_plusPi_plusHist2->Fill(K_plusPi_plus.M(), weight);
        K_plusK_minus1K_minus2Hist2->Fill(K_plusK_minus1K_minus2.M(), weight);
        K_plusK_minus1Pi_plusHist2->Fill(K_plusK_minus1Pi_plus.M(), weight);
        // Fill all the histograms with all the invariant masses (squared)
    }

    TCanvas* canv1 = new TCanvas("canv1", "Canvas", 1200, 800);
    canv1->Divide(3,1);

    canv1->cd(1);
    K_plusK_minus1Hist1->GetXaxis()->CenterTitle();
    K_plusK_minus1Hist1->GetXaxis()->SetTitleOffset(1.25);
    K_plusK_minus1Hist1->SetLineColor(2);
    K_plusK_minus1Hist1->Draw();

    canv1->cd(2);
    K_plusK_minus2Hist->GetXaxis()->CenterTitle();
    K_plusK_minus2Hist->GetXaxis()->SetTitleOffset(1.25);
    K_plusK_minus2Hist->SetLineColor(3);
    K_plusK_minus2Hist->Draw();

    canv1->cd(3);
    K_minus1K_minus2Hist->GetXaxis()->CenterTitle();
    K_minus1K_minus2Hist->GetXaxis()->SetTitleOffset(1.25);
    K_minus1K_minus2Hist->SetLineColor(4);
    K_minus1K_minus2Hist->Draw();

    TCanvas* canv2 = new TCanvas("canv2", "Canvas", 1200, 800);
    canv2->Divide(3,1);

    canv2->cd(1);
    K_plusPi_plusHist1->GetXaxis()->CenterTitle();
    K_plusPi_plusHist1->GetXaxis()->SetTitleOffset(1.25);
    K_plusPi_plusHist1->SetLineColor(2);
    K_plusPi_plusHist1->Draw();

    canv2->cd(2);
    K_minus1Pi_plusHist->GetXaxis()->CenterTitle();
    K_minus1Pi_plusHist->GetXaxis()->SetTitleOffset(1.25);
    K_minus1Pi_plusHist->SetLineColor(3);
    K_minus1Pi_plusHist->Draw();

    canv2->cd(3);
    K_minus2Pi_plusHist->GetXaxis()->CenterTitle();
    K_minus2Pi_plusHist->GetXaxis()->SetTitleOffset(1.25);
    K_minus2Pi_plusHist->SetLineColor(4);
    K_minus2Pi_plusHist->Draw();

    TCanvas* canv3 = new TCanvas("canv3", "Canvas", 1200, 800);

    K_plusK_minus1K_minus2Hist1->GetXaxis()->CenterTitle();
    K_plusK_minus1K_minus2Hist1->GetXaxis()->SetTitleOffset(1.25);
    K_plusK_minus1K_minus2Hist1->SetLineColor(6);
    K_plusK_minus1K_minus2Hist1->Draw();

    TCanvas* canv4 = new TCanvas("canv4", "Canvas", 1200, 800);
    canv4->Divide(3,1);

    canv4->cd(1);
    K_plusK_minus1Pi_plusHist1->GetXaxis()->CenterTitle();
    K_plusK_minus1Pi_plusHist1->GetXaxis()->SetTitleOffset(1.25);
    K_plusK_minus1Pi_plusHist1->SetLineColor(2);
    K_plusK_minus1Pi_plusHist1->Draw();

    canv4->cd(2);
    K_plusK_minus2Pi_plusHist->GetXaxis()->CenterTitle();
    K_plusK_minus2Pi_plusHist->GetXaxis()->SetTitleOffset(1.25);
    K_plusK_minus2Pi_plusHist->SetLineColor(3);
    K_plusK_minus2Pi_plusHist->Draw();

    canv4->cd(3);
    K_minus1K_minus2Pi_plusHist->GetXaxis()->CenterTitle();
    K_minus1K_minus2Pi_plusHist->GetXaxis()->SetTitleOffset(1.25);
    K_minus1K_minus2Pi_plusHist->SetLineColor(4);
    K_minus1K_minus2Pi_plusHist->Draw();

    TCanvas *canv5 = new TCanvas("canv5", "Canvas", 1000, 1000);
    canv5->Divide(2,2);

    canv5->cd(1);
    K_plusK_minus1Hist2->SetLineColor(1);
    K_plusK_minus1Hist2->Draw();

    canv5->cd(2);
    K_plusPi_plusHist2->SetLineColor(2);
    K_plusPi_plusHist2->Draw();

    canv5->cd(3);
    K_plusK_minus1K_minus2Hist2->SetLineColor(3);
    K_plusK_minus1K_minus2Hist2->Draw();

    canv5->cd(4);
    K_plusK_minus1Pi_plusHist2->SetLineColor(4);
    K_plusK_minus1Pi_plusHist2->Draw();

    canv1->Print("../graphs/FourBodyDecay1.eps");
    canv2->Print("../graphs/FourBodyDecay2.eps");
    canv3->Print("../graphs/FourBodyDecay3.eps");
    canv4->Print("../graphs/FourBodyDecay4.eps");

    canv5->Print("../graphs/FourBodyDecay.eps");

    delete canv1;
    delete canv2;
    delete canv3;
    delete canv4;
    delete canv5;

    delete K_plusK_minus1Hist1;
    delete K_plusK_minus2Hist;
    delete K_minus1K_minus2Hist;

    delete K_plusPi_plusHist1;
    delete K_minus1Pi_plusHist;
    delete K_minus2Pi_plusHist;

    delete K_plusK_minus1K_minus2Hist1;

    delete K_plusK_minus1Pi_plusHist1;
    delete K_plusK_minus2Pi_plusHist;
    delete K_minus1K_minus2Pi_plusHist;

    delete K_plusK_minus1Hist2;
    delete K_plusPi_plusHist2;
    delete K_plusK_minus1K_minus2Hist2;
    delete K_plusK_minus1Pi_plusHist2;

    return 0;
}
