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
```
mkdir build
cd build
cmake ..
make
```

## Git commands

* download from server `git pull`
* save changes `git commit -a`
* upload changes to server `git push`
* change branches `git checkout BRANCH`
* create new branch `git checkout -b NEWBRANCH`

## Coding style

* use standard library when possible
* avoid heap allocation (`new`)
* follow [these naming conventions](
[https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Naming](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Naming))