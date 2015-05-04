HInclude(${PROJECT_SOURCE_DIR}/source)
# HInclude(".")

HDictionary(HBranch HBranch.cpp ../include/HLinkDef.hh)

set(EventSources
HObject.cpp
HFourVector.cpp
HFile.cpp
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
HDoublet.cpp
HTriplet.cpp
HQuartet.cpp
HQuartet31.cpp
HSextet.cpp
)
HLibrary(HContainer "${WrapperSources}" PARENT_SCOPE)



set(HepTaggerSource
HTopTagger.cpp
)
HLibrary(HepTagger "${HepTaggerSource}" PARENT_SCOPE)
add_dependencies(HepTagger HepTopTagger)

set(AnalysisSources
HAnalysis.cpp
HJetTag.cpp
HJetInfo.cpp
HReconstruction.cpp
HDiscriminator.cpp
HHiggsTagger.cpp
# HTopTagger.cpp
# HEPTopTagger.cpp
# HSuperStructure.cpp
HSubStructure.cpp

HMva.cpp
HFactory.cpp
HReader.cpp

HBottomTagger.cpp
HTauTagger.cpp
HWTagger.cpp
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
