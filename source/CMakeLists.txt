#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(${PROJECT_SOURCE_DIR})

add_subdirectory(generic)
add_subdirectory(fastjet)
add_subdirectory(latex)
add_subdirectory(physics)
add_subdirectory(math)
add_subdirectory(external)
add_subdirectory(exroot)
add_subdirectory(io)
add_subdirectory(delphes)
add_subdirectory(multiplets)
add_subdirectory(multivariant)
add_subdirectory(analysis)
add_subdirectory(branch)
add_subdirectory(tagger)

create_dictionary(Colors Colors.cpp Colors.hh LinkDef.hh boca)
add_subdirectory(plotting)

set(boca_sources
Names.cpp
Tag.cpp
Names.cpp
MomentumRange.cpp
PreCuts.cpp
Settings.cpp
Constituent.cpp
Observable.cpp
Observables.cpp
HemisphereMasses.cpp
EventShapes.cpp
Event.cpp
WimpMass.cpp
FileInfo.cpp
)
create_library(Boca boca_sources)
