#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/exroot)

set(ExRootSources
TreeBranch.cpp
TreeWriter.cpp
)
create_library(ExRootTree ExRootSources)

create_dictionary(ExRoot ExRootClasses.cc ../../include/exroot/ExRootAnalysisLinkDef.h exroot)

set(EventExRootSources
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
create_library(EventExRoot EventExRootSources)
