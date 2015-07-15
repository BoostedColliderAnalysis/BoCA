# include "EflowAnalysis.hh"

# include "BottomTagger.hh"


int main()
{

     analysis::BottomTagger bottom_tagger;
     analysis::eflow::EflowAnalysis bottom_analysis(bottom_tagger);
     bottom_analysis.AnalysisMain();
}

