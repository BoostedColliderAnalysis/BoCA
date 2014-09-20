#include "HAnalysisHeavyHiggs.hh"

int main()
{
    HAnalysisHeavyHiggs *Analysis = new HAnalysisHeavyHiggs();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}