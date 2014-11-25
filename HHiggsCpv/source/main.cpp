#include "HAnalysisHiggsCpv.hh"
#include "HMvaEvent.hh"
#include "HMvaHiggs.hh"
#include "HMvaBottom.hh"
#include "HMvaTop.hh"

int main()
{

    hmva::HMva *Mva;
    hmva::HFactory *Factory;
    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

    Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HBottomTagger);
// //     Mva = new hhiggscpv::HMvaBottom();
    Factory = new hmva::HFactory(Analysis->BottomTagger);
//     //     Analysis->SetMva(Mva);
    Analysis->BottomTagger->SetMva();
//
    Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HTopTagger);
//     Mva = new hhiggscpv::HMvaTop();
    Factory = new hmva::HFactory(Analysis->LeptonicTopTagger);
    Analysis->LeptonicTopTagger->SetMva();
//
    Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HHiggsTagger);
//     Mva = new hhiggscpv::HMvaHiggs();
    Factory = new hmva::HFactory(Analysis->HiggsTagger);
    Analysis->HiggsTagger->SetMva();
//
    Analysis->AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
    Mva = new hhiggscpv::HMvaEvent();
    Factory = new hmva::HFactory(Mva);
    Analysis->SetMva(Mva);

    delete Factory;
    delete Mva;
    delete Analysis;

    return 1;

}
