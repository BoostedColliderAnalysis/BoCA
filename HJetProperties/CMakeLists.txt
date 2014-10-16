set(IncludeDirectory
${IncludeDirectory}
${PROJECT_SOURCE_DIR}/HJetProperties
)
include_directories(${IncludeDirectory})

HDictionary(HJetPropertiesBranch HJetPropertiesBranch.cpp HJetPropertiesLinkDef.hh)

HLibrary(HAnalysisJetProperties HAnalysisJetProperties.cpp)

HExecutable(HJetProperties main.cpp)
