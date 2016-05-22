#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(..)

add_executable(root-browser Browser.cpp)
target_link_libraries(root-browser ${ROOT_LIBRARIES})
install (TARGETS root-browser DESTINATION "$ENV{HOME}/.bin")

add_subdirectory(fastjet)
add_subdirectory(generic)
add_subdirectory(latex)
add_subdirectory(physics)
add_subdirectory(math)
add_subdirectory(external)
add_subdirectory(exroot)
add_subdirectory(io)
add_subdirectory(delphes)
add_subdirectory(multiplets)
add_subdirectory(multivariant)

create_dictionary(Colors Colors.cpp Colors.hh LinkDef.hh)
add_subdirectory(plotting)

create_dictionary(Branches Branches.cpp Branches.hh LinkDef.hh)

set(shape_sources
HemisphereMasses.cpp
EventShapes.cpp
Names.cpp
)
create_library(EventShapes shape_sources)

set(event_sources
Event.cpp
)
create_library(Event event_sources)

set(analysis_sources
MomentumRange.cpp
Observable.cpp
Observables.cpp
PreCuts.cpp
Constituent.cpp
Settings.cpp
WimpMass.cpp
)
create_library(Analysis analysis_sources)

set(tagger_sources
GlobalObservables.cpp
GlobalTagger.cpp
File.cpp
Tagger.cpp
AnalysisBase.cpp
)
create_library(Tagger tagger_sources)

add_subdirectory(standardmodel)
