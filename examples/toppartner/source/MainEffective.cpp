#include "include/analysis/Effective.hh"
#include "include/tagger/EventEffectiveTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::Effective<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::Higgs>();
    Run<boca::standardmodel::tagger::Boson>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<toppartner::HiggsPairTagger>(boca::Output::efficiency);
    Run<toppartner::TopPartnerHadronicNeutralTagger>(boca::Output::efficiency);
    Run<toppartner::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
//     Run<toppartner::TopPartnerHadronicChargedTagger>();
//     Run<toppartner::TopPartnerLeptonicChargedTagger>();
//     Run<toppartner::TopPartnerHadronicTagger>();
//     Run<toppartner::TopPartnerLeptonicTagger>();
    Run<toppartner::SignatureEffectiveTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<toppartner::EventEffectiveTagger>(boca::Output::significance);
}
