set(IncludeDirectory
${IncludeDirectory}
${PROJECT_SOURCE_DIR}/source
)
include_directories(${IncludeDirectory})

HDictionary(HBranch HBranch.cpp ../include/HLinkDef.hh)

set(HObjectSources 
HObject.cpp 
HFourVector.cpp
)
HLibrary(HObject "${HObjectSources}")


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
HJetTag.cpp
)
HLibrary(HEvent "${EventSources}")

set(AnalysisSources
HAnalysis.cpp
# HAnalysisNew.cpp
HFile.cpp
HClonesArray.cpp
)
HLibrary(HAnalysis "${AnalysisSources}")

set(MvaSources
HMva.cpp
HFactory.cpp
HReader.cpp
)
HLibrary(HMva "${MvaSources}")

