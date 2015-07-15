#include "AnalysisBottom.hh"
#include "BottomTagger.hh"

int main()
{
    analysis::standardmodel::AnalysisBottom<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFullEfficiency();
    bottom_analysis.RunPlots();
}
