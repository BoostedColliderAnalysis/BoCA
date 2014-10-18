HInclude(${PROJECT_SOURCE_DIR}/HJetProperties)

HDictionary(HJetPropertiesBranch HJetPropertiesBranch.cpp HJetPropertiesLinkDef.hh)

HLibrary(HAnalysisJetProperties HAnalysisJetProperties.cpp)

HExecutable(HJetProperties main.cpp)
