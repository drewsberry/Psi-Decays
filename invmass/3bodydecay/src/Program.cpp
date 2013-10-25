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

    TH2F *DK-DKHist = new TH2F(
        "DK-DKHist; m^{2}(D^{0}K^{+}) [(GeV/c^{2})^{2}];m^{2}(#bar{D^{0}}K^{+}) [(GeV/c^{2})^{2}]",
        "DK-DK", 50, 5, 12, 50, 5, 12);
    TH2F *DK-DDHist = new TH2F(
        "DK-DDHist;m^{2}(D^{0}#bar{D^{0}}) [(GeV/c^{2})^{2}];m^{2}(D^{0}K^{+}) [(GeV/c^{2})^{2}]",
        "DK-DD", 50, 12, 25, 50, 5, 12);
    TH1F *D-DHist = new TH1F(
        "B^{+} Meson Decay;m(D^{0}#bar{D^{0}}) [GeV/c^{2}]", 
        "D-D", 50, 3.5, 5);
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

        DK-DKHist->Fill(D_0K_plus.M2(), D_0barK_plus.M2(), weight);
        DK-DDHist->Fill(D_0D_0bar.M2(), D_0K_plus.M2(), weight);
        // Fill the histograms with weighted invariant mass squared

        D-DHist->Fill(D_0D_0bar.M(), weight);
        // Fill the histograms with weighted invariant mass
    }

    TCanvas *2DCanv = new TCanvas("2DCanv", "2DCanvas", 1000, 500);
    2DCanv->Divide(2,1);

    2DCanv->cd(1);
    hist->GetXaxis()->CenterTitle();
    hist->GetXaxis()->SetTitleOffset(1.75);
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetTitleOffset(1.75);
    hist->Draw("Lego2"); // Lego 2D histogram

    2DCanv->cd(2);
    hist2->GetXaxis()->CenterTitle();
    hist2->GetXaxis()->SetTitleOffset(1.75);
    hist2->GetYaxis()->CenterTitle();
    hist2->GetYaxis()->SetTitleOffset(1.75);
    hist2->Draw("Lego2");

    TCanvas *1DCanv = new TCanvas("2DCanv", "1DCanvas", 500, 500);

    1DCanv->SetTitle("B^{+} Meson Decay;m(D^{0}#bar{D^{0}}) [GeV/c^{2}]");
    1DCanv->GetXaxis()->CenterTitle();
    1DCanv->GetXaxis()->SetTitleOffset(1.25);
    1DCanv->Draw();

    2DCanv->Print("../graphs/ThreeBodyDecay1.eps");
    1DCanv->Print("../graphs/ThreeBodyDecay2.eps");

    delete 1DCanv;
    delete 2DCanv;
    delete DK-DKHist;
    delete DK-DDHist;
    delete D-DHist;

    return 0;
}
