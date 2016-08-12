#include "include/analysis/Pair.hh"
#include "include/tagger/JetPair.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::fast)
{
    heavyhiggs::analysis::Pair<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<heavyhiggs::tagger::JetPair>(boca::Output::efficiency);
}
