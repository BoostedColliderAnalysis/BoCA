
# set path to dependencies
set(MadGraphDir ~/madness/MadGraph) # Ying Ying
# set(MadGraphDir ~/Development/MadGraph) # Jan
set(ExRootDir ${MadGraphDir}/ExRootAnalysis)
set(DelphesDir ${MadGraphDir}/Delphes)

find_library(
  ExRootLibrary
  NAMES ExRootAnalysis
#   HINTS ${ExRootDir}/lib # Jan
  HINTS ${ExRootDir} # Ying Ying
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
