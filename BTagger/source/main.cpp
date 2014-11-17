#include "HAnalysisHiggsCpv.hh"

int main()
{
  hbtagger::HAnalysis *Analysis = new hbtagger::HAnalysis();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
