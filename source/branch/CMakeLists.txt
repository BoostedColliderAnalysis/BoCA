#
# Copyright (C) 2015-2016 Jan Hajer
#

set(source
Base.cpp
Info.cpp
Result.cpp
Bdt.cpp
Cut.cpp
Particle.cpp
TwoBody.cpp
Multi.cpp
ThreeBody.cpp
GlobalBase.cpp
Global.cpp
Event.cpp
EventShapes.cpp
Signature.cpp
)

set(header
Base.hh
Info.hh
Result.hh
Bdt.hh
Cut.hh
Particle.hh
TwoBody.hh
Multi.hh
ThreeBody.hh
GlobalBase.hh
Global.hh
Event.hh
EventShapes.hh
Signature.hh
)

create_dictionary(Branches "${source}" "${header}" LinkDef.hh boca branch)
