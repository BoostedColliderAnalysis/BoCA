add_include_path(.)
HSource(.)

create_dictionary(HJetPropertiesBranch HJetPropertiesBranch.cpp HJetPropertiesLinkDef.hh)

set(PropLib HAnalysisJetProperties.cpp)
create_library(HAnalysisJetProperties PropLib)

create_executable(HJetProperties main.cpp)
