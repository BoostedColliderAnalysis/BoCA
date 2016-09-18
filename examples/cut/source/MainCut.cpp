// Include the cut based analysis
#include "cut/Analysis.hh"

/**
 * \example cut/source/MainCut.cpp
 * A simple Cut based analysis
 *
 * \include cut/cut/Analysis.hh
 * The analysis class is called like this
 */

int main(){
  // Create an object of the cut based analysis
  cut::Analysis analysis;
  // Run the analysis and create efficiency plots
  analysis.Run(boca::Output::efficiency);
}
