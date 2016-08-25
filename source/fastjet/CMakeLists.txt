#
# Copyright (C) 2015-2016 Jan Hajer
#
set(fastjet_sources
PseudoJet.cpp
ClusterSequence.cpp
InfoRecombiner.cpp
SubJettiness.cpp
NSubJettiness.cpp
)
create_library(Fastjet fastjet_sources)
