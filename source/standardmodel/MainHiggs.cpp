#include "boca/standardmodel/AnalysisHiggs.hh"
#include "boca/standardmodel/tagger/Higgs.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::AnalysisHiggs<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>(boca::Output::fast) ;
    Run<boca::standardmodel::tagger::Higgs>(boca::Output::efficiency);
}
