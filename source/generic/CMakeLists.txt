#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/)
set(GenericSources
Debug.cpp
Exception.cpp
Options.cpp
)
create_library(Generic GenericSources)
