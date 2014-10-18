
HDictionary(HBranchDiscriminator HBranchDiscriminator.cpp ../include/HDiscriminatorLinkDef.hh)

HLibrary(HJetDiscriminator HJetDiscriminator.cpp)

HExecutable(HJetDiscriminatorMain HJetDiscriminatorMain.cpp)

HLibrary(HAnalysisDiscriminator HAnalysisDiscriminator.cpp)
# HLibrary(HAnalysisDiscriminator HAnalysisOld.cpp)

HExecutable(HDiscriminator main.cpp)

HLibrary(HMvaDiscriminator HMvaDiscriminator.cpp)

HExecutable(HDiscriminatorFactory HFactory.cpp)

HExecutable(HDiscriminatorReader HReader.cpp)
