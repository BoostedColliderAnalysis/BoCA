set(file "/home/toodles/madness/analysis/build/WimpMass-prefix/src/wimpmass-1.00.tar.gz")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "1068a6ab41bf52043dd42ce1cd88cbc2")
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
