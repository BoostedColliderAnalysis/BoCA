set(TopPartnerBranchSources
Complete.cpp
HiggsTwoBody.cpp
Event.cpp
SignatureEffective.cpp
SignatureSingle.cpp
SignatureSingleHadronic.cpp
TopPartner.cpp
Truth.cpp
VetoTopPartner.cpp
)

set(TopPartnerBranchHeader
Complete.hh
HiggsTwoBody.hh
Event.hh
SignatureEffective.hh
SignatureSingle.hh
SignatureSingleHadronic.hh
TopPartner.hh
Truth.hh
VetoTopPartner.hh
)

create_dictionary(TopPartnerBranches "${TopPartnerBranchSources}" "${TopPartnerBranchHeader}" LinkDef.hh include branch)
