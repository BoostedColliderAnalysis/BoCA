#
# Copyright (C) 2015-2016 Jan Hajer
#
set(DelphesFactorySources
DelphesFactory.cc
)
create_library(DelphesFactory DelphesFactorySources)

create_dictionary(Delphes DelphesClasses.cc DelphesClasses.h LinkDef.hh boca delphes)

set(EventDelphesSources
# Partons.cpp
# Leptons.cpp
# Hadrons.cpp
Event.cpp
)
create_library(EventDelphes EventDelphesSources)
