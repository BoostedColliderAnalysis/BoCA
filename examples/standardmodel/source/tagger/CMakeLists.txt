set(sm_tagger_sources
Tau.cpp
Bottom.cpp
Boson.cpp
WHadronic.cpp
WLeptonic.cpp
ZHadronic.cpp
Higgs.cpp
TopHadronic.cpp
TopLeptonic.cpp
Truth.cpp
Global.cpp
)
create_library(Sm sm_tagger_sources)

set(hep_tagger_source
TopHadronicHep.cpp
TopHadronicHep2.cpp
)
create_library(HepTagger hep_tagger_source)
