#include "HJetDiscriminator.hh"

int main()
{
    HJetDiscriminator *Analysis = new HJetDiscriminator();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}