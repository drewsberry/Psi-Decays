#include "Program.h"
using namespace std;

void Program::Fit()
{
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

    TCanvas     *fitCanvas      = new TCanvas("fitCanvas", "Fitting Canvas", 1500, 500);
    fitCanvas->Divide(3,1);

    fitCanvas->cd(1);
    tree->Draw("pxlab", "", "E");
    pxHist     = (TH1F *)gPad->GetPrimitive("htemp");
    pxHist->SetTitle("p_{x} in Lab Frame; p_{x} [MeV/c]");
    pxHist->GetXaxis()->SetRangeUser(-30000,30000);
    //pxHist -> SetBins(100, pxHist -> GetXaxis() -> GetXmin(),pxHist -> GetXaxis() -> GetXmax());
    gaussFuncPx->SetLineWidth(1);

    pxHist->Fit("gaussFuncPx");
    // Fit px to a Gaussian 

    fitCanvas->cd(2);
    tree->Draw("pylab", "", "E");
    pyHist     = (TH1F *)gPad->GetPrimitive("htemp");
    pyHist->SetTitle("p_{y} in Lab Frame; p_{y} [MeV/c]");
    pyHist->GetXaxis()->SetRangeUser(-30000,30000);
    gaussFuncPy -> SetLineWidth(1);
    pyHist->Fit("gaussFuncPy");
    // Fit py to a Gaussian 

    fitCanvas->cd(3);
    tree->Draw("pzlab", "", "E");
    pzHist     = (TH1F *)gPad->GetPrimitive("htemp");
    pzHist->SetTitle("p_{z} in Lab Frame; p_{z} [MeV/c]");
    pzHist->GetXaxis()->SetRangeUser(0,600000);

    landauFunc->SetLineColor(kBlue);
    gaussFuncPz->SetLineColor(kBlue);
    pzHist->Fit("landauFunc","R");
    pzHist->Fit("gaussFuncPz", "R+");

    landauFunc->GetParameters(&ipar[0]);
    gaussFuncPz->GetParameters(&ipar[5]);

    totalPz->SetLineWidth(1);
    totalPz->SetParameters(ipar);
    pzHist->Fit("totalPz", "+");

    cout << "px chi^2/NDF: " << (totalPz->GetChisquare())/(totalPz->GetNDF()) << endl;

    totalPz->GetParameters(&fpar[0]);

    cout << endl;
    for (Int_t i = 0; i < 8; i++)
        cout << "Parameter " << i << ":  " << fpar[i] << endl;
    cout << endl;

    fitCanvas -> Print("fitCanvas.eps");

    pxRand      = new TH1F("pxRand", "pxRand", pxHist->GetNbinsX(), pxHist->GetXaxis()->GetXmin(), pxHist->GetXaxis()->GetXmax());
    pyRand      = new TH1F("pyRand", "pyRand", pyHist->GetNbinsX(), pyHist->GetXaxis()->GetXmin(), pyHist->GetXaxis()->GetXmax());
    pzRand      = new TH1F("pzRand", "pzRand", pzHist->GetNbinsX(), pzHist->GetXaxis()->GetXmin(), pzHist->GetXaxis()->GetXmax());

    pxHistScale = TH1F("pxHistScale", "pxHistScale", pxHist->GetNbinsX(), pxHist->GetXaxis()->GetXmin(), pxHist->GetXaxis()->GetXmax());
    pyHistScale = TH1F("pyHistScale", "pyHistScale", pyHist->GetNbinsX(), pyHist->GetXaxis()->GetXmin(), pyHist->GetXaxis()->GetXmax());
    pzHistScale = TH1F("pzHistScale", "pzHistScale", pzHist->GetNbinsX(), pzHist->GetXaxis()->GetXmin(), pzHist->GetXaxis()->GetXmax());   
    
    for (Int_t i; i < 1000000; i++)
    {
        pxRand->Fill(gaussFuncPx -> GetRandom());
        pyRand->Fill(gaussFuncPy -> GetRandom());
        pzRand->Fill(totalPz -> GetRandom());
    }

    TCanvas     *randCanvas     = new TCanvas("randCanvas", "Random Canvas", 1500, 500);
    randCanvas->Divide(3,1);

    randCanvas->cd(1);
    pxHistScale = *pxHist;
    pxHistScale.Draw();
    pxRand->Scale((pxHist->GetEntries())/(pxRand->GetEntries()));
    pxRand->Draw("same");


    randCanvas->cd(2);
    pyHistScale = *pyHist;
    pyHistScale.Draw();
    pyRand->Scale((pyHist->GetEntries())/(pyRand->GetEntries()));
    pyRand->Draw("same");

    randCanvas->cd(3);
    pzHistScale = *pzHist;
    pzHistScale.Draw();
    pzRand->Scale((pzHist->GetEntries())/(pzRand->GetEntries()));
    pzRand->Draw("same");

    randCanvas->Print("randCanvas.eps");

    TCanvas     *distroCanvas     = new TCanvas("distroCanvas", "Distribution Canvas", 1500, 500);
    distroCanvas->Divide(3,1);

    distroCanvas->cd(1);
    gaussFuncPx->Draw();

    distroCanvas->cd(2);
    gaussFuncPy->Draw();

    distroCanvas->cd(3);
    totalPz->Draw();

    distroCanvas->Print("distroCanvas.eps");
}
