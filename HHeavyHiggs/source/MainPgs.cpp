#include "HAnalysisHeavyHiggsPgs.hh"

int main()
{
  HeavyHiggs::HAnalysisHeavyHiggsPgs *Analysis = new HeavyHiggs::HAnalysisHeavyHiggsPgs();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
