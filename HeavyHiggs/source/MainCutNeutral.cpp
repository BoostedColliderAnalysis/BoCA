#include "AnalysisNeutral.hh"
#include "CutTaggerNeutral.hh"

template<typename Tagger>
void Run(boca::Output output)
{
    boca::heavyhiggs::AnalysisNeutral<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast);
    Run<boca::heavyhiggs::CutTaggerNeutral>(boca::Output::cut);
}
