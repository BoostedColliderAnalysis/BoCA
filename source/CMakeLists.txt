#
# Copyright (C) 2015-2016 Jan Hajer
#
add_subdirectory(external)
add_subdirectory(generic)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(exroot)
add_subdirectory(delphes)

create_dictionary(Colors Colors.cpp ../include/LinkDef.hh)
add_subdirectory(plotting)

add_include_path(../include)
create_dictionary(Branches Branches.cpp ../include/LinkDef.hh)
create_dictionary(Names Names.cpp ../include/LinkDef.hh)

set(vector_sources
EventShapes.cpp
HemisphereMasses.cpp
ClusterSequence.cpp
)
create_library(Vector vector_sources)


add_subdirectory(multiplets)

set(event_sources
File.cpp
TreeReader.cpp
Event.cpp
FourVector.cpp
Hadrons.cpp
Partons.cpp
Leptons.cpp
Isolation.cpp
)
create_library(Event event_sources)

set(multiplet_sources
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

set(analysis_sources
# Configuration.cpp
AnalysisBase.cpp
Constituent.cpp
SubJettiness.cpp
DetectorGeometry.cpp
InfoRecombiner.cpp
WimpMass.cpp
# JetInfoFamily.cpp
)
create_library(Analysis analysis_sources)

add_executable(root-browser Browser.cpp)
target_link_libraries(root-browser ${ROOT_LIBRARIES})
install (TARGETS root-browser DESTINATION ~/.bin)
