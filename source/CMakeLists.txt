# HObject Library
set(HObjectSources HObject.cpp )
add_library(HObject SHARED ${HObjectSources} )
target_link_libraries(HObject ${LinkLibraries})
set_target_properties(HObject PROPERTIES ${LibraryProperties})
install(TARGETS HObject DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})

# HEvent Library
set(EventSources
# HEvent.cpp
HEventBase.cpp
HEventDelphes.cpp
# HParticle.cpp
HParticleBase.cpp
HParticleDelphes.cpp
HParticleParton.cpp
HJet.cpp
# HLepton.cpp
HLeptonBase.cpp
HLeptonDelphes.cpp
HLeptonPgs.cpp
HTopTagger.cpp
HDiscriminator.cpp
HHiggsTagger.cpp
HEPTopTagger.cpp
HPull.cpp
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
install(TARGETS HEvent DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})

# HAnalysisBase Library
set(AnalysisBaseSources
HAnalysisBase.cpp
HFile.cpp
HClonesArray.cpp
)

set(HAnalysisBaseLinkLibraries
${ExRootLibrary}
HObject
HEvent 
)
set(AnalysisBaseSources ${AnalysisBaseSources}) 
add_library(HAnalysisBase SHARED ${AnalysisBaseSources})
target_link_libraries (HAnalysisBase ${HAnalysisBaseLinkLibraries})
set_target_properties(HAnalysisBase PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisBase DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})

# HMva Library
set(MvaBaseSources
HMvaBase.cpp
HFactory.cpp
HReader.cpp
)

set(HMvaBaseLinkLibraries
TMVA
${ExRootLibrary}
HObject
HBranch
)
set(MvaBaseSources ${MvaBaseSources}) 
add_library(HMvaBase SHARED ${MvaBaseSources})
target_link_libraries (HMvaBase ${HMvaBaseLinkLibraries})
set_target_properties(HMvaBase PROPERTIES ${LibraryProperties})
install(TARGETS HMvaBase DESTINATION ${LIBRARY_OUTPUT_DIRECTORY})