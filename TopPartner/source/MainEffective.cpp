#include "AnalysisTopPartnerEffective.hh"
#include "EventEffectiveTagger.hh"

// #include <stdio.h>
// #include <execinfo.h>
// #include <signal.h>
// #include <stdlib.h>
// #include <unistd.h>
//
// void handler(int sig)
// {
//     void* array[10];
//     size_t size;
//
//     // get void*'s for all entries on the stack
//     size = backtrace(array, 10);
//
//     // print out all the frames to stderr
//     std::fprintf(stderr, "Error: signal %d:\n", sig);
//     backtrace_symbols_fd(array, size, STDERR_FILENO);
//     exit(1);
// }

int main()
{
//     signal(SIGSEGV, handler);   // install our handler

    analysis::toppartner::AnalysisEffective<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();

    analysis::toppartner::AnalysisEffective<analysis::HiggsTagger> higgs_analysis;
    higgs_analysis.RunNormal();

    analysis::toppartner::AnalysisEffective<analysis::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunNormal();

    analysis::toppartner::AnalysisEffective<analysis::BosonTagger> boson_analysis;
    boson_analysis.RunNormal();

    analysis::toppartner::AnalysisEffective<analysis::toppartner::HiggsPairTagger> higgs_pair_analysis;
    higgs_pair_analysis.RunFullEfficiency();
    higgs_pair_analysis.RunPlots();

    analysis::toppartner::AnalysisEffective<analysis::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunNormal();

    analysis::toppartner::AnalysisEffective<analysis::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

    analysis::toppartner::AnalysisEffective<analysis::toppartner::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
    top_partner_leptonic_analysis.RunFullEfficiency();

    analysis::toppartner::AnalysisEffective<analysis::toppartner::TopPartnerHadronicTagger> top_partner_hadronic_analysis;
    top_partner_hadronic_analysis.RunFullEfficiency();
    top_partner_hadronic_analysis.RunPlots();

    analysis::toppartner::AnalysisEffective<analysis::toppartner::TopPartnerPairTagger> top_partner_pair_analysis;
    top_partner_pair_analysis.RunFullEfficiency();
    top_partner_pair_analysis.RunPlots();

    analysis::toppartner::AnalysisEffective<analysis::toppartner::SignatureEffectiveTagger> signature_analysis;
    signature_analysis.RunFullEfficiency();
    signature_analysis.RunPlots();

    analysis::toppartner::AnalysisEffective<analysis::toppartner::EventEffectiveTagger> event_analysis;
    event_analysis.RunFullSignificance();
    event_analysis.RunPlots();
}

