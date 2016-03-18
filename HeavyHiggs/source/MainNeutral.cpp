#include "AnalysisNeutral.hh"
#include "EventNeutralTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::heavyhiggs::AnalysisNeutral<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::heavyhiggs::JetPairTagger>();
    Run<boca::heavyhiggs::HeavyHiggsSemiTagger>();
    Run<boca::heavyhiggs::SignatureNeutralTagger>();
    Run<boca::heavyhiggs::EventNeutralTagger>(boca::Output::significance);
}
