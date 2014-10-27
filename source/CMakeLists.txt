HInclude(${PROJECT_SOURCE_DIR}/source)
# HInclude(".")

HDictionary(HBranch HBranch.cpp ../include/HLinkDef.hh)

set(HObjectSources
HObject.cpp
HFourVector.cpp
)
HLibrary(HObject "${HObjectSources}" PARENT_SCOPE)

set(EventSources
HJetTag.cpp
HEvent.cpp
HEventDelphes.cpp
HEventParton.cpp
HEventPgs.cpp
HParticle.cpp
HParticleDelphes.cpp
HParticleParton.cpp
HJetInfo.cpp
HJet.cpp
HJetDelphes.cpp
HJetPgs.cpp
HLepton.cpp
HLeptonDelphes.cpp
HLeptonPgs.cpp
HReconstruction.cpp
HDiscriminator.cpp
HHiggsTagger.cpp
HTopTagger.cpp
HEPTopTagger.cpp
HPull.cpp
HSubStructure.cpp
)
HLibrary(HEvent "${EventSources}" PARENT_SCOPE)

set(AnalysisSources
HClonesArray.cpp
HFile.cpp
HAnalysis.cpp
# HAnalysisNew.cpp
)
HLibrary(hanalysis "${AnalysisSources}" PARENT_SCOPE)

set(MvaSources
HMva.cpp
HFactory.cpp
HReader.cpp
)
HLibrary(HMva "${MvaSources}" PARENT_SCOPE)

