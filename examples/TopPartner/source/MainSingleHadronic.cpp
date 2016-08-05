/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/analysis/AnalysisTopPartnerSingleHadronic.hh"
#include "include/tagger/EventSingleHadronicTagger.hh"
#include "include/tagger/CompleteSingleHadronicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::AnalysisSingleHadronic<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    Run<boca::standardmodel::tagger::Higgs>();
    Run<boca::standardmodel::tagger::Boson>();
    Run<boca::standardmodel::tagger::WHadronic>();
    Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::TopHadronic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    Run<toppartner::TopPartnerHadronicNeutralTagger>(boca::Output::efficiency);
    Run<toppartner::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
    Run<toppartner::VetoTopPartnerLeptonicTagger>(boca::Output::efficiency);
    Run<toppartner::SignatureSingleHadronicTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<toppartner::EventSingleHadronicTagger>(boca::Output::significance);
//     Run<toppartner::CompleteSingleHadronicTagger>(boca::Output::significance);
}

