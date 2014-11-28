#include "HAnalysisHiggsCpv.hh"
#include "HMvaEvent.hh"
#include "HMvaHiggs.hh"
#include "HMvaBottom.hh"
#include "HMvaTop.hh"

int main()
{

    hmva::HFactory *Factory;
    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

    Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HBottomTagger);
    Factory = new hmva::HFactory(Analysis->BottomTagger);

    Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HTopTagger);
    Factory = new hmva::HFactory(Analysis->LeptonicTopTagger);

    Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HHiggsTagger);
    Factory = new hmva::HFactory(Analysis->HiggsTagger);

    Analysis->AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
    hmva::HMva *Mva = new hhiggscpv::HMvaEvent();
    Factory = new hmva::HFactory(Mva);

    delete Factory;
    delete Mva;
    delete Analysis;

    return 1;

}
