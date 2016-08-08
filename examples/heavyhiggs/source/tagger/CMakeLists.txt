set(HeavyHiggsTaggerSources
JetPair.cpp
TripletJetPair.cpp
HeavyHiggsLeptonic.cpp
HeavyHiggsSemi.cpp
HeavyHiggsTau.cpp
ChargedHiggsSemi.cpp
ChargedHiggsLeptonic.cpp
SignatureNeutral.cpp
SignatureCharged.cpp
EventNeutral.cpp
EventCharged.cpp
EventFusion.cpp
EventNeutralFourTop.cpp
Cut.cpp
CutNeutral.cpp

)
create_library(HeavyHiggsTagger HeavyHiggsTaggerSources)
