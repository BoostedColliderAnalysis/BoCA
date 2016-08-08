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
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<heavyhiggs::tagger::HeavyHiggsSemi>();
    Run<heavyhiggs::tagger::EventFusion>(boca::Output::significance);
}
