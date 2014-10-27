#include "HAnalysisHeavyHiggsDelphes.hh"

int main()
{
  hheavyhiggs::HAnalysisHeavyHiggsDelphes *Analysis = new hheavyhiggs::HAnalysisHeavyHiggsDelphes();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
