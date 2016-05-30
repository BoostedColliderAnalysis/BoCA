#include "boca/AnalysisPair.hh"
#include "boca/JetPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::fusionpair::Analysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::heavyhiggs::JetPairTagger>(boca::Output::efficiency);
}
