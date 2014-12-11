HInclude(${PROJECT_SOURCE_DIR}/source)
# HInclude(".")

HDictionary(HBranch HBranch.cpp ../include/HLinkDef.hh)

set(EventSources
HObject.cpp
HFourVector.cpp
HFile.cpp
HClonesArray.cpp
HEvent.cpp
HParticle.cpp
HLepton.cpp
HJet.cpp
)
HLibrary(HEvent "${EventSources}" PARENT_SCOPE)

set(PartonEventSources
HEventParton.cpp
HParticleParton.cpp
HFileParton.cpp
)
HLibrary(HPartonEvent "${PartonEventSources}" PARENT_SCOPE)

set(PgsEventSources
HFilePgs.cpp
HEventPgs.cpp
HLeptonPgs.cpp
HJetPgs.cpp
)
HLibrary(HPgsEvent "${PgsEventSources}" PARENT_SCOPE)

set(DelphesEventSources
HFileDelphes.cpp
HEventDelphes.cpp
HParticleDelphes.cpp
HLeptonDelphes.cpp
HJetDelphes.cpp
)
HLibrary(HDelphesEvent "${DelphesEventSources}" PARENT_SCOPE)



set(WrapperSources
HPair.cpp
HJetLeptonPair.cpp
HPairPair.cpp
HTag.cpp
HPairJetPair.cpp
HTriple.cpp
HTriplePair.cpp
)
HLibrary(HContainer "${WrapperSources}" PARENT_SCOPE)



set(HepTaggerSource
HTopTagger.cpp
)
HLibrary(HepTagger "${HepTaggerSource}" PARENT_SCOPE)

set(AnalysisSources
HAnalysis.cpp
HJetTag.cpp
HJetInfo.cpp
HReconstruction.cpp
HDiscriminator.cpp
HHiggsTagger.cpp
# HTopTagger.cpp
# HEPTopTagger.cpp
HSuperStructure.cpp
HSubStructure.cpp

HMva.cpp
HFactory.cpp
HReader.cpp

HBottomTagger.cpp
HTopLeptonicTagger.cpp
HLeptonicTopTagger.cpp
HMvaHiggsTagger.cpp
HHeavyHiggsLeptonicTagger.cpp
HHeavyHiggsHadronicTagger.cpp
HHeavyHiggsMixedTagger.cpp
HWTagger.cpp
HHadronicTopTagger.cpp

# Wrapper.cpp
# topology22.cpp
)
HLibrary(HAnalysis "${AnalysisSources}" PARENT_SCOPE)
