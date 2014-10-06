#include "HAnalysisJetProperties.hh"

int main()
{
    HAnalysisJetProperties *Analysis = new HAnalysisJetProperties();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}