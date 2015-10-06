/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "AnalysisTopPartnerSingleHadronic.hh"
#include "EventSingleHadronicTagger.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::naturalness::AnalysisSingleHadronic<Tagger> analysis;
    boca::Run(analysis, run);
}

int main()
{
    Run<boca::BottomTagger>();
    Run<boca::HiggsTagger>();
    Run<boca::BosonTagger>();
    Run<boca::WHadronicTagger>();
    Run<boca::TopHadronicTagger>();
    Run<boca::TopLeptonicTagger>();
    Run<boca::naturalness::TopPartnerHadronicTagger>();
    Run<boca::naturalness::TopPartnerLeptonicTagger>();
    Run<boca::naturalness::SignatureSingleHadronicTagger>(boca::Output::efficiency);
    Run<boca::naturalness::EventSingleHadronicTagger>(boca::Output::significance);
}

