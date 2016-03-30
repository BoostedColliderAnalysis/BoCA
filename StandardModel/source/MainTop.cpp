#include "AnalysisTop.hh"
#include "TopHadronicTagger.hh"
#include "TopHadronicHep.hh"
#include "TopLeptonicTagger.hh"
#include "physics/Matrix3.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::TopAnalysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    switch (boca::standardmodel::TopAnalysis<boca::standardmodel::BottomTagger>::TopDecay()) {
    case boca::Decay::hadronic :
        Run<boca::standardmodel::BottomTagger>() ;
        Run<boca::standardmodel::WHadronicTagger>();
        Run<boca::standardmodel::TopHadronicTagger>(boca::Output::efficiency | boca::Output::plot);
        break;
    case boca::Decay::leptonic :
        Run<boca::standardmodel::BottomTagger>() ;
        Run<boca::standardmodel::WLeptonicTagger>();
        Run<boca::standardmodel::TopLeptonicTagger>(boca::Output::efficiency | boca::Output::plot);
        break;
    case boca::Decay::other :
        Run<boca::standardmodel::TopHadronicHep>(boca::Output::efficiency | boca::Output::plot);
        break;
    }
}

