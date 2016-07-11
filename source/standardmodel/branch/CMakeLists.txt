#
# Copyright (C) 2015-2016 Jan Hajer
#

set(source
BottomBase.cpp
Bottom.cpp
Higgs.cpp
Tau.cpp
TopHadronic.cpp
TopHadronicHep.cpp
TopLeptonic.cpp
Truth.cpp
WHadronic.cpp
WLeptonic.cpp
ZHadronic.cpp
LeptonVeto.cpp
)

set(header
BottomBase.hh
Bottom.hh
Higgs.hh
Tau.hh
TopHadronic.hh
TopHadronicHep.hh
TopLeptonic.hh
Truth.hh
WHadronic.hh
WLeptonic.hh
ZHadronic.hh
LeptonVeto.hh
)

create_dictionary(SMBranches "${source}" "${header}" LinkDef.hh standardmodel branch)
