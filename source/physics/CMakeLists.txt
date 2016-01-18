#
# Copyright (C) 2015 Jan Hajer
#
add_include_path(../../include/)
set(PhysicsSources
Math.cpp
LorentzVector.cpp
Barn.cpp
ElectronVolt.cpp
Si.cpp
Vector3.cpp
Particles.cpp
)
create_library(Physics PhysicsSources)
