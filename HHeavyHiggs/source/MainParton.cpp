#include "HAnalysisHeavyHiggsParton.hh"

int main()
{
    HAnalysisHeavyHiggsParton *Analysis = new HAnalysisHeavyHiggsParton();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}