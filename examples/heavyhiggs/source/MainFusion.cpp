#include "include/analysis/Fusion.hh"
#include "include/tagger/EventFusion.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::fast)
{
    heavyhiggs::analysis::Fusion<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::WHadronic>();
    Run<standardmodel::tagger::WLeptonic>();
    Run<standardmodel::tagger::TopHadronic>();
    Run<standardmodel::tagger::TopLeptonic>();
    Run<heavyhiggs::tagger::HeavyHiggsSemi>();
    Run<heavyhiggs::tagger::EventFusion>(boca::Output::significance);
}
