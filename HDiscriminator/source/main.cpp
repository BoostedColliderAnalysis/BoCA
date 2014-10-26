#include "HAnalysisDiscriminator.hh"

int main()
{
  HiggsCPV::HAnalysis *Analysis = new HiggsCPV::HAnalysis();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
