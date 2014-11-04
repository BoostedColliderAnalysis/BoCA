#include "HAnalysisHiggsCpv.hh"

int main()
{
  hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
