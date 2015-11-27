#include "AnalysisNeutralFourTop.hh"
#include "CutTagger.hh"

int main()
{
    boca::heavyhiggs::AnalysisNeutralFourTop<boca::heavyhiggs::CutTagger> analysis;
    analysis.Run(boca::Output::cut);
}

