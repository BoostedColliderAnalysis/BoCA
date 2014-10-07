#include "HAnalysisTest.hh"

int main()
{
    HAnalysisTest *Analysis = new HAnalysisTest();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
