#
# Copyright (C) 2015 Jan Hajer
#
add_subdirectory(exroot)
add_subdirectory(delphes)

add_include_path(../include)
create_dictionary(Branches Branches.cpp ../include/LinkDef.hh)

set(vector_sources
Vector2.cpp
Vector3.cpp
LorentzVector.cpp
EventShapes.cpp
EventShape.cpp
)
create_library(Vector vector_sources)

set(global_sources
Particles.cpp
Debug.cpp
Types.cpp
Vector.cpp
Math.cpp
Units.cpp
)
create_library(Global global_sources)

set(event_sources
File.cpp
ClonesArrays.cpp
Event.cpp
FourVector.cpp
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
create_library(Event event_sources)

set(multiplet_sources
Multiplet.cpp
Identification.cpp
Singlet.cpp
Doublet.cpp
Triplet.cpp
Quartet.cpp
Quintet.cpp
Sextet.cpp
Octet.cpp
GlobalObservables.cpp
)
create_library(Multiplets multiplet_sources)

set(hep_tagger_source
TopHadronicHep.cpp
)
create_library(HepTagger hep_tagger_source)
add_dependencies(HepTagger HepTopTagger)

set(tagger_sources
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
Observable.cpp
PreCuts.cpp
Trainer.cpp
)
create_library(Tagger tagger_sources)

set(wimp_sources
WimpMass.cpp
)
create_library(Wimp wimp_sources)
add_dependencies(Wimp WimpMass)

set(analysis_sources
Configuration.cpp
AnalysisBase.cpp
Trees.cpp
Particle.cpp
Family.cpp
Constituent.cpp
JetTag.cpp
DetectorGeometry.cpp
JetInfo.cpp
ParticleInfo.cpp
InfoRecombiner.cpp
JetInfoFamily.cpp
Reconstruction.cpp
Discriminator.cpp
Plotting.cpp
Result.cpp
)
create_library(Analysis analysis_sources)

