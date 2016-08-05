#include "include/analysis/AnalysisTopPartnerSingleLeptonic.hh"
#include "include/tagger/EventSingleLeptonicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::AnalysisSingleLeptonic<Tagger> analysis;
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
    Run<toppartner::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
    Run<toppartner::VetoTopPartnerHadronicTagger>(boca::Output::efficiency);
    Run<toppartner::SignatureSingleLeptonicTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<toppartner::EventSingleLeptonicTagger>(boca::Output::significance);
}
