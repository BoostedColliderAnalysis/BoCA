#include "HAnalysisHiggsCpv.hh"
#include "HMvaHiggsCpv.hh"
#include "HMvaPairs.hh"
#include "HMvaBTagger.hh"

int main()
{

    hmva::HMva *Mva;
    
    hmva::HFactory *Factory;

    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

//     Analysis->AnalysisLoop("BTagger");    
    Mva = new hhiggscpv::HMvaBTagger();
//     Factory = new hmva::HFactory(Mva);
    Analysis->SetMva(Mva);
    
//     Analysis->AnalysisLoop("JetPair");    
    Mva = new hhiggscpv::HMvaPair();    
    Factory = new hmva::HFactory(Mva);
    Analysis->SetMva(Mva);
    
    Analysis->AnalysisLoop("Event");    
    Mva = new hhiggscpv::HMvaEvent();    
    Factory = new hmva::HFactory(Mva);
    Analysis->SetMva(Mva);
    
    delete Factory;
    
    delete Mva;

    delete Analysis;

    return 1;

}
