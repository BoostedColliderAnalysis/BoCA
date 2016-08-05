#include "include/analysis/AnalysisTopPartnerPair.hh"
#include "include/tagger/EventPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::AnalysisPair<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::Boson>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<toppartner::TopPartnerHadronicNeutralTagger>();
    Run<toppartner::TopPartnerLeptonicNeutralTagger>();
    Run<toppartner::TopPartnerPairTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<toppartner::EventPairTagger>(boca::Output::significance);
}
