#include "toppartner/analysis/Effective.hh"
#include "toppartner/tagger/TruthLevel.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::fast | boca::Output::plot_hist)
{
    toppartner::analysis::Effective<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<toppartner::tagger::TruthLevel>();
}

