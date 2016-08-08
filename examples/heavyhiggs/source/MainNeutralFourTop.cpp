#include "include/analysis/NeutralFourTop.hh"
#include "include/tagger/EventNeutralFourTop.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::fast)
{
    heavyhiggs::analysis::NeutralFourTop<Tagger_> analysis;
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
    Run<heavyhiggs::tagger::EventNeutralFourTop>(boca::Output::significance);
}
