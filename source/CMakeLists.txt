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
HEventDelphes.cpp
HEventParton.cpp
HEventPgs.cpp
HEvent.cpp
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
HSuperStructure.cpp
HSubStructure.cpp
HBottomTagger.cpp
HLeptonicTopTagger.cpp
HMvaHiggsTagger.cpp
HHeavyHiggsTagger.cpp
HPair.cpp
HJetLeptonPair.cpp
HPairPair.cpp
HTag.cpp
HHadronicWTagger.cpp
HPairJetPair.cpp
HHadronicTopTagger.cpp
)
HLibrary(HEvent "${EventSources}" PARENT_SCOPE)

set(AnalysisSources
HClonesArray.cpp
HFile.cpp
HFileParton.cpp
HFilePgs.cpp
HFileDelphes.cpp
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

