/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "AnalysisTopPartnerSingleHadronic.hh"
#include "EventSingleHadronicTagger.hh"
// #include "VetoTopPartnerLeptonicTagger.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::naturalness::AnalysisSingleHadronic<Tagger> analysis;
    boca::Run(analysis, run);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::HiggsTagger>();
    Run<boca::standardmodel::BosonTagger>();
    Run<boca::standardmodel::WHadronicTagger>(boca::Output::efficiency);
    Run<boca::standardmodel::TopHadronicTagger>(boca::Output::efficiency);
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::naturalness::TopPartnerHadronicTagger>(boca::Output::efficiency);
//     Run<boca::naturalness::TopPartnerLeptonicTagger>();
    Run<boca::naturalness::VetoTopPartnerLeptonicTagger>();
    Run<boca::naturalness::SignatureSingleHadronicTagger>(boca::Output::significance);
    Run<boca::naturalness::EventSingleHadronicTagger>(boca::Output::significance);
}

