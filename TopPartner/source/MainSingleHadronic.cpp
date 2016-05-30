/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/AnalysisTopPartnerSingleHadronic.hh"
#include "boca/EventSingleHadronicTagger.hh"
#include "boca/CompleteSingleHadronicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::toppartner::AnalysisSingleHadronic<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::HiggsTagger>();
    Run<boca::standardmodel::BosonTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::toppartner::TopPartnerHadronicNeutralTagger>(boca::Output::efficiency);
    Run<boca::toppartner::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
    Run<boca::toppartner::VetoTopPartnerLeptonicTagger>(boca::Output::efficiency);
    Run<boca::toppartner::SignatureSingleHadronicTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance);
    Run<boca::toppartner::EventSingleHadronicTagger>(boca::Output::significance);
//     Run<boca::toppartner::CompleteSingleHadronicTagger>(boca::Output::significance);
}

