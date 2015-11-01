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
  Run<boca::BottomTagger>(boca::Output::normal) ;
    switch (boca::standardmodel::TopAnalysis<boca::BottomTagger>::TopDecay()) {
    case boca::Decay::hadronic : {
        Run<boca::WHadronicTagger>(boca::Output::fast);
        Run<boca::TopHadronicTagger>(boca::Output::efficiency);
        break;
    }
    case boca::Decay::leptonic : {
        Run<boca::WLeptonicTagger>(boca::Output::fast);
        Run<boca::TopLeptonicTagger>(boca::Output::efficiency);
        break;
    }
    }
}

