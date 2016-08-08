  SET(temp_directories
    ${include_directories}
  )


add_subdirectory(HiggsCpv)
  SET(include_directories
    ${temp_directories}
    CACHE INTERNAL include_directories FORCE
  )
add_subdirectory(heavyhiggs)
  SET(include_directories
    ${temp_directories}
    CACHE INTERNAL include_directories FORCE
  )
add_subdirectory(toppartner)
  SET(include_directories
    ${temp_directories}
    CACHE INTERNAL include_directories FORCE
  )
add_subdirectory(cut)
  SET(include_directories
    ${temp_directories}
    CACHE INTERNAL include_directories FORCE
  )
