#include "../include/Program.h"
using namespace std;

void Program::Boost()
{
    TLorentzVector B(0.0, 0.0, 0.0, BMASS);

    Double_t masses[2] = {PSIMASS, KMASS};
    Double_t secondmasses[2] = {DMASS, DMASS};

    TGenPhaseSpace event;
    event.SetDecay(B, 2, masses);
    TGenPhaseSpace secondevent;

    psikNonBoostAngleHist = new TH1F("Non-Boosted #psi K Angle",
            "Non-Boosted Angle Between  #psi(3770) and K; Angle [ #circ];",
            50, 179, 181);

    d0d0barNonBoostAngleHist = new TH1F("Non-Boosted D^{0} #bar{D}D^{0} Angle",
            "Non-Boosted Angle Between D ^{0} and #bar{D}^{0}; Angle [ #circ];",
            50, 0, 55);

    psikBoostAngleHist = new TH1F("Boosted #psi K Angle",
            "Boosted Angle Between  #psi(3770) and K; Angle [ #circ];",
            50, 0, 6);

    d0d0barBoostAngleHist = new TH1F("Boosted D^{0} #bar{D}D^{0} Angle",
            "Boosted Angle Between D ^{0} and #bar{D}^{0}; Angle [ #circ];",
            50, 0, 1);

    for (Int_t i = 0; i < 10000000; i++)
    {
        randm = randm3.Rndm();

        Double_t        weight          = event.Generate();
        TLorentzVector  *Psi3770        = event.GetDecay(0);
        TLorentzVector  *K              = event.GetDecay(1);

        Double_t        PsiKAngle       = Psi3770->Angle(K->Vect());

        psikNonBoostAngleHist->Fill(PsiKAngle*(180./TMath::Pi()), weight);

        secondevent.SetDecay(*Psi3770, 2, secondmasses);

        Double_t        secondweight    = secondevent.Generate();
        TLorentzVector  *D0             = secondevent.GetDecay(0);
        TLorentzVector  *D0bar          = secondevent.GetDecay(1);

        Double_t        D0D0barAngle    = D0->Angle(D0bar->Vect());

        d0d0barNonBoostAngleHist->Fill(D0D0barAngle*(180./TMath::Pi()), secondweight);

        Double_t        Bpx             = (B_PxFunc->GetRandom())/1000.;
        Double_t        Bpy             = (B_PyFunc->GetRandom())/1000.;
        Double_t        Bpz;
        if(randm >= landaufrac) {
            Bpz             = (B_PzFitGaus->GetRandom())/1000.;
        } else {
            Bpz             = (B_PzFitLand->GetRandom())/1000.;
        }
        Double_t        BE              = sqrt(Bpx*Bpx + Bpy*Bpy + Bpz*Bpz + BMASS*BMASS);
        TLorentzVector  BBoostLorentzVector(Bpx, Bpy, Bpz, BE);
        TVector3        BBoostVector    = (BBoostLorentzVector.BoostVector());

        Psi3770->Boost(BBoostVector);
        K->Boost(BBoostVector);
        D0->Boost(BBoostVector);
        D0bar->Boost(BBoostVector);

        Double_t        PsiKBoostAngle   = Psi3770->Angle(K->Vect());
        Double_t        D0D0barBoostAngle= D0->Angle(D0bar->Vect());

        psikBoostAngleHist->Fill(PsiKBoostAngle*(180./TMath::Pi()), weight);
        d0d0barBoostAngleHist->Fill(D0D0barBoostAngle*(180./TMath::Pi()), secondweight);
    }

    TCanvas     *nonBoostAngleCanv   = new TCanvas("nonBoostAngleCanv", "nonBoostAngleCanv", 1000, 500);
    nonBoostAngleCanv->Divide(2,1);

    nonBoostAngleCanv->cd(1);
    psikNonBoostAngleHist->Draw();

    nonBoostAngleCanv->cd(2);
    d0d0barNonBoostAngleHist->SetLineColor(2);
    d0d0barNonBoostAngleHist->Draw();

    nonBoostAngleCanv->Print("../graphs/boost/nonBoostAngleCanv.eps");

    TCanvas     *boostAngleCanv   = new TCanvas("boostAngleCanv", "boostAngleCanv", 1000, 500);
    boostAngleCanv->Divide(2,1);

    boostAngleCanv->cd(1);
    psikBoostAngleHist->Draw();

    boostAngleCanv->cd(2);
    d0d0barBoostAngleHist->SetLineColor(2);
    d0d0barBoostAngleHist->Draw();

    boostAngleCanv->Print("../graphs/boost/boostAngleCanv.eps");

    delete nonBoostAngleCanv;
    delete boostAngleCanv;
}
