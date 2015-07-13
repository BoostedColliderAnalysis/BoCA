hinclude(.)
HDictionary(HBranchDiscriminator ./HBranchDiscriminator.cpp ../include/HDiscriminatorLinkDef.hh)

set(DiscriminatorLib
HAnalysisDiscriminator.cpp
HMvaDiscriminator.cpp
)
HLibrary(HAnalysisDiscriminator DiscriminatorLib)

HExecutable(HDiscriminator main.cpp)
HExecutable(HFactoryDiscriminator HFactory.cpp)
HExecutable(HReaderDiscriminator Reader.cpp)
