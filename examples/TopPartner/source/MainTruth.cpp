#include "include/analysis/AnalysisTopPartnerEffective.hh"
#include "include/TruthLevel.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast | boca::Output::plot_hist)
{
    toppartner::AnalysisEffective<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<toppartner::TruthLevel>();
}

