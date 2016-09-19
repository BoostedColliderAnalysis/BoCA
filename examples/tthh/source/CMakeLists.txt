add_subdirectory(branch)
add_subdirectory(tagger)

set(tthhFiles
Observables.cpp
)
create_library(tthh tthhFiles)

create_executable(tthhAnalysis Maintthh.cpp)
