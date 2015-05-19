# Readme

This code performs BDT analyses based on root files originating from MadGraph / Pythia / PGS / Delphes.


## Dependencies

* ROOT
* MadGraph with ExRootAnalysis and Delphes 
* Fastjet
* Fastjet coontrib (must be compiled with `CXXFLAGS=-fPIC`)
* libconfig

## Installation

* edit MadGraph path in FindMadGraph.cmake
* if you are using a different than the standad ROOT version edit the ROOT path in FindROOT.cmake
     mkdir build
     cd build
     cmake ..
     make