#include "HAnalysisHeavyHiggsPgs.hh"

int main()
{
    HAnalysisHeavyHiggsPgs *Analysis = new HAnalysisHeavyHiggsPgs();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}