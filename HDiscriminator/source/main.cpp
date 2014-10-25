#include "HAnalysisDiscriminator.hh"

int main()
{
  Discriminator::HAnalysis *Analysis = new Discriminator::HAnalysis();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
