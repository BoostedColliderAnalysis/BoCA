set(file "/home/toodles/madness/analysis/build/HepTopTagger-prefix/src/heptop_v1.0.tar.gz")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "a92b1eaa8b009d32a3f5cc34b627d4d2")
file(MD5 "${file}" actual_value)
if("${actual_value}" STREQUAL "${expect_value}")
  message(STATUS "verifying file... done")
else()
  message(FATAL_ERROR "error: MD5 hash of
  ${file}
does not match expected value
  expected: ${expect_value}
    actual: ${actual_value}
")
endif()
