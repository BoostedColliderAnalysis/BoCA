#include "standardmodel/AnalysisW.hh"
#include "standardmodel/tagger/WHadronic.hh"
#include "standardmodel/tagger/WLeptonic.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    standardmodel::AnalysisW<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>(boca::Output::fast) ;
    switch (standardmodel::AnalysisW<standardmodel::tagger::Bottom>::WDecay()) {
    case boca::Decay::hadronic : Run<standardmodel::tagger::WHadronic>(boca::Output::efficiency);
        break;
    case boca::Decay::leptonic : Run<standardmodel::tagger::WLeptonic>(boca::Output::efficiency);
        break;
    default : break;
    }
}
