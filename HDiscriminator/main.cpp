#include "HAnalysis.hh"

int main()
{
    HAnalysis *Analysis = new HAnalysis();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}