#include "AnalysisNeutralFourTop.hh"
#include "CutTagger.hh"

template<typename Tagger>
void Run(boca::Output output)
{
    boca::heavyhiggs::AnalysisNeutralFourTop<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast);
    Run<boca::heavyhiggs::CutTagger>(boca::Output::cut);
}
