set(file "/home/toodles/madness/analysis/build/Mt2-prefix/src/mt2-1.01a.tar.gz")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "dd2d167abb23f4146c05fd0962fba6dc")
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
