#include "HJetDiscriminator.hh"

int main()
{
    Analysis::HAnalysis *Analysis = new HiggsCPV::HJetDiscriminator();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
