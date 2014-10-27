#include "HAnalysisDiscriminator.hh"

int main()
{
  hcpvhiggs::HAnalysis *Analysis = new hcpvhiggs::HAnalysis();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
