#include "boca/AnalysisNeutral.hh"
#include "boca/CutTaggerNeutral.hh"

template<typename Tagger>
void Run(boca::Output output)
{
    boca::heavyhiggs::AnalysisNeutral<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>(boca::Output::fast);
    Run<boca::heavyhiggs::CutTaggerNeutral>(boca::Output::cut);
}
