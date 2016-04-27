#
# Copyright (C) 2015-2016 Jan Hajer
#
set(TreeSources
Io.cpp
# Arrays.cpp
TreeBranch.cpp
TreeReaderArray.cpp
TreeReader.cpp
TreeWriter.cpp
FileWriter.cpp
)
create_library(Trees TreeSources)
