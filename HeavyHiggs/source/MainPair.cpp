#include "AnalysisPair.hh"
#include "JetPairTagger.hh"

int main()
{
    boca::fusionpair::Analysis<boca::standardmodel::BottomTagger > bottom_analysis;
    bottom_analysis.RunNormal();

    boca::fusionpair::Analysis<boca::JetPairTagger > pair_analysis;
    pair_analysis.RunFullEfficiency();
}
