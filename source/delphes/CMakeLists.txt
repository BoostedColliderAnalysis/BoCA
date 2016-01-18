#
# Copyright (C) 2015 Jan Hajer
#
add_include_path(../../include/)

# set(DelphesSources
# DelphesClasses.cc
# DelphesFactory.cc
# )
# create_library(Delphes DelphesSources)
# create_dictionary2(DelphesFactory DelphesFactory.cc ../include/delphes/ClassesLinkDef.h)
# create_dictionary2(Delphes DelphesClasses.cc ../include/delphes/ClassesLinkDef.h)

set(EventDelphesSources
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
create_library(EventDelphes EventDelphesSources)
