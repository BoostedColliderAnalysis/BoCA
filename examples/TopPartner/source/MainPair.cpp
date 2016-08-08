#include "boca/AnalysisTopPartnerPair.hh"
#include "boca/EventPairTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::toppartner::AnalysisPair<Tagger> analysis;
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
    Run<boca::toppartner::TopPartnerHadronicNeutralTagger>();
    Run<boca::toppartner::TopPartnerLeptonicNeutralTagger>();
    Run<boca::toppartner::TopPartnerPairTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::toppartner::EventPairTagger>(boca::Output::significance);
}
