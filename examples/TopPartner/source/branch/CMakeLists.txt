set(TopPartnerBranchSources
Complete.cpp
HiggsTwoBody.cpp
NewEvent.cpp
NewEvent2.cpp
NewEvent3.cpp
NewEvent4.cpp
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
NewEvent.hh
NewEvent2.hh
NewEvent3.hh
NewEvent4.hh
SignatureEffective.hh
SignatureSingle.hh
SignatureSingleHadronic.hh
TopPartner.hh
Truth.hh
VetoTopPartner.hh
)

create_dictionary(TopPartnerBranches "${TopPartnerBranchSources}" "${TopPartnerBranchHeader}" LinkDefTopPartner.hh include branch)
