#include "HAnalysisHiggsCpv.hh"
#include "HMvaEvent.hh"
#include "HMvaPairs.hh"
#include "HMvaBTagger.hh"

int main()
{

    hmva::HMva *Mva;
    hmva::HFactory *Factory;
    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

    Analysis->AnalysisLoop("BottomTagger");
    Mva = new hhiggscpv::HMvaBTagger();
    Factory = new hmva::HFactory(Mva);
    Analysis->SetMva(Mva);
    
    Analysis->AnalysisLoop("TopTagger");
    Mva = new hhiggscpv::HMvaPair();
    Factory = new hmva::HFactory(Mva);
    Analysis->SetMva(Mva);

    Analysis->AnalysisLoop("HiggsTagger");
    Mva = new hhiggscpv::HMvaPair();
    Factory = new hmva::HFactory(Mva);
    Analysis->SetMva(Mva);

    Analysis->AnalysisLoop("EventTagger");
    Mva = new hhiggscpv::HMvaEvent();
    Factory = new hmva::HFactory(Mva);
    Analysis->SetMva(Mva);

    delete Factory;
    delete Mva;
    delete Analysis;

    return 1;

}