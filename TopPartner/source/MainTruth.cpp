#include "boca/AnalysisTopPartnerEffective.hh"
#include "boca/../boca/TruthLevel.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast | boca::Output::plot_hist)
{
    boca::toppartner::AnalysisEffective<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::toppartner::TruthLevel>();
}

