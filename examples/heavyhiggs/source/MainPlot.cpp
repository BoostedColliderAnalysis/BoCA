#include "include/analysis/Neutral.hh"
#include "boca/EventNeutralTagger.hh"

int main()
{
    heavyhiggs::analysis::Neutral<heavyhiggs::tagger::EventNeutral> analysis;
    analysis.Run(boca::Output::significance);
}
