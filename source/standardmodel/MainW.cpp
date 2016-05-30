#include "boca/standardmodel/AnalysisW.hh"
#include "boca/standardmodel/tagger/WHadronic.hh"
#include "boca/standardmodel/tagger/WLeptonic.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::AnalysisW<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>(boca::Output::fast) ;
    switch (boca::standardmodel::AnalysisW<boca::standardmodel::tagger::Bottom>::WDecay()) {
    case boca::Decay::hadronic : Run<boca::standardmodel::tagger::WHadronic>(boca::Output::efficiency);
        break;
    case boca::Decay::leptonic : Run<boca::standardmodel::tagger::WLeptonic>(boca::Output::efficiency);
        break;
    default : break;
    }
}
