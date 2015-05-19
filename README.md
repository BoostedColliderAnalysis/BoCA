# Readme

This code performs BDT analyses based on root files originating from MadGraph / Pythia / PGS / Delphes.

## Dependencies

* ROOT
* MadGraph with installed ExRootAnalysis and Delphes 
* fastjet
* fastjet contrib (must be compiled with `CXXFLAGS=-fPIC`)
* libconfig

## Installation

* the following is tested on recent ubuntu installations
* edit MadGraph path in FindMadGraph.cmake
* if you are using a ROOT version other than the system version edit the ROOT path in FindROOT.cmake
    mkdir build
    cd buil
    cmake ..
    make