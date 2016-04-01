#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/)
set(ExternalSources
TopTagger.cpp
mt2_bisect.cpp
PolynomialRoots.cpp
Invisible2.cpp
Invisible3.cpp
)
create_library(External ExternalSources)

