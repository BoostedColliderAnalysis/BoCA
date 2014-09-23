#include "HAnalysisHeavyHiggsDelphes.hh"

int main()
{
    HAnalysisHeavyHiggsDelphes *Analysis = new HAnalysisHeavyHiggsDelphes();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}