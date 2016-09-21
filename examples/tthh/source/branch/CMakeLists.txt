set(source
Global.cpp
Higgs.cpp
Signature.cpp
)

set(header
Global.hh
Higgs.hh
Signature.hh
)

create_dictionary(tthhBranches "${source}" "${header}" LinkDef.hh tthh branch)
