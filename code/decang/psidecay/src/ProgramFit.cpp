#include "../include/Program.h"
using namespace std;

Int_t Program::Fit()
{
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

    fitCanvas -> Print("../graphs/fit/fitCanvas.eps");

    pxNBins = pxHist->GetNbinsX();
    pxXMin  = pxHist->GetXaxis()->GetXmin();
    pxXMax  = pxHist->GetXaxis()->GetXmax();
    
    pyNBins = pyHist->GetNbinsX();
    pyXMin  = pyHist->GetXaxis()->GetXmin();
    pyXMax  = pyHist->GetXaxis()->GetXmax();
    
    pzNBins = pzHist->GetNbinsX();
    pzXMin  = pzHist->GetXaxis()->GetXmin();
    pzXMax  = pzHist->GetXaxis()->GetXmax();

    pxRand      = new TH1F("pxRand", "pxRand", pxNBins, pxXMin, pxXMax);
    pyRand      = new TH1F("pyRand", "pyRand", pyNBins, pyXMin, pyXMax);
    pzRand      = new TH1F("pzRand", "pzRand", pzNBins, pzXMin, pzXMax);

    pxHistScale = TH1F("pxHistScale", "pxHistScale", pxNBins, pxXMin, pxXMax);
    pyHistScale = TH1F("pyHistScale", "pyHistScale", pyNBins, pyXMin, pyXMax);
    pzHistScale = TH1F("pzHistScale", "pzHistScale", pzNBins, pzXMin, pzXMax);   
    
    for (Int_t i; i < 1000000; i++)
    {
        pxRand->Fill(gaussFuncPx->GetRandom());
        pyRand->Fill(gaussFuncPy->GetRandom());
        pzRand->Fill(totalPz->GetRandom());
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

    randCanvas->Print("../graphs/fit/randCanvas.eps");

    TCanvas     *distroCanvas     = new TCanvas("distroCanvas", "Distribution Canvas", 1500, 500);
    distroCanvas->Divide(3,1);

    distroCanvas->cd(1);
    gaussFuncPx->Draw();

    distroCanvas->cd(2);
    gaussFuncPy->Draw();

    distroCanvas->cd(3);
    totalPz->Draw();

    distroCanvas->Print("../graphs/fit/distroCanvas.eps");

    return 0;
}
