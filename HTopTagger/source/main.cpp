#include "HAnalysisTopTagger.hh"

int main()
{
    HAnalysisTopTagger *Analysis = new HAnalysisTopTagger();
        
    Analysis->AnalysisLoop();
    
    delete Analysis;
    
    return 1;
    
}