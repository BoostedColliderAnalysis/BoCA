#include "boca/standardmodel/AnalysisBoson.hh"
#include "boca/standardmodel/tagger/Boson.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::standardmodel::AnalysisBoson<Tagger> analysis;
    analysis.Run(run);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>(boca::Output::fast) ;
    Run<boca::standardmodel::tagger::Boson>(boca::Output::efficiency);
}

