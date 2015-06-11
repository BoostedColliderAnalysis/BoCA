HInclude(${PROJECT_SOURCE_DIR}/source)
HInclude(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(exroot)
add_subdirectory(delphes)

HDictionary(Branches Branches.cpp ../include/LinkDef.hh)

set(EventSources
Global.cpp
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
HLibrary(Event "${EventSources}")

set(MultipletSources
Multiplet.cpp
Identification.cpp
Singlet.cpp
Doublet.cpp
Triplet.cpp
Quartet22.cpp
Quartet31.cpp
Quintet.cpp
Sextet.cpp
Octet62.cpp
)
HLibrary(Multiplets "${MultipletSources}")

set(HepTaggerSource
TopHadronicHep.cpp
)
HLibrary(HepTagger "${HepTaggerSource}")
add_dependencies(HepTagger HepTopTagger)

set(AnalysisSources
Configuration.cpp
Analysis.cpp
Family.cpp
Constituent.cpp
JetTag.cpp
JetInfo.cpp
Reconstruction.cpp
Discriminator.cpp
HiggsTagger.cpp
SubStructure.cpp

Tagger.cpp
Factory.cpp
Reader.cpp

WimpMass.cpp
BottomTagger.cpp
TauTagger.cpp
# DoubletTagger.cpp
ZHadronicTagger.cpp
WHadronicTagger.cpp
WSemiTagger.cpp
JetPairTagger.cpp
TripletJetPairTagger.cpp
TopHadronicTagger.cpp
TopLeptonicTagger.cpp
TopSemiTagger.cpp
)
HLibrary(Analysis "${AnalysisSources}")
add_dependencies(Analysis WimpMass)
