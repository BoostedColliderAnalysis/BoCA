#include "AnalysisTopPartnerSingleLeptonic.hh"
#include "EventSingleLeptonicTagger.hh"


#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "Debug.hh"

void handler(int sig)
{
    Info0;
    void* array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}



template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    Info0;
    boca::naturalness::AnalysisSingleLeptonic<Tagger> analysis;
    Info0;
    boca::Run(analysis, output);
}

int main()
{
    Info0;
    signal(SIGSEGV, handler);   // install our handler
    Info0;
    Run<boca::standardmodel::BottomTagger>();
    Info0;
    Run<boca::standardmodel::HiggsTagger>();
    Run<boca::standardmodel::BosonTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::naturalness::TopPartnerLeptonicTagger>();
    Run<boca::naturalness::TopPartnerHadronicTagger>();
    Run<boca::naturalness::SignatureSingleLeptonicTagger>(boca::Output::efficiency);
    Run<boca::naturalness::EventSingleLeptonicTagger>(boca::Output::significance);
}
