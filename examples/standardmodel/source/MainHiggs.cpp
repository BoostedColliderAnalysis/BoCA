#include "standardmodel/AnalysisHiggs.hh"
#include "standardmodel/tagger/Higgs.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    standardmodel::AnalysisHiggs<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>(boca::Output::fast) ;
    Run<standardmodel::tagger::Higgs>(boca::Output::efficiency);
}
