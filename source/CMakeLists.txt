#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../include)

add_subdirectory(generic)
add_subdirectory(io)
add_subdirectory(physics)
add_subdirectory(math)
add_subdirectory(external)
add_subdirectory(exroot)
add_subdirectory(delphes)
add_subdirectory(multiplets)

create_dictionary(Colors Colors.cpp Colors.hh LinkDef.hh)
add_subdirectory(plotting)

create_dictionary(Branches Branches.cpp Branches.hh LinkDef.hh)
create_dictionary(Names Names.cpp Names.hh LinkDef.hh)

set(fastjet_sources
ClusterSequence.cpp
SubJettiness.cpp
InfoRecombiner.cpp
HemisphereMasses.cpp
EventShapes.cpp
)
create_library(FastJet fastjet_sources)

set(event_sources
Event.cpp
FourVector.cpp
Hadrons.cpp
Partons.cpp
Leptons.cpp
Isolation.cpp
)
create_library(Event event_sources)

set(analysis_sources
MomentumRange.cpp
Phase.cpp
Observable.cpp
Observables.cpp
PreCuts.cpp
Constituent.cpp
DetectorGeometry.cpp
WimpMass.cpp
)
create_library(Analysis analysis_sources)

set(tagger_sources
GlobalObservables.cpp
GlobalTagger.cpp
File.cpp
Tagger.cpp
AnalysisBase.cpp
Trainer.cpp
)
create_library(Tagger tagger_sources)

add_executable(root-browser Browser.cpp)
target_link_libraries(root-browser ${ROOT_LIBRARIES})
install (TARGETS root-browser DESTINATION ~/.bin)
