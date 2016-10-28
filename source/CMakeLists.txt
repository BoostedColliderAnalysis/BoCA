#
# Copyright (C) 2015-2016 Jan Hajer
#
add_subdirectory(generic)
add_subdirectory(units)
add_subdirectory(exroot)
add_subdirectory(delphes)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(fastjet)
add_subdirectory(multivariant)
add_subdirectory(branch)
add_subdirectory(latex)
add_subdirectory(io)
add_subdirectory(multiplets)
add_subdirectory(plotting)
add_subdirectory(tagger)
add_subdirectory(analysis)

set(boca_sources
Names.cpp
Tag.cpp
Names.cpp
PreCuts.cpp
Settings.cpp
HemisphereMasses.cpp
EventShapes.cpp
Event.cpp
WimpMass.cpp
FileInfo.cpp
)
create_library(Boca boca_sources)
