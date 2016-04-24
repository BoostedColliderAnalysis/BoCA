#include "boca/standardmodel/AnalysisTop.hh"
#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/standardmodel/TopHadronicTagger.hh"
#include "boca/standardmodel/TopHadronicHep.hh"
#include "boca/standardmodel/TopHadronicHep2.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::TopAnalysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    switch (boca::standardmodel::TopAnalysis<boca::standardmodel::BottomTagger>::TopDecay()) {
    case boca::Decay::leptonic :
        Run<boca::standardmodel::BottomTagger>() ;
        Run<boca::standardmodel::WLeptonicTagger>();
        Run<boca::standardmodel::TopLeptonicTagger>(boca::Output::efficiency | boca::Output::plot);
        break;
    case boca::Decay::hadronic :
        switch (boca::standardmodel::TopAnalysis<boca::standardmodel::BottomTagger>::TopTagger()) {
        case boca::standardmodel::TopTagger::boca :
            Run<boca::standardmodel::BottomTagger>() ;
            Run<boca::standardmodel::WHadronicTagger>();
            Run<boca::standardmodel::TopHadronicTagger>(boca::Output::efficiency | boca::Output::plot);
            break;
        case boca::standardmodel::TopTagger::hep :
            Run<boca::standardmodel::TopHadronicHep>(boca::Output::efficiency | boca::Output::plot);
            break;
        case boca::standardmodel::TopTagger::hep2 :
            Run<boca::standardmodel::TopHadronicHep2>(boca::Output::efficiency | boca::Output::plot);
            break;
        }
    }
}

