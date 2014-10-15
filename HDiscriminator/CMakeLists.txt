set(IncludeDirectory
${IncludeDirectory}   
${PROJECT_SOURCE_DIR}/HDiscriminator/include
${PROJECT_SOURCE_DIR}/HDiscriminator/source
)
include_directories(${IncludeDirectory})

add_subdirectory(source)