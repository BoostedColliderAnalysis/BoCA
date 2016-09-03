#
# Copyright (C) 2015-2016 Jan Hajer
#
set(TreeSources
Source.cpp
Io.cpp
TreeBranch.cpp
TreeReaderArray.cpp
TreeReader.cpp
TreeWriter.cpp
FileWriter.cpp
)
create_library(Trees TreeSources)

add_executable(root-browser Browser.cpp)
target_link_libraries(root-browser ${ROOT_LIBRARIES})
install (TARGETS root-browser DESTINATION "$ENV{HOME}/.bin")
