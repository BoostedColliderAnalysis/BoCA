#include "AnalysisPair.hh"
#include "JetPairTagger.hh"

int main()
{
    analysis::fusionpair::Analysis<analysis::BottomTagger > bottom_analysis;
    bottom_analysis.RunNormal();

    analysis::fusionpair::Analysis<analysis::JetPairTagger > pair_analysis;
    pair_analysis.RunFullEfficiency();
}
