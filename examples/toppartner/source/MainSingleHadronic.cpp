/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/analysis/SingleHadronic.hh"
#include "include/tagger/EventSingleHadronic.hh"
#include "include/tagger/CompleteSingleHadronic.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    toppartner::analysis::SingleHadronic<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::Higgs>();
    Run<standardmodel::tagger::Boson>();
    Run<standardmodel::tagger::WHadronic>();
    Run<standardmodel::tagger::WLeptonic>();
    Run<standardmodel::tagger::TopHadronic>();
    Run<standardmodel::tagger::TopLeptonic>();
    Run<toppartner::tagger::TopPartnerHadronicNeutral>(boca::Output::efficiency);
    Run<toppartner::tagger::TopPartnerLeptonicNeutral>(boca::Output::efficiency);
    Run<toppartner::tagger::VetoTopPartnerLeptonic>(boca::Output::efficiency);
    Run<toppartner::tagger::SignatureSingleHadronic>(boca::Output::significance);
    Run<boca::tagger::Global>(boca::Output::significance);
    Run<toppartner::tagger::EventSingleHadronic>(boca::Output::significance);
//     Run<toppartner::tagger::CompleteSingleHadronic>(boca::Output::significance);
}

