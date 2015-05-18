HInclude(${PROJECT_SOURCE_DIR}/source)
# HInclude(".")

HDictionary(Branch Branch.cpp ../include/HLinkDef.hh)

set(EventSources
Object.cpp
FourVector.cpp
File.cpp
ClonesArrays.cpp
Event.cpp
Partons.cpp
Leptons.cpp
Hadrons.cpp
Predicate.cpp
)
HLibrary(HEvent "${EventSources}" PARENT_SCOPE)

set(PartonEventSources
# HEventParton.cpp
HParticleParton.cpp
# HFileParton.cpp
)
HLibrary(HPartonEvent "${PartonEventSources}" PARENT_SCOPE)

set(PgsEventSources
# HFilePgs.cpp
# HEventPgs.cpp
HLeptonPgs.cpp
HJetPgs.cpp
)
HLibrary(HPgsEvent "${PgsEventSources}" PARENT_SCOPE)

set(DelphesEventSources
# HFileDelphes.cpp
# HEventDelphes.cpp
HParticleDelphes.cpp
HLeptonDelphes.cpp
HJetDelphes.cpp
)
HLibrary(HDelphesEvent "${DelphesEventSources}" PARENT_SCOPE)



set(WrapperSources
HTag.cpp
# HTagPrivate.cpp
Singlet.cpp
Doublet.cpp
Triplet.cpp
HQuartet.cpp
HQuartet31.cpp
HSextet.cpp
)
HLibrary(HContainer "${WrapperSources}" PARENT_SCOPE)



set(HepTaggerSource
TopHadronicHep.cpp
)
HLibrary(HepTagger "${HepTaggerSource}" PARENT_SCOPE)
add_dependencies(HepTagger HepTopTagger)

set(AnalysisSources
Analysis.cpp
Family.cpp
Constituent.cpp
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
Reader.cpp

BottomTagger.cpp
HTauTagger.cpp
WHadronicTagger.cpp
HWSemiTagger.cpp
HJetPairTagger.cpp
HChargedJetPairTagger.cpp
TopHadronicTagger.cpp
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
