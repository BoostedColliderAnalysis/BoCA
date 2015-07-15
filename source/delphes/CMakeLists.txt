add_include_path(../../include/)
set(EventDelphesSources
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
create_library(EventDelphes EventDelphesSources)
