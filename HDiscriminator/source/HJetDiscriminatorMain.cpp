#include "HJetDiscriminator.hh"

int main()
{
    Discriminator::HJetDiscriminator *Analysis = new Discriminator::HJetDiscriminator();

    Analysis->AnalysisLoop();

    delete Analysis;

    return 1;

}
