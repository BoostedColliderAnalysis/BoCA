#include "HJetDiscriminator.hh"

int main()
{
    hanalysis::HAnalysis *Analysis = new hcpvhiggs::HJetDiscriminator();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
