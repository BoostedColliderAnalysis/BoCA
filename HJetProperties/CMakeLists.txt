# HInclude(.)
HSource(.)

HDictionary(HJetPropertiesBranch HJetPropertiesBranch.cpp HJetPropertiesLinkDef.hh)

set(PropLib HAnalysisJetProperties.cpp)
HLibrary(HAnalysisJetProperties PropLib)

HExecutable(HJetProperties main.cpp)
