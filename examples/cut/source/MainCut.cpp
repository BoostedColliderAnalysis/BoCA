//  Dummy tagger
#include "boca/tagger/Dummy.hh"
//  Cut based analysis
#include "cut/Analysis.hh"

int main(){
  // Create the cut based analysis using a Dummy tagger
  cut::Analysis<boca::tagger::Dummy> analysis;
  // Run the cut based analysis and create efficiency plots
  analysis.Run(boca::Output::efficiency);
}
