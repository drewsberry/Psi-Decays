#include "../include/Program.h"
using namespace std;

Int_t Program::Code()
{
    /* Note that TFGenPhaseSpace, as per LHCb standard, is in GeV. Hence all the
     * calculations and graphs hereonin are in GeV. */
     
    gStyle->SetOptStat(0); // Get rid of annoying statistics

    const Int_t NRGBs = 5;
    const Int_t NCont = 35;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle -> SetNumberContours(NCont);
    
    if (!gROOT->GetClass("TGenPhaseSpace")) // Get "TGenPhaseSpace" class
        gSystem->Load("libPhysics"); // Load it if successful

    DK_DKHist = new TH2F("DK-DK",
        "DK-DKHist; m^{2}(D^{0}K^{+}) [(GeV/c^{2})^{2}];m^{2}(#bar{D^{0}}K^{+}) [(GeV/c^{2})^{2}]",
         50, 5, 12, 50, 5, 12);
    DK_DDHist = new TH2F("DK-DD",
        "DK-DDHist;m^{2}(D^{0}#bar{D^{0}}) [(GeV/c^{2})^{2}];m^{2}(D^{0}K^{+}) [(GeV/c^{2})^{2}]",
         50, 12, 25, 50, 5, 12);
    D_DHist = new TH1F("D-D",
        "B^{+} Meson Decay;m(D^{0}#bar{D^{0}}) [GeV/c^{2}]", 
         50, 3.5, 5);
    // Declare the histograms to be ploted later

    TLorentzVector B_plus(0.0, 0.0, 0.0, BPLUSMASS);
    // Lorentz Vector for the parent B+ (in rest frame)

    Double_t masses[3] = { DMASS, DMASS, KPLUSMASS };
    // Array of masses for the product particles

    TGenPhaseSpace event; // Declare event of type class TGenPhaseSpace
    event.SetDecay(B_plus, 3, masses); // Set the decay up

    for (Int_t n = 0; n < 1000000; n++)
    {
        Double_t        weight          = event.Generate();
        // Generate weightings for each decay

        TLorentzVector  *D_0           = event.GetDecay(0);
        TLorentzVector  *D_0bar        = event.GetDecay(1);
        TLorentzVector  *K_plus        = event.GetDecay(2);
        /* Set decay products equal to result from GetDecay().
         * Note that the order of particles must correspond to the order
         * of the particles in the masses array, and that pointers to
         * TLorentzVectors are returned. */

        TLorentzVector  D_0K_plus      = *K_plus + *D_0;
        TLorentzVector  D_0barK_plus   = *K_plus + *D_0bar;
        TLorentzVector  D_0D_0bar      = *D_0 + *D_0bar;
        /* Add together all possible combinations of the three decay products.
         * Note the TLorentzVectors are pointers, so need to be dereferenced.
         * For use in calculating the invariant mass of the combinations*/

        DK_DKHist->Fill(D_0K_plus.M2(), D_0barK_plus.M2(), weight);
        DK_DDHist->Fill(D_0D_0bar.M2(), D_0K_plus.M2(), weight);
        // Fill the histograms with weighted invariant mass squared

        D_DHist->Fill(D_0D_0bar.M(), weight);
        // Fill the histograms with weighted invariant mass
    }

    TCanvas *TwoDCanv = new TCanvas("TwoDCanv", "TwoDCanvas", 1000, 500);
    TwoDCanv->Divide(2,1);

    TwoDCanv->cd(1);
    DK_DKHist->GetXaxis()->CenterTitle();
    DK_DKHist->GetXaxis()->SetTitleOffset(1.75);
    DK_DKHist->GetYaxis()->CenterTitle();
    DK_DKHist->GetYaxis()->SetTitleOffset(1.75);
    DK_DKHist->Draw("Lego2"); 

    TwoDCanv->cd(2);
    DK_DDHist->GetXaxis()->CenterTitle();
    DK_DDHist->GetXaxis()->SetTitleOffset(1.75);
    DK_DDHist->GetYaxis()->CenterTitle();
    DK_DDHist->GetYaxis()->SetTitleOffset(1.75);
    DK_DDHist->Draw("Lego2");

    TCanvas *OneDCanv = new TCanvas("TwoDCanv", "OneDCanvas", 500, 500);

    D_DHist->SetTitle("B^{+} Meson Decay;m(D^{0}#bar{D^{0}}) [GeV/c^{2}]");
    D_DHist->GetXaxis()->CenterTitle();
    D_DHist->GetXaxis()->SetTitleOffset(1.25);
    D_DHist->Draw();

    TwoDCanv->Print("../graphs/ThreeBodyDecay1.eps");
    OneDCanv->Print("../graphs/ThreeBodyDecay2.eps");

    delete OneDCanv;
    delete TwoDCanv;
    delete DK_DKHist;
    delete DK_DDHist;
    delete D_DHist;

    return 0;
}
