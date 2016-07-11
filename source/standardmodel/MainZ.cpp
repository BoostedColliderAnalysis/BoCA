#include "boca/standardmodel/AnalysisZ.hh"
#include "boca/standardmodel/tagger/ZHadronic.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::AnalysisZ<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>(boca::Output::fast) ;
    Run<boca::standardmodel::tagger::ZHadronic>(boca::Output::efficiency);
}
