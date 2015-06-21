message(STATUS "downloading...
     src='http://www.thphys.uni-heidelberg.de/~plehn/includes/heptoptagger/heptop_v1.0.tar.gz'
     dst='/home/toodles/madness/analysis/build/HepTopTagger-prefix/src/heptop_v1.0.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "http://www.thphys.uni-heidelberg.de/~plehn/includes/heptoptagger/heptop_v1.0.tar.gz"
  "/home/toodles/madness/analysis/build/HepTopTagger-prefix/src/heptop_v1.0.tar.gz"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=a92b1eaa8b009d32a3f5cc34b627d4d2
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://www.thphys.uni-heidelberg.de/~plehn/includes/heptoptagger/heptop_v1.0.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
