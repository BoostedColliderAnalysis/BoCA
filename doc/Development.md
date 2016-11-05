# Development

## Git commands

* initial download of the project [`git clone git@github.com:BoostedColliderAnalysis/BoCA.git`](git@github.com:BoostedColliderAnalysis/BoCA.git)
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
* Classes and Functions are written in CamelCase
* variables are written small_with_underscore
* member_variables_ and TemplateParamter_ end on an underscore

## Dynamic program analysis with [`Valgrind`](http://valgrind.org/)

[`Valgrind`](http://valgrind.org/) is a framework for dynamic program analysis.
The most usefull tools are

* The callgraph generator [`Callgrind`](http://valgrind.org/docs/manual/cl-manual.html).

  Which can be called via

      valgrind --tool=callgrind program

  The output file can be analysed with [`KCachegrind`](https://kcachegrind.github.io/html/Home.html).
  In order to dump intermediate results call

      callgrind_control -d

* The memory error detector [`Memcheck`](http://valgrind.org/docs/manual/mc-manual.html).

  Which can be called via

      valgrind --suppressions=$ROOTSYS/etc/valgrind-root.supp program

  The suppression file suppresses false positive hits from [`ROOT`](https://root.cern.ch/).
  The output can be analysed with [`Valkyrie`](http://valgrind.org/downloads/guis.html).
