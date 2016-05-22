#
# Copyright (C) 2015-2016 Jan Hajer
#
set(ExternalSources
Mt2.cpp
Invisible2.cpp
Invisible3.cpp
)
create_library(External ExternalSources)

set(QJetSources
QJets.cpp
QJetsPlugin.cpp
)
create_library(QJet QJetSources)

set(HEPSources
TopTagger.cpp
TopTaggerFixedR.cpp
TopTagger2.cpp
FWM.cc
LowPt.cc
QHTT.cc
)
create_library(HEP HEPSources)

set(BoostedBSources
# TopTagger.cpp
# TopTaggerFixedR.cpp
# TopTagger2.cpp
# FWM.cc
# LowPt.cc
# QHTT.cc
MuXboostedBTagging.cpp
)
create_library(BoostedB BoostedBSources)
