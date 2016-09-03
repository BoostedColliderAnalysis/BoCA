#include "standardmodel/AnalysisBoson.hh"
#include "standardmodel/tagger/Boson.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    standardmodel::AnalysisBoson<Tagger> analysis;
    analysis.Run(run);
}

int main()
{
    Run<standardmodel::tagger::Bottom>(boca::Output::fast) ;
    Run<standardmodel::tagger::Boson>(boca::Output::efficiency);
}

