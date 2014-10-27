#include "HAnalysisTopTagger.hh"

int main()
{
    hanalysis::HAnalysis *Analysis = new htoptagger::HAnalysis();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
