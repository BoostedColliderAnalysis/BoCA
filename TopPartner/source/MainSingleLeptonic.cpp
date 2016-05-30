#include "boca/AnalysisTopPartnerSingleLeptonic.hh"
#include "boca/EventSingleLeptonicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::toppartner::AnalysisSingleLeptonic<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::Higgs>();
    Run<boca::standardmodel::tagger::Boson>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<boca::toppartner::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
    Run<boca::toppartner::VetoTopPartnerHadronicTagger>(boca::Output::efficiency);
    Run<boca::toppartner::SignatureSingleLeptonicTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::toppartner::EventSingleLeptonicTagger>(boca::Output::significance);
}
