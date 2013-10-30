#include "../include/Program.h"
using namespace std;

void Program::Clean()
{
    correlationFactors.close();

    delete D0_PxFit;
    delete D0_PxFunc;
    delete D0_PyFit;
    delete D0_PyFunc;
    delete Bach_PxFit;
    delete Bach_PxFunc;
    delete Bach_PyFit;
    delete Bach_PyFunc;
    delete B_PxFit;
    delete B_PxFunc;
    delete B_PyFit;
    delete B_PyFunc;
    delete B_PzFitLand;
    delete B_PzFitGaus;
    delete B_PzRandHist;
}
