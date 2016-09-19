#include "simple/Analysis.hh"
#include "simple/Tagger.hh"

/**
 * A simple TMVA based analysis
 * \example simple/source/MainSimple.cpp
 *
 * The analysis class
 * \include simple/simple/Analysis.hh
 *
 * The Tagger class
 * \include simple/simple/Tagger.hh
 * The Tagger definition
 * \include simple/source/Tagger.cpp
 *
 * The Observable class
 * \include simple/simple/Observables.hh
 * The Observable definition
 * \include simple/source/Observables.cpp
 *
 * The Branch class
 * \include simple/simple/Branch.hh
 * The Branch definition
 * \include simple/source/Branch.cpp
 * The root LinkDef necessary for the root file creation
 * \include simple/simple/LinkDef.hh
 * The main file
 */

int main()
{
    // Create an object of the simple Analysis and pass it the simple Tagger
    simple::Analysis<simple::Tagger> analysis;
    //  Run the simple analysis and create efficiency plots
    analysis.Run(boca::Output::efficiency);
}
