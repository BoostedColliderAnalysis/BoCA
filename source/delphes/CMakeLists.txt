#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/delphes)

set(DelphesFactorySources
DelphesFactory.cc
)
create_library(DelphesFactory DelphesFactorySources)

create_dictionary(Delphes DelphesClasses.cc ../../include/delphes/ClassesLinkDef.h delphes)

set(EventDelphesSources
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
create_library(EventDelphes EventDelphesSources)
