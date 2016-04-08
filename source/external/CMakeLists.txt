#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/)
set(ExternalSources
Mt2.cpp
Invisible2.cpp
Invisible3.cpp
)
create_library(External ExternalSources)

set(HEPSources
TopTagger.cpp
QJets.cpp
QJetsPlugin.cpp
TopTaggerFixedR.cpp
TopTagger2.cpp
FWM.cc
LowPt.cc
QHTT.cc
)
create_library(HEP HEPSources)
