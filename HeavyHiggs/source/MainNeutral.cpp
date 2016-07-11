#include "boca/AnalysisNeutral.hh"
#include "boca/EventNeutralTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::heavyhiggs::AnalysisNeutral<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<boca::heavyhiggs::JetPairTagger>();
    Run<boca::heavyhiggs::HeavyHiggsSemiTagger>();
    Run<boca::heavyhiggs::SignatureNeutralTagger>();
    Run<boca::heavyhiggs::EventNeutralTagger>(boca::Output::significance);
}
