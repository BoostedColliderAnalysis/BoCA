set(source
Global.cpp
Higgs.cpp
HiggsSemiLeptonic.cpp
Signature.cpp
)

set(header
Global.hh
Higgs.hh
HiggsSemiLeptonic.hh
Signature.hh
)

create_dictionary(tthhBranches "${source}" "${header}" LinkDef.hh tthh branch)
