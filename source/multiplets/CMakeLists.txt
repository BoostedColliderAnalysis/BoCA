#
# Copyright (C) 2015-2016 Jan Hajer
#
set(multiplet_sources
Jet.cpp
Particle.cpp
JetInfo.cpp
ParticleInfo.cpp
Identification.cpp
Singlet.cpp
ClosestLepton.cpp
Multiplet.cpp
Doublet.cpp
Triplet.cpp
Quartet.cpp
Quintet.cpp
Sextet.cpp
Octet.cpp
Particles.cpp
GlobalObservables.cpp
)
create_library(Multiplets multiplet_sources)
