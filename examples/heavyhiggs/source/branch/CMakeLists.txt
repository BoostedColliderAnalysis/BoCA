set(HeavyHiggsSources
ChargedHiggsLeptonic.cpp
ChargedHiggsSemi.cpp
Cut.cpp
CutNeutral.cpp
EventCharged.cpp
EventFusion.cpp
EventNeutral.cpp
EventNeutralFourTop.cpp
HeavyHiggsLeptonic.cpp
HeavyHiggsSemi.cpp
HeavyHiggsTau.cpp
OctetCharged.cpp
OctetNeutral.cpp
JetPair.cpp
TripletJetPair.cpp
)

set(HeavyHiggsHeader
ChargedHiggsLeptonic.hh
ChargedHiggsSemi.hh
Cut.hh
CutNeutral.hh
EventCharged.hh
EventFusion.hh
EventNeutral.hh
EventNeutralFourTop.hh
HeavyHiggsLeptonic.hh
HeavyHiggsSemi.hh
HeavyHiggsTau.hh
OctetCharged.hh
OctetNeutral.hh
JetPair.hh
TripletJetPair.hh
)

create_dictionary(HeavyHiggsBranches "${HeavyHiggsSources}" "${HeavyHiggsHeader}" LinkDefHeavyHiggs.hh include branch)
