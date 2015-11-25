#include "AnalysisCut.hh"
#include "CutTagger.hh"

int main()
{
    boca::heavyhiggs::AnalysisCut<boca::heavyhiggs::CutTagger> analysis;
    analysis.Run(boca::Output::cut);
}

