#include "AnalysisNeutralFourTop.hh"
#include "EventNeutralFourTopTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::heavyhiggs::AnalysisNeutralFourTop<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::JetPairTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::heavyhiggs::HeavyHiggsSemiTagger>();
    Run<boca::heavyhiggs::SignatureNeutralTagger>();
    Run<boca::heavyhiggs::EventNeutralFourTopTagger>(boca::Output::significance);
}
