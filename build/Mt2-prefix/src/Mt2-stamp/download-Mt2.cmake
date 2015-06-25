message(STATUS "downloading...
     src='http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=mt2-1.01a.tar.gz'
     dst='/home/toodles/madness/analysis/build/Mt2-prefix/src/mt2-1.01a.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=mt2-1.01a.tar.gz"
  "/home/toodles/madness/analysis/build/Mt2-prefix/src/mt2-1.01a.tar.gz"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=dd2d167abb23f4146c05fd0962fba6dc
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://particle.physics.ucdavis.edu/hefti/projects/lib/exe/fetch.php?media=mt2-1.01a.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
