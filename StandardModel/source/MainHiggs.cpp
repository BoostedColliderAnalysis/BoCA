#include "AnalysisHiggs.hh"
#include "HiggsTagger.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::standardmodel::AnalysisHiggs<Tagger> analysis;
    boca::Run(analysis, run);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast) ;
    Run<boca::standardmodel::HiggsTagger>(boca::Output::efficiency);
}
