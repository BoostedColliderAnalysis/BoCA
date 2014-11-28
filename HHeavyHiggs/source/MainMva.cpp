#include "HAnalysisHeavyHiggsMva.hh"
#include "HMvaEvent.hh"
// #include "HMvaHiggs.hh"
// #include "HMvaBottom.hh"
// #include "HMvaTop.hh"

int main()
{

    hmva::HMva *Mva;
    hmva::HFactory *Factory;
//     hmva::HReader* Reader;
    hheavyhiggs::HAnalysisMva *Analysis = new hheavyhiggs::HAnalysisMva();

    Analysis->AnalysisLoop(hheavyhiggs::HAnalysisMva::HBottomTagger);
// //     Mva = new hhiggscpv::HMvaBottom();
    Factory = new hmva::HFactory(Analysis->BottomTagger);
//     Reader = new hmva::HReader(Analysis->BottomTagger);
//     //     Analysis->SetMva(Mva);
//     Analysis->BottomTagger->SetMva();
//
    Analysis->AnalysisLoop(hheavyhiggs::HAnalysisMva::HTopTagger);
// //     Mva = new hhiggscpv::HMvaTop();
//     Factory = new hmva::HFactory(Analysis->LeptonicTopTagger);
//     Analysis->LeptonicTopTagger->SetMva();
// //
//     Analysis->AnalysisLoop(hheavyhiggs::HAnalysisMva::HHiggsTagger);
// //     Mva = new hhiggscpv::HMvaHiggs();
//     Factory = new hmva::HFactory(Analysis->HeavyHiggsTagger);
//     Analysis->HeavyHiggsTagger->SetMva();
// //
//     Analysis->AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
//     Mva = new hheavyhiggs::HMvaEvent();
//     Factory = new hmva::HFactory(Mva);
//     Analysis->SetMva(Mva);

    delete Factory;
    delete Mva;
    delete Analysis;

    return 1;

}
