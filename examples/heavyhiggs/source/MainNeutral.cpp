#include "include/analysis/Neutral.hh"
#include "include/tagger/EventNeutral.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::fast)
{
    heavyhiggs::analysis::Neutral<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<heavyhiggs::tagger::JetPair>();
    Run<heavyhiggs::tagger::HeavyHiggsSemi>();
    Run<heavyhiggs::tagger::SignatureNeutral>();
    Run<heavyhiggs::tagger::EventNeutral>(boca::Output::significance);
}
