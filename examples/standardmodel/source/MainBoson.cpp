#include "standardmodel/analysis/Boson.hh"
#include "standardmodel/tagger/Boson.hh"

template<typename Tagger_>
void Run(boca::Output run = boca::Output::normal)
{
    standardmodel::analysis::Boson<Tagger_> analysis;
    analysis.Run(run);
}

int main()
{
    Run<standardmodel::tagger::Bottom>(boca::Output::fast) ;
    Run<standardmodel::tagger::Boson>(boca::Output::efficiency);
}

