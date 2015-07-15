
# set path to dependencies

# set(MadGraphDir ~/madness/MadGraph) # Ying Ying
set(MadGraphDir ~/Development/MadGraph) # Jan

set(ExRootDir ${MadGraphDir}/ExRootAnalysis)
set(DelphesDir ${MadGraphDir}/Delphes)

find_library(
  ExRootLibrary
  NAMES ExRootAnalysis
#   HINTS ${ExRootDir}/lib # old
  HINTS ${ExRootDir} # new
)
add_include_path(${ExRootDir} SYSTEM)
add_libraries(${ExRootLibrary})

find_library(
  DelphesLibrary
  NAMES Delphes
  HINTS ${DelphesDir}
)
add_include_path(${DelphesDir} SYSTEM)
add_libraries(${DelphesLibrary})
