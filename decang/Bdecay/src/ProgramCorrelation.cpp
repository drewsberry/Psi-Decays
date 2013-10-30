#include "../include/Program.h"
using namespace std;

void Program::Correlation()
{
    TCanvas *BPxPyCanv = new TCanvas("BPxPyCanv", "BPxPyCanv", 1500, 500);
    BPxPyCanv->Divide(3,1);

    BPxPyCanv->cd(1);
    mctree1->Draw("D0_PX + Bach_PX:D0_PY + Bach_PY", backCut, "lego2");
    BPxPyLego = get2DHist();
    BPxPyLego->SetTitle("p_{x} Versus p_{y} for B (Lego); p_{y} (MeV/c); p_{x}");
    BPxPyLego->GetXaxis()->SetTitleOffset(2);
    BPxPyLego->GetYaxis()->SetTitleOffset(2);

    BPxPyCanv->cd(2);
    mctree1->Draw("D0_PX + Bach_PX:D0_PY + Bach_PY", backCut, "contour");
    BPxPyCont = get2DHist();
    BPxPyCont->SetTitle("p_{x} Versus p_{y} for B (Contour); p_{y} (MeV/c); p_{x}");

    BPxPyCanv->cd(3);
    mctree1->Draw("D0_PX + Bach_PX:D0_PY + Bach_PY", backCut, "scat");
    BPxPyScat = get2DHist();
    BPxPyScat->SetTitle("p_{x} Versus p_{y} for B (Scatter); p_{y} (MeV/c); p_{x}");
    BPxPyScat->SetMarkerStyle(1);

    cout << "Px Py Correlation Factor: " << BPxPyScat->GetCorrelationFactor() 
        << endl;
    correlationFactors << "Px Py Correlation Factor: " << BPxPyScat->GetCorrelationFactor()
        << endl;

    BPxPyCanv->Print("../graphs/correlation/BPxPyCanv.eps");

    TCanvas *BPxPzCanv = new TCanvas("BPxPzCanv", "BPxPzCanv", 1500, 500);
    BPxPzCanv->Divide(3,1);

    BPxPzCanv->cd(1);
    mctree1->Draw("D0_PX + Bach_PX:D0_PZ + Bach_PZ", backCut, "lego2");
    BPxPzLego = get2DHist();
    BPxPzLego->SetTitle("p_{x} Versus p_{z} for B (Lego); p_{z} (MeV/c); p_{x}");
    BPxPzLego->GetXaxis()->SetTitleOffset(2);
    BPxPzLego->GetYaxis()->SetTitleOffset(2);

    BPxPzCanv->cd(2);
    mctree1->Draw("D0_PX + Bach_PX:D0_PZ + Bach_PZ", backCut, "contour");
    BPxPzCont = get2DHist();
    BPxPzCont->SetTitle("p_{x} Versus p_{z} for B (Contour); p_{z} (MeV/c); p_{x}");

    BPxPzCanv->cd(3);
    mctree1->Draw("D0_PX + Bach_PX:D0_PZ + Bach_PZ", backCut, "scat");
    BPxPzScat = get2DHist();
    BPxPzScat->SetTitle("p_{x} Versus p_{z} for B (Scatter); p_{z} (MeV/c); p_{x}");
    BPxPzScat->SetMarkerStyle(1);

    cout << "Px Pz Correlation Factor: " << BPxPzScat->GetCorrelationFactor() 
        << endl;
    correlationFactors << "Px Pz Correlation Factor: " << BPxPzScat->GetCorrelationFactor()
        << endl;

    BPxPzCanv->Print("../graphs/correlation/BPxPzCanv.eps");

    TCanvas *BPyPzCanv = new TCanvas("BPyPzCanv", "BPyPzCanv", 1500, 500);
    BPyPzCanv->Divide(3,1);

    BPyPzCanv->cd(1);
    mctree1->Draw("D0_PY + Bach_PY:D0_PZ + Bach_PZ", backCut, "lego2");
    BPyPzLego = get2DHist();
    BPyPzLego->SetTitle("p_{y} Versus p_{z} for B (Lego); p_{z} (MeV/c); p_{y}");
    BPyPzLego->GetXaxis()->SetTitleOffset(2);
    BPyPzLego->GetYaxis()->SetTitleOffset(2);

    BPyPzCanv->cd(2);
    mctree1->Draw("D0_PY + Bach_PY:D0_PZ + Bach_PZ", backCut, "contour");
    BPyPzCont = get2DHist();
    BPyPzCont->SetTitle("p_{y} Versus p_{z} for B (Contour); p_{z} (MeV/c); p_{y}");

    BPyPzCanv->cd(3);
    mctree1->Draw("D0_PY + Bach_PY:D0_PZ + Bach_PZ", backCut, "scat");
    BPyPzScat = get2DHist();
    BPyPzScat->SetTitle("p_{y} Versus p_{z} for B (Scatter); p_{z} (MeV/c); p_{y}");
    BPyPzScat->SetMarkerStyle(1);

    cout << "Py Pz Correlation Factor: " << BPyPzScat->GetCorrelationFactor() 
        << endl;
    correlationFactors << "Py Pz Correlation Factor: " << BPyPzScat->GetCorrelationFactor()
        << endl;

    BPyPzCanv->Print("../graphs/correlation/BPyPzCanv.eps");

    ///////////////////////////////////////////////////////////////////////////
    TCanvas *Correlation = new TCanvas("Correlation", "Correlation", 1500, 1500);
    Correlation->Divide(3,3);

    Correlation->cd(1);
    BPxPyScat->Draw();

    Correlation->cd(2);
    BPxPyLego->Draw("lego2");
    
    Correlation->cd(3);
    BPxPyCont->Draw("contour");

    Correlation->cd(4);
    BPxPzScat->Draw();

    Correlation->cd(5);
    BPxPzLego->Draw("lego2");

    Correlation->cd(6);
    BPxPzCont->Draw("contour");

    Correlation->cd(7);
    BPyPzScat->Draw();

    Correlation->cd(8);
    BPyPzLego->Draw("lego2");

    Correlation->cd(9);
    BPyPzCont->Draw("contour");

    Correlation->Print("../graphs/correlation/Correlation.eps");

    delete BPxPyCanv;
    delete BPxPzCanv;
    delete BPyPzCanv;
    delete Correlation;

}
