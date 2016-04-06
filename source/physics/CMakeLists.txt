#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/)
set(PhysicsSources
Barn.cpp
ElectronVolt.cpp
Si.cpp
Particles.cpp
Member.cpp
Family.cpp
)
create_library(physics PhysicsSources)
