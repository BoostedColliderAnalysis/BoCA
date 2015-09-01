#
# Copyright (C) 2015 Jan Hajer
#
add_include_path(../../include/)
set(EventDelphesSources
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
create_library(EventDelphes EventDelphesSources)
