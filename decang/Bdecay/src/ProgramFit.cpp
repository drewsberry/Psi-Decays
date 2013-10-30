#include "../include/Program.h"
using namespace std;

void Program::Fit()
{
    TCanvas *D0MomCanv = new TCanvas("D0MomCanv", "D0MomCanv", 1000, 1000);
    D0MomCanv->Divide(2,2);

    D0MomCanv->cd(1);
    mctree1->Draw("D0_PX", backCut);
    D0_PxHist = get1DHist();
    D0_PxHist->SetTitle("D^{0} p_{x}; p_{x} (MeV/c)");
    D0_PxHist->SetLineColor(kRed);
    mctree1->Draw("D0_PX", backCut && D0PXCut, "same");


    D0MomCanv->cd(2);
    mctree1->Draw("D0_PY", backCut);
    D0_PyHist = get1DHist();
    D0_PyHist->SetTitle("D^{0} p_{y}; p_{y} (MeV/c)");
    D0_PyHist->SetLineColor(kRed);
    mctree1->Draw("D0_PY", backCut && D0PYCut, "same");

    D0MomCanv->cd(3);
    mctree1->Draw("D0_PZ", backCut);
    D0_PzHist = get1DHist();
    D0_PzHist->SetTitle("D^{0} p_{z}; p_{z} (MeV/c)");

    D0MomCanv->cd(4);
    mctree1->Draw("D0_E", backCut);
    D0_EHist = get1DHist();
    D0_EHist->SetTitle("D^{0} Energy; Energy (MeV)");

    D0MomCanv->Print("../graphs/fit/D0Momentum.eps");

    TCanvas *BachMomCanv = new TCanvas("BachMomCanv", "BachMomCanv", 1000, 1000);
    BachMomCanv->Divide(2,2);

    BachMomCanv->cd(1);
    mctree1->Draw("Bach_PX", backCut);
    Bach_PxHist = get1DHist();
    Bach_PxHist->SetTitle("Bachelor p_{x}; p_{x} (MeV/c)");
    Bach_PxHist->SetLineColor(kRed);
    mctree1->Draw("Bach_PX", backCut && BachPXCut, "same");

    BachMomCanv->cd(2);
    mctree1->Draw("Bach_PY", backCut);
    Bach_PyHist = get1DHist();
    Bach_PyHist->SetTitle("Bachelor p_{y}; p_{y} (MeV/c)");
    Bach_PyHist->SetLineColor(kRed);
    mctree1->Draw("Bach_PY", backCut && BachPYCut, "same");

    BachMomCanv->cd(3);
    mctree1->Draw("Bach_PZ", backCut);
    Bach_PzHist = get1DHist();
    Bach_PzHist->SetTitle("Bachelor p_{x}; p_{x} (MeV/c)");

    BachMomCanv->cd(4);
    mctree1->Draw("Bach_E", backCut);
    Bach_EHist = get1DHist();
    Bach_EHist->SetTitle("Bachelor p_{x}; p_{x} (MeV/c)");

    BachMomCanv->Print("../graphs/fit/BachMomentum.eps");

    TCanvas *BMomCanv = new TCanvas("BMomCanv", "BMomCanv", 1000, 1000);
    BMomCanv->Divide(2,2);

    BMomCanv->cd(1);
    mctree1->Draw("D0_PX + Bach_PX", backCut);
    B_PxHist = get1DHist();
    B_PxHist->SetTitle("B Meson p_{x}; p_{x} (MeV/c)");
    B_PxHist->SetLineColor(kRed);
    mctree1->Draw("D0_PX + Bach_PX", backCut && BPXCut, "same");

    BMomCanv->cd(2);
    mctree1->Draw("D0_PY + Bach_PY", backCut);
    B_PyHist = get1DHist();
    B_PyHist->SetTitle("B Meson p_{y}; p_{y} (MeV/c)");
    B_PyHist->SetLineColor(kRed);
    mctree1->Draw("D0_PY + Bach_PY", backCut && BPYCut, "same");

    BMomCanv->cd(3);
    mctree1->Draw("D0_PZ + Bach_PZ", backCut);
    B_PzHist = get1DHist();
    B_PzHist->SetTitle("B Meson p_{z}; p_{z} (MeV/c)");
    B_PzHist->SetLineColor(kRed);

    BMomCanv->cd(4);
    mctree1->Draw("D0_E + Bach_E", backCut);
    B_EHist = get1DHist();
    B_EHist->SetTitle("B Meson Energy; Energy (MeV/c)");

    BMomCanv->Print("../graphs/fit/BMomentum.eps");

    TCanvas *FitCanv = new TCanvas("FitCanv", "FitCanv", 1000, 1000);
    FitCanv->Divide(3,3);

    FitCanv->cd(1);
    D0_PxHist->GetYaxis()->SetRangeUser(0,500);
    D0_PxHist->Draw();
    D0_PxHist->Fit("D0_PxFit", "NR");
    D0_PxFunc->SetParameters(D0_PxFit->GetParameters());
    D0_PxFunc->SetLineColor(kBlue);
    D0_PxFunc->Draw("same");

    FitCanv->cd(2);
    D0_PyHist->Draw();
    D0_PyHist->Fit("D0_PyFit", "NR");
    D0_PyFunc->SetParameters(D0_PyFit->GetParameters());
    D0_PyFunc->SetLineColor(kBlue);
    D0_PyFunc->Draw("same");

    FitCanv->cd(4);
    Bach_PxHist->Draw();
    Bach_PxHist->Fit("Bach_PxFit", "NR");
    Bach_PxFunc->SetParameters(Bach_PxFit->GetParameters());
    Bach_PxFunc->SetLineColor(kBlue);
    Bach_PxFunc->Draw("same");

    FitCanv->cd(5);
    Bach_PyHist->Draw();
    Bach_PyHist->Fit("Bach_PyFit", "NR");
    Bach_PyFunc->SetParameters(Bach_PyFit->GetParameters());
    Bach_PyFunc->SetLineColor(kBlue);
    Bach_PyFunc->Draw("same");

    FitCanv->cd(7);
    B_PxHist->GetYaxis()->SetRangeUser(0,500);
    B_PxHist->Draw();
    B_PxHist->Fit("B_PxFit", "NR");
    B_PxFunc->SetParameters(B_PxFit->GetParameters());
    B_PxFunc->SetLineColor(kBlue);
    B_PxFunc->Draw("same");

    FitCanv->cd(8);
    B_PyHist->GetYaxis()->SetRangeUser(0,400);
    B_PyHist->Draw();
    B_PyHist->Fit("B_PyFit", "NR");
    B_PyFunc->SetParameters(B_PyFit->GetParameters());
    B_PyFunc->SetLineColor(kBlue);
    B_PyFunc->Draw("same");

    FitCanv->cd(9);
    B_PzHist->Draw();
    B_PzFitLand->SetLineColor(kGreen);
    B_PzFitGaus->SetLineColor(kGreen);
    B_PzHist->Fit("B_PzFitLand", "NR");
    B_PzHist->Fit("B_PzFitGaus", "NR+");

    B_PzFitLand->GetParameters(&ipar[0]);
    B_PzFitGaus->GetParameters(&ipar[5]);

    cout << endl;
    cout << "Parameters: " << endl;
    for(Int_t i = 0; i < 8; i++) {
        cout << "Parameter " << i << ": " << ipar[i] << endl;
    }
    cout << endl;

    Double_t landaufrac     = (B_PzFitLand->Integral(0,130000))/(B_PzFitLand->Integral(0,130000) + B_PzFitGaus->Integral(130000,1100000));

    for(Int_t i = 0; i < 7742; i++) {
        randm = randm3.Rndm();
        if(randm >= landaufrac) {
            B_PzRandHist->Fill(B_PzFitGaus->GetRandom());
        } else {
            B_PzRandHist->Fill(B_PzFitLand->GetRandom());
        }
    }

    B_PzRandHist->Draw("same");

    FitCanv->Print("../graphs/fit/FitCanv.eps");

    TCanvas *TransMomCanv = new TCanvas("TransMomCanv", "TransMomCanv", 1000, 500);
    TransMomCanv->Divide(2,1);

    TransMomCanv->cd(1);
    mctree1->Draw("D0_PT", backCut);
    D0_PTHist = get1DHist();
    D0_PTHist->SetTitle("D^{0} Transverse Momentum; D^{0} Tranverse Momentum [MeV/c]");
    D0_PTHist->SetLineColor(2);
    //mctree1->Draw("D0_PT", backCut && D0PTCut, "same");

    TransMomCanv->cd(2);
    mctree1->Draw("Bach_PT", backCut);
    Bach_PTHist = get1DHist();
    Bach_PTHist->SetTitle("Bach Transverse Momentum; Bach Tranverse Momentum [MeV/c]");
    Bach_PTHist->SetLineColor(2);
    //mctree1->Draw("Bach_PT", backCut && BachPTCut, "same");

    TransMomCanv->cd(3);

    TransMomCanv->Print("../graphs/fit/BachTransMom.eps");

    ////////////////////////////////////////////////////////////////////////////
    TCanvas *ComponentFits = new TCanvas("ComponentFits", "ComponentFits", 1500, 500);
    ComponentFits->Divide(3,1);

    ComponentFits->cd(1);
    B_PxHist->Draw("E");
    B_PxFunc->SetLineWidth(1);
    B_PxFunc->Draw("same");

    ComponentFits->cd(2);
    B_PyHist->Draw("E");
    B_PyFunc->SetLineWidth(1);
    B_PyFunc->Draw("same");

    ComponentFits->cd(3);
    B_PzHist->Draw("E");
    B_PzRandHist->Draw("same");

    ComponentFits->Print("../graphs/fit/ComponentFits.eps");

    delete D0MomCanv;
    delete BachMomCanv;
    delete BMomCanv;
    delete FitCanv;
    delete TransMomCanv;
    delete ComponentFits;
}
