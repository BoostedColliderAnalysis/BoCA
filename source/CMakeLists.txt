HInclude(${PROJECT_SOURCE_DIR}/source)

add_subdirectory(exroot)
add_subdirectory(delphes)

HDictionary(Branches Branches.cpp ../include/LinkDef.hh)

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
HLibrary(Event "${EventSources}" PARENT_SCOPE)

set(MultipletSources
Identification.cpp
Singlet.cpp
Doublet.cpp
Triplet.cpp
Quartet22.cpp
Quartet31.cpp
Sextet.cpp
)
HLibrary(Multiplets "${MultipletSources}" PARENT_SCOPE)

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
HSubStructure.cpp

Tagger.cpp
Factory.cpp
Reader.cpp

BottomTagger.cpp
TauTagger.cpp
ZHadronicTagger.cpp
WHadronicTagger.cpp
WSemiTagger.cpp
HJetPairTagger.cpp
HChargedJetPairTagger.cpp
TopHadronicTagger.cpp
HTopLeptonicTagger.cpp
TopSemiTagger.cpp
HMvaHiggsTagger.cpp
HHeavyHiggsLeptonicTagger.cpp
HHeavyHiggsHadronicTagger.cpp
HHeavyHiggsSemiTagger.cpp
HHeavyHiggsTauTagger.cpp
HChargedHiggsSemiTagger.cpp
HChargedHiggsHadronicTagger.cpp
HChargedHiggsLeptonicTagger.cpp
)
HLibrary(Analysis "${AnalysisSources}" PARENT_SCOPE)
add_dependencies(Analysis HWimpMass)
