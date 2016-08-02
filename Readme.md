# Readme

This code performs staged BDT analyses using root files as in- and output format.

## Dependencies

* `ROOT` version >= 6 and compiled with TMVA and MathMore
* `fastjet`
* `fastjet contrib` (must be compiled with `CXXFLAGS=-fPIC`)
* `Boost` (`Optional`, `Range`, `Units`)

The BoCA code makes heavy use of modern c++ features. The limiting factor for the minimal supportet compiler version is given by the use of return type deduction.
Therefore the compiler version must be
* GCC version >= 4.9
* Clang version >= 3.3

## Installation

* the following is tested on recent ubuntu installations

~~~~
mkdir build
cd build
cmake ..
make
~~~~

* for quicker compilation (install ccache and ninja-build)

~~~~
mkdir build
cd build
cmake -G Ninja ..
ninja
~~~~

## Usage

Each analysis needs a dedicated `Analysis` class, a set of `Tagger` classess and a `main.cpp` file.
The `Analysis` class contains the global information of the analysis, such as file names, path names, variables names etc.
Every `Tagger` class tags or reconstructs one specific particle or signature. Each analysis needs at least one dedicated `Tagger`.
The `main.cpp` defines the order in which each `Tagger` is passed to the `Analysis`.

## Standard model

The acceptances for Standard model particles at a future 100 TeV collider are presented [here](doc/standard-model.md).
These plots represent some examples of the power of this code.

## Source code documentation

The source code documentation including all classes and functions can be found [here](http://boostedcollideranalysis.github.io/BoCA).

## License

BoCa is licenced under the [GPL 3](doc/License.md).

## Reference

Please cite:
* [Jan Hajer, Ying-Ying Li, Tao Liu, John F. H. Shiu: *Heavy Higgs Bosons at 14 TeV and 100 TeV*, April 2015](https://inspirehep.net/record/1365110)
* [Nathaniel Craig, Jan Hajer, Ying-Ying Li, Tao Liu, Hao Zhang: *Heavy Higgs Bosons at Low tan β: from the LHC to 100 TeV*, May 2016](https://inspirehep.net/record/1466130)

## Git commands

* initial download of the project `git clone git@github.com:BoostedColliderAnalysis/BoCA.git`
* downloading updates from the server `git pull`
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
* Classes and functions are written in CamelCase
* variables are written small_with_underscore
* member_variables_ and TemplateParamter_ end on an underscore
