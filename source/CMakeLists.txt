# generate dictionary
# set(HBranchSources HBranch.cpp)
# set(HLinkDefHeader ../include/HLinkDef.hh)
# set(HDictionarySource HBranchDict.cpp)
# set(IncludeDirectory ${IncludeDirectory} ${PROJECT_SOURCE_DIR}/source)
# ROOT_GENERATE_DICTIONARY("${HBranchSources}" "${HLinkDefHeader}" "${HDictionarySource}" "${IncludeDirectory}")

# generate library
# set(HBranchSources ${HDictionarySource})
# add_library(HBranch SHARED ${HBranchSources})
# target_link_libraries(HBranch ${LinkLibraries})
# set_target_properties(HBranch PROPERTIES ${LibraryProperties})
# install(TARGETS HBranch DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})


# HObject Library
set(HObjectSources HObject.cpp HFourVector.cpp
)
add_library(HObject SHARED ${HObjectSources} )
target_link_libraries(HObject ${LinkLibraries})
set_target_properties(HObject PROPERTIES ${LibraryProperties})
install(TARGETS HObject DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# HEvent Library
set(EventSources
HEvent.cpp
HEventDelphes.cpp
HEventParton.cpp
HEventPgs.cpp
HParticle.cpp
HParticleDelphes.cpp
HParticleParton.cpp
HJet.cpp
HJetDelphes.cpp
HJetPgs.cpp
HLepton.cpp
HLeptonDelphes.cpp
HLeptonPgs.cpp
HReconstruction.cpp
HTopTagger.cpp
HDiscriminator.cpp
HHiggsTagger.cpp
HEPTopTagger.cpp
HPull.cpp
HJetInfo.cpp
)

set(HEventLinkLibraries
${fastjet_LIBRARIES}
${DelphesLibrary}
HObject
)
set(EventSources ${EventSources})
add_library(HEvent SHARED ${EventSources} )
target_link_libraries (HEvent ${HEventLinkLibraries})
set_target_properties(HEvent PROPERTIES ${LibraryProperties})
install(TARGETS HEvent DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# HAnalysis Library
set(AnalysisSources
HAnalysis.cpp
# HAnalysisNew.cpp
HFile.cpp
HClonesArray.cpp
)

set(HAnalysisLinkLibraries
${ExRootLibrary}
HObject
HEvent
)
set(AnalysisSources ${AnalysisSources})
add_library(HAnalysis SHARED ${AnalysisSources})
target_link_libraries (HAnalysis ${HAnalysisLinkLibraries})
set_target_properties(HAnalysis PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysis DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# HMva Library
set(MvaSources
HMva.cpp
HFactory.cpp
HReader.cpp
)

set(HMvaLinkLibraries
TMVA
${ExRootLibrary}
HObject
HBranch
)
set(MvaSources ${MvaSources})
add_library(HMva SHARED ${MvaSources})
target_link_libraries (HMva ${HMvaLinkLibraries})
set_target_properties(HMva PROPERTIES ${LibraryProperties})
install(TARGETS HMva DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
