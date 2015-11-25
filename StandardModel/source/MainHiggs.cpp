#include "AnalysisHiggs.hh"
#include "HiggsTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::AnalysisHiggs<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast) ;
    Run<boca::standardmodel::HiggsTagger>(boca::Output::efficiency);
}
