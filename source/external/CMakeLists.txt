#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/)
set(ExternalSources
# mt2_bisect.cpp
Invisible2.cpp
# Invisible3.cpp
)
create_library(External ExternalSources)

set(HEPSources
TopTagger.cpp
)
create_library(HEP HEPSources)
