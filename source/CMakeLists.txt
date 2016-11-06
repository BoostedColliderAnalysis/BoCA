#
# Copyright (C) 2015-2016 Jan Hajer
#
add_subdirectory(branch)
add_subdirectory(generic)
add_subdirectory(units)
add_subdirectory(math)
add_subdirectory(identification)
add_subdirectory(fastjet)
add_subdirectory(event)
add_subdirectory(multiplets)
add_subdirectory(multivariant)
add_subdirectory(latex)
add_subdirectory(io)
add_subdirectory(plotting)
add_subdirectory(tagger)
add_subdirectory(analysis)

set(boca_sources
Settings.cpp
WimpMass.cpp
)
create_library(Boca boca_sources)
