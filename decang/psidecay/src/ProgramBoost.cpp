#include "../include/Program.h"
using namespace std;

Int_t Program::Boost()
{
    TLorentzVector Psi_3770(0.0, 0.0, 0.0, PSIMASS);

    Double_t masses[2] = { DMASS, DMASS };

    TGenPhaseSpace event;
    event.SetDecay(Psi_3770, 2, masses);

    for (Int_t n = 0; n < 1000000; n++)
    {
        Double_t        weight         = event.Generate(); // Weighting for each event

        TLorentzVector  *D0            = event.GetDecay(0); // First product
        TLorentzVector  *D0bar         = event.GetDecay(1); // Second product

        /* Note that event.GetDecay(n) returns a pointer to a TLorentzVector.
         * Additionally, note that the index in GetDecay(n) corresponds to that
         * index particle in the masses[] array. Hence here it makes no 
         * difference. */

        TLorentzVector  D0D0bar        = *D0 + *D0bar;
        // Add Lorentz Vector of two particle, for calculation of invariant mass
        Double_t        nonBoostedAngle = D0bar -> Angle(D0 -> Vect());
        // Get the angle between D0 vector and D0bar vector

        histNonBoost -> Fill(nonBoostedAngle*(180.0/TMath::Pi()), weight);
        /* Fill second hist with angle between D0 and D0bar. Because this is 
         * in the frame of centre of momentum, and there are only two particles
         * of equal mass, the angle between them should be 180 degrees */

        // Declare all the Lorentz Vector to be boosted different amounts
        // Note that the results of rand.Gaus are /1000 as they are in MeV not GeV
        Double_t        px              = (gaussFuncPx -> GetRandom())/1000.;
        Double_t        py              = (gaussFuncPy -> GetRandom())/1000.;
        Double_t        pz              = (totalPz -> GetRandom())/1000.;
        Double_t        E               = sqrt(px*px + py*py + pz*pz + (3.773*3.773));
        TLorentzVector  boostLorentzVector(px, py, pz, E);
        TVector3        boostVector     = (boostLorentzVector.BoostVector());
        // Default boost: specify particle momentum, then find boost vector therefrom

        D0 -> Boost(boostVector);
        D0bar -> Boost(boostVector);
        // Boost particles by previously calculated vector
        
        Double_t        boostedAngle    = D0bar->Angle(D0->Vect());
        // Calculate angle between boosted vectors
        histBoost->Fill(boostedAngle*(180.0/TMath::Pi()), weight);
        // Fill hist in degrees (default = radians)
    }


    TCanvas     *anglesCanvas        = new TCanvas("anglesCanvas", "anglesCanvas", 1000, 500);
    anglesCanvas->Divide(2,1);

    anglesCanvas->cd(1);
    histNonBoost->SetTitle("Non-Boosted Angle Between D ^{0} and #bar{D}^{0}; Angle [ #circ];");
    histNonBoost->Draw();

    anglesCanvas->cd(2);
    histBoost->SetLineColor(2);
    histBoost->SetTitle("Boosted Angle Between D ^{0} and #bar{D}^{0}; Angle [ #circ];");
    histBoost->Draw();

    anglesCanvas->Print("../graphs/boost/anglesCanvas.eps");

    TCanvas     *boostedAngle        = new TCanvas("boostedAngle", "boostedAngle", 1000, 500);

    histBoost->SetLineColor(4);
    histBoost->Draw();

    boostedAngle->Print("../graphs/boost/boostedAngle.eps");

    return 0;
}
