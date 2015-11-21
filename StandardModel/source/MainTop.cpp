#include "AnalysisTop.hh"
#include "TopHadronicTagger.hh"
#include "TopLeptonicTagger.hh"
#include "Debug.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::standardmodel::TopAnalysis<Tagger> analysis;
    boca::Run(analysis, run);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::normal) ;
    switch (boca::standardmodel::TopAnalysis<boca::standardmodel::BottomTagger>::TopDecay()) {
    case boca::Decay::hadronic : {
        Run<boca::standardmodel::WHadronicTagger>(boca::Output::fast);
        Run<boca::standardmodel::TopHadronicTagger>(boca::Output::efficiency);
        break;
    }
    case boca::Decay::leptonic : {
//         Run<boca::standardmodel::WLeptonicTagger>(boca::Output::fast);
        Run<boca::standardmodel::TopLeptonicTagger>(boca::Output::efficiency);
        break;
    }
    }
}

