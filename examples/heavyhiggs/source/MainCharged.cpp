#include "include/analysis/Charged.hh"
#include "include/tagger/EventCharged.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::fast)
{
    heavyhiggs::analysis::Charged<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<heavyhiggs::tagger::ChargedHiggsSemi>();
    Run<heavyhiggs::tagger::SignatureCharged>();
    Run<heavyhiggs::tagger::EventCharged>(boca::Output::significance);
}
