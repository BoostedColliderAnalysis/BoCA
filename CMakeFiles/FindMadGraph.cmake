
# set path to dependencies
set(MadGraphDir ~/Development/MadGraph)
set(ExRootDir ${MadGraphDir}/ExRootAnalysis)
set(DelphesDir ${MadGraphDir}/Delphes)

# find external libraries
find_library(
  ExRootLibrary
  NAMES ExRootAnalysis
  HINTS ${ExRootDir}/lib
)

find_library(
  DelphesLibrary
  NAMES Delphesset(LinkLibraries
  ${LIBCONFIGPP_LIBRARIES}
  ${ROOT_LIBRARIES}
  TMVA
  ${fastjet_LIBRARIES}
  ${DelphesLibrary}
  ${ExRootLibrary}
)

  HINTS ${DelphesDir}
)

set(Directory
#   ${ROOT_INCLUDE_DIR}
  ${ExRootDir}
  ${DelphesDir}
#   ${LIBCONFIG_INCLUDE_DIR}
)
HInclude("${Directory}" SYSTEM)

set(LinkLibraries
#   ${LIBCONFIGPP_LIBRARIES}
#   ${ROOT_LIBRARIES}
#   TMVA
#   ${fastjet_LIBRARIES}
  ${DelphesLibrary}
  ${ExRootLibrary}
)
