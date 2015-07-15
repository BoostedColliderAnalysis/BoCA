add_include_path(.)
create_dictionary(HBranchDiscriminator ./HBranchDiscriminator.cpp ../include/HDiscriminatorLinkDef.hh)

set(DiscriminatorLib
HAnalysisDiscriminator.cpp
HMvaDiscriminator.cpp
)
create_library(HAnalysisDiscriminator DiscriminatorLib)

create_executable(HDiscriminator main.cpp)
create_executable(HFactoryDiscriminator HFactory.cpp)
create_executable(HReaderDiscriminator Reader.cpp)
