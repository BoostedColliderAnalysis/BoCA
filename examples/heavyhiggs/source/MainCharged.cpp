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
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::WHadronic>();
    Run<standardmodel::tagger::WLeptonic>();
    Run<standardmodel::tagger::TopHadronic>();
    Run<standardmodel::tagger::TopLeptonic>();
    Run<heavyhiggs::tagger::ChargedHiggsSemi>();
    Run<heavyhiggs::tagger::SignatureCharged>();
    Run<heavyhiggs::tagger::EventCharged>(boca::Output::significance);
}
