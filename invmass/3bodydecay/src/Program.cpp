#include "../include/Program.h"
using namespace std;

Int_t Program::Code()
{
    /* Note that TFGenPhaseSpace, as per LHCb standard, is in GeV. Hence all the
     * calculations and graphs hereonin are in GeV. */
     
    const Int_t NRGBs = 5;
    const Int_t NCont = 35;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle -> SetNumberContours(NCont);
    
    if (!gROOT->GetClass("TGenPhaseSpace")) // Get "TGenPhaseSpace" c;ass
        gSystem->Load("libPhysics"); // Load it if successful

    TH2F *hist = new TH2F("hist", "B Plus Decay", 50, 5, 12, 50, 5, 12);
    TH2F *hist2 = new TH2F("hist2", "B Plus Decay 2", 50, 12, 25, 50, 5, 12);
    TH1F *hist3 = new TH1F("hist3", "B Plus Decay 3", 50, 3.5, 5);
    // Declare the histograms to be ploted later

    TLorentzVector B_plus(0.0, 0.0, 0.0,5.27953);
    // Lorentz Vector for the parent B+ (in rest frame)

    Double_t masses[3] = { 1.86484, 1.86484, 0.493677 };
    // Array of masses for the product particles

    TGenPhaseSpace event; // Declare event of type class TGenPhaseSpace
    event.SetDecay(B_plus, 3, masses); // Set the decay up

    for (Int_t n = 0; n < 100000; n++) // Loop 100,000 times
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

        hist->Fill(D_0K_plus.M2(), D_0barK_plus.M2(), weight);
        hist2->Fill(D_0D_0bar.M2(), D_0K_plus.M2(), weight);
        // Fill the histograms with weighted invariant mass squared

        hist3->Fill(D_0D_0bar.M(), weight);
        // Fill the histograms with weighted invariant mass
    }

    // Split the canvas into 4 pads
    TCanvas *canv1 = new TCanvas("canv1", "Canvas", 1000, 500);
    canv1->Divide(2,1);

    gStyle->SetOptStat(0); // Get rid of annoying statistics

    canv1->cd(1);
    hist->SetTitle(";m^{2}(D^{0}K^{+}) [(GeV/c^{2})^{2}];m^{2}(#bar{D^{0}}K^{+}) [(GeV/c^{2})^{2}]");
    hist->GetXaxis()->CenterTitle();
    hist->GetXaxis()->SetTitleOffset(1.75);
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetTitleOffset(1.75);
    hist->Draw("Lego2"); // Lego 2D histogram

    canv1->cd(2);
    hist2->SetTitle(";m^{2}(D^{0}#bar{D^{0}}) [(GeV/c^{2})^{2}];m^{2}(D^{0}K^{+}) [(GeV/c^{2})^{2}]");
    hist2->GetXaxis()->CenterTitle();
    hist2->GetXaxis()->SetTitleOffset(1.75);
    hist2->GetYaxis()->CenterTitle();
    hist2->GetYaxis()->SetTitleOffset(1.75);
    hist2->Draw("Lego2");

    TCanvas *canv2 = new TCanvas("canv2", "Canvas", 500, 500);

    hist3->SetTitle("B^{+} Meson Decay;m(D^{0}#bar{D^{0}}) [GeV/c^{2}]");
    hist3->GetXaxis()->CenterTitle();
    hist3->GetXaxis()->SetTitleOffset(1.25);
    hist3->Draw();

    canv1->Print("../graphs/ThreeBodyDecay1.eps");
    canv2->Print("../graphs/ThreeBodyDecay2.eps");

    delete canv1;
    delete canv2;
    delete hist;
    delete hist2;
    delete hist3;

    return 0;
}
