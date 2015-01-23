#include "HAnalysisHeavyHiggsMva.hh"

#include "fastjet/LimitedWarning.hh"


// #include <stdio.h>
// #include <execinfo.h>
// #include <signal.h>
// #include <stdlib.h>
// #include <unistd.h>


// void handler(int sig) {
//   void *array[10];
//   size_t size;
//
//   // get void*'s for all entries on the stack
//   size = backtrace(array, 10);
//
//   // print out all the frames to stderr
//   fprintf(stderr, "Error: signal %d:\n", sig);
//   backtrace_symbols_fd(array, size, STDERR_FILENO);
//   exit(1);
// }
//
// void handler2() {
//   void *array[10];
//   size_t size;
//
//   // get void*'s for all entries on the stack
//   size = backtrace(array, 10);
//
//   // print out all the frames to stderr
//   fprintf(stderr, "Error: signal %d:\n");
//   backtrace_symbols_fd(array, size, STDERR_FILENO);
//   exit(1);
// }


void RunTagger(const hanalysis::HAnalysis::HTagger Tagger)
{
    hanalysis::HFactory *Factory;
    hanalysis::HReader *Reader;
    bool HasFactory = 0;
    bool HasReader = 0;

    hheavyhiggs::HAnalysisMva *Analysis = new hheavyhiggs::HAnalysisMva();
    const std::string Name = Analysis->GetStudyNames(Tagger);

    Analysis->Print(Analysis->HError, "Tagger", Tagger, Name);

    TFile *File(0);
    std::string FileName = Analysis->GetProjectName() + "/" + Name + ".root";

    if (gSystem->AccessPathName(FileName.c_str())) Analysis->AnalysisLoop(Tagger);

    FileName = Analysis->GetProjectName() + "/Mva" + Name + ".root";

    Analysis->GetFiles(Tagger, hanalysis::HObject::HSignal);
    if (gSystem->AccessPathName(FileName.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HBottomTagger:
            Factory = new hanalysis::HFactory(Analysis->BottomTagger);
            break;
        case hanalysis::HAnalysis::HJetPairTagger:
            Factory = new hanalysis::HFactory(Analysis->JetPairTagger);
            break;
        case hanalysis::HAnalysis::HWHadronicTagger:
            Factory = new hanalysis::HFactory(Analysis->WHadronicTagger);
            break;
        case hanalysis::HAnalysis::HWSemiTagger:
            Factory = new hanalysis::HFactory(Analysis->WSemiTagger);
            break;
        case hanalysis::HAnalysis::HTopLeptonicTagger:
            Factory = new hanalysis::HFactory(Analysis->TopLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HTopHadronicTagger:
            Factory = new hanalysis::HFactory(Analysis->TopHadronicTagger);
            break;
        case hanalysis::HAnalysis::HTopSemiTagger:
            Factory = new hanalysis::HFactory(Analysis->TopSemiTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger:
            Factory = new hanalysis::HFactory(Analysis->HeavyHiggsLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsHadronicTagger:
            Factory = new hanalysis::HFactory(Analysis->HeavyHiggsHadronicTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsSemiTagger:
            Factory = new hanalysis::HFactory(Analysis->HeavyHiggsSemiTagger);
            break;
        case hanalysis::HAnalysis::HEventLeptonicTagger:
            Factory = new hanalysis::HFactory(Analysis->EventLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HEventHadronicTagger:
            Factory = new hanalysis::HFactory(Analysis->EventHadronicTagger);
            break;
        case hanalysis::HAnalysis::HEventSemiTagger:
            Factory = new hanalysis::HFactory(Analysis->EventSemiTagger);
            break;
//         case hanalysis::HAnalysis::HChargedHiggsSemiTagger:
//           Factory = new hanalysis::HFactory(Analysis->ChargedHiggsSemiTagger);
//           break;
        default:
            std::cout << "Unhandled case" << std::endl;
        }
        HasFactory = 1;
    }
//     if (HasFactory) delete Factory;

    FileName = Analysis->GetProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HEventLeptonicReader:
            Reader = new hanalysis::HReader(Analysis->EventLeptonicTagger);
            Reader->SimpleMVALoop();
            break;
        case hanalysis::HAnalysis::HEventSemiReader:
            Reader = new hanalysis::HReader(Analysis->EventSemiTagger);
            Reader->SimpleMVALoop();
            break;
//         case hanalysis::HAnalysis::HHeavyHiggsSemiReader:
//           Reader = new hanalysis::HReader(Analysis->HeavyHiggsSemiTagger);
//           Reader->SimpleMVALoop();
//           break;
        default:
            std::cout << "Unhandled case" << std::endl;
        }
        HasReader = 1;
    }
//     if (HasReader) delete Reader;

    delete Analysis;
}

int main()
{
    /// controls whether the error message (and the backtrace, if its printing is enabled)
    /// is printed out or not
    fastjet::Error::set_print_errors(true);
    /// controls whether the backtrace is printed out with the error message or not.
    /// The default is "false".
    fastjet::Error::set_print_backtrace(true);

//   signal(SIGSEGV, handler);   // install our handler
//   signal(fastjet::PseudoJet::InexistentUserInfo(), handler2);   // install our handler

    RunTagger(hanalysis::HAnalysis::HBottomTagger);
    RunTagger(hanalysis::HAnalysis::HBottomReader);

    RunTagger(hanalysis::HAnalysis::HJetPairTagger);
    RunTagger(hanalysis::HAnalysis::HJetPairReader);
//
    RunTagger(hanalysis::HAnalysis::HWHadronicTagger);
    RunTagger(hanalysis::HAnalysis::HWHadronicReader);
//
    RunTagger(hanalysis::HAnalysis::HWSemiTagger);
    RunTagger(hanalysis::HAnalysis::HWSemiReader);
//
//     RunTagger(hanalysis::HAnalysis::HTopLeptonicTagger);
//     RunTagger(hanalysis::HAnalysis::HTopLeptonicReader);
//
    RunTagger(hanalysis::HAnalysis::HTopHadronicTagger);
    RunTagger(hanalysis::HAnalysis::HTopHadronicReader);
//
    RunTagger(hanalysis::HAnalysis::HTopSemiTagger);
    RunTagger(hanalysis::HAnalysis::HTopSemiReader);
//
// //     RunTagger(hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger);
// //     RunTagger(hanalysis::HAnalysis::HHeavyHiggsLeptonicReader);
//
// //     RunTagger(hanalysis::HAnalysis::HEventLeptonicTagger);
// //     RunTagger(hanalysis::HAnalysis::HEventLeptonicReader);
//
    RunTagger(hanalysis::HAnalysis::HHeavyHiggsSemiTagger);
    RunTagger(hanalysis::HAnalysis::HHeavyHiggsSemiReader);
//
    RunTagger(hanalysis::HAnalysis::HEventSemiTagger);
    RunTagger(hanalysis::HAnalysis::HEventSemiReader);
//
// //     RunTagger(hanalysis::HAnalysis::HHeavyHiggsHadronicTagger);
// //     RunTagger(hanalysis::HAnalysis::HEventHadronicTagger);
//
// //     RunTagger(hanalysis::HAnalysis::HChargedHiggsSemiTagger);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;



    return 0;

}

