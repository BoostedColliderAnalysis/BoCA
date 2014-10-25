#include "HAnalysisHeavyHiggsParton.hh"

int main()
{
  HeavyHiggs::HAnalysisHeavyHiggsParton *Analysis = new HeavyHiggs::HAnalysisHeavyHiggsParton();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
