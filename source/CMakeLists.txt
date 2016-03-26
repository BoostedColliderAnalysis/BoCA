#
# Copyright (C) 2015-2016 Jan Hajer
#
add_subdirectory(exroot)
add_subdirectory(delphes)
add_subdirectory(physics)
create_dictionary(Colors Colors.cpp ../include/LinkDef.hh)
add_subdirectory(plotting)

add_include_path(../include)
create_dictionary(Branches Branches.cpp ../include/LinkDef.hh)
create_dictionary(Names Names.cpp ../include/LinkDef.hh)

set(vector_sources
EventShapes.cpp
EventShapesOld.cpp
HemisphereMasses.cpp
PseudoJet.cpp
Jet.cpp
Particle.cpp
ClusterSequence.cpp
)
create_library(Vector vector_sources)


add_subdirectory(multiplets)

set(global_sources
Debug.cpp
Types.cpp
Particles.cpp
Exception.cpp
Options.cpp
)
create_library(Global global_sources)

set(event_sources
File.cpp
TreeReader.cpp
Event.cpp
Isolation.cpp
FourVector.cpp
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
create_library(Event event_sources)

set(multiplet_sources
Identification.cpp
GlobalObservables.cpp
GlobalTagger.cpp
# EventTagger.cpp
)
create_library(Multiplets2 multiplet_sources)

set(tagger_sources
Tagger.cpp
ReaderBase.cpp
Phase.cpp
Files.cpp
Observable.cpp
Observables.cpp
MomentumRange.cpp
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
# Configuration.cpp
AnalysisBase.cpp
Member.cpp
Family.cpp
Constituent.cpp
SubJettiness.cpp
DetectorGeometry.cpp
JetInfo.cpp
ParticleInfo.cpp
InfoRecombiner.cpp
# JetInfoFamily.cpp
)
create_library(Analysis analysis_sources)

add_executable(root-browser Browser.cpp)
target_link_libraries(root-browser ${ROOT_LIBRARIES})
install (TARGETS root-browser DESTINATION ~/.bin)
