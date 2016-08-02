#include "boca/AnalysisCharged.hh"
#include "boca/EventChargedTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::heavyhiggs::AnalysisCharged<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<boca::heavyhiggs::ChargedHiggsSemiTagger>();
    Run<boca::heavyhiggs::SignatureChargedTagger>();
    Run<boca::heavyhiggs::EventChargedTagger>(boca::Output::significance);
}
