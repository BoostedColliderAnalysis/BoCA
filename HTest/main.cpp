#include "HAnalysisTest.hh"

int main()
{
    hanalysis::HAnalysis *Analysis = new htest::HAnalysis();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
