# Readme

This code performs BDT analyses based on root files originating from MadGraph / Pythia / PGS / Delphes.

## Dependencies

* ROOT
* MadGraph with installed ExRootAnalysis and Delphes
* fastjet
* fastjet contrib (must be compiled with `CXXFLAGS=-fPIC`)
* libconfig
* The PEG

## Installation

* the following is tested on recent ubuntu installations
* edit `MadGraph` path in `FindMadGraph.cmake`
* if you are using a `ROOT` version other than the system version edit the `ROOT` path in `FindROOT.cmake`

    mkdir build
    cd build
    cmake ..
    make # for external dependencies
    make # for the actual program

## Usage

Each analysis needs a dedicated `Analysis` class, a set of `Tagger` classess and a `main.cpp` file.
The `Analysis` class contains the global information of the analysis, such as file names, path names, variables names.
Every `Tagger` class reconstructs or tags one specific particle or signature. Each analysis needs at least one dedicated `Tagger`.
The `main.cpp` defines the order in which each `Tagger` is passed to the `Analysis`.

## Git commands

* initial download of the project `git clone https://NAME@bitbucket.org/janhajer/analysis.git`
* downloading update from the server `git pull`
* save changes of specific files `git commit FILES`
* save changes in to all files `git commit -a`
* upload changes to server `git push`
* change branches `git checkout BRANCH`
* create new branch `git checkout -b NEWBRANCH`
* merge branches `git merge BRANCH`
* save unfinished work on stash `git stash`
* get stash changes back `git stash pop`

## Coding style

* use standard library when possible
* avoid heap allocation `new`
* prefer references `&` over pointers `*`
* follow [these naming conventions](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Naming)

## License

[License](License.md)

## Authors

[Authors](Authors.md)
