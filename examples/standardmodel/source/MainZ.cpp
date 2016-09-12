#include "standardmodel/analysis/Z.hh"
#include "standardmodel/tagger/ZHadronic.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    standardmodel::analysis::Z<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>(boca::Output::fast) ;
    Run<standardmodel::tagger::ZHadronic>(boca::Output::efficiency);
}
