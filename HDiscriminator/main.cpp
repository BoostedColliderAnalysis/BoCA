#include "HAnalysisDiscriminator.hh"

int main()
{
    HAnalysisDiscriminator *Analysis = new HAnalysisDiscriminator();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}