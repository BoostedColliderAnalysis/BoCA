add_subdirectory(exroot)
add_subdirectory(delphes)

add_include_path(../include)
create_dictionary(Branches ./Branches.cpp ../include/LinkDef.hh)

set(VectorSources
Vector3.cpp
LorentzVector.cpp
)
create_library(Vector VectorSources)

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
create_library(Event EventSources)

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
create_library(Multiplets MultipletSources)

set(HepTaggerSource
TopHadronicHep.cpp
)
create_library(HepTagger HepTaggerSource)
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
WLeptonicTagger.cpp
ZHadronicTagger.cpp
HiggsTagger.cpp
TopHadronicTagger.cpp
TopLeptonicTagger.cpp
JetPairTagger.cpp
TripletJetPairTagger.cpp
)
create_library(Tagger TaggerSources)

set(WimpSources
WimpMass.cpp
)
create_library(Wimp WimpSources)
add_dependencies(Wimp WimpMass)

set(AnalysisSources
Configuration.cpp
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
create_library(Analysis AnalysisSources)
