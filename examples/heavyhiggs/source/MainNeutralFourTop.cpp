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
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::WHadronic>();
    Run<standardmodel::tagger::WLeptonic>();
    Run<standardmodel::tagger::TopHadronic>();
    Run<standardmodel::tagger::TopLeptonic>();
    Run<heavyhiggs::tagger::JetPair>();
    Run<heavyhiggs::tagger::HeavyHiggsSemi>();
    Run<heavyhiggs::tagger::SignatureNeutral>();
    Run<heavyhiggs::tagger::EventNeutralFourTop>(boca::Output::significance);
}
