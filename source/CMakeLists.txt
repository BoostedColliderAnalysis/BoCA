# HObject Library
set(HObjectSources HObject.cpp HConstants.cpp)
add_library(HObject SHARED ${HObjectSources} )
target_link_libraries(HObject ${LinkLibraries})
set_target_properties(HObject PROPERTIES ${LibraryProperties})
install(TARGETS HObject DESTINATION ${LibraryDestination})

# HEvent Library
set(EventSources
HEvent.cpp
HParticle.cpp
HJet.cpp
HLepton.cpp
HTopTagger.cpp
HDiscriminator.cpp
HHiggsTagger.cpp
HEPTopTagger.cpp
HPull.cpp
)

set(HEventLinkLibraries
${LinkLibraries}
${fastjet_LIBRARIES} 
${DelphesLibrary}
HObject 
)
set(EventSources ${EventSources} ${HDictionarySource}) 
add_library(HEvent SHARED ${EventSources} )
target_link_libraries (HEvent ${HEventLinkLibraries})
set_target_properties(HEvent PROPERTIES ${LibraryProperties})
install(TARGETS HEvent DESTINATION ${LibraryDestination})

# HAnalysisBase Library
set(AnalysisBaseSources
HAnalysisBase.cpp
HFile.cpp
HClonesArray.cpp
)

set(HAnalysisBaseLinkLibraries
${LinkLibraries}
${ExRootLibrary}
HObject
HEvent 
)
set(AnalysisBaseSources ${AnalysisBaseSources} ${HDictionarySource}) 
add_library(HAnalysisBase SHARED ${AnalysisBaseSources})
target_link_libraries (HAnalysisBase ${HAnalysisBaseLinkLibraries})
set_target_properties(HAnalysisBase PROPERTIES ${LibraryProperties})
install(TARGETS HAnalysisBase DESTINATION ${LibraryDestination})

# HMva Library
# set(MvaBaseSources
# HMvaBase.cpp
# HFactory.cpp
# HReader.cpp
# )
# 
# set(HMvaBaseLinkLibraries
# ${LinkLibraries}
# ${ExRootLibrary}
# HObject
# )
# set(MvaBaseSources ${MvaBaseSources} ${HDictionarySource}) 
# add_library(HMvaBase SHARED ${MvaBaseSources})
# target_link_libraries (HMvaBase ${HMvaBaseLinkLibraries})
# set_target_properties(HMvaBase PROPERTIES ${LibraryProperties})
# install(TARGETS HMvaBase DESTINATION ${LibraryDestination})