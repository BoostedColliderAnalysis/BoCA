HInclude(${PROJECT_SOURCE_DIR}/source)
# HInclude(".")

HDictionary(Branch Branch.cpp ../include/HLinkDef.hh)

set(EventSources
HObject.cpp
HFourVector.cpp
RootFile.cpp
ClonesArrays.cpp
HEvent.cpp
HParticle.cpp
HLepton.cpp
HJet.cpp
Predicate.cpp
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
HTag.cpp
HTagPrivate.cpp
Singlet.cpp
Doublet.cpp
Triplet.cpp
HQuartet.cpp
HQuartet31.cpp
HSextet.cpp
)
HLibrary(HContainer "${WrapperSources}" PARENT_SCOPE)



set(HepTaggerSource
TopHadronicTagger.cpp
)
HLibrary(HepTagger "${HepTaggerSource}" PARENT_SCOPE)
add_dependencies(HepTagger HepTopTagger)

set(AnalysisSources
HAnalysis.cpp
HJetTag.cpp
JetInfo.cpp
HReconstruction.cpp
HDiscriminator.cpp
HHiggsTagger.cpp
# HTopTagger.cpp
# HEPTopTagger.cpp
# HSuperStructure.cpp
HSubStructure.cpp

Tagger.cpp
Factory.cpp
HReader.cpp

BottomTagger.cpp
HTauTagger.cpp
HWHadronicTagger.cpp
HWSemiTagger.cpp
HJetPairTagger.cpp
HChargedJetPairTagger.cpp
HTopHadronicTagger.cpp
HTopLeptonicTagger.cpp
HTopSemiTagger.cpp
HMvaHiggsTagger.cpp
HHeavyHiggsLeptonicTagger.cpp
HHeavyHiggsHadronicTagger.cpp
HHeavyHiggsSemiTagger.cpp
HHeavyHiggsTauTagger.cpp
HChargedHiggsSemiTagger.cpp
HChargedHiggsHadronicTagger.cpp
HChargedHiggsLeptonicTagger.cpp

# Wrapper.cpp
# topology22.cpp
)
HLibrary(HAnalysis "${AnalysisSources}" PARENT_SCOPE)
add_dependencies(HAnalysis HWimpMass)
