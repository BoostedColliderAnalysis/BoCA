#include "HAnalysisHeavyHiggsDelphes.hh"

int main()
{
  HeavyHiggs::HAnalysisHeavyHiggsDelphes *Analysis = new HeavyHiggs::HAnalysisHeavyHiggsDelphes();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
