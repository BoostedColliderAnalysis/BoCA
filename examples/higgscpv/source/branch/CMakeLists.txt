set(HiggsCpvSources
Event.cpp
Octet.cpp
QuartetTwoBody.cpp
SignatureLepton.cpp
SignatureLeptonT.cpp
SignatureLeptonic.cpp
SignatureT.cpp
TopLeptonicTwoBody.cpp
TripletTwoBody.cpp
)

set(HiggsCpvHeader
Event.hh
Octet.hh
QuartetTwoBody.hh
SignatureLepton.hh
SignatureLeptonT.hh
SignatureLeptonic.hh
SignatureT.hh
TopLeptonicTwoBody.hh
TripletTwoBody.hh
)

create_dictionary(HiggsCpvBranches "${HiggsCpvSources}" "${HiggsCpvHeader}" LinkDefHiggsCpv.hh higgscpv branch)
