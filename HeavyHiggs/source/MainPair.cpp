#include "AnalysisPair.hh"
#include "JetPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::fusionpair::Analysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::JetPairTagger>(boca::Output::efficiency);
}
