message(STATUS "downloading...
     src='http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=wimpmass-1.00.tar.gz'
     dst='/home/toodles/madness/analysis/build/WimpMass-prefix/src/wimpmass-1.00.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=wimpmass-1.00.tar.gz"
  "/home/toodles/madness/analysis/build/WimpMass-prefix/src/wimpmass-1.00.tar.gz"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=1068a6ab41bf52043dd42ce1cd88cbc2
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=wimpmass-1.00.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
