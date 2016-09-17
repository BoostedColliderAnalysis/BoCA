#include "simple/Analysis.hh"
#include "simple/Tagger.hh"

/**
 * A simple TMVA based analysis
 * \example simple/source/MainSimple.cpp
 *
 * The analysis class
 * \include simple/simple/Analysis.hh
 *
 * The Branch class
 * \include simple/simple/Branch.hh
 * \include simple/source/Branch.cpp
 * \include simple/simple/LinkDef.hh
 *
 * The Observable class
 * \include simple/simple/Observables.hh
 * \include simple/source/Observables.cpp
 *
 * The Tagger class
 * \include simple/simple/Tagger.hh
 * \include simple/source/Tagger.cpp
 */

int main(){
  simple::Analysis<simple::Tagger> analysis;
  analysis.Run(boca::Output::efficiency);
}
