HInclude(${PROJECT_SOURCE_DIR}/include)
HInclude(${PROJECT_SOURCE_DIR}/source)

add_subdirectory(exroot)
add_subdirectory(delphes)

HDictionary(Branches Branches.cpp ../include/LinkDef.hh)

set(VectorSources
Vector2.cpp
Vector3.cpp
LorentzVector.cpp
)
HLibrary(Vector VectorSources)

set(EventSources
Global.cpp
Debug.cpp
Predicate.cpp
File.cpp
ClonesArrays.cpp
Event.cpp
FourVector.cpp
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
HLibrary(Event EventSources)

set(MultipletSources
Identification.cpp
Multiplet.cpp
Singlet.cpp
Doublet.cpp
Triplet.cpp
Quartet.cpp
Quintet.cpp
Sextet.cpp
Octet62.cpp
GlobalObservables.cpp
MultipletEvent.cpp
)
HLibrary(Multiplets MultipletSources)

set(HepTaggerSource
TopHadronicHep.cpp
)
HLibrary(HepTagger HepTaggerSource)
add_dependencies(HepTagger HepTopTagger)

set(TaggerSources
Observable.cpp
PreCuts.cpp
Factory.cpp
Reader.cpp
Plot.cpp

Tagger.cpp
TauTagger.cpp
BottomTagger.cpp
BosonTagger.cpp
WHadronicTagger.cpp
WSemiTagger.cpp
ZHadronicTagger.cpp
HiggsTagger.cpp
TopHadronicTagger.cpp
TopSemiTagger.cpp
TopLeptonicTagger.cpp
JetPairTagger.cpp
TripletJetPairTagger.cpp
)
HLibrary(Tagger TaggerSources)

set(WimpSources
WimpMass.cpp
)
HLibrary(Wimp WimpSources)
add_dependencies(Wimp WimpMass)

set(AnalysisSources
Configuration.cpp
Analysis.cpp
AnalysisBase.cpp
Particle.cpp
Family.cpp
Constituent.cpp
JetTag.cpp
DetectorGeometry.cpp
JetInfo.cpp
Reconstruction.cpp
Discriminator.cpp
SubStructure.cpp
)
HLibrary(Analysis AnalysisSources)
