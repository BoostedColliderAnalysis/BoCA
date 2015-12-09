#include "AnalysisTop.hh"
#include "TopHadronicTagger.hh"
#include "TopHadronicHep.hh"
#include "TopLeptonicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::TopAnalysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    switch (boca::standardmodel::TopAnalysis<boca::standardmodel::BottomTagger>::TopDecay()) {
    case boca::Decay::hadronic : {
        Run<boca::standardmodel::BottomTagger>(boca::Output::normal) ;
        Run<boca::standardmodel::WHadronicTagger>(boca::Output::fast);
        Run<boca::standardmodel::TopHadronicTagger>(boca::Output::efficiency);
        break;
    }
    case boca::Decay::leptonic : {
        Run<boca::standardmodel::BottomTagger>(boca::Output::normal) ;
//         Run<boca::standardmodel::WLeptonicTagger>(boca::Output::fast);
        Run<boca::standardmodel::TopLeptonicTagger>(boca::Output::efficiency);
        break;
    }
    case boca::Decay::other : {
        Run<boca::standardmodel::TopHadronicHep>(boca::Output::efficiency);
        break;
    }
    }
}

