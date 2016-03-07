#
# Copyright (C) 2015 Jan Hajer
#

# set path to madgraph folder
set(
  MadGraphDir
  ~/Development/madgraph
  ~/madness/MadGraph
  ~/HEP/MadGraph5_v1_5_14
)

find_path(
  ExRootDir
  NAMES ExRootAnalysis/ExRootClasses.h
  PATHS ${MadGraphDir}
  PATH_SUFFIXES ExRootAnalysis
  DOC "Path to ExRoot installed by MadGraph"
)
add_include_path(${ExRootDir} SYSTEM)

find_library(
  ExRootLibrary
  NAMES ExRootAnalysis
  HINTS ${ExRootDir}
  DOC "ExRoot library installed by MadGraph"
)
add_libraries(${ExRootLibrary})

# find_path(
#   DelphesDir
#   NAMES classes/DelphesClasses.h
#   PATHS ${MadGraphDir}
#   PATH_SUFFIXES Delphes
#   DOC "Path to Delphes installed by MadGraph"
# )
# add_include_path(${DelphesDir} SYSTEM)
#
# find_library(
#   DelphesLibrary
#   NAMES DelphesNoFastJet
#   HINTS ${DelphesDir}
#   DOC "Delphes library installed by MadGraph"
# )
# add_libraries(${DelphesLibrary})
