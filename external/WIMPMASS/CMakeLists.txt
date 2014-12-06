
set(Directory
${PROJECT_SOURCE_DIR}/external/WIMPMASS/WIMPMASS
# ${PROJECT_SOURCE_DIR}/external/WIMPMASS/examples
# ${PROJECT_SOURCE_DIR}/external/WIMPMASS/src
)
HInclude("${Directory}" SYSTEM)

add_subdirectory(src)
