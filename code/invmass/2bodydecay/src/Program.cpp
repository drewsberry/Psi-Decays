#include "../include/Program.h"
using namespace std;

Int_t Program::Code()
{
    /* Note that TFGenPhaseSpace, as per LHCb standard, is in GeV. Hence all the
    * calculations and graphs hereonin are in GeV. */

    if (!gROOT->GetClass("TGenPhaseSpace"))
        gSystem->Load("libPhysics"); // get and load TGenPhaseSpace class
 
    psiInvMass = new TH1F("#psi(3770) Decay",
            "#psi(3770) Meson Decay;m(D^{0}#bar{D^{0}}) [GeV/c^{2}];",
            50, 3, 4);
    // Initialise histogram for plot later
 
    TLorentzVector Psi_3770(0.0, 0.0, 0.0, PSIMASS);
    // Parent Psi 4-momentum in rest frame
 
    Double_t masses[2] = { DMASS, DMASS };
    // Product particle mass array
 
    TGenPhaseSpace event; // Declare event of type class TGenPhaseSpace
    event.SetDecay(Psi_3770, 2, masses); // Set up decay parents and products
 
    for (Int_t n = 0; n < 1000000; n++) // Loop 100,000 times
    {
        Double_t        weight         = event.Generate();
        // Produce weighting for each event
 
        TLorentzVector  *D_0           = event.GetDecay(0);
        TLorentzVector  *D_0bar        = event.GetDecay(1);
        // Get product 4-vectors from GteDecay()
 
        TLorentzVector  D_0D_0bar      = *D_0 + *D_0bar;
        // Add 4-vectors together, for purpose of calculating invariant mass
 
        psiInvMass->Fill(D_0D_0bar.M(), weight);
        // Fill histogram with invariant mass
    }
 
    TCanvas* PsiInvMassCanv = new TCanvas("PsiInvMassCanv", "PsiInvMassCanv", 500, 500);
 
    psiInvMass->GetXaxis()->CenterTitle();
    psiInvMass->GetXaxis()->SetTitleOffset(1.25);
    psiInvMass->Draw();
 
    PsiInvMassCanv->Print("../graphs/TwoBodyDecay.eps");

    delete PsiInvMassCanv;
    delete psiInvMass;

    return 0;
}
