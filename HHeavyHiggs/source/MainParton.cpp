#include "HAnalysisHeavyHiggsParton.hh"

int main()
{
  hheavyhiggs::HAnalysisHeavyHiggsParton *Analysis = new hheavyhiggs::HAnalysisHeavyHiggsParton();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
