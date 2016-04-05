#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/io)

set(TreeSources
Io.cpp
TreeBranch.cpp
TreeReaderArray.cpp
TreeReader.cpp
TreeWriter.cpp
)
create_library(Trees TreeSources)
