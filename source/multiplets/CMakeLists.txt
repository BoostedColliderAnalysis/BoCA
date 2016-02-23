#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/)

set(multiplet_sources
Singlet.cpp
Multiplet.cpp
Doublet.cpp
Triplet.cpp
Quartet.cpp
Quintet.cpp
Sextet.cpp
Octet.cpp
)
create_library(Multiplets multiplet_sources)
