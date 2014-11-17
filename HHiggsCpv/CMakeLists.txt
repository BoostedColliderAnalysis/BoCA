
set(Directory
${PROJECT_SOURCE_DIR}/HHiggsCpv/include
${PROJECT_SOURCE_DIR}/HHiggsCpv/source
${PROJECT_SOURCE_DIR}/HBTagger/include
)

HInclude("${Directory}")

add_subdirectory(source)
