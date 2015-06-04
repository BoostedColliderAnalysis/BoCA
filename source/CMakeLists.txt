HInclude(${PROJECT_SOURCE_DIR}/source)
HInclude(${PROJECT_SOURCE_DIR}/include)

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
Quintet.cpp
Sextet.cpp
)
HLibrary(Multiplets "${MultipletSources}" PARENT_SCOPE)

set(HepTaggerSource
TopHadronicHep.cpp
)
HLibrary(HepTagger "${HepTaggerSource}" PARENT_SCOPE)
add_dependencies(HepTagger HepTopTagger)

set(AnalysisSources
Configuration.cpp
Analysis.cpp
Family.cpp
Constituent.cpp
JetTag.cpp
JetInfo.cpp
HReconstruction.cpp
HDiscriminator.cpp
HiggsTagger.cpp
HSubStructure.cpp

Tagger.cpp
Factory.cpp
Reader.cpp

BottomTagger.cpp
TauTagger.cpp
ZHadronicTagger.cpp
WHadronicTagger.cpp
WSemiTagger.cpp
JetPairTagger.cpp
TripletJetPairTagger.cpp
TopHadronicTagger.cpp
TopLeptonicTagger.cpp
TopSemiTagger.cpp
HeavyHiggsLeptonicTagger.cpp
HeavyHiggsSemiTagger.cpp
HHeavyHiggsTauTagger.cpp
ChargedHiggsSemiTagger.cpp
ChargedHiggsLeptonicTagger.cpp
)
HLibrary(Analysis "${AnalysisSources}" PARENT_SCOPE)
add_dependencies(Analysis HWimpMass)
