#include "HAnalysisHiggsCpv.hh"

int main()
{
    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

    Analysis->AnalysisLoop("BTagger");


    hanalysis::HMvaBTagger *Mva = new hhiggscpv::HMvaBTagger();

    hmva::HFactory *Factory = new hmva::HFactory(Mva);

    delete Factory;

    delete Mva;

    Analysis->AnalysisLoop("Event");

    delete Analysis;

    return 1;

}
