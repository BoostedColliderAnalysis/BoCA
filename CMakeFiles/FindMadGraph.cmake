
# set path to dependencies
set(MadGraphDir ~/Development/MadGraph)
set(ExRootDir ${MadGraphDir}/ExRootAnalysis)
set(DelphesDir ${MadGraphDir}/Delphes)

find_library(
  ExRootLibrary
  NAMES ExRootAnalysis
  HINTS ${ExRootDir}/lib
)
HInclude(${ExRootDir} SYSTEM)
HLinkLibraries(${ExRootLibrary})

find_library(
  DelphesLibrary
  NAMES Delphes
  HINTS ${DelphesDir}
)
HInclude(${DelphesDir} SYSTEM)
HLinkLibraries(${DelphesLibrary})
