/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "AnalysisTopPartnerSingleHadronic.hh"
#include "EventSingleHadronicTagger.hh"
#include "CompleteSingleHadronicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::naturalness::AnalysisSingleHadronic<Tagger> analysis;
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
    Run<boca::naturalness::TopPartnerHadronicNeutralTagger>(boca::Output::efficiency);
    Run<boca::naturalness::TopPartnerLeptonicNeutralTagger>(boca::Output::efficiency);
    Run<boca::naturalness::VetoTopPartnerLeptonicTagger>(boca::Output::efficiency);
    Run<boca::naturalness::SignatureSingleHadronicTagger>(boca::Output::significance);
    Run<boca::GlobalTagger>(boca::Output::significance | boca::Output::plot);
    Run<boca::naturalness::EventSingleHadronicTagger>(boca::Output::significance);
    Run<boca::naturalness::CompleteSingleHadronicTagger>(boca::Output::significance);
}

